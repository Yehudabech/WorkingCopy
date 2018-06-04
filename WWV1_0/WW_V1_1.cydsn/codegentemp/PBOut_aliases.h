/*******************************************************************************
* File Name: PBOut.h  
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

#if !defined(CY_PINS_PBOut_ALIASES_H) /* Pins PBOut_ALIASES_H */
#define CY_PINS_PBOut_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PBOut_0			(PBOut__0__PC)
#define PBOut_0_PS		(PBOut__0__PS)
#define PBOut_0_PC		(PBOut__0__PC)
#define PBOut_0_DR		(PBOut__0__DR)
#define PBOut_0_SHIFT	(PBOut__0__SHIFT)
#define PBOut_0_INTR	((uint16)((uint16)0x0003u << (PBOut__0__SHIFT*2u)))

#define PBOut_INTR_ALL	 ((uint16)(PBOut_0_INTR))


#endif /* End Pins PBOut_ALIASES_H */


/* [] END OF FILE */
