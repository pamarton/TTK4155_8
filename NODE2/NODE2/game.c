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
uint8_t controller_type;

uint16_t score_count;

int8_t joystick_min;
int8_t joystick_max;
int8_t slider_min;
int8_t slider_max;
int8_t slider_l;
int8_t slider_r;


uint8_t joystick_sensitivity;
	
void game_init(uint8_t params[CAN_GAME_PARAMS_LENGTH]){
	
	solenoid_charge = 0;
	joystick_x = 0;
	joystick_y	= 0;
	joystick_button = 0;
	button_l = 0;
	button_r = 0;
	slider_l = 0;
	slider_r = 0;
	rel_pos_ref = 0;
	
	joystick_min = (int8_t) params[0];
	joystick_max = (int8_t) params[1];
	joystick_sensitivity = (uint8_t)(params[2] <<8)|params[3];
	//joystick_sensitivity = params[2];
	slider_min   = (int8_t) params[4];
	slider_max   = (int8_t) params[5];
	controller_type   = (uint8_t) params[6];
	
	printf("Game parameters: %i\t%i\t%i\t%i\t%i\t%i\n",joystick_min, joystick_max, joystick_sensitivity, slider_min, slider_max, controller_type);
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
				joystick_x		= (int8_t) CAN_message_receive()->data[0];
				joystick_y		= (int8_t) CAN_message_receive()->data[1];
				joystick_button = (int8_t) CAN_message_receive()->data[2];
				button_l		= (int8_t) CAN_message_receive()->data[3];
				button_r		= (int8_t) CAN_message_receive()->data[4];
				slider_l		= (int8_t) CAN_message_receive()->data[5];
				slider_r		= (int8_t) CAN_message_receive()->data[6];
				
				printf("Game input: \t%i\t%i\t%i\t%i\t%i\t%i\t%i\n",joystick_x, joystick_y, joystick_button, button_l, button_r, slider_l, slider_r);
			}
		}

		// Get desired motor position
		if(controller_type == CONTROLLER_TYPE_JOYSTICK_ONLY && ~joystick_button){ //use joystick to increment position
			rel_pos_ref += joystick_sensitivity * (joystick_x / joystick_max);
		}else{ // use slider to use absolute position
			rel_pos_ref = slider_min + slider_pos*(slider_max - slider_min);
		}
		
		// Update position.
		pi_controller_update(rel_pos_ref);

		// When joystick button is pressed, keep motor position constant and use joystick to control servo.
		if(joystick_button){
			servo_set(joystick_x);
			joystick_button = 0;//solenoid_charge = 1;
			printf("RELOADING!\n");
		}
		
		// Shoot on button release of joystick-button.
		if(button_r){//if(~joystick_button && solenoid_charge){
			solenoid_fire();
			printf("FIRE!\n");
		}
		
		
		// Check if IR-beam is interrupted.
		if(read_adc() < IR_interrupt_factor*IR_max){
			game_on = 0;
		}
	}
	return score_count;
}