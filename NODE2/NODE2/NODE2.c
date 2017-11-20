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

	int8_t motor_speed = 0;
	int8_t direction = 0.1;

	while(1){
		if(CAN_data_receive()){
			//printf("CAN value = %i", CAN_message_receive()->data[0]);
			motor_speed =  (int8_t)  CAN_message_receive()->data[0];
			
			
			if(motor_speed < 0 ){
				direction = 1;
				motor_speed = direction * motor_speed;
			}else if(motor_speed > 0){
				direction = -1;
				motor_speed = direction * motor_speed;
			}else{
				motor_speed = 0;
				direction = 0;
			}

			printf("motor_speed: %i\n", motor_speed);
			//servo_set(CAN_message_receive()->data[0]);
		}
		
		//printf("A");
		
		//read_adc();
		//printf("IR 	%i\n", ADCH);
		//encoder_read();
		
		double smotor_speed = 0.2;
		
		pi_controller_update(smotor_speed * motor_speed);
		motor_set_direction(direction);
		
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
