/*
 * game.c
 *
 * Created: 21/11/2017 15:56:43
 *  Author: Amund Marton
 */ 
#include "game.h"


uint16_t gamescore = 0;

int8_t X_reading = 0;
int8_t Y_reading = 0;
uint8_t L_slider = 0;
uint8_t R_slider = 0;
uint8_t Game_Over = 0;
uint8_t J_btn = 0;
uint8_t L_btn = 0;
uint8_t R_btn = 0;
uint8_t data_to_send[8];

uint8_t send_can = 1;

int16_t temp_reading;

void play_game(void){
	game_init(CONTROLLER_TYPE_JOYSTICK_ONLY,10);
	Game_Over = 0;
	sram_init();
	sram_goto_line(0);
	sram_write_string("SQUASH SIMULATOR");
	sram_update_oled();
	sram_goto_line(3);
	sram_write_string("SCORE: ");
	sram_write_int(gamescore);
	
	
	for (int8_t i = 0; i < 8;  i++)//send all zeros to 
	{
		data_to_send[i] = 0;
	}
	CAN_construct_message(CAN_GAME_CONTROL_ID,8);
	CAN_message_send(data_to_send,0);
	
	
	while(!Game_Over){
		game_send_data();//send data_to_send if it is updated
		
		update_score();//check if the game is over
	}
	while (!button_pressed())//wait for button to be pressed to show the score
	{
		
	}
}
void update_score(void){
	if(CAN_data_receive()){
		if(CAN_message_receive()->id == CAN_GAME_SCORE_ID){
			sram_init();
			sram_goto_line(0);
			sram_write_string("SQUASH SIMULATOR");
			sram_update_oled();
			sram_goto_line(3);
			sram_write_string("SCORE: ");
			sram_write_int(((CAN_message_receive()->data[0]<<8)|CAN_message_receive()->data[1]));
			sram_update_oled();
			Game_Over = 1;
		}
	}
}


void game_send_data(void){//sends a can message if there is an update
	send_can = 0;
	temp_reading = read_control_input('X');
	if (temp_reading != X_reading)
	{
		X_reading = temp_reading;
		data_to_send[0] = temp_reading;
		send_can = 1;
	}
	temp_reading = read_control_input('Y');
	if (temp_reading != Y_reading)
	{
		Y_reading = temp_reading;
		data_to_send[1] = temp_reading;		
		send_can = 1;
	}
	temp_reading = joystick_pressed();
	if (temp_reading != J_btn)
	{
		J_btn = temp_reading;
		data_to_send[2] = temp_reading;
		send_can = 1;
	}
	temp_reading = check_flag_left();
	if (temp_reading != L_btn)
	{
		L_btn = temp_reading;
		data_to_send[3] = temp_reading;
		send_can = 1;
	}
	temp_reading = check_flag_right();
	if (temp_reading != R_btn)
	{
		R_btn = temp_reading;
		data_to_send[4] = temp_reading;
		send_can = 1;
	}
	temp_reading = read_control_input('L');
	if (temp_reading != L_slider)
	{
		L_slider = temp_reading;
		data_to_send[5] = temp_reading;
		send_can = 1;
	}
	if (send_can)
	{
		CAN_construct_message(CAN_GAME_CONTROL_ID,8);
		CAN_message_send(data_to_send,0);
	}
}





void game_init(uint8_t controller_type, uint16_t sensitivity){
	data_to_send[0] = (uint8_t)JOYSTICK_MIN;
	data_to_send[1] = (uint8_t)JOYSTICK_MAX;
	data_to_send[2] = (uint8_t)(sensitivity >> 8);
	data_to_send[3] = (uint8_t)sensitivity;
	data_to_send[4] = (uint8_t)SLIDER_MIN;
	data_to_send[5] = (uint8_t)SLIDER_MAX;
	data_to_send[6] = (uint8_t)controller_type;
	
	
	X_reading = read_control_input('X');
	Y_reading = read_control_input('Y');
	L_slider = read_control_input('L');
	R_slider = read_control_input('R');
	
	J_btn = joystick_pressed();
	L_btn = check_flag_left();
	R_btn = check_flag_right();
		
	Game_Over = 0;
	
	CAN_construct_message(CAN_GAME_PARAMS_ID,CAN_GAME_PARAMS_LENGTH);
	CAN_message_send(data_to_send,0);
}