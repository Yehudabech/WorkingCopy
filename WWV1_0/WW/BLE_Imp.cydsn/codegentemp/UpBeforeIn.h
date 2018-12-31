/*******************************************************************************
* File Name: UpBeforeIn.h  
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

#if !defined(CY_PINS_UpBeforeIn_H) /* Pins UpBeforeIn_H */
#define CY_PINS_UpBeforeIn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "UpBeforeIn_aliases.h"


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
} UpBeforeIn_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   UpBeforeIn_Read(void);
void    UpBeforeIn_Write(uint8 value);
uint8   UpBeforeIn_ReadDataReg(void);
#if defined(UpBeforeIn__PC) || (CY_PSOC4_4200L) 
    void    UpBeforeIn_SetDriveMode(uint8 mode);
#endif
void    UpBeforeIn_SetInterruptMode(uint16 position, uint16 mode);
uint8   UpBeforeIn_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void UpBeforeIn_Sleep(void); 
void UpBeforeIn_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(UpBeforeIn__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define UpBeforeIn_DRIVE_MODE_BITS        (3)
    #define UpBeforeIn_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - UpBeforeIn_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the UpBeforeIn_SetDriveMode() function.
         *  @{
         */
        #define UpBeforeIn_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define UpBeforeIn_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define UpBeforeIn_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define UpBeforeIn_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define UpBeforeIn_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define UpBeforeIn_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define UpBeforeIn_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define UpBeforeIn_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define UpBeforeIn_MASK               UpBeforeIn__MASK
#define UpBeforeIn_SHIFT              UpBeforeIn__SHIFT
#define UpBeforeIn_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in UpBeforeIn_SetInterruptMode() function.
     *  @{
     */
        #define UpBeforeIn_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define UpBeforeIn_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define UpBeforeIn_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define UpBeforeIn_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(UpBeforeIn__SIO)
    #define UpBeforeIn_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(UpBeforeIn__PC) && (CY_PSOC4_4200L)
    #define UpBeforeIn_USBIO_ENABLE               ((uint32)0x80000000u)
    #define UpBeforeIn_USBIO_DISABLE              ((uint32)(~UpBeforeIn_USBIO_ENABLE))
    #define UpBeforeIn_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define UpBeforeIn_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define UpBeforeIn_USBIO_ENTER_SLEEP          ((uint32)((1u << UpBeforeIn_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << UpBeforeIn_USBIO_SUSPEND_DEL_SHIFT)))
    #define UpBeforeIn_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << UpBeforeIn_USBIO_SUSPEND_SHIFT)))
    #define UpBeforeIn_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << UpBeforeIn_USBIO_SUSPEND_DEL_SHIFT)))
    #define UpBeforeIn_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(UpBeforeIn__PC)
    /* Port Configuration */
    #define UpBeforeIn_PC                 (* (reg32 *) UpBeforeIn__PC)
#endif
/* Pin State */
#define UpBeforeIn_PS                     (* (reg32 *) UpBeforeIn__PS)
/* Data Register */
#define UpBeforeIn_DR                     (* (reg32 *) UpBeforeIn__DR)
/* Input Buffer Disable Override */
#define UpBeforeIn_INP_DIS                (* (reg32 *) UpBeforeIn__PC2)

/* Interrupt configuration Registers */
#define UpBeforeIn_INTCFG                 (* (reg32 *) UpBeforeIn__INTCFG)
#define UpBeforeIn_INTSTAT                (* (reg32 *) UpBeforeIn__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define UpBeforeIn_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(UpBeforeIn__SIO)
    #define UpBeforeIn_SIO_REG            (* (reg32 *) UpBeforeIn__SIO)
#endif /* (UpBeforeIn__SIO_CFG) */

/* USBIO registers */
#if !defined(UpBeforeIn__PC) && (CY_PSOC4_4200L)
    #define UpBeforeIn_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define UpBeforeIn_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define UpBeforeIn_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define UpBeforeIn_DRIVE_MODE_SHIFT       (0x00u)
#define UpBeforeIn_DRIVE_MODE_MASK        (0x07u << UpBeforeIn_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins UpBeforeIn_H */


/* [] END OF FILE */
