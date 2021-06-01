#define F_CPU 16000000
#include <avr/io.h>
//#include <avr/iom328p.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void init_adc() { // AREF 0, channel 0.
	ADMUX &= ~(1 << REFS0 | 1 << REFS1 | 1 << ADLAR | 1 << MUX0 | 1 << MUX1
			| 1 << MUX2 | 1 << MUX3);
	ADCSRA |= 1 << ADEN;
	DIDR0 |= 0xFF;
}
int adc_conv() { // Get pot. value
	ADCSRA |= 1 << ADSC;
	while (~(ADCSRA & ~(1 << ADSC)))
		;
	return ADC;
}

void enable_pwm() {
	TCCR0A |= ((1 << WGM01) | (1 << COM0A1)) & (~(1 << WGM00) & ~(1 << COM0A0));
	TCCR0B &= (~(1 << CS02)) & (~(1 << CS00)) ;
	TCCR0B |= 1 << CS01;
}

void lab6_eval() {
	DDRD &= ~(1 << DDD0 | 1 << DDD1); //D0, D1 inputs
	DDRD |= 1 << DDD2 | 1 << DDD3; // D2, D3 output
	DDRC &= ~(1 << DDC0);
	init_adc();
	enable_pwm();
	char i1, i2;
	unsigned int adc_out;
	while (1) {
		adc_out = adc_conv() / 4;
//		PWM changes adc_out/
		OCR0A = adc_out;
		i1 = PIND & 1 << PIND0;
		i2 = PIND & 1 << PIND1;
		_delay_ms(100);
		if (((PIND & (1 << PIND0)) == i1) && ((i2 == PIND) & (1 << PIND1))) {
			if (i1 == i2)
				PORTD &= ~(1 << PD3 | 1 << PD4);
			else if (i1 == 1)
				PORTD |= 1 << PD3 & ~(1 << PD4);
			else
				PORTD |= 1 << PD4 & ~(1 << PD3);
		}
	}
}

int main() {
	lab6_eval();
}


