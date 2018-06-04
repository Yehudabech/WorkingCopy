/*******************************************************************************
* File Name: VerUp.h  
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

#if !defined(CY_PINS_VerUp_ALIASES_H) /* Pins VerUp_ALIASES_H */
#define CY_PINS_VerUp_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define VerUp_0			(VerUp__0__PC)
#define VerUp_0_PS		(VerUp__0__PS)
#define VerUp_0_PC		(VerUp__0__PC)
#define VerUp_0_DR		(VerUp__0__DR)
#define VerUp_0_SHIFT	(VerUp__0__SHIFT)
#define VerUp_0_INTR	((uint16)((uint16)0x0003u << (VerUp__0__SHIFT*2u)))

#define VerUp_INTR_ALL	 ((uint16)(VerUp_0_INTR))


#endif /* End Pins VerUp_ALIASES_H */


/* [] END OF FILE */
