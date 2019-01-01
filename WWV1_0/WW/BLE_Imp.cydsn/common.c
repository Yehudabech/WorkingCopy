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

/**** Includes *****************************************/
#include "common.h"
#include "BuzzerImp.h"
#include "LEDs.h"
/**** Private functions decleration *******************/

/**** Private functions *******************************/


/**************************************************************
* Name: TasksScheduler
* Parameters[in]: None
* Return: None
* Description: This function run the timing for all time based
* tasks in RT.

************************************************************/
void TasksScheduler(void)
{
  BuzzerBeepGetClockVal(SysTickGet());
  LED_BlinkpGetClockVal(SysTickGet());
}

/* [] END OF FILE */
