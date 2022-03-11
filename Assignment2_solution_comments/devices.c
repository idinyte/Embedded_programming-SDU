/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: ecp.c
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
* 090222  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "devices.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

BOOLEAN turn_led( name, action )
INT8U name;
INT8U action;
/*****************************************************************************
*   Input    :
*   Output   :
*   Function :
******************************************************************************/
{
  BOOLEAN Result;

  switch( name )
  {
    case LED_GREEN:
	  switch( action )
	  {
	    case TURN_LED_ON:
	      GPIO_PORTF_DATA_R &= 0xF7;
	      break;
	    case TURN_LED_OFF:
	      GPIO_PORTF_DATA_R |= 0x08;
    	  break;
	    case TOGGLE_LED:
	      GPIO_PORTF_DATA_R ^= 0x08;
	      break;
	  }
	  Result = !(GPIO_PORTF_DATA_R & 0x02 );
	  break;
	case LED_YELLOW:
	  switch( action )
	  {
	    case TURN_LED_ON:
	      GPIO_PORTF_DATA_R &= 0xFB;
	      break;
	    case TURN_LED_OFF:
    	  GPIO_PORTF_DATA_R |= 0x04;
    	  break;
	    case TOGGLE_LED:
	      GPIO_PORTF_DATA_R ^= 0x04;
	      break;
	  }
	  Result = !(GPIO_PORTF_DATA_R & 0x01 );
	  break;
	case LED_RED:
	  switch( action )
	  {
	    case TURN_LED_ON:
	      GPIO_PORTF_DATA_R &= 0xFD;
	      break;
	    case TURN_LED_OFF:
    	  GPIO_PORTF_DATA_R |= 0x02;
    	  break;
	    case TOGGLE_LED:
	      GPIO_PORTF_DATA_R ^= 0x02;
	      break;
	  }
	  Result = !(GPIO_PORTF_DATA_R & 0x40 );
	  break;
	case LED_STATUS:
	  switch( action )
	  {
	    case TURN_LED_ON:
	      GPIO_PORTD_DATA_R &= 0xCF;
	      break;
	    case TURN_LED_OFF:
    	  GPIO_PORTD_DATA_R |= 0x40;
    	  break;
	    case TOGGLE_LED:
	      GPIO_PORTD_DATA_R ^= 0x40;
	      break;
	  }
	  Result = !(GPIO_PORTD_DATA_R & 0x01 );
	  break;
  }
  return( Result );
}	

/****************************** End Of Module *******************************/











