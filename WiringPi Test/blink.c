#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <errno.h>

#include <wiringPi.h>


static const int kLed = 17;



static inline void cleanup()
{
	puts("cleanup");
	digitalWrite(kLed, LOW);
}


static void sig_handler(int sig)
{
	cleanup();
	exit(sig);	
}


int main(void)
{
	if (wiringPiSetupGpio()) {
		printf("Couldn't initialize WiringPi: %d", errno);
		return EXIT_FAILURE;
	} 

	signal(SIGINT, sig_handler);
	signal(SIGKILL, sig_handler);
	signal(SIGTERM, sig_handler);

	pinMode(kLed, OUTPUT);
	int delaytime = 0;
	bool up = true;

	for (;;) {
		digitalWrite(kLed, HIGH);
		delay(delaytime);
		digitalWrite(kLed, LOW);
		delay(delaytime);

		if (up) {
			delaytime += 15;
			if (delaytime >= 300)
				up = false;
		} else {
			delaytime -= 15;
			if (delaytime <= 0)
				up = true;
		}	
	}


	return EXIT_SUCCESS;
}

