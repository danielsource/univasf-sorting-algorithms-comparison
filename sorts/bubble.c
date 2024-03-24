#include "test.h"

static void sort_bubble_(int *a, int len) {
    int i, t, s = 1;
    while (s) {
        s = 0;
        for (i = 1; i < len; i++) {
            if (a[i] < a[i - 1]) {
                t = a[i];
                a[i] = a[i - 1];
                a[i - 1] = t;
                s = 1;
            }
        }
        --len;
    }
}

Metric sort_bubble(Sequence seq) {
	return (Metric){0};
}
