#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logic-functions.h"


static inline void tobinstr(const unsigned char x, char bits[8])
{
	for (int i = 0; i < 8; ++i)
		bits[i] = (x & (0x80>>i)) != 0 ? '1' : '0';
}


static inline unsigned char strtobyte(const char bits[8])
{
	unsigned char byte = 0;

	for (int i = 0; i < 8 && bits[i] != '\0'; ++i)
		byte |= (bits[i] != '0') ? (0x80>>i) : 0x00;

	return byte;
}


int main(const int argc, const char* const * const argv)
{
	const char* const kLogicFuncsNames[] = {
		"AND", "OR", "NOT",
		"NAND", "NOR", "XOR", "XNOR"
	};
	
	const LogicFunc kLogicFuncs[] = {
		and, or, (LogicFunc)not,
		nand, nor, xor, xnor
	};

	const int kLogicFuncsCnt = sizeof(kLogicFuncs)/sizeof(kLogicFuncs[0]);

	if (argc < 3) {
		fprintf(stderr, "Usage: %s [8 bit binary value] [8 bit binary value]\n"
			"Example: %s 01010101 10101010\n",
		        argv[0], argv[0]);
		return EXIT_FAILURE;
	}

	char xbits[9];
	char ybits[9];
	char rbits[9];
	memset(xbits, 0, sizeof(xbits));
	memset(ybits, 0, sizeof(ybits));
	memset(rbits, 0, sizeof(rbits));

	const unsigned char x = strtobyte(argv[1]);
	const unsigned char y = strtobyte(argv[2]);

	tobinstr(x, xbits);
	tobinstr(y, ybits);

	for (int i = 0; i < kLogicFuncsCnt; ++i) {
		const LogicFunc lf = kLogicFuncs[i];

		if (lf == (LogicFunc)not) {
			tobinstr(not(x), rbits);
			printf("\n%s:\nx: %s\nr: %s\n", kLogicFuncsNames[i], xbits, rbits);
			tobinstr(not(y), rbits);
			printf("\n%s:\ny: %s\nr: %s\n", kLogicFuncsNames[i], ybits, rbits);
			continue;
		}

		tobinstr(lf(x, y), rbits);
		printf("\n%s:\nx: %s\ny: %s\nr: %s\n",
		       kLogicFuncsNames[i], xbits, ybits, rbits);
	}

	return EXIT_SUCCESS;
}

