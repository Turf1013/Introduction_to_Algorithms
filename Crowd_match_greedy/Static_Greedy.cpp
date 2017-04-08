/**
	\author: Trasier
	\date: 2017.04.02
*/
#include <bits/stdc++.h>
using namespace std;
//#pragma comment(linker,"/STACK:102400000,1024000")
#include "input.h"
#include "monitor.h"

//#define AT_THE_SERVER
#define LOCAL_DEBUG

enum rule_t {
	worker, task
};

union W_un {
	double cost;
	double pay;
	double rate;
};
	
struct node_t {
	int id;				// id
	rule_t type;		// 0: task, 1: worker
	pair<double, double> loc;	// location
	int	cap;			// capacity
	int flow;			// flow
	double rad;			// radius	
	W_un cost;			// cost
	int begTime, endTime;	// time interval

	void print() {
		if (type == worker)
		 	printf("id = %d, loc = (%.2lf, %.2lf), rad = %.2lf, cap = %d, time = (%d, %d)\n",
		 			id, loc.first, loc.second, rad, cap, begTime, endTime);
		else
			printf("id = %d, loc = (%.2lf, %.2lf), time = (%d, %d)\n",
		 			id, loc.first, loc.second, begTime, endTime);
	}
};

bool satisfyLoc(const node_t& worker, const node_t& task);
bool satisfy(const node_t& worker, const node_t& task);

vector<vector<double> > weightArr;
inline double calcCost(const node_t& task, const node_t& worker) {
	#ifdef LOCAL_DEBUG
	assert(worker.id>=0 && worker.id<weightArr.size());
	assert(task.id>=0 && task.id<weightArr[worker.id].size());
	#endif
	double ret = weightArr[worker.id][task.id];
	if (!satisfyLoc(worker, task)) ret = 0.0;
	return ret;
}

inline double Length(pair<double,double> pa, pair<double,double> pb) {
	return sqrt( (pa.first-pb.first)*(pa.first-pb.first) + (pa.second-pb.second)*(pa.second-pb.second) );
}

inline double Length2(pair<double,double> pa, pair<double,double> pb) {
	return (pa.first-pb.first)*(pa.first-pb.first) + (pa.second-pb.second)*(pa.second-pb.second);
}

const double eps = 1e-6;
inline int dcmp(double a) {
	if (fabs(a) < eps)
		return 0;
	return a>0 ? 1:-1;
}

struct Greedy_t {
	struct vertex_t {
		int u, v;
		double w;
		
		vertex_t(int u=0, int v=0, double w=0):
			u(u), v(v), w(w) {}
			
		bool operator<(const vertex_t& o) const {
			return w < o.w;
		}
	};
	
	const double INF = 1e18;
	priority_queue<vertex_t> Q;
	vector<int> yx, xy;
	int n;
	
	Greedy_t() {
		init();
	}
	
	void init(int n=0) {
		this->n = n;
		clear();
		yx.resize(n, -1);
		xy.resize(n, -1);
	}
	
	void clear() {
		yx.clear();
		xy.clear();
		while (!Q.empty())
			Q.pop();
	}
	
	void build(const vector<int>& T_delta, const vector<int>& W_delta, 
				const vector<node_t>& tasks, const vector<node_t>& workers) {
		const int Tsz = T_delta.size();
		const int Wsz = W_delta.size();
		int vertexN = max(Tsz, Wsz);
		
		init(vertexN);
		for (int i=0; i<vertexN; ++i) {
			const int workerId = (i < Wsz) ? W_delta[i] : -2;

			for (int j=0; j<vertexN; ++j) {
				const int taskId = (j < Tsz) ? T_delta[j] : -2;

				double cost;
				if (workerId==-2 || taskId==-2) {
					cost = 0.0;
				} else {
					cost = calcCost(tasks[taskId], workers[workerId]);
				}

				Q.push(vertex_t(i, j, cost));
			}

			// #ifdef LOCAL_DEBUG
			// printf("%d: sz = %d, vertexN = %d\n", i, (int)g[i].size(), vertexN);
			// assert(g[i].size() == vertexN);
			// #endif
		}

		#ifdef LOCAL_DEBUG
		assert(Q.size() == vertexN * vertexN);
		#endif
	}
	
