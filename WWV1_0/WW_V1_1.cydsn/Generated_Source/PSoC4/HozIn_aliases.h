/*******************************************************************************
* File Name: HozIn.h  
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

#if !defined(CY_PINS_HozIn_ALIASES_H) /* Pins HozIn_ALIASES_H */
#define CY_PINS_HozIn_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define HozIn_0			(HozIn__0__PC)
#define HozIn_0_PS		(HozIn__0__PS)
#define HozIn_0_PC		(HozIn__0__PC)
#define HozIn_0_DR		(HozIn__0__DR)
#define HozIn_0_SHIFT	(HozIn__0__SHIFT)
#define HozIn_0_INTR	((uint16)((uint16)0x0003u << (HozIn__0__SHIFT*2u)))

#define HozIn_INTR_ALL	 ((uint16)(HozIn_0_INTR))


#endif /* End Pins HozIn_ALIASES_H */


/* [] END OF FILE */
