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
#include "swtimers.h"
/*****************************    Defines    *******************************/
// Counter States
// --------------
#define CS_MAN_UP    0
#define CS_MAN_DOWN  1
#define CS_AUTO_UP   2
#define CS_AUTO_DOWN 3

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/


INT8U counter( INT8U event )
/*****************************************************************************
*   Input    : event from button press
*   Output   : counter value to set LED color
*   Function : controls counter and switches between manual and auto mode
******************************************************************************/
{
  static INT8U  counter_state =  CS_MAN_UP;
  static INT8U  counter_value = 0;
  static INT16U counter_timer = 0;

  if( counter_timer )					// if timer is running
    if( ! --counter_timer )				// decrement timer and check if now zero
      event = TE_TIMEOUT;				// then set event to timeout
  
  if( event )
  {
    switch( counter_state )
    {
	    case CS_MAN_UP:				// if in manual mode and counting up
	      switch( event )
	      {
	        case BE_SINGLE_PUSH:			// if event is single push
	          counter_value++;			// increment counter value
	          break;
	        case BE_DOUBBLE_PUSH:			// if event is double push
		        counter_state = CS_MAN_DOWN;	// change mode to counting down
	          break;
	        case BE_LONG_PUSH:			// if event is long push
	            counter_state = CS_AUTO_UP;		// change mode to auto
		        counter_timer = TIM_200_MSEC;	// and start the timer
	          break;
	        default:
	          break;
	      }
	      break;
	    case CS_MAN_DOWN:				// if in manual mode and counting down; same as previous but decrement value
	      switch( event )
	      {
	        case BE_SINGLE_PUSH:
	          counter_value--;
	          break;
	        case BE_DOUBBLE_PUSH:
		        counter_state = CS_MAN_UP;
	          break;
	        case BE_LONG_PUSH:
		        counter_timer = TIM_200_MSEC;
		        counter_state = CS_AUTO_DOWN;
	          break;
	        default:
	          break;
	      }
	      break;
	    case CS_AUTO_UP:				// if in auto mode and counting up
	      switch( event )
	      {
	        case TE_TIMEOUT:			// if timer has run out
	          counter_value++;			// increment the counter value
	          counter_timer = TIM_200_MSEC;		// and reset the timer
	          break;
	        default:				// if event is any button press
	          counter_state = CS_MAN_UP;		// change mode back to manual
	          break;
	      }
	      break;
	    case CS_AUTO_DOWN:				// if in auto mode and counting down; same as previous but decrement value
	      switch( event )
	      {
	        case TE_TIMEOUT:
	          counter_value--;
	          counter_timer = TIM_200_MSEC;
	          break;
	        default:
	          counter_state = CS_MAN_UP;
	          break;
	      }
	      break;
	    default:
	      break;
    }
  }
  return( counter_value );
}


/****************************** End Of Module *******************************/












