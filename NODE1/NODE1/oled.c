/*
 * oled.c
 *
 * Created: 28.09.2017 16:22:41
 *  Author: dirkpr
 */ 


#include "oled.h"
#include "font.h"
#include "input_conversion.h"
#include <avr/io.h>

unsigned int page_sram = 0;
unsigned int col_sram = 0;
char edited = 0b00000000;//11111111; //so that the screen updates on first go
char startram = 0;

volatile char *oled_cmd = (char *) 0x1000; // Start address for the OLED_Command
volatile char *oled_data = (char *) 0x1200; // Start address for the OLED_DATA

int page,col;

void write_c(uint8_t cmd)
{
	*oled_cmd = cmd;
}


void write_d(uint8_t data)
{
	*oled_data = data;
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
	for(int i = 0; i < 8;i++){
		oled_clear_line(i);
	}
}

void oled_home(void)
{
	page_sram = 0;
	col_sram = 0;
	
	
	write_c(0x21); // set column (left to right)
	write_c(0x00); // column start
	write_c(0x7f); // column end
	
	write_c(0x22); // set row (top to bottom)
	write_c(0x00); // row start
	write_c(0x7); // row end
	
	//write_c(0x00);
	//write_c(0x10);
}



void oled_goto_line(unsigned int line){
	oled_home();
	page_sram = line;
	if(line%8){
		write_c(0x00);
		write_c(0x10);
		write_c(0xB0 | line);
	}
}


void oled_goto_column(unsigned int column){
	col_sram = column%128;
}
void oled_pos(unsigned int row,unsigned int column){
	oled_goto_column(column);
	oled_goto_line(row);
}

void oled_clear_line(unsigned int line){
	oled_goto_line(line);
	if(line < 8){
		for(unsigned int i = 0; i < 128; i++){
			write_d(0b00000000);
		}
	}
}
/*



int oled_print_char(char letter){
	if(letter != '\0'){
		for(unsigned int i = 0; i < 8; i++){
			 * oled_data = pgm_read_byte(&font[letter-' '][i]);
		}
		return 1;
	}else{
		return 0;	
	}
}

int oled_print_char_effect(char letter, char effect){
	if(letter != '\0'){
		for(unsigned int i = 0; i < 8; i++){
			* oled_data = pgm_read_byte(&font[letter-' '][i]) | effect;
		}
		return 1;
	}else{
		return 0;
	}
}

void oled_print(char* letters){
	unsigned int i = 0;
	while (oled_print_char(letters[i++])){
	}
}

void oled_print_effect(char* letters, char effect){
	unsigned int i = 0;
	while (oled_print_char_effect(letters[i++],effect)){
	}
}
*/


#define S_WITDTH 128
#define S_HEIGHT 64
#define WRITE_HEIGHT = S_HEIGHT/8;


//char screendata[8][128][8]; //line, col, data(8)
volatile char *ext_ram = (char *) 0x1800;

void sram_write_string(char letters[]){
	unsigned int i = 0;
	while (sram_write_char(letters[i++])){
	}
}


void sram_write_int(int num){
	if(num > 0){
		sram_write_int(num/10);
		sram_write_char('0'+ num%10);
		
		
	}
}


uint8_t sram_write_char(char letter){
	if (letter == '\n'){
		page_sram = (page_sram+1)%8;
		col_sram = 0;
		return 1;
	}else if(letter != '\0'){
		for(unsigned int i = 0; i < 8; i++){
			ext_ram[page_sram*128 + col_sram] = pgm_read_byte(&font[letter-' '][i]);
			col_sram++;
		}
		return 1;
	}else{
		return 0;
	}
}

void sram_init(void){
	for(unsigned int r = 0; r < 8; r++){
		for(unsigned int k = 0; k < 128; k++){
			ext_ram[r*128+k] = 0b00000000;
		}
	}
	sram_push();
}

void sram_write(int page, int col, char data){
	ext_ram[page%8*128 + col%128] = data;
}

void sram_write_and(int page, int col, char data){
	ext_ram[page%8*128 + col%128] &= data;
}

void sram_write_or(int page, int col, char data){
	ext_ram[page%8*128 + col%128] |= data;
}

uint8_t sram_pixel(int x, int y){
	if(x >= 0 && x < 128 && y >= 0 && y < 64){
		sram_write_or((y/8),x,(1<<(y%8)));
		return 1;
	}
	return 0;
}

void sram_draw_line(int x0, int y0, int x1, int y1){
	if(x0 > x1){
		int temp_val = x1;
		x1 = x0;
		x0 = temp_val;
		temp_val = y1;
		y1 = y0;
		y0 = temp_val;
	}
	double gradient = ((double)(y1-y0)/(double)(x1-x0));	
	
	
	
	if(x0 != x1){//CANT DIVIDE BY ZERO!
		for(double x = x0; x < x1; x += 0.1){
			sram_pixel(x,(gradient*(x-x0))+y0);
		}
	}
	
	if(y0 > y1){//rearranging after size
		int temp_val = y1;
		y1 = y0;
		y0 = temp_val;
	}
	
	
	if(x0 == x1){//f we were to divide by zero, the lines straight uppward woild not be drawn. This fixes that
		for (uint8_t y = y0; y < y1; y++)
		{
			sram_pixel(x0,y);
		}
	}
}

void sram_draw_circle(int x0, int y0, int radius){
	for(double x = -radius; x <= radius; x += 0.02){
		sram_pixel(x+x0,y0-sqrt((pow(radius,2)-pow(x,2))));
		sram_pixel(-x+x0,y0+sqrt((pow(radius,2)-pow(x,2))));
	}
}


void sram_push(void){	
	for(unsigned int line = 0; line < 8; line++){//Sends the data from the sram to the oled
		sram_push_line(line);
	}
}

void sram_push_line(uint8_t line){
	oled_goto_line(line);
	for(unsigned int k = 0; k < 128; k++){
		write_d(ext_ram[line*128 + k]);
	}
}

void sram_clear_line(uint8_t line){
	oled_goto_line(line);
	if(line < 8){
		for(unsigned int i = 0; i < 128; i++){
			ext_ram[line*128 + i] = 0b00000000;
		}
		edited |= 1 << line;
	}
}

uint8_t tempdata[8];
void sram_scroll_data(uint8_t line, uint8_t scroll){
	if(scroll > 8){
		scroll -= 8;
		sram_scroll_data(line,scroll);
	}
	for (uint8_t s = 0; s < scroll; s++){
		tempdata[s] = ext_ram[line*128 + s];
	}
	for(uint8_t i = 0; i < 128-scroll; i++){
		ext_ram[line*128 + i] = ext_ram[line*128 + i + scroll];
	}
	for (uint8_t s = 0; s < scroll; s++){
		ext_ram[line*128 + 127-scroll+s] = tempdata[s];
	}
	edited |= 1 << line;
}



void sram_draw_triangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
	sram_draw_line(x0,y0,x1,y1);
	sram_draw_line(x1,y1,x2,y2);
	sram_draw_line(x2,y2,x0,y0);
}


void sram_draw_rectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1){
	sram_draw_line(x0,y0,x0,y1);
	sram_draw_line(x0,y0,x1,y0);
	sram_draw_line(x0,y1,x1,y1);
	sram_draw_line(x1,y0,x1,y1);
}