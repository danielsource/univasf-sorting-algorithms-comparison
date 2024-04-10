#include "test.h"

static Metric M;

static int max(int *a, int len, int i, int j, int k) {
	int m = i;
	if (j < len && a[j] > a[m]) {
		m = j;
		++M.comp;
	}
	if (k < len && a[k] > a[m]) {
		m = k;
		++M.comp;
	}
	return m;
}

static void downheap(int *a, int len, int i) {
	while (1) {
		int j = max(a, len, i, 2*i + 1, 2*i + 2);
		if (j == i) {
			break;
		}
		int t = a[i];
		a[i] = a[j];
		a[j] = t;
		i = j;
		++M.swap;
	}
}

static void heapsort(int *a, int len) {
	int i;
	for (i = (len - 2) / 2; i >= 0; i--) {
		downheap(a, len, i);
	}
	for (i = 0; i < len; i++) {
		int t = a[len - i - 1];
		a[len - i - 1] = a[0];
		a[0] = t;
		++M.swap;
		downheap(a, len - i - 1, 0);
	}
}

Metric sort_heap(Sequence seq) {
	M.comp = M.swap = M.ptime = 0;
	heapsort(seq.data, seq.len);
	return M;
}
