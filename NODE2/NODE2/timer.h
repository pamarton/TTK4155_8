/*
 * timer.h
 *
 * Created: 17/10/2017 16:04:52
 *  Author: Amund Marton
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#define TIMER_PRESCALER 1024

#define TIMER_FREQ 50
//------------------------------------------//
//	INCLUDE									//
//------------------------------------------//

#include "../../common_library/common.h"
#include <avr/interrupt.h>
#include "../../common_library/uart.h"

//------------------------------------------//
//	DECLARATIONS							//
//------------------------------------------//


void initialize_timer(uint16_t timer_freq);
ISR(TIMER4_COMPA_vect);//interrupt when Timer_0 is done
uint8_t timer_check_flag(void);
uint16_t timestamp(uint16_t time_ms);
uint8_t check_timestamp(uint16_t stamp);
//------------------------------------------//
//	INTERRUPTS								//
//------------------------------------------//

ISR(TIMER4_COMPA_vect);//interrupt when Timer_0 is done

#endif /* TIMER_H_ */