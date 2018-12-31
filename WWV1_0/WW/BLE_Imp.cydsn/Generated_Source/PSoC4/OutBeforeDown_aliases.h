/*******************************************************************************
* File Name: OutBeforeDown.h  
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

#if !defined(CY_PINS_OutBeforeDown_ALIASES_H) /* Pins OutBeforeDown_ALIASES_H */
#define CY_PINS_OutBeforeDown_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define OutBeforeDown_0			(OutBeforeDown__0__PC)
#define OutBeforeDown_0_PS		(OutBeforeDown__0__PS)
#define OutBeforeDown_0_PC		(OutBeforeDown__0__PC)
#define OutBeforeDown_0_DR		(OutBeforeDown__0__DR)
#define OutBeforeDown_0_SHIFT	(OutBeforeDown__0__SHIFT)
#define OutBeforeDown_0_INTR	((uint16)((uint16)0x0003u << (OutBeforeDown__0__SHIFT*2u)))

#define OutBeforeDown_INTR_ALL	 ((uint16)(OutBeforeDown_0_INTR))


#endif /* End Pins OutBeforeDown_ALIASES_H */


/* [] END OF FILE */
