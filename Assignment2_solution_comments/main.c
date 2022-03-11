/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: main.c
*
* PROJECT....: EMP
*
* DESCRIPTION: Assignment 2, main module. No main.h file.
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150215  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "swtimers.h"
#include "systick.h"
#include "gpio.h"
#include "events.h"
#include "tmodel.h"
#include "messages.h"
#include "devices.h"
#include "button.h"
#include "leds.h"

/*****************************    Defines    *******************************/
// TRAFFIC LIGHT STATES
#define TL_INIT         0
#define TL_RED          1
#define TL_RED_YELLOW   2
#define TL_GREEN        3
#define TL_YELLOW       4

// FLASH STATES
#define FLASH_INIT      0
#define FLASH_ON        1
#define FLASH_OFF       2

// MAIN STATES
#define MAIN_INIT       0
#define MAIN_RUN        1
/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
extern volatile INT16S ticks;
INT16S alive_timer = MILLISEC(500);

/*****************************   Functions   *******************************/

void tl_task( INT8U task_no )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : normal traffic light mode (runs all the time but only sets LEDs when this state is active)
******************************************************************************/
{
  static INT8U tl_state = TL_INIT;

  switch( tl_state )
  {
    case TL_INIT:
      start_swtimer( ST_TLIGHT, SEB_TO_TRAFFIC_LIGHT, MILLISEC(100) );      // start a 100ms timer and go to next state (red)
      tl_state = TL_RED;
      break;
    case TL_RED:
      if( get_msg_event( SEB_TO_TRAFFIC_LIGHT )) // time out                // if there was a timer timeout (the 100ms have elapsed)
      {
        if( get_msg_state( SSM_TRAFFIC_LIGHT_MODE ) == MM_TLIGHT )          // if we are in normal traffic mode
          set_leds( TURN_LED_ON, TURN_LED_OFF, TURN_LED_OFF );              // turn on only red LED
        start_swtimer( ST_TLIGHT, SEB_TO_TRAFFIC_LIGHT, MILLISEC(5000) );   // start a 5s timer and go to next state (red+yellow)
        tl_state = TL_RED_YELLOW;
      }
      break;
    case TL_RED_YELLOW:
      if( get_msg_event( SEB_TO_TRAFFIC_LIGHT )) // time out                // when the 5s timer runs out
      {
        if( get_msg_state( SSM_TRAFFIC_LIGHT_MODE ) == MM_TLIGHT )          // if we are in normal traffic mode
       	  set_leds( TURN_LED_ON, TURN_LED_ON, TURN_LED_OFF );               // turn on red and yellow LEDs
        start_swtimer( ST_TLIGHT, SEB_TO_TRAFFIC_LIGHT, MILLISEC( 2000 ));  // start a 2s timer and go to next state (green)
        tl_state = TL_GREEN;
      }
      break;
    case TL_GREEN:
      if( get_msg_event( SEB_TO_TRAFFIC_LIGHT )) // time out                // if the 2s timer has run out
      {
        if( get_msg_state( SSM_TRAFFIC_LIGHT_MODE ) == MM_TLIGHT )          // if we are in normal traffic mode
       	  set_leds( TURN_LED_OFF, TURN_LED_OFF, TURN_LED_ON );              // turn on only the green LED
        start_swtimer( ST_TLIGHT, SEB_TO_TRAFFIC_LIGHT, MILLISEC( 5000 ));  // set a 5s timer and go to next state (yellow)
        tl_state = TL_YELLOW;
      }
      break;
    case TL_YELLOW:
      if( get_msg_event( SEB_TO_TRAFFIC_LIGHT )) // time out                // if the 5s timer has run out
      {
        if( get_msg_state( SSM_TRAFFIC_LIGHT_MODE ) == MM_TLIGHT )          // if we are in normal traffic mode
          set_leds( TURN_LED_OFF, TURN_LED_ON, TURN_LED_OFF );              // turn on only the yellow LED
        start_swtimer( ST_TLIGHT, SEB_TO_TRAFFIC_LIGHT, MILLISEC( 2000 ));  // set a 2s timer and go to state (red)
        tl_state = TL_RED;
      }
      break;
    default:
      tl_state = TL_RED;
  }
}

