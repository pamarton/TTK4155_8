/*
 * SD_card.c
 *
 * Created: 12.11.2017 14:54:06
 *  Author: pamarton
 */ 
#include	"SD_card.h"
#define CMD0	0x400000000095 //INIT
#define CMD55	0x770000000065 
void SD_initialize(void){
	 
	DDRL |= (1<<PL0);
	SPCR |= (1<<SPR0);
	
	/* Set MOSI and SCK output, all others input */
	DDRB |= (1<<SD_MOSI)|(1<<SD_SCK);
	DDRL |= (1<<SD_SS);
	DDRB &= ~(1<<SD_MISO);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR |= (1<<SPE)|(1<<MSTR);
		
	
	//ENABLE SD CARD
	PORTB |= (1<<PB0);
	PORTB |= (1<<SD_MOSI);
	SD_select();
	
	
	for (int a = 0; a < 0xFFFF; a++)
	{
		
	}
	
	SD_send(CMD0);
	
	while(!(SPSR & (1<<SPIF)));
	printf("\nA %i",SPDR);
	
	while(!(SPSR & (1<<SPIF)));
	printf("\nB %i",SPDR);
	
	#if UART_ENABLE
		//printf("SD communication initialized.\n");
	#endif
}


void SD_send(uint64_t data) {
	//SD_select();
	// Start the transmission
	for(int i = 40; i >= 0 ;i = i-8){
		SPDR = (uint8_t)(data>>i);
	}
	// Wait for transmission complete (checks if the register is empty)
	while(!(SPSR & (1<<SPIF)));
	
	
	//SD_deselect();
}


uint8_t SD_receive(void){
	
	// Send dummy data to receive from slave
	SD_send(0);
	
	// Wait for reception complete
	while(!(SPSR & (1<<SPIF)));

	// Return Data Register
	return SPDR;
}

void SD_select(void){
	PORTB &= ~(1 << SD_SS);
}

void SD_deselect(void){
	PORTB |= (1 << SD_SS);
}

void SD_test(void) {
	for (int i = 0; i< 256; i++){
		SD_send(0x02);
		SD_send(0);
		SD_send(i);
		SD_send(0x03);
		SD_send(0);
		printf("Value of i: %i\t value of reg:\t%i\n",i,SD_receive());
	}	
}