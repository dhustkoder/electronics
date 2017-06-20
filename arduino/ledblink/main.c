#include <avr/io.h>
#include <util/delay.h>


__attribute__((noreturn)) void main(void) 
{

	DDRD |= _BV(DDD5); // set pin 5 for OUTPUT

	for (;;) {
		PORTD |= _BV(PORTD5);
		_delay_ms(500);
		PORTD &= ~_BV(PORTD5);
		_delay_ms(500);
	}
}


