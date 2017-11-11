/*
 SRAM.c
 *
 * Created: 09.11.2017 17:45:57
 *  Author: pamarton
 */ 

#include "SRAM.h"
#include "font.h"

volatile char *ext_ram = (char *) 0x1800;
uint8_t page,col;

void sram_init(void){//empty sram and reset the possition, then empty the screen
	for(uint8_t r = 0; r < 8; r++){
		for(uint8_t k = 0; k < 128; k++){
			ext_ram[r*128+k] = 0b00000000;
		}
	}
	page = 0;
	col = 0;
	sram_update_oled();
}

uint8_t sram_write_char(char letter){//function that writes a char to the sram, and changes line if \n is used
	if (letter == '\n'){
		page = (page+1)%8;
		col = 0;
		return 1;
	}else if(letter != '\0'){
		for(uint8_t i = 0; i < 8; i++){
			ext_ram[page*128 + col] = pgm_read_byte(&font[letter-' '][i]);
			col++;
		}
		return 1;
	}
	return 0;
	
}

void sram_goto_line(uint8_t line){
	oled_goto_line(line);
	page = line;
}

void sram_goto_column(uint8_t column){
	oled_goto_column(column);
	col = column;
}

void sram_write_string(char letters[]){//function that writes a string to the sram
	uint8_t i = 0;
	while (sram_write_char(letters[i++])){
	}
}

void sram_write_int(int num){//recursive function that writes an integer to the sram
	if(num > 0){
		sram_write_int(num/10);
		sram_write_char('0'+ num%10);
	}
}

void sram_write(uint8_t page, uint8_t col, char data){
	ext_ram[page%8*128 + col%128] = data;
}

uint8_t sram_read(uint8_t page, uint8_t col){
	return ext_ram[page%8*128 + col%128];
}

void sram_write_and(uint8_t page, uint8_t col, char data){
	ext_ram[page%8*128 + col%128] &= data;
}

void sram_write_or(uint8_t page, uint8_t col, char data){
	ext_ram[page%8*128 + col%128] |= data;
}

uint8_t sram_pixel(uint8_t x, uint8_t y){//does this need to be uint_8
	if(x >= 0 && x < 128 && y >= 0 && y < 64){
		sram_write_or((y/8),x,(1<<(y%8)));
		return 1;
	}
	return 0;
}

uint8_t sram_remove_pixel(uint8_t x, uint8_t y){//does this need to be uint_8
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

uint8_t prev_x, prev_y;//temproary storage for the possition, which allows for easier drawing

void sram_draw_line(uint8_t x0, uint8_t y0){
	sram_draw_new_line(prev_x,prev_y,x0,y0);
	sram_set_point(x0,y0);
}

void sram_draw_new_circle(uint8_t x0, uint8_t y0, uint8_t radius){
	for(double x = -radius; x <= radius; x += 0.02){
		//sram_pixel(x+x0,y0-sqrt((pow(radius,2)-pow(x,2))));
		//sram_pixel(-x+x0,y0+sqrt((pow(radius,2)-pow(x,2))));
	}
}

void sram_draw_circle(uint8_t radius){
	sram_draw_new_circle(prev_x,prev_y,radius);
}

void sram_update_oled(void){
	for(uint8_t line = 0; line < 8; line++){//Sends the data from the sram to the oled
		sram_push_line(line);
	}
}

void sram_push_line(uint8_t line){
	sram_goto_line(line);
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
	}
}

uint8_t tempdata[8];//temp storage for the scrolling

void sram_scroll_line(uint8_t line, uint8_t scroll){
	if(scroll > 8){
		scroll -= 8;
		sram_scroll_line(line,scroll);
	}
	sram_scroll_horizontally(line, 0, 127, scroll);
}

void sram_scroll_horizontally(uint8_t line, uint8_t lower_col, uint8_t upper_col, uint8_t scroll){
	for (uint8_t s = 0; s < scroll; s++){
		tempdata[s] = ext_ram[line*128 + s];
	}
	for(uint8_t i = 0; i < 128-scroll; i++){
		ext_ram[line*128 + i] = ext_ram[line*128 + i + scroll];
	}
	for (uint8_t s = 0; s < scroll; s++){
		ext_ram[line*128 + 127-scroll+s] = tempdata[s];
	}
}

void sram_scroll_vertically(uint8_t x, uint8_t y_l, uint8_t y_h, int8_t dir, uint8_t rollower){
	
	uint64_t temp_scroll = 0;;
	for (int y = 7; y >= 0; y--){
		temp_scroll = temp_scroll << 8;
		temp_scroll |= sram_read(y,x);
	}
	
	uint64_t scroll_mask = ~0;//setting up the mask, done in multiple lines just to make it more readable
	scroll_mask = scroll_mask << (S_HEIGHT - 1 -y_h);
	scroll_mask = scroll_mask >> (S_HEIGHT - 1 -y_h + y_l);
	scroll_mask = scroll_mask << (y_l);
	
	
	if(rollower){
		rollower = ((temp_scroll>>(y_h-dir)) & ((1<<dir)-1));
	}
	
	temp_scroll &= scroll_mask;
	
	temp_scroll = temp_scroll << dir;
	
	temp_scroll = (temp_scroll>>y_l | rollower) << y_l;
	
//	temp_scroll = temp_scroll << y_l;
	
	
	
	temp_scroll &= scroll_mask;
	scroll_mask = ~scroll_mask;
	
	uint8_t data = 0;
	for (int y = 0; y < 8; y++){
		data = (uint8_t)scroll_mask;
		sram_write_and(y,x,data);//empties the ram that will be written over (to save the data outside the scope of the scroll)
		scroll_mask = (scroll_mask >> 8);
		
		data = (uint8_t)temp_scroll;
		sram_write_or(y,x,data);//writes over the newly absent places (to save the data outside the scope of the scroll)
		temp_scroll = (temp_scroll >> 8);
	}
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
	col = 8;
	page = 1;
	sram_write_string(letters);
	sram_update_oled();
	//_delay_ms(10000);
}

#include "../../common_library/uart.h"

void sram_render_box(uint8_t column, uint8_t row, char letter, uint8_t box_size){
	sram_draw_rectangle(column*box_size,row*box_size,(column+1)*box_size-1,(row+1)*box_size-1);
	sram_goto_column(column*box_size);
	if(letter != ' '){
		for(uint8_t i = 0; i < 8; i++){
			
			ext_ram[row*2*128 + col+4] |= pgm_read_byte(&font[letter-' '][i])<<4;
			
			ext_ram[(row*2+1)*128 + col+4] |= pgm_read_byte(&font[letter-' '][i])>>4;
			
			col++;
		}
	}
}