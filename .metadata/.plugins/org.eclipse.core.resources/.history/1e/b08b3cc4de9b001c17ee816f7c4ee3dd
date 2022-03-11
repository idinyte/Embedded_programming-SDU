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
#define LOCKED   0
#define COMB1    1
#define COMB2    2
#define COMB3    3
#define COMB4    4
#define UNLOCKED 5


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

    static INT8U state = LOCKED;

    if (event)
    {
        switch (event)
        {
        case BE_SW1:
            if (state == LOCKED)
            {
                state = COMB1;
            }
            else if (state == COMB3)
            {
                state = COMB4;
            }
            else
            {
                state = COMB1;
            }
            break;
        case BE_SW2:
            if (state == COMB1)
            {
                state = COMB2;
            }
            else if (state == COMB2)
            {
                state = COMB3;
            }
            else if (state == COMB4)
            {
                state = UNLOCKED;
            }
            else
            {
                state = LOCKED;
            }
            break;
        default:
            break;
        }

    }

    return (state);
}
/****************************** End Of Module *******************************/












