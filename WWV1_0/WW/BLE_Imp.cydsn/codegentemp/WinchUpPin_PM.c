/*******************************************************************************
* File Name: WinchUpPin.c  
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
#include "WinchUpPin.h"

static WinchUpPin_BACKUP_STRUCT  WinchUpPin_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: WinchUpPin_Sleep
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
*  \snippet WinchUpPin_SUT.c usage_WinchUpPin_Sleep_Wakeup
*******************************************************************************/
void WinchUpPin_Sleep(void)
{
    #if defined(WinchUpPin__PC)
        WinchUpPin_backup.pcState = WinchUpPin_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            WinchUpPin_backup.usbState = WinchUpPin_CR1_REG;
            WinchUpPin_USB_POWER_REG |= WinchUpPin_USBIO_ENTER_SLEEP;
            WinchUpPin_CR1_REG &= WinchUpPin_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(WinchUpPin__SIO)
        WinchUpPin_backup.sioState = WinchUpPin_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        WinchUpPin_SIO_REG &= (uint32)(~WinchUpPin_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: WinchUpPin_Wakeup
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
*  Refer to WinchUpPin_Sleep() for an example usage.
*******************************************************************************/
void WinchUpPin_Wakeup(void)
{
    #if defined(WinchUpPin__PC)
        WinchUpPin_PC = WinchUpPin_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            WinchUpPin_USB_POWER_REG &= WinchUpPin_USBIO_EXIT_SLEEP_PH1;
            WinchUpPin_CR1_REG = WinchUpPin_backup.usbState;
            WinchUpPin_USB_POWER_REG &= WinchUpPin_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(WinchUpPin__SIO)
        WinchUpPin_SIO_REG = WinchUpPin_backup.sioState;
    #endif
}


/* [] END OF FILE */
