#include <Arduino.h>


void setup(void)
{
	pinMode(5, OUTPUT);
}


void loop(void) 
{
	for (;;) {
		digitalWrite(5, HIGH);
		delay(500);
		digitalWrite(5, LOW);
		delay(500);
	}
}


