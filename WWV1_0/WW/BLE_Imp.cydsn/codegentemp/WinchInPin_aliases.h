/*******************************************************************************
* File Name: WinchInPin.h  
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

#if !defined(CY_PINS_WinchInPin_ALIASES_H) /* Pins WinchInPin_ALIASES_H */
#define CY_PINS_WinchInPin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define WinchInPin_0			(WinchInPin__0__PC)
#define WinchInPin_0_PS		(WinchInPin__0__PS)
#define WinchInPin_0_PC		(WinchInPin__0__PC)
#define WinchInPin_0_DR		(WinchInPin__0__DR)
#define WinchInPin_0_SHIFT	(WinchInPin__0__SHIFT)
#define WinchInPin_0_INTR	((uint16)((uint16)0x0003u << (WinchInPin__0__SHIFT*2u)))

#define WinchInPin_INTR_ALL	 ((uint16)(WinchInPin_0_INTR))


#endif /* End Pins WinchInPin_ALIASES_H */


/* [] END OF FILE */
