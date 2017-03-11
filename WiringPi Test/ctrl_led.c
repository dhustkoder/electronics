#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>

#include <wiringPi.h>


static const int kLed = 17;


static inline void cleanup();
static void sig_handler(int sig);

static inline void run(int delaytime, time_t runtime);


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

	unsigned int delaytime = 0;
	unsigned int runtime = 5;
	char op = '\0';

	for (;;) {

		system("clear");
		
		printf("delay time: %u\n"
		       "run time: %u\n"
		       "r: run\n"
		       "d: set delay time\n"
		       "s: set run time\n"
		       "e: exit\n"
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


void run(const int delaytime, const time_t runtime)
{
	puts("[:: Running ::]");

	time_t begin = time(NULL);

	if (delaytime) {

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

void sig_handler(int sig)
{
	cleanup();
	exit(sig);	
}
