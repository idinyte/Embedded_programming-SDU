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
#ifndef EVENT_MANAGER_H_
#define EVENT_MANAGER_H_


/***************************** Include files *******************************/
#include "emp_type.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

void event_manager( INT8U event );
/*****************************************************************************
*   Input    : The wanted counter value
*   Output   : -
*   Function : Turn on counter leds according to countervalue.
******************************************************************************/


/****************************** End Of Module *******************************/


#endif /* EVENT_MANAGER_H_ */
