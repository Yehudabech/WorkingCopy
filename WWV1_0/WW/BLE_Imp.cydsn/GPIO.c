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
#include "GPIO.h"
#include "iprintf.h"


/**** Defines *****************************************/
#define PIN_ON                  1
#define PIN_OFF                 0

enum
{
  UP,
  DOWN,
  IN,
  OUT,
  STOP_UP,
  STOP_DOWN,
  STOP_IN,
  STOP_OUT,
  UP_AND_IN,
  OUT_AND_DOWN,
  STOP_ALL
}Operations;
/**** Private functions decleration *******************/

/**** Private functions *******************************/

uint8_t OperationsMain(uint8_t ReceivedByte)
{   
  uint8_t Val2Ret = 0 ;
  switch(ReceivedByte)
  {
  case UP:
    iprintf(" UP command received\n\r");
    WinchUpPin_Write(PIN_ON);
    break;
  case DOWN:
    iprintf(" DOWN command received\n\r");
    WinchDownPin_Write(PIN_ON);
    break;
  case IN:
    iprintf(" IN command received\n\r");
    WinchInPin_Write(PIN_ON);
    break;
  case OUT:
    iprintf(" OUT command received\n\r");
    WinchOutPin_Write(PIN_ON);
    break;
  case STOP_UP:
    iprintf(" STOP_UP command received\n\r");
    WinchUpPin_Write(PIN_OFF);
    break;
  case STOP_DOWN:
    iprintf(" STOP_DOWN command received\n\r");
    WinchDownPin_Write(PIN_OFF);
    break;
  case STOP_IN:
    iprintf(" STOP_IN command received\n\r");
    WinchInPin_Write(PIN_OFF);
    break;
  case STOP_OUT:
    iprintf(" STOP_OUT command received\n\r");
    WinchOutPin_Write(PIN_OFF);
    break;
  case UP_AND_IN:
    iprintf(" UP_AND_IN command received\n\r");
    break;
  case OUT_AND_DOWN:
    iprintf(" OUT_AND_DOWN command received\n\r");
    break;
  case STOP_ALL:
    iprintf(" STOP_ALL command received\n\r");
    WinchUpPin_Write(PIN_OFF);
    WinchInPin_Write(PIN_OFF);
    WinchDownPin_Write(PIN_OFF);
    WinchOutPin_Write(PIN_OFF);
    break;
  default:
      break;
  }
  return Val2Ret;
}

/* [] END OF FILE */
