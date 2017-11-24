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
#include	"TWI_Master.h"
#include	"motor.h"
void init_all(void);
#include	"../../common_library/uart.h"//REMOVE ME
#include	"pi_controller.h"
#include	"solenoid.h"
#include	 "game.h"


int main(void){
	

	
	init_all();
	
	while(1){
		game_init(1);
		game_play();
	}
	
	/*
	uint8_t joysens = 10;
	int8_t joymax = 100;
	int8_t joyx = 10;
	
	float result = (float) joyx;
	
	float x = 1.1;
	unsigned char *chptr;
	//float result = (float)joysens * (float)joyx / (float)joymax;
	//printf("result: %2.2f", 10.3);
	chptr = (unsigned char *) &x;
	printf("result: %c\t%c\t%c\t%c\t\n", (*chptr++),(*chptr++),(*chptr++),(*chptr++));
	//printf("result: %i\t%i\n", (*chptr));
	
	while(1){
		
	}
	*/
	//initialize_timer(50);
	

	
	
	/*
	while(1){
		CAN_data_receive();
		if(CAN_message_receive()->id == CAN_GAME_PARAMS_ID){
			printf("Joystick_min: %i", (int8_t) CAN_message_receive()->data[0]);
		}
	}
	return 0;
	
	uint8_t score[CAN_GAME_SCORE_LENGTH];
	score[0] = (1000>>8);
	score[1] = (1000);
	//Send score to Node1
	CAN_construct_message(CAN_GAME_SCORE_ID, CAN_GAME_SCORE_LENGTH);
	CAN_message_send(score,0);
	
	
	
	while(1){
		CAN_data_receive();
	}
	return 0;
	
	while(1){
		printf("IR: %i\n", read_adc());
	}
	*/
	

	while(1){
		if(CAN_data_receive()){
			
			if(CAN_message_receive()->id == CAN_GAME_PARAMS_ID){
				game_init(CAN_message_receive()->data);
				printf("Game initialized...\n");
			}
			
			if(CAN_message_receive()->id == CAN_GAME_CONTROL_ID){
				uint8_t score[CAN_GAME_SCORE_LENGTH];
				score[0] = 0;
				score[1] = game_play();
				//Send score to Node1
				CAN_construct_message(CAN_GAME_SCORE_ID, CAN_GAME_SCORE_LENGTH);
				CAN_message_send(score,0);
			}
		}
	}

	return 0;
}

void init_all(void){
	
	cli();
	init_UART();
	CAN_initialize();
	printf("CAN initialized\n");
	TWI_Master_Initialise();
	printf("TWI initialized\n");
	//Motor is being initialized by PI-Controller.
	//motor_init();
	//motor_calibrate(100);
	//printf("Motor initialized\n");
	servo_init();
	printf("Servo initialized\n");
	IR_init();
	printf("IR initialized\n");
	//printf("solenoid\n");
	solenoid_init();
	initialize_timer(TIMER_FREQ);
	//printf("Solenoid initialized\n");
	pi_controller_init(TIMER_FREQ);
	//pi_controller_init(1,1,TIMER_FREQ);
	printf("PI_Controller initialized.\n");
	#if UART_ENABLE
		init_UART();
		printf("Program initialized\n");
	#endif
	sei();
}


