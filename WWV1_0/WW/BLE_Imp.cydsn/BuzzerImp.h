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
#include "project.h"
#include "common.h"
#include "main.h"

/**** Defines *****************************************/

/**** Private functions decleration *******************/

/**** Private functions *******************************/

/**************************************************************
* Name: BuzzerBeepStart
* Parameters[in]: uint32_t Interval
* Return: None
* Description: This function sets a repeatable beep with interval
* set by the user. To stop the operation, call BuzzerBeepStop() funcion.

************************************************************/
void BuzzerBeepStart(uint32_t Interval);


/**************************************************************
* Name: BuzzerBeepStop
* Parameters[in]: None
* Return: None
* Description: This function the beep set by BuzzerBeepStart
* fucntion

************************************************************/
void BuzzerBeepStop(void);



/**************************************************************
* Name: BuzzerBeepReload
* Parameters[in]: None
* Return: None
* Description: This function reload the value for the timer
* of the buzzer and update the value of the status flag

************************************************************/
void BuzzerBeepReload(void);



/**************************************************************
* Name: BuzzerBeepGetClockVal
* Parameters[in]: uint32_t CurrenTime
* Return: None
* Description: This function receive the current time of the 
* tick timer and compare it with value sampled last time.

************************************************************/
void BuzzerBeepGetClockVal(uint32_t CurrenTime);
/* [] END OF FILE */
