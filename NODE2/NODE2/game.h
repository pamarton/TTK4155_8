/*
 * game.h
 *
 * Created: 21.11.2017 08:44:34
 *  Author: dirkpr
 */ 



//------------------------------------------//
//	INCLUDE									//
//------------------------------------------//

#include "../../common_library/common.h"
#include <avr/interrupt.h>
#include "../../common_library/uart.h"
#include <util/delay.h>
#include "../../common_library/can.h"

//------------------------------------------//
//	MACROS									//
//------------------------------------------//
#define IR_interrupt_factor 0.75

//------------------------------------------//
//	DECLARATIONS							//
//------------------------------------------//
uint16_t game_play(void);
void game_init(uint8_t* params);