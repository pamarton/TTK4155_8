/*
 * uart.h
 *
 * Created: 22.10.2017 12:09:24
 *  Author: jonasgl
 */

#ifndef UART_H_
#define UART_H_

//------------------------------------------//
//	INCLUDES								//
//------------------------------------------//

//#include "new_printf.h"
#include <avr/io.h>
#include <stdio.h>
#include "common.h"

//------------------------------------------//
//	DEFINITIONS								//
//------------------------------------------//

// Clock Speed
#if NODE == 1
	#define FOSC 4915200
	#define BAUDRATE 9600 // Valgt verdi data sendt pr sekund
	#define UBRR 31 //F_CPU (called FOSC here)/(16*BAUDRATE)-1
#elif NODE == 2
	#define FOSC 16000000
	#define BAUDRATE 9600 // Valgt verdi data sendt pr sekund
	#define UBRR 103 //F_CPU (called FOSC here)/(16*BAUDRATE)-1
#endif



//------------------------------------------//
//	FUNCTIONS								//
//------------------------------------------//

void send_UART(char letter);
void init_UART(void);
unsigned int recieve_UART(void);
void testUart(void);

#endif /* UART_H_ */