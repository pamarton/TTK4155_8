/*
 * game_2048.h
 *
 * Created: 07.11.2017 18:12:13
 *  Author: pamarton
 */ 


#ifndef GAME_2048_H_
#define GAME_2048_H_

#include <stdlib.h>//RANDOM FUNCTIOn
#include "oled.h"
#include "button_interrupts.h"
#include "input_conversion.h"
#include "timer.h"
#include "../../common_library/common.h"

void main_2048(void);
void render_boxes(void);
void game_2048(void);
#endif /* GAME_2048_H_ */