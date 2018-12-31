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

#include "iprintf.h"
#include "BLE_Applications.h"
#include "BuzzerImp.h"

/**** Defines *****************************************/
#define CLOCK_FREQ 48000000                     //Frequency of the system's clock
#define INTERRUPT_FREQ 1000                     //Value to devide the clock in, for tick timer   
#define SYSTICK_INTERRUPT_VECTORE_NUMBER 15u    //Cortex M0 and M0+ hard vector.

/**** Private functions decleration *******************/
void Init(void);
uint32_t TickCounter= 0;






/**** Private functions *******************************/
/*************************************************************
* Name: CY_ISR
* Parameters[in]: SysTick_ISR
* Return: None
* Description: This fuction is the interrupt handler of SysTick
* for the system

************************************************************/

CY_ISR(SysTick_ISR)
{
   TickCounter++;
}

/*************************************************************
* Name: SysTickGet
* Parameters[in]: None
* Return: TickCounter
* Description: This is the get function for the TickCounter

************************************************************/
uint32_t SysTickGet(void)
{
  return TickCounter;
}

/*************************************************************
* Name: Init
* Parameters[in]: None
* Return: None
* Description: This fuction contains all of the init functions
*              and the starts of all of the components

************************************************************/
void Init(void)
{
    SCB_1_Start();                                                              //Init the component of UART
    BuzzerPWM_Start();
    CyBle_Start(CustomEventHandler);                                            //BLE init
    CyIntSetSysVector(SYSTICK_INTERRUPT_VECTORE_NUMBER, SysTick_ISR);           //Init systick        
    (void)SysTick_Config(CLOCK_FREQ/INTERRUPT_FREQ);
    CyGlobalIntEnable;                                                          //Enable global interrupts. 
    
    
    iprintf("**********************\n\r");
    iprintf("Application start from IAR!!!\n\rFW version V1.0.0\n\r");
    iprintf("**********************\n\r");
}


//uint8_t Arr2Print[20] = {0x05, 0x07, 0x34, 0x05, 0x07, 0x34, 0x05, 0x07, 0x34,0x05, 0x07, 0x34, 0x05, 0x07, 0x34,0x05, 0x07, 0x34,0x07, 0x34};
//uint8_t Arr2Print1[20] = {0x06, 0x0F, 0xDD, 0x03, 0x07, 0x34, 0x05, 0x07, 0x34,0x05, 0x07, 0x34, 0x05, 0x07, 0x34,0x05, 0x07, 0x34,0x07, 0x34};

#define DELAY 70
int main(void)
{
    Init();
    
    for(;;)
    {
        CyBle_ProcessEvents();
        TasksScheduler();
        if(BLE_IsConnectedGet())
        {
           ;
        }   
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
