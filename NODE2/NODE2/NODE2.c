/*
 * NODE1.c
 *
 * Created: 30.10.2017 16:50:33
 *  Author: pamarton
 */ 


#include	<avr/io.h>
#include	"../../common_library/common.h"
#include	<avr/interrupt.h>
#include	"../../common_library/CAN.h"
void init_all(void);
#include	<util/delay.h>
#include "pwm.h"
int main(void)
{
	
	
	init_all();
	
	pwm_init(20);
	
	pwm_set_pulse_width(1);
	while(1){
		
	}
	
	
	
	
	
	
	
	int8_t temp[8] = {1,2,3,4,5,6,7,8};
    int8_t *data = temp;

    uint8_t sendCAN = 0;

    while(1){
	    if(sendCAN){
		    data[7]++;
		    CAN_message_send(data,0);
			_delay_ms(100);
	    }
	    
	    
	    if(~sendCAN){
		    CAN_data_receive();
	    }
    }
    
}

void init_all(void){
	cli();
	init_UART();
	CAN_initialize();
	printf("Program initialized\n");
	sei();
}
