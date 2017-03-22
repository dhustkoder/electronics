#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>

#include <wiringPi.h>


static const int kLed = 17;

static inline void run(unsigned int delaytime, time_t runtime);
static inline void cleanup();

static void sig_handler(int sig);


int main(void)
{
	if (wiringPiSetupGpio()) {
		fprintf(stderr, "Couldn't initialize WiringPi: %s", strerror(errno));
		return EXIT_FAILURE;
	} 

	signal(SIGINT, sig_handler);
	signal(SIGKILL, sig_handler);
	signal(SIGTERM, sig_handler);

	pinMode(kLed, OUTPUT);

	unsigned int delaytime = 0;
	unsigned int runtime = 5;
	char op = '\0';

	for (;;) {

		system("clear");
		
		printf("Delay time: %u ms\n"
		       "Run time:   %u s\n"
                       "::::::::::::::::::\n"
		       "Options:\n"
		       "r: Run\n"
		       "d: Set delay time\n"
		       "s: Set run time\n"
		       "e: Exit\n"
		       "::::::::::::::::::\n"
		       "Enter an option: ",
		       delaytime, runtime);

		scanf("%c%*c", &op);

		if (op == 'r') {
			run(delaytime, (time_t)runtime);
		} else if (op == 'd') {
			printf("Enter new delay time: ");
			scanf("%u%*c", &delaytime);
		} else if (op == 's') {
			printf("Enter new run time: ");
			scanf("%u%*c", &runtime);
		} else if (op == 'e') {
			break;
		} else {
			printf("Unknown option \'%c\'\n", op);
		}
	}

	return EXIT_SUCCESS;
}


void run(const unsigned int delaytime, const time_t runtime)
{
	puts("[:: Running ::]");

	if (delaytime > 0) {

		const time_t begin = time(NULL);

		do {
			digitalWrite(kLed, HIGH);
			delay(delaytime);
			digitalWrite(kLed, LOW);
			delay(delaytime);
		} while ((time(NULL) - begin) < runtime);

	} else {

		digitalWrite(kLed, HIGH);
		delay(runtime * 1000);
	}


	puts("[:: Done ::]");
	delay(500);

	cleanup();
}


void cleanup()
{
	puts("cleanup");
	digitalWrite(kLed, LOW);
}


void sig_handler(const int sig)
{
	cleanup();
	exit(sig);	
}

