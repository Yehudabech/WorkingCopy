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
#include "BuzzerImp.h"
#include "Buzzer.h"

/**** Defines *****************************************/

/**** Private variables decleration *******************/

static uint32_t TimeSample4Buzzer = 0;
static uint32_t BuzzerLocalInterval = 0;
static uint8_t BuzzerStatus = OFF;
static uint8_t BuzzerBeepIsSetFlag = FALSE;

/**** Private functions decleration *******************/

/**** Private functions *******************************/


/**************************************************************
* Name: BuzzerBeepStart
* Parameters[in]: uint32_t Interval
* Return: None
* Description: This function sets a repeatable beep with interval
* set by the user. To stop the operation, call BuzzerBeepStop() funcion.

************************************************************/
void BuzzerBeepStart(uint32_t Interval)
{
  TimeSample4Buzzer = SysTickGet();
  BuzzerLocalInterval = Interval;                               //Set the interval from the user to the local variable for later use
  BuzzerPWM_Stop();                                             //Stop the buzzer the make its status well known        
  BuzzerPWM_Start();                                            //Now start the buzzer
  BuzzerStatus = ON;                                                  //Set the value of status to be ON, for the
  
  BuzzerBeepIsSetFlag = TRUE;
}


/**************************************************************
* Name: BuzzerBeepStop
* Parameters[in]: None
* Return: None
* Description: This function the beep set by BuzzerBeepStart
* fucntion

************************************************************/
void BuzzerBeepStop(void)
{
  BuzzerPWM_Stop();
  BuzzerStatus = OFF;
  BuzzerBeepIsSetFlag = FALSE;
}


/**************************************************************
* Name: BuzzerBeepReload
* Parameters[in]: None
* Return: None
* Description: This function reload the value for the timer
* of the buzzer and update the value of the status flag

************************************************************/
void BuzzerBeepReload(void)
{
  TimeSample4Buzzer = SysTickGet();
  if(BuzzerBeepIsSetFlag == TRUE)
  {
    if(BuzzerStatus == ON)
    {
      BuzzerStatus = OFF;
      BuzzerPWM_Stop();
    }
    else if(BuzzerStatus == OFF)
    {
      BuzzerStatus = ON;
      BuzzerPWM_Start();
    }
  }
}



/**************************************************************
* Name: BuzzerBeepGetClockVal
* Parameters[in]: uint32_t CurrenTime
* Return: None
* Description: This function receive the current time of the 
* tick timer and compare it with value sampled last time.

************************************************************/
void BuzzerBeepGetClockVal(uint32_t CurrenTime)
{
  if(CurrenTime - TimeSample4Buzzer > BuzzerLocalInterval)
  {
    BuzzerBeepReload();
  }
}


/**************************************************************
* Name: BuzzerActive
* Parameters[in]: uint32_t Interval
* Return: None
* Description: This function activate the buzzer for Interval
* period of time, with blocking.

************************************************************/
void BuzzerActive(uint32_t Interval)
{
  BuzzerPWM_Start();
  CyDelay(Interval);
  BuzzerPWM_Stop();
}



/* [] END OF FILE */
