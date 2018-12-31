/*******************************************************************************
* File Name: SysTimers_1.c
* Version 1.0
*
* Description:
*  This file provides source code for the System Timers component's API.
*
* 6-26-2013  MEH  Initial Creation
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CyLib.h"
#include <device.h>
#include "SysTimers_1.h"

volatile uint32  SysTimers_1_TimerSCount[SysTimers_1_TIMERS];
volatile uint32  SysTimers_1_TimerPeriod[SysTimers_1_TIMERS];
volatile uint32  SysTimers_1_TimerStatus[SysTimers_1_TIMERS];
volatile uint32  SysTimers_1_SysTickCount;

uint8 SysTimers_1_initVar = 0u;

/*******************************************************************************
* Function Name: SysTimers_1_Start
********************************************************************************
*
* Summary:
*  Initializes all the timers to initial condition.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void    SysTimers_1_Start(void)
{
    uint32 index;
	
	if( SysTimers_1_initVar == 0 )
	{
	    SysTimers_1_initVar = 1; 
	    for(index=0; index < SysTimers_1_TIMERS; index++)
		{
		    SysTimers_1_TimerSCount[index] = SysTimers_1_INVALID_PERIOD;
			SysTimers_1_TimerPeriod[index] = SysTimers_1_INVALID_PERIOD;
			SysTimers_1_TimerStatus[index] = SysTimers_1_NOT_IN_USE;	
		}
		CyIntSetSysVector(SysTimers_1_SYSTICK_IRQN, SysTimers_1_SysTickISR);
    }
	SysTick_Config(SysTimers_1_SYSTICK_PERIOD);
}


/*******************************************************************************
* Function Name: SysTimers_1_SysTickISR
********************************************************************************
*
* Summary:
*  The ISR takes care of all the timing functions.  The user sets the interrupt
*  (or resolution) of the timers which determine the rate at which the ISR is
*  triggered.  The ISR overhead is a function of the interrupt frequency, the
*  number of timers, and the System clock setting.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
CY_ISR(SysTimers_1_SysTickISR)
{

#if(SysTimers_1_TIMER_MODE == SysTimers_1_MODE_FAST_IRQ)
    /* Fast efficient ISR */
    SysTimers_1_SysTickCount++;
	
#else  /* This method takes longer but all timers are kept up to date */
    static uint32 index;
	SysTimers_1_SysTickCount++;
	
	for(index = 0; index < SysTimers_1_TIMERS; index++)
	{
	    SysTimers_1_TimerSCount[index]--;
		if(SysTimers_1_TimerSCount[index] == 0)
		{
		    SysTimers_1_TimerStatus[index] |= SysTimers_1_ALARM;
			SysTimers_1_TimerStatus[index]++;  /* Increment the alarm count */
			SysTimers_1_TimerSCount[index]  = SysTimers_1_TimerPeriod[index];
		}
	}
#endif
}

