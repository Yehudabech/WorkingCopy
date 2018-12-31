/* ========================================
 *
 * Demo project to test the SysTimers component
 * on PSoC 5LP.
 *
 * 9-19-2013 meh Test System timer on PSoC 5LP
 *
 * This project toggles the following GPIOs
 * at a different rates.
 *
 * P60 1 Hz   
 * P66 2 Hz   
 * P62 1 Hz  
 * P20 0.5 Hz
 * ========================================
*/
#include <device.h>

void main()
{
    uint32 LED1_timerID, LED2_timerID, LED3_timerID, LED4_timerID;
	
    SysTimers_Start();

    CyGlobalIntEnable;  /* Uncomment this line to enable global interrupts. */
	 
	LED1_timerID = SysTimers_GetTimer(SysTimers_TICKS_PER_SECOND/1); // Change LED state at 1 Hz
	LED2_timerID = SysTimers_GetTimer(SysTimers_TICKS_PER_SECOND/2); // Change LED state at 2 Hz
	LED3_timerID = SysTimers_GetTimer(SysTimers_TICKS_PER_SECOND/4); // Change LED state at 4 Hz
	LED4_timerID = SysTimers_GetTimer(SysTimers_TICKS_PER_SECOND/8); // Change LED state at 8 Hz
	
    for(;;)
    {
        if( SysTimers_GetTimerStatus(LED1_timerID)) 
		{
		    P60_LED1_Write(P60_LED1_Read() ? 0 : 1);  // Toggle LED1
	    }
		
		if( SysTimers_GetTimerStatus(LED2_timerID)) 
		{
		    P66_LED2_Write(P66_LED2_Read() ? 0 : 1);   // Toggle LED2
	    }
		
		if( SysTimers_GetTimerStatus(LED3_timerID)) 
		{
		    P62_LED3_Write(P62_LED3_Read() ? 0 : 1);    // Toggle LED3
		}
		
		if( SysTimers_GetTimerStatus(LED4_timerID)) 
		{
		    P63_LED4_Write(P63_LED4_Read() ? 0 : 1);     // Toggle LED4
		}
    }
}

/* [] END OF FILE */
