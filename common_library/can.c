/*
* can.c
*
* Created: 16.10.2017 10:46:30
*  Author: pamarton
*/

#include "can.h"

//#include <util/delay.h>

static CAN_message_t CAN_receive_buffer; 
static CAN_message_t CAN_send_buffer;
uint8_t receive_flag = 0;

void CAN_initialize(void){

	MCP2515_initialize();

	// Initialize empty message for transmission
	CAN_construct_message(CAN_ID,CAN_MESSAGE_LENGTH);
	
	// Turn mask/filters off; receive any message AND Enable Rollover
	MCP2515_bit_modify(MCP_RXB0CTRL,0b01100100,0xFF);
	MCP2515_bit_modify(MCP_RXB1CTRL,0b01100100,0xFF);
	
	// RX0IE Receive Buffer 0 FUll Interrupt Enable bit
	MCP2515_bit_modify(MCP_CANINTE,0x01,1);
	
	//set CAN mode
	MCP2515_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL); 
	
	// Set up interrupts.
	CAN_interrupt_setup();
	
	#if UART_ENABLE
		printf("MCP_CANSTAT: %i\n", MCP2515_read(MCP_CANSTAT));//comment out later
		printf("CAN initialized.\n");
	#endif
}

CAN_message_t* CAN_message_receive(void){						// What does this step do //NOT NECCECARY, but if we want to reference the recieved data from another part of the program this is necceccary
	return &CAN_receive_buffer;						// What does this step do
}
	
void CAN_construct_message(int id, uint8_t length){
	CAN_send_buffer.id = id;
	CAN_send_buffer.length = length;
	for(uint8_t i = 0; i < length; i++){
		CAN_send_buffer.data[i] = 0;
	}
}

	//array of int8_t as input (we chose int8_t over uint8_t so that we can send negative values
void CAN_message_send(uint8_t *data,uint8_t TXn){
	for(uint8_t i = 0; i < CAN_send_buffer.length; i++){
		CAN_send_buffer.data[i] = data[i];
	}
	CAN_send_byte(&CAN_send_buffer,TXn);
}

void CAN_send_byte(CAN_message_t* message,uint8_t TXn){
	MCP2515_write(MCP_TXBnSIDH+TXn*0x10,message->id>>3);		//8 most significant bits of the message ID
	MCP2515_write(MCP_TXBnSIDL+TXn*0x10,message->id<<5);		//3 least significant bits of the message ID
	MCP2515_write(MCP_TXBnDLC+TXn*0x10,(0b00001111)&(message->length));		//Message length
		
	for (uint8_t i = 0; i < message->length;i++){
		MCP2515_write(MCP_TXBnD0+TXn*0x10+i,message->data[i]);	//Message data
	}

	//MCP2515_request_to_send(MCP_MERRF+(1<<n));
	MCP2515_request_to_send(TXn);
	CAN_transmission_complete(TXn);
	#if UART_ENABLE
		printf("\nSENT MESSAGE:");
		CAN_print(CAN_send_buffer);
	#endif
}

uint8_t CAN_read(uint8_t adr){
	return MCP2515_read(adr);
}

uint8_t CAN_data_receive(void) {
	if(receive_flag){
		receive_flag = 0;
		uint8_t n = CAN_reception_complete();
		if (n >= 0){
			CAN_receive_buffer.id = ((CAN_read(RXBnSIDH + n*0x10)<<3)|(0b11100000 & (CAN_read(RXBnSIDL + n*0x10))>>5));
			CAN_receive_buffer.length = (CAN_read(RXBnDLC + n*0x10) & 0b00001111);
			for (uint8_t m = 0; m < CAN_receive_buffer.length; m++){
				CAN_receive_buffer.data[m] =  CAN_read(RXBnDM + m);
			}
		}
		#if UART_ENABLE == 1
			printf("\nRECIVED MESSAGE:");
			CAN_print(CAN_receive_buffer);
		#endif
		return 1;
	}
	return 0;
}

void CAN_print(CAN_message_t message){
	printf("\nID %i\tL: %i\tDATA:\n",message.id,message.length);
	for(uint8_t i = 0; i < message.length; i++){
		printf("%i\t",message.data[i]);
	}
}

#if NODE == 1
ISR(INT2_vect){//interrupt incoming message
	receive_flag = 1;
}
#elif NODE == 2
ISR(INT4_vect){//interrupt incoming message
	receive_flag = 1;
}
#endif

	
void CAN_interrupt_setup(void){
	cli();
	#if NODE == 1
		//Extended MCU Control Register bit 0 ....turned off?
		EMCUCR &= ~(1<<ISC2);
		
		//General Interrupt Control Register port int2 defined as on?
		GICR |= (1<<INT2);
	#elif NODE == 2
		// Use PE4 as external interrupt pin
		DDRE &= ~(1<<PINE4);
	
		// Trigger interrupt on r edge (Compare sec 15.2.2 of Atmega2560 data sheet).
		EICRB &= ~(1<<ISC40);	//x0
		EICRB |= (1<<ISC41);	//1x
	
		// Enable INT4 (Compare sec 15.2.3 of Atmega2560 data sheet).
		EIMSK |= (1<<INT4);

		//Enable global interrupt.
		
	
	#endif
	sei();
}

int8_t CAN_reception_complete(void){
	//printf("MCP_CANINTF = %i",MCP2515_read(MCP_CANINTF));
	
	// Wait for data to be loaded into either receive buffer.
	while(!((MCP2515_read(MCP_CANINTF) & MCP_RX0IF) | (MCP2515_read(MCP_CANINTF) & MCP_RX1IF)));
	
	
	
	// Check which buffer contains the message and clear interrupt flag.
	if(MCP2515_read(MCP_CANINTF) & MCP_RX0IF){
		MCP2515_bit_modify(MCP_CANINTF,MCP_RX0IF,0);
		return 0;
	}
	if(MCP2515_read(MCP_CANINTF) & MCP_RX1IF){
		MCP2515_bit_modify(MCP_CANINTF,MCP_RX1IF,0);
		return 1;
	}
	return -1;
}

uint8_t CAN_transmission_complete(uint8_t buffer){
	while(!(MCP2515_read(MCP_CANINTF) & (MCP_TX0IF << buffer)));
	return 1;
}



