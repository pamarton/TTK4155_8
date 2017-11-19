/*
 * flappy_pixel.c
 *
 * Created: 03.11.2017 19:39:57
 *  Author: pamarton
 */ 
#include "flappy_pixel.h"
#define FONT_WIDTH 8
#define WALL_HOLE 20
#define SCREEN_HEIGHT 64
#define SCREEN_WIDTH 128
#define PLAYER_POS 10
#define DEATH_CROSS 5
int score = 0;
uint8_t quit = 0;
uint8_t pause = 0;
volatile char *ext_ram_adress = (char *) 0x1800;
uint8_t player_height = 0;
uint8_t game_over = 0;
double velocity = 0;
double acceleration = 0.03;
double player_height_accurate = 0;
uint8_t difficulity = 100;
uint8_t new_wall = 100;

int flappy_main(void){
	srand(TCNT0); //using the clock counter for this, to give an approximated random value each time
	quit = 0;
	flappy_loading_screen();

	while (quit != 1){
		game_over = 0;
		
		player_height_accurate = 1;
		player_height = 1;
		velocity = 0;
		difficulity = 100;
		score = 0;
		flappy_game();
		sram_goto_line(6);
		sram_write_string("   TRY AGAIN?");
		flappy_restart();
	}
	
	return 0;
}

void flappy_loading_screen(void){
	sram_init();
	sram_goto_line(0);
	sram_write_string("  FLAPPY BIRD");
	sram_update_oled();
	
	timer_delay(1000);
	
	sram_draw_new_line(8*FONT_WIDTH+4,8,13*FONT_WIDTH+4,0);
	sram_draw_new_line(8*FONT_WIDTH+4,0,13*FONT_WIDTH+4,8);
	sram_update_oled();
	
	timer_delay(1000);
	
	sram_goto_line(2);
	sram_goto_column(FONT_WIDTH*8+4);
	sram_write_string("PIXEL");
	sram_update_oled();
	
	timer_delay(500);
	
	for (uint8_t i = 0; i < FONT_WIDTH*2; i++)
	{
		for (uint8_t x = FONT_WIDTH*2; x < FONT_WIDTH*8; x++){
			sram_scroll_vertically(x,0,FONT_WIDTH*3,1,0);
		}
		timer_delay(30);
		sram_update_oled();
	}
	
	//sram
	
	flappy_restart();
}

void flappy_restart(void){
	sram_goto_line(7);
	sram_write_string("BACK        PLAY");
	sram_update_oled();
	quit = 0;
	printf("MP");
	while (!(quit | check_flag_right()))
	{
		quit = check_flag_left();
	}
	
	sram_init();
}

void flappy_game(void){
	sram_update_oled();
	printf("M1");
	while (!flappy_pixel_collision() && !game_over)
	
	{
		if(timer_check_flag()){
			flappy_controll();
			sram_pixel(PLAYER_POS,player_height);
			flappy_scroll_wall();
			sram_update_oled();
		}
		if(check_flag_left()){//PAUSE
			sram_goto_line(0);
			sram_goto_column(0);
			sram_write_char('S');
			int tempscore = score;
			printf("MP");
			for (uint8_t i = 5; i > 1; i--)
			{
				sram_goto_line(i);
				sram_goto_column(0);
				if(tempscore != 0){
					sram_write_char('0'+(tempscore%10));
					tempscore -= tempscore%10;
					tempscore /= 10;
				}
				
			}
			sram_goto_line(7);
			sram_goto_column(0);
			sram_write_char('P');
			sram_update_oled();
			while(!(check_flag_left() | check_flag_right())){
				
			}
			printf("MR");
		}
	}
	printf("M2");
	timer_delay(1000);
	sram_init();
	sram_goto_line(0);
	sram_goto_column(FONT_WIDTH*3);
	sram_write_string("GAME  OVER");
	sram_goto_line(1);
	sram_goto_column(FONT_WIDTH*4);
	sram_write_string("SCORE: ");
	sram_write_int(score);
	sram_update_oled();
}

void flappy_render_wall(uint8_t selected_wall, uint8_t pos){
	if (selected_wall > SCREEN_HEIGHT-1 -WALL_HOLE){
		sram_draw_new_line(pos, 0, pos, SCREEN_HEIGHT-1 -WALL_HOLE);
	}else if(selected_wall < WALL_HOLE){ 
		sram_draw_new_line(pos, WALL_HOLE, pos , SCREEN_HEIGHT-1);
	}else{
		sram_draw_new_line(pos, 0, pos, selected_wall-WALL_HOLE/2);
		sram_draw_new_line(pos, selected_wall + WALL_HOLE/2, pos , SCREEN_HEIGHT-1);
	}
}

void flappy_controll(void){
	velocity += acceleration;
	if(check_flag_left() | check_flag_right()){
		velocity -= 1;
	}
	if(velocity > 1){
		velocity = 1;
	}else if(velocity < -1){
		velocity = -1;
	}
	player_height_accurate += velocity;
	if(player_height_accurate >= SCREEN_HEIGHT-1){
		game_over = 1;
	}else if(player_height_accurate<= 0){
		game_over = 1;
	}
	player_height = (int)player_height_accurate;
}

uint8_t flappy_pixel_collision(void){
	if (ext_ram_adress[PLAYER_POS+((player_height-player_height%8)/8)*128] & (1<<player_height%8)){
		return 1;
	}
	return 0;
}

void flappy_scroll_wall(void){
	
	for (uint8_t line = 0; line < 8; line++)//remove the left-most collumn (it must dissapear)
	{
		ext_ram_adress[line*SCREEN_WIDTH] = 0;
	}
	for(uint8_t wall_pos = 0; wall_pos < SCREEN_WIDTH-1; wall_pos++){
		for (uint8_t line = 0; line < 8; line++)//move the collumn to the left
		{
			ext_ram_adress[wall_pos + (line*SCREEN_WIDTH)] = ext_ram_adress[wall_pos + (line*SCREEN_WIDTH)+1];
		}
	}
	
	for (uint8_t line = 0; line < 8; line++)//move the collumn to the left
	{
		ext_ram_adress[(SCREEN_WIDTH - 1 + line*SCREEN_WIDTH)] = 0x00;
	}
	if(new_wall >= difficulity){//if a wall has been removed a new one must be made
		flappy_render_wall(rand()%(SCREEN_HEIGHT-WALL_HOLE/2)+WALL_HOLE/4,127);
		new_wall = 0;
		score++;
	}else{
		new_wall++;
	}
}