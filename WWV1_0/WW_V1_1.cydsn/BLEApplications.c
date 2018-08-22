/* ========================================
 * Written by Yehuda Ben Chaim
 * 06/2018 Israel
 * All Rights Reserved
 * WW FW Version 1.0.0.0

 * ========================================
*/

#include <BLEApplications.h>
#include "main.h"
#include <stdbool.h>
#include <CyFlash.h>
#include "iprintf.h"

#define CYREG_SRSS_TST_DDFT_CTRL 0x40030008
CYBLE_GATT_HANDLE_VALUE_PAIR_T		rgbHandle;	
uint8 ReedSwitchNotifications = FALSE;	
uint8 updateNotificationCCCAttribute = FALSE;
CYBLE_CONN_HANDLE_T  connectionHandle;
CYBLE_GAP_BD_ADDR_T Peer_Addr;
uint8 Addr_arr[7];
uint8 Addr_compare[6];
uint8 CompareResult = 0;
CYBLE_GAP_BONDED_DEV_ADDR_LIST_T Peer_Addr1;
uint8                   AddrNibble;     //Actual value derived from INPUT ASCII value
uint8                  MAC_Letters;//Character Input from the UART Terminal
CYBLE_GAP_BD_ADDR_T     whitelistdeviceaddress;
uint8 Count = 0;        //Count of the Characters from UART while 
uint8* readptr ;
uint8 byte_count = 0;
bool MAC_Addr_Flag = FALSE;
bool OK_To_Connect = FALSE;
bool User_RST = FALSE;
uint8 Addr_in_flash_flag = 0;
cystatus WriteStatus = CYRET_SUCCESS;
uint8 deviceConnected = FALSE;
uint8 restartAdvertisement = FALSE;
uint8_t password[4];        //This array is for storing the incoming data from the BLE
uint8_t pass[2];
static CYBLE_GATT_HANDLE_VALUE_PAIR_T        readHandle;
static uint8 isConnectionUpdateRequested = TRUE;
static CYBLE_GAP_CONN_UPDATE_PARAM_T ConnectionParam =
{
    CONN_PARAM_UPDATE_MIN_CONN_INTERVAL,  		      
    CONN_PARAM_UPDATE_MAX_CONN_INTERVAL,		       
    CONN_PARAM_UPDATE_SLAVE_LATENCY,			    
    CONN_PARAM_UPDATE_SUPRV_TIMEOUT 			         	
};

void CustomEventHandler(uint32 event, void * eventParam)
{
	CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;
   
    switch(event)
    {
        case CYBLE_EVT_STACK_ON:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            /* Enable the Skyworks SE2438T PA/LNA */
            CSD_Write(1);
            CPS_Write(1);
             /* Configure the Link Layer to automatically switch PA control pin P3[2] and LNA control pin P3[3] */
            CY_SET_XTND_REG32((void CYFAR *)(CYREG_BLE_BLESS_RF_CONFIG), 0x0331);
            CY_SET_XTND_REG32((void CYFAR *)(CYREG_SRSS_TST_DDFT_CTRL), 0x80000302);
            /* Start Advertisement and enter Discoverable mode*/
			
                break;
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
			/* Start Advertisement and enter Discoverable mode*/
			CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
			break;
			
		case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
			/* Set the BLE state variable to control LED status */
            if(CYBLE_STATE_DISCONNECTED == CyBle_GetState())
            {
                /* Start Advertisement and enter Discoverable mode*/
                CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            }
			break;
			
        case CYBLE_EVT_GATT_CONNECT_IND:
            /* This event is received when device is connected over GATT level */
            /* Update attribute handle on GATT Connection*/
            connectionHandle = *(CYBLE_CONN_HANDLE_T *) eventParam;
            CyBle_GapGetBondedDevicesList(&Peer_Addr1);
            deviceConnected = TRUE;
			break;
        
        case CYBLE_EVT_GATT_DISCONNECT_IND:			
			/* Reset CapSense notification flag to prevent further notifications
			 * being sent to Central device after next connection. */
			ReedSwitchNotifications = FALSE;
			deviceConnected = FALSE;
			/* Reset the CCCD value to disable notifications */
			updateNotificationCCCAttribute = TRUE;
			
			/* Reset the color coordinates */
			break; 
        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
            
            break;
        case CYBLE_EVT_GATTS_WRITE_REQ: 							
            /* This event is received when Central device sends a Write command 
             * on an Attribute. 
             * We first get the attribute handle from the event parameter and 
             * then try to match that handle with an attribute in the database.
             */
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
 

			if(CYBLE_WW_SERVICE_INCOMINGDATA_CHAR_HANDLE == wrReqParam->handleValPair.attrHandle )
           {      
               password[0] = wrReqParam->handleValPair.value.val[0];
               password[1] = wrReqParam->handleValPair.value.val[1];
                
                iprintf("The value of the password[o] is %x\n\r", password[0]);
                iprintf("The value of the password[1] is %x\n\r", password[1]);
           
               CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, ZERO, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
           }
			/* ADD_CODE to send the response to the write request received. */
			CyBle_GattsWriteRsp(cyBle_connHandle);
			
			break;
            
            /* Mandatory events to be handled by BLE application code */
        
        default:

       	 	break;
    }
}


