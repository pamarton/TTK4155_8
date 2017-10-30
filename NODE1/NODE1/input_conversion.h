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
#define RANGE_MAX 100
#define RANGE_MIN -RANGE_MAX
#define RESOLUTION 10

//------------------------------------------//
//	FUNCTIONS								//
//------------------------------------------//

int signal_to_range(int signal, int signal_min, int signal_max, int output_min, int output_max, int calibrate, int reference, int step);
void calibrate_joystick(void);
void initialize_control_input(void);
int read_control_input(char channel);
#endif /* INPUT_CONVERSION_H_ */