#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "stdbool.h"

int main(void)
{
	DDRD &= 0b11111011;
	DDRB |= 0b00000011;
	PORTB &= 0b11111100;
	PORTB |= 0b00000011;
	bool btn_pushed = false;
	int count = 0;
//	while (1)
//	{
//		if (PIND & 0b00000100)
//		{
//			_delay_ms(100);
//			if (PIND & 0b00000100 & ~btn_pushed) //button is pushed
//			{
//				count++;
//				btn_pushed = true;
//				if(count == 1)
//					PORTB |= 0b000000001;
//				else if(count >= 5)
//					PORTB |= 0b000000010;
//			}
//			else if(~ PIND & 0b00000100)
//			{
//				btn_pushed = false;
//			}
//			_delay_ms(100);
//		}
//	}
}

