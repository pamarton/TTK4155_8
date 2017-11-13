/*
 * SD_card.h
 *
 * Created: 12.11.2017 14:53:53
 *  Author: pamarton
 */ 


#ifndef SD_CARD_H_
#define SD_CARD_H_



//------------------------------------------//
//	INCLUDES								//
//------------------------------------------//
#include <avr/io.h>
#include "../../common_library/common.h"
#include "../../common_library/uart.h" //REMOVE AFTER USE
#include "../../common_library/i_o.h"
#include "../../common_library/MCP2515.h"

//------------------------------------------//
//	PIN DEFINITIONS							//
//------------------------------------------//

#define		SD_SS		PL0
#define		SD_MOSI		PB2
#define		SD_MISO		PB3
#define		SD_SCK		PB1

//------------------------------------------//
//	FUNCTIONS								//
//------------------------------------------//

void SD_initialize(void);
void SD_send(uint64_t data);
uint8_t SD_receive(void);
void SD_select(void);
void SD_deselect(void);
void SD_test(void);

#endif /* SD_CARD_H_ */