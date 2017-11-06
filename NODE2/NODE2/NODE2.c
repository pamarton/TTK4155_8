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



void init_all(void);

int main(void){
	init_all();
	
	printf("Hallo\n");
	
	IR_init();
	
	
	servo_init();
	
	int8_t temp[8] = {1,2,3,4,5,6,7,8};
	int8_t *data = temp;

	uint8_t sendCAN = 0;
	 while(1){
		if(sendCAN){
			CAN_message_send(data,0);
			data[7]--;
		}
		if(CAN_data_receive()){
			servo_set(CAN_message_receive()->data[0]);
		 }
		// read_adc();
		printf("Value of IR is:	%i\n", ADCH);
		_delay_ms(500);
	 }
    return 0;
}

void init_all(void){
	
	cli();
	init_UART();
	CAN_initialize();
	
	
	#if UART_ENABLE
		printf("Program initialized\n");
	#endif
	sei();
}
