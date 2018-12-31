/* ========================================
 *
 * Copyright Yehuda Ben Chaim, 2018
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Yehuda Ben Chaim.
 *
 * ========================================
*/

/**** Includes ***************************************************************************/

#include "BLE_Applications.h"
#include "GPIO.h"
#include "project.h"

/**** File general variables *************************************************************/
CYBLE_CONN_HANDLE_T  connectionHandle;
uint8 deviceConnected = 0;
CYBLE_GAP_BONDED_DEV_ADDR_LIST_T Peer_Addr1;

uint8_t password[2] = {0};

uint8_t BLE_IsConnectedFlag = 0;
uint8_t DataUpdateFlag = 0;



/*** Private functions ******************************************************************/

/*************************************************************
* Name: CustomEventHandler
* Parameters[in]: uint32 event
*                 void * eventParam
* Return: None
* Description: This fuction is the handler of the BLE.

************************************************************/

void CustomEventHandler(uint32 event, void * eventParam)
{
	CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;
   
    switch(event)
    {
        case CYBLE_EVT_STACK_ON:
            /* Start Advertisement and enter Discoverable mode*/
			CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
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
            deviceConnected = 1;
			break;
        
        case CYBLE_EVT_GATT_DISCONNECT_IND:			
			iprintf("Device disconnected\n\r");
			break; 
        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
            iprintf("Device connected\n\r");
            BLE_IsConnectedSet(1);
            break;
        case CYBLE_EVT_GATTC_HANDLE_VALUE_NTF:
          //  CyBle_NotificationEventHandler((CYBLE_GATTC_HANDLE_VALUE_NTF_PARAM_T *)eventParam);
            break;
        case CYBLE_EVT_GATTS_WRITE_REQ: 							
            /* This event is received when Central device sends a Write command 
             * on an Attribute. 
             * We first get the attribute handle from the event parameter and 
             * then try to match that handle with an attribute in the database.
             */
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
            /* This condition checks whether the CCCD descriptor for CapSense
             * slider characteristic has been written to. This tells us whether
             * the notifications for CapSense slider have been enabled/disabled.
             */
            
            if(wrReqParam->handleValPair.attrHandle == cyBle_customs[CYBLE_WW_SERVICE_SERVICE_INDEX].\
				customServiceInfo[CYBLE_WW_SERVICE_INCOMINGDATA_CHAR_INDEX].customServiceCharDescriptors[CYBLE_WW_SERVICE_INCOMINGDATA_CHAR_INDEX])
            {
                //TESTARR = wrReqParam->handleValPair.value.val[0];
				
				/* Set flag to allow CCCD to be updated for next read operation */
				//TESTARR1 = 1;
            }

			if(CYBLE_WW_SERVICE_INCOMINGDATA_CHAR_HANDLE == wrReqParam->handleValPair.attrHandle )
           {      
               password[0] = wrReqParam->handleValPair.value.val[0];
               password[1] = wrReqParam->handleValPair.value.val[1];
               if(password[0] == 0x05)
               {
                 OperationsMain(password[1]);
                 //iprintf("It's 5!!!\n\r");
               }
               else
               {
                 DataUpdateSet(0);
                 iprintf("It's not 5!!!\n\r");
               }
                iprintf("The first value is: %x and the second value is: %x\n\r", password[0], password[1]);
               //CyBle_GattsWriteAttributeValue(&wrReqParam->handleValPair, ZERO, &cyBle_connHandle, CYBLE_GATT_DB_PEER_INITIATED);
           }
			/* ADD_CODE to send the response to the write request received. */
            
			CyBle_GattsWriteRsp(cyBle_connHandle);
			
			break;

        default:

       	 	break;
    }
}


void OutgoingDataUpdate(uint8_t *Arr2Print)
{
  CYBLE_GATTS_HANDLE_VALUE_NTF_T OutgoingNTF_Hnadler;
  
  OutgoingNTF_Hnadler.attrHandle = CYBLE_WW_SERVICE_OUTGOINGDATA_CHAR_HANDLE;	
  OutgoingNTF_Hnadler.value.val = Arr2Print;
  OutgoingNTF_Hnadler.value.len = 20;
  CyBle_GattsNotification(cyBle_connHandle, &OutgoingNTF_Hnadler);
  
  
}


void BLE_IsConnectedSet(uint8_t status)
{
  BLE_IsConnectedFlag = status;
}

uint8_t BLE_IsConnectedGet(void)
{
  return BLE_IsConnectedFlag;
}



void DataUpdateSet(uint8_t status)
{
  DataUpdateFlag = status;
}

uint8_t DataUpdateGet(void)
{
  return DataUpdateFlag;
}

/* [] END OF FILE */
