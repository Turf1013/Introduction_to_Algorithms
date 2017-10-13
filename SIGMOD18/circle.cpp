/**
	\author: 	Trasier
	\date: 		2017.10.13
*/
#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
#include "global.h"
// #include "monitor.h"

// #define LOCAL_DEBUG

struct guard_t {
	int idx;
	double curTime;
};

int V, N, C, M;
position_t* points = NULL;
order_t* orders = NULL;
guard_t driver;
double *pickTime;
double *deliverTime;
int *mark;
int *route;

void initial_route() {
	typedef pair<double,double> pdd;
	vector<pair<pdd,int> > ps;
	for (int i=0; i<V; ++i) {
		pdd p = make_pair(points[i].x, points[i].y);
		ps.push_back(make_pair(p, i));
	}
	
	sort(ps.begin(), ps.end());
	
	for (int i=0; i<V; i+=10) {
		vector<int> permu;
		for (int j=0; i+j<V&&j<10; ++j) {
			permu.push_back(ps[i+j].second);
		}
		sort(permu.begin(), permu.end());
		double maxLen = inf, tmpLen;
		do {
			tmpLen = 0;
			for (int j=1; j<permu.size(); ++j) {
				int aid = permu[j-1], bid = permu[j];
				tmpLen += Length(points[aid], points[bid]);
			}
			if (tmpLen < maxLen) {
				for (int j=0; i+j<V&&j<10; ++j) {
					route[i+j] = permu[j];
				}
			}
		} while(next_permutation(permu.begin(), permu.end()));
	}
	
	#ifdef LOCAL_DEBUG
	for (int i=0; i<V; ++i)
		assert(route[i] != -1);
	#endif
}

void init() {
	mark = new int[M];
	pickTime = new double[M];
	deliverTime = new double[M];
	for (int i=0; i<M; ++i) {
		pickTime[i] = deliverTime[i] = inf;
		mark[i] = -1;
	}
	
	#ifdef LOCAL_DEBUG
	printf("V = %d, N = %d, C = %d, M = %d\n", V, N, C, M);
	#endif
	
	route = new int[V];
	memset(route, -1, sizeof(int)*V);
	initial_route();
	
	driver.idx = 0;
	driver.curTime = 0;
}

void FreeMem() {
	delete[] points;
	delete[] orders;
	delete[] pickTime;
	delete[] deliverTime;
	delete[] mark;
	delete[] route;
}

void scheduling(const int orderId) {
	order_t& order = orders[orderId];
	int& idx = driver.idx;
	double& curTime = driver.curTime;
	double tmpTime;
	position_t curLoc, nextLoc;
	
	while (true) {
		curLoc = points[route[idx]];
		nextLoc = points[route[(idx+1)%V]];
		tmpTime = curTime + Length(curLoc, nextLoc);
		
	}
}

void greedyInsert() {
	int driverId, orderId, pickLoc, deliverLoc;
	double flowTime;

	for (orderId=0; orderId<M; ++orderId) {
		updateDriver(driverId, orders[orderId].tid);
		scheduling(orderId, driverId);
	}

	for (driverId=0; driverId<N; ++driverId) {
		driver_t& driver = drivers[driverId];
		while (!driver.isEmpty())
			updateMove(driverId);
	}
}

double calcResult() {
	double ans = 0;

	for (int orderId=0; orderId<M; ++orderId) {
		#ifdef LOCAL_DEBUG
		assert(mark[orderId] == 1);
		#endif
		ans += deliverTime[orderId]-orders[orderId].tid;
	}

	return ans;
}

double solve() {
	init();

	greedyInsert();

	double flowTime = calcResult();
	return flowTime;
}

int main(int argc, char **argv) {
	string execName("GreedyInsert");

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
