#include <stdint.h>
#include <Arduino.h>


#define RED_DELAY (8500)
#define GREEN_DELAY (RED_DELAY)
#define YELLOW_DELAY (1200)


enum Pins {
	PIN_PED_RED = 2,
	PIN_PED_GREEN = 3,
	PIN_SEM_RED = 4,
	PIN_SEM_YELLOW = 5,
	PIN_SEM_GREEN = 6,
	PIN_FIRST = PIN_PED_RED,
	PIN_LAST = PIN_SEM_GREEN

};


static uint16_t delays[] = { 1200, 8200, 1200, 8200 };
static uint8_t traff_pins[] = { PIN_SEM_YELLOW, PIN_SEM_RED, PIN_SEM_YELLOW, PIN_SEM_GREEN };
static uint8_t ped_pins[] = { PIN_PED_RED, PIN_PED_GREEN, PIN_PED_RED, PIN_PED_RED };
static uint8_t oldstate = 0;
static uint8_t state = 0;


static void update_traff(void)
{
	digitalWrite(traff_pins[oldstate], LOW);
	digitalWrite(traff_pins[state], HIGH);
}

static void update_ped(void)
{
	digitalWrite(ped_pins[oldstate], LOW);
	digitalWrite(ped_pins[state], HIGH);
}

void setup(void)
{
	for (unsigned i = PIN_FIRST; i <= PIN_LAST; ++i)
		pinMode(i, OUTPUT);

	update_ped();
	update_traff();
}


void loop(void)
{
	delay(delays[state]);

	oldstate = state;
	if (++state == 4)
		state = 0;

	update_traff();
	delay(1000);
	update_ped();

}

