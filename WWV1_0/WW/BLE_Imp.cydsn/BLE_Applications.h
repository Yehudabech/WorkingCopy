/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/**** Includes *************************************/
#include "project.h"
#include "iprintf.h"


/**** Defines ***************************************/

/**** Private functions decleration *****************/
void CustomEventHandler(uint32, void *);
void OutgoingDataUpdate(uint8_t *Arr2Print);
void BLE_IsConnectedSet(uint8_t status);
uint8_t BLE_IsConnectedGet(void);
void DataUpdateSet(uint8_t status);
uint8_t DataUpdateGet(void);

/* [] END OF FILE */
