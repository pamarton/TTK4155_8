/*
 * sounds.h
 *
 * Created: 13.11.2017 08:53:59
 *  Author: pamarton
 */ 


#ifndef SOUNDS_H_
#define SOUNDS_H_

#include "buzzer.h"
#include <util/delay.h>

void sound_toggle(uint8_t on_off);

void sound_play_effect(uint8_t effect);

#endif /* SOUNDS_H_ */