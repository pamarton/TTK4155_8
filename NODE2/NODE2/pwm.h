/*
 * timer.h
 *
 * Created: 17/10/2017 16:04:52
 *  Author: Amund Marton
 */ 


#ifndef PWM_H_
#define PWM_H_

//------------------------------------------//
//	INCLUDE									//
//------------------------------------------//

#include "../../common_library/common.h"
#include <avr/interrupt.h>

//------------------------------------------//
//	DEFINITIONS								//
//------------------------------------------//

#define FREQ_IN_MS 1000//Frequency of a milli-second 
#define PWM_PRESCALER 1024//Prescaler of the pwm
#define SCALAR_IN_MS (double)(F_CPU/FREQ_IN_MS)/PWM_PRESCALER//Number the timer count to each milli-second

#define PWM_DDR DDRE
#define PWM_PIN PE3
#define PWM_TCCRnA TCCR3A
#define PWM_TCCRnB TCCR3B
#define PWM_OCRnA OCR3A
#define PWM_ICRn ICR3

//------------------------------------------//
//	DECLARATIONS							//
//------------------------------------------//

void pwm_init(double period);				//	Function for initialization of the timers 
void pwm_set_period(double period);			//	Function for setting period of the pwm
void pwm_set_pulse_width(double period);	//	Function for setting the pulse width of the pwm

#endif /* PWM_H_ */