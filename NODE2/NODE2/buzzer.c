/*
 * buzzer.c
 *
 * Created: 11.11.2017 16:18:12
 *  Author: pamarton
 */ 
/*
 * timer.c
 *
 * Created: 17/10/2017 16:04:36
 *  Author: Amund Marton
 */ 

#include "buzzer.h"
#include "../../common_library/common.h"
#include "../../common_library/i_o.h"
#include "../../common_library/uart.h"
uint8_t FLAG_refresh_screen;
uint8_t buzzer_on;
void buzzer_init(void){	//	Function for initilization of the timers. Period is given in ms
	//Enable output at port E3
	DDRH |= (1 << PH3);
	// Use Fast-pwm/mode 14. Compare Table 17.2 on page 145 of the Arduino2560 datasheet. Using  OC3A.
	TCCR4A &= ~(1<<WGM40);
	TCCR4A |= (1<<WGM41);
	TCCR4B |= (1<<WGM43)|(1<<WGM42); //		WGM01: set mode to CTC (reset timer on OCR0)     CS0n:set prescaler (to 1024)
	
	//Set COM3A_1:0 to 10 to use non-inverted pwm.
	TCCR4A |= (1<<COM4A1);
	TCCR4A &= ~(1<<COM4A0);

	// Set prescaler. Compare Table17-6. Clock Select Bit Description.
	TCCR4B |= (1<<CS42) | (1<<CS40);
	TCCR4B &= ~(1<<CS41);
	
	// Define TOP. Compare Table 17.2.				
	buzzer_set_period(1);
	buzzer_set_freq(4);
}

void buzzer_set_period(double period){
	TCNT4 = 0;
	OCR4A = period;
}

void buzzer_set_freq(double freq){
	DDRH |= (1 << PH3);
	TCNT4 = 0;
	ICR4 = (int)(BUZZER_SCALAR_IN_MS * 1000 / freq);
}

void buzzer_of(){
	DDRH &= ~(1<<PH3);
	TCNT4 = 0;
}

