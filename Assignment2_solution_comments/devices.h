/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: ecp.h
*
* PROJECT....: ECP
*
* DESCRIPTION: Test.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
*
*****************************************************************************/

#ifndef DEVICES_H_
#define DEVICES_H_

/***************************** Include files *******************************/
#include "emp_type.h"
/*****************************    Defines    *******************************/
// Device Types
// ------------
//
// LED devices
// -----------
//
#define LED_STATUS 	11
#define LED_RED		21
#define LED_YELLOW	22
#define LED_GREEN	23
//
//
// Device actions
// --------------
//
// LED acions
// ----------
//
#define TURN_LED_ON		1
#define TURN_LED_OFF	2
#define TOGGLE_LED		3

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

BOOLEAN turn_led( INT8U, INT8U );
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Test function
******************************************************************************/


/****************************** End Of Module *******************************/
#endif /*DEVICES_H_*/
