/*
 * solenoid.c
 *
 * Created: 20.11.2017 14:47:53
 *  Author: dirkpr
 */ 

#include "solenoid.h"
#include "timer.h"

uint16_t solenoid_loaded;

void solenoid_init(void){
	SOLENOID_DDR |= (1 << SOLENOID_PIN);
	solenoid_loaded = 0;
}

void solenoid_disable(void){
	SOLENOID_PORT |= (1<< SOLENOID_PIN);
}

void solenoid_enable(void){
	SOLENOID_PORT &= ~(1<< SOLENOID_PIN);
}

void solenoid_fire(void){
	if (solenoid_reloaded())
	{
		solenoid_enable();
		_delay_ms(20);
		solenoid_disable();
		solenoid_loaded = timestamp(SOLENOID_REALOAD);
	}
}

uint8_t solenoid_reloaded(void){
	if (check_timestamp(solenoid_loaded))
	{
		return 1;
	}
	return 0;
}

