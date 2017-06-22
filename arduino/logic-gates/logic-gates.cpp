#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Time.h>


enum Pin {
	PIN_INPUT_A    = 2,
	PIN_INPUT_B    = 3,
	PIN_SWITCHER   = 5,
	PIN_OUTPUT     = 4
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


static bool switchpin_released = true;
static LogicGate currgate = LOGIC_GATE_FIRST;
volatile time_t lasttime;


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
	pinMode(PIN_INPUT_A, INPUT);
	pinMode(PIN_INPUT_B, INPUT);
	pinMode(PIN_SWITCHER, INPUT);
	pinMode(PIN_OUTPUT, OUTPUT);
	lasttime = now();
	void(*wakeup)() = [] { lasttime = now(); };
	attachInterrupt(digitalPinToInterrupt(PIN_INPUT_A), wakeup, CHANGE);
	attachInterrupt(digitalPinToInterrupt(PIN_INPUT_B), wakeup, CHANGE);
}


void loop()
{
	if ((now() - lasttime) > 10) {
		Serial.println("hibernating...");
		delay(150);
		hibernate();
		Serial.println("waking up...");
	}


	if (digitalRead(PIN_SWITCHER) == LOW) {
		if (switchpin_released) {
			++currgate;
			switchpin_released = false;
		}
	} else {
		switchpin_released = true;
		const bool a = digitalRead(PIN_INPUT_A) == LOW;
		const bool b = digitalRead(PIN_INPUT_B) == LOW;
		const bool result = executeLogicFunction(currgate, a, b);
		digitalWrite(PIN_OUTPUT, result ? HIGH : LOW);
	}

	delay(100);
}