/*******************************************************************************
* Function Name: SysTimers_1_Init
********************************************************************************
*
* Summary:
*  Disables interrupts
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void    SysTimers_1_Stop(void)
{
    SysTick->CTRL  = 0u;  /* Disable interrupt and deactivate timer */
}
/*******************************************************************************
* Function Name: SysTimers_1_GetTimer
********************************************************************************
*
* Summary:
*  Reserve a timer to be used with the specified timout value.  A zero will be
*  return if no timers are available.  The user should check to make sure the
*  return value is non-zero.
*
* Parameters:
*  uint32 timerValue:  Timer period in sysTicks.
*
* Return:
*  A non-zero value will be return if a timer has been assigned.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint32  SysTimers_1_GetTimer(uint32 timerValue )
{
    uint32 index;
	uint32 timerID = SysTimers_1_INVALID_TIMER;
	
	/* Search for a unused timer */	for(index=0; index < SysTimers_1_TIMERS; index++)
	{
		if(!(SysTimers_1_TimerStatus[index] & SysTimers_1_ACTIVE))
		{
		    #if(SysTimers_1_TIMER_MODE == SysTimers_1_MODE_FAST_IRQ)
			    SysTimers_1_TimerSCount[index]  = SysTimers_1_SysTickCount;
		    #else
			    SysTimers_1_TimerSCount[index] = timerValue;
			#endif
			SysTimers_1_TimerPeriod[index] = timerValue;
			SysTimers_1_TimerStatus[index] = SysTimers_1_IN_USE | SysTimers_1_ACTIVE;
			timerID = index + 1;
			break;
		}
	}
	return(timerID);
}
/*******************************************************************************
* Function Name: SysTimers_1_GetTimerStatus
********************************************************************************
*
* Summary:
*  Returns the status for the given timer.
*
* Parameters:
*  uint32 timerID:  The ID of the timer to be queried. 
*
* Return:
*  Status of timer, invalid, alarm triggered, or running.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint32  SysTimers_1_GetTimerStatus(uint32 timerID)
{
    uint32 status = 0;
	
	#if(SysTimers_1_TIMER_MODE == SysTimers_1_MODE_FAST_IRQ)
	    uint32 delta;
	    uint32 sysTickCnt;
	    timerID--;
	    timerID = timerID & SysTimers_1_TIMER_MASK;
	    sysTickCnt = SysTimers_1_SysTickCount;
	
		delta = sysTickCnt - SysTimers_1_TimerSCount[timerID];
		if(delta >= SysTimers_1_TimerPeriod[timerID] )
		{
		    status = 1;
			SysTimers_1_TimerSCount[timerID] +=  SysTimers_1_TimerPeriod[timerID];
		}
	#else
	    timerID--;
	    timerID = timerID & SysTimers_1_TIMER_MASK;
		status = SysTimers_1_TimerStatus[timerID] & SysTimers_1_ALARM_CNT_MASK;
	    if(status != 0)
		{
		    SysTimers_1_TimerStatus[timerID] &= SysTimers_1_ALARM_CLR_MASK;
		}
    #endif
	
    return(status);
}

/*******************************************************************************
* Function Name: SysTimers_1_GetTimerValue
********************************************************************************
*
* Summary:
*  Returns the time left on the timer.
*
* Parameters:
*  uint32 timerID:  The ID of the timer to be queried. 
*
* Return:
*  The number of sysClocks before tiemr expires.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint32  SysTimers_1_GetTimerValue(uint32 timerID)
{
    uint32 timerValue;
    timerID--;
	timerID = timerID & SysTimers_1_TIMER_MASK;
	
    #if(SysTimers_1_TIMER_MODE == SysTimers_1_MODE_FAST_IRQ)
	    timerValue = SysTimers_1_SysTickCount - SysTimers_1_TimerSCount[timerID];
	#else
        timerValue = SysTimers_1_TimerSCount[timerID];
	#endif
	return(timerValue);
}

/*******************************************************************************
* Function Name: SysTimers_1_GetSysTickValue
********************************************************************************
*
* Summary:
*  Returns the sysTick counter value.
*
* Parameters:
*  none 
*
* Return:
*  Value of sysTick since reset.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint32  SysTimers_1_GetSysTickValue(void)
{
    return(SysTimers_1_SysTickCount);
}

/*******************************************************************************
* Function Name: SysTimers_1_ResetTimer
********************************************************************************
*
* Summary:
*  Reset timer to new or old period.
*
* Parameters:
*  uint32 timerID:  The timers identification number.
*  uint32 timerValue:  New timer period, if zero reload with old value.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void  SysTimers_1_ResetTimer(uint32 timerID, uint32 timerValue)
{
    timerID--;
	timerID = timerID & SysTimers_1_TIMER_MASK;
	if(timerValue != 0)  /* If timerValue not zero, load new period */
	{
	    SysTimers_1_TimerPeriod[timerID] = timerValue;
	}
	#if(SysTimers_1_TIMER_MODE == SysTimers_1_MODE_FAST_IRQ)
        SysTimers_1_TimerSCount[timerID] = SysTimers_1_SysTickCount;
	#else
	    SysTimers_1_TimerSCount[timerID] = SysTimers_1_TimerPeriod[timerID];
	#endif
	
	SysTimers_1_TimerStatus[timerID] &= SysTimers_1_ALARM_CLR_MASK;
}
/*******************************************************************************
* Function Name: SysTimers_1_ReleaseTimer
********************************************************************************
*
* Summary:
*  Return timer to the queue, so that it may be used again.
*
* Parameters:
*  uint32 timerID:  ID of the timer to release.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void  SysTimers_1_ReleaseTimer(uint32 timerID)
{
	SysTimers_1_TimerStatus[timerID] = SysTimers_1_NOT_IN_USE;
	SysTimers_1_TimerSCount[timerID] = SysTimers_1_INVALID_PERIOD;
	SysTimers_1_TimerPeriod[timerID] = SysTimers_1_INVALID_PERIOD;
}
/*******************************************************************************
* Function Name: SysTimers_1_ReleaseAllTimers
********************************************************************************
*
* Summary:
*  Return all timers to the queue.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void  SysTimers_1_ReleaseAllTimers(void)
{
    uint32 index;
	
	for(index = 1; index <= SysTimers_1_TIMERS; index++)
	{
	    SysTimers_1_TimerSCount[index]--;
		if(SysTimers_1_TimerStatus[index] == 0)
		{
		    SysTimers_1_ReleaseTimer(index);
		}
	}
}

/* [] END OF FILE */