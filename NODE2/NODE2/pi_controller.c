/*
 * pi_controller.c
 *
 * Created: 19.11.2017 14:44:11
 *  Author: pamarton
 */ 

#include "pi_controller.h"


float T_Update = 1;
float motor_speed_error;

int16_t Ki; //Integral gain
int16_t Kp; //Proportional gain
int16_t u; //Control input
int16_t pos_ref; //Position reference (input to control loop)
int16_t pos_errSum; //Sigma error

int16_t pos_meas;
int16_t pos_err;

uint8_t sMotor; 
int16_t pos_max;
uint16_t sample_freq;

int16_t z;
int16_t zd;
int16_t vel;
int16_t acc_fric;
int8_t sign_vel;

int16_t p_term;
int32_t i_term, ret, temp;

int32_t MAX_ERROR = MAX_INT / (KP + 1);
int32_t MAX_ERROR_SUM = MAX_I_TERM / (KP + 1);

void pi_controller_init(int16_t sample_freq_init){
	pos_errSum = 0;
	pos_ref = 0;
	u = 0;
	sample_freq = sample_freq_init;
	
	initialize_timer(sample_freq);
	pos_max = motor_init();
	
	//printf("pos_max: %i\n", pos_max);
	
	// For friction estimator.
	z = 0;
	zd = 0;
	vel = 0;
	acc_fric = 0;
}

void pi_controller_update(int16_t pos_ref){
	//pos_ref = 5000;
	if(timer_check_flag()){
		
		//Measured position
		pos_meas = encoder_read();
		
		pos_err = pos_ref - pos_meas;
		pos_errSum  += pos_err;
		
		// Calculate p-term and limit to maximum error
		if(pos_err > MAX_ERROR){
			p_term = MAX_INT;
		}else if(pos_err < -MAX_ERROR){
			p_term = -MAX_INT;
		}else{
			p_term = pos_err * KP;
		}
		
		// Calculate i-term and limit integral runaway
		temp = pos_err + pos_errSum;
		if(temp > MAX_ERROR_SUM){
			i_term = MAX_I_TERM;
			pos_errSum = MAX_ERROR_SUM;
		}else if(temp < -MAX_ERROR_SUM){
			i_term = -MAX_I_TERM;
			pos_errSum = -MAX_ERROR_SUM;
		}else{
			pos_errSum = temp;
			i_term = KI *pos_errSum;
		}
		
		
		//u = (p_term + i_term) / SCALING_FACTOR;
		
		u = (p_term ) / SCALING_FACTOR;
		if(u > MAX_INT){
			u = MAX_INT;
		}else if(ret < - MAX_INT){
			u = -MAX_INT;
		}
		
		
		
		int16_t g = 1;// motor_get_velocity();

		
		//u = (pos_err/KP);// +  pos_errSum/KI/TIMER_FREQ;
		//printf("g: %i\tu: %i\tpos_err:\t%i\terrSum:\t%i\n", motor_get_velocity(), u, pos_err, pos_errSum);
		
		int8_t offset = 40;
		int8_t maxSpeed = 50;
		
		
		if (u > 0)
		{
			motor_set_direction(MOTOR_POLARITY);
		}else if(u < 0){
			motor_set_direction(-MOTOR_POLARITY);
			u*=-1;
		}
		
		if(ESTIMATE_FRICTION){
			int16_t friction = estimate_friction(u, motor_get_velocity());
			printf("Friction: %i\n", friction);
			u += friction;
		}
		
		
		if(u > maxSpeed){
			u = maxSpeed;
		}	
		//printf("u: %i\t p_r:\t%i\tp_e:\t%i\n",u,pos_ref,pos_err);
	
		//------------------------------
		
		
		int8_t errorWindow = 50;
		if(pos_err > -errorWindow && pos_err < errorWindow){
			pi_controller_reset();
			motor_set_motor_speed(0);
		}else{
			set_speed(u);
		}
	}
	
	
	/*
	if(pos_ref < pos_meas + 5 || pos_ref > pos_meas -5){
		motor_set_motor_speed(find_speed());
		}else{
		motor_set_motor_speed(0);
	}*/
	
	//motor_set_motor_speed((int16_t)u);
	
}

int16_t estimate_friction(int16_t u, int16_t vel){
	int8_t kInv = 100;
	int8_t mInv = 100;
	
	/*
	if(vel < 0){
		sign_vel = -1;
	}else{
		sign_vel = 1;
	}
	
		
	zd = u*sign_vel/kInv;
	z += zd;
	acc_fric = z - vel*sign_vel/kInv/mInv;

	int16_t friction =  acc_fric*sign_vel;
	*/
	
	zd = u/kInv;
	z+= zd;
	acc_fric = z - vel/kInv/mInv;
	int16_t friction =  acc_fric;
	return friction;	
}
void pi_controller_reset(void){
	pos_errSum = 0;
}

void set_speed(uint8_t input_speed){
	if (input_speed > 2)
	{
		motor_set_motor_speed(MOTOR_DEADBAND + input_speed);
	}else{
		motor_set_motor_speed(0);
	}
	
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




