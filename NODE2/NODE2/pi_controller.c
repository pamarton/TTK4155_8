/*
 * pi_controller.c
 *
 * Created: 19.11.2017 14:44:11
 *  Author: pamarton
 */ 

#include "pi_controller.h"

float errorSum;
float T_Update = 1;
float speed_error;
uint8_t pi_update_flag;
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
	if(pi_update_flag){
		float vel_meas;
		printf("%i\n",(int16_t)(motor_get_velocity()));
		float error = vel_ref - vel_meas;
		//errorSum += speed_error;
		u = Kp*error + Ki*errorSum*T_Update;
		
		if(u<0){
			//motor_set_direction(-1);
		}else if(u>0){
			//motor_set_direction(1);
		}else{
			//motor_set_direction(0);
		}
		pi_update_flag = 0;
		
	}
	//motor_set_speed((int16_t)u);
}

//	Function for initialization of the timers
void initialize_timer(float T_Update){
	
	//Enable interrupt. When timer is the same as OCR4A it sends an interrupt.
	TIMSK4 |= (1<<OCIE4A);
	
	// Reset timer.
	TCNT4 = 0x0000;
	
	// Use CTC mode.
	TCCR4B |= (1<<WGM42);
	TCCR4B &= ~(1<<WGM43);
	
	//Set prescaler.
	#if PI_TIMER_PRESCALER == 1
	TCCR4B |= (1<<CS40);
	#elif PI_TIMER_PRESCALER == 8
	TCCR4B |= (1<<CS41);
	#elif PI_TIMER_PRESCALER == 64
	TCCR4B |= (1<<CS41)|(1<<CS40);
	#elif PI_TIMER_PRESCALER == 256
	TCCR4B |= (1<<CS42);
	#elif PI_TIMER_PRESCALER == 1024
	TCCR4B |= (1<<CS42)|(1<<CS40);
	#endif
	
	
	
	// Set counter limit.
	OCR4A = (F_CPU/(PI_TIMER_PRESCALER))*T_Update - 1;
	pi_update_flag = 0;
}

ISR(TIMER4_COMPA_vect){//interrupt when Timer_0 is done, resets itself
	pi_update_flag = 1;
	//printf("INT");
	//TIFR4 &= ~(1<<OCF1A);
}


/*
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
*/




