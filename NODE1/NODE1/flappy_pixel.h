/*
 * flappy_pixel.h
 *
 * Created: 03.11.2017 19:40:09
 *  Author: pamarton
 */ 


#ifndef FLAPPY_PIXEL_H_
#define FLAPPY_PIXEL_H_



#include <stdlib.h>//RANDOM FUNCTIOn
#include "oled.h"
#include "button_interrupts.h"
#include "input_conversion.h"
#include "timer.h"
#include "../../common_library/common.h"

int flappy_main(void);
void flappy_loading_screen(void);
void flappy_game(void);

void flappy_render_wall(uint8_t wall, uint8_t pos);
uint8_t flappy_pixel_collision(void);
void flappy_controll();

void flappy_scroll_wall(void);

#endif /* FLAPPY_PIXEL_H_ */