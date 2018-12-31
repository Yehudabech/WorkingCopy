/*******************************************************************************
* File Name: WinchOutPin.c  
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
#include "WinchOutPin.h"

static WinchOutPin_BACKUP_STRUCT  WinchOutPin_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: WinchOutPin_Sleep
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
*  \snippet WinchOutPin_SUT.c usage_WinchOutPin_Sleep_Wakeup
*******************************************************************************/
void WinchOutPin_Sleep(void)
{
    #if defined(WinchOutPin__PC)
        WinchOutPin_backup.pcState = WinchOutPin_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            WinchOutPin_backup.usbState = WinchOutPin_CR1_REG;
            WinchOutPin_USB_POWER_REG |= WinchOutPin_USBIO_ENTER_SLEEP;
            WinchOutPin_CR1_REG &= WinchOutPin_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(WinchOutPin__SIO)
        WinchOutPin_backup.sioState = WinchOutPin_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        WinchOutPin_SIO_REG &= (uint32)(~WinchOutPin_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: WinchOutPin_Wakeup
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
*  Refer to WinchOutPin_Sleep() for an example usage.
*******************************************************************************/
void WinchOutPin_Wakeup(void)
{
    #if defined(WinchOutPin__PC)
        WinchOutPin_PC = WinchOutPin_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            WinchOutPin_USB_POWER_REG &= WinchOutPin_USBIO_EXIT_SLEEP_PH1;
            WinchOutPin_CR1_REG = WinchOutPin_backup.usbState;
            WinchOutPin_USB_POWER_REG &= WinchOutPin_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(WinchOutPin__SIO)
        WinchOutPin_SIO_REG = WinchOutPin_backup.sioState;
    #endif
}


/* [] END OF FILE */
