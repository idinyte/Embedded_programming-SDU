/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: tryk.c
*
* PROJECT....: ECP
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
#include "button.h"
#include "swtimers.h"
#include "tmodel.h"
#include "messages.h"
/*****************************    Defines    *******************************/
#define BS_IDLE           0
#define BS_FIRST_PUSH     1
#define BS_FIRST_RELEASE  2
#define BS_SECOND_PUSH    3
#define BS_LONG_PUSH      4

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

INT8U    dummy1;
INT16S   dummy2;

/*****************************   Functions   *******************************/
INT8U button_pushed()
{
  return( !(GPIO_PORTF_DATA_R & 0x10) );
}

void button_task( INT8U task_no )
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
  static INT8U  button_state = BS_IDLE;
         INT8U  time_out;

  time_out = get_msg_event( SEB_TO_BUTTON );

  switch( button_state )
  {
    case BS_IDLE:
	    if( button_pushed( ))		// if button pushed
	    {
        button_state = BS_FIRST_PUSH;
	      start_swtimer( ST_BUTTON, SEB_TO_BUTTON, MILLISEC(2000) );
      }
	    break;
    case BS_FIRST_PUSH:
	    if( time_out )			// if timeout
	    {
	      button_state = BS_LONG_PUSH;
	      put_msg_event( SEB_BUTTON_EVENT, BE_LONG_PUSH );
	    }
	    else
	    {
        if(  !button_pushed( ) )	// if button released
		    {
	        button_state = BS_FIRST_RELEASE;
	        start_swtimer( ST_BUTTON, SEB_TO_BUTTON, MILLISEC(100) );
        }
	    }
	    break;
    case BS_FIRST_RELEASE:
	    if( time_out )			// if timeout
	    {
	      button_state = BS_IDLE;
        put_msg_event( SEB_BUTTON_EVENT, BE_SINGLE_PUSH );
	    }
	    else
	    {
        if(  button_pushed(  ))		// if button pressed
		    {
	        button_state = BS_SECOND_PUSH;
          start_swtimer( ST_BUTTON, SEB_TO_BUTTON, MILLISEC( 2000 ));
        }
	    }
	    break;
    case BS_SECOND_PUSH:
	    if( time_out )			// if timeout
	    {
	      button_state = BS_LONG_PUSH;
        put_msg_event( SEB_BUTTON_EVENT, BE_LONG_PUSH );
      }
	    else
	    {
        if( ! button_pushed( ) )					// if button released
		    {
	        button_state = BS_IDLE;
	        put_msg_event( SEB_BUTTON_EVENT, BE_DOUBBLE_PUSH );
        }
	    }
	    break;
    case BS_LONG_PUSH:
      if( ! button_pushed(  ) )					// if button released
	      button_state = BS_IDLE;
	    break;
    default:
      break;
  }
}

/****************************** End Of Module *******************************/












