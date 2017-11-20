/*
 * solenoid.h
 *
 * Created: 20.11.2017 14:48:08
 *  Author: dirkpr
 */ 


#ifndef SOLENOID_H_
#define SOLENOID_H_

//------------------------------------------//
//	INCLUDE									//
//------------------------------------------//
#include "../../common_library/common.h"
#include	<util/delay.h>
#include "../../common_library/uart.h"

//------------------------------------------//
//	Definitions								//
//------------------------------------------//

#define SOLENOID_PORT PORTB
#define SOLENOID_PIN PB7
#define SOLENOID_DDR DDRB


void solenoid_init(void);
void solenoid_disable(void);
void solenoid_enable(void);




#endif /* SOLENOID_H_ */