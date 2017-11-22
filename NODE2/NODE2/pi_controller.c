/*
 * pi_controller.c
 *
 * Created: 19.11.2017 14:44:11
 *  Author: pamarton
 */ 

#include "pi_controller.h"


float T_Update = 1;
float motor_speed_error;

float Ki; //Integral gain
float Kp; //Proportional gain
float u; //Control input
uint8_t pos_ref; //Position reference (input to control loop)
float pos_errSum;

int16_t pos_meas;
int16_t pos_err;

float sMotor; 
float T_Update;
int16_t pos_max;

void pi_controller_init(float Ki_init, float Kp_init, float T_Update_init){
	pos_errSum = 0;
	pos_ref = 0;
	u = 0;
	Ki = Ki_init;
	Kp = Kp_init;
	T_Update = T_Update_init;
	
	initialize_timer(T_Update_init);
	pos_max = motor_init();
}

void pi_controller_update(float rel_pos_ref){
	
	pos_ref = rel_pos_ref * pos_max;
	if(timer_check_flag()){
		pos_meas = encoder_read();
		pos_err = pos_ref - pos_meas;
		pos_errSum  += pos_err;
		u = Kp*pos_err + Ki*pos_errSum/TIMER_FREQ;
	}
	motor_set_motor_speed((int16_t)u);
}



/* Tried to control speed

#define CONTROLER_INPUT_MAX 100
#define CONTROLER_INPUT_MIN 10

void pi_controller_update_reference(int8_t controller_input){
	if (controller_input == 0)
	{
		motor_set_direction(0);
		vel_ref = 0;
	}else if (controller_input < 0)
	{
		motor_set_direction(-MOTOR_POLARITY);
		vel_ref = motor_get_speed_min()+((float)-controller_input/(CONTROLER_INPUT_MAX-CONTROLER_INPUT_MIN))* (float)motor_get_speed_range();
	}else if(controller_input > 0){
		motor_set_direction(MOTOR_POLARITY);
		vel_ref = motor_get_speed_min()+((float)controller_input/(CONTROLER_INPUT_MAX-CONTROLER_INPUT_MIN))* (float)motor_get_speed_range();;
		//vel_ref = motor_get_speed_min()+(-(float)controller_input/(90) )* (float)motor_get_speed_range();
	}
	printf("C_I %i\t%i\n",controller_input,(int)vel_ref);
}

void pi_controller_update(float ctrl_in){
	
	//vel_ref = vel_ref_in;
	if(timer_check_flag()){
		
		float vel_error = vel_ref - motor_get_velocity();
		
		
		//u = Kp*error + Ki*errorSum*T_Update;
		
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




