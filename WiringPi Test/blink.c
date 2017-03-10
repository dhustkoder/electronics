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
	digitalWrite(0, LOW);	


	printf("o: turn on/off\ne: exit\n");

	char op;
	int status = LOW;

	while (1) {
		printf("Enter op: ");
		scanf("%c%*c", &op);

		if (op == 'o')
			status = status == LOW ? HIGH : LOW;
		else if (op == 'e')
			break;
		else
			printf("No option %c\n", op);

		digitalWrite(0, status);
	};


	cleanup();
	return EXIT_SUCCESS;
}

