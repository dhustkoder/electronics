#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "logic-functions.h"


static inline LogicFunc get_logic_func(const char symbol)
{
	switch (symbol) {
	case '&': return and;
	case '|': return or;
	}

	return NULL;
}


static inline int get_bit_index(const char symbol)
{
	const int idx = ('A' - symbol);
	return idx < 0 ? -idx : idx;
}


static inline int bitscnt(const char* const expr)
{
	int cnt = 0;
	for (const char* p = expr; *p != '\0'; ++p)
		if (*p >= 'A' && *p <= 'H')
			++cnt;
	return cnt;
}


static inline void bitstostr(const int bits, unsigned char val, char* const out)
{
	const int shift = (0x80 >> (8 - bits));
	for (int i = 0; i < bits; ++i)
		out[i] = (val & (shift>>i)) != 0 ? '1' : '0';
}


static inline char* maketbl(const char* const expr)
{
	const int bits = bitscnt(expr);
	const int linechars = bits + 3;
	const int lines = (int) powf(2, bits);
	char* const buffer = calloc(linechars * lines + 1, sizeof(char));
	unsigned char bools[bits];
	unsigned char result;

	for (int i = 0; i < lines; ++i) {
		char* line = &buffer[linechars * i];
		bitstostr(bits, i, line);

		for (int j = 0; j < bits; ++j)
			bools[j] = (i&(0x01<<j))>>j;

		const char* p = expr;
		for (int j = result = 0; j < bits; j += 2) {
			while (*p != '\0' && (*p < 'A' || *p > 'H'))
				++p;

			const unsigned char x = *(p - 1) == '~' ? !bools[get_bit_index(*p)] : bools[get_bit_index(*p)];
			++p;

			while (*p != '\0' && (*p < 'A' || *p > 'H'))
				++p;

			const unsigned char y = *(p - 1) == '~' ? !bools[get_bit_index(*p)] : bools[get_bit_index(*p)];

			LogicFunc lfun;
			while (p >= expr) {
				lfun = get_logic_func(*p);
				if (lfun != NULL)
					break;
				--p;
			}

			if (lfun != NULL)
				result |= lfun(x, y);
		}

		line[linechars - 3] = ':';
		line[linechars - 2] = result != 0 ? '1' : '0';
		line[linechars - 1] = '\n';
	}

	return buffer;
}


int main(const int argc, const char* const * argv)
{
	if (argc < 2) {
		fprintf(stderr, "Usage: %s \"expression\"\n"
		        "Example: %s \"(A & B)\"\n", argv[0], argv[0]);
		return EXIT_FAILURE;
	}

	char* const buffer = maketbl(argv[1]);

	printf("%s", buffer);

	free(buffer);
	return EXIT_SUCCESS;
}




