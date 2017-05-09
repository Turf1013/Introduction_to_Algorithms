/**
	\author: Trasier
	\date: 2017.05.08
*/
#include <bits/stdc++.h>
using namespace std;

#include "monitor.h"
#include "input.h"
#include "output.h"

#define LOCAL_DEBUG

typedef long long LL;
vector<int> xy, yx;
vector<int> workerVisit, taskVisit;
vector<int> workerCap, workerFlow;
vector<int> taskCap, taskFlow;
unordered_map<int,int> guideMap;
int workerN, taskN;
double dw, dr, vw;
int slotN, gridLength, gridWidth, gridNum, spatialN;
#ifdef WATCH_MEM
int usedMemory = 0;
#endif

inline int calcSpatialH(const int slotId, const int gridId) {
	return slotId * gridNum + gridId;
}

void init(const string& predictFileName, const string& bipartiteFileName) {
	/**
		\step 1: parse from predict file.
	*/
	vector<predictItem_t> predictItems;

	readInput_predict(workerN, taskN, dw, dr, vw, slotN, gridLength, gridWidth, predictItems);

	gridNum = gridLength * gridWidth;
	spatialN = slotN * gridNum;
	workerCap.clear();
	workerFlow.clear();
	workerCap.resize(spatialN, 0);
	workerFlow.resize(spatialN, 0);

	taskCap.clear();
	taskFlow.clear();
	taskCap.resize(spatialN, 0);
	taskFlow.resize(spatialN, 0);

	for (int i=0; i<spatialN; ++i) {
		int workerCnt = predictItems[i].workerN, taskCnt = predictItems[i].taskN;
		if (i > 0) {
			workerCap[i] = workerCap[i-1] + workerCnt;
			taskCap[i] = taskCap[i-1] + taskCnt;

			workerFlow[i] = workerCap[i-1];
			taskFlow[i] = taskCap[i-1];
		} else {
			workerCap[i] = workerCnt;
			taskCap[i] = taskCnt;

			workerFlow[i] = 0;
			taskFlow[i] = 0;
		}
	}


	/**
		\step 2: parse from bipartie file
	*/
	vector<pair<int,int> > edges;

	readInput_bipartite(bipartiteFileName, edges);
	int edgeN = edges.size();

	xy.clear();
	yx.clear();
	xy.resize(workerN, -1);
	yx.resize(taskN, -1);
	
	workerVisit.clear();
	taskVisit.clear();
	workerVisit.resize(workerN, 0);
	taskVisit.resize(taskN, 0);

	for (int i=0; i<edgeN; ++i) {
		#ifdef LOCAL_DEBUG
		assert(edges[i].first>=0 && edges[i].first<xy.size());
		assert(edges[i].second>=0 && edges[i].second<yx.size());
		#endif
		xy[edges[i].first] = edges[i].second;
		yx[edges[i].second] = edges[i].first;
	}

	#ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMemory);
	#endif
}

int Polar() {
	int ret = 0;

	scanf("%d %d %lf %lf %lf %d %d %d", &workerN, &taskN, &dw, &dr, &vw, &slotN, &gridLength, &gridWidth);
	const int itemN = workerN + taskN;
	int typeId, slotId, gridId;
	vector<int> workerQueue;
	vector<int> taskQueue;

	for (int i=0; i<itemN; ++i) {
		scanf("%d %d %d", &typeId, &slotId, &gridId);
		int spatialId = calcSpatialH(slotId, gridId);

		if (typeId==0 && workerFlow[spatialId]<workerCap[spatialId]) {// worker
			int xid = workerFlow[spatialId], yid = xy[xid];

			if (workerVisit[xid]==0 && yid!=-1) {
				workerVisit[xid] = 1;
				if (taskVisit[yid] == 1) {
					workerVisit[xid] = taskVisit[yid] = -1;
					++ret;
				}
			}

			++workerFlow[spatialId];
		} else if (typeId==1 && taskFlow[spatialId]<taskCap[spatialId]) {// task
			int yid = taskFlow[spatialId], xid = yx[yid];

			if (taskVisit[yid]==0 && xid!=-1) {
				taskVisit[yid] = 1;
				if (workerVisit[xid] == 1) {
					workerVisit[xid] = taskVisit[yid] = -1;
					++ret;
				}
			}

			++taskFlow[spatialId];
		}

		#ifdef WATCH_MEM
		watchSolutionOnce(getpid(), usedMemory);
		#endif
	}

	return ret;
}

int solve(const string& predictFileName, const string& bipartiteFileName) {
	int ret;
	init(predictFileName, bipartiteFileName);
	ret = Polar();
	return ret;
}

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	program_t begProg, endProg;
	string predictFileName, bipartiteFileName;

	if (argc > 1) {
		predictFileName = string(argv[1]);
	} else {
		perror("no valid predict File");
		exit(1);
	}
	if (argc > 2) {
		bipartiteFileName = string(argv[2]);
	} else {
		perror("no valid network File");
		exit(1);	
	}
	if (argc > 3) 
		freopen(argv[3], "r", stdin);
	if (argc > 4)
		freopen(argv[4], "w", stdout);

	save_time(begProg);
	int nPairs = solve(predictFileName, bipartiteFileName);
	save_time(endProg);

	double usedTime = calc_time(begProg, endProg);
	#ifdef WATCH_MEM
	printf("Polar %d %.4lf %d\n", nPairs, usedTime, usedMemory/1024);
	#else
	printf("Polar %d %.4lf\n", nPairs, usedTime);
	#endif
	
	return 0;
}