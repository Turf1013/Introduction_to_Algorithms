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

inline LL calcPairH(const int sp1, const int sp2) {
	return 1LL * sp1 * spatialN + sp2;
}

void init(const string& networkFileName) {
	vector<int> items;
	vector<networkEdge_t> edges;
	int edgeN;

	readInput_network(networkFileName, workerN, taskN, dw, dr, vw,
						slotN, gridLength, gridWidth, items, edgeN, edges);

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

	vector<int> workers, tasks;

	for (int i=0; i<workerN; ++i) {
		int workerH = calcSpatialH(items[i<<1], items[(i<<1)|1]);
		workers.push_back(workerH);
	}
	for (int j=workerN; j<workerN+taskN; ++j) {
		int taskH = calcSpatialH(items[j<<1], items[(j<<1)|1]);
		tasks.push_back(taskH);
	}

	int u, v, f;
	guideMap.clear();
	for (int i=0; i<edgeN; ++i) {
		u = edges[i].u;
		v = edges[i].v;
		f = edges[i].f;
		#ifdef LOCAL_DEBUG
		assert(u>=0 && u<workers.size());
		assert(v>=0 && v<tasks.size());
		assert(guideMap.count(calcPairH(workers[u], tasks[v])) == 0);
		#endif
		LL pairH = calcPairH(workers[u], tasks[v]);
		guideMap[pairH] = f;
		workerCap[workers[u]] += f;
		taskCap[tasks[v]] += f;
	}
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
		int spatialH = calcSpatialH(slotId, gridId);
		if (typeId==0 && workerFlow[spatialH]<workerCap[spatialH]) {
			++workerFlow[spatialH];

			// calculate the number of valid task
			int validN = 0, validId;
			for (auto taskH : taskQueue) {
				LL pairH = calcPairH(spatialH, taskH);
				if (guideMap[pairH]>0 && taskFlow[taskH]<taskCap[taskH]) {
					++validN;
				}
			}
			// random selected or add into the waitQueue
			if (validN > 0) {
				validId = rand() % validN;
				validN = 0;
				for (int j=0; j<taskQueue.size(); ++j) {
					int taskH = taskQueue[j];
					LL pairH = calcPairH(spatialH, taskH);
					if (guideMap[pairH]>0 && taskFlow[taskH]<taskCap[taskH] && validN++==validId) {
						if (--guideMap[pairH] == 0)
							guideMap.erase(pairH);
						++taskFlow[taskH];
						taskQueue[j] = *taskQueue.rbegin();
						taskQueue.pop_back();
						break;
					}
				}
				++ret;
			} else {
				workerQueue.push_back(spatialH);
			}
		} else if (typeId==1 && taskFlow[spatialH]<taskCap[spatialH]) {
			++taskFlow[spatialH];
			
			// calculate the number of valid worker
			int validN = 0, validId;
			for (auto workerH : workerQueue) {
				LL pairH = calcPairH(workerH, spatialH);
				if (guideMap[pairH]>0 && workerFlow[workerH]<workerCap[workerH]) {
					++validN;
				}
			}
			// random selected or add into the waitQueue
			if (validN > 0) {
				validId = rand() % validN;
				validN = 0;
				for (int j=0; j<workerQueue.size(); ++j) {
					int workerH = workerQueue[j];
					LL pairH = calcPairH(workerH, spatialH);
					if (guideMap[pairH]>0 && workerFlow[workerH]<workerCap[workerH] && validN++==validId) {
						if (--guideMap[pairH] == 0)
							guideMap.erase(pairH);
						++workerFlow[workerH];
						workerQueue[j] = *workerQueue.rbegin();
						workerQueue.pop_back();
						break;
					}		
				}
				++ret;
			} else {
				taskQueue.push_back(spatialH);
			}
		}

		#ifdef WATCH_MEM
		watchSolutionOnce(getpid(), usedMemory);
		#endif
	}

	return ret;
}

int solve(const string& networkFileName) {
	init(networkFileName);
	int ret = Polar();
	return ret;
}

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	program_t begProg, endProg;
	string networkFileName;

	if (argc > 1) {
		networkFileName = string(argv[1]);
	} else {
		perror("no valid network File");
		exit(1);
	}
	if (argc > 2)
		freopen(argv[2], "r", stdin);
	if (argc > 3)
		freopen(argv[3], "w", stdout);

	save_time(begProg);
	int nPairs = solve(networkFileName);
	save_time(endProg);

	double usedTime = calc_time(begProg, endProg);
	#ifdef WATCH_MEM
	printf("Polar %d %.4lf %d\n", nPairs, usedTime, usedMemory/1024);
	#else
	printf("Polar %d %.4lf\n", nPairs, usedTime);
	#endif
	
	return 0;
}