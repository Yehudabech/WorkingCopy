/*******************************************************************************
* File Name: PBIn.h  
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

#if !defined(CY_PINS_PBIn_H) /* Pins PBIn_H */
#define CY_PINS_PBIn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PBIn_aliases.h"


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
} PBIn_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PBIn_Read(void);
void    PBIn_Write(uint8 value);
uint8   PBIn_ReadDataReg(void);
#if defined(PBIn__PC) || (CY_PSOC4_4200L) 
    void    PBIn_SetDriveMode(uint8 mode);
#endif
void    PBIn_SetInterruptMode(uint16 position, uint16 mode);
uint8   PBIn_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PBIn_Sleep(void); 
void PBIn_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PBIn__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PBIn_DRIVE_MODE_BITS        (3)
    #define PBIn_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PBIn_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PBIn_SetDriveMode() function.
         *  @{
         */
        #define PBIn_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PBIn_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PBIn_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PBIn_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PBIn_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PBIn_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PBIn_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PBIn_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PBIn_MASK               PBIn__MASK
#define PBIn_SHIFT              PBIn__SHIFT
#define PBIn_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PBIn_SetInterruptMode() function.
     *  @{
     */
        #define PBIn_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PBIn_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PBIn_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PBIn_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PBIn__SIO)
    #define PBIn_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PBIn__PC) && (CY_PSOC4_4200L)
    #define PBIn_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PBIn_USBIO_DISABLE              ((uint32)(~PBIn_USBIO_ENABLE))
    #define PBIn_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PBIn_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PBIn_USBIO_ENTER_SLEEP          ((uint32)((1u << PBIn_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PBIn_USBIO_SUSPEND_DEL_SHIFT)))
    #define PBIn_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PBIn_USBIO_SUSPEND_SHIFT)))
    #define PBIn_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PBIn_USBIO_SUSPEND_DEL_SHIFT)))
    #define PBIn_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PBIn__PC)
    /* Port Configuration */
    #define PBIn_PC                 (* (reg32 *) PBIn__PC)
#endif
/* Pin State */
#define PBIn_PS                     (* (reg32 *) PBIn__PS)
/* Data Register */
#define PBIn_DR                     (* (reg32 *) PBIn__DR)
/* Input Buffer Disable Override */
#define PBIn_INP_DIS                (* (reg32 *) PBIn__PC2)

/* Interrupt configuration Registers */
#define PBIn_INTCFG                 (* (reg32 *) PBIn__INTCFG)
#define PBIn_INTSTAT                (* (reg32 *) PBIn__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PBIn_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PBIn__SIO)
    #define PBIn_SIO_REG            (* (reg32 *) PBIn__SIO)
#endif /* (PBIn__SIO_CFG) */

/* USBIO registers */
#if !defined(PBIn__PC) && (CY_PSOC4_4200L)
    #define PBIn_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PBIn_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PBIn_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PBIn_DRIVE_MODE_SHIFT       (0x00u)
#define PBIn_DRIVE_MODE_MASK        (0x07u << PBIn_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PBIn_H */


/* [] END OF FILE */
