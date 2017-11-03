/*
 * menu.c
 *
 * Created: 28.09.2017 20:18:00
 *  Author: dirkpr
 */ 
#include "menu.h"

menu* current_head;
menu* current_selected;

uint8_t right_button_flag = 0;
uint8_t left_button_flag = 0;

void setup_menu(menu * new_menu, menu * ptr_sib_down, menu * ptr_parent, menu * ptr_child, int n_sib, PGM_P title){
	//new_menu->ptr_self = new_menu;
	//new_menu->ptr_sib_up = ptr_sib_up;
	new_menu->ptr_sib_down = ptr_sib_down;
	new_menu->ptr_child = ptr_child;
	new_menu->ptr_parent = ptr_parent;
	
	new_menu->title = title;
	new_menu->n_sib = n_sib;
}

	
const char mainmenu_entry_0[] PROGMEM = "Start";
const char mainmenu_entry_1[] PROGMEM = "Highscore";
const char mainmenu_entry_2[] PROGMEM = "Debug";
const char mainmenu_entry_3[] PROGMEM = "Options";
const char highscore_entry_0[] PROGMEM = "Highscore:";
const char highscore_entry_1[] PROGMEM = "2nd";
const char highscore_entry_2[] PROGMEM = "3rd";
const char option_entry_0[] PROGMEM = "Music";
const char option_entry_1[] PROGMEM = "Contrast";
const char option_entry_2[] PROGMEM = "opt2";
const char option_entry_3[] PROGMEM = "Inv. colors";
const char debug_entry_0[] PROGMEM = "fit screen";
const char debug_entry_1[] PROGMEM = "Calibrate";
const char debug_entry_2[] PROGMEM = "debug2";
const char debug_entry_3[] PROGMEM = "debug3";


char temp[16];

// menu highscore_0;
// menu highscore_1;
// menu highscore_2;
menu option_0;
menu option_1;
//menu option_2;
//menu option_3;
menu debug_0;
menu debug_1;
menu mainmenu_0;//Highscore
menu mainmenu_1;
menu mainmenu_2;
//menu mainmenu_3;

void initialize_menu(void){

	setup_menu(&mainmenu_0,&mainmenu_1,NULL,NULL,3,mainmenu_entry_1);
	setup_menu(&mainmenu_1,&mainmenu_2,NULL,&debug_0,3,mainmenu_entry_2);
	setup_menu(&mainmenu_2,&mainmenu_0,NULL,&option_0,3,mainmenu_entry_3);
	
	setup_menu(&option_0,&option_1,&mainmenu_0,NULL,2,option_entry_0);
	setup_menu(&option_1,&option_0,&mainmenu_0,NULL,2,option_entry_1);

	setup_menu(&debug_0,&debug_1,&mainmenu_0,NULL,2,debug_entry_0);
	setup_menu(&debug_1,&debug_0,&mainmenu_0,NULL,2,debug_entry_1);
	
	// current_head is the top entry of the current menu.
	current_head = &mainmenu_0;
	
	// current_selected is the selected menu entry of the current menu.
	current_selected = &mainmenu_0;
	
}

int8_t navigation_counter = 0;
void menu_update(void){
	if(navigate_menu()){ //if something is selected this is true, else the screen updates
		
	}else{
		for (int j = 0; j < 7; j++)
		{
			sram_clear_line(j);
		}
		
		for (int i = 0; i < current_head->n_sib; i++)
		{
			oled_goto_line(i);
			oled_goto_column(0);
			strcpy_P(temp,current_head->title);
			
			
			//oled_print_char(128 + (current_head == current_selected));
			sram_write_char(128 + (current_head == current_selected));
			//oled_print(temp);
			sram_write_string(temp);
			current_head = current_head->ptr_sib_down;
		}
		
	}
	
	if(timer_check_flag()){//a timer with frequency of 60Hz ensures a framerate of 60Hz
		navigation_counter++;
		sram_push();
		timer_disable_flag();
		sram_scroll_line(7,1);
	}
}



