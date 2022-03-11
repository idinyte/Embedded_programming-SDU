

/**
 * main.c
 */

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "systick.h"

#define TIM_1_SEC     200

extern int ticks;

int main(void)
{

    int alive_timer = TIM_1_SEC;

    init_systick();

    int dummy;
    SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;        // enable the GPIO port that is used for the on-board LEDs and switches
    dummy = SYSCTL_RCGC2_R;                     // dummy read to insert a few cycles after enabling the peripheral
    GPIO_PORTF_DIR_R = 0x0E;                    // set the direction as output for LED pins on PortF (PF1 - PF3)
    GPIO_PORTF_DEN_R = 0x1E;                    // enable the GPIO pins for digital function (PF1 - PF4)
    GPIO_PORTF_PUR_R = 0x10;                    // enable internal pull-up resistor for switch (PF4)

    while(1)                                    // loop forever
    {
        while( !ticks );

        // The following will be executed every 5mS
        ticks--;

        if( ! --alive_timer )
        {
          alive_timer        = TIM_1_SEC;
          GPIO_PORTF_DATA_R ^= 0x04;
        }
    }
    return 0;
}
