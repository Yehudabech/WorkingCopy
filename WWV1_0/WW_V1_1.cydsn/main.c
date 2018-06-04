/* ========================================
 * Written by Yehuda Ben Chaim
 * 06/2018 Israel
 * All Rights Reserved
 * WW FW Version 1.0.0.0

 * ========================================
*/
#include <project.h>
#include <BLEApplications.h>
#include "Control.h"
#include "iprintf.h"


void AppCallBack(uint32 event, void* eventParam);
int main (void)
{
    CyGlobalIntEnable;
    CyBle_Start(CustomEventHandler);            //Start BLE component. the CustomEventHandler argument located in BLEApplication.c file
    SCB_1_Start();                              //Start the UART component of iprintf. UART as logger.
    iprintf("Start up, welcome!");
    for(;;)
    {
        if(CyBle_GetState() == CYBLE_STATE_CONNECTED)
        {
            CyBle_ProcessEvents();
        }
        CyBle_ProcessEvents();
        IncomingDataAnalys();
        
    }
}

