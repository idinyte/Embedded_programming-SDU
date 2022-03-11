/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: tmodel.h
*
* PROJECT....: ECP
*
* DESCRIPTION: Defines the elemtn of the task model..
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 101004  MoH   Module created.
*
*****************************************************************************/

#ifndef _TMODEL_H_
#define _TMODEL_H_

// Tasks.
// ------
#define TASK_SW_TIMERS 11
#define TASK_MAIN 12
#define TASK_BUTTON 13
#define TASK_TRAFFIC_LIGHT 14
#define TASK_NORWEGIAN_NIGHT 15
#define TASK_EMERGENCY 16

// Interrupt Service Routines.
// ---------------------------
#define ISR_TIMER 21

// Shared State Memory.
// --------------------
#define SSM_TRAFFIC_LIGHT_MODE 31

// Shared Event Buffers.
// ---------------------
#define SEB_BUTTON_EVENT 41
#define SEB_TO_BUTTON 42 // Time Out
#define SEB_TO_TRAFFIC_LIGHT 43 // Time Out
#define SEB_TO_NORWEGIAN_NIGHT 44 // Time Out

// Traffic Light Modes.
// --------------------
#define MM_TLIGHT   1
#define MM_REDLIGHT 2
#define MM_FLASH    3

// Software Timers.
// ----------------
#define ST_BUTTON   1
#define ST_FLASH    2
#define ST_TLIGHT   3

#endif /* _TMODEL_H_ */
