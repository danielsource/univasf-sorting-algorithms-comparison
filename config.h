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
	int *a = malloc(len * sizeof(int));
	int c = RAND_MAX/len + 1;	/* https://c-faq.com/lib/randrange.html */
	for (int i = 0; i < len; ++i)
		a[i] = rand() / c;
	return a;
}

Metric sort_bubble(Sequence seq);
Metric sort_insert(Sequence seq);
Metric sort_quick(Sequence seq);
Metric sort_merge(Sequence seq);
Metric sort_heap(Sequence seq);

int repeattest = 3;	/* repeat x times and get the average */

Sequence seqs[] = {
	{"ascending", init_asc, 2000},
	{"ascending", init_asc, 16000},
	{"ascending", init_asc, 128000},
	{"descending", init_des, 2000},
	{"descending", init_des, 16000},
	{"descending", init_des, 128000},
	{"random", init_ran, 2000},
	{"random", init_ran, 16000},
	{"random", init_ran, 128000}
};

struct TestCase {
	char *name;
	SortFunc *sort;
	Metric mets[LENGTH(seqs)];
};

TestCase tests[] = {
	{"Bubble sort", sort_bubble},
	{"Insertion sort", sort_insert},
	{"Quicksort", sort_quick},
	{"Mergesort", sort_merge},
	{"Heapsort", sort_heap},
};
