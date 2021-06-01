#include <avr/io.h>
#include <avr/interrupt.h>
int btn_1_or_2;
int count = 0;
int main(void) {
	DDRD &= 0b11110011; // PD2,3 inputs
	DDRB |= 0b00000001; // PB0 output
	SREG |= 0b10000000;
	TIMSK0 |= 0b00000001; //TOIE = 1
	TCCR1A = 0b00000101;
	TCCR1B = 0b00000101; // 101 mode: 1024 prescaler
	while (~PORTD0 && ~PORTD1) {
	}
	if (PORTD0)
		btn_1_or_2 = false;
	else
		btn_1_or_2 = true;

	while (1) {
	}

}

ISR(TIMER1_OVF_vect) {
	if (~btn_1_or_2) //btn 1
	{

	} else {

	}
	PORTB0 ^= 1;
	TIFR |= (1 << TOV1);
}
