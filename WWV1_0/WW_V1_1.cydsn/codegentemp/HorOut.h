/*******************************************************************************
* File Name: HorOut.h  
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

#if !defined(CY_PINS_HorOut_H) /* Pins HorOut_H */
#define CY_PINS_HorOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "HorOut_aliases.h"


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
} HorOut_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   HorOut_Read(void);
void    HorOut_Write(uint8 value);
uint8   HorOut_ReadDataReg(void);
#if defined(HorOut__PC) || (CY_PSOC4_4200L) 
    void    HorOut_SetDriveMode(uint8 mode);
#endif
void    HorOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   HorOut_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void HorOut_Sleep(void); 
void HorOut_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(HorOut__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define HorOut_DRIVE_MODE_BITS        (3)
    #define HorOut_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - HorOut_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the HorOut_SetDriveMode() function.
         *  @{
         */
        #define HorOut_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define HorOut_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define HorOut_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define HorOut_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define HorOut_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define HorOut_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define HorOut_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define HorOut_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define HorOut_MASK               HorOut__MASK
#define HorOut_SHIFT              HorOut__SHIFT
#define HorOut_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HorOut_SetInterruptMode() function.
     *  @{
     */
        #define HorOut_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define HorOut_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define HorOut_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define HorOut_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(HorOut__SIO)
    #define HorOut_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(HorOut__PC) && (CY_PSOC4_4200L)
    #define HorOut_USBIO_ENABLE               ((uint32)0x80000000u)
    #define HorOut_USBIO_DISABLE              ((uint32)(~HorOut_USBIO_ENABLE))
    #define HorOut_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define HorOut_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define HorOut_USBIO_ENTER_SLEEP          ((uint32)((1u << HorOut_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << HorOut_USBIO_SUSPEND_DEL_SHIFT)))
    #define HorOut_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << HorOut_USBIO_SUSPEND_SHIFT)))
    #define HorOut_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << HorOut_USBIO_SUSPEND_DEL_SHIFT)))
    #define HorOut_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(HorOut__PC)
    /* Port Configuration */
    #define HorOut_PC                 (* (reg32 *) HorOut__PC)
#endif
/* Pin State */
#define HorOut_PS                     (* (reg32 *) HorOut__PS)
/* Data Register */
#define HorOut_DR                     (* (reg32 *) HorOut__DR)
/* Input Buffer Disable Override */
#define HorOut_INP_DIS                (* (reg32 *) HorOut__PC2)

/* Interrupt configuration Registers */
#define HorOut_INTCFG                 (* (reg32 *) HorOut__INTCFG)
#define HorOut_INTSTAT                (* (reg32 *) HorOut__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define HorOut_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(HorOut__SIO)
    #define HorOut_SIO_REG            (* (reg32 *) HorOut__SIO)
#endif /* (HorOut__SIO_CFG) */

/* USBIO registers */
#if !defined(HorOut__PC) && (CY_PSOC4_4200L)
    #define HorOut_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define HorOut_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define HorOut_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define HorOut_DRIVE_MODE_SHIFT       (0x00u)
#define HorOut_DRIVE_MODE_MASK        (0x07u << HorOut_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins HorOut_H */


/* [] END OF FILE */
