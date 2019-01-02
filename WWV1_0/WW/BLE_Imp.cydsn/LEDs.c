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
#include "LEDs.h"
#include "RedLED.h"
#include "GreenLED.h"
#include "YellowLED.h"
/**** Private Defines *********************************/

/**** Private Typdefs *********************************/
/*Green LED*/
static uint32_t TimeSample4GreenLED = 0;
static uint8_t GreenLED_Status = OFF;
static uint8_t GreenLED_BlinkIsSetFlag = FALSE;
static uint32_t GreenLED_LocalInterval = 0;

/*Red LED*/
static uint32_t TimeSample4RedLED = 0;
static uint8_t RedLED_Status = OFF;
static uint8_t RedLED_BlinkIsSetFlag = FALSE;
static uint32_t RedLED_LocalInterval = 0;

/*Yellow LED*/
static uint32_t TimeSample4YellowLED = 0;
static uint8_t YellowLED_Status = OFF;
static uint8_t YellowLED_BlinkIsSetFlag = FALSE;
static uint32_t YellowLED_LocalInterval = 0;



/**** Private functions decleration *******************/

/**** Private functions *******************************/


/**************************************************************
* Name: LED_BlinkStart
* Parameters[in]: uint32_t Interval
* Return: None
* Description: This function sets a repeatable blink with interval
* set by the user. To stop the operation, call LED_BlinkStop() funcion.

************************************************************/
void LED_BlinkStart(uint32_t Interval, uint8_t Color)
{                                                  
  if(Color == GREEN_LED)
  {
    GreenLED_LocalInterval = Interval; 
    TimeSample4GreenLED = SysTickGet();
    GreenLED_Write(ON);
    GreenLED_Status = ON;
    GreenLED_BlinkIsSetFlag = TRUE;
  }
  else if(Color == YELLOW_LED)
  {
    YellowLED_LocalInterval = Interval; 
    TimeSample4YellowLED = SysTickGet();
    YellowLED_Write(ON);
    YellowLED_Status = ON;
    YellowLED_BlinkIsSetFlag = TRUE;
  }
  else if(Color == RED_LED)
  {
    RedLED_LocalInterval = Interval; 
    TimeSample4RedLED = SysTickGet();
    RedLED_Write(ON);
    RedLED_Status = ON;
    RedLED_BlinkIsSetFlag = TRUE;
  }
}


/**************************************************************
* Name: LED_BlinkStop
* Parameters[in]: uint8_t Color
* Return: None
* Description: This function stop LEDs color from blinking
* fucntion

************************************************************/
void LED_BlinkStop(uint8_t Color)
{
  if(Color == GREEN_LED)
  {
    GreenLED_Write(OFF);
    GreenLED_Status = OFF;
    GreenLED_BlinkIsSetFlag = FALSE;
  }
  else if(Color == YELLOW_LED)
  {
    YellowLED_Write(OFF);
    YellowLED_Status = OFF;
    YellowLED_BlinkIsSetFlag = FALSE;
  }
  else if(Color == RED_LED)
  {
    RedLED_Write(OFF);
    RedLED_Status = OFF;
    RedLED_BlinkIsSetFlag = FALSE;
  }
}


/**************************************************************
* Name: LED_BlinkReload
* Parameters[in]: uint8_t Color
* Return: None
* Description: This function reload the value for the timer
* of the current LED and update the value of the status flag

************************************************************/
void LED_BlinkReload(uint8_t Color)
{
  if(Color == GREEN_LED)
  {
    TimeSample4GreenLED = SysTickGet();
    if(GreenLED_BlinkIsSetFlag == TRUE)
    {
      if(GreenLED_Status == ON)
      {
        GreenLED_Status = OFF;
        GreenLED_Write(OFF);
      }
      else if(GreenLED_Status == OFF)
      {
        GreenLED_Status = ON;
        GreenLED_Write(ON);
      }
    }
  }
  else if(Color == YELLOW_LED)
  {
    TimeSample4YellowLED = SysTickGet();
    if(YellowLED_BlinkIsSetFlag == TRUE)
    {
      if(YellowLED_Status == ON)
      {
        YellowLED_Status = OFF;
        YellowLED_Write(OFF);
      }
      else if(YellowLED_Status == OFF)
      {
        YellowLED_Status = ON;
        YellowLED_Write(ON);
      }
    }
  }
  else if(Color == RED_LED)
  {
    TimeSample4RedLED = SysTickGet();
    if(RedLED_BlinkIsSetFlag == TRUE)
    {
      if(RedLED_Status == ON)
      {
        RedLED_Status = OFF;
        RedLED_Write(OFF);
      }
      else if(RedLED_Status == OFF)
      {
        RedLED_Status = ON;
        RedLED_Write(ON);
      }
    }
  }
}



/**************************************************************
* Name: LED_BlinkpGetClockVal
* Parameters[in]: uint32_t CurrenTime
* Return: None
* Description: This function receive the current time of the 
* tick timer and compare it with value sampled last time.

************************************************************/
void LED_BlinkpGetClockVal(uint32_t CurrenTime)
{
  if(CurrenTime - TimeSample4RedLED > RedLED_LocalInterval)
  {
    LED_BlinkReload(RED_LED);
  }
  if(CurrenTime - TimeSample4YellowLED > YellowLED_LocalInterval)
  {
    LED_BlinkReload(YELLOW_LED);
  }
  if(CurrenTime - TimeSample4GreenLED > GreenLED_LocalInterval)
  {
    LED_BlinkReload(GREEN_LED);
  }
}



/**************************************************************
* Name: TurnON_LED
* Parameters[in]: uint8_t Color
* Return: None
* Description: This function turns ON Color led

************************************************************/
void TurnON_LED(uint8_t Color)
{
  if(Color == GREEN_LED)
    GreenLED_Write(ON);
  else if(Color == YELLOW_LED)
    YellowLED_Write(ON);
  else if(Color == RED_LED)
    RedLED_Write(ON);
}



/**************************************************************
* Name: TurnOFF_LED
* Parameters[in]: uint8_t Color
* Return: None
* Description: This function turns OFF Color led

************************************************************/
void TurnOFF_LED(uint8_t Color)
{
  if(Color == GREEN_LED)
    GreenLED_Write(OFF);
  else if(Color == YELLOW_LED)
    YellowLED_Write(OFF);
  else if(Color == RED_LED)
    RedLED_Write(OFF);
}

/* [] END OF FILE */
