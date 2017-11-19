/*
 * pi_controller.c
 *
 * Created: 19.11.2017 14:44:11
 *  Author: pamarton
 */ 

//sampling time T of 20 milliseconds
//take 5 samples within T

#include "pi_controller.h"

float errorSum;
float T = 20;
float speed_error;

void pi_controller_init(void){
	errorSum = 0;
}

float pi_compute_error(float speed){
	
	for (uint8_t i = 0; i<5; i++){
	float speed_measured = encoder_read();
	float speed_desired = speed;
	
	float speed_error = speed_desired - speed_measured;
	
	errorSum += speed_error;
	
	_delay_ms(4);
	}
	
	
	return speed_error;
}

float pi_compute_input(float speed_error, float dT){
	float u = Kp *speed_error + T*Ki*errorSum; 
	return 0;
}