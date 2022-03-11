/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: countled.h
*
* PROJECT....: EMP
*
* DESCRIPTION: Turn on counter leds according to countervalue.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 100925  MoH   Module created.
*
*****************************************************************************/
#ifndef LED_H_
#define LED_H_


/***************************** Include files *******************************/
#include "emp_type.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

void leds( INT8U state );
/*****************************************************************************
*   Input    : The wanted counter value
*   Output   : -
*   Function : Turn on counter leds according to countervalue.
******************************************************************************/


/****************************** End Of Module *******************************/


#endif /* LED_H_ */
