/*******************************************************************************
* File Name: PBUp.h  
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

#if !defined(CY_PINS_PBUp_H) /* Pins PBUp_H */
#define CY_PINS_PBUp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PBUp_aliases.h"


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
} PBUp_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PBUp_Read(void);
void    PBUp_Write(uint8 value);
uint8   PBUp_ReadDataReg(void);
#if defined(PBUp__PC) || (CY_PSOC4_4200L) 
    void    PBUp_SetDriveMode(uint8 mode);
#endif
void    PBUp_SetInterruptMode(uint16 position, uint16 mode);
uint8   PBUp_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PBUp_Sleep(void); 
void PBUp_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PBUp__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PBUp_DRIVE_MODE_BITS        (3)
    #define PBUp_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PBUp_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PBUp_SetDriveMode() function.
         *  @{
         */
        #define PBUp_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PBUp_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PBUp_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PBUp_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PBUp_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PBUp_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PBUp_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PBUp_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PBUp_MASK               PBUp__MASK
#define PBUp_SHIFT              PBUp__SHIFT
#define PBUp_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PBUp_SetInterruptMode() function.
     *  @{
     */
        #define PBUp_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PBUp_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PBUp_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PBUp_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PBUp__SIO)
    #define PBUp_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PBUp__PC) && (CY_PSOC4_4200L)
    #define PBUp_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PBUp_USBIO_DISABLE              ((uint32)(~PBUp_USBIO_ENABLE))
    #define PBUp_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PBUp_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PBUp_USBIO_ENTER_SLEEP          ((uint32)((1u << PBUp_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PBUp_USBIO_SUSPEND_DEL_SHIFT)))
    #define PBUp_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PBUp_USBIO_SUSPEND_SHIFT)))
    #define PBUp_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PBUp_USBIO_SUSPEND_DEL_SHIFT)))
    #define PBUp_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PBUp__PC)
    /* Port Configuration */
    #define PBUp_PC                 (* (reg32 *) PBUp__PC)
#endif
/* Pin State */
#define PBUp_PS                     (* (reg32 *) PBUp__PS)
/* Data Register */
#define PBUp_DR                     (* (reg32 *) PBUp__DR)
/* Input Buffer Disable Override */
#define PBUp_INP_DIS                (* (reg32 *) PBUp__PC2)

/* Interrupt configuration Registers */
#define PBUp_INTCFG                 (* (reg32 *) PBUp__INTCFG)
#define PBUp_INTSTAT                (* (reg32 *) PBUp__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PBUp_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PBUp__SIO)
    #define PBUp_SIO_REG            (* (reg32 *) PBUp__SIO)
#endif /* (PBUp__SIO_CFG) */

/* USBIO registers */
#if !defined(PBUp__PC) && (CY_PSOC4_4200L)
    #define PBUp_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PBUp_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PBUp_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PBUp_DRIVE_MODE_SHIFT       (0x00u)
#define PBUp_DRIVE_MODE_MASK        (0x07u << PBUp_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PBUp_H */


/* [] END OF FILE */
