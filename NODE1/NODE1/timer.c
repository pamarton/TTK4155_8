/*
 * timer.c
 *
 * Created: 17/10/2017 16:04:36
 *  Author: Amund Marton
 */ 

#include "timer.h"

uint8_t FLAG_timer_1_complete;

void initialize_timer(uint8_t fps){	//	Function for initialization of the timers
	TIMSK |= (1<<OCIE0);//when timer is the same as OCR0 it sends an interrupt
	TCCR0 |= (1<<WGM01)|(1<<CS02)|(1<<CS00);//		WGM01: set mode to CTC (reset timer on OCR0)     CS0n:set prescaler (to 1024)
	OCR0 = (F_CPU/PRESCALER)/fps;//-> 4800Hz. Then we just need to count to (4800Hz/Desired_Fps) to get the amount we need count to. (60fps -> 80)
	FLAG_timer_1_complete = 1;//since we are initializing we want to refresh the page
}

uint8_t timer_check_flag(void){	//	function for getting the value of the timer
	if (FLAG_timer_1_complete == 1)
	{
		FLAG_timer_1_complete = 0;
		return 1;
	}
	return 0;
}

void timer_disable_flag(void){	//	function for getting the value of the timer
	FLAG_timer_1_complete = 0;
}

ISR(TIMER0_COMP_vect){//interrupt when Timer_0 is done, resets itself
	FLAG_timer_1_complete = 1;
}

void timer_delay(int timer_ms){ //simple delay function, in miliseconds
	timer_ms = (FPS*((double)timer_ms/1000));
	while(timer_ms>0){
		if (timer_check_flag())
		{
			timer_ms--;
		}
	}
}