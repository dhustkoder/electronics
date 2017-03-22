#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static float read_font_tension()
{
	float vt;

	printf("Enter Font Tesion: ");

	scanf("%f%*c", &vt);

	return vt;
}


static float compute_total_resistance(const float series[32][32], const unsigned char n_resistors[32], const int n_series)
{
	int series_trs[32];

	for (int i = 0; i < n_series; ++i) {

		series_trs[i] = 0;

		for (int j = 0; j < n_resistors[i]; ++j)
			series_trs[i] += series[i][j];
	}

	float divisor = 0;

	for (int i = 0; i < n_series; ++i)
		divisor += 1.0f / series_trs[i];

	return 1.0f / divisor;
}


int main(void)
{
	float series[32][32];
	unsigned char n_resistors[32];
	int serie_idx = 0;

	char opt;

	const float vt = read_font_tension();

	memset(series, 0, sizeof(float) * 32 * 32);
	memset(n_resistors, 0, sizeof(unsigned char) * 32);

	do {
		printf("o: open new serie\n"
		       "a: add new resitor to current serie\n"
		       "e: print result and exit\n"
		       "Enter option: ");

		scanf("%c%*c", &opt);

		if (opt == 'o') {

			if (n_resistors[serie_idx] == 0) {
				puts("Can't add new serie without adding at least one resistor to the current serie!");
				continue;
			}

			++serie_idx;

		} else if (opt == 'a') {
			float ohms;
			printf("enter new resistor's ohms: ");
			scanf("%f%*c", &ohms);
			series[serie_idx][n_resistors[serie_idx]] = ohms;
			++n_resistors[serie_idx];
		}


	} while (opt != 'e');


	for (int i = 0; i <= serie_idx; ++i) {
		printf("Serie %d:\n", (i + 1));
		for (int j = 0; j < n_resistors[i]; ++j)
			printf("R%d (%.2f ohms)\n", (j + 1), series[i][j]);
	}



	const float rt = compute_total_resistance(series, n_resistors, serie_idx + 1);
	const float it = vt / rt;

	printf("Vt = %.2f\nRt = %.2f\nIt = %.2f\n", vt, rt, it);

	return EXIT_SUCCESS;
}


