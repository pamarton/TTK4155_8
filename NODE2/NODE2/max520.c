/*
 * max520.c
 *
 * Created: 16.11.2017 16:30:55
 *  Author: pamarton
 */ 
#include "TWI_Master.h"
#include "max520.h"
#include <avr/interrupt.h>
#include <stdint.h>

void max520_init(void){
	
	TWI_Master_Initialise();
	sei();
	
}

void max520_send(uint8_t val){
	
	unsigned char msg[3] = {0b01011100,0,val}; //hardcoded slave address
		TWI_Start_Transceiver_With_Data(msg,3);
}