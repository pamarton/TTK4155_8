/*
 * solenoid.c
 *
 * Created: 20.11.2017 14:47:53
 *  Author: dirkpr
 */ 

#include "solenoid.h"


void solenoid_init(void){
	SOLENOID_DDR |= (1 << SOLENOID_PIN);
}

void solenoid_disable(void){
	SOLENOID_PORT |= (1<< SOLENOID_PIN);
}

void solenoid_enable(void){
	SOLENOID_PORT &= ~(1<< SOLENOID_PIN);
}
