/*******************************************************************************
* File Name: PBUp.h  
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

#if !defined(CY_PINS_PBUp_ALIASES_H) /* Pins PBUp_ALIASES_H */
#define CY_PINS_PBUp_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PBUp_0			(PBUp__0__PC)
#define PBUp_0_PS		(PBUp__0__PS)
#define PBUp_0_PC		(PBUp__0__PC)
#define PBUp_0_DR		(PBUp__0__DR)
#define PBUp_0_SHIFT	(PBUp__0__SHIFT)
#define PBUp_0_INTR	((uint16)((uint16)0x0003u << (PBUp__0__SHIFT*2u)))

#define PBUp_INTR_ALL	 ((uint16)(PBUp_0_INTR))


#endif /* End Pins PBUp_ALIASES_H */


/* [] END OF FILE */
