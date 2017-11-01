/*
 * timer.c
 *
 * Created: 17/10/2017 16:04:36
 *  Author: Amund Marton
 */ 

#include "pwm.h"
#include "../../common_library/i_o.h"
uint8_t FLAG_refresh_screen;

void pwm_init(int period){	//	Function for initilization of the timers
	//Enable output at port E3
	DDRE |= (1 << PE3);
	
	// Use Fast-pwm/mode 14. Compare Table 17.2 on page 145 of the Arduino2560 datasheet. Using  OC3A.
	TCCR3A &= ~(1<<WGM30);
	TCCR3A |= (1<<WGM31);
	TCCR3B |= (1<<WGM33)|(1<<WGM32); //		WGM01: set mode to CTC (reset timer on OCR0)     CS0n:set prescaler (to 1024)	
		
	//Set COM3A_1:0 to 10 to use non-inverted pwm.
	TCCR3A |= (1<<COM3A1);
	TCCR3A &= ~(1<<COM3A0);

	// Set prescaler. Compare Table17-6. Clock Select Bit Description.
	TCCR3B |= (1<<CS32) | (1<<CS30);
	TCCR3B &= ~(1<<CS31);
	
	// Define TOP. Compare Table 17.2.
	
	int TOP = 1000;
	int N = 1024;
	
	ICR3 = F_CPU / N / (1 + TOP) / period;
	
	
	//ICR3 = F_CPU/128/2;
}

void pwm_set_pulse_width(int val){
	OCR3A = val;
}