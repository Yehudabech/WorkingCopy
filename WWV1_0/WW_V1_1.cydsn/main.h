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
#include <project.h>
#include <stdbool.h>
#define TRUE							(1)
#define FALSE							(0)
#define ZERO							(0)
#define ENABLE_LOW_POWER_MODE
#define HIGH                            (1)
#define LOW                             (0)
extern bool User_RST;
extern uint8 Notification_Data;
extern bool RST_flag;
CYBLE_GAP_BD_ADDR_T Peer_Addr;
void Application_ManagePower(void);