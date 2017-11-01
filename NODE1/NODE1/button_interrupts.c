/*
 * button_interrupts.c
 *
 * Created: 21.09.2017 18:11:23
 *  Author: pamarton
 */ 
#include "button_interrupts.h"

void initalize_interrupts(void){
	BIT_ON(DDRB, PD2);//enable input
	BIT_ON(DDRB, PD3);
	
	BIT_ON(MCUCR, ISC00);//configuring the interrupts for INT0 on rising edge
	BIT_ON(MCUCR, ISC01);
	
	BIT_ON(MCUCR, ISC10);//configuring the interrupts for INT1 on rising edge
	BIT_ON(MCUCR, ISC11);
	
	BIT_ON(GICR, INT0);//enabling the interrupts INT0 and INT1 in the memory ???????????????????? 21.09.17
	BIT_ON(GICR, INT1);
}

#include "../../common_library/uart.h"
ISR(INT0_vect){//interrupt button Right
	//printf("X: %i\tY: %i\tL: %i\tR: %i\n",read_control_input('X'),read_control_input('Y'),read_control_input('L'),read_control_input('R'));//REMOVE THIS AND THE #INCLUDE "input_convercions.h" in button_interrupts.h
	menu_right_button_flag();//sets the interupt flag
}

ISR(INT1_vect){//interrupt button Left
	menu_left_button_flag();//sets the interrupt flag
}