/*
 * NODE2.c
 *
 * Created: 30.10.2017 16:50:33
 *  Author: pamarton
 */ 


#include	<avr/io.h>
#include	"../../common_library/common.h"
#include	<avr/interrupt.h>
#include	"../../common_library/CAN.h"
#include	<util/delay.h>
#include	"servo_driver.h"
#include	"IRsensor.h"
#include	"buzzer.h"
#include	"SD_card.h"
#include	"sounds.h"
#include "TWI_Master.h"
#include "motor.h"
void init_all(void);

int main(void){
	init_all();
	
	printf("Hallo\n");
	servo_init();
	
	
	/*
	buzzer_init();
	buzzer_set_freq(100);
	_delay_ms(200);
	buzzer_of();
	*/
	IR_init();
	
	init_all();
	
	
	
	//SD_CARD
	//SD_initialize();
	//SD_test();
	
	//END SD_CARD
	
	
	
	
	//uint8_t temp[8] = {1,2,3,4,5,6,7,8};
	//uint8_t *data = temp;

	uint8_t sendCAN = 0;
	uint8_t speed = 50;
	uint8_t direction = 1;
	while(1){
		/*
		if(sendCAN){
			//CAN_message_send(data,0);
			//data[7]--;
		}
		if(CAN_data_receive()){
			//_delay_ms(1000);
			//sound_play_effect(1);
			
			//servo_set(CAN_message_receive()->data[0]);
		}
		*/
		//read_adc();
		//printf("IR 	%i\n", ADCH);
		direction = -1 * direction;
		motor_set_direction(direction);
		
		
		motor_set_speed(0);
		//_delay_ms(100);
		//motor_set_speed(0);
		//_delay_ms(50);
		
	}
    return 0;
}

void init_all(void){
	
	cli();
	
	CAN_initialize();
	TWI_Master_Initialise();
	motor_init();
	
	
	#if UART_ENABLE
		init_UART();
		printf("Program initialized\n");
	#endif
	sei();
}
