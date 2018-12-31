/*******************************************************************************
* File Name: WinchUpPin.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_WinchUpPin_H) /* Pins WinchUpPin_H */
#define CY_PINS_WinchUpPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "WinchUpPin_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} WinchUpPin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   WinchUpPin_Read(void);
void    WinchUpPin_Write(uint8 value);
uint8   WinchUpPin_ReadDataReg(void);
#if defined(WinchUpPin__PC) || (CY_PSOC4_4200L) 
    void    WinchUpPin_SetDriveMode(uint8 mode);
#endif
void    WinchUpPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   WinchUpPin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void WinchUpPin_Sleep(void); 
void WinchUpPin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(WinchUpPin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define WinchUpPin_DRIVE_MODE_BITS        (3)
    #define WinchUpPin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - WinchUpPin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the WinchUpPin_SetDriveMode() function.
         *  @{
         */
        #define WinchUpPin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define WinchUpPin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define WinchUpPin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define WinchUpPin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define WinchUpPin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define WinchUpPin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define WinchUpPin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define WinchUpPin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define WinchUpPin_MASK               WinchUpPin__MASK
#define WinchUpPin_SHIFT              WinchUpPin__SHIFT
#define WinchUpPin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in WinchUpPin_SetInterruptMode() function.
     *  @{
     */
        #define WinchUpPin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define WinchUpPin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define WinchUpPin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define WinchUpPin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(WinchUpPin__SIO)
    #define WinchUpPin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(WinchUpPin__PC) && (CY_PSOC4_4200L)
    #define WinchUpPin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define WinchUpPin_USBIO_DISABLE              ((uint32)(~WinchUpPin_USBIO_ENABLE))
    #define WinchUpPin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define WinchUpPin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define WinchUpPin_USBIO_ENTER_SLEEP          ((uint32)((1u << WinchUpPin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << WinchUpPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define WinchUpPin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << WinchUpPin_USBIO_SUSPEND_SHIFT)))
    #define WinchUpPin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << WinchUpPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define WinchUpPin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(WinchUpPin__PC)
    /* Port Configuration */
    #define WinchUpPin_PC                 (* (reg32 *) WinchUpPin__PC)
#endif
/* Pin State */
#define WinchUpPin_PS                     (* (reg32 *) WinchUpPin__PS)
/* Data Register */
#define WinchUpPin_DR                     (* (reg32 *) WinchUpPin__DR)
/* Input Buffer Disable Override */
#define WinchUpPin_INP_DIS                (* (reg32 *) WinchUpPin__PC2)

/* Interrupt configuration Registers */
#define WinchUpPin_INTCFG                 (* (reg32 *) WinchUpPin__INTCFG)
#define WinchUpPin_INTSTAT                (* (reg32 *) WinchUpPin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define WinchUpPin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(WinchUpPin__SIO)
    #define WinchUpPin_SIO_REG            (* (reg32 *) WinchUpPin__SIO)
#endif /* (WinchUpPin__SIO_CFG) */

/* USBIO registers */
#if !defined(WinchUpPin__PC) && (CY_PSOC4_4200L)
    #define WinchUpPin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define WinchUpPin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define WinchUpPin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define WinchUpPin_DRIVE_MODE_SHIFT       (0x00u)
#define WinchUpPin_DRIVE_MODE_MASK        (0x07u << WinchUpPin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins WinchUpPin_H */


/* [] END OF FILE */
