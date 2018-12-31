/*******************************************************************************
* File Name: UpBeforeIn.c  
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
#include "UpBeforeIn.h"

static UpBeforeIn_BACKUP_STRUCT  UpBeforeIn_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: UpBeforeIn_Sleep
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
*  \snippet UpBeforeIn_SUT.c usage_UpBeforeIn_Sleep_Wakeup
*******************************************************************************/
void UpBeforeIn_Sleep(void)
{
    #if defined(UpBeforeIn__PC)
        UpBeforeIn_backup.pcState = UpBeforeIn_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            UpBeforeIn_backup.usbState = UpBeforeIn_CR1_REG;
            UpBeforeIn_USB_POWER_REG |= UpBeforeIn_USBIO_ENTER_SLEEP;
            UpBeforeIn_CR1_REG &= UpBeforeIn_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(UpBeforeIn__SIO)
        UpBeforeIn_backup.sioState = UpBeforeIn_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        UpBeforeIn_SIO_REG &= (uint32)(~UpBeforeIn_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: UpBeforeIn_Wakeup
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
*  Refer to UpBeforeIn_Sleep() for an example usage.
*******************************************************************************/
void UpBeforeIn_Wakeup(void)
{
    #if defined(UpBeforeIn__PC)
        UpBeforeIn_PC = UpBeforeIn_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            UpBeforeIn_USB_POWER_REG &= UpBeforeIn_USBIO_EXIT_SLEEP_PH1;
            UpBeforeIn_CR1_REG = UpBeforeIn_backup.usbState;
            UpBeforeIn_USB_POWER_REG &= UpBeforeIn_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(UpBeforeIn__SIO)
        UpBeforeIn_SIO_REG = UpBeforeIn_backup.sioState;
    #endif
}


/* [] END OF FILE */
