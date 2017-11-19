/*
 * motor.h
 *
 * Created: 16.11.2017 09:36:59
 *  Author: pamarton
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include <avr/io.h>

// MJ1 header pins on arduino shield
#define OEN PH5
#define RSTN PH6
#define SEL PH3
#define EN  PH4
#define DIR PH1

#define MOTOR_PORT PORTH
#define MOTOR_PIN PORTH
#define MOTOR_DDR DDRH

#define ENCODER_PORT PORTK
#define ENCODER_PIN PINK
#define ENCODER_DDR DDRK

#define ADC_ADDRESS 0x50
#define ADC_DAC0_ADDRESS 0x00
#define ADC_DAC1_ADDRESS 0x01

void motor_init(void);
void motor_set_direction(int8_t direction);
int16_t encoder_read(void);
void motor_set_speed(uint8_t speed);
void encoder_reset(void);

int16_t e_r(void);


#endif /* MOTOR_H_ */