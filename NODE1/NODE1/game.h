/*
 * game.h
 *
 * Created: 21/11/2017 15:56:26
 *  Author: Amund Marton
 */ 


#ifndef GAME_H_
#define GAME_H_

#include "../../common_library/common.h"
#include "../../common_library/uart.h"
#include "../../common_library/can.h"
#include "input_conversion.h"
#include "buttons.h"
#include "sram.h"

void play_game(void);
void update_score(void);
void game_send_data(void);
void game_init(uint8_t controller_type, uint16_t sensitivity);

#endif /* GAME_H_ */