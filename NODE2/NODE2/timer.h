/*
 * timer.h
 *
 * Created: 17/10/2017 16:04:52
 *  Author: Amund Marton
 */ 


#ifndef TIMER_H_
#define TIMER_H_
#define TIMER_PRESCALER 1024

//------------------------------------------//
//	INCLUDE									//
//------------------------------------------//

#include "../../common_library/common.h"
#include <avr/interrupt.h>
#include "../../common_library/uart.h"

//------------------------------------------//
//	DECLARATIONS							//
//------------------------------------------//


void initialize_timer(float T_Update);
ISR(TIMER4_COMPA_vect);//interrupt when Timer_0 is done
uint8_t timer_check_flag(void);
//------------------------------------------//
//	INTERRUPTS								//
//------------------------------------------//

ISR(TIMER4_COMPA_vect);//interrupt when Timer_0 is done

#endif /* TIMER_H_ */