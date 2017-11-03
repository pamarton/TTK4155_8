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
#include	"pwm.h"

void init_all(void);

int main(void){
	init_all();
	
	
	
	servo_init(20);
	servo_set(-100);
	_delay_ms(100);

	while(1){
		for (int i = -100; i <= 100; i++)
		{
			servo_set(i);
			_delay_ms(10);
		}
		for (int i = 100; i >= -100; i--)
		{
			servo_set(i);
			_delay_ms(10);
		}
	}
	
	
	int8_t temp[8] = {1,2,3,4,5,6,7,8};
	int8_t *data = temp;

	uint8_t sendCAN = 0;

	while(1){
		if(sendCAN){
			data[7]++;
			CAN_message_send(data,0);
			_delay_ms(-10);
		}
		
		
		if(~sendCAN){
			CAN_data_receive();
		}
	}
	
	
    return 0;
}

void init_all(void){
	
	cli();
	init_UART();
	CAN_initialize();
	
	
	
	printf("Program initialized\n");
	sei();
}
