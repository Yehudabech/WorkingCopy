/*******************************************************************************
* File Name: WinchDownPin.h  
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

#if !defined(CY_PINS_WinchDownPin_ALIASES_H) /* Pins WinchDownPin_ALIASES_H */
#define CY_PINS_WinchDownPin_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define WinchDownPin_0			(WinchDownPin__0__PC)
#define WinchDownPin_0_PS		(WinchDownPin__0__PS)
#define WinchDownPin_0_PC		(WinchDownPin__0__PC)
#define WinchDownPin_0_DR		(WinchDownPin__0__DR)
#define WinchDownPin_0_SHIFT	(WinchDownPin__0__SHIFT)
#define WinchDownPin_0_INTR	((uint16)((uint16)0x0003u << (WinchDownPin__0__SHIFT*2u)))

#define WinchDownPin_INTR_ALL	 ((uint16)(WinchDownPin_0_INTR))


#endif /* End Pins WinchDownPin_ALIASES_H */


/* [] END OF FILE */
