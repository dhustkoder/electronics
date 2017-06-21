#include <stdbool.h>
#include <Arduino.h>


enum LedPins {
	PIN_INPUT_A = 2,
	PIN_INPUT_B = 3,
	PIN_OUTPUT  = 4,
	PIN_SWITCH  = 6
};


static bool and(bool a, bool b)
{
	return a && b;
}

static bool nand(bool a, bool b)
{
	return !(a && b);
}

static bool or(bool a, bool b)
{
	return a || b;
}

static bool nor(bool a, bool b)
{
	return !(a || b);
}

static bool xor(bool a, bool b)
{
	return a ^ b;
}

static bool xnor(bool a, bool b)
{
	return !(a ^ b);
}


#define LOGIC_GATES_SIZE ((int)6)
static bool (* const logicgates[LOGIC_GATES_SIZE])(bool,bool) = {
	and, nand, or, nor, xor, xnor
};
static int logicgates_idx = 0;
static bool switchpin_released = true;


void setup(void)
{
	pinMode(PIN_INPUT_A, INPUT);
	pinMode(PIN_INPUT_B, INPUT);
	pinMode(PIN_SWITCH, INPUT);
	pinMode(PIN_OUTPUT, OUTPUT);
}


void loop(void)
{
	if (digitalRead(PIN_SWITCH) == LOW) {
		if (switchpin_released) {
			++logicgates_idx;
			if (logicgates_idx >= LOGIC_GATES_SIZE)
				logicgates_idx = 0;
			switchpin_released = false;
		}
	} else {
		switchpin_released = true;
		const bool a = digitalRead(PIN_INPUT_A) == LOW;
		const bool b = digitalRead(PIN_INPUT_B) == LOW;
		digitalWrite(PIN_OUTPUT, logicgates[logicgates_idx](a, b) ? HIGH : LOW);
	}
	delay(50);
}




