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
#define NORMAL    5
#define NORWEGIAN  6
#define EMERGENCY   7
#define GREEN   8
#define YELLOW   9
#define RED   10
#define PINK   11
#define NONE   12

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

static INT8U current_color = PINK;
static INT8U state = NORMAL;


INT8U event_manager( INT8U event )
/*****************************************************************************
*   Input    : event from button press
*   Output   : counter value to set LED color
*   Function : controls counter and switches between manual and auto mode
******************************************************************************/
{

    static INT8U counter_value = 0;
    static INT16U counter_timer = 1;

    if (event)
    {
        switch (event)
        {
        case BE_SINGLE_PUSH:
            state = NORWEGIAN;
            counter_timer = 1;
            current_color = YELLOW;
            break;
        case BE_DOUBBLE_PUSH:
            state = EMERGENCY;
            counter_timer = 1;
            current_color = RED;
            break;
        case BE_LONG_PUSH:
            state = NORMAL;
            counter_timer = 1;
            current_color = PINK;
            break;
        default:
            break;
        }

    }
    switch (state)
    {
    case NORMAL:
        counter_timer = normal(counter_timer);
        break;
    case NORWEGIAN:
        counter_timer = norwegian(counter_timer);
        break;
    }
    return (current_color);
}

int normal(INT16U counter_timer)
{

    INT8U event;

    if (counter_timer)                  // if timer is running
        if (!--counter_timer)       // decrement timer and check if now zero
            event = TE_TIMEOUT;             // then set event to timeout

    if (event)
    {
        switch (current_color)
        {
        case GREEN:
            current_color = YELLOW;
            counter_timer = TIM_500_MSEC;
            break;
        case YELLOW:
            current_color = RED;
            counter_timer = TIM_2_SEC;
            break;
        case RED:
            current_color = PINK;
            counter_timer = TIM_500_MSEC;
            break;
        case PINK:
            current_color = GREEN;
            counter_timer = TIM_2_SEC;
            break;
        }
    }
    return counter_timer;
}

int norwegian(INT16U counter_timer)
{

    INT8U event;

    if (counter_timer)                  // if timer is running
        if (!--counter_timer)       // decrement timer and check if now zero
            event = TE_TIMEOUT;             // then set event to timeout

    if (event)
    {
        switch (current_color)
        {
        case YELLOW:
            current_color = NONE;
            counter_timer = TIM_1_SEC;
            break;
        case NONE:
            current_color = YELLOW;
            counter_timer = TIM_1_SEC;
            break;
        }
    }
    return counter_timer;
}

/****************************** End Of Module *******************************/












