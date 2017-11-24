/*
 * menu.c
 *
 * Created: 28.09.2017 20:18:00
 *  Author: dirkpr
 */ 
#include "menu.h"

menu* current_head;
menu* current_selected;

void setup_menu(menu * new_menu, menu * ptr_sib_down, menu * ptr_parent, menu * ptr_child, int n_sib, PGM_P title){
	new_menu->ptr_sib_down = ptr_sib_down;
	new_menu->ptr_child = ptr_child;
	new_menu->ptr_parent = ptr_parent;
	new_menu->title = title;
	new_menu->n_sib = n_sib;
}


#if HIGHSCORE_ENABLE 
const char mainmenu_entry_highscore[] PROGMEM = "Highscore";
const char highscore_entry_0[] PROGMEM = "Squash-sim";
const char highscore_entry_1[] PROGMEM = "Flappy Pixel";
#endif
#if TOTAL_GAMES>0
const char mainmenu_entry_games[] PROGMEM = "Games";
const char game_entry_0[] PROGMEM = "Squash-sim";
const char game_entry_1[] PROGMEM = "Flappy Pixel";
#endif

#if OPTION_ENABLE
const char mainmenu_entry_options[] PROGMEM = "Options";
const char option_entry_0[] PROGMEM = "Music";
const char option_entry_1[] PROGMEM = "Contrast";
#endif

#if DEBUG_ENABLE
const char mainmenu_entry_debug[] PROGMEM = "Debug";
const char debug_entry_0[] PROGMEM = "fit screen";
const char debug_entry_1[] PROGMEM = "Calibrate";
#endif

//setup debug
#if DEBUG_ENABLE
//SETUP OF THE DEBUG
menu debug_0;
menu debug_1;
menu *debug_list[TOTAL_DEBUG] = {
	&debug_0,
	&debug_1
};
const char *debug_entry_list[TOTAL_DEBUG] = {
	debug_entry_0,
	debug_entry_1
};
menu *debug_ptr_list[TOTAL_DEBUG] = {
	NULL,
	NULL
};
#endif

//SETUP OF THE OPTION
#if OPTION_ENABLE
menu option_0;
menu option_1;
menu *option_list[TOTAL_OPTION] = {
	&option_0,
	&option_1
};
const char *option_entry_list[TOTAL_OPTION] = {
	option_entry_0,
	option_entry_1
};
menu *option_ptr_list[TOTAL_OPTION] = {
	NULL,
	NULL,
};
#endif

//setup games
#if TOTAL_GAMES > 0
#if SQUASH_SIM
menu game_0;
#endif
#if FLAPPY
menu game_1;
#endif

menu *game_list[TOTAL_OPTION] = {
	#if SQUASH_SIM
	&game_0,
	#endif
	#if FLAPPY
	&game_1
	#endif
};
const char *game_entry_list[TOTAL_OPTION] = {
	#if SQUASH_SIM
	game_entry_0,
	#endif
	#if FLAPPY
	game_entry_1
	#endif
};
menu *game_ptr_list[TOTAL_OPTION] = {
	#if SQUASH_SIM
	NULL,
	#endif
	#if FLAPPY
	NULL
	#endif
};
#endif

#if DEBUG_ENABLE
menu mainmenu_debug;
#endif

#if HIGHSCORE_ENABLE
#define TOTAL_HIGHSCORE 2
menu mainmenu_highscore;
menu highscore_0;
menu highscore_1;

menu *highscore_list[TOTAL_HIGHSCORE] = {
	&highscore_0,
	&highscore_1
};
const char *highscore_entry_list[TOTAL_HIGHSCORE] = {
	highscore_entry_0,
	highscore_entry_1
};
menu *highscore_ptr_list[TOTAL_HIGHSCORE] = {
	NULL,
	NULL
};

#endif

#if OPTION_ENABLE
menu mainmenu_options;
#endif

