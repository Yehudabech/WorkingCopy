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

/**** File general variables *************************************************************/
CYBLE_CONN_HANDLE_T  connectionHandle;
uint8 deviceConnected = 0;
CYBLE_GAP_BONDED_DEV_ADDR_LIST_T Peer_Addr1;

uint8_t password[2] = {0};



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

/* [] END OF FILE */
