/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: lcd.c
*
* PROJECT....: EMP
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 220304  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "swtimers.h"
#include "events.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/
#define INITIALIZE   0
#define TURN_ON 1
#define SET_MODE 2
#define WRITE 3
/*****************************   Variables   *******************************/
/*****************************   Functions   *******************************/



int lcd(INT8U action)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : The super loop.
******************************************************************************/
{
    static INT8U bus_timer = TIM_100_MSEC;
    static INT8U state = INITIALIZE;
    static INT8U traffic = 0;
    INT8U bus_timeout = 0;
    static INT8U initialize = 1;
    static INT8U pause = 0;
    if (bus_timer)
    {
        if (! --bus_timer)
        {
            bus_timeout = TE_TIMEOUT;
        }
    }


    /*switch( state )
    {
    case INITIALIZE:
        if(bus_timeout == TE_TIMEOUT)
        {
            if(traffic == 0)
            {
                // Sets LCD display mode to 4 bit
                GPIO_PORTC_DATA_R = 0x20;
                traffic = 1;
                bus_timer = TIM_40_MSEC;
            }
            else if(traffic == 1)
            {
                GPIO_PORTC_DATA_R = 0x20;
                traffic = 2;
                bus_timer = TIM_40_MSEC;
            }
            else
            {
                // Sets number of display lines and font
                GPIO_PORTC_DATA_R = 0x0;
                traffic = 0;
                state = TURN_ON;
                bus_timer = TIM_40_MSEC;
            }
        break;
    case TURN_ON: // turns on display
        if (bus_timeout == TE_TIMEOUT)
        {
            if(traffic == 0)
            {
                GPIO_PORTC_DATA_R = 0x00;
                traffic = 1;
                bus_timer = TIM_40_MSEC;
            }
            else
            {
                GPIO_PORTC_DATA_R = 0xE0;
                traffic = 0;
                state = SET_MODE;
                bus_timer = TIM_40_MSEC;
            }
        }
        break;
        /* Sets mode to increment the address by one and to shift the cursor to the
         * right at the time of write to the DD/CGRAM. Display is not shifted.*/
    /*case SET_MODE:
        if (bus_timeout == TE_TIMEOUT)
        {
            if(traffic == 0)
            {
                GPIO_PORTC_DATA_R = 0x00;
                traffic = 1;
                bus_timer = TIM_40_MSEC;
            }
            else
            {
                GPIO_PORTC_DATA_R = 0x60;
                traffic = 0;
                state = WRITE;
                bus_timer = TIM_40_MSEC;
            }
        }
        break;
    case WRITE: // writes H
        if (bus_timeout == TE_TIMEOUT)
        {
            if (traffic == 0)
            {
                GPIO_PORTD_DATA_R |= 0x04;
                GPIO_PORTC_DATA_R = 0x40;
                traffic = 1;
                bus_timer = TIM_40_MSEC;
            }
            else
            {
                GPIO_PORTD_DATA_R |= 0x04;
                GPIO_PORTC_DATA_R = 0x80;
                traffic = 0;
                state = WRITE;
                bus_timer = TIM_40_MSEC;
            }
        }
        break;
    }
    }*/
    if (initialize)
    {
        if (bus_timeout == TE_TIMEOUT)
        {
            if (pause)
            {
                GPIO_PORTD_DATA_R &= ~(0x08);
                bus_timer = TIM_40_MSEC;
                pause = 0;
            }
            else
            {
                if (traffic == 0)
                {
                    GPIO_PORTC_DATA_R = 0x30;
                    GPIO_PORTD_DATA_R = 0x08;
                    traffic = 1;
                    pause = 1;
                    bus_timer = TIM_40_MSEC;
                }
                else if (traffic == 1)
                {
                    GPIO_PORTC_DATA_R = 0x30;
                    GPIO_PORTD_DATA_R = 0x08;
                    traffic = 2;
                    pause = 1;
                    bus_timer = TIM_40_MSEC;
                }
                else if (traffic == 2)
                {
                    GPIO_PORTC_DATA_R = 0x30;
                    GPIO_PORTD_DATA_R = 0x08;
                    traffic = 3;
                    pause = 1;
                    bus_timer = TIM_40_MSEC;
                }
                else if (traffic == 3)
                {
                    GPIO_PORTC_DATA_R = 0x20;
                    GPIO_PORTD_DATA_R = 0x08;
                    traffic = 4;
                    pause = 1;
                    bus_timer = TIM_40_MSEC;
                }
                else if (traffic == 4)
                {
                    GPIO_PORTC_DATA_R = 0x20;
                    GPIO_PORTD_DATA_R = 0x08;
                    traffic = 5;
                    pause = 1;
                    bus_timer = TIM_40_MSEC;
                }
                else if (traffic == 5)
                {
                    GPIO_PORTC_DATA_R = 0x00;
                    GPIO_PORTD_DATA_R = 0x08;
                    traffic = 6;
                    pause = 1;
                    bus_timer = TIM_40_MSEC;
                }
                else if (traffic == 6)
                {
                    GPIO_PORTC_DATA_R = 0x00;
                    GPIO_PORTD_DATA_R = 0x08;
                    traffic = 7;
                    pause = 1;
                    bus_timer = TIM_40_MSEC;
                }
                else if (traffic == 6)
                {
                    GPIO_PORTC_DATA_R = 0x00;
                    GPIO_PORTD_DATA_R = 0x08;
                    traffic = 7;
                    pause = 1;
                    bus_timer = TIM_40_MSEC;
                }
                else if (traffic == 7)
                {
                    GPIO_PORTC_DATA_R = 0x80;
                    GPIO_PORTD_DATA_R = 0x08;
                    traffic = 8;
                    pause = 1;
                    bus_timer = TIM_40_MSEC;
                }
                else if (traffic == 8)
                {
                    GPIO_PORTC_DATA_R = 0x00;
                    GPIO_PORTD_DATA_R = 0x08;
                    traffic = 9;
                    pause = 1;
                    bus_timer = TIM_40_MSEC;
                }
                else if (traffic == 9)
                {
                    GPIO_PORTC_DATA_R = 0x10;
                    GPIO_PORTD_DATA_R = 0x08;
                    traffic = 10;
                    pause = 1;
                    bus_timer = TIM_40_MSEC;
                }
                else if (traffic == 10)
                {
                    GPIO_PORTC_DATA_R = 0x00;
                    GPIO_PORTD_DATA_R = 0x08;
                    traffic = 11;
                    pause = 1;
                    bus_timer = TIM_40_MSEC;
                }
                else if (traffic == 11)
                {
                    GPIO_PORTC_DATA_R = 0x40;
                    GPIO_PORTD_DATA_R = 0x08;
                    traffic = 12;
                    pause = 1;
                    bus_timer = TIM_40_MSEC;
                    initialize = 0;
                }
            }
        }
    }

  return( 0 );
}

/****************************** End Of Module *******************************/
