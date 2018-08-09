/* ========================================
 * Written by Yehuda Ben Chaim
 * 06/2018 Israel
 * All Rights Reserved
 * WW FW Version 1.0.0.0

 * ========================================
*/
#define W_ROLL_UP       0x001u
#define W_ROLL_DOWN     0x010u
#define P_PULL_IN       0x011u
#define P_PUSH_OUT      0x100u

#include "Control.h"
#include "BLEApplications.h"
#include "main.h"
#include "iprintf.h"

void IncomingDataAnalys(void)
{
    uint16_t incomingDataAll = ((password[0]<<8) & 0xFF00) | (password[1] & 0x00FF);
    //iprintf("The value of incomingDataAll is: %x\n\r", incomingDataAll);
    switch(incomingDataAll)
    {
        case IN:
            iprintf("The load in coming in\n\r");
        
        break;
        case OUT:
        
        break;
        case UP:
        
        break;
        case DOWN:
        
        break;
        case UP_AND_IN:
        
        break;
        case OUT_AND_DOWN:
        
        break;
        case STOP:
        
        break;
        defauls:
            iprintf("No such command, please try again\n\r");
        break;
    }
    if(password[1] == 0x10)
    {
        LED_Write(ON);
    }
    else
        LED_Write(OFF);
}