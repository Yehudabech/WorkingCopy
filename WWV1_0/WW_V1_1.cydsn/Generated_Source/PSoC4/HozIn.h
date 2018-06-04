/*******************************************************************************
* File Name: HozIn.h  
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

#if !defined(CY_PINS_HozIn_H) /* Pins HozIn_H */
#define CY_PINS_HozIn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "HozIn_aliases.h"


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
} HozIn_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   HozIn_Read(void);
void    HozIn_Write(uint8 value);
uint8   HozIn_ReadDataReg(void);
#if defined(HozIn__PC) || (CY_PSOC4_4200L) 
    void    HozIn_SetDriveMode(uint8 mode);
#endif
void    HozIn_SetInterruptMode(uint16 position, uint16 mode);
uint8   HozIn_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void HozIn_Sleep(void); 
void HozIn_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(HozIn__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define HozIn_DRIVE_MODE_BITS        (3)
    #define HozIn_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - HozIn_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the HozIn_SetDriveMode() function.
         *  @{
         */
        #define HozIn_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define HozIn_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define HozIn_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define HozIn_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define HozIn_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define HozIn_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define HozIn_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define HozIn_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define HozIn_MASK               HozIn__MASK
#define HozIn_SHIFT              HozIn__SHIFT
#define HozIn_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HozIn_SetInterruptMode() function.
     *  @{
     */
        #define HozIn_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define HozIn_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define HozIn_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define HozIn_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(HozIn__SIO)
    #define HozIn_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(HozIn__PC) && (CY_PSOC4_4200L)
    #define HozIn_USBIO_ENABLE               ((uint32)0x80000000u)
    #define HozIn_USBIO_DISABLE              ((uint32)(~HozIn_USBIO_ENABLE))
    #define HozIn_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define HozIn_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define HozIn_USBIO_ENTER_SLEEP          ((uint32)((1u << HozIn_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << HozIn_USBIO_SUSPEND_DEL_SHIFT)))
    #define HozIn_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << HozIn_USBIO_SUSPEND_SHIFT)))
    #define HozIn_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << HozIn_USBIO_SUSPEND_DEL_SHIFT)))
    #define HozIn_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(HozIn__PC)
    /* Port Configuration */
    #define HozIn_PC                 (* (reg32 *) HozIn__PC)
#endif
/* Pin State */
#define HozIn_PS                     (* (reg32 *) HozIn__PS)
/* Data Register */
#define HozIn_DR                     (* (reg32 *) HozIn__DR)
/* Input Buffer Disable Override */
#define HozIn_INP_DIS                (* (reg32 *) HozIn__PC2)

/* Interrupt configuration Registers */
#define HozIn_INTCFG                 (* (reg32 *) HozIn__INTCFG)
#define HozIn_INTSTAT                (* (reg32 *) HozIn__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define HozIn_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(HozIn__SIO)
    #define HozIn_SIO_REG            (* (reg32 *) HozIn__SIO)
#endif /* (HozIn__SIO_CFG) */

/* USBIO registers */
#if !defined(HozIn__PC) && (CY_PSOC4_4200L)
    #define HozIn_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define HozIn_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define HozIn_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define HozIn_DRIVE_MODE_SHIFT       (0x00u)
#define HozIn_DRIVE_MODE_MASK        (0x07u << HozIn_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins HozIn_H */


/* [] END OF FILE */
