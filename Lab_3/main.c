/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: main.c
*
* PROJECT....: EMP
*
* DESCRIPTION: Lab 3, main module. No main.h file.
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
#include "led.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
extern INT16S ticks;
/*****************************   Functions   *******************************/


int main(void)
{
    int dummy;
        SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF; // 1) activate clock for Port F
        dummy = SYSCTL_RCGC2_R;              // allow time for clock to start

        GPIO_PORTF_LOCK_R = 0x4C4F434B;      // 2) unlock GPIO Port F
        GPIO_PORTF_CR_R = 0x1F;              // allow changes to PF4-0

        GPIO_PORTF_DIR_R = 0x0E;
        GPIO_PORTF_DEN_R = 0x1F;
        GPIO_PORTF_PUR_R = 0x11;

        INT8U event;
        INT8U state;

        while(1)
        {
            event = select_button();
            state = event_manager(event);
            leds(state);
        }
        return 0;
}
