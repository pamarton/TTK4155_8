/*
 * timer.c
 *
 * Created: 17/10/2017 16:04:36
 *  Author: Amund Marton
 */ 

#include "timer.h"

uint8_t FLAG_timer_1_complete;

void initialize_timer(uint16_t timer_frequency){	//	Function for initialization of the timers
	TIMSK4 |= (1<<OCIE4A);//when timer is the same as OCR4A it sends an interrupt
	
	TCNT4 = 0x0000; //resetiing timer
	
	TCCR4B |= (1<<WGM42); //CTC mode 
	TCCR4B &= ~(1<<WGM43); //CTC mode
	
	
	#if TIMER_PRESCALER == 1//Set prescaler
		TCCR4B |= (1<<CS40);
	#elif TIMER_PRESCALER == 8
		TCCR4B |= (1<<CS41);
	#elif TIMER_PRESCALER == 64
		TCCR4B |= (1<<CS41)|(1<<CS40);
	#elif TIMER_PRESCALER == 256
		TCCR4B |= (1<<CS42);
	#elif TIMER_PRESCALER == 1024
		TCCR4B |= (1<<CS42)|(1<<CS40);
	#endif
	
	TCCR4A |= (1<< COM4A1);//ENABLES OUTPUT, REMOVE THIS LATER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	OCR4A = (F_CPU/(TIMER_PRESCALER))/timer_frequency - 1;
	FLAG_timer_1_complete = 0;
}

uint8_t timer_check_flag(void){	//	function for getting the value of the timer
	if (FLAG_timer_1_complete == 1)
	{
		FLAG_timer_1_complete = 0;
		return 1;
	}
	return 0;
}

void timer_reset_flag(void){	//	function for getting the value of the timer
	FLAG_timer_1_complete = 0;
}

ISR(TIMER4_COMPA_vect){//interrupt when Timer_0 is done, resets itself
	FLAG_timer_1_complete = 1;
	TIFR4 &= ~(1<<OCF1A);
}



void timer_delay(int timer_ms){ //simple delay function, in miliseconds
	//REMOVED
}