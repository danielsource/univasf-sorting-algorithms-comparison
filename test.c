#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "test.h"

typedef struct TestCase TestCase;

#include "config.h"

static bool is_array_sorted(int *a, int len) {
	for (int i = 0; i < len-1; ++i)
		if (a[i] > a[i+1])
			return false;
	return true;
}

static void test(TestCase t) {
	for (int i = 0; i < LENGTH(seqs); ++i) {
		Sequence seq = seqs[i];
		int repeat = repeattest;
		seq.data = NULL;

		while (repeat--) {
			free(seq.data);
			seq.data = malloc(seq.len * sizeof(int));
			memcpy(seq.data, seqs[i].data, seq.len * sizeof(int));

			Metric aux = {0};
			clock_t t_beg, t_end;
			t_beg = clock();
			aux = t.sort(seq);
			t_end = clock();
			aux.ptime = (double)(t_end - t_beg) / (CLOCKS_PER_SEC/1000);

			t.mets[i].comp += aux.comp;
			t.mets[i].swap += aux.swap;
			t.mets[i].ptime += aux.ptime;
		}

		t.mets[i].comp /= repeattest;
		t.mets[i].swap /= repeattest;
		t.mets[i].ptime /= repeattest;

		printf("%s,%d,%s,%lld,%lld,%.3lf,%s\n",
				t.name,
				seqs[i].len,
				seqs[i].name,
				t.mets[i].comp,
				t.mets[i].swap,
				t.mets[i].ptime,
				is_array_sorted(seq.data, seq.len) ? "sorted" : "UNSORTED");

		free(seq.data);
	}
}

int main(void) {
	srand(time(0));

	for (int i = 0; i < LENGTH(seqs); ++i)
		seqs[i].data = seqs[i].initpop(seqs[i].len);
	printf("Algorithm,Load number,Init sort,Comparisons,Swaps,CPU time (ms),Is sorted?\n");
	for (int i = 0; i < LENGTH(tests); ++i)
		test(tests[i]);
	for (int i = 0; i < LENGTH(seqs); ++i)
		free(seqs[i].data);

	return 0;
}
