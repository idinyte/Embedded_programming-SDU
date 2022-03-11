/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: leds.c
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
* 090215  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "emp_type.h"
#include "devices.h"
#include "gpio.h"

void set_leds( red, yellow, green )
BOOLEAN red, yellow, green;
{
  turn_led( LED_RED,    red    );
  turn_led( LED_YELLOW, yellow );
  turn_led( LED_GREEN,  green  );
}
