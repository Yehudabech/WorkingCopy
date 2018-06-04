/* ========================================
 * Written by Yehuda Ben Chaim
 * 06/2018 Israel
 * All Rights Reserved
 * WW FW Version 1.0.0.0

 * ========================================
*/
#include <project.h>
#define CCC_HANDLE				(0x000F)
#define CCC_DATA_LEN					(2)
#define CCC_DATA_INDEX					(0u)
#define CHAR_HANDLE (0x000E) //TBD
#define CHAR_DATA_LEN			(1)
#define CY_TEST_FLASH_ROW       (CY_FLASH_NUMBER_ROWS - 2u)
#define CY_TEST_FLASH_ADDR      (CY_TEST_FLASH_ROW * CY_FLASH_SIZEOF_ROW)
extern uint8 LPMselData; 
/* Minimum connection interval = CONN_PARAM_UPDATE_MIN_CONN_INTERVAL * 1.25 ms*/
#define CONN_PARAM_UPDATE_MIN_CONN_INTERVAL	100        	
/* Maximum connection interval = CONN_PARAM_UPDATE_MAX_CONN_INTERVAL * 1.25 ms */
#define CONN_PARAM_UPDATE_MAX_CONN_INTERVAL	110        	
/* Slave latency = Number of connection events */
#define CONN_PARAM_UPDATE_SLAVE_LATENCY		0          
/* Supervision timeout = CONN_PARAM_UPDATE_SUPRV_TIMEOUT * 10*/
#define CONN_PARAM_UPDATE_SUPRV_TIMEOUT		200     

void CustomEventHandler(uint32 event, void * eventParam);
void UpdateNotificationCCCD(void);
void SendReedSwitchNotification(uint8 ReedData);
void UpdateConnectionParam(void);
void Write_pass_to_flash(void);
//void Update_password(void);
void Update_password(uint8_t val[2]);
uint8_t password[8];
/* [] END OF FILE */