	void GreedyMatch(const vector<int>& T_delta, const vector<int>& W_delta, 
					const vector<node_t>& tasks, const vector<node_t>& workers) {
		const int Tsz = T_delta.size();
		const int Wsz = W_delta.size();
		vertex_t ver;
		int taskId, workerId;
		
		while (!Q.empty()) {
			ver = Q.top();
			Q.pop();
			if (xy[ver.u]>=0 || yx[ver.v]>=0) continue;

			workerId = (ver.u<Wsz) ? W_delta[ver.u] : -2;
			taskId = (ver.v<Tsz) ? T_delta[ver.v] : -2;

			
			if (workerId>=0 && taskId>=0) {
				const node_t& workerNode = workers[workerId];
				const node_t& taskNode = tasks[taskId]; 
				
				if (satisfy(workerNode, taskNode)) {
					xy[ver.u] = ver.v;
					yx[ver.v] = ver.u;
				}
			} else {
				xy[ver.u] = ver.v;
				yx[ver.v] = ver.u;	
			}
		}
	}
	
	void match(const vector<int>& T_delta, const vector<int>& W_delta, const vector<node_t>& tasks, const vector<node_t>& workers) {
		GreedyMatch(T_delta, W_delta, tasks, workers);
	}
};

typedef long long LL;
int n, m, umax;
double utility;
Greedy_t greedy;
int usedMemory;

void init(int taskN, int workerN, int Umax) {
	n = workerN;
	m = taskN;
	umax = Umax;
	utility = 0;
	usedMemory = 0;
}

void nextSeq(ifstream& fin, node_t& nd) {
	int timeId;
	string stype;

	fin >> nd.begTime >> stype;
	if (stype[0] == 'w') {
		nd.type = worker;
		fin >> nd.id >> nd.loc.first >> nd.loc.second >> nd.rad >> nd.cap >> nd.endTime >> nd.cost.rate;
		nd.endTime += nd.begTime;
	} else {
		nd.type = task;
		fin >> nd.id >> nd.loc.first >> nd.loc.second >> nd.endTime >> nd.cost.pay;
		nd.endTime += nd.begTime;
	}

	nd.flow = 0;
	nd.cap = 1;
	nd.endTime = 1e8;

	// #ifdef LOCAL_DEBUG
	// nd.print();
	// #endif
}

inline bool satisfyLoc(const node_t& worker, const node_t& task) {
	// 4. condition of location
	if (Length2(worker.loc, task.loc) > worker.rad * worker.rad)
		return false;
	
	return true;
}

inline bool satisfyCap(const node_t& worker, const node_t& task) {
	// 2&3. capacity of worker & task
	if (worker.cap<=worker.flow || task.cap<=task.flow)
		return false;
	return true;
}

inline bool satisfyTime(const node_t& worker, const node_t& task) {
	// 1. condition of deadline
	if (!(worker.begTime<=task.endTime && task.begTime<=worker.endTime))
		return false;
	return true;
}

bool satisfy(const node_t& worker, const node_t& task) {
	// return satisfyCap(worker, task) && satisfyTime(worker, task) && satisfyLoc(worker, task);
	return satisfyCap(worker, task) && satisfyLoc(worker, task);
}

void addOneMatch(node_t& task, node_t& worker) {
	// add cost to utility
	utility += calcCost(task, worker);
	// update the capacity of task & worker
	++task.flow;
	++worker.flow;
}

