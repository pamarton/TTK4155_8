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

uint8_t page_sram = 0;
uint8_t col_sram = 0;
char edited = 0b00000000;//11111111; //so that the screen updates on first go
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



void oled_goto_line(uint8_t line){
	oled_home();
	page_sram = line;
	if(line%8){
		write_c(0x00);
		write_c(0x10);
		write_c(0xB0 | line);
	}
}


void oled_goto_column(uint8_t column){
	col_sram = column%128;
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


volatile char *ext_ram = (char *) 0x1800;

void sram_write_string(char letters[]){
	uint8_t i = 0;
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
		for(uint8_t i = 0; i < 8; i++){
			ext_ram[page_sram*128 + col_sram] = pgm_read_byte(&font[letter-' '][i]);
			col_sram++;
		}
		return 1;
	}else{
		return 0;
	}
}

void sram_init(void){
	for(uint8_t r = 0; r < 8; r++){
		for(uint8_t k = 0; k < 128; k++){
			ext_ram[r*128+k] = 0b00000000;
		}
	}
	sram_push();
}

void sram_write(uint8_t page, uint8_t col, char data){
	ext_ram[page%8*128 + col%128] = data;
}

void sram_write_and(uint8_t page, uint8_t col, char data){
	ext_ram[page%8*128 + col%128] &= data;
}

void sram_write_or(uint8_t page, uint8_t col, char data){
	ext_ram[page%8*128 + col%128] |= data;
}

uint8_t sram_pixel(uint8_t x, uint8_t y){
	if(x >= 0 && x < 128 && y >= 0 && y < 64){
		sram_write_or((y/8),x,(1<<(y%8)));
		return 1;
	}
	return 0;
}

uint8_t sram_remove_pixel(uint8_t x, uint8_t y){
	if(x >= 0 && x < 128 && y >= 0 && y < 64){
		ext_ram[page%8*128 + col%128] &= ~(1<<(y%8));
		return 1;
	}
	return 0;
}

void sram_draw_new_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1){
	if(x0 > x1){
		uint8_t temp_val = x1;
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
		uint8_t temp_val = y1;
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
uint8_t prev_x, prev_y;

void sram_draw_line(uint8_t x0, uint8_t y0){
	sram_draw_new_line(prev_x,prev_y,x0,y0);
	sram_set_point(x0,y0);
}

void sram_draw_new_circle(uint8_t x0, uint8_t y0, uint8_t radius){
	for(double x = -radius; x <= radius; x += 0.02){
		sram_pixel(x+x0,y0-sqrt((pow(radius,2)-pow(x,2))));
		sram_pixel(-x+x0,y0+sqrt((pow(radius,2)-pow(x,2))));
	}
}


void sram_draw_circle(uint8_t radius){
	sram_draw_new_circle(prev_x,prev_y,radius);
}

void sram_push(void){	
	for(uint8_t line = 0; line < 8; line++){//Sends the data from the sram to the oled
		sram_push_line(line);
	}
}

void sram_push_line(uint8_t line){
	oled_goto_line(line);
	for(uint8_t k = 0; k < 128; k++){
		write_d(ext_ram[line*128 + k]);
	}
}

void sram_clear_line(uint8_t line){
	oled_goto_line(line);
	if(line < 8){
		for(uint8_t i = 0; i < 128; i++){
			ext_ram[line*128 + i] = 0b00000000;
		}
		edited |= 1 << line;
	}
}

uint8_t tempdata[8];
void sram_scroll_line(uint8_t line, uint8_t scroll){
	if(scroll > 8){
		scroll -= 8;
		sram_scroll_line(line,scroll);
	}
	sram_scroll_data(line, 0, 127, scroll);
}

void sram_scroll_data(uint8_t line, uint8_t lower_col, uint8_t upper_col, uint8_t scroll){
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



void sram_set_point(uint8_t x0,uint8_t y0){
	prev_x = x0;
	prev_y = y0;
}

void sram_draw_triangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
	sram_set_point(x0,y0);
	sram_draw_line(x1,y1);
	sram_draw_line(x2,y2);
	sram_draw_line(x0,y0);
}


void sram_draw_rectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1){
	sram_set_point(x0,y0);
	sram_draw_line(x0,y1);
	sram_draw_line(x1,y1);
	sram_draw_line(x1,y0);
	sram_draw_line(x0,y0);
}


void sram_draw_notice_box(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,uint8_t width){
	sram_set_point(x0,y0);
	sram_draw_line(x1-width,y0+width);
	sram_draw_line(x1,y1);
	sram_draw_line(x0+width,y1-width);
	sram_draw_line(x0,y0);
	sram_set_point(x0,y1);
	sram_draw_line(x0+width,y0+width);
	sram_draw_line(x1,y0);
	sram_draw_line(x1-width,y1-width);
	sram_draw_line(x0,y1);
}

void sram_write_improtant_information(char letters[]){
	sram_draw_notice_box(1,1,127,63,6);
	
	col_sram = 8;
	page_sram = 1;
	sram_write_string(letters);
	sram_push();
	_delay_ms(10000);
}