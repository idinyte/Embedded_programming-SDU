/*****************************************************************************
* Odense University College of Enginerring
* Embedded C Programming (ECP)
*
* MODULENAME.: queue.c
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
* 090928  MoH   Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/

#include "emp_type.h"
#include "glob_def.h"
#include "queue.h"

/*****************************    Defines    *******************************/
#define QUEUE_SIZE   128
#define NOF_QUEUES     8

typedef struct 
{
	INT8U	head;
	INT8U	tail;
	INT8U	len;
	INT8U buf[QUEUE_SIZE];
} queue_descriptor;

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
queue_descriptor queue_pool[NOF_QUEUES];

/*****************************   Functions   *******************************/


INT8S queue_open( id )
INT8U id;
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  INT8S result;
  
	if( id < NOF_QUEUES )
	{
	  queue_pool[id].head = 0;
    queue_pool[id].tail = 0;
    queue_pool[id].len  = 0;
    result = id;
	}
	else
	  result = -1;
	return( result );
}

INT8U queue_put( id, ch )
INT8U id;
INT8U ch;
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  INT8U result = FALSE;
  
  if( id < NOF_QUEUES )
  {
    if( queue_pool[id].len < QUEUE_SIZE )
    {
      queue_pool[id].buf[queue_pool[id].head++] = ch;
      queue_pool[id].head &= 0x7F;
      queue_pool[id].len++;
      result = TRUE;
    }
  }
  return( result );
}

INT8U queue_get( id )
INT8U id;
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  INT8U Ch = '\0';
  
  if( id < NOF_QUEUES )
  {
    if( queue_pool[id].len )
    {
      Ch = queue_pool[id].buf[queue_pool[id].tail++];
      queue_pool[id].tail &= 0x7F;
      queue_pool[id].len--;
    }
  }
  return( Ch );
}

INT8U queue_test( id )
INT8U id;
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  INT8U result = 0;
  
  if( id < NOF_QUEUES )
  {
    result = queue_pool[id].len;
  }
  return( result );
}



/****************************** End Of Module *******************************/












