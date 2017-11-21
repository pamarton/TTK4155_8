/*
 * game.c
 *
 * Created: 21.11.2017 08:44:21
 *  Author: dirkpr
 */ 

#include "game.h"
#include "pi_controller.h"
uint8_t solenoid_charge;

int joystick_x;
int	joystick_y;
float rel_pos_ref;
uint8_t	joystick_button;
uint8_t	button_l;
uint8_t	button_r;
uint8_t	slider_pos;
uint8_t use_slider;

uint16_t score_count;

uint8_t joystick_min;
uint8_t joystick_max;
uint8_t slider_min;
uint8_t slider_max;


uint8_t joystick_sensitivity;
	
void game_init(uint8_t* params){
	
	solenoid_charge = 0;
	joystick_x = 0;
	joystick_y	= 0;
	joystick_button = 0;
	button_l = 0;
	button_r = 0;
	slider_pos = 0;
	rel_pos_ref = 0;
	
	joystick_min = params[0];
	joystick_max = params[1];
	joystick_sensitivity = params[2];
	slider_min   = params[3];
	slider_max   = params[4];
	use_slider   = params[5];
}

uint16_t game_play(void){
	score_count = 0;
	uint8_t game_on = 1;
	
	float IR_max = read_adc();
	
	while(game_on){
		// Get input values
		if(CAN_data_receive()){
			//data = CAN_message_receive()->data;
			//id   = CAN_message_receive()->id;
			if(CAN_message_receive()->id == CAN_GAME_CONTROL_ID){
				joystick_x		= CAN_message_receive()->data[0];
				joystick_y		= CAN_message_receive()->data[1];
				joystick_button = CAN_message_receive()->data[2];
				button_l		= CAN_message_receive()->data[3];
				button_r		= CAN_message_receive()->data[4];
				slider_pos		= CAN_message_receive()->data[5];
				//slider_r		= CAN_message_receive()->data[6];
			}
		}

		// Get desired motor position
		if(~use_slider && ~joystick_button){ //use joystick to increment position
			rel_pos_ref += joystick_sensitivity * (joystick_x / joystick_max);
		}else{ // use slider to use absolute position
			rel_pos_ref = slider_min + slider_pos*(slider_max - slider_min);
		}
		
		// Update position.
		pi_controller_update(rel_pos_ref);

		// When joystick button is pressed, keep motor position constant and use joystick to control servo.
		if(joystick_button){
			servo_set(joystick_x);
			solenoid_charge = 1;
		}
		
		// Shoot on button release of joystick-button.
		if(~joystick_button && solenoid_charge){
			solenoid_enable();
			_delay_ms(20);
			solenoid_disable();
			solenoid_charge = 0;
		}
		
		
		// Check if IR-beam is interrupted.
		if(read_adc() < IR_interrupt_factor*IR_max){
			game_on = 0;
		}
	}
	return score_count;
}