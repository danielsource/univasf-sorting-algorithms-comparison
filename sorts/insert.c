#include "test.h"

static Metric M;

static void insertsort(int *a, int len) {
	int i, j, key;
	for (i = 1; i < len; ++i) {
		key = a[i];
		j = i;
		if (j > 0 && key < a[j-1]) {
			do {
				a[j] = a[j-1];
				--j;
				++M.swap;
				++M.comp;
			} while (j > 0 && key < a[j-1]);
		}
		a[j] = key;
		++M.comp;
		++M.swap;
	}
}

Metric sort_insert(Sequence seq) {
	M.comp = M.swap = M.ptime = 0;
	insertsort(seq.data, seq.len);
	return M;
}
