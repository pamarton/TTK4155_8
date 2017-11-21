/*
 * uart_exchange.h
 *
 * Created: 21.11.2017 02:33:57
 *  Author: pamarton
 */ 


#ifndef UART_EXCHANGE_H_
#define UART_EXCHANGE_H_

//macros for the commands
#define PLAY_MUSIC "R"
#define PAUSE_MUSIC "P"
#define SELECT_MUSIC "M"
#define SELECT_SCOREBOARD "S"
#define SCOREBOARD_READ "R"
#define SCOREBOARD_WRITE "W"

//macros for the songs
#define SONG_MORTAL_COMBAT 1
#define SONG_MARIO 2
#define SOUND_EFFECT_1 3
#define SOUND_EFFECT_2 4
#define SOUND_EFFECT_3 5
#define SONG_SALIEL 9

//macros for the files 
#define SCOREBOARD_FLAPPY_BIRD 0
#define	SCOREBOARD_MAIN_GAME 8

#include "../../common_library/uart.h"
#include "../../common_library/common.h"
#include "timer.h"
#include "SRAM.h"
#include "input_conversion.h"
#include "button_interrupts.h"

void print_highscore(uint8_t game);
uint8_t decode_hex(char hex);
void play_song(uint8_t song);
void resume_music(void);
void pause_music(void);
void get_scoreboard(uint8_t file, uint8_t pos);

void keyboard_input(uint8_t file, uint16_t score);
#endif /* UART_EXCHANGE_H_ */