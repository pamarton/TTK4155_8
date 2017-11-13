/*
 * oled.c
 *
 * Created: 28.09.2017 16:22:41
 *  Author: dirkpr
 */ 


#include "oled.h"
//#include "font.h"
#include "input_conversion.h"
#include <avr/io.h>


char startram = 0;

volatile char *oled_cmd = (char *) 0x1000; // Start address for the OLED_Command
volatile char *oled_data = (char *) 0x1200; // Start address for the OLED_DATA

uint8_t page,col;

void write_c(uint8_t cmd)
{
	*oled_cmd = cmd;
}


void write_d(uint8_t data)
{
	*oled_data = data;
}

void oled_refresh(){
	
}
void oled_ini(void)
{
	//Enable the external memory interface
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
	
	write_c(0xae);        //display  off
	write_c(0xa1);        //segment  remap
	write_c(0xda);        //common  pads  hardware:  alternative
	write_c(0x12);
	write_c(0xc8);        //common output scan direction:com63~com0
	write_c(0xa8);        //multiplex  ration  mode:63
	write_c(0x3f);
	write_c(0xd5);        //displayc divide ratio/osc. freq. mode
	write_c(0x80);
	write_c(0x81);        //contrast  control
	write_c(0x50);
	write_c(0xd9);        //set  pre-charge  period
	write_c(0x21);
	write_c(0x20);        //Set  Memory  Addressing  Mode
	write_c(0x00);
	write_c(0xdb);        //VCOM  deselect  level  mode
	write_c(0x30);
	write_c(0xad);        //master  configuration
	write_c(0x00);
	write_c(0xa4);        //out  follows  RAM  content
	write_c(0xa6);        //set  normal  display
	write_c(0xaf);        //  display  on
	
	oled_reset();
	oled_home();
}


void oled_reset(void)
{		
	for(uint8_t i = 0; i < 8;i++){
		oled_clear_line(i);
	}
}

void oled_home(void)
{
	page = 0;
	col = 0;
	
	
	write_c(0x21); // set column (left to right)
	write_c(0x00); // column start
	write_c(0x7f); // column end
	
	write_c(0x22); // set row (top to bottom)
	write_c(0x00); // row start
	write_c(0x7); // row end
	
	//write_c(0x00);
	//write_c(0x10);
}



void oled_goto_line(uint8_t line){
	oled_home();
	page = line;
	if(line%8){
		write_c(0x00);
		write_c(0x10);
		write_c(0xB0 | line);
	}
}


void oled_goto_column(uint8_t column){
	col = column%128;
}
void oled_pos(uint8_t row,uint8_t column){
	oled_goto_column(column);
	oled_goto_line(row);
}

void oled_clear_line(uint8_t line){
	oled_goto_line(line);
	if(line < 8){
		for(uint8_t i = 0; i < 128; i++){
			write_d(0b00000000);
		}
	}
}