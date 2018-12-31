/*******************************************************************************
* File Name: UpBeforeIn.h  
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

#if !defined(CY_PINS_UpBeforeIn_ALIASES_H) /* Pins UpBeforeIn_ALIASES_H */
#define CY_PINS_UpBeforeIn_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define UpBeforeIn_0			(UpBeforeIn__0__PC)
#define UpBeforeIn_0_PS		(UpBeforeIn__0__PS)
#define UpBeforeIn_0_PC		(UpBeforeIn__0__PC)
#define UpBeforeIn_0_DR		(UpBeforeIn__0__DR)
#define UpBeforeIn_0_SHIFT	(UpBeforeIn__0__SHIFT)
#define UpBeforeIn_0_INTR	((uint16)((uint16)0x0003u << (UpBeforeIn__0__SHIFT*2u)))

#define UpBeforeIn_INTR_ALL	 ((uint16)(UpBeforeIn_0_INTR))


#endif /* End Pins UpBeforeIn_ALIASES_H */


/* [] END OF FILE */
