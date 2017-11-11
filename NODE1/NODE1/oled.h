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
void oled_goto_line(uint8_t line);
void oled_goto_column(uint8_t column);
void oled_clear_line(uint8_t line);

#endif /* OLED_H_ */