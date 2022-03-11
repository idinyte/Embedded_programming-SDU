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
#define GREEN   8
#define YELLOW   9
#define RED   10
#define PINK   11
#define NONE   12


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/


void leds( INT8U color )
/*****************************************************************************
 *   Input    :
 *   Output   :
 *   Function :
 ******************************************************************************/
{
    if (color == GREEN)
    {
        GPIO_PORTF_DATA_R &= ~(0xE); // clear led colors
        GPIO_PORTF_DATA_R |= 0x08; // green
    }
    else if (color == YELLOW)
    {
        GPIO_PORTF_DATA_R &= ~(0xE); // clear led colors
        GPIO_PORTF_DATA_R |= 0x0A; // yellow
    }

    else if (color == RED)
    {
        GPIO_PORTF_DATA_R &= ~(0xE); // clear led colors
        GPIO_PORTF_DATA_R |= 0x02; // red
    }
    else if (color == PINK)
    {
        GPIO_PORTF_DATA_R &= ~(0xE); // clear led colors
        GPIO_PORTF_DATA_R |= 0x06; // pink
    }
    else if (color == NONE)
    {
        GPIO_PORTF_DATA_R &= ~(0xE); // clear led colors
    }
}

/****************************** End Of Module *******************************/












