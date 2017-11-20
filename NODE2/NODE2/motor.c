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


#define F_CPU 16000000	

int16_t encoder_read(void){
	MOTOR_PORT |= (1<<SEL);
	MOTOR_PORT &= ~(1<<OEN);
	
	// Read MSB.
	MOTOR_PORT &= ~(1<<SEL);
	_delay_us(2000);
	uint8_t msb = ENCODER_PIN;
	
	// Read LSB
	MOTOR_PORT |= (1<<SEL);
	_delay_us(2000);
	uint8_t lsb = ENCODER_PIN;
	
	//encoder_reset();
	
	
	
	
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





int16_t end_pos1;
int16_t end_pos2;

void motor_calibrate(uint8_t speed){
	motor_goto_end(70,-MOTOR_POLARITY);
	encoder_reset();
	end_pos2 = motor_goto_end(70,MOTOR_POLARITY);
	end_pos1 = motor_goto_end(70,-MOTOR_POLARITY);
	printf("C_L:%i\tC_R: %i\n",end_pos1, end_pos2);
}


int16_t pos;
int16_t old_pos;

int16_t motor_goto_end(uint8_t speed, int8_t direction){
	motor_set_direction(direction);
	motor_set_speed(speed);
	pos = encoder_read();
	uint16_t same_value_counter = 0;
	int16_t encoder_val = 0;
	while(same_value_counter < 10000){
		encoder_val = encoder_read();
		
		if(encoder_val == pos){
			same_value_counter++;
		}else{
			same_value_counter = 0;
			pos = encoder_val;
		}	
	}
	motor_set_speed(0);
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

