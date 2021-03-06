/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: button.c
*
* PROJECT....: EMP
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 090215  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "button.h"
#include "events.h"
#include "emp_type.h"
/*****************************    Defines    *******************************/
#define BS_IDLE    0
#define BS_SW1     1
#define BS_SW2     2

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/
INT8U sw1_pushed()
{
  return( !(GPIO_PORTF_DATA_R & 0x10) );  // SW1 at PF4
}

INT8U sw2_pushed()
{
  return( !(GPIO_PORTF_DATA_R & 0x01) );  // SW1 at PF4
}

INT8U select_button(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
    static INT8U button_state = BS_IDLE;
    static INT8U button_event = GE_NO_EVENT;

    switch (button_state)
    {
    case BS_IDLE:
        if (sw1_pushed())		            // if button pushed
        {
            button_state = BS_SW1;
            button_event = BE_SW1;
        }
        if (sw2_pushed())                  // if button pushed
        {
            button_state = BS_SW2;
            button_event = BE_SW2;
        }
        break;
    case BS_SW1:
        if (!sw1_pushed())	                // if button released
        {
            button_state = BS_IDLE;
        }
        button_event = GE_NO_EVENT;
        break;
    case BS_SW2:
        if (!sw2_pushed())                 // if button released
        {
            button_state = BS_IDLE;
        }
        button_event = GE_NO_EVENT;
        break;
    default:
        break;
    }
    return (button_event);
}

/****************************** End Of Module *******************************/












