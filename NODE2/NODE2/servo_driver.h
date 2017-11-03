/*
 * motor_controller.h
 *
 * Created: 02.11.2017 16:38:24
 *  Author: pamarton
 */ 


#ifndef MOTOR_CONTROLLER_H_
#define MOTOR_CONTROLLER_H_


#include "pwm.h"

#define PULSE_WIDTH_MAX 2.1 //MS
#define PULSE_WIDTH_MIN 0.9 //MS
#define CONTROL_INPUT_MAX 100
#define CONTROL_INPUT_MIN -100

void servo_init(void);
int servo_set(int value);

#endif /* MOTOR_CONTROLLER_H_ */