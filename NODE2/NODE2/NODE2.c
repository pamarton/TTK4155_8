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

	while (1)
	{
			//servo_set(CAN_message_receive()->data[0]);
		servo_set(-100);
		
	}
	
	
	
	printf("solenoid\n");
	solenoid_init();
	
	while(0){
		solenoid_enable();
		_delay_ms(50);
		solenoid_disable();
		_delay_ms(1000);
	}
	
	IR_init();
	
	init_all();
	/*
	twos_compliment_decode(0,0);
	twos_compliment_decode(0,127);
	twos_compliment_decode(0,128);
	twos_compliment_decode(0,129);
	twos_compliment_decode(0,255);
	twos_compliment_decode(128,0);
	twos_compliment_decode(128,127);
	twos_compliment_decode(128,128);
	twos_compliment_decode(128,129);*/
	
	//uint8_t temp[8] = {1,2,3,4,5,6,7,8};
	//int8_t *data = temp;

	uint8_t sendCAN = 0;
	int8_t speed = 0;
	int8_t direction = 0.1;

	pi_controller_init(0.5,1,T_UPDATE);
	


	//motor_calibrate(100);
	
	
	while(1){
		if(sendCAN){
			//CAN_message_send(data,0);
			//data[7]--;
		}
		
		
		if(CAN_data_receive()){
			//printf("CAN value = %i", CAN_message_receive()->data[0]);
			speed =  (int8_t)  CAN_message_receive()->data[0];
			
			if(speed < 0 ){
				direction = 1;
				speed = direction * speed;
			}else if(speed > 0){
				direction = -1;
				speed = direction * speed;
			}else{
				speed = 0;
				direction = 0;
			}
			
			//printf("E_r\t%i\n", encoder_read());
				
			//_delay_ms(1000);
			//sound_play_effect(1);
			
			//servo_set(CAN_message_receive()->data[0]);
		}
		/*
		for(uint8_t i = 0; i< 0xff; i++){
			speed = i;
			_delay_ms(10);
			motor_set_speed(speed);
		}
		*/
		//printf("A");
		
		//read_adc();
		//printf("IR 	%i\n", ADCH);
		//encoder_read();
		pi_controller_update(speed);
		motor_set_direction(direction);
		
		//_delay_ms(1000);
		
		//motor_set_speed(speed);
		//_delay_ms(1000);
		
		
		//speed += 1;
		//motor_set_speed(0);
		//_delay_ms(50);
		
		
	}
    return 0;
}

void init_all(void){
	
	cli();
	init_UART();
	
	CAN_initialize();
	TWI_Master_Initialise();
	motor_init();
	servo_init();
	
	#if UART_ENABLE
		init_UART();
		printf("Program initialized\n");
	#endif
	sei();
}