void Static_Greedy(ifstream& fin, int seqN) {
	vector<int> W_delta, T_delta;
	node_t node;
	vector<node_t> tasks, workers;
	int taskId, workerId;
	
	while (seqN--) {
		workerId = taskId = -1;
		nextSeq(fin, node);
		if (node.type == task) { // node is task
			taskId = tasks.size();
			tasks.push_back(node);
		} else {
			workerId = workers.size();
			workers.push_back(node);
		}
		
		if (node.type == task) {
			for (int i=0; i<node.cap; ++i)
				T_delta.push_back(taskId);
		} else {
			for (int i=0; i<node.cap; ++i)
				W_delta.push_back(workerId);
		}
	}

	greedy.build(T_delta, W_delta, tasks, workers);	
	#ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMemory);
	#endif
	greedy.match();

	const int Tsz = T_delta.size();
	const int Wsz = W_delta.size();

	for (int x=0; x<greedy.xy.size(); ++x) {
		int y = greedy.xy[x];
		
		if (y < 0) continue;

		const int workerId = (x < Wsz) ? W_delta[x] : -2;
		const int taskId = (y < Tsz) ? T_delta[y] : -2;

		if (workerId>=0 && taskId>=0) {
			#ifdef LOCAL_DEBUG
			assert(satisfy(workers[workerId], tasks[taskId]));
			#endif
			addOneMatch(tasks[taskId], workers[workerId]);
		}
	}

	#ifdef LOCAL_DEBUG
	int taskFlow = 0, workerFlow = 0;
	int freeTask = 0, freeWorker = 0;
	for (int i=0; i<tasks.size(); ++i) {
		assert(tasks[i].cap >= tasks[i].flow);
		freeTask += tasks[i].cap - tasks[i].flow;
		taskFlow += tasks[i].flow;
	}
	for (int i=0; i<workers.size(); ++i) {
		assert(workers[i].cap >= workers[i].flow);
		freeWorker += workers[i].cap - workers[i].flow;
		workerFlow += workers[i].flow;
	}
	assert(taskFlow == workerFlow);
	printf("taskN = %d, freeTask = %d, workerN = %d, freeWorker = %d\n", 
		tasks.size(), freeTask, workers.size(), freeWorker);
	#endif
}

void solve(string fileName) {
	int taskN, workerN, Umax, seqN, sumC;
	ifstream fin(fileName, ios::in);

	if (!fin.is_open()) {
		printf("Error openning FILE %s.\n", fileName.c_str());
		exit(1);
	}

	fin >> workerN >> taskN >> Umax >> sumC;
	seqN = taskN + workerN;
	init(taskN, workerN, Umax);
	Static_Greedy(fin, seqN);
}

int main(int argc, char* argv[]) {
	cin.tie(0);
	ios::sync_with_stdio(false);

	string dataPath, fileName;
	program_t begProg, endProg;

	if (argc > 1) {
		fileName = string(argv[1]);
		for (int i=fileName.length()-1; i>=0; --i) {
			if (fileName[i] == '/') {
				dataPath = fileName.substr(0, i);
				break;
			}
		}
	} else {
		#ifdef AT_THE_SERVER
		dataPath = "/home/server/zyx/Data0/7";
		fileName = "/home/server/zyx/Data0/7/order14.txt";
		#else
		dataPath = "/home/turf/Code/Data/Data0/0";
		fileName = "/home/turf/Code/Data/Data0/0/order14.txt";
		dataPath = "/home/server/zyx/Data0/7";
		fileName = "/home/server/zyx/Data0/7/order14.txt";
		#endif

	}

	input_weight(dataPath, weightArr);

	save_time(begProg);
	solve(fileName);
	save_time(endProg);

	double usedTime = calc_time(begProg, endProg);
	#ifdef WATCH_MEM
	printf("OPT %s %.6lf %.6lfs %dKB\n", fileName.c_str(), utility, usedTime, usedMemory);
	#else
	printf("OPT %s %.6lf %.6lfs\n", fileName.c_str(), utility, usedTime);
	#endif
	fflush(stdout);
	
	return 0;
}
