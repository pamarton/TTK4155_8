/*
 * oled.h
 *
 * Created: 28.09.2017 16:23:56
 *  Author: dirkpr
 */ 


#ifndef OLED_H_
#define OLED_H_

//------------------------------------------//
//	INCLUDES									//
//------------------------------------------//

#include <avr/io.h>

//------------------------------------------//
//	FUNCTIONS								//
//------------------------------------------//

void write_c(uint8_t cmd);
void write_d(uint8_t data);

void oled_home(void);
void oled_ini(void);
void oled_reset(void);
void oled_goto_line(unsigned int line);
void oled_goto_column(unsigned int column);
void oled_clear_line(unsigned int line);
/*
void oled_print(char * letters);
void oled_print_effect(char * letters, char effect);
int oled_print_char(char letter);
int oled_print_char_effect(char letter, char effect);
void oled_reset(void);

*/

void sram_scroll_data(uint8_t line, uint8_t scroll);
void sram_clear_line(uint8_t line);
void sram_init(void);//initialize the sram
void sram_write(int rad,int kol, char data);//overwrites the data in the sram indiscriminately
void sram_write_and(int rad,int kol, char data);//compares the existing data in the sram and only keeps the pixels they both have
void sram_write_or(int rad,int kol, char data);//writes to the sram, "pastes" on top instead of overwriting
void sram_push(void);//send the data from the sram to the oled
void sram_push_line(uint8_t line);//send a line of data from the sram to the oled
uint8_t sram_pixel(int x, int y);//sets 1 pixel in the sram
void sram_draw_line(int x0, int y0, int x1, int y1);//draws a line in the sram
uint8_t sram_write_char(char letter);//writes a char in the sram
void sram_write_int(int num);//writes a number to the sram (recursive)
void sram_write_string(char letters[]);//writes a string to the sram. \n is next line
void sram_draw_circle(int x0, int y0, int radius);//draws a circle in the sram
void sram_draw_triangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);//draws a triangle in the sram
void sram_draw_rectangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);//draws a rectangle in the sram

#endif /* OLED_H_ */