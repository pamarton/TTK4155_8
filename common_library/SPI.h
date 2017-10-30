/*
 * SPI.h
 *
 * Created: 23.10.2017 09:49:09
 *  Author: jonasgl
 */ 

#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include "common.h"


//------------------------------------------//
//	INCLUDES								//
//------------------------------------------//


#include "uart.h" //REMOVE AFTER USE
#include "i_o.h"
#include "MCP2515.h"

//------------------------------------------//
//	PIN DEFINITIONS							//
//------------------------------------------//

#if NODE == 1
	#define		SPI_SS			PB4 // compare physical connection to I/O-board
	#define		SPI_MOSI		PB5
	#define		SPI_MISO		PB6
	#define		SPI_SCK			PB7
#elif NODE == 2
	#define		SPI_SS			PB7 // compare physical connection to I/O-board
	#define		SPI_MOSI		PB2
	#define		SPI_MISO		PB3
	#define		SPI_SCK			PB1
	#define		SPI_SSInit		PB0
#endif

//------------------------------------------//
//	FUNCTIONS								//
//------------------------------------------//

void SPI_initialize(void);
void SPI_send(uint8_t data);
uint8_t SPI_receive(void);
void SPI_select(void);
void SPI_deselect(void);
void SPI_test(void);

#endif /* SPI_H_ */