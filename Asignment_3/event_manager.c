/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: counter.c
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
#include "emp_type.h"
#include "events.h"
/*****************************    Defines    *******************************/
// Counter States
// --------------
#define CLEAR   0
#define DISPLAY 1



/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/



INT8U event_manager( INT8U event )
/*****************************************************************************
*   Input    : event from button press
*   Output   : counter value to set LED color
*   Function : controls counter and switches between manual and auto mode
******************************************************************************/
{

    static INT8U action = DISPLAY;

    if (event)
    {
        switch (event)
        {
        case BE_SINGLE_PUSH:
            action = CLEAR;
            break;
        case BE_DOUBBLE_PUSH:
            action = DISPLAY;
            break;
        case BE_LONG_PUSH:

            break;
        default:
            break;
        }

    }

    return (action);
}
/****************************** End Of Module *******************************/












