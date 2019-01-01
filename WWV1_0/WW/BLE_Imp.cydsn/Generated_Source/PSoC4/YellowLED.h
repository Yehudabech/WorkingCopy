/*******************************************************************************
* File Name: YellowLED.h  
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

#if !defined(CY_PINS_YellowLED_H) /* Pins YellowLED_H */
#define CY_PINS_YellowLED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "YellowLED_aliases.h"


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
} YellowLED_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   YellowLED_Read(void);
void    YellowLED_Write(uint8 value);
uint8   YellowLED_ReadDataReg(void);
#if defined(YellowLED__PC) || (CY_PSOC4_4200L) 
    void    YellowLED_SetDriveMode(uint8 mode);
#endif
void    YellowLED_SetInterruptMode(uint16 position, uint16 mode);
uint8   YellowLED_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void YellowLED_Sleep(void); 
void YellowLED_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(YellowLED__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define YellowLED_DRIVE_MODE_BITS        (3)
    #define YellowLED_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - YellowLED_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the YellowLED_SetDriveMode() function.
         *  @{
         */
        #define YellowLED_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define YellowLED_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define YellowLED_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define YellowLED_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define YellowLED_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define YellowLED_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define YellowLED_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define YellowLED_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define YellowLED_MASK               YellowLED__MASK
#define YellowLED_SHIFT              YellowLED__SHIFT
#define YellowLED_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in YellowLED_SetInterruptMode() function.
     *  @{
     */
        #define YellowLED_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define YellowLED_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define YellowLED_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define YellowLED_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(YellowLED__SIO)
    #define YellowLED_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(YellowLED__PC) && (CY_PSOC4_4200L)
    #define YellowLED_USBIO_ENABLE               ((uint32)0x80000000u)
    #define YellowLED_USBIO_DISABLE              ((uint32)(~YellowLED_USBIO_ENABLE))
    #define YellowLED_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define YellowLED_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define YellowLED_USBIO_ENTER_SLEEP          ((uint32)((1u << YellowLED_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << YellowLED_USBIO_SUSPEND_DEL_SHIFT)))
    #define YellowLED_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << YellowLED_USBIO_SUSPEND_SHIFT)))
    #define YellowLED_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << YellowLED_USBIO_SUSPEND_DEL_SHIFT)))
    #define YellowLED_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(YellowLED__PC)
    /* Port Configuration */
    #define YellowLED_PC                 (* (reg32 *) YellowLED__PC)
#endif
/* Pin State */
#define YellowLED_PS                     (* (reg32 *) YellowLED__PS)
/* Data Register */
#define YellowLED_DR                     (* (reg32 *) YellowLED__DR)
/* Input Buffer Disable Override */
#define YellowLED_INP_DIS                (* (reg32 *) YellowLED__PC2)

/* Interrupt configuration Registers */
#define YellowLED_INTCFG                 (* (reg32 *) YellowLED__INTCFG)
#define YellowLED_INTSTAT                (* (reg32 *) YellowLED__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define YellowLED_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(YellowLED__SIO)
    #define YellowLED_SIO_REG            (* (reg32 *) YellowLED__SIO)
#endif /* (YellowLED__SIO_CFG) */

/* USBIO registers */
#if !defined(YellowLED__PC) && (CY_PSOC4_4200L)
    #define YellowLED_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define YellowLED_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define YellowLED_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define YellowLED_DRIVE_MODE_SHIFT       (0x00u)
#define YellowLED_DRIVE_MODE_MASK        (0x07u << YellowLED_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins YellowLED_H */


/* [] END OF FILE */