void flash_task( INT8U task_no )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Norwegian Night (flash) mode
******************************************************************************/
{
  static INT8U flash_state = FLASH_INIT;
  INT8U led_action;

  switch( flash_state )
  {
    case FLASH_INIT:
      led_action = TURN_LED_OFF;                                                // set LED action to OFF
      start_swtimer( ST_FLASH, SEB_TO_NORWEGIAN_NIGHT, MILLISEC( 500 ));        // start 500ms timer
      flash_state = FLASH_ON;                                                   // go to next state (flash on)
      break;
    case FLASH_ON:
      if( get_msg_event( SEB_TO_NORWEGIAN_NIGHT )) // time out                  // if the 500ms timer has run out
      {
        led_action = TURN_LED_ON;                                               // set LED action to ON
        start_swtimer( ST_FLASH, SEB_TO_NORWEGIAN_NIGHT, MILLISEC( 500 ));      // restart the 500ms timer
        flash_state = FLASH_OFF;                                                // go to next state (flash off)
      }
      break;
    case FLASH_OFF:
      if( get_msg_event( SEB_TO_NORWEGIAN_NIGHT )) // time out                  // if the timer has run out
      {
        led_action = TURN_LED_OFF;                                              // set LED action to OFF
        start_swtimer( ST_FLASH, SEB_TO_NORWEGIAN_NIGHT, MILLISEC( 500 ));      // restart the timer
        flash_state = FLASH_ON;                                                 // go back to state (flash on)
      }
      break;
  }
  if( get_msg_state( SSM_TRAFFIC_LIGHT_MODE ) == MM_FLASH )                     // if we are in Norwegian Nights mode (flash mode)
    set_leds( TURN_LED_OFF, led_action, TURN_LED_OFF );                         // set the yellow LED according to the LED action value
}

void red_task( INT8U task_no )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Red light mode
******************************************************************************/
{
  if( get_msg_state( SSM_TRAFFIC_LIGHT_MODE ) == MM_REDLIGHT )                  // if we are in red light mode
    set_leds( TURN_LED_ON, TURN_LED_OFF, TURN_LED_OFF );                        // turn on only red LED
}


void main_task( INT8U task_no )
{
  static INT8U main_task_state = MAIN_INIT;
  INT8U event;

  switch( main_task_state )
  {
  case MAIN_INIT:
    put_msg_state( SSM_TRAFFIC_LIGHT_MODE, MM_TLIGHT );         // set the mode to normal traffic light
    main_task_state = MAIN_RUN;                                 // go to next state (run)
    break;
  case MAIN_RUN:
    event = get_msg_event( SEB_BUTTON_EVENT );                  // read the event buffer for the button
    switch( event )
    {
      case BE_SINGLE_PUSH:                                      // if the event is a single push
        put_msg_state( SSM_TRAFFIC_LIGHT_MODE, MM_FLASH );      // send message to put us in Norwegian mode
        break;
      case BE_DOUBBLE_PUSH:                                     // if the event is a double push
        put_msg_state( SSM_TRAFFIC_LIGHT_MODE, MM_REDLIGHT );   // send message to put us in red light mode
        break;
      case BE_LONG_PUSH:                                        // if the event is a long push
        put_msg_state( SSM_TRAFFIC_LIGHT_MODE, MM_TLIGHT );     // send message to put us in normal traffic light mode
        break;
    }
  }
}


int main(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : The super loop.
******************************************************************************/
{
  init_systick();
  init_gpio();

  // Loop forever.
  while(1)
  {
	// System part of the super loop.
	// ------------------------------
	while( !ticks );


	// The following will be executed every 5ms
	ticks--;

	if( ! --alive_timer )
	{
	  alive_timer =	MILLISEC( 500 );
	  GPIO_PORTD_DATA_R ^= 0x40;
	}

    // Protected operating system mode
    swt_ctrl();                                 // task controlling the timers

    // Application mode
    button_task( TASK_BUTTON );
    main_task( TASK_MAIN );
    tl_task( TASK_TRAFFIC_LIGHT );
    flash_task( TASK_NORWEGIAN_NIGHT );
    red_task( TASK_EMERGENCY );

  }
}

/****************************** End Of Module *******************************/
