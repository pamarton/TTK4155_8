/*
 * uart_exchange.c
 *
 * Created: 21.11.2017 02:34:05
 *  Author: pamarton
 */ 
#include "uart_exchange.h"


void print_highscore(uint8_t game){//retrives the highscore from the SD
	sram_init();
	char a[10];
	for (uint8_t b = 0; b <8; b++)
	{
		sram_goto_line(b);
		sram_write_char('1'+b);
		sram_write_char(' ');
		
		printf("S0R");
		printf("%c",'0'+b);
		
		for (unsigned int i = 0; i< 4;i++)
		{
			a[i] = recieve_UART();
		}
		uint16_t temp = decode_hex(a[0])<<12 | decode_hex(a[1])<<8 | decode_hex(a[2])<<4 | decode_hex(a[3]);
		sram_write_int(temp);
		sram_goto_column(63);
		
		for (unsigned int i = 0; i< 8;i++)
		{
			a[i] = recieve_UART();
		}
		sram_write_string(a);
		sram_update_oled();
	}
	
}

uint8_t decode_hex(char hex){
	if (hex >= 'A')
	{
		return 10 + hex - 'A';
	}else{
		return hex - '0';
	}
}

char code_hex(uint8_t dec){
	if (dec >= 10)
	{
		return 'A'+dec-10;
	}
	return '0'+dec;
}

void play_song(uint8_t song){
	printf(SELECT_MUSIC);
	printf("%i",song);
}

void resume_music(void){
	printf(SELECT_MUSIC);
	printf(PLAY_MUSIC);
}

void pause_music(void){
	printf(SELECT_MUSIC);
	printf(PAUSE_MUSIC);
}

void get_scoreboard(uint8_t file, uint8_t pos){
	printf(SELECT_SCOREBOARD);
	printf("%i",file);
	printf(SCOREBOARD_READ);
	printf("%i",pos);
	while (1)
	{
		sram_write_char(recieve_UART());
	}
}


void keyboard_input(uint8_t file, uint16_t score){
	char current_letter = 'A';
	char letters[13];
	uint8_t char_pos = 4;
	sram_init();
	sram_goto_line(1);
	sram_write_string("NAME:");
	sram_goto_line(3);
	sram_write_string("Use UP/DOWN and\nR_BTM");
	letters[0] = code_hex(score>>12	& 0x000F);
	letters[1] = code_hex(score>>8	& 0x000F);
	letters[2] = code_hex(score>>4	& 0x000F);
	letters[3] = code_hex(score		& 0x000F);
	
	while(char_pos < 12){	
		
		
		timer_delay(200);
		sram_clear_line(2);
		if (read_control_input('Y') > 0){
			current_letter++;
		}
		else if(read_control_input('Y') < 0){
			current_letter--;
		}
		if (current_letter < 'A')
		{
			current_letter = 'Z';
		}
		if(check_flag_right()){
			letters[char_pos++] = current_letter;
		}
		if (check_flag_left() && char_pos > 4)
		{
			letters[char_pos--] = ' ';
		}
		for (uint8_t i = 4; i < char_pos +1; i++)
		{
			sram_write_char(letters[i]);
		}
		sram_write_char(current_letter);
		sram_update_oled();
	}
	printf(SELECT_SCOREBOARD);
	printf("%i",file);
	printf(SCOREBOARD_WRITE);
	for (uint8_t i = 0; i < 12; i++)//send through uart
	{
		printf("%c",letters[i]);
		//sram_write_char(letters[i]);
	}
	
}