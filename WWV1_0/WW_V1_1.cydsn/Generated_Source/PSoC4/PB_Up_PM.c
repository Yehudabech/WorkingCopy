/*******************************************************************************
* File Name: PB_Up.c  
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
#include "PB_Up.h"

static PB_Up_BACKUP_STRUCT  PB_Up_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: PB_Up_Sleep
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
*  \snippet PB_Up_SUT.c usage_PB_Up_Sleep_Wakeup
*******************************************************************************/
void PB_Up_Sleep(void)
{
    #if defined(PB_Up__PC)
        PB_Up_backup.pcState = PB_Up_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            PB_Up_backup.usbState = PB_Up_CR1_REG;
            PB_Up_USB_POWER_REG |= PB_Up_USBIO_ENTER_SLEEP;
            PB_Up_CR1_REG &= PB_Up_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PB_Up__SIO)
        PB_Up_backup.sioState = PB_Up_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        PB_Up_SIO_REG &= (uint32)(~PB_Up_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: PB_Up_Wakeup
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
*  Refer to PB_Up_Sleep() for an example usage.
*******************************************************************************/
void PB_Up_Wakeup(void)
{
    #if defined(PB_Up__PC)
        PB_Up_PC = PB_Up_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            PB_Up_USB_POWER_REG &= PB_Up_USBIO_EXIT_SLEEP_PH1;
            PB_Up_CR1_REG = PB_Up_backup.usbState;
            PB_Up_USB_POWER_REG &= PB_Up_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PB_Up__SIO)
        PB_Up_SIO_REG = PB_Up_backup.sioState;
    #endif
}


/* [] END OF FILE */
