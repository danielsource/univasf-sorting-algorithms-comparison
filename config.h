Metric sort_bubble(Sequence seq);
Metric sort_insert(Sequence seq);
Metric sort_quick(Sequence seq);
Metric sort_merge(Sequence seq);
Metric sort_heap(Sequence seq);

int repeattest = 3;	      /* repeat x times and get the average */

Sequence seqs[] = {
	{"ascending", init_asc, 100},
	{"ascending", init_asc, 1000},
	{"ascending", init_asc, 10000},
	{"descending", init_des, 100},
	{"descending", init_des, 1000},
	{"descending", init_des, 10000},
	{"random", init_ran, 100},
	{"random", init_ran, 1000},
	{"random", init_ran, 10000}
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
