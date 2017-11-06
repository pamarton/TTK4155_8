/*
 * IRsensor.h
 *
 * Created: 06.11.2017 14:25:41
 *  Author: jonasgl
 */ 
#ifndef IRSENSOR_H_
#define IRSENSOR_H_


#include <avr/io.h>

void IR_init(void);

uint16_t read_adc(void);





#endif /* IRSENSOR_H_ */