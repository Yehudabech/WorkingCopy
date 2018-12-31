/*******************************************************************************
* File Name: WinchDownPin.h  
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

#if !defined(CY_PINS_WinchDownPin_H) /* Pins WinchDownPin_H */
#define CY_PINS_WinchDownPin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "WinchDownPin_aliases.h"


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
} WinchDownPin_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   WinchDownPin_Read(void);
void    WinchDownPin_Write(uint8 value);
uint8   WinchDownPin_ReadDataReg(void);
#if defined(WinchDownPin__PC) || (CY_PSOC4_4200L) 
    void    WinchDownPin_SetDriveMode(uint8 mode);
#endif
void    WinchDownPin_SetInterruptMode(uint16 position, uint16 mode);
uint8   WinchDownPin_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void WinchDownPin_Sleep(void); 
void WinchDownPin_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(WinchDownPin__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define WinchDownPin_DRIVE_MODE_BITS        (3)
    #define WinchDownPin_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - WinchDownPin_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the WinchDownPin_SetDriveMode() function.
         *  @{
         */
        #define WinchDownPin_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define WinchDownPin_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define WinchDownPin_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define WinchDownPin_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define WinchDownPin_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define WinchDownPin_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define WinchDownPin_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define WinchDownPin_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define WinchDownPin_MASK               WinchDownPin__MASK
#define WinchDownPin_SHIFT              WinchDownPin__SHIFT
#define WinchDownPin_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in WinchDownPin_SetInterruptMode() function.
     *  @{
     */
        #define WinchDownPin_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define WinchDownPin_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define WinchDownPin_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define WinchDownPin_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(WinchDownPin__SIO)
    #define WinchDownPin_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(WinchDownPin__PC) && (CY_PSOC4_4200L)
    #define WinchDownPin_USBIO_ENABLE               ((uint32)0x80000000u)
    #define WinchDownPin_USBIO_DISABLE              ((uint32)(~WinchDownPin_USBIO_ENABLE))
    #define WinchDownPin_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define WinchDownPin_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define WinchDownPin_USBIO_ENTER_SLEEP          ((uint32)((1u << WinchDownPin_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << WinchDownPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define WinchDownPin_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << WinchDownPin_USBIO_SUSPEND_SHIFT)))
    #define WinchDownPin_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << WinchDownPin_USBIO_SUSPEND_DEL_SHIFT)))
    #define WinchDownPin_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(WinchDownPin__PC)
    /* Port Configuration */
    #define WinchDownPin_PC                 (* (reg32 *) WinchDownPin__PC)
#endif
/* Pin State */
#define WinchDownPin_PS                     (* (reg32 *) WinchDownPin__PS)
/* Data Register */
#define WinchDownPin_DR                     (* (reg32 *) WinchDownPin__DR)
/* Input Buffer Disable Override */
#define WinchDownPin_INP_DIS                (* (reg32 *) WinchDownPin__PC2)

/* Interrupt configuration Registers */
#define WinchDownPin_INTCFG                 (* (reg32 *) WinchDownPin__INTCFG)
#define WinchDownPin_INTSTAT                (* (reg32 *) WinchDownPin__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define WinchDownPin_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(WinchDownPin__SIO)
    #define WinchDownPin_SIO_REG            (* (reg32 *) WinchDownPin__SIO)
#endif /* (WinchDownPin__SIO_CFG) */

/* USBIO registers */
#if !defined(WinchDownPin__PC) && (CY_PSOC4_4200L)
    #define WinchDownPin_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define WinchDownPin_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define WinchDownPin_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define WinchDownPin_DRIVE_MODE_SHIFT       (0x00u)
#define WinchDownPin_DRIVE_MODE_MASK        (0x07u << WinchDownPin_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins WinchDownPin_H */


/* [] END OF FILE */
