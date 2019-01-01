/*******************************************************************************
* File Name: YellowLED.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_YellowLED_ALIASES_H) /* Pins YellowLED_ALIASES_H */
#define CY_PINS_YellowLED_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define YellowLED_0			(YellowLED__0__PC)
#define YellowLED_0_PS		(YellowLED__0__PS)
#define YellowLED_0_PC		(YellowLED__0__PC)
#define YellowLED_0_DR		(YellowLED__0__DR)
#define YellowLED_0_SHIFT	(YellowLED__0__SHIFT)
#define YellowLED_0_INTR	((uint16)((uint16)0x0003u << (YellowLED__0__SHIFT*2u)))

#define YellowLED_INTR_ALL	 ((uint16)(YellowLED_0_INTR))


#endif /* End Pins YellowLED_ALIASES_H */


/* [] END OF FILE */
