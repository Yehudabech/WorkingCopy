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
#include "iprintf.h"
#include "BLE_Applications.h"

/**** Private functions decleration *******************/
void Init(void);





/**** Private functions *******************************/

/*************************************************************
* Name: Init
* Parameters[in]: None
* Return: None
* Description: This fuction contains all of the init functions
*              and the starts of all of the components

************************************************************/
void Init(void)
{
    SCB_1_Start();
    CyBle_Start(CustomEventHandler);
    CyGlobalIntEnable; /* Enable global interrupts. */
}



int main(void)
{
    Init();
    
    for(;;)
    {
        CyBle_ProcessEvents();
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
