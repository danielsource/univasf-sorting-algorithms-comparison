#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "test.h"

static int *init_asc(int len) {
	int *a = malloc(len * sizeof(int));
	for (int i = 0; i < len; ++i)
		a[i] = i;
	return a;
}

static int *init_des(int len) {
	int *a = malloc(len * sizeof(int));
	for (int i = 0; i < len; ++i)
		a[i] = len-i-1;
	return a;
}

#if RAND_MAX <= 32767
#warning "RAND_MAX is less than or equal to 32767."
#endif
static int *init_ran(int len) {
	int *a = malloc(len * sizeof(int)), c = RAND_MAX/len + 1;
	for (int i = 0; i < len; ++i)
		a[i] = rand() / c;
	return a;
}

#include "config.h"

static bool is_array_sorted(int *a, int len) {
	for (int i = 0; i < len-1; ++i)
		if (a[i] > a[i+1])
			return false;
	return true;
}

static void test(TestCase t) {
	for (int i = 0; i < LENGTH(seqs); ++i) {
		Metric aux = {0};
		bool unsorted = false;
		int repeat = repeattest;

		printf("%s,%d,%s,", t.name, seqs[i].len, seqs[i].name);

		while (repeat--) {
			Sequence seq = {0};
			seq.name = seqs[i].name;
			seq.len = seqs[i].len;
			seq.data = malloc(seq.len * sizeof(int));
			memcpy(seq.data, seqs[i].data, seq.len * sizeof(int));

			aux = t.sort(seq);
			t.mets[i].comp += aux.comp;
			t.mets[i].chan += aux.chan;
			t.mets[i].wtime += aux.wtime;

			if (!is_array_sorted(seq.data, seq.len))
				unsorted = true;
			free(seq.data);
		}

		t.mets[i].comp /= repeattest;
		t.mets[i].chan /= repeattest;
		t.mets[i].wtime /= repeattest;
		printf(unsorted ? "unsorted" : "sorted");
		putchar('\n');
	}
}

int main(void) {
	srand(time(0));

	for (int i = 0; i < LENGTH(seqs); ++i)
		seqs[i].data = seqs[i].initpop(seqs[i].len);
	for (int i = 0; i < LENGTH(tests); ++i)
		test(tests[i]);
	for (int i = 0; i < LENGTH(seqs); ++i)
		free(seqs[i].data);

	return 0;
}
