/*
 * timer.c
 *
 * Created: 17/10/2017 16:04:36
 *  Author: Amund Marton
 */ 

#include "timer.h"

uint8_t update_flag;
uint16_t score_count;

void initialize_timer(float T_Update){
	
	//Enable interrupt. When timer is the same as OCR4A it sends an interrupt.
	TIMSK4 |= (1<<OCIE4A);
	
	// Reset timer.
	TCNT4 = 0x0000;
	
	// Use CTC mode.
	TCCR4B |= (1<<WGM42);
	TCCR4B &= ~(1<<WGM43);
	
	//Set prescaler.
	#if TIMER_PRESCALER == 1
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

	// Set counter limit.
	OCR4A = (F_CPU/(TIMER_PRESCALER))*T_Update - 1;
	update_flag = 0;
}

ISR(TIMER4_COMPA_vect){//interrupt when Timer_0 is done, resets itself
	update_flag = 1;
	score_count++;
	//printf("INT");
	//TIFR4 &= ~(1<<OCF1A);
}

uint8_t timer_check_flag(void){
	if (update_flag)
	{
		update_flag = 0;
		return 1;
	}
	return 0;
}
