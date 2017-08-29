#include <Arduino.h>


enum Note {
	NOTE_NULL = 0,
	NOTE_B0  = 31,
	NOTE_C1  = 33,
	NOTE_CS1 = 35,
	NOTE_D1  = 37,
	NOTE_DS1 = 39,
	NOTE_E1  = 41,
	NOTE_F1  = 44,
	NOTE_FS1 = 46,
	NOTE_G1  = 49,
	NOTE_GS1 = 52,
	NOTE_A1  = 55,
	NOTE_AS1 = 58,
	NOTE_B1  = 62,
	NOTE_C2  = 65,
	NOTE_CS2 = 69,
	NOTE_D2  = 73,
	NOTE_DS2 = 78,
	NOTE_E2  = 82,
	NOTE_F2  = 87,
	NOTE_FS2 = 93,
	NOTE_G2  = 98,
	NOTE_GS2 = 104,
	NOTE_A2  = 110,
	NOTE_AS2 = 117,
	NOTE_B2  = 123,
	NOTE_C3  = 131,
	NOTE_CS3 = 139,
	NOTE_D3  = 147,
	NOTE_DS3 = 156,
	NOTE_E3  = 165,
	NOTE_F3  = 175,
	NOTE_FS3 = 185,
	NOTE_G3  = 196,
	NOTE_GS3 = 208,
	NOTE_A3  = 220,
	NOTE_AS3 = 233,
	NOTE_B3  = 247,
	NOTE_C4  = 262,
	NOTE_CS4 = 277,
	NOTE_D4  = 294,
	NOTE_DS4 = 311,
	NOTE_E4  = 330,
	NOTE_F4  = 349,
	NOTE_FS4 = 370,
	NOTE_G4  = 392,
	NOTE_GS4 = 415,
	NOTE_A4  = 440,
	NOTE_AS4 = 466,
	NOTE_B4  = 494,
	NOTE_C5  = 523,
	NOTE_CS5 = 554,
	NOTE_D5  = 587,
	NOTE_DS5 = 622,
	NOTE_E5  = 659,
	NOTE_F5  = 698,
	NOTE_FS5 = 740,
	NOTE_G5  = 784,
	NOTE_GS5 = 831,
	NOTE_A5  = 880,
	NOTE_AS5 = 932,
	NOTE_B5  = 988,
	NOTE_C6  = 1047,
	NOTE_CS6 = 1109,
	NOTE_D6  = 1175,
	NOTE_DS6 = 1245,
	NOTE_E6  = 1319,
	NOTE_F6  = 1397,
	NOTE_FS6 = 1480,
	NOTE_G6  = 1568,
	NOTE_GS6 = 1661,
	NOTE_A6  = 1760,
	NOTE_AS6 = 1865,
	NOTE_B6  = 1976,
	NOTE_C7  = 2093,
	NOTE_CS7 = 2217,
	NOTE_D7  = 2349,
	NOTE_DS7 = 2489,
	NOTE_E7  = 2637,
	NOTE_F7  = 2794,
	NOTE_FS7 = 2960,
	NOTE_G7  = 3136,
	NOTE_GS7 = 3322,
	NOTE_A7  = 3520,
	NOTE_AS7 = 3729,
	NOTE_B7  = 3951,
	NOTE_C8  = 4186,
	NOTE_CS8 = 4435,
	NOTE_D8  = 4699,
	NOTE_DS8 = 4978
};


static const Note mario_theme_notes[] = {
	NOTE_E7, NOTE_E7, NOTE_NULL, NOTE_E7,
	NOTE_NULL, NOTE_C7, NOTE_E7, NOTE_NULL,
	NOTE_G7, NOTE_NULL, NOTE_NULL,  NOTE_NULL,
	NOTE_G6, NOTE_NULL, NOTE_NULL, NOTE_NULL,

	NOTE_C7, NOTE_NULL, NOTE_NULL, NOTE_G6,
	NOTE_NULL, NOTE_NULL, NOTE_E6, NOTE_NULL,
	NOTE_NULL, NOTE_A6, NOTE_NULL, NOTE_B6,
	NOTE_NULL, NOTE_AS6, NOTE_A6, NOTE_NULL,

	NOTE_G6, NOTE_E7, NOTE_G7,
	NOTE_A7, NOTE_NULL, NOTE_F7, NOTE_G7,
	NOTE_NULL, NOTE_E7, NOTE_NULL, NOTE_C7,
	NOTE_D7, NOTE_B6, NOTE_NULL, NOTE_NULL,

	NOTE_C7, NOTE_NULL, NOTE_NULL, NOTE_G6,
	NOTE_NULL, NOTE_NULL, NOTE_E6, NOTE_NULL,
	NOTE_NULL, NOTE_A6, NOTE_NULL, NOTE_B6,
	NOTE_NULL, NOTE_AS6, NOTE_A6, NOTE_NULL,

	NOTE_G6, NOTE_E7, NOTE_G7,
	NOTE_A7, NOTE_NULL, NOTE_F7, NOTE_G7,
	NOTE_NULL, NOTE_E7, NOTE_NULL, NOTE_C7,
	NOTE_D7, NOTE_B6, NOTE_NULL, NOTE_NULL
};

