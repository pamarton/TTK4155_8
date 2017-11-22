/*
 * motor.c
 *
 * Created: 16.11.2017 09:36:40
 *  Author: pamarton
 */ 

#include "motor.h"
#include "../../common_library/common.h"
#include	<util/delay.h>
#include "../../common_library/uart.h"

int16_t motor_init(void){
	
	// Make all relevant motor pins output.
	MOTOR_DDR |= (1<<OEN)|(1<<RSTN)|(1<<SEL)|(1<<EN)|(1<<DIR);
	
	// Make all encoder pins input.
	ENCODER_DDR = 0x00;
	
	// Enable motor.
	MOTOR_PORT |= (1<<EN);
	
	encoder_reset();
	
	int16_t pos_max = motor_calibrate(100);
	return pos_max;
}

void motor_set_motor_speed(uint8_t motor_speed){
	//printf("Setting motor motor_speed: %i\n", motor_speed);
	unsigned char TWI_msg[3] = {ADC_ADDRESS, ADC_DAC0_ADDRESS, motor_speed};
	TWI_Start_Transceiver_With_Data(TWI_msg, 3);
}

void motor_set_direction(int8_t direction){
	
	switch (direction){
		case MOTOR_POLARITY:
			//printf("Setting motor direction: %i\n", direction);
			MOTOR_PORT &= ~(1<<DIR);
			break;
		case -MOTOR_POLARITY: 
			//printf("Setting motor direction: %i\n", direction);
			MOTOR_PORT |=  (1<<DIR);
			break;
	}	
}

//Toggle RSTN to reset encoder.
void encoder_reset(void){
	MOTOR_PORT &= ~(1<<RSTN);
	_delay_us(20);
	MOTOR_PORT |= (1<<RSTN);
}

// Encoder read procedure (compare motorbox.pdf page 5)
int16_t encoder_read(void){
	MOTOR_PORT |= (1<<SEL);
	MOTOR_PORT &= ~(1<<OEN);
	
	// Read MSB.
	MOTOR_PORT &= ~(1<<SEL);
	_delay_us(20);
	uint8_t msb = ENCODER_PIN;
	
	// Read LSB
	MOTOR_PORT |= (1<<SEL);
	_delay_us(20);
	uint8_t lsb = ENCODER_PIN;

	// Disable output of encoder
	MOTOR_PORT |= (1<<OEN);
	
	
	#if UART_ENABLE
		printf("%i %i\n",msb,lsb);
	
	#endif
	//printf("%i %i\n",msb,lsb);
	//printf("\nENC %i\n",twos_compliment_decode(msb,lsb));
	return twos_compliment_decode(msb,lsb);
}



int16_t twos_compliment_decode(uint8_t msb, uint8_t lsb){
	return (int16_t)((msb<<8)|lsb);
}



/*
void motor_calibrate(uint8_t motor_speed){
	motor_goto_end(70,-MOTOR_POLARITY);
	encoder_reset();
	end_pos2 = motor_goto_end(70,MOTOR_POLARITY);
	end_pos1 = motor_goto_end(70,-MOTOR_POLARITY);
	printf("C_L:%i\tC_R: %i\n",end_pos1, end_pos2);
}

void motor_calibrate(uint8_t motor_speed){
	motor_goto_end(motor_speed,-MOTOR_POLARITY);
	encoder_reset();
	end_pos2 = motor_goto_end(motor_speed,MOTOR_POLARITY);
	end_pos1 = motor_goto_end(motor_speed,-MOTOR_POLARITY);
	printf("C_L:%i\tC_R: %i\n",end_pos1, end_pos2);
}
*/

int16_t pos_max;
int16_t vel_max;
int16_t pos_min = 0;
uint8_t motor_speed_min;
uint8_t motor_speed_max;

#define MIN_VELOCITY 10

