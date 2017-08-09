/**
	\author: Trasier
*/
#ifndef LI_OUTPUT_H
#define LI_OUTPUT_H

#include <bits/stdc++.h>
using namespace std;

struct move_t {
	double x, y;
	double arrive, leave;
	vector<int> bucket;

	void print() const {
		int nBucket = bucket.size();
		printf("%.8lf %.8lf %.8lf %.8lf %d", x, y, arrive, leave, nBucket);
		for (int i=0; i<nBucket; ++i) {
			// if (i == nBucket-1)
			// 	printf("%d\n", bucket[i]);
			// else
			printf(" %d", bucket[i]+1);
		}
		putchar('\n');	
	}
};

void dumpOutput(const vector<vector<move_t> >& workerMove);
void dumpOutput(const vector<move_t>& moves);

void dumpOutput(const vector<vector<move_t> >& workerMove) {
	int nWorker = workerMove.size();

	for (int i=0; i<nWorker; ++i) {
		const vector<move_t>& moves = workerMove[i];
		int nMove = moves.size();
		printf("%d %d\n", i+1, nMove);
		dumpOutput(moves);
	}
}

void dumpOutput(const vector<move_t>& moves) {
	int nMove = moves.size();

	for (int i=0; i<nMove; ++i)
		moves[i].print();
}

#endif
