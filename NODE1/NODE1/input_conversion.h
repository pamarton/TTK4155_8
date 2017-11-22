/*
 * input_conversion.h
 *
 * Created: 21.09.2017 15:42:44
 *  Author: pamarton
 */ 


#ifndef INPUT_CONVERSION_H_
#define INPUT_CONVERSION_H_

//------------------------------------------//
//	INCLUDES								//
//------------------------------------------//

#include "../../common_library/uart.h"
#include "adc.h"

//------------------------------------------//
//	DEFINITIONS								//
//------------------------------------------//

#define SIGNAL_MAX 0xff //255 in decimal
#define SIGNAL_MIN 0x00 //0 in decimal
#define JOYSTICK_MAX 100
#define SLIDER_MAX 100
#define SLIDER_MIN 0
#define JOYSTICK_MIN -JOYSTICK_MAX
#define RESOLUTION 10

#define ADC_CHANNEL_X 1		// Joystick LEFT/RIGHT
#define ADC_CHANNEL_Y 2		// Joystick UP/DOWN 
#define ADC_CHANNEL_L 3		// left slider
#define ADC_CHANNEL_R 4		// right slider

//------------------------------------------//
//	FUNCTIONS								//
//------------------------------------------//

int signal_to_range(int signal, int signal_min, int signal_max, int output_min, int output_max, int calibrate, int reference, int step);
void calibrate_joystick(void);
void initialize_control_input(void);
int read_control_input(char channel);
#endif /* INPUT_CONVERSION_H_ */