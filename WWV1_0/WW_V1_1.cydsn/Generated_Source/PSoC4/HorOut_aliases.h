/*******************************************************************************
* File Name: HorOut.h  
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

#if !defined(CY_PINS_HorOut_ALIASES_H) /* Pins HorOut_ALIASES_H */
#define CY_PINS_HorOut_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define HorOut_0			(HorOut__0__PC)
#define HorOut_0_PS		(HorOut__0__PS)
#define HorOut_0_PC		(HorOut__0__PC)
#define HorOut_0_DR		(HorOut__0__DR)
#define HorOut_0_SHIFT	(HorOut__0__SHIFT)
#define HorOut_0_INTR	((uint16)((uint16)0x0003u << (HorOut__0__SHIFT*2u)))

#define HorOut_INTR_ALL	 ((uint16)(HorOut_0_INTR))


#endif /* End Pins HorOut_ALIASES_H */


/* [] END OF FILE */
