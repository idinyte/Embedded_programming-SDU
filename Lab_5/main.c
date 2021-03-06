/*******************************************
* MODULENAME.: main.c
********************************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include <stdio.h>
#include <uart0.h>

#define TIM_2_SEC     400
#define TIM_200_MS   40

extern int ticks;

int main(void)
/**********************************
* Function : LED follows SWITCH
**************************************************/
{
int dummy;
int i = 0;
int direction = 1;
unsigned long button_pressed;
int pressed = 1;
int hold_timer = TIM_2_SEC;
int auto_mode = 0;
int auto_timer = TIM_200_MS;
int pause_time = 10000; // arbitrary value for first loop
INT8U baud_rate = 9600;
INT8U databits = 8;
INT8U stopbits = 1;
INT8U parity = 'n';
char name[10] = {'c','o','d','e','\0'};

uart0_init(baud_rate, databits, stopbits, parity );
init_systick();

// Enable the GPIO port that is used for the on-board LEDs and switches.
SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

// Do a dummy read to insert a few cycles after enabling the peripheral.
dummy = SYSCTL_RCGC2_R;

//colors array
unsigned char color[8] = {0x00, 0x08, 0x04, 0x0C, 0x02, 0x0A, 0x06, 0x0E};

// Set the direction as output (PF1 - PF3).
GPIO_PORTF_DIR_R = 0x0E;
// Enable the GPIO pins for digital function (PF1 - PF4)
GPIO_PORTF_DEN_R = 0x1E;

// Enable internal pull-up (PF4).
GPIO_PORTF_PUR_R = 0x10;

PrintResults();
// Loop forever.
while(1)
{
    button_pressed = !(GPIO_PORTF_DATA_R & 0x10);
    while( !ticks );

    // The following will be executed every 5mS
    ticks--;

    if (button_pressed)
    {
        if (pressed)
        {
            i = update_LED_color(color, i, direction);
            auto_mode = 0;
            hold_timer = TIM_2_SEC;
            pressed = 0;

            // change direction on double tap
            if(pause_time < 180) direction *= -1;
            pause_time = 0;
        }

        // checks if button is held for 2 seconds
        if( ! --hold_timer )
        {
          auto_mode = 1;
        }
    }
    else
    {
        pressed = 1;
        pause_time += 5;
    }

    if (auto_mode)
    {
        if( ! --auto_timer )
        {
            auto_timer = TIM_200_MS;
            i = update_LED_color(color, i, direction);
        }
    }


}
return( 0 );
}

int update_LED_color(char color[], int i, int direction)
{
   //changes LED color
   GPIO_PORTF_DATA_R = color[i];
   i += direction;

   //constrains available colors to 8
   if (i > 7) i = 0;
   else if (i < 0) i = 7;

   return i;
}

/****************************** End Of Module*******************************/
