/*
 * scoreboard.h
 *
 * Created: 13.11.2017 16:29:34
 *  Author: jonasgl
 */ 


#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#include <avr/io.h>

void scoreboard_write(uint8_t data);

void scoreboard_command(uint8_t command);

void scoreboard_init(void);


#endif /* SCOREBOARD_H_ */