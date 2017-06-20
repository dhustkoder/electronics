#include <Arduino.h>


const int kLedPin = 2;


void setup(void)
{
	pinMode(kLedPin, OUTPUT);
}


void loop(void)
{
	extern void blink(int);
	blink(kLedPin);
}

