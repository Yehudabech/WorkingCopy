/*******************************************************************************
* File Name: VerDown.h  
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

#if !defined(CY_PINS_VerDown_H) /* Pins VerDown_H */
#define CY_PINS_VerDown_H

#include "cytypes.h"
#include "cyfitter.h"
#include "VerDown_aliases.h"


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
} VerDown_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   VerDown_Read(void);
void    VerDown_Write(uint8 value);
uint8   VerDown_ReadDataReg(void);
#if defined(VerDown__PC) || (CY_PSOC4_4200L) 
    void    VerDown_SetDriveMode(uint8 mode);
#endif
void    VerDown_SetInterruptMode(uint16 position, uint16 mode);
uint8   VerDown_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void VerDown_Sleep(void); 
void VerDown_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(VerDown__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define VerDown_DRIVE_MODE_BITS        (3)
    #define VerDown_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - VerDown_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the VerDown_SetDriveMode() function.
         *  @{
         */
        #define VerDown_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define VerDown_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define VerDown_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define VerDown_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define VerDown_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define VerDown_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define VerDown_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define VerDown_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define VerDown_MASK               VerDown__MASK
#define VerDown_SHIFT              VerDown__SHIFT
#define VerDown_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VerDown_SetInterruptMode() function.
     *  @{
     */
        #define VerDown_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define VerDown_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define VerDown_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define VerDown_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(VerDown__SIO)
    #define VerDown_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(VerDown__PC) && (CY_PSOC4_4200L)
    #define VerDown_USBIO_ENABLE               ((uint32)0x80000000u)
    #define VerDown_USBIO_DISABLE              ((uint32)(~VerDown_USBIO_ENABLE))
    #define VerDown_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define VerDown_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define VerDown_USBIO_ENTER_SLEEP          ((uint32)((1u << VerDown_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << VerDown_USBIO_SUSPEND_DEL_SHIFT)))
    #define VerDown_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << VerDown_USBIO_SUSPEND_SHIFT)))
    #define VerDown_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << VerDown_USBIO_SUSPEND_DEL_SHIFT)))
    #define VerDown_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(VerDown__PC)
    /* Port Configuration */
    #define VerDown_PC                 (* (reg32 *) VerDown__PC)
#endif
/* Pin State */
#define VerDown_PS                     (* (reg32 *) VerDown__PS)
/* Data Register */
#define VerDown_DR                     (* (reg32 *) VerDown__DR)
/* Input Buffer Disable Override */
#define VerDown_INP_DIS                (* (reg32 *) VerDown__PC2)

/* Interrupt configuration Registers */
#define VerDown_INTCFG                 (* (reg32 *) VerDown__INTCFG)
#define VerDown_INTSTAT                (* (reg32 *) VerDown__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define VerDown_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(VerDown__SIO)
    #define VerDown_SIO_REG            (* (reg32 *) VerDown__SIO)
#endif /* (VerDown__SIO_CFG) */

/* USBIO registers */
#if !defined(VerDown__PC) && (CY_PSOC4_4200L)
    #define VerDown_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define VerDown_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define VerDown_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define VerDown_DRIVE_MODE_SHIFT       (0x00u)
#define VerDown_DRIVE_MODE_MASK        (0x07u << VerDown_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins VerDown_H */


/* [] END OF FILE */
