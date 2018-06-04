/*******************************************************************************
* File Name: PB_Down.h  
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

#if !defined(CY_PINS_PB_Down_ALIASES_H) /* Pins PB_Down_ALIASES_H */
#define CY_PINS_PB_Down_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PB_Down_0			(PB_Down__0__PC)
#define PB_Down_0_PS		(PB_Down__0__PS)
#define PB_Down_0_PC		(PB_Down__0__PC)
#define PB_Down_0_DR		(PB_Down__0__DR)
#define PB_Down_0_SHIFT	(PB_Down__0__SHIFT)
#define PB_Down_0_INTR	((uint16)((uint16)0x0003u << (PB_Down__0__SHIFT*2u)))

#define PB_Down_INTR_ALL	 ((uint16)(PB_Down_0_INTR))


#endif /* End Pins PB_Down_ALIASES_H */


/* [] END OF FILE */
