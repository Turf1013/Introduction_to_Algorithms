#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <limits.h>
#include <assert.h>
#include "rs_tst.h"
#include "log.h"

#define FILENAME "./data.in"
#define MAXN 100200
#define MAXL 60

#ifndef min
#define min(a, b) ((a)<(b) ? (a):(b))
#endif /* min */

#define swap(a, b)\
{\
	char *t = x[a];\
	x[a] = x[b];\
	x[b] = t;\
}
#define i2c(i) x[i][dep]

void swapn(int a, int b, int n, char *x[]) {
	while (n--)	{
		swap(a, b);
		++a;
		++b;
	}
}

void sortStr(char *x[], int n, int dep) {
	int a, b, c, d, r, v;

	if (n <= 1)	return ;
	a = rand() % n;
	swap(0, a)
	v = i2c(0);
	a = b = 1;
	c = d = n - 1;
	while (1) {
		while (b<=c && (r=i2c(b)-v) <=0) {
			if (r == 0)	{swap(a, b); ++a;}
			++b;
		}
		while (c>=b && (r=i2c(c)-v) >= 0) {
			if (r == 0) {swap(d, c); --d;}
			--c;
		}
		if (b > c)	break;
		swap(b, c);
		++b;
		--c;
	}

	r = min(a, b-a);
	swapn(0, b-r, r, x);
	r = min(d-c, n-1-d);
	swapn(b, n-r, r, x);
	r = b-a;
	sortStr(x, r, dep);
	if (v != 0)	sortStr(x+r, a+n-1-d, dep+1);
	r = d-c;
	sortStr(x+n-r, r, dep);
}

void sortedStr(char *x[], int n) {
	sortStr(x, n, 0);
}

typedef void (*sorted_ptr) (char *[], int);
char filename[80];
char words[MAXN][MAXL];
char *X[MAXN];
int n;

static void readWord(char *filename) {
	FILE *fin;

	fin = fopen(filename, "r");
	if (!fin) {
		fprintf(stderr, "Error: can't open file \"%s\"", filename);
		abort();
	}

	n = 0;
	while (fscanf(fin, "%s", words[n])!=EOF) {
		X[n] = words[n];
		++n;
	}

	fclose(fin);
}

static void dumpWord(char *filename) {
	FILE *fout;
	int i;

	fout = fopen(filename, "w");
	if (!fout) {
		fprintf(stderr, "Error: can't open file \"%s\"", filename);
		abort();
	}

	for (i=0; i<n; ++i)	fprintf(fout, "%s\n", X[i]);

	fclose(fout);
}

int qstrcomp(const void *a, const void *b) {
	return strcmp(*(char **)a, *(char **)b);
}

static void testSortStr() {
	program_t prog;

	readWord(filename);
	program_start(&prog);
	qsort(X, n, sizeof(char*), qstrcomp);
	program_end(stdout, &prog, "qsort-lib");
	dumpWord("data-lib.out");

	readWord(filename);
	program_start(&prog);
	sortedStr(X, n);
	program_end(stdout, &prog, "qsort-mk");
	dumpWord("data-mk.out");
}

int main(int argc, char **argv) {
	if (argc > 1) {
		strcpy(filename, argv[1]);
	} else {
		strcpy(filename, FILENAME);
	}

	testSortStr();

	return 0;
}