int navigate_menu(void){
	/*int joystick_reading_y = read_control_input('Y');
	
	if(joystick_reading_y > NAVIGATION_TRHESHOLD){
		for(int i = 0; i < current_selected->n_sib-1; i++){
			current_selected = current_selected->ptr_sib_down;
		}
	}
	else if (joystick_reading_y < -NAVIGATION_TRHESHOLD){
		current_selected = current_selected->ptr_sib_down;
	}
	*/
	int joystick_reading = read_control_input('Y');
	
	// Navigate up.
	if(joystick_reading > NAVIGATION_TRHESHOLD && navigation_counter >= NAVIGATION_COUNTER_MAX){
		for(int i = 0; i < current_selected->n_sib-1; i++){
			current_selected = current_selected->ptr_sib_down;
		}
		navigation_counter = 0;
	}else if (joystick_reading < -NAVIGATION_TRHESHOLD && navigation_counter >= NAVIGATION_COUNTER_MAX)
	{
		current_selected = current_selected->ptr_sib_down;
		navigation_counter = 0;
		// No navigation input on y-axis.
	}else if(joystick_reading < NAVIGATION_TRHESHOLD && joystick_reading > -NAVIGATION_TRHESHOLD){
		navigation_counter = NAVIGATION_COUNTER_MAX - 1;
	}
	if (check_flag_right())
	{
		if(current_selected->ptr_child != NULL){
			current_head = current_selected->ptr_child;
			current_selected = current_selected->ptr_child;
		}else{
			menu_function_selected();
		}
	}else if (check_flag_left()){
		if (current_selected->ptr_parent != NULL){
			current_head = current_head->ptr_parent;
			current_selected = current_selected->ptr_parent;
		}
	}
	return 0;
	
}

void menu_left_button_flag(void){
	left_button_flag = 1;
}


void menu_right_button_flag(void){
	right_button_flag = 1;
}

void menu_function_selected(void){
	if(current_selected == &option_1){
		menu_set_contrast();
	}else if(current_selected == &debug_1){
		menu_calibrate_joystick();
	}
}

const char btn_0[] PROGMEM = "->L_BTN";
const char btn_1[] PROGMEM = "->R_BTN";

const char brightness_text_0[] PROGMEM = "Use left slider";

void menu_set_contrast(void){
	
	oled_goto_line(0);
	strcpy_P(temp,brightness_text_0);
	sram_write_string(temp);
	sram_clear_line(1);
	oled_goto_line(2);
	strcpy_P(temp,btn_1);
	sram_write_string(temp);
	sram_push();
	while (!check_flag_right()){
		write_c(0x81);
		write_c(readADC(3)/2);
	}
	
}




const char calibrate_text_0[] PROGMEM = "Let go";
const char calibrate_text_1[] PROGMEM = "Hold Joystick";
const char calibrate_direction_0[] PROGMEM = "UP";
const char calibrate_direction_1[] PROGMEM = "DOWN";
const char calibrate_direction_2[] PROGMEM = "LEFT";
const char calibrate_direction_3[] PROGMEM = "RIGHT";
const char* const calibrate_direction_array[] PROGMEM = {calibrate_direction_0,calibrate_direction_1,calibrate_direction_2,calibrate_direction_3};

void menu_calibrate_joystick(void){
	for (uint8_t i = 0; i < 7; i++){
		sram_clear_line(i);
	}
	oled_goto_line(0);
	strcpy_P(temp,calibrate_text_0);
	sram_write_string(temp);
	oled_goto_line(2);
	strcpy_P(temp,btn_1);
	sram_write_string(temp);
	sram_push();
	while (!check_flag_right()){
		
	}
	
	
	oled_clear_line(0);
	strcpy_P(temp,calibrate_text_1);
	sram_write_string(temp);
	
	for (uint8_t i = 0; i < 4; i++){
		
		oled_clear_line(1);
		strcpy_P(temp,(char*)pgm_read_word(&(calibrate_direction_array[i])));
		sram_write_string(temp);
		sram_push();
		while (!check_flag_right()){
			
		}
		
	}
}