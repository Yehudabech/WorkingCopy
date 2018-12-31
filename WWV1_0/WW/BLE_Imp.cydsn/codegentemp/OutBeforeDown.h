/*******************************************************************************
* File Name: OutBeforeDown.h  
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

#if !defined(CY_PINS_OutBeforeDown_H) /* Pins OutBeforeDown_H */
#define CY_PINS_OutBeforeDown_H

#include "cytypes.h"
#include "cyfitter.h"
#include "OutBeforeDown_aliases.h"


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
} OutBeforeDown_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   OutBeforeDown_Read(void);
void    OutBeforeDown_Write(uint8 value);
uint8   OutBeforeDown_ReadDataReg(void);
#if defined(OutBeforeDown__PC) || (CY_PSOC4_4200L) 
    void    OutBeforeDown_SetDriveMode(uint8 mode);
#endif
void    OutBeforeDown_SetInterruptMode(uint16 position, uint16 mode);
uint8   OutBeforeDown_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void OutBeforeDown_Sleep(void); 
void OutBeforeDown_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(OutBeforeDown__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define OutBeforeDown_DRIVE_MODE_BITS        (3)
    #define OutBeforeDown_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - OutBeforeDown_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the OutBeforeDown_SetDriveMode() function.
         *  @{
         */
        #define OutBeforeDown_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define OutBeforeDown_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define OutBeforeDown_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define OutBeforeDown_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define OutBeforeDown_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define OutBeforeDown_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define OutBeforeDown_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define OutBeforeDown_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define OutBeforeDown_MASK               OutBeforeDown__MASK
#define OutBeforeDown_SHIFT              OutBeforeDown__SHIFT
#define OutBeforeDown_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in OutBeforeDown_SetInterruptMode() function.
     *  @{
     */
        #define OutBeforeDown_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define OutBeforeDown_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define OutBeforeDown_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define OutBeforeDown_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(OutBeforeDown__SIO)
    #define OutBeforeDown_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(OutBeforeDown__PC) && (CY_PSOC4_4200L)
    #define OutBeforeDown_USBIO_ENABLE               ((uint32)0x80000000u)
    #define OutBeforeDown_USBIO_DISABLE              ((uint32)(~OutBeforeDown_USBIO_ENABLE))
    #define OutBeforeDown_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define OutBeforeDown_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define OutBeforeDown_USBIO_ENTER_SLEEP          ((uint32)((1u << OutBeforeDown_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << OutBeforeDown_USBIO_SUSPEND_DEL_SHIFT)))
    #define OutBeforeDown_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << OutBeforeDown_USBIO_SUSPEND_SHIFT)))
    #define OutBeforeDown_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << OutBeforeDown_USBIO_SUSPEND_DEL_SHIFT)))
    #define OutBeforeDown_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(OutBeforeDown__PC)
    /* Port Configuration */
    #define OutBeforeDown_PC                 (* (reg32 *) OutBeforeDown__PC)
#endif
/* Pin State */
#define OutBeforeDown_PS                     (* (reg32 *) OutBeforeDown__PS)
/* Data Register */
#define OutBeforeDown_DR                     (* (reg32 *) OutBeforeDown__DR)
/* Input Buffer Disable Override */
#define OutBeforeDown_INP_DIS                (* (reg32 *) OutBeforeDown__PC2)

/* Interrupt configuration Registers */
#define OutBeforeDown_INTCFG                 (* (reg32 *) OutBeforeDown__INTCFG)
#define OutBeforeDown_INTSTAT                (* (reg32 *) OutBeforeDown__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define OutBeforeDown_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(OutBeforeDown__SIO)
    #define OutBeforeDown_SIO_REG            (* (reg32 *) OutBeforeDown__SIO)
#endif /* (OutBeforeDown__SIO_CFG) */

/* USBIO registers */
#if !defined(OutBeforeDown__PC) && (CY_PSOC4_4200L)
    #define OutBeforeDown_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define OutBeforeDown_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define OutBeforeDown_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define OutBeforeDown_DRIVE_MODE_SHIFT       (0x00u)
#define OutBeforeDown_DRIVE_MODE_MASK        (0x07u << OutBeforeDown_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins OutBeforeDown_H */


/* [] END OF FILE */
