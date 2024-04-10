#include "test.h"

static Metric M;

static void quicksort(int *a, int len) {
	if (len < 2)
		return;
	int pivot = a[len / 2];
	int i, j, t;
	for (i = 0, j = len - 1; ; ++i, --j) {
		if (a[i] < pivot) {
			do  {
				++i;
				++M.comp;
			} while (a[i] < pivot);
		}
		++M.comp;
		if (a[j] > pivot) {
			do  {
				--j;
				++M.comp;
			} while (a[j] > pivot);
		}
		++M.comp;
		if (i >= j)
			break;
		t = a[i];
		a[i] = a[j];
		a[j] = t;
		++M.swap;
	}
	quicksort(a, i);
	quicksort(a + i, len - i);
}

Metric sort_quick(Sequence seq) {
	M.comp = M.swap = M.ptime = 0;
	quicksort(seq.data, seq.len);
	return M;
}
