/*
 * motor_controller.c
 *
 * Created: 02.11.2017 16:38:12
 *  Author: pamarton
 */ 
#include "servo_driver.h"

void servo_init(void){
	pwm_init(20);
}

#define PULSE_MAX 2.1 //MS
#define PULSE_MIN 0.9 //MS
int servo_set(int value){
	if(value >= -100 && value <= 100){
		double pulse_width = (PULSE_MIN + (PULSE_MAX - PULSE_MIN) * (((double)value+100)/200));
		if(pulse_width >= 0.9 && pulse_width <= 2.1){
			pwm_set_pulse_width(pulse_width);
			printf("%i",(int)(100*pulse_width));
			return 1;
		}else{
			return 0;
		}
	}else{
		return -1;
	}
}