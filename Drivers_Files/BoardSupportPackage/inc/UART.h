/*
 * UART.h
 *
 *  Created on: Mar 1, 2020
 *      Author: Khaled
 */

#ifndef BOARDSUPPORTPACKAGE_INC_UART_H_
#define BOARDSUPPORTPACKAGE_INC_UART_H_



#include <driverlib.h>
#include "msp.h"
#include <stdio.h>
static inline void  uartTransmitString(char *s);
void uartInit();
#endif /* BOARDSUPPORTPACKAGE_INC_UART_H_ */
