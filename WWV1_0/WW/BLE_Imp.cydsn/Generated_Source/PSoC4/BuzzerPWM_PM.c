/*******************************************************************************
* File Name: BuzzerPWM_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BuzzerPWM.h"

static BuzzerPWM_backupStruct BuzzerPWM_backup;


/*******************************************************************************
* Function Name: BuzzerPWM_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  BuzzerPWM_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void BuzzerPWM_SaveConfig(void) 
{

    #if(!BuzzerPWM_UsingFixedFunction)
        #if(!BuzzerPWM_PWMModeIsCenterAligned)
            BuzzerPWM_backup.PWMPeriod = BuzzerPWM_ReadPeriod();
        #endif /* (!BuzzerPWM_PWMModeIsCenterAligned) */
        BuzzerPWM_backup.PWMUdb = BuzzerPWM_ReadCounter();
        #if (BuzzerPWM_UseStatus)
            BuzzerPWM_backup.InterruptMaskValue = BuzzerPWM_STATUS_MASK;
        #endif /* (BuzzerPWM_UseStatus) */

        #if(BuzzerPWM_DeadBandMode == BuzzerPWM__B_PWM__DBM_256_CLOCKS || \
            BuzzerPWM_DeadBandMode == BuzzerPWM__B_PWM__DBM_2_4_CLOCKS)
            BuzzerPWM_backup.PWMdeadBandValue = BuzzerPWM_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(BuzzerPWM_KillModeMinTime)
             BuzzerPWM_backup.PWMKillCounterPeriod = BuzzerPWM_ReadKillTime();
        #endif /* (BuzzerPWM_KillModeMinTime) */

        #if(BuzzerPWM_UseControl)
            BuzzerPWM_backup.PWMControlRegister = BuzzerPWM_ReadControlRegister();
        #endif /* (BuzzerPWM_UseControl) */
    #endif  /* (!BuzzerPWM_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BuzzerPWM_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  BuzzerPWM_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void BuzzerPWM_RestoreConfig(void) 
{
        #if(!BuzzerPWM_UsingFixedFunction)
            #if(!BuzzerPWM_PWMModeIsCenterAligned)
                BuzzerPWM_WritePeriod(BuzzerPWM_backup.PWMPeriod);
            #endif /* (!BuzzerPWM_PWMModeIsCenterAligned) */

            BuzzerPWM_WriteCounter(BuzzerPWM_backup.PWMUdb);

            #if (BuzzerPWM_UseStatus)
                BuzzerPWM_STATUS_MASK = BuzzerPWM_backup.InterruptMaskValue;
            #endif /* (BuzzerPWM_UseStatus) */

            #if(BuzzerPWM_DeadBandMode == BuzzerPWM__B_PWM__DBM_256_CLOCKS || \
                BuzzerPWM_DeadBandMode == BuzzerPWM__B_PWM__DBM_2_4_CLOCKS)
                BuzzerPWM_WriteDeadTime(BuzzerPWM_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(BuzzerPWM_KillModeMinTime)
                BuzzerPWM_WriteKillTime(BuzzerPWM_backup.PWMKillCounterPeriod);
            #endif /* (BuzzerPWM_KillModeMinTime) */

            #if(BuzzerPWM_UseControl)
                BuzzerPWM_WriteControlRegister(BuzzerPWM_backup.PWMControlRegister);
            #endif /* (BuzzerPWM_UseControl) */
        #endif  /* (!BuzzerPWM_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: BuzzerPWM_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  BuzzerPWM_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void BuzzerPWM_Sleep(void) 
{
    #if(BuzzerPWM_UseControl)
        if(BuzzerPWM_CTRL_ENABLE == (BuzzerPWM_CONTROL & BuzzerPWM_CTRL_ENABLE))
        {
            /*Component is enabled */
            BuzzerPWM_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            BuzzerPWM_backup.PWMEnableState = 0u;
        }
    #endif /* (BuzzerPWM_UseControl) */

    /* Stop component */
    BuzzerPWM_Stop();

    /* Save registers configuration */
    BuzzerPWM_SaveConfig();
}


/*******************************************************************************
* Function Name: BuzzerPWM_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  BuzzerPWM_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BuzzerPWM_Wakeup(void) 
{
     /* Restore registers values */
    BuzzerPWM_RestoreConfig();

    if(BuzzerPWM_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        BuzzerPWM_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
