#include <Arduino.h>


void blink(const int pin)
{
	digitalWrite(pin, HIGH);
	delay(500);
	digitalWrite(pin, LOW);
	delay(500);	
}


