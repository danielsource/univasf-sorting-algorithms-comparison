#define LENGTH(arr) ((int)(sizeof(arr) / sizeof((arr)[0])))

typedef struct Sequence Sequence;

typedef struct TestCase TestCase;

typedef struct {
	int comp, chan, wtime;	/* comparisons, changes, walltime (elapsed time) */
} Metric;

struct Sequence {
	char *name;
	int *(*initpop)(int len);
	int len;
	int *data;
};

typedef Metric SortFunc(Sequence seq);
