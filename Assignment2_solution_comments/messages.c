/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: swtimers.c
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
* 080219  MoH    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include "emp_type.h"
/*****************************    Defines    *******************************/
#define MAX_MSG 64

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

INT8U   msg_event[MAX_MSG];                 // buffer of events
INT8U   msg_state[MAX_MSG];                 // buffer of states

                                            // events are sent from button to main task
                                            //             and from swtimers in case of a timer timeout

                                            // states are set from the main task and read by the 3 light mode tasks

/*****************************   Functions   *******************************/

INT8U get_msg_event( no )
INT8U no;
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{                                       // get the event given the number
  INT8U result = 0;

  if( no < MAX_MSG )                    // if the number is less than the maximum number of events
  {
    if( msg_event[no] )                 // and if the event exists
	  {
	    result = msg_event[no];         // read the event
	    msg_event[no] = 0;              // and reset the event to 0
	  }
  }
  return( result );
}


void put_msg_event( no, event )
INT8U  no;
INT8U  event;
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  if( no < MAX_MSG )
    msg_event[no] = event;              // add event to the message with the given number (no)
}


INT8U get_msg_state( no )
INT8U no;
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{                                       // get the state given the number
  INT8U result = 0;

  if( no < MAX_MSG )                    // if the number is within the maximum number of messages
  {
    result = msg_state[no];             // read the state
  }
  return( result );                     // return the state
}


void put_msg_state( no, state )
INT8U  no;
INT8U  state;
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  if( no < MAX_MSG )
    msg_state[no] = state;              // add state to the message with the given number (no)
}

