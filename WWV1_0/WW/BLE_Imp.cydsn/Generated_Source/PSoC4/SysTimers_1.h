/*******************************************************************************
* File Name: SysTimers_1.h
* Version 1.0
*
* Description:
*  This header file contains registers and constants associated with the
*  System Timer Component
*
*  6-26-2013  MEH  Initial Creation

* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SYSTIMERS_SysTimers_1_H)
#define CY_SYSTIMERS_SysTimers_1_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define SysTimers_1_TIMERS           2
#define SysTimers_1_TIMER_MASK       (2-1)
#define SysTimers_1_RESOLUTION       1000
#define SysTimers_1_TIMER_MODE       0
#define SysTimers_1_TICKS_PER_SECOND 1000
#define SysTimers_1_SYSTICK_IRQN     (uint8)(SysTick_IRQn + 16)  /* Offset between user and system vectors */


#define SysTimers_1_MODE_FAST_IRQ  1u
#define SysTimers_1_MODE_NORMAL    0u
#define SysTimers_1_ALARM_CNT_MASK 0x0000FFFF
#define SysTimers_1_ALARM_CLR_MASK 0x80000000
#define SysTimers_1_ALARM          0x10000000
#define SysTimers_1_IN_USE         0x80000000
#define SysTimers_1_ACTIVE         0x40000000
#define SysTimers_1_NOT_IN_USE     0x00000000
#define SysTimers_1_RELOAD         0x00000000
#define SysTimers_1_INVALID_TIMER  0x00000000
#define SysTimers_1_INVALID_PERIOD 0xFFF00000
#define SysTimers_1_SYS_CLOCK      0



void    SysTimers_1_Start(void);
void    SysTimers_1_Stop(void);
uint32  SysTimers_1_GetTimer(uint32 timerValue);
uint32  SysTimers_1_GetTimerStatus(uint32 timerID);
uint32  SysTimers_1_GetTimerValue(uint32 timerID);
uint32  SysTimers_1_GetSysTickValue(void);
void    SysTimers_1_ResetTimer(uint32 timerID, uint32 timerValue);
void    SysTimers_1_ReleaseTimer(uint32 timerID);
void    SysTimers_1_ReleaseAllTimers(void);

CY_ISR_PROTO(SysTimers_1_SysTickISR);

#if (CY_PSOC3 || CY_PSOC5LP)
    #define  SysTimers_1_SYSTICK_PERIOD     ((BCLK__BUS_CLK__HZ)/1000)
#elif (CY_PSOC4)
    #define  SysTimers_1_SYSTICK_PERIOD     ((CYDEV_BCLK__HFCLK__HZ)/1000)
#endif /* CY_PSOC5A */

#endif

//[] END OF FILE
