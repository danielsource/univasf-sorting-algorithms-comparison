#define LENGTH(arr) ((int)(sizeof(arr) / sizeof((arr)[0])))

typedef struct Sequence Sequence;

typedef struct {
	unsigned long long comp, swap;	/* comparisons, swaps, */
	double ptime;			/* CPU time (in ms) */
} Metric;

struct Sequence {
	char *name;
	int *(*initpop)(int len);
	int len;
	int *data;
};

typedef Metric SortFunc(Sequence seq);
