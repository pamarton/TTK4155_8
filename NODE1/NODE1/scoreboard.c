/*
 * scoreboard.c
 *
 * Created: 13.11.2017 16:29:47
 *  Author: jonasgl
 */ 
#include "scoreboard.h"
#include "timer.h"

void scoreboard_write(uint8_t data){
	PORTB |= (1<<PB1)|(1<<PB0);
	PORTA = data;
	timer_delay(1);
	PORTB &= ~((1<<PB1)|(1<<PB0));
}

void scoreboard_command(uint8_t command){
	PORTB |= (1<<PB0);
	PORTA = command;
	timer_delay(1);
	PORTB &= ~((1<<PB0));
}

void scoreboard_init(void){
	DDRB |= (1<<PB0) | (1<<PB1); //make PINB1 and PINB0 outputs
	DDRA |= 0xFF; //make all PINA outputs
	
 	scoreboard_command(0b00000001);
 	timer_delay(100);
 	scoreboard_command(0b00001100);
 	timer_delay(100);
}