/*******************************************************************************
* Function Name: UpdateNotificationCCCD
********************************************************************************
* Summary:
* Update the data handle for notification status and report it to BLE 
* component so that it can be read by Central device.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void UpdateNotificationCCCD(void)
{
	/* Handle value to update the CCCD */
	CYBLE_GATT_HANDLE_VALUE_PAIR_T NotificationCCCDhandle;
	
	/* Update notification attribute only when there has been change */
	if(updateNotificationCCCAttribute)
	{
		updateNotificationCCCAttribute = FALSE;
	
		/* Update CCCD handle with notification status data*/
		NotificationCCCDhandle.attrHandle =  CYBLE_WW_SERVICE_OUTGOINGDATA_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE;
		NotificationCCCDhandle.value.val = &Notification_Data;//CCCDvalue;
		NotificationCCCDhandle.value.len = CCC_DATA_LEN;
		
		/* Report data to BLE component for sending data when read by Central device */
		CyBle_GattsWriteAttributeValue(&NotificationCCCDhandle, ZERO, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
		
		/* Register the updated attribute write value to BLE component once before
		* updating the next CCCD attribute value */
		CyBle_ProcessEvents();
	}	
}

/*******************************************************************************
* Function Name: SendReedSwitchNotification
********************************************************************************
* Summary:
* Send CapSense Slider data as BLE Notifications. This function updates
* the notification handle with data and triggers the BLE component to send 
* notification
*
* Parameters:
*  ReedData:	CapSense slider value	
*
* Return:
*  void
*
*******************************************************************************/
void    SendReedSwitchNotification(uint8 *ReedData)
{
	/* 'ReednotificationHandle' stores CapSense notification data parameters */
	CYBLE_GATTS_HANDLE_VALUE_NTF_T		OutgoingNotificationsHandle;	
	
	/* Update notification handle with CapSense slider data*/
	OutgoingNotificationsHandle.attrHandle = CYBLE_WW_SERVICE_CUSTOM_CHARACTERISTIC_CHAR_HANDLE;				
	OutgoingNotificationsHandle.value.val = (void*)ReedData;
	OutgoingNotificationsHandle.value.len = CHAR_DATA_LEN;
	
	/* Send notifications. */
	CyBle_GattsNotification(cyBle_connHandle, &OutgoingNotificationsHandle);
}

void UpdateConnectionParam(void)
{
	/* If device is connected and Update connection parameter not updated yet,
	* then send the Connection Parameter Update request to Client. */
    if(deviceConnected && isConnectionUpdateRequested)
	{
		/* Reset the flag to indicate that connection Update request has been sent */
		isConnectionUpdateRequested = FALSE;
		
		/* Send Connection Update request with set Parameter */
		CyBle_L2capLeConnectionParamUpdateRequest(cyBle_connHandle.bdHandle, &ConnectionParam);
	}
}


/*******************************************************************************
* Function Name: Write_pass_to_flash
********************************************************************************
* Summary:
* Write the current password to flash and also zeros if the user elapsed the password.
*
* Parameters:
*  None
*
* Return:
*  void
*******************************************************************************/
void Write_pass_to_flash()
{
    if(RST_flag)
    {
        //password[0] = 0x00;
       // password[1] = 0x00;
        CySysFlashWriteRow(CY_TEST_FLASH_ROW, password); 
        //Update_password(password);
        RST_flag = FALSE;
    }
    else
    {
        CySysFlashWriteRow(CY_TEST_FLASH_ROW, password); 
        pass[0] = (*((uint8 *) (CY_TEST_FLASH_ADDR)));
        pass[1] = (*((uint8 *) (CY_TEST_FLASH_ADDR + 1)));
        //Update_password(password);
        RST_flag = FALSE;
    }
}



/* [] END OF FILE */
