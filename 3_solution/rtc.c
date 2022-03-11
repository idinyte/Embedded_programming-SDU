/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: rtc.c
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
* 090926  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include "emp_type.h"
#include "tmodel.h"
#include "swtimers.h"
#include "events.h"
#include "messages.h"
#include "tmodel.h"
#include "lcd.h"
#include "sem.h"


/*****************************    Defines    *******************************/
#define RTC_INIT    0
#define RTC_RUNNING 1

#define ARTC_IDLE   0
#define ARTC_ADJUST 1


/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/


/*****************************   Functions   *******************************/


void rtc_task( INT8U task_no )                                      // this task controls the clock
{
  static INT8U rtc_state = RTC_INIT;                                // start in the init state
  INT8U sec, min, hour;

  switch( rtc_state )
  {
    case RTC_INIT:                                                  // if we are in the init state
      start_swtimer( ST_RTC, SEB_TO_RTC, MILLISEC(1000) );          // start a 1s timer
      rtc_state = RTC_RUNNING;                                      // move to the next state (running)
      break;
    case RTC_RUNNING:                                               // if we are in the running state
      if( get_msg_event( SEB_TO_RTC )) // time out                  // if the 1s timer has run out
      {
        sec = get_msg_state( SSM_RTC_SEC );                         // read the current value for seconds
        sec++;                                                      // increment this value
        if( sec >= 60 )                                             // if it is now 60 we do the same for minute counter
        {
          min = get_msg_state( SSM_RTC_MIN );                       // read the current value for minutes
          min++;                                                    // increment this value
          if( min >= 60 )                                           // if it is now 60 we do the same for the hour counter
          {
            hour = get_msg_state( SSM_RTC_HOUR );                   // read the current value for hours
        	hour++;                                                 // increment this value
        	if( hour >= 24 )                                        // if it is now 24
        	  hour = 0;                                             // reset it to 0
            put_msg_state( SSM_RTC_HOUR, hour );                    // send a message with the hour value
        	min = 0;                                                // reset the minute counter
          }
          put_msg_state( SSM_RTC_MIN, min );                        // send a message with the minute value
          sec = 0;                                                  // reset the seconds counter
        }
        put_msg_state( SSM_RTC_SEC, sec );                          // send a message with the seconds value
        start_swtimer( ST_RTC, SEB_TO_RTC, MILLISEC(1000) );        // restart the 1s timer
        signal( SEM_RTC_UPDATED );                                  // signal the display task to update the clock
      }
      break;
  }
}

void display_rtc_task( INT8U task_no )                              // this task displays the clock
{
  INT8U sec;
  INT8U min;
  INT8U hour;
  
  if( wait( SEM_RTC_UPDATED ))                                      // wait for the signal from the rtc_task that the clock has been updated
  {
    if( wait( MUTEX_LCD_DISPLAY ))                                  // wait if the display is already being used
    {
      if( wait( MUTEX_SYSTEM_RTC ))                                 // wait for the system rtc semaphore
      {
        sec  = get_msg_state( SSM_RTC_SEC  );                       // read the values for seconds, minutes and hours
        min  = get_msg_state( SSM_RTC_MIN  );
        hour = get_msg_state( SSM_RTC_HOUR );
        
        move_LCD( 4, 0 );                                           // move the cursor
        wr_ch_LCD( (INT8U)(hour/10+'0') );                          // write the first digit of the hour
        wr_ch_LCD( (INT8U)(hour%10+'0') );                          // write the second digit of the hour
        if( sec & 0x01 )                                            // if the value for seconds ends in a 1 (so every other second)
          wr_ch_LCD( ':' );                                         // display a colon
        else
          wr_ch_LCD( ' ' );                                         // if the value for seconds ends in a 0, write a blank space
        wr_ch_LCD( (INT8U)(min/10+'0') );                           // repeat for minutes and seconds...
        wr_ch_LCD( (INT8U)(min%10+'0') );
        if( sec & 0x01 )
          wr_ch_LCD( ' ' );
        else
          wr_ch_LCD( ':' );
        wr_ch_LCD( (INT8U)(sec/10+'0') );
        wr_ch_LCD( (INT8U)(sec%10+'0') );
      
        signal( MUTEX_SYSTEM_RTC );                                 // signal the to mutexes to say we are not using the display anymore
      }
      signal( MUTEX_LCD_DISPLAY );
    }
  }
}

void ajust_rtc_task( INT8U task_no )
{
  static INT8U state = ARTC_IDLE;
  static INT8U sec;
  static INT8U min;
  static INT8U hour;
  
  switch( state )
  {
    case ARTC_IDLE:
      if( get_msg_event( SEB_BUTTON_EVENT ) == BE_LONG_PUSH )       // if a long push is registered
      {
        if( wait( MUTEX_LCD_DISPLAY ))                              // wait for the display mutex
        {
          if( wait( MUTEX_SYSTEM_RTC ))                             // wait for the rtc mutex
          {
            min = get_msg_state( SSM_RTC_MIN );                     // read the current value for minutes
            move_LCD( 0, 0 );                                       // move the cursor
            wr_ch_LCD( 0xFF );                                      // clear the display
            wr_str_LCD( "Min: ");                                   // write the string "Min: "
            wr_ch_LCD( (INT8U)(min/10+'0') );                       // write the first digit of the minutes
            wr_ch_LCD( (INT8U)(min%10+'0') );                       // write the second digit of the minutes
          }
          signal( MUTEX_SYSTEM_RTC );
        }
        state = ARTC_ADJUST;                                        // move to the next state (adjust)
      }
      break;
    case ARTC_ADJUST:
      switch( get_msg_event( SEB_BUTTON_EVENT ))                    // if a button event is registered
      {
        case BE_SINGLE_PUSH:                                        // if it is a single push
          min++;                                                    // increment the minutes counter
          if( min >= 60 )                                           // if it is 60
            min = 0;                                                // then reset it to 0
          move_LCD( 5, 0 );                                         // move the cursor
          wr_ch_LCD( (INT8U)(min/10+'0') );                         // write the two digits of the minutes counter
          wr_ch_LCD( (INT8U)(min%10+'0') );
          break;
        case BE_LONG_PUSH:                                          // if a long push is registered
          put_msg_state( SSM_RTC_MIN, min );                        // send the chosen minute value as a message
          move_LCD( 0, 0 );                                         // move the cursor back
          wr_ch_LCD( 0xFF );                                        // clear the display
          signal( MUTEX_LCD_DISPLAY );                              // signal to say we are not using the display anymore
          state = ARTC_IDLE;                                        // go back to the idle state
          break;
          
      }
      break;
  }
}

/****************************** End Of Module *******************************/












