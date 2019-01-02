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

/**** Includes ****************************************/
#include "project.h"
#include "common.h"
/**** Exported Defines ********************************/

/**** Exported Typdefs ********************************/

enum
{
  GREEN_LED,
  YELLOW_LED,
  RED_LED
};

/**** Exported functions decleration ******************/

/**** Exported functions ******************************/

/**************************************************************
* Name: LED_BlinkStart
* Parameters[in]: uint32_t Interval
* Return: None
* Description: This function sets a repeatable blink with interval
* set by the user. To stop the operation, call LED_BlinkStop() funcion.

************************************************************/
void LED_BlinkStart(uint32_t Interval, uint8_t Color);


/**************************************************************
* Name: LED_BlinkStop
* Parameters[in]: uint8_t Color
* Return: None
* Description: This function stop LEDs color from blinking
* fucntion

************************************************************/
void LED_BlinkStop(uint8_t Color);


/**************************************************************
* Name: LED_BlinkReload
* Parameters[in]: uint8_t Color
* Return: None
* Description: This function reload the value for the timer
* of the current LED and update the value of the status flag

************************************************************/
void LED_BlinkReload(uint8_t Color);


/**************************************************************
* Name: LED_BlinkpGetClockVal
* Parameters[in]: uint32_t CurrenTime
* Return: None
* Description: This function receive the current time of the 
* tick timer and compare it with value sampled last time.

************************************************************/
void LED_BlinkpGetClockVal(uint32_t CurrenTime);



/**************************************************************
* Name: TurnON_LED
* Parameters[in]: uint8_t Color
* Return: None
* Description: This function turns ON Color led

************************************************************/
void TurnON_LED(uint8_t Color);



/**************************************************************
* Name: TurnOFF_LED
* Parameters[in]: uint8_t Color
* Return: None
* Description: This function turns OFF Color led

************************************************************/
void TurnOFF_LED(uint8_t Color);



/* [] END OF FILE */