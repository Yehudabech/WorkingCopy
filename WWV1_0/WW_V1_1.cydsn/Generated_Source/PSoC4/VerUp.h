/*******************************************************************************
* File Name: VerUp.h  
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

#if !defined(CY_PINS_VerUp_H) /* Pins VerUp_H */
#define CY_PINS_VerUp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "VerUp_aliases.h"


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
} VerUp_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   VerUp_Read(void);
void    VerUp_Write(uint8 value);
uint8   VerUp_ReadDataReg(void);
#if defined(VerUp__PC) || (CY_PSOC4_4200L) 
    void    VerUp_SetDriveMode(uint8 mode);
#endif
void    VerUp_SetInterruptMode(uint16 position, uint16 mode);
uint8   VerUp_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void VerUp_Sleep(void); 
void VerUp_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(VerUp__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define VerUp_DRIVE_MODE_BITS        (3)
    #define VerUp_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - VerUp_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the VerUp_SetDriveMode() function.
         *  @{
         */
        #define VerUp_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define VerUp_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define VerUp_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define VerUp_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define VerUp_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define VerUp_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define VerUp_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define VerUp_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define VerUp_MASK               VerUp__MASK
#define VerUp_SHIFT              VerUp__SHIFT
#define VerUp_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VerUp_SetInterruptMode() function.
     *  @{
     */
        #define VerUp_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define VerUp_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define VerUp_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define VerUp_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(VerUp__SIO)
    #define VerUp_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(VerUp__PC) && (CY_PSOC4_4200L)
    #define VerUp_USBIO_ENABLE               ((uint32)0x80000000u)
    #define VerUp_USBIO_DISABLE              ((uint32)(~VerUp_USBIO_ENABLE))
    #define VerUp_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define VerUp_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define VerUp_USBIO_ENTER_SLEEP          ((uint32)((1u << VerUp_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << VerUp_USBIO_SUSPEND_DEL_SHIFT)))
    #define VerUp_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << VerUp_USBIO_SUSPEND_SHIFT)))
    #define VerUp_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << VerUp_USBIO_SUSPEND_DEL_SHIFT)))
    #define VerUp_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(VerUp__PC)
    /* Port Configuration */
    #define VerUp_PC                 (* (reg32 *) VerUp__PC)
#endif
/* Pin State */
#define VerUp_PS                     (* (reg32 *) VerUp__PS)
/* Data Register */
#define VerUp_DR                     (* (reg32 *) VerUp__DR)
/* Input Buffer Disable Override */
#define VerUp_INP_DIS                (* (reg32 *) VerUp__PC2)

/* Interrupt configuration Registers */
#define VerUp_INTCFG                 (* (reg32 *) VerUp__INTCFG)
#define VerUp_INTSTAT                (* (reg32 *) VerUp__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define VerUp_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(VerUp__SIO)
    #define VerUp_SIO_REG            (* (reg32 *) VerUp__SIO)
#endif /* (VerUp__SIO_CFG) */

/* USBIO registers */
#if !defined(VerUp__PC) && (CY_PSOC4_4200L)
    #define VerUp_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define VerUp_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define VerUp_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define VerUp_DRIVE_MODE_SHIFT       (0x00u)
#define VerUp_DRIVE_MODE_MASK        (0x07u << VerUp_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins VerUp_H */


/* [] END OF FILE */
