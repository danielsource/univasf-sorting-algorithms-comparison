#include <stdlib.h>

#include "test.h"

static Metric M;

static void merge(int *a, int len, int m, int *x) {
	int i, j, k;
	for (i = 0; i < m; i++) {
		x[i] = a[i];
	}
	M.swap += m;
	for (i = 0, j = m, k = 0;;) {
		++M.comp;
		++M.swap;
		if (a[j] < x[i]) {
			a[k++] = a[j++];
			if (j >= len)
				break;
		} else {
			a[k++] = x[i++];
			if (i >= m)
				return;
		}
	}
	while (i < m)
		a[k++] = x[i++];
	M.swap += m;
}

static void mergesort(int *a, int len, int *x) {
	if (len < 2)
		return;
	int m = len / 2;
	if (len > 2) {
		mergesort(a, m, x);
		mergesort(a + m, len - m, x);
	}
	merge(a, len, m, x);
}

Metric sort_merge(Sequence seq) {
	M.comp = M.swap = M.ptime = 0;
	if (seq.len < 2)
		return M;
	int *x = malloc(seq.len/2 * sizeof(int));
	mergesort(seq.data, seq.len, x);
	free(x);
	return M;
}
