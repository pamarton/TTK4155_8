/*
 * motor_controller.c
 *
 * Created: 02.11.2017 16:38:12
 *  Author: pamarton
 */ 
#include "servo_driver.h"

void servo_init(void){
	pwm_init(20);
	servo_set(0);
}

int servo_set(int value){
	if(value >= CONTROL_INPUT_MIN && value <= CONTROL_INPUT_MAX){
		double pulse_width = (PULSE_WIDTH_MIN + (PULSE_WIDTH_MAX - PULSE_WIDTH_MIN) * ((CONTROL_INPUT_MAX - (double)value)/(CONTROL_INPUT_MAX - CONTROL_INPUT_MIN)));
		if(pulse_width >= PULSE_WIDTH_MIN && pulse_width <= PULSE_WIDTH_MAX){//UNNECCECARY, BUT STAY SAFE
			pwm_set_pulse_width(pulse_width);
			#if UART_ENABLE
				printf("%i",(int)(100*pulse_width));
			#endif
			return 1;
		}else{
			return 0;
		}
	}else{
		return -1;
	}
}