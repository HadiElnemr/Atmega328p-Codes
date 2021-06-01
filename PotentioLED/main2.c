#define F_CPU 16000000
#include <avr/io.h>
//#include <avr/iom328p.h>
#include <util/delay.h>


int main(void) {
	DDRB &= ~(1<<PB0);
	DDRD |= 1;
	TCCR1A = 0;
	TCCR1B |= (1<<ICES1) | (1<<CS10);
	TIMSK1 |= (1<<ICIE1);
	unsigned int cur,prev,delta;
	char isfirst = 1;
	SREG |= 1<SREG_I;
	while(1){
		while(~(TIFR1 & 1<<ICF1));
		if (isfirst)
		{
			isfirst = 0;
			cur = prev = ICR1;
			continue;
		}
		cur =ICR1;
		if(TIFR1 & 1<<TOV1)
			delta = cur + 65536-prev;
		else
			delta = cur - prev;
		if(delta>24000)
			PORTD|=1;
		else
			PORTD&=0;
		TIFR1 |= (1<<TOV1) | (1<<ICF1);
		prev = cur;


	}




}
