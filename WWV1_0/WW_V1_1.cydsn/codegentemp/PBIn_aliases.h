/*******************************************************************************
* File Name: PBIn.h  
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

#if !defined(CY_PINS_PBIn_ALIASES_H) /* Pins PBIn_ALIASES_H */
#define CY_PINS_PBIn_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PBIn_0			(PBIn__0__PC)
#define PBIn_0_PS		(PBIn__0__PS)
#define PBIn_0_PC		(PBIn__0__PC)
#define PBIn_0_DR		(PBIn__0__DR)
#define PBIn_0_SHIFT	(PBIn__0__SHIFT)
#define PBIn_0_INTR	((uint16)((uint16)0x0003u << (PBIn__0__SHIFT*2u)))

#define PBIn_INTR_ALL	 ((uint16)(PBIn_0_INTR))


#endif /* End Pins PBIn_ALIASES_H */


/* [] END OF FILE */
