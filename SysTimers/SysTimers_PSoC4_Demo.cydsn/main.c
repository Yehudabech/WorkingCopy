/* ========================================
 *
 * Demo project to test the SysTimers component
 * on PSoC 4.
 *
 * 9-19-2013 meh Test System timer on PSoC 54
 *
 * This project toggles the following GPIOs
 * at a different rate.
 *
 * P02 4 Hz   (red LED)
 * P03 2 Hz   (green LED)
 * P16 1 Hz   (blue LED)
 * P20 0.5 Hz
 * ========================================
*/
#include <device.h>

void main()
{
    uint32 red_timerID, green_timerID, blue_timerID, pulse_timerID;

    SysTimers_Start();

    CyGlobalIntEnable;  /* Uncomment this line to enable global interrupts. */
 
	red_timerID   = SysTimers_GetTimer(SysTimers_TICKS_PER_SECOND/4);  // 4 Hz
	green_timerID = SysTimers_GetTimer(SysTimers_TICKS_PER_SECOND/2);  // 2 Hz 
	blue_timerID  = SysTimers_GetTimer(SysTimers_TICKS_PER_SECOND/1);  // 1 Hz
	pulse_timerID = SysTimers_GetTimer(SysTimers_TICKS_PER_SECOND*2);  // 2 Second timer

	
    for(;;)
    {
        if( SysTimers_GetTimerStatus(green_timerID)) 
		{
		    P02_Green_Write(P02_Green_Read() ? 0 : 1);  // Toggle Green
	    }
		
		if( SysTimers_GetTimerStatus(blue_timerID)) 
		{
		    P03_Blue_Write(P03_Blue_Read() ? 0 : 1);     // Toggle Blue
	    }
		
		if( SysTimers_GetTimerStatus(red_timerID)) 
		{
		    P16_Red_Write(P16_Red_Read() ? 0 : 1);        // Toggle Red
		}
		
		if( SysTimers_GetTimerStatus(pulse_timerID)) 
		{
		    P20_Pulse_Write(P20_Pulse_Read() ? 0 : 1);        // Toggle Pulse
		}
    }
}

/* [] END OF FILE */
