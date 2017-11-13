/*
 * sounds.c
 *
 * Created: 13.11.2017 08:53:32
 *  Author: pamarton
 */ 

#include "sounds.h"

void sound_toggle(uint8_t on_off){
	if(on_off == 1){
		DDRH |= (1 << PH3);
		}else if (on_off == 0){
		DDRH &= ~(1 << PH3);
	}
}


void sound_play_effect(uint8_t effect){
	if(effect == 0){
		sound_toggle(0);
	}else if(effect == 1){
		buzzer_set_freq(440);
		_delay_ms(100);
		buzzer_set_freq(311);
		_delay_ms(100);
	}
	
	
}