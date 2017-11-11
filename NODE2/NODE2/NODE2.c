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


void init_all(void);

int main(void){
	init_all();
	
	printf("Hallo\n");
	//servo_init();
	buzzer_init();
	buzzer_set_freq(300);
	_delay_ms(300);
	buzzer_of();
	
	/*IR_init();*/
	
	
	
	
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
			buzzer_set_freq(300);
			_delay_ms(300);
			buzzer_set_freq(200);
			_delay_ms(300);
			buzzer_set_freq(100);
			_delay_ms(300);
			buzzer_of();
			
			//servo_set(CAN_message_receive()->data[0]);
		 }
		// read_adc();
		//printf("Value of IR is:	%i\n", ADCH);
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
