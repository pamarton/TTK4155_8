/*
 * can.h
 *
 * Created: 23.10.2017 09:48:03
 *  Author: jonasgl
 */ 

#ifndef CAN_H_
#define CAN_H_

//------------------------------------------//
//	NODE DEPENDENT 							//
//------------------------------------------//

//IF THIS NODE, DO THIS, else do that


//------------------------------------------//
//	INCLUDES								//
//------------------------------------------//

#include <avr/io.h>
#include "common.h"
#include "MCP2515.h"
#include "MCP2515_driver.h"
#include "SPI.h"
#include <avr/interrupt.h>

//------------------------------------------//
//	DEFINITIONS								//
//------------------------------------------//

#define CANINTE 0x2B

//------------------------------------------//
//	STRUCTS									//
//------------------------------------------//

typedef struct CAN_message_t{
	int id;
	uint8_t length;
	int8_t data[CAN_MESSAGE_LENGTH];
} CAN_message_t;

//------------------------------------------//
//	FUNCTIONS								//
//------------------------------------------//

void CAN_initialize(void);
CAN_message_t* CAN_message_receive(void);
void CAN_send_byte(CAN_message_t* message,uint8_t n);//Sends the data
void CAN_message_send(uint8_t *data, uint8_t TXn);//array of uint8_t as input, sends the massage to the CAN_send_byte
void CAN_construct_message(int id, uint8_t length);//Used to redefine the ID and length of the messages
uint8_t CAN_transmission_complete(uint8_t buffer); //Function that waits for the transmission to be complete
int8_t CAN_reception_complete(void); //Function that checks out which buffer received a message
void CAN_interrupt_setup(void);
uint8_t CAN_read(uint8_t adr);
uint8_t CAN_data_receive(void);
void CAN_print(CAN_message_t message);

//------------------------------------------//
//	INTERRUPTS								//
//------------------------------------------//

ISR(INT4_vect);//Interrupt that fires when a message appears - you got mail!

#endif /* CAN_H_ */