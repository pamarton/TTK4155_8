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
//	DECLARATIONS							//
//------------------------------------------//

void pwm_init(int period);	//	Function for initialization of the timers 


#endif /* PWM_H_ */