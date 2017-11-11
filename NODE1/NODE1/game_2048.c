/*
 * game_2048.c
 *
 * Created: 07.11.2017 18:12:06
 *  Author: pamarton
 */ 

#include "game_2048.h"
#include "../../common_library/uart.h"
#include "SRAM.h"
#include "input_conversion.h"
//#include "font.h"
volatile char *ext_ram_adr = (char *) 0x1800;
#define GRID_SIZE 4
#define NUMBER_OF_BOXES GRID_SIZE*GRID_SIZE
#define BOX_SIZE 16


char boxes[GRID_SIZE][GRID_SIZE] = {{' ',' ',' ',' '},
									{' ',' ',' ',' '},
									{' ',' ',' ',' '},
									{' ','A',' ','D'}};


void main_2048(void){
	render_boxes();
	
	game_2048();
	
	
}

int8_t x_reading = 0;
int8_t y_reading = 0;

void game_2048(void){
	while(1){
		render_boxes();
		
		//JOYSTICK INPUT
		
		
		while((x_reading < 70) && (x_reading > -70) && (y_reading < 70) && (y_reading > -70)){
			x_reading = read_control_input('X');
			y_reading = read_control_input('Y');
			if((x_reading > 70 || x_reading < -70) && (y_reading > 70 || y_reading < -70)){//prevent inputs in wierd directions
				x_reading = 0;
				y_reading = 0;
			}
		}
		x_reading = x_reading/51;
		y_reading = y_reading/51;
		
		printf("%i %i\n",x_reading,y_reading);
		
		//ANIMASJON
		
		//MECHANICS
		/*
		for (uint8_t rep = 0; rep < GRID_SIZE; rep++)
		{
			if(x_reading == -1){
				for (uint8_t a = 0; a < GRID_SIZE; a++){
					for (uint8_t b = 0; b < GRID_SIZE-1; b++)
					{
						printf("%c",boxes[a][b]);
						if (boxes[a][b] == ' ')
						{
							boxes[a][b] = boxes[a][b+1];
							boxes[a][b+1] = ' ';
						}
						else if(boxes[a][b] == boxes[a][b+1]){
							boxes[a][b]++;
							boxes[a][b+1] = ' ';
						}
					}
				}
			}else if (x_reading == 1){
				for (uint8_t a = 0; a < GRID_SIZE; a++){
					for (uint8_t b = GRID_SIZE-1; b >= 1; b--)
					{
						printf("%c",boxes[a][b]);
						if (boxes[a][b] == ' ')
						{
							boxes[a][b] = boxes[a][b-1];
							boxes[a][b-1] = ' ';
						}
						else if(boxes[a][b] == boxes[a][b-1]){
							boxes[a][b]++;
							boxes[a][b-1] = ' ';
						}
					}
				}
			}
		}*/
		for (uint8_t a = 0; a < GRID_SIZE; a++){
			for (uint8_t b = 0; b < GRID_SIZE-1; b++)
			{
				if (boxes[a][b+1] == ' ')
				{
					boxes[a][b] = boxes[a][b+1];
					boxes[a][b] = ' ';
				}
			}
		}
		
		
		
		timer_delay(100);
		
		
	}
}

void render_boxes(void){
	printf("\n");
	printf("%c\t%c\t%c\t%c\n",boxes[0][0],	boxes[0][1],	boxes[0][2],	boxes[0][3]);
	printf("%c\t%c\t%c\t%c\n",boxes[1][0],	boxes[1][1],	boxes[1][2],	boxes[1][3]);
	printf("%c\t%c\t%c\t%c\n",boxes[2][0],	boxes[2][1],	boxes[2][2],	boxes[2][3]);
	printf("%c\t%c\t%c\t%c\n",boxes[3][0],	boxes[3][1],	boxes[3][2],	boxes[3][3]);
	sram_init();
	for (uint8_t a = 0; a < GRID_SIZE; a++)
	{
		for (uint8_t b = 0; b < GRID_SIZE; b++)
		{
			sram_render_box(a,b,(boxes[b][a]),BOX_SIZE);
		}
	}
	sram_update_oled();
}