static const int mario_theme_tempo[] = {
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	9, 9, 9,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,

	9, 9, 9,
	12, 12, 12, 12,
	12, 12, 12, 12,
	12, 12, 12, 12,
};

static const Note underworld_notes[] = {
	NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
	NOTE_AS3, NOTE_AS4, NOTE_NULL,
	NOTE_NULL,
	NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
	NOTE_AS3, NOTE_AS4, NOTE_NULL,
	NOTE_NULL,
	NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
	NOTE_DS3, NOTE_DS4, NOTE_NULL,
	NOTE_NULL,
	NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
	NOTE_DS3, NOTE_DS4, NOTE_NULL,
	NOTE_NULL, NOTE_DS4, NOTE_CS4, NOTE_D4,
	NOTE_CS4, NOTE_DS4,
	NOTE_DS4, NOTE_GS3,
	NOTE_G3, NOTE_CS4,
	NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
	NOTE_GS4, NOTE_DS4, NOTE_B3,
	NOTE_AS3, NOTE_A3, NOTE_GS3,
	NOTE_NULL, NOTE_NULL, NOTE_NULL
};

static const int underworld_tempo[] = {
	12, 12, 12, 12,
	12, 12, 6,
	3,
	12, 12, 12, 12,
	12, 12, 6,
	3,
	12, 12, 12, 12,
	12, 12, 6,
	3,
	12, 12, 12, 12,
	12, 12, 6,
	6, 18, 18, 18,
	6, 6,
	6, 6,
	6, 6,
	18, 18, 18, 18, 18, 18,
	10, 10, 10,
	10, 10, 10,
	3, 3, 3
};

static const Note vampire_killer_notes[] = {
	NOTE_D5, NOTE_D5, NOTE_C5, NOTE_B4,
	NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5,
	NOTE_A5, NOTE_D5, NOTE_A5, NOTE_G5,
	NOTE_C5,

	NOTE_D5, NOTE_D5, NOTE_C5, NOTE_B4,
	NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5,
	NOTE_A5, NOTE_D5, NOTE_A5, NOTE_G5,
	NOTE_C5
	
};

static const int vampire_killer_tempo[] = {
	12, 12, 8, 8,
	10, 12, 12, 12,
	8, 8, 10, 8,
	4,

	12, 12, 8, 8,
	10, 12, 12, 12,
	8, 8, 10, 8,
	4

};

static int pin_buzzer;
static int pin_led_first;
static int pin_led_last;
static int pin_led;


static inline void buzz(const Note frequency, const long length)
{
	if (frequency != NOTE_NULL)
		digitalWrite(pin_led, HIGH);

	const long delay = 1000000 / frequency / 2; // calculate the delay value between transitions
	//// 1 second's worth of microseconds, divided by the frequency, then split in half since
	//// there are two phases to each cycle
	const long cycles = frequency * length / 1000; // calculate the number of cycles for proper timing
	//// multiply frequency, which is really cycles per second, by the number of seconds to
	//// get the total number of cycles to produce
	for (long i = 0; i < cycles; i++) { // for the calculated length of time...
		digitalWrite(pin_buzzer, HIGH); // wr	ite the buzzer pin high to push out the diaphram
		delayMicroseconds(delay); // wait for the calculated delay value
		digitalWrite(pin_buzzer, LOW); // write the buzzer pin low to pull back the diaphram
		delayMicroseconds(delay); // wait again or the calculated delay value
	}
	
	if (frequency != NOTE_NULL) {
		digitalWrite(pin_led, LOW);
		++pin_led;
		if (pin_led > pin_led_last)
			pin_led = pin_led_first;
	}
}

static inline void sing(const Note notes[], const int tempo[], const int size)
{
	for (int note = 0; note < size; ++note) {
		// to calculate the note duration, take one second
		// divided by the note type.
		// e.g. quarter note = 1000 / 4, eighth note = 1000 / 8, etc.
		const int notetime = 1000 / tempo[note];

		buzz(notes[note], notetime);

		// to distinguish the notes, set a minimum time between them.
		// the note's duration + 30% seems to work well:
		const int pause_between_notes = notetime * 1.30;
		delay(pause_between_notes);

		// stop the tone playing:
		buzz(NOTE_NULL, notetime);
	}
}


void midi_init(const int buzzpin, const int ledpin_first, const int ledpin_last)
{
	pin_buzzer = buzzpin;
	pin_led_first = ledpin_first;
	pin_led_last = ledpin_last;
}

void midi_play(void)
{
	pin_led = pin_led_first;
	sing(mario_theme_notes, mario_theme_tempo,
	     sizeof(mario_theme_notes) / sizeof(mario_theme_notes[0]));
	sing(underworld_notes, underworld_tempo,
	     sizeof(underworld_notes) / sizeof(underworld_notes[0]));
	sing(vampire_killer_notes, vampire_killer_tempo,
	     sizeof(vampire_killer_notes) / sizeof(vampire_killer_notes[0]));

}
