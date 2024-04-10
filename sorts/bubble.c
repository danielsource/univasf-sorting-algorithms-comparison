#include "test.h"

static Metric M;

static void bubblesort(int *a, int len) {
	int i, t, s = 1;
	while (s) {
		s = 0;
		for (i = 1; i < len; i++) {
			if (a[i] < a[i-1]) {
				t = a[i];
				a[i] = a[i-1];
				a[i-1] = t;
				s = 1;
				++M.swap;
			}
			++M.comp;
		}
		--len;
	}
}

Metric sort_bubble(Sequence seq) {
	M.comp = M.swap = M.ptime = 0;
	bubblesort(seq.data, seq.len);
	return M;
}
