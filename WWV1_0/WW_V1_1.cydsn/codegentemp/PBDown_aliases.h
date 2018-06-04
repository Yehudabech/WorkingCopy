/*******************************************************************************
* File Name: PBDown.h  
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

#if !defined(CY_PINS_PBDown_ALIASES_H) /* Pins PBDown_ALIASES_H */
#define CY_PINS_PBDown_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PBDown_0			(PBDown__0__PC)
#define PBDown_0_PS		(PBDown__0__PS)
#define PBDown_0_PC		(PBDown__0__PC)
#define PBDown_0_DR		(PBDown__0__DR)
#define PBDown_0_SHIFT	(PBDown__0__SHIFT)
#define PBDown_0_INTR	((uint16)((uint16)0x0003u << (PBDown__0__SHIFT*2u)))

#define PBDown_INTR_ALL	 ((uint16)(PBDown_0_INTR))


#endif /* End Pins PBDown_ALIASES_H */


/* [] END OF FILE */
