/*
 * NODE1.c
 *
 * Created: 30.10.2017 16:50:33
 *  Author: pamarton
 */ 


#include	<avr/io.h>
#include	"../../common_library/common.h"
#include	<avr/interrupt.h>
#include	"../../common_library/can.h"
#include	<util/delay.h>
#include	"menu.h"
#include	"timer.h"

void init_all(void);
void bootscreen(void);
#include "game_2048.h"
#include "scoreboard.h"


#include "../../common_library/uart.h" //remove
int main(void)
{
	//scoreboard_init();
	init_all();
	//http: //www.dreamdealer.nl/tutorials/connecting_a_1602a_lcd_display_and_a_light_sensor_to_arduino_uno.html
	//sram_update_oled();
	
	//scoreboard_command(1);
	//_delay_ms(1000);
	
	
	
	//timer_delay(500);
	
	//sram_init();
	//main_2048();
	
	
	uint8_t temp[8] = {1,2,3,4,5,6,7,8};
	uint8_t *data = temp;
	
	
	/* HIGHSCORE, LEAVE AS IS!
	char a[16];
	for (uint8_t b = 0; b < 8; b++)
	{
		printf("S0R");
		printf("%c",'0'+b);
		sram_goto_line(b);
		for (unsigned int i = 0; i< 12;i++)
		{
			a[i] = recieve_UART();
		}
		sram_write_string(a);
	}
	while (1)
	{
		sram_update_oled();
	}*/
	
	
	
	
	
	
	
    uint8_t sendCAN = 1;
	int8_t controller = 0;
    while(1){
	    if(sendCAN){
			
			controller = read_control_input('X');
			
			if(controller != data[0]){
				data[0] = controller;
				//printf("Sending Can: \t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%i\n", (int8_t)data[0], (int8_t)data[1], (int8_t)data[2], (int8_t)data[3], (int8_t)data[4], (int8_t)data[5], (int8_t)data[6], (int8_t)data[7]);
				CAN_message_send(data,0);
			}
	    }else if(~sendCAN){
			//if (CAN_data_receive())
			//{
			//	
			//}		    
	    }
		menu_update();
    }
    
}

void init_all(void){
	cli();
	init_UART();
	#if UART_ENABLE
	printf("LOADING g17_%s %s %s\nINITIALIZING...\n\nUART successfully initialized\n\n", VERSION,__DATE__,__TIME__);
	#endif
	BIT_ON(MCUCR,SRE); //SET THIS IN SOME INITALIZE FUNBCTION
	BIT_ON(SFIOR,XMM2);//HVORFOR GJORDE DE DETTE I OLED?

	oled_ini();
	sram_init();
	bootscreen();
	initialize_menu();
	
	initialize_control_input();
	
	initalize_interrupts();
	
	initialize_timer(FPS);//60 FPS
	
	CAN_initialize();
	
	sei();//enable interrupts
}

#include <stdlib.h>
void SRAM_test(void)//CAN BE REMOVED, IN CASE OF LOW STORAGE
{

	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	printf("Starting SRAM test...\n");
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n", i,	retreived_value, some_value);
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n",i, retreived_value, some_value);
			retrieval_errors++;
		}
	}
	printf("SRAM test completed with\n%4d errors in write phase and\n%4d errors	in retrieval phase\n\n", write_errors, retrieval_errors);
}



void bootscreen(void){
	int x = 24;
	int y = 61;
	
	sram_set_point(x-15,y);
	sram_draw_line(x-15,y-60);//letter G
	sram_draw_line(x+15,y-60);
	sram_draw_line(x+15,y-48);
	sram_draw_line(x-6,y-48);
	sram_draw_line(x-6,y-12);
	sram_draw_line(x+6,y-12);
	sram_draw_line(x+6,y-36);
	sram_draw_line(x+15,y-36);
	sram_draw_line(x+15,y);
	sram_draw_line(x-15,y);//end of letter
	
	x += 40;
	sram_draw_rectangle(x-5,y,x+5,y-60);

	x += 40;
	sram_set_point(x+15,y-60);//number 7
	sram_draw_line(x-15,y-60);
	sram_draw_line(x-12,y-48);
	sram_draw_line(x+6,y-48);
	sram_draw_line(x+3,y-36);
	sram_draw_line(x-9,y-36);
	sram_draw_line(x-6,y-24);
	sram_draw_line(x,y-24);
	sram_draw_line(x-3,y-12);
	sram_draw_line(x,y);
	sram_draw_line(x+15,y-60);//end of number
	
	sram_update_oled();
}