#include <stdint.h>
#include <HardwareSerial.h>
#include <Arduino.h>


#define RED_DELAY (8500)
#define GREEN_DELAY (RED_DELAY)
#define YELLOW_DELAY (1200)


enum light_pins {
	LPIN_PED_RED = 4,
	LPIN_PED_GREEN = 5,
	LPIN_SEM_RED = 6,
	LPIN_SEM_YELLOW = 7,
	LPIN_SEM_GREEN = 8,
	LPIN_NPINS = 5,
	LPIN_FIRST = LPIN_PED_RED,
	LPIN_LAST = LPIN_SEM_GREEN,

};

enum button_pins {
	BPIN_PED = 2
};

enum buzz_pins {
	BUZZ_PIN = 3,
	BUZZ_PIN_LED = 13
};


extern void midi_init(int buzzpin, int ledpin_first, int ledpin_last);
extern void midi_play(void);


static uint16_t delays[] = { 1200, 8200, 1200, 8200 };
static uint8_t traff_pins[] = { LPIN_SEM_YELLOW, LPIN_SEM_RED, LPIN_SEM_YELLOW, LPIN_SEM_GREEN };
static uint8_t ped_pins[] = { LPIN_PED_RED, LPIN_PED_GREEN, LPIN_PED_RED, LPIN_PED_RED };
static uint8_t oldstate = 0;
static uint8_t state = 0;
volatile bool interrupted = false;


static void ped_button_int(void)
{
	interrupted = true;
}

static void enable_int(void)
{
	attachInterrupt(digitalPinToInterrupt(2), ped_button_int, LOW);
	interrupts();
}

static void disable_int(void)
{
	detachInterrupt(digitalPinToInterrupt(2));
}

static void delay_int(const int milli)
{
	enable_int();
	delay(milli);
	disable_int();
}


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
	for (unsigned i = LPIN_FIRST; i <= LPIN_LAST; ++i)
		pinMode(i, OUTPUT);

	pinMode(BUZZ_PIN, OUTPUT);
	pinMode(BPIN_PED, INPUT_PULLUP);
	midi_init(BUZZ_PIN, LPIN_FIRST, LPIN_LAST);

	Serial.begin(9600);
	update_ped();
	update_traff();
}


void loop(void)
{
	delay_int(delays[state]);

	oldstate = state;
	if (++state == 4)
		state = 0;

	update_traff();
	delay_int(1000);
	update_ped();

	if (interrupted) {
		uint8_t pinstates[LPIN_NPINS];
		for (unsigned i = LPIN_FIRST, j = 0; i <= LPIN_LAST; ++i, ++j) {
			pinstates[j] = digitalRead(i);
			digitalWrite(i, LOW);
		}

		midi_play();
		
		for (unsigned i = LPIN_FIRST, j = 0; i <= LPIN_LAST; ++i, ++j)
			digitalWrite(i, pinstates[j]);

		interrupted = false;
	}
}

