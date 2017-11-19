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

void motor_init(void){
	
	// Make all relevant motor pins output.
	MOTOR_DDR |= (1<<OEN)|(1<<RSTN)|(1<<SEL)|(1<<EN)|(1<<DIR);
	
	// Make all encoder pins input.
	ENCODER_DDR = 0x00;
	
	// Enable motor.
	MOTOR_PORT |= (1<<EN);
	
	encoder_reset();
	
	
}

void motor_set_speed(uint8_t speed){
	//printf("Setting motor speed: %i\n", speed);
	unsigned char TWI_msg[3] = {ADC_ADDRESS, ADC_DAC0_ADDRESS, speed};
	TWI_Start_Transceiver_With_Data( TWI_msg, 3);
}

void motor_set_direction(int8_t direction){
	
	switch (direction){
		case -1:
			//printf("Setting motor direction: %i\n", direction);
			MOTOR_PORT &= ~(1<<DIR);
			break;
		case +1: 
			//printf("Setting motor direction: %i\n", direction);
			MOTOR_PORT |=  (1<<DIR);
			break;
	}	
}

//Toggle RSTN to reset encoder.
void encoder_reset(void){/*
	if(MOTOR_PORT & (1<<RSTN)){
		MOTOR_PORT &= ~(1<<RSTN);
	}
	else{
		MOTOR_PORT |= (1<<RSTN);
	}
	*/
	MOTOR_PORT &= ~(1<<RSTN);
	_delay_us(20);
	MOTOR_PORT |= (1<<RSTN);
}


// Encoder read procedure (compare motorbox.pdf page 5)

int16_t encoder_read(void){
	MOTOR_PORT &= ~(1<<OEN);
	
	// Read MSB.
	MOTOR_PORT &= ~(1<<SEL);
	_delay_us(200);
	uint8_t msb = ENCODER_PIN;
	
	// Read LSB
	MOTOR_PORT |= (1<<SEL);
	_delay_us(200);
	uint8_t lsb = ENCODER_PIN;
	
	encoder_reset();
	
	
	printf("E_r %i\t%i\n",msb, lsb);
	
	// Disable output of encoder
	MOTOR_PORT |= (1<<OEN);
	
	int16_t encoder_reading = ((int16_t)msb << 8)|((int16_t)lsb);
	
	return encoder_reading;
}



int16_t e_r(void){
	
}