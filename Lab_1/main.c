/*******************************************
* MODULENAME.: main.c
********************************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"

int main(void)
/**********************************
* Function : LED follows SWITCH
**************************************************/
{
int dummy;

// Enable the GPIO port that is used for the on-board LEDs and switches.
SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

// Do a dummy read to insert a few cycles after enabling the peripheral.
dummy = SYSCTL_RCGC2_R;

// Set the direction as output (PF1 - PF3).
GPIO_PORTF_DIR_R = 0x0E;
// Enable the GPIO pins for digital function (PF1 - PF4)
GPIO_PORTF_DEN_R = 0x1E;

// Enable internal pull-up (PF4).
GPIO_PORTF_PUR_R = 0x10;


// Loop forever.
while(1)
{
    if( GPIO_PORTF_DATA_R & 0x10 )
        GPIO_PORTF_DATA_R &= ~(0x02);
    else
        GPIO_PORTF_DATA_R |= 0x02;
}
return( 0 );
}
/****************************** End Of Module*******************************/
