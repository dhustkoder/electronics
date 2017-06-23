#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Time.h>


enum Pin {
	PIN_INTERRUPT  = 2,
	PIN_INPUT_A    = 4,
	PIN_INPUT_B    = 5,
	PIN_OUTPUT     = 6,
	PIN_SWITCHER   = 7,
};


enum LogicGate {
	LOGIC_GATE_AND,
	LOGIC_GATE_FIRST = LOGIC_GATE_AND,
	LOGIC_GATE_NAND,
	LOGIC_GATE_OR,
	LOGIC_GATE_NOR,
	LOGIC_GATE_XOR,
	LOGIC_GATE_XNOR,
	LOGIC_GATE_LAST = LOGIC_GATE_XNOR
};


static inline LogicGate& operator++(LogicGate& gate)
{
	gate = static_cast<LogicGate>(static_cast<int>(gate) + 1);
	if (static_cast<int>(gate) > static_cast<int>(LOGIC_GATE_LAST))
		gate = LOGIC_GATE_FIRST;

	return gate;
}

static inline LogicGate& operator--(LogicGate& gate)
{
	gate = static_cast<LogicGate>(static_cast<int>(gate) - 1);
	if (static_cast<int>(gate) < static_cast<int>(LOGIC_GATE_FIRST))
		gate = LOGIC_GATE_LAST;
	return gate;
}


static LogicGate currgate = LOGIC_GATE_FIRST;
static bool pin_switch_pressed = false;
static time_t last_interaction = 0;
volatile bool has_interaction = false;


static inline bool executeLogicFunction(LogicGate gate, bool a, bool b)
{
	switch (gate) {
	case LOGIC_GATE_AND:  return a && b;
	case LOGIC_GATE_NAND: return !(a && b);
	case LOGIC_GATE_OR:   return a || b;
	case LOGIC_GATE_NOR:  return !(a || b);
	case LOGIC_GATE_XOR:  return a ^ b;
	case LOGIC_GATE_XNOR: return !(a ^ b);
	}
	return false;
}


static inline void hibernate()
{
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	cli();
	sleep_enable();
	sleep_bod_disable();
	sei();
	sleep_cpu();
}


void setup()
{
	Serial.begin(9600);
	pinMode(PIN_INTERRUPT, INPUT);
	pinMode(PIN_INPUT_A, INPUT);
	pinMode(PIN_INPUT_B, INPUT);
	pinMode(PIN_SWITCHER, INPUT);
	pinMode(PIN_OUTPUT, OUTPUT);
	const auto dummy = [] { has_interaction = true; };
	attachInterrupt(digitalPinToInterrupt(PIN_INTERRUPT), dummy, CHANGE);
}


void loop()
{
	if (!has_interaction) {
		Serial.println("Hibernating...");
		delay(150);  // let it write to serial before hibernating
		hibernate(); // hibernate until next user's interaction
		Serial.println("Waking up...");
	}

	Serial.println("Processing...");
	has_interaction = false;
	last_interaction = now();

	do {
		if (digitalRead(PIN_SWITCHER) == LOW) {
			if (!pin_switch_pressed) {
				++currgate;
				pin_switch_pressed = true;
				delay(50); // button bounce
			}
		} else {
			pin_switch_pressed = false;
		}

		const bool a = digitalRead(PIN_INPUT_A) == LOW;
		const bool b = digitalRead(PIN_INPUT_B) == LOW;
		const bool result = executeLogicFunction(currgate, a, b);
		digitalWrite(PIN_OUTPUT, result ? HIGH : LOW);
	} while ((now() - last_interaction) < 1);
}




