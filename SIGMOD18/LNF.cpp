/**
	\author:	Trasier
	\date:		2017.10.28
*/
#include "LNF.h"

#define LOCAL_DEBUG

struct myDriver_t {
	int vid;
	position_t pos;
	double curTime;
};

int V, N, C, M;
myTreeNode_t* root = NULL;
vector<myTreeNode_t*> leafs;
set<myTreeNode_t*> knodes;
position_t* points = NULL;
order_t* orders = NULL;
myDriver_t* drivers;
double *pickTime;
double *deliverTime;

void updateNode(myTreeNode_t* leaf, int delta);

void init() {
	pickTime = new double[M];
	deliverTime = new double[M];
	for (int i=0; i<M; ++i) {
		pickTime[i] = deliverTime[i] = inf;
	}
	drivers = new myDriver_t[N];
	for (int i=0; i<N; ++i) {
		int idx = 0; //rand() % N;
		drivers[i].pos = points[idx];
	}
	HST_construction(V, points, root);
	for (int i=0; i<V; ++i) {
		leafs.push_back(NULL);
	}
	HST_pointToLeaf(V, root, leafs);

	#ifdef LOCAL_DEBUG
	printf("V = %d, N = %d, C = %d, M = %d\n", V, N, C, M);
	#endif
}

void FreeMem() {
	delete[] points;
	delete[] orders;
	delete[] drivers;
	delete[] pickTime;
	delete[] deliverTime;
	HST_delete(root);
}

position_t getEndPosition(myDriver_t& driver) {
	return driver.pos;
}

double assign(double curTime, int driverId) {
	myDriver_t& driver = drivers[driverId];
	position_t pos = getEndPosition(driver);
	double ret = curTime;

	vector<int> korders = HST_getKorders();

	return ret;
}

void LNF() {
	typedef pair<double,int> pdi;
	double curTime = 0.0;
	priority_queue<pdi, vector<pdi>, greater<pdi> > Q;

	for (int i=0; i<N; ++i) {
		Q.push(make_pair(curTime, i));
	}

	for (int i=0; i<M; ++i) {
		order_t& order = orders[i];
		while (Q.top().first < order.tid) {
			pdi p = Q.top();
			Q.pop();
			double finishTime = assign(p.first, p.second);
			if (finishTime < 0)
				finishTime = order.tid;
			Q.push(make_pair(finishTime, p.second));
		}
	}
}

double calcResult() {
	double ans = 0;

	for (int orderId=1; orderId<=M; ++orderId) {
		#ifdef LOCAL_DEBUG
		assert(deliverTime[orderId] < inf);
		#endif
		ans += deliverTime[orderId]-orders[orderId].tid;
	}

	return ans;
}

double solve() {
	init();
	LNF();
	return calcResult();
}

int main(int argc, char **argv) {
	string execName("LNF");

	string srcFileName;
	if (argc > 1) {
		srcFileName = string(argv[1]);
	}
	if (argc > 2)
		freopen(argv[2], "w", stdout);

	// step1: read Input
	if (srcFileName.empty()) {
		readInput(cin, V, N, C, M, points, orders);
	} else {
		readInput(srcFileName, V, N, C, M, points, orders);
	}

	#ifdef LOCAL_DEBUG
	fprintf(stderr, "finish reading input.\n");
	#endif

	// step2: online execute
	clock_t begTime, endTime;
	begTime = clock();
	double ans = solve();
	endTime = clock();

	#ifdef LOCAL_DEBUG
	fprintf(stderr, "finish solving.\n");
	#endif

	// step3: output result
	double usedTime = (endTime - begTime)*1.0 / CLOCKS_PER_SEC;
	#ifdef WATCH_MEM
	dumpResult(execName, ans, usedTime, usedMemory/1024.0);
	#else
	dumpResult(execName, ans, usedTime);
	#endif

	#ifdef LOCAL_DEBUG
	fprintf(stderr, "finish dumping.\n");
	#endif

	// step4: free memory
	FreeMem();

	#ifdef LOCAL_DEBUG
	fprintf(stderr, "finish free memory.\n");
	#endif

	fflush(stdout);

	return 0;
}

void updateNode(myTreeNode_t* leaf, int delta) {
	myTreeNode_t *p = leaf;

	while (p != NULL) {
		p->c += delta;
		if (p->c >= C) {
			if (knodes.count(p) == 0)
				knodes.insert(p);
		} else {
			if (knodes.count(p) > 0)
				knodes.erase(p);
		}
		p = p->fa;
	}
}
