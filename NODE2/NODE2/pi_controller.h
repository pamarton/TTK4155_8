/*
 * pi_controller.h
 *
 * Created: 19.11.2017 14:44:26
 *  Author: pamarton
 */ 


#ifndef PI_CONTROLLER_H_
#define PI_CONTROLLER_H_

//#define Kp 1
//#define Ki 1


//------------------------------------------//
//	INCLUDE									//
//------------------------------------------//

#include "../../common_library/common.h"
#include <avr/interrupt.h>
#include "../../common_library/uart.h"
#include "motor.h"
#include "timer.h"






void pi_controller_update(float vel_ref);
void pi_controller_init(float Ki_init, float Kp_init, float T_Update_init);
//------------------------------------------//
//	INTERRUPTS								//
//------------------------------------------//



#endif /* PI_CONTROLLER_H_ */