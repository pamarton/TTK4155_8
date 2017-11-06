/*
 * IRsensor.c
 *
 * Created: 06.11.2017 14:25:28
 *  Author: jonasgl
 */ 

#include "IRsensor.h"


//int input_val;

void IR_init(void){	
	
	//Enable input at port F0
	DDRF &= ~(1 << PF0);
	
	
	//ADCSRB &= ~((1<<ADTS0)&(1<<ADTS1)&(1<<ADTS2));

	//Left adjusting (the 10-bit result) instead of right adjusting.
	//ADMUX |= (1<<ADLAR);
	
	// Set ADC prescaler to 128 -> 125kHz sample rate @ 16MHz.
	ADCSRA |= (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);		
	
	//Turning on internal voltage reference.
	ADMUX = (1<<REFS0);//|(1<<REFS1);
	
	//Use ADC0 -> Mux5:0 = 00000
	ADMUX &= ~((1<<MUX4)&(1<<MUX3)&(1<<MUX2)&(1<<MUX1)&(1<<MUX0));
	ADCSRB &= ~(1<<MUX5);
	
	// ADC Auto Triger Engable.
	ADCSRA |= (1<<ADATE);
	
	//Use Free-running mode.
	ADCSRB = (1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0);
	
	//Use 8-bit resolution, all data is stored in ADCH.
	ADMUX |= (1<<ADLAR);
	
	//Enabling ADC. ADC Result will be presented in ADC Data Registers ADCH & ADCL.
	ADCSRA |= (1<<ADEN);
	
	// Start A2D conversion.
	ADCSRA |= (1<<ADSC);            
	
	
	

}

	
	
	uint16_t read_adc(void)
	{
		//ADMUX = (ch & 0x00);
		//ADCSRA &= ~(1<<ADEN);			//Disabling ADC -> restarting the prescaler
		//ADCSRA |= (1<<ADEN);			//Enabling the ADC
		//ADCSRA |= (1<<ADSC);            //start conversion

		
		while( (ADCSRA & (1<<ADSC)) );                        //Wait for conversion to be done.
		
		//read ADC somewhere

		//printf("%i", ADCH); 
		return 0;   
		                                     //return the ADC conversion result from the ADC Result Registers (ADCL, ADCH)
	}
	