#if TOTAL_GAMES > 0
menu mainmenu_games;
#endif
menu *mainmenu_list[TOTAL_MAINMENU] = {
	#if TOTAL_GAMES > 0
	&mainmenu_games,
	#endif
	#if HIGHSCORE_ENABLE
	&mainmenu_highscore,
	#endif
	&mainmenu_options,
	#if DEBUG_ENABLE
	&mainmenu_debug
	#endif
};
const char *mainmenu_entry_list[TOTAL_MAINMENU] = {
	#if TOTAL_GAMES > 0
	mainmenu_entry_games,
	#endif
	#if HIGHSCORE_ENABLE
	mainmenu_entry_highscore,
	#endif
	mainmenu_entry_options,
	#if DEBUG_ENABLE
	mainmenu_entry_debug
	#endif
};
menu *mainmenu_ptr_list[TOTAL_MAINMENU] = {
	#if TOTAL_GAMES > 0
	&game_0,//GAME POINTER
	#endif
	#if HIGHSCORE_ENABLE
	&highscore_0,
	#endif
	&option_0,
	#if DEBUG_ENABLE
	&debug_0
	#endif
};

char temp[16];

void initialize_menu(void){
	for (uint8_t m = 0; m < TOTAL_MAINMENU; m++)
	{
		setup_menu(mainmenu_list[m],mainmenu_list[(m+1)%TOTAL_MAINMENU],NULL,mainmenu_ptr_list[m],TOTAL_MAINMENU,mainmenu_entry_list[m]);
	}
	#if OPTION_ENABLE
	for (uint8_t o = 0; o < TOTAL_OPTION; o++)
	{
		setup_menu(option_list[o],option_list[(o+1)%TOTAL_OPTION],mainmenu_list[0],option_ptr_list[o],TOTAL_OPTION,option_entry_list[o]);
	}
	#endif
	#if DEBUG_ENABLE
	for (uint8_t d = 0; d < TOTAL_DEBUG; d++)
	{
		setup_menu(debug_list[d],debug_list[(d+1)%TOTAL_DEBUG],mainmenu_list[0],debug_ptr_list[d],TOTAL_DEBUG,debug_entry_list[d]);
	}
	#endif
	#if TOTAL_GAMES > 0
	for (uint8_t g = 0; g < TOTAL_GAMES; g++)
	{
		setup_menu(game_list[g],game_list[(g+1)%TOTAL_GAMES],mainmenu_list[0],game_ptr_list[g],TOTAL_GAMES,game_entry_list[g]);
	}
	#endif
	#if HIGHSCORE_ENABLE
	for (uint8_t h = 0; h < TOTAL_HIGHSCORE; h++)
	{
		setup_menu(highscore_list[h],highscore_list[(h+1)%TOTAL_HIGHSCORE],mainmenu_list[0],highscore_ptr_list[h],TOTAL_HIGHSCORE,highscore_entry_list[h]);
	}
	#endif
	
	// current_head is the top entry of the current menu.
	current_head = &mainmenu_games;
	
	// current_selected is the selected menu entry of the current menu.
	current_selected = &mainmenu_games;
	
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
		sram_update_oled();
		timer_disable_flag();
		sram_scroll_line(7,1);
	}
}



int navigate_menu(void){
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

void menu_function_selected(void){
	if(current_selected == &option_1){
		menu_set_contrast();
	}
	#if DEBUG_ENABLE
	else if(current_selected == &debug_1){
		menu_calibrate_joystick();
	}
	#endif
	#if FLAPPY == 1
	else if(current_selected == &game_1){
		flappy_main();
	}
	#endif
	
	#if SQUASH_SIM == 1
	else if(current_selected == &game_0){
		play_game();
	}
	#endif
	
	#if HIGHSCORE_ENABLE
	else if(current_selected == &highscore_0){
		print_highscore(SCOREBOARD_MAIN_GAME);
		while (!(check_flag_left()||check_flag_right()))
		{
			
		}
	}
	
	else if(current_selected == &highscore_1){
		print_highscore(SCOREBOARD_FLAPPY_BIRD);
		while (!(check_flag_left()||check_flag_right()))
		{
			
		}
	}
	#endif
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
	sram_update_oled();
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
	sram_update_oled();
	while (!check_flag_right()){
		
	}
	
	
	oled_clear_line(0);
	strcpy_P(temp,calibrate_text_1);
	sram_write_string(temp);
	
	for (uint8_t i = 0; i < 4; i++){
		
		oled_clear_line(1);
		strcpy_P(temp,(char*)pgm_read_word(&(calibrate_direction_array[i])));
		sram_write_string(temp);
		sram_update_oled();
		while (!check_flag_right()){
			
		}
		
	}
}