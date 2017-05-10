#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	char alpha[8] = { 0 };

	for (const char* p = expr; *p != '\0'; ++p) {
		if (*p >= 'A' && *p <= 'H') {
			int i;

			for (i = 0; i < cnt; ++i)
				if (alpha[i] == *p)
					break;

			if (i == cnt)
				alpha[cnt++] = *p;
		}
	}

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
	memset(bools, 0, sizeof(bools));

	for (int i = 0; i < lines; ++i) {
		char* line = &buffer[linechars * i];
		bitstostr(bits, i, line);

		for (int j = bits; j > 0; --j)
			bools[bits - j] = (i&(0x01<<(j - 1)))>>(j - 1);

		const char* p = expr;
		signed char result = -1;

		for (int j = 0; j < bits; j += 2) {
			while (*p != '\0' && (*p < 'A' || *p > 'H'))
				++p;

			const unsigned char x = *(p - 1) == '~'
				? !bools[get_bit_index(*p)]
				: bools[get_bit_index(*p)];
			++p;

			while (*p != '\0' && (*p < 'A' || *p > 'H'))
				++p;

			const unsigned char y = *(p - 1) == '~'
				? !bools[get_bit_index(*p)]
				: bools[get_bit_index(*p)];

			++p;

			LogicFunc lfun = NULL;
			for (const char* pp = p - 1; pp >= expr; --pp) {
				lfun = get_logic_func(*pp);
				if (lfun != NULL)
					break;
			}

			if (lfun != NULL) {
				if (result != -1)
					result = lfun(result, lfun(x, y));
				else
					result = lfun(x, y);
			}
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

	char* const table = maketbl(argv[1]);

	printf("%s", table);

	free(table);
	return EXIT_SUCCESS;
}




