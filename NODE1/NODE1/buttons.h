/*
 * buttons.h
 *
 * Created: 21.09.2017 18:11:11
 *  Author: pamarton
 */ 


#ifndef buttons_H_
#define buttons_H_

//------------------------------------------//
//	INCLUDES								//
//------------------------------------------//

#include <avr/io.h>
#include <avr/interrupt.h>
#if UART_ENABLE
	#include "../../common_library/uart.h"
#endif
#include "../../common_library/i_o.h"
#include "input_conversion.h"//REMOVE THIS AND THE PRINTF IN THE buttons.c FILE

//------------------------------------------//
//	FUNCTIONS								//
//------------------------------------------//

void initalize_interrupts(void);
uint8_t check_flag_left(void);
uint8_t check_flag_right(void);
uint8_t joystick_pressed(void);
uint8_t button_pressed(void);

//------------------------------------------//
//	INTERRUPTS								//
//------------------------------------------//

ISR(INT0_vect);//interrupt button Right
ISR(INT1_vect);//interrupt button Left

#endif /* buttons_H_ */