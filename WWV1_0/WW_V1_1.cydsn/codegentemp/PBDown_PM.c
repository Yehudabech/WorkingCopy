/*******************************************************************************
* File Name: PBDown.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "PBDown.h"

static PBDown_BACKUP_STRUCT  PBDown_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: PBDown_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet PBDown_SUT.c usage_PBDown_Sleep_Wakeup
*******************************************************************************/
void PBDown_Sleep(void)
{
    #if defined(PBDown__PC)
        PBDown_backup.pcState = PBDown_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            PBDown_backup.usbState = PBDown_CR1_REG;
            PBDown_USB_POWER_REG |= PBDown_USBIO_ENTER_SLEEP;
            PBDown_CR1_REG &= PBDown_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PBDown__SIO)
        PBDown_backup.sioState = PBDown_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        PBDown_SIO_REG &= (uint32)(~PBDown_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: PBDown_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to PBDown_Sleep() for an example usage.
*******************************************************************************/
void PBDown_Wakeup(void)
{
    #if defined(PBDown__PC)
        PBDown_PC = PBDown_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            PBDown_USB_POWER_REG &= PBDown_USBIO_EXIT_SLEEP_PH1;
            PBDown_CR1_REG = PBDown_backup.usbState;
            PBDown_USB_POWER_REG &= PBDown_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PBDown__SIO)
        PBDown_SIO_REG = PBDown_backup.sioState;
    #endif
}


/* [] END OF FILE */
