/*
 * buzzer.h
 *
 * Created: 11.11.2017 16:18:26
 *  Author: pamarton
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_
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

//------------------------------------------//
//	DECLARATIONS							//
//------------------------------------------//

void buzzer_init(void); 
void buzzer_set_freq(double freq);
void buzzer_set_period(double period);
void buzzer_of(void);

#endif /* BUZZER_H_ */