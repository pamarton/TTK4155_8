/*
 * motor_controller.h
 *
 * Created: 02.11.2017 16:38:24
 *  Author: pamarton
 */ 


#ifndef MOTOR_CONTROLLER_H_
#define MOTOR_CONTROLLER_H_


#include "pwm.h"

#define PWM_PERIOD 20 // Period of pwm-signal in [ms]
#define PULSE_WIDTH_MAX 2.1 // Maximum pulse-width of pwm-signal in [ms]
#define PULSE_WIDTH_MIN 0.9 // Minimum pulse-width of pwm-signal in [ms]
#define CONTROL_INPUT_MAX 100 // Maximum control-input in [%]
#define CONTROL_INPUT_MIN -100 // Minimum control-input in [%]

void servo_init(void);
int servo_set(int8_t value);

#endif /* MOTOR_CONTROLLER_H_ */