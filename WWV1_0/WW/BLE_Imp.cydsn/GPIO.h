/* ========================================
 *
 * Copyright Yehuda Ben Chaim, 2018
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF Yehuda Ben Chaim.
 *
 * ========================================
*/

/**** Includes *****************************************/
#include "project.h"

/**** Private functions decleration *******************/

/**** Private functions *******************************/

uint8_t OperationsMain(uint8_t ReceivedByte);

/*************************************************************
* Name: OutBeforeDown_CallbackFucntion
* Parameters[in]: None
* Return: None
* Description: This fuction is the callback funciton of 
* OutBeforeDown pin interrupt.

************************************************************/
void OutBeforeDown_CallbackFucntion(void);


/*************************************************************
* Name: UpBeforeIn_CallbackFucntion
* Parameters[in]: None
* Return: None
* Description: This fuction is the callback funciton of 
* UpBeforeIn pin interrupt.

************************************************************/
void UpBeforeIn_CallbackFucntion(void);


/* [] END OF FILE */
