/*
 * pi_controller.h
 *
 * Created: 19.11.2017 14:44:26
 *  Author: pamarton
 */ 


#ifndef PI_CONTROLLER_H_
#define PI_CONTROLLER_H_


//------------------------------------------//
//	INCLUDE									//
//------------------------------------------//

#include "../../common_library/common.h"
#include <avr/interrupt.h>
#include "../../common_library/uart.h"
#include "motor.h"
#include "timer.h"


//#define KP 50
//#define KI 300
//Ti = 1
//#define KC 20
#define KP 10
#define KI 2
#define MOTOR_DEADBAND 46

#define SCALING_FACTOR 128

#define MAX_INT INT16_MAX
#define MAX_LONG INT32_MAX
#define MAX_I_TERM (MAX_LONG / 2)

#define COMPENSATE_FRICTION 0

void pi_controller_update(int16_t pos_ref);
void pi_controller_init(int16_t sample_freq_init);
void pi_controller_reset(void);
int16_t estimate_friction(int16_t u, int16_t vel);
void set_speed(uint8_t input_speed);
//void pi_controller_update_reference(int8_t controller_input);
//------------------------------------------//
//	INTERRUPTS								//
//------------------------------------------//



#endif /* PI_CONTROLLER_H_ */