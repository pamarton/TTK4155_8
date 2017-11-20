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

//Enable output at port E3

//------------------------------------------//
//	Definitions								//
//------------------------------------------//

/*
#define SOLENOID_PORT PORTE
#define SOLENOID_PIN PE
#define SOLENOID_DDR DDRB
*/

#define SOLENOID_PORT PORTB
#define SOLENOID_PIN PB7
#define SOLENOID_DDR DDRB


#endif /* SOLENOID_H_ */