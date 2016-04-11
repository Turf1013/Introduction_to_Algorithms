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


/*
	qsort with multi-key
*/
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


/*
	ternary search tree:`tst`
*/
#define left(p) 	(p)->lokid
#define right(p)	(p)->hikid
#define mid(p)		(p)->eqkid
#define newNode(rt, ch)\
{\
	rt = (Ndptr)malloc(sizeof(Node));\
	(rt)->splitchar = ch;\
	(rt)->lokid = (rt)->hikid = (rt)->eqkid = NULL;\
}

Ndptr tst_rt;

void tst_hard_Insert(char *s) {
	#ifdef storeStr
	char *ss = s;
	#endif /* storeStr */
	int d;
	//char ch;
	// Ndptr p, q;
	// int flag = 1;

	// if (rt == NULL) {
	// 	ch = *s;
	// 	newNode(rt, ch);
	// }

	// p = tst_rt;
	// while (flag) {
	// 	ch = *s;
	// 	if (ch == p->splichar) {
	// 		if (ch == 0)	flag = 0;
	// 		++s;
	// 		if (ch && mid(p) == NULL) newNode(mid(p), *s);
	// 		q = mid(p);
	// 	} else if (ch < p->splichar) {
	// 		if (left(p) == NULL) newNode(left(p), ch);
	// 		q = left(p);
	// 	} else {
	// 		if (right(p) == NULL) newNode(right(p), ch);
	// 		q = right(p);
	// 	}
	// };
	Ndptr q, *p;

	p = &tst_rt;
	while ((q = *p) != NULL) {
		if ((d = *s-q->splitchar) == 0) {
			if (*s++ == 0)	return ;
			p = &(mid(q));
		} else if (d < 0) {
			p = &(left(q));
		} else {
			p = &(right(q));
		}
	}

	for (;;) {
		newNode(*p, *s);
		q = *p;
		if (*s++ == 0) {
			#ifdef storeStr
			mid(q) = (Ndptr) ss;
			#endif /* storeStr */
			return;
		}
		p = &(mid(q));
	}
}

Ndptr tst_simple_Insert(Ndptr p, char *s) {
	if (p == NULL) {
		newNode(p, *s);
	}
	if (*s < p->splitchar) {
		left(p) = tst_simple_Insert(left(p), s);
	} else if (*s == p->splitchar) {
		if (*s)	mid(p) = tst_simple_Insert(mid(p), ++s);
	} else {
		right(p) = tst_simple_Insert(right(p), s);
	}
	return p;
}

int tst_Search(char *s) {
	Ndptr p = tst_rt;
	int d;

	while (p) {
		if ((d = *s-p->splitchar) == 0) {
			if (*s++ == 0)	return 1;
			p = mid(p);
		} else if (d < 0) {
			p = left(p);
		} else {
			p = right(p);
		}
	}
	return 0;
}

void tst_Delete(Ndptr rt) {
	if (rt) {
		tst_Delete(left(rt));
		tst_Delete(mid(rt));
		tst_Delete(right(rt));
		free(rt);
	}
}


/*
	Hash
*/
Hdptr *hashtable;
int tabsize;

void hash_init(int n) {
	tabsize = n;
	hashtable = (Hdptr *)malloc(sizeof(Hdptr) * tabsize);
	memset(hashtable, 0, sizeof(Hdptr) * tabsize);
}

unsigned getH(char *s) {
	unsigned ret = 0;
	while (*s)	ret = ret * 31 + *s++;
	return ret % tabsize;
}

void hash_Insert(char *s) {
	unsigned h = getH(s);
	Hdptr p = (Hdptr) malloc(sizeof(HNode));
	p->nxt = hashtable[h];
	p->s = s;
	hashtable[h] = p;
}

static inline int inline_strcmp(char *src, char *des) {
	for (; *src==*des; ++src,++des) if (*src == 0) return 0;
	return *src - *des;
}

int hash_Search(char *s) {
	Hdptr p;

	for (p=hashtable[getH(s)]; p; p=p->nxt) {
		if (inline_strcmp(s, p->s) == 0)	return 1;
	}
	return 0;
}

static void hash_Delete_Entry(Hdptr p) {
	if (p) {
		hash_Delete_Entry(p->nxt);
		free(p);
	}
}

void hash_Delete() {
	int i;

	for (i=0; i<tabsize; ++i) hash_Delete_Entry(hashtable[i]);
	free(hashtable);
}

/*
	trie
*/
Tdptr trie_rt;

void trie_Init() {
	int i;

	trie_rt = (Tdptr) malloc(sizeof(TNode));
	for (i=0; i<MAXK; ++i) trie_rt->nxt[i] = NULL;
	trie_rt->flag = 0;
}

void trie_Insert_v1(char *s) {
	int i, id;
	Tdptr p = trie_rt, q;

	while (*s) {
		id = *s - 'a';
		q = p->nxt[id];
		if (q == NULL)	{
			q = p->nxt[id] = (Tdptr) malloc(sizeof(TNode));
			for (i=0; i<MAXK; ++i) q->nxt[i] = NULL;
			q->flag = 0;
		}
		p = q;
		++s;
	}
	p->flag = 1;
}

void trie_Insert_v2(char *s) {
	int i, id;
	Tdptr p = trie_rt, q;

	while (*s) {
		id = *s - 'a';
		q = p->nxt[id];
		if (q == NULL)	break;
		p = q;
		++s;
	}

	while (*s) {
		id = *s - 'a';
		p->nxt[id] = (Tdptr) malloc(sizeof(TNode));
		p = p->nxt[id];
		for (i=0; i<MAXK; ++i) p->nxt[i] = NULL;
		p->flag = 0;
		++s;
	}

	p->flag = 1;
}

int trie_Search_v1(char *s) {
	int id;
	Tdptr p = trie_rt;

	while (*s) {
		id = *s - 'a';
		if (p->nxt[id] == NULL)	return 0;
		p = p->nxt[id];
		++s;
	}

	return p->flag;
}

int trie_Search_v2(char *s) {
	Tdptr p = trie_rt;
	for (; p && *s; ++s) p = p->nxt[*s-'a'];
	return p && p->flag;
}

void trie_Delete(Tdptr p) {
	int i;

	if (p) {
		for (i=0; i<MAXK; ++i) trie_Delete(p->nxt[i]);
		free(p);
	}
}

/*======================================================================*/
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
