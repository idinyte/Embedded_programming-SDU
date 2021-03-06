/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: uart.h
*
* PROJECT....: EMP
*
* DESCRIPTION: Test.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 150228  MoH   Module created.
*
*****************************************************************************/

#ifndef _UART_H
  #define _UART_H

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

extern BOOLEAN uart0_rx_rdy();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Character ready at uart0 RX
******************************************************************************/

extern INT8U uart0_getc();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Get character from uart0 RX
******************************************************************************/

extern BOOLEAN uart0_tx_rdy();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : uart0 TX buffer ready
******************************************************************************/

extern void uart0_putc( INT8U );
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Put character to uart0 TX
******************************************************************************/

extern void uart0_init( INT32U, INT8U, INT8U, INT8U );
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Initialize uart 0
******************************************************************************/


//------------UART_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
char UART_InChar(void);

//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART_OutChar(char data);

//------------UART_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART_OutString(char *pt);

void UART_newline(void);
int stdout_putchar(int ch);
int stdin_getchar(void);
int stderr_putchar(int ch);
int PrintResults(void);
/****************************** End Of Module *******************************/
#endif

