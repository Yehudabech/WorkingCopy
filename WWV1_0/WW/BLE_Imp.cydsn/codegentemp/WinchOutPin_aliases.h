/*******************************************************************************
* File Name: WinchOutPin.h  
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

#if !defined(CY_PINS_WinchOutPin_ALIASES_H) /* Pins WinchOutPin_ALIASES_H */
#define CY_PINS_WinchOutPin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define WinchOutPin_0			(WinchOutPin__0__PC)
#define WinchOutPin_0_PS		(WinchOutPin__0__PS)
#define WinchOutPin_0_PC		(WinchOutPin__0__PC)
#define WinchOutPin_0_DR		(WinchOutPin__0__DR)
#define WinchOutPin_0_SHIFT	(WinchOutPin__0__SHIFT)
#define WinchOutPin_0_INTR	((uint16)((uint16)0x0003u << (WinchOutPin__0__SHIFT*2u)))

#define WinchOutPin_INTR_ALL	 ((uint16)(WinchOutPin_0_INTR))


#endif /* End Pins WinchOutPin_ALIASES_H */


/* [] END OF FILE */
