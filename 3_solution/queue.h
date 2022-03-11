/*****************************************************************************
* Odense University College of Enginerring
* Embedded C Programming (ECP)
*
* MODULENAME.: queue.h
*
* PROJECT....: ECP
*
* DESCRIPTION:
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
*
*****************************************************************************/

#ifndef _QUEUE_H
  #define _QUEUE_H

/***************************** Include files *******************************/
#include "emp_type.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

INT8S queue_open( INT8U );
INT8U queue_put( INT8U, INT8U );
INT8U queue_get( INT8U );
INT8U queue_test( INT8U );

/****************************** End Of Module *******************************/
#endif
