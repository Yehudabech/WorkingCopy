/*******************************************************************************
* File Name: BuzzerPWM.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_BuzzerPWM_H)
#define CY_PWM_BuzzerPWM_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 BuzzerPWM_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define BuzzerPWM_Resolution                     (8u)
#define BuzzerPWM_UsingFixedFunction             (0u)
#define BuzzerPWM_DeadBandMode                   (0u)
#define BuzzerPWM_KillModeMinTime                (0u)
#define BuzzerPWM_KillMode                       (0u)
#define BuzzerPWM_PWMMode                        (1u)
#define BuzzerPWM_PWMModeIsCenterAligned         (0u)
#define BuzzerPWM_DeadBandUsed                   (0u)
#define BuzzerPWM_DeadBand2_4                    (0u)

#if !defined(BuzzerPWM_PWMUDB_genblk8_stsreg__REMOVED)
    #define BuzzerPWM_UseStatus                  (1u)
#else
    #define BuzzerPWM_UseStatus                  (0u)
#endif /* !defined(BuzzerPWM_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(BuzzerPWM_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define BuzzerPWM_UseControl                 (1u)
#else
    #define BuzzerPWM_UseControl                 (0u)
#endif /* !defined(BuzzerPWM_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define BuzzerPWM_UseOneCompareMode              (0u)
#define BuzzerPWM_MinimumKillTime                (1u)
#define BuzzerPWM_EnableMode                     (0u)

#define BuzzerPWM_CompareMode1SW                 (0u)
#define BuzzerPWM_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define BuzzerPWM__B_PWM__DISABLED 0
#define BuzzerPWM__B_PWM__ASYNCHRONOUS 1
#define BuzzerPWM__B_PWM__SINGLECYCLE 2
#define BuzzerPWM__B_PWM__LATCHED 3
#define BuzzerPWM__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define BuzzerPWM__B_PWM__DBMDISABLED 0
#define BuzzerPWM__B_PWM__DBM_2_4_CLOCKS 1
#define BuzzerPWM__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define BuzzerPWM__B_PWM__ONE_OUTPUT 0
#define BuzzerPWM__B_PWM__TWO_OUTPUTS 1
#define BuzzerPWM__B_PWM__DUAL_EDGE 2
#define BuzzerPWM__B_PWM__CENTER_ALIGN 3
#define BuzzerPWM__B_PWM__DITHER 5
#define BuzzerPWM__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define BuzzerPWM__B_PWM__LESS_THAN 1
#define BuzzerPWM__B_PWM__LESS_THAN_OR_EQUAL 2
#define BuzzerPWM__B_PWM__GREATER_THAN 3
#define BuzzerPWM__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define BuzzerPWM__B_PWM__EQUAL 0
#define BuzzerPWM__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!BuzzerPWM_UsingFixedFunction)
        uint8 PWMUdb;               /* PWM Current Counter value  */
        #if(!BuzzerPWM_PWMModeIsCenterAligned)
            uint8 PWMPeriod;
        #endif /* (!BuzzerPWM_PWMModeIsCenterAligned) */
        #if (BuzzerPWM_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (BuzzerPWM_UseStatus) */

        /* Backup for Deadband parameters */
        #if(BuzzerPWM_DeadBandMode == BuzzerPWM__B_PWM__DBM_256_CLOCKS || \
            BuzzerPWM_DeadBandMode == BuzzerPWM__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(BuzzerPWM_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (BuzzerPWM_KillModeMinTime) */

        /* Backup control register */
        #if(BuzzerPWM_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (BuzzerPWM_UseControl) */

    #endif /* (!BuzzerPWM_UsingFixedFunction) */

}BuzzerPWM_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    BuzzerPWM_Start(void) ;
void    BuzzerPWM_Stop(void) ;

#if (BuzzerPWM_UseStatus || BuzzerPWM_UsingFixedFunction)
    void  BuzzerPWM_SetInterruptMode(uint8 interruptMode) ;
    uint8 BuzzerPWM_ReadStatusRegister(void) ;
#endif /* (BuzzerPWM_UseStatus || BuzzerPWM_UsingFixedFunction) */

#define BuzzerPWM_GetInterruptSource() BuzzerPWM_ReadStatusRegister()

