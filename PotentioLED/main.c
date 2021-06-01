#define F_CPU 16000000
#include <avr/io.h>
//#include <avr/iom328p.h>
#include <util/delay.h>

//unsigned int initD, initB;
//unsigned int readD, readB;

int main(void) {
	DDRD |= 0xFF; //all output
	DDRB |= 3; // B0,B1 output
	DDRC &= 0xFE;
	PORTD = 0;
	PORTB &= 0xFC;

	ADMUX = 0; //AREF, Right shifted, ADC0
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //Enable ADC and 128 prescaler/division factor
	ADCSRB = 0; // Free running mode // Not found?
	DIDR0 = 0x01;

	ADCSRA |= 1 << ADSC; //start conversion
	while (ADCSRA & 0b01000000)
		;
	PORTD = ADCL;
	PORTB = ADCH;
	while (1) {
		ADCSRA |= 1 << ADSC; //start conversion
		while (ADCSRA & (1 << ADSC));
		PORTD = ADCL;
		PORTB = ADCH;
		_delay_ms(100);
	}
}
