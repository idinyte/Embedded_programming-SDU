/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: countled.c
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
* 100925  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
/*****************************    Defines    *******************************/
#define UNLOCKED 5
/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/


void leds(INT8U state)
/*****************************************************************************
 *   Input    :
 *   Output   :
 *   Function :
 ******************************************************************************/
{
    if (state == UNLOCKED)
    {
        GPIO_PORTF_DATA_R &= 0xBD;
        GPIO_PORTF_DATA_R |= 0x08;
    }
    else
    {
        GPIO_PORTF_DATA_R &= 0xF7;
        GPIO_PORTF_DATA_R |= 0x02;
    }

}

/****************************** End Of Module *******************************/












