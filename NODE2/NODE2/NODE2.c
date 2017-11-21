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

int main(void){
	
	init_all();

	uint8_t* score[CAN_GAME_SCORE_LENGTH];
	score[2] = 1;
	//Send score to Node1
	CAN_construct_message(CAN_GAME_SCORE_ID, CAN_GAME_SCORE_LENGTH);
	CAN_message_send(score,0);
	
	while(1){

	}
	
	while(1){
		if(CAN_data_receive()){
			if(CAN_message_receive()->id == CAN_GAME_PARAMS_ID){
				game_init(CAN_message_receive()->data);
			}
			
			if(CAN_message_receive()->id == CAN_GAME_CONTROL_ID){
				uint8_t* score[CAN_GAME_SCORE_LENGTH];
				score[0] = game_play();
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
	printf("Solenoid initialized\n");
	pi_controller_init(0.1,1,T_UPDATE);
	printf("PI_Controller initialized.\n");
	//pi_controller_init(5,1,T_UPDATE);
	#if UART_ENABLE
		init_UART();
		printf("Program initialized\n");
	#endif
	sei();
}