float  motor_calibrate(uint8_t motor_speed){
	//Move sledge all the way to the right.
	motor_goto_end(motor_speed,-MOTOR_POLARITY);
	encoder_reset();
	pos_max = motor_goto_end(motor_speed,MOTOR_POLARITY);
	motor_goto_end(motor_speed,-MOTOR_POLARITY);
	
	//end_pos1 = motor_goto_end(motor_speed,-MOTOR_POLARITY);
	printf("E_min:%i\tE_Max: %i\n",pos_min, pos_max);
	/*
	//Move sledge back and measure motor_speed.
	motor_speed_max = motor_speed;
	
	vel_max = motor_calibrate_max_velocity(motor_speed,-MOTOR_POLARITY);
	motor_speed_min = motor_calibrate_min_motor_speed(MOTOR_POLARITY);
	motor_goto_end(motor_speed_min,MOTOR_POLARITY);
	uint8_t temp_motor_speed_min = motor_calibrate_min_motor_speed(-MOTOR_POLARITY);
	if(temp_motor_speed_min > motor_speed_min){
		motor_speed_min = temp_motor_speed_min;
	}
	
	//float sMotor = vel_max /(motor_speed_max - motor_speed_min);
	*/
	return pos_max;
}

int16_t motor_get_speed_range(void){
	return (motor_speed_max - motor_speed_min);
}

int16_t motor_get_speed_min(void){
	return motor_speed_min;
}


int16_t motor_get_speed_max(void){
	return motor_speed_max;
}


int16_t pos;
int16_t old_pos;

int16_t motor_goto_end(uint8_t motor_speed, int8_t direction){
	motor_set_direction(direction);
	motor_set_motor_speed(motor_speed);
	pos = encoder_read();
	uint8_t time_counter = 0;
	int16_t encoder_val = 0;
	
	while(time_counter < 2*TIMER_FREQ){
		encoder_val = encoder_read();
		time_counter += timer_check_flag();
		if(encoder_val != pos){
			pos = encoder_val;
		}	
	}
	motor_set_motor_speed(0);
	return pos;
}

int16_t motor_get_position(void){
	old_pos = pos;
	pos = encoder_read(); 
	return pos;
}

int16_t motor_get_velocity(void){
	motor_get_position();
	return (pos - old_pos);
}

uint8_t motor_calibrate_max_velocity(uint8_t max_motor_speed, int8_t direction){
	motor_set_direction(direction);
	motor_set_motor_speed(max_motor_speed);
	uint16_t time_counter = 0;
	
	while(pos > (pos_max-pos_min)*0.8){
		motor_get_position();
	}
	
	while(pos >= (pos_max-pos_min)*0.2){
		motor_get_position();
		time_counter += timer_check_flag();
	}
	
	while(pos > (pos_max-pos_min)*0.1){
		motor_get_position();
	}
	motor_set_motor_speed(0);
	printf("p %i \t t %i \t v %i \n", (((pos_max-pos_min)/10)*6),(time_counter),((((pos_max-pos_min)/10)*6)/time_counter));
	
	return ((((pos_max-pos_min)/10)*6)/time_counter);
}

uint8_t motor_calibrate_min_motor_speed(int8_t direction){
	uint16_t motor_speed = 0;
	uint8_t time_counter = 0;
	motor_set_motor_speed(0);
	motor_set_direction(direction);
	int16_t t_vel = motor_get_velocity();
	printf("s %i,\tv %i,\n",motor_speed,t_vel);
	_delay_ms(1000);
	motor_get_velocity();
	_delay_ms(1000);
	
	if (direction == MOTOR_POLARITY)
	{
		do{
			t_vel = motor_get_velocity();
			printf("s %i,\tv %i,\n",motor_speed,t_vel);
			motor_set_motor_speed(motor_speed);
			motor_speed++;
		}while (t_vel < MIN_VELOCITY);
	}
	
	if (direction == -MOTOR_POLARITY){
		do{
			t_vel = motor_get_velocity();
			printf("s %i,\tv %i,\n",motor_speed,t_vel);
			motor_set_motor_speed(motor_speed);
			motor_speed++;
		}while (t_vel > -MIN_VELOCITY);
	}
	
	_delay_ms(1000);
		
	motor_set_motor_speed(0);
	
	
	
	printf("FINAL\ts %i,\tv %i,\n",motor_speed,t_vel);
	return motor_speed;
}


