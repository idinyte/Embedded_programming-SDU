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

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/


void counter_leds( INT8U counter_value )
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
  if( counter_value &  0x01 )	// Red LED PF3, Counter bit 0
    GPIO_PORTF_DATA_R |= 0x08;
  else
    GPIO_PORTF_DATA_R &= 0xF7;

  if( counter_value &  0x02 )	// Blue LED PF3, Counter bit 1
    GPIO_PORTF_DATA_R |= 0x04;
  else
    GPIO_PORTF_DATA_R &= 0xFB;

  if( counter_value &  0x04 )	// Green LED PF1, Counter bit 2
    GPIO_PORTF_DATA_R |= 0x02;
  else
    GPIO_PORTF_DATA_R &= 0xBD;
}

/****************************** End Of Module *******************************/












