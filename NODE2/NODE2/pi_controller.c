/*
 * pi_controller.c
 *
 * Created: 19.11.2017 14:44:11
 *  Author: pamarton
 */ 

#include "pi_controller.h"

float errorSum;
float T_Update = 1;
float motor_speed_error;

float Ki;
float Kp;
float u;
float vel_ref;



void pi_controller_init(float Ki_init, float Kp_init, float T_Update_init){
	errorSum = 0.0;
	vel_ref = 0.0;
	u = 0.0;
	Ki = Ki_init;
	Kp = Kp_init;
	initialize_timer(T_Update_init);
	motor_init();
}

void pi_controller_update(float vel_ref){
	
	//vel_ref = vel_ref_in;
	if(timer_check_flag()){
		float vel_meas;
		//printf("Vel_ref: %i\n",vel_ref);
		//printf("Vel_meas: %i\n",(int16_t)(motor_get_velocity()));
		float error = vel_ref - vel_meas;
		//errorSum += motor_speed_error;
		u = Kp*error + Ki*errorSum*T_Update;
		
		//printf("u: %i\n",u);
		
		if(u<0){
			//motor_set_direction(-1);
		}else if(u>0){
			//motor_set_direction(1);
		}else{
			//motor_set_direction(0);
		}
	}
	motor_set_motor_speed((int16_t)u);
}

//	Function for initialization of the timers

/*
float pi_compute_error(float motor_speed){
	
	for (uint8_t i = 0; i<5; i++){
	float motor_speed_measured = encoder_read();
	float motor_speed_desired = motor_speed;
	
	float motor_speed_error = motor_speed_desired - motor_speed_measured;
	
	errorSum += motor_speed_error;
	
	_delay_ms(4);
	}
	
	
	return motor_speed_error;
}

float pi_compute_input(float motor_speed_error, float dT){
	float u = Kp *motor_speed_error + T*Ki*errorSum; 
	return 0;
}
*/