#if (BuzzerPWM_UseControl)
    uint8 BuzzerPWM_ReadControlRegister(void) ;
    void  BuzzerPWM_WriteControlRegister(uint8 control)
          ;
#endif /* (BuzzerPWM_UseControl) */

#if (BuzzerPWM_UseOneCompareMode)
   #if (BuzzerPWM_CompareMode1SW)
       void    BuzzerPWM_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (BuzzerPWM_CompareMode1SW) */
#else
    #if (BuzzerPWM_CompareMode1SW)
        void    BuzzerPWM_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (BuzzerPWM_CompareMode1SW) */
    #if (BuzzerPWM_CompareMode2SW)
        void    BuzzerPWM_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (BuzzerPWM_CompareMode2SW) */
#endif /* (BuzzerPWM_UseOneCompareMode) */

#if (!BuzzerPWM_UsingFixedFunction)
    uint8   BuzzerPWM_ReadCounter(void) ;
    uint8 BuzzerPWM_ReadCapture(void) ;

    #if (BuzzerPWM_UseStatus)
            void BuzzerPWM_ClearFIFO(void) ;
    #endif /* (BuzzerPWM_UseStatus) */

    void    BuzzerPWM_WriteCounter(uint8 counter)
            ;
#endif /* (!BuzzerPWM_UsingFixedFunction) */

void    BuzzerPWM_WritePeriod(uint8 period)
        ;
uint8 BuzzerPWM_ReadPeriod(void) ;

#if (BuzzerPWM_UseOneCompareMode)
    void    BuzzerPWM_WriteCompare(uint8 compare)
            ;
    uint8 BuzzerPWM_ReadCompare(void) ;
#else
    void    BuzzerPWM_WriteCompare1(uint8 compare)
            ;
    uint8 BuzzerPWM_ReadCompare1(void) ;
    void    BuzzerPWM_WriteCompare2(uint8 compare)
            ;
    uint8 BuzzerPWM_ReadCompare2(void) ;
#endif /* (BuzzerPWM_UseOneCompareMode) */


#if (BuzzerPWM_DeadBandUsed)
    void    BuzzerPWM_WriteDeadTime(uint8 deadtime) ;
    uint8   BuzzerPWM_ReadDeadTime(void) ;
#endif /* (BuzzerPWM_DeadBandUsed) */

#if ( BuzzerPWM_KillModeMinTime)
    void BuzzerPWM_WriteKillTime(uint8 killtime) ;
    uint8 BuzzerPWM_ReadKillTime(void) ;
#endif /* ( BuzzerPWM_KillModeMinTime) */

void BuzzerPWM_Init(void) ;
void BuzzerPWM_Enable(void) ;
void BuzzerPWM_Sleep(void) ;
void BuzzerPWM_Wakeup(void) ;
void BuzzerPWM_SaveConfig(void) ;
void BuzzerPWM_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define BuzzerPWM_INIT_PERIOD_VALUE          (255u)
#define BuzzerPWM_INIT_COMPARE_VALUE1        (127u)
#define BuzzerPWM_INIT_COMPARE_VALUE2        (63u)
#define BuzzerPWM_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    BuzzerPWM_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    BuzzerPWM_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    BuzzerPWM_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    BuzzerPWM_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define BuzzerPWM_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  BuzzerPWM_CTRL_CMPMODE2_SHIFT)
#define BuzzerPWM_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  BuzzerPWM_CTRL_CMPMODE1_SHIFT)
#define BuzzerPWM_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (BuzzerPWM_UsingFixedFunction)
   #define BuzzerPWM_PERIOD_LSB              (*(reg16 *) BuzzerPWM_PWMHW__PER0)
   #define BuzzerPWM_PERIOD_LSB_PTR          ( (reg16 *) BuzzerPWM_PWMHW__PER0)
   #define BuzzerPWM_COMPARE1_LSB            (*(reg16 *) BuzzerPWM_PWMHW__CNT_CMP0)
   #define BuzzerPWM_COMPARE1_LSB_PTR        ( (reg16 *) BuzzerPWM_PWMHW__CNT_CMP0)
   #define BuzzerPWM_COMPARE2_LSB            (0x00u)
   #define BuzzerPWM_COMPARE2_LSB_PTR        (0x00u)
   #define BuzzerPWM_COUNTER_LSB             (*(reg16 *) BuzzerPWM_PWMHW__CNT_CMP0)
   #define BuzzerPWM_COUNTER_LSB_PTR         ( (reg16 *) BuzzerPWM_PWMHW__CNT_CMP0)
   #define BuzzerPWM_CAPTURE_LSB             (*(reg16 *) BuzzerPWM_PWMHW__CAP0)
   #define BuzzerPWM_CAPTURE_LSB_PTR         ( (reg16 *) BuzzerPWM_PWMHW__CAP0)
   #define BuzzerPWM_RT1                     (*(reg8 *)  BuzzerPWM_PWMHW__RT1)
   #define BuzzerPWM_RT1_PTR                 ( (reg8 *)  BuzzerPWM_PWMHW__RT1)

