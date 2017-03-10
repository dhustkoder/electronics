#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>


static inline void cleanup()
{
	puts("cleanup");
	digitalWrite(0, LOW);
}


static void sig_handler(int sig)
{
	cleanup();
	exit(sig);	
}


int main(void)
{
	wiringPiSetup();

	signal(SIGINT, sig_handler);
	signal(SIGKILL, sig_handler);
	signal(SIGTERM, sig_handler);

	pinMode(0, OUTPUT);
	int delaytime = 0;
	unsigned char up = 1;

	for (;;) {
		digitalWrite(0, HIGH);
		delay(delaytime);
		digitalWrite(0, LOW);
		delay(delaytime);

		if (up) {
			delaytime += 15;
			if (delaytime >= 300)
				up = 0;
		} else {
			delaytime -= 15;
			if (delaytime <= 0)
				up = 1;
		}	
	}


	return EXIT_SUCCESS;
}

