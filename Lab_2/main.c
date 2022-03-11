/*******************************************
* MODULENAME.: main.c
********************************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include <stdio.h>

#define TIM_1_SEC     200
#define TIM_500_MS     100

extern int ticks;

int main(void)
{
    // A)
    unsigned short var1 = 0xFFFF;
    var1 &= 0xFF9F; // clear bit 5 and 6

    // B)
    unsigned short var2 = 0xFE3F;
    var2 &= ~(0x0420); // clear bit 5 and 10
    var2 |= 0x3C0; // fill bits 6-9

    // C)

    unsigned short varC = 0x67;
    int first_press = 1;
    unsigned long button_pressed;
    int i = 0;

    // D)
    init_systick();
    int display_every_second = 1; // change this value to 0 to test "C)" part
    int timer = TIM_1_SEC;
    int half_timer = TIM_500_MS;


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
        while( !ticks );

        // The following will be executed every 5mS
        ticks--;

        if(! --half_timer && display_every_second)
        {
            half_timer = TIM_500_MS;
            if(i != 8) GPIO_PORTF_DATA_R &= ~(0x44C); // clear color every half a second
        }
        if(! --timer)
        {
            timer = TIM_1_SEC;
            if(display_every_second)
            {
                if( (varC >> i) & 0x01 ) GPIO_PORTF_DATA_R |= 0x08; // bit = 1, green led
                else GPIO_PORTF_DATA_R |= 0x04; // bit = 0, blue led

                i = recycle(i);
            }
        }

        if( !(GPIO_PORTF_DATA_R & 0x10) && !display_every_second)
        {
            if(first_press)
            {
                first_press = 0;
                GPIO_PORTF_DATA_R &= ~(0x44C); // clear color
                if( (varC >> i) & 0x01 ) GPIO_PORTF_DATA_R |= 0x08; // bit = 1, green led
                else GPIO_PORTF_DATA_R |= 0x04; // bit = 0, blue led

                i = recycle(i);
            }

        }
        else
        {
            first_press = 1;
        }

    }
	return 0;
}

int recycle(int i)
{
    if( i == 8 )
    {
        GPIO_PORTF_DATA_R &= ~(0x44C); // clear color
        GPIO_PORTF_DATA_R |= 0x02; // end of 8 bits, red led
        i = -1;
    }
    else GPIO_PORTF_DATA_R &= ~(0x02);
    i++;

   return i;
}
