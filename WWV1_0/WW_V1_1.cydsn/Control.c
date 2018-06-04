/* ========================================
 * Written by Yehuda Ben Chaim
 * 06/2018 Israel
 * All Rights Reserved
 * WW FW Version 1.0.0.0

 * ========================================
*/
#include "Control.h"
#include "BLEApplications.h"

void IncomingDataAnalys(void)
{
    if(password[1] == 0x55)
    {
        LED_Write(1);
    }
    else
        LED_Write(0);
}