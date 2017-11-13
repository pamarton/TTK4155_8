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
	
	
	
	//SD_CARD
	//SD_initialize();
	//SD_test();
	
	//END SD_CARD
	
	
	
	
	//uint8_t temp[8] = {1,2,3,4,5,6,7,8};
	//uint8_t *data = temp;

	uint8_t sendCAN = 0;
	while(1){
		if(sendCAN){
			//CAN_message_send(data,0);
			//data[7]--;
		}
		if(CAN_data_receive()){
			//_delay_ms(1000);
			//sound_play_effect(1);
			
			//servo_set(CAN_message_receive()->data[0]);
		}
		read_adc();
		printf("IR 	%i\n", ADCH);
	}
    return 0;
}

void init_all(void){
	
	cli();
	
	CAN_initialize();
	
	
	#if UART_ENABLE
		init_UART();
		printf("Program initialized\n");
	#endif
	sei();
}
