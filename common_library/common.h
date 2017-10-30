/*
 * common.h
 *
 * Created: 23.10.2017 10:45:15
 *  Author: jonasgl
 */ 
/*
 * common.h
 *
 * Created: 17/10/2017 16:07:16
 *  Author: Amund Marton
 */ 

//------------------------------------------//
//	COMMON INCLUDES							//
//------------------------------------------//

#include <avr/io.h> //constants for the use of the avr

//------------------------------------------//
//	COMMON DEFINITIONS						//
//------------------------------------------//

#ifndef COMMON_H_
#define COMMON_H_

#define VERSION "l6d2" //version name

#ifdef __AVR_ATmega162__//DEFÌNING NODE
	#define NODE 1
#endif
#ifdef __AVR_ATmega2560__
	#define NODE 2
#endif

//------------------------------------------//
//	DEFFINITIONS FOR THE UART				//
//------------------------------------------//

#if NODE == 1
	#define F_CPU 4915200	// clock frequency in Hz
#elif NODE == 2
	#define F_CPU 16000000	// clock frequency in Hz
#endif

//------------------------------------------//
//	DEFINITIONS FOR THE ADC					//
//------------------------------------------//

#define MAX_SIGNAL 0xFF //max value of signals (8 bit)
#define MIN_SIGNAL 0 //min value of signals (8 bit)

//------------------------------------------//
//	DEFINITIONS FOR THE TIMER				//
//------------------------------------------//

#define PRESCALER 1024 //prescaler for timer
#define FPS 60

//------------------------------------------//
//	DEFINITIONS FOR THE CAN					//
//------------------------------------------//

#define CAN_ID 40 //ID of the message (we might change this)
#define CAN_MESSAGE_LENGTH 8//length of can messages

#define RXBnSIDH 0x61
#define RXBnSIDL 0x62
#define RXBnDLC 0x65
#define RXBnDM 0x66



#endif /* COMMON_H_ */