#else
   #if (BuzzerPWM_Resolution == 8u) /* 8bit - PWM */

       #if(BuzzerPWM_PWMModeIsCenterAligned)
           #define BuzzerPWM_PERIOD_LSB      (*(reg8 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
           #define BuzzerPWM_PERIOD_LSB_PTR  ((reg8 *)   BuzzerPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #else
           #define BuzzerPWM_PERIOD_LSB      (*(reg8 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
           #define BuzzerPWM_PERIOD_LSB_PTR  ((reg8 *)   BuzzerPWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
       #endif /* (BuzzerPWM_PWMModeIsCenterAligned) */

       #define BuzzerPWM_COMPARE1_LSB        (*(reg8 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define BuzzerPWM_COMPARE1_LSB_PTR    ((reg8 *)   BuzzerPWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
       #define BuzzerPWM_COMPARE2_LSB        (*(reg8 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define BuzzerPWM_COMPARE2_LSB_PTR    ((reg8 *)   BuzzerPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
       #define BuzzerPWM_COUNTERCAP_LSB      (*(reg8 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define BuzzerPWM_COUNTERCAP_LSB_PTR  ((reg8 *)   BuzzerPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
       #define BuzzerPWM_COUNTER_LSB         (*(reg8 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define BuzzerPWM_COUNTER_LSB_PTR     ((reg8 *)   BuzzerPWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
       #define BuzzerPWM_CAPTURE_LSB         (*(reg8 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__F1_REG)
       #define BuzzerPWM_CAPTURE_LSB_PTR     ((reg8 *)   BuzzerPWM_PWMUDB_sP8_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(BuzzerPWM_PWMModeIsCenterAligned)
               #define BuzzerPWM_PERIOD_LSB      (*(reg16 *) BuzzerPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
               #define BuzzerPWM_PERIOD_LSB_PTR  ((reg16 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #else
               #define BuzzerPWM_PERIOD_LSB      (*(reg16 *) BuzzerPWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
               #define BuzzerPWM_PERIOD_LSB_PTR  ((reg16 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__F0_REG)
            #endif /* (BuzzerPWM_PWMModeIsCenterAligned) */

            #define BuzzerPWM_COMPARE1_LSB       (*(reg16 *) BuzzerPWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define BuzzerPWM_COMPARE1_LSB_PTR   ((reg16 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__D0_REG)
            #define BuzzerPWM_COMPARE2_LSB       (*(reg16 *) BuzzerPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define BuzzerPWM_COMPARE2_LSB_PTR   ((reg16 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__D1_REG)
            #define BuzzerPWM_COUNTERCAP_LSB     (*(reg16 *) BuzzerPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define BuzzerPWM_COUNTERCAP_LSB_PTR ((reg16 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
            #define BuzzerPWM_COUNTER_LSB        (*(reg16 *) BuzzerPWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define BuzzerPWM_COUNTER_LSB_PTR    ((reg16 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__A0_REG)
            #define BuzzerPWM_CAPTURE_LSB        (*(reg16 *) BuzzerPWM_PWMUDB_sP8_pwmdp_u0__F1_REG)
            #define BuzzerPWM_CAPTURE_LSB_PTR    ((reg16 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__F1_REG)
        #else
            #if(BuzzerPWM_PWMModeIsCenterAligned)
               #define BuzzerPWM_PERIOD_LSB      (*(reg16 *) BuzzerPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
               #define BuzzerPWM_PERIOD_LSB_PTR  ((reg16 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #else
               #define BuzzerPWM_PERIOD_LSB      (*(reg16 *) BuzzerPWM_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
               #define BuzzerPWM_PERIOD_LSB_PTR  ((reg16 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__16BIT_F0_REG)
            #endif /* (BuzzerPWM_PWMModeIsCenterAligned) */

            #define BuzzerPWM_COMPARE1_LSB       (*(reg16 *) BuzzerPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define BuzzerPWM_COMPARE1_LSB_PTR   ((reg16 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D0_REG)
            #define BuzzerPWM_COMPARE2_LSB       (*(reg16 *) BuzzerPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define BuzzerPWM_COMPARE2_LSB_PTR   ((reg16 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__16BIT_D1_REG)
            #define BuzzerPWM_COUNTERCAP_LSB     (*(reg16 *) BuzzerPWM_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define BuzzerPWM_COUNTERCAP_LSB_PTR ((reg16 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__16BIT_A1_REG)
            #define BuzzerPWM_COUNTER_LSB        (*(reg16 *) BuzzerPWM_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define BuzzerPWM_COUNTER_LSB_PTR    ((reg16 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__16BIT_A0_REG)
            #define BuzzerPWM_CAPTURE_LSB        (*(reg16 *) BuzzerPWM_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
            #define BuzzerPWM_CAPTURE_LSB_PTR    ((reg16 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define BuzzerPWM_AUX_CONTROLDP1          (*(reg8 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)
       #define BuzzerPWM_AUX_CONTROLDP1_PTR      ((reg8 *)   BuzzerPWM_PWMUDB_sP8_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (BuzzerPWM_Resolution == 8) */

   #define BuzzerPWM_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__A1_REG)
   #define BuzzerPWM_AUX_CONTROLDP0          (*(reg8 *)  BuzzerPWM_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)
   #define BuzzerPWM_AUX_CONTROLDP0_PTR      ((reg8 *)   BuzzerPWM_PWMUDB_sP8_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (BuzzerPWM_UsingFixedFunction) */

#if(BuzzerPWM_KillModeMinTime )
    #define BuzzerPWM_KILLMODEMINTIME        (*(reg8 *)  BuzzerPWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define BuzzerPWM_KILLMODEMINTIME_PTR    ((reg8 *)   BuzzerPWM_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (BuzzerPWM_KillModeMinTime ) */

#if(BuzzerPWM_DeadBandMode == BuzzerPWM__B_PWM__DBM_256_CLOCKS)
    #define BuzzerPWM_DEADBAND_COUNT         (*(reg8 *)  BuzzerPWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define BuzzerPWM_DEADBAND_COUNT_PTR     ((reg8 *)   BuzzerPWM_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define BuzzerPWM_DEADBAND_LSB_PTR       ((reg8 *)   BuzzerPWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define BuzzerPWM_DEADBAND_LSB           (*(reg8 *)  BuzzerPWM_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(BuzzerPWM_DeadBandMode == BuzzerPWM__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (BuzzerPWM_UsingFixedFunction)
        #define BuzzerPWM_DEADBAND_COUNT         (*(reg8 *)  BuzzerPWM_PWMHW__CFG0)
        #define BuzzerPWM_DEADBAND_COUNT_PTR     ((reg8 *)   BuzzerPWM_PWMHW__CFG0)
        #define BuzzerPWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << BuzzerPWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define BuzzerPWM_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define BuzzerPWM_DEADBAND_COUNT         (*(reg8 *)  BuzzerPWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define BuzzerPWM_DEADBAND_COUNT_PTR     ((reg8 *)   BuzzerPWM_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define BuzzerPWM_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << BuzzerPWM_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define BuzzerPWM_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (BuzzerPWM_UsingFixedFunction) */
#endif /* (BuzzerPWM_DeadBandMode == BuzzerPWM__B_PWM__DBM_256_CLOCKS) */



#if (BuzzerPWM_UsingFixedFunction)
    #define BuzzerPWM_STATUS                 (*(reg8 *) BuzzerPWM_PWMHW__SR0)
    #define BuzzerPWM_STATUS_PTR             ((reg8 *) BuzzerPWM_PWMHW__SR0)
    #define BuzzerPWM_STATUS_MASK            (*(reg8 *) BuzzerPWM_PWMHW__SR0)
    #define BuzzerPWM_STATUS_MASK_PTR        ((reg8 *) BuzzerPWM_PWMHW__SR0)
    #define BuzzerPWM_CONTROL                (*(reg8 *) BuzzerPWM_PWMHW__CFG0)
    #define BuzzerPWM_CONTROL_PTR            ((reg8 *) BuzzerPWM_PWMHW__CFG0)
    #define BuzzerPWM_CONTROL2               (*(reg8 *) BuzzerPWM_PWMHW__CFG1)
    #define BuzzerPWM_CONTROL3               (*(reg8 *) BuzzerPWM_PWMHW__CFG2)
    #define BuzzerPWM_GLOBAL_ENABLE          (*(reg8 *) BuzzerPWM_PWMHW__PM_ACT_CFG)
    #define BuzzerPWM_GLOBAL_ENABLE_PTR      ( (reg8 *) BuzzerPWM_PWMHW__PM_ACT_CFG)
    #define BuzzerPWM_GLOBAL_STBY_ENABLE     (*(reg8 *) BuzzerPWM_PWMHW__PM_STBY_CFG)
    #define BuzzerPWM_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) BuzzerPWM_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define BuzzerPWM_BLOCK_EN_MASK          (BuzzerPWM_PWMHW__PM_ACT_MSK)
    #define BuzzerPWM_BLOCK_STBY_EN_MASK     (BuzzerPWM_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define BuzzerPWM_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define BuzzerPWM_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define BuzzerPWM_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define BuzzerPWM_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define BuzzerPWM_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define BuzzerPWM_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define BuzzerPWM_CTRL_ENABLE            (uint8)((uint8)0x01u << BuzzerPWM_CTRL_ENABLE_SHIFT)
    #define BuzzerPWM_CTRL_RESET             (uint8)((uint8)0x01u << BuzzerPWM_CTRL_RESET_SHIFT)
    #define BuzzerPWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << BuzzerPWM_CTRL_CMPMODE2_SHIFT)
    #define BuzzerPWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << BuzzerPWM_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define BuzzerPWM_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define BuzzerPWM_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << BuzzerPWM_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define BuzzerPWM_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define BuzzerPWM_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define BuzzerPWM_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define BuzzerPWM_STATUS_TC_INT_EN_MASK_SHIFT            (BuzzerPWM_STATUS_TC_SHIFT - 4u)
    #define BuzzerPWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define BuzzerPWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (BuzzerPWM_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define BuzzerPWM_STATUS_TC              (uint8)((uint8)0x01u << BuzzerPWM_STATUS_TC_SHIFT)
    #define BuzzerPWM_STATUS_CMP1            (uint8)((uint8)0x01u << BuzzerPWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define BuzzerPWM_STATUS_TC_INT_EN_MASK              (uint8)((uint8)BuzzerPWM_STATUS_TC >> 4u)
    #define BuzzerPWM_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)BuzzerPWM_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define BuzzerPWM_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define BuzzerPWM_RT1_MASK              (uint8)((uint8)0x03u << BuzzerPWM_RT1_SHIFT)
    #define BuzzerPWM_SYNC                  (uint8)((uint8)0x03u << BuzzerPWM_RT1_SHIFT)
    #define BuzzerPWM_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define BuzzerPWM_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << BuzzerPWM_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define BuzzerPWM_SYNCDSI_EN            (uint8)((uint8)0x0Fu << BuzzerPWM_SYNCDSI_SHIFT)


#else
    #define BuzzerPWM_STATUS                (*(reg8 *)   BuzzerPWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define BuzzerPWM_STATUS_PTR            ((reg8 *)    BuzzerPWM_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define BuzzerPWM_STATUS_MASK           (*(reg8 *)   BuzzerPWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define BuzzerPWM_STATUS_MASK_PTR       ((reg8 *)    BuzzerPWM_PWMUDB_genblk8_stsreg__MASK_REG)
    #define BuzzerPWM_STATUS_AUX_CTRL       (*(reg8 *)   BuzzerPWM_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define BuzzerPWM_CONTROL               (*(reg8 *)   BuzzerPWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define BuzzerPWM_CONTROL_PTR           ((reg8 *)    BuzzerPWM_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define BuzzerPWM_CTRL_ENABLE_SHIFT      (0x07u)
    #define BuzzerPWM_CTRL_RESET_SHIFT       (0x06u)
    #define BuzzerPWM_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define BuzzerPWM_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define BuzzerPWM_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define BuzzerPWM_CTRL_ENABLE            (uint8)((uint8)0x01u << BuzzerPWM_CTRL_ENABLE_SHIFT)
    #define BuzzerPWM_CTRL_RESET             (uint8)((uint8)0x01u << BuzzerPWM_CTRL_RESET_SHIFT)
    #define BuzzerPWM_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << BuzzerPWM_CTRL_CMPMODE2_SHIFT)
    #define BuzzerPWM_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << BuzzerPWM_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define BuzzerPWM_STATUS_KILL_SHIFT          (0x05u)
    #define BuzzerPWM_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define BuzzerPWM_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define BuzzerPWM_STATUS_TC_SHIFT            (0x02u)
    #define BuzzerPWM_STATUS_CMP2_SHIFT          (0x01u)
    #define BuzzerPWM_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define BuzzerPWM_STATUS_KILL_INT_EN_MASK_SHIFT          (BuzzerPWM_STATUS_KILL_SHIFT)
    #define BuzzerPWM_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (BuzzerPWM_STATUS_FIFONEMPTY_SHIFT)
    #define BuzzerPWM_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (BuzzerPWM_STATUS_FIFOFULL_SHIFT)
    #define BuzzerPWM_STATUS_TC_INT_EN_MASK_SHIFT            (BuzzerPWM_STATUS_TC_SHIFT)
    #define BuzzerPWM_STATUS_CMP2_INT_EN_MASK_SHIFT          (BuzzerPWM_STATUS_CMP2_SHIFT)
    #define BuzzerPWM_STATUS_CMP1_INT_EN_MASK_SHIFT          (BuzzerPWM_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define BuzzerPWM_STATUS_KILL            (uint8)((uint8)0x00u << BuzzerPWM_STATUS_KILL_SHIFT )
    #define BuzzerPWM_STATUS_FIFOFULL        (uint8)((uint8)0x01u << BuzzerPWM_STATUS_FIFOFULL_SHIFT)
    #define BuzzerPWM_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << BuzzerPWM_STATUS_FIFONEMPTY_SHIFT)
    #define BuzzerPWM_STATUS_TC              (uint8)((uint8)0x01u << BuzzerPWM_STATUS_TC_SHIFT)
    #define BuzzerPWM_STATUS_CMP2            (uint8)((uint8)0x01u << BuzzerPWM_STATUS_CMP2_SHIFT)
    #define BuzzerPWM_STATUS_CMP1            (uint8)((uint8)0x01u << BuzzerPWM_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define BuzzerPWM_STATUS_KILL_INT_EN_MASK            (BuzzerPWM_STATUS_KILL)
    #define BuzzerPWM_STATUS_FIFOFULL_INT_EN_MASK        (BuzzerPWM_STATUS_FIFOFULL)
    #define BuzzerPWM_STATUS_FIFONEMPTY_INT_EN_MASK      (BuzzerPWM_STATUS_FIFONEMPTY)
    #define BuzzerPWM_STATUS_TC_INT_EN_MASK              (BuzzerPWM_STATUS_TC)
    #define BuzzerPWM_STATUS_CMP2_INT_EN_MASK            (BuzzerPWM_STATUS_CMP2)
    #define BuzzerPWM_STATUS_CMP1_INT_EN_MASK            (BuzzerPWM_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define BuzzerPWM_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define BuzzerPWM_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define BuzzerPWM_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define BuzzerPWM_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define BuzzerPWM_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* BuzzerPWM_UsingFixedFunction */

#endif  /* CY_PWM_BuzzerPWM_H */


/* [] END OF FILE */
