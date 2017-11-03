/*
 * motor_controller.h
 *
 * Created: 02.11.2017 16:38:24
 *  Author: pamarton
 */ 


#ifndef MOTOR_CONTROLLER_H_
#define MOTOR_CONTROLLER_H_

#include "pwm.h"

void servo_init(void);
int servo_set(int value);

#endif /* MOTOR_CONTROLLER_H_ */