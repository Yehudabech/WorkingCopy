/*******************************************************************************
* File Name: PBDown.h  
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

#if !defined(CY_PINS_PBDown_H) /* Pins PBDown_H */
#define CY_PINS_PBDown_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PBDown_aliases.h"


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
} PBDown_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PBDown_Read(void);
void    PBDown_Write(uint8 value);
uint8   PBDown_ReadDataReg(void);
#if defined(PBDown__PC) || (CY_PSOC4_4200L) 
    void    PBDown_SetDriveMode(uint8 mode);
#endif
void    PBDown_SetInterruptMode(uint16 position, uint16 mode);
uint8   PBDown_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PBDown_Sleep(void); 
void PBDown_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PBDown__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PBDown_DRIVE_MODE_BITS        (3)
    #define PBDown_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PBDown_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PBDown_SetDriveMode() function.
         *  @{
         */
        #define PBDown_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PBDown_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PBDown_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PBDown_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PBDown_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PBDown_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PBDown_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PBDown_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PBDown_MASK               PBDown__MASK
#define PBDown_SHIFT              PBDown__SHIFT
#define PBDown_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PBDown_SetInterruptMode() function.
     *  @{
     */
        #define PBDown_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PBDown_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PBDown_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PBDown_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PBDown__SIO)
    #define PBDown_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PBDown__PC) && (CY_PSOC4_4200L)
    #define PBDown_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PBDown_USBIO_DISABLE              ((uint32)(~PBDown_USBIO_ENABLE))
    #define PBDown_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PBDown_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PBDown_USBIO_ENTER_SLEEP          ((uint32)((1u << PBDown_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PBDown_USBIO_SUSPEND_DEL_SHIFT)))
    #define PBDown_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PBDown_USBIO_SUSPEND_SHIFT)))
    #define PBDown_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PBDown_USBIO_SUSPEND_DEL_SHIFT)))
    #define PBDown_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PBDown__PC)
    /* Port Configuration */
    #define PBDown_PC                 (* (reg32 *) PBDown__PC)
#endif
/* Pin State */
#define PBDown_PS                     (* (reg32 *) PBDown__PS)
/* Data Register */
#define PBDown_DR                     (* (reg32 *) PBDown__DR)
/* Input Buffer Disable Override */
#define PBDown_INP_DIS                (* (reg32 *) PBDown__PC2)

/* Interrupt configuration Registers */
#define PBDown_INTCFG                 (* (reg32 *) PBDown__INTCFG)
#define PBDown_INTSTAT                (* (reg32 *) PBDown__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PBDown_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PBDown__SIO)
    #define PBDown_SIO_REG            (* (reg32 *) PBDown__SIO)
#endif /* (PBDown__SIO_CFG) */

/* USBIO registers */
#if !defined(PBDown__PC) && (CY_PSOC4_4200L)
    #define PBDown_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PBDown_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PBDown_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PBDown_DRIVE_MODE_SHIFT       (0x00u)
#define PBDown_DRIVE_MODE_MASK        (0x07u << PBDown_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PBDown_H */


/* [] END OF FILE */
