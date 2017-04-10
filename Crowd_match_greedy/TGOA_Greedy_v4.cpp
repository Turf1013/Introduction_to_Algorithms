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
//#define LOCAL_DEBUG

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
		 	printf("id = %d, loc = (%.2lf, %.2lf), rad = %.2lf, cap = %d, flow = %d, time = (%d, %d)\n",
		 			id, loc.first, loc.second, rad, cap, flow, begTime, endTime);
		else
			printf("id = %d, loc = (%.2lf, %.2lf), flow = %d, time = (%d, %d)\n",
		 			id, loc.first, loc.second, flow, begTime, endTime);
	}
};

bool satisfyLoc(const node_t& worker, const node_t& task);

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


const double eps = 1e-6;
inline double dcmp(double a) {
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
			return w > o.w;
		}
	};
	
	const double INF = 1e18;
	vector<vertex_t> E;
	vector<int> yx, xy;
	
	Greedy_t() {
		init(0, 0);
	}
	
	void init(int Wsz, int Tsz) {
		clear();
		yx.resize(Tsz, -1);
		xy.resize(Wsz, -1);
	}
	
	void clear() {
		yx.clear();
		xy.clear();
		E.clear();
	}
	
	void build(const vector<int>& T_delta, const vector<int>& W_delta, const vector<node_t>& tasks, 
				const vector<node_t>& workers, const node_t& node) {
		const int Tsz = T_delta.size();
		const int Wsz = W_delta.size();
		const int curTsz = Tsz + (node.type == task);
		const int curWsz = Wsz + (node.type == worker);
		
		init(curWsz, curTsz);
		for (int i=0; i<curWsz; ++i) {
			const int workerId = (i < Wsz) ? W_delta[i] : -1;

			for (int j=0; j<curTsz; ++j) {
				const int taskId = (j < Tsz) ? T_delta[j] : -1;

				double cost;
				if (workerId==-1) {
					if (satisfyLoc(node, tasks[taskId])) {
						cost = calcCost(tasks[taskId], node);
						E.push_back(vertex_t(i, j, cost));
					}
				} else if (taskId == -1) {
					if (satisfyLoc(workers[workerId], node)) {
						cost = calcCost(node, workers[workerId]);
						E.push_back(vertex_t(i, j, cost));
					}	
				} else {
					if (satisfyLoc(workers[workerId], tasks[taskId])) {
						cost = calcCost(tasks[taskId], workers[workerId]);
						E.push_back(vertex_t(i, j, cost));
					}
				}
			}
		}
	}
	
	void GreedyMatch(const vector<int>& T_delta, const vector<int>& W_delta, const vector<node_t>& tasks, 
				const vector<node_t>& workers, const node_t& node) {
		const int Tsz = T_delta.size();
		const int Wsz = W_delta.size();
		const int Esz = E.size();
		vertex_t ver;
		int taskId, workerId;
		
		sort(E.begin(), E.end());
		#ifdef LOCAL_DEBUG
		printf("E.size() = %d\n", (int)E.size());
		#endif
		for (int i=0; i<Esz; ++i) {
			ver = E[i];

			if (xy[ver.u]>=0 || yx[ver.v]>=0) continue;

			workerId = (ver.u<Wsz) ? W_delta[ver.u] : -1;
			taskId = (ver.v<Tsz) ? T_delta[ver.v] : -1;
			const node_t& workerNode = (workerId==-1) ? node:workers[workerId];
			const node_t& taskNode = (taskId==-1) ? node:tasks[taskId]; 

			#ifdef LOCAL_DEBUG
			if (workerId == -1) {
				assert(taskId>=0 && taskId<tasks.size());
			} else if (taskId == -1) {
				assert(workerId>=0 && workerId<workers.size());
			}
			#endif

			if ((workerId==-1 || taskId==-1)) {
				if (satisfy(workerNode, taskNode)) {
					xy[ver.u] = ver.v;
					yx[ver.v] = ver.u;
				}
				#ifdef LOCAL_DEBUG
				assert(!(workerId==-1 && taskId==-1));
				#endif
				return ;
			}

			xy[ver.u] = ver.v;
			yx[ver.v] = ver.u;
		}
	}
	
	void match(const vector<int>& T_delta, const vector<int>& W_delta, const vector<node_t>& tasks, 
				const vector<node_t>& workers, const node_t& node) {
		GreedyMatch(T_delta, W_delta, tasks, workers, node);
	}
};

typedef long long LL;
int n, m, umax;
double utility;
int usedMemory;
Greedy_t greedy;

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

int chosenNextTask(const vector<node_t>& tasks, node_t& worker) {
	int taskN = tasks.size();
	double tmpCost;
	double mxCost = -1e8;
	int ret = -1;
	
	for (int i=0; i<taskN; ++i) {
		tmpCost = calcCost(tasks[i], worker);
		if (satisfy(worker, tasks[i]) && tmpCost>mxCost) {
			mxCost = tmpCost;
			ret = i;
		}
	}
	
	return ret;
}

int chosenNextWorker(const vector<node_t>& workers, node_t& task) {
	int workerN = workers.size();
	double tmpCost;
	double mxCost = -1e8;
	int ret = -1;
	
	for (int i=0; i<workerN; ++i) {
		tmpCost = calcCost(task, workers[i]);
		if (satisfy(workers[i], task) && tmpCost>mxCost) {
			mxCost = tmpCost;
			ret = i;
		}
	}
	
	return ret;
}

void addOneMatch(node_t& task, node_t& worker) {
	// add cost to utility
	utility += calcCost(task, worker);
	// update the capacity of task & worker
	++task.flow;
	++worker.flow;
}

void TGOA_Greedy(ifstream& fin, int seqN) {
	int k = (m + n) / 2;
	vector<int> W_delta, T_delta;
	node_t node;
	vector<node_t> tasks, workers;
	int taskId, workerId;
	bool isSecondHalf = false;
	
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
		
		if (!isSecondHalf && W_delta.size() + T_delta.size() <= k) {
			if (node.type == task) {
				workerId = chosenNextWorker(workers, node);
			} else {
				taskId = chosenNextTask(tasks, node);
			}
			
		} else {
			#ifdef LOCAL_DEBUG
			printf("ws.size() = %d, ts.size() = %d, ", W_delta.size(), T_delta.size());
			#endif

			greedy.build(T_delta, W_delta, tasks, workers, node);
			greedy.match(T_delta, W_delta, tasks, workers, node);
			const int Tsz = T_delta.size();
			const int Wsz = W_delta.size();
			
			if (node.type == task) {
				if (greedy.yx[Tsz] >= 0) {
					#ifdef LOCAL_DEBUG
 					assert(greedy.yx[Tsz] < Wsz);
					#endif

					workerId = W_delta[greedy.yx[Tsz]];

					#ifdef LOCAL_DEBUG
					assert(workerId < workers.size());
					// assert(satisfy(workers[workerId], node));
					#endif

					if (satisfy(workers[workerId], node)) {
						/* valid, do nothing*/
					} else {
						workerId = -1;
					}
				}
				
			} else {
				if (greedy.xy[Wsz] >= 0) {
					#ifdef LOCAL_DEBUG
					assert(greedy.xy[Wsz] < Tsz);
					#endif

					taskId = T_delta[greedy.xy[Wsz]];

					#ifdef LOCAL_DEBUG
					assert(taskId < tasks.size());
					// assert(satisfy(node, tasks[taskId]));
					#endif

					if (satisfy(node, tasks[taskId])) {
						/* valid, do nothing*/
					} else {
						taskId = -1;
					}
				}
			}
			
		}
		
		if (workerId>=0 && taskId>=0) {
			addOneMatch(tasks[taskId], workers[workerId]);
		}

		#ifdef LOCAL_DEBUG
			if (workerId>=0 && taskId>=0) {
				if (isSecondHalf) {
					if (node.type == worker)
						printf("w.id = %d, tmp = %.4lf\n", workerId, weightArr[workerId][taskId]);
					else
						printf("t.id = %d, tmp = %.4lf\n", taskId, weightArr[workerId][taskId]);
				} else {
					printf("w.id = %d, t.id = %d, tmp = %.4lf\n", workerId, taskId, weightArr[workerId][taskId]);
				}
			} else {
				if (isSecondHalf) {
					if (node.type == worker)
						printf("w.id = %d, tmp = %.4lf\n", workerId, 0.0);
					else
						printf("t.id = %d, tmp = %.4lf\n", taskId, 0.0);
				} else {
					printf("w.id = %d, t.id = %d, tmp = %.4lf\n", workerId, taskId, -1.0);
				}
			}
		#endif
		
		if (node.type == task) {
			for (int i=0; i<node.cap; ++i)
				T_delta.push_back(taskId);
		} else {
			for (int i=0; i<node.cap; ++i)
				W_delta.push_back(workerId);
		}

		if (!isSecondHalf && T_delta.size()+W_delta.size()>k) {
			isSecondHalf = true;
			T_delta.clear();
			W_delta.clear();
		}
		#ifdef WATCH_MEM
		watchSolutionOnce(getpid(), usedMemory);
		#endif
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
	ifstream fin(fileName.c_str(), ios::in);

	if (!fin.is_open()) {
		printf("Error openning FILE %s.\n", fileName.c_str());
		exit(1);
	}

	fin >> workerN >> taskN >> Umax >> sumC;
	seqN = taskN + workerN;
	init(taskN, workerN, Umax);
	TGOA_Greedy(fin, seqN);
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
		dataPath = "/home/turf/tmp/";
		fileName = "/home/turf/tmp/order0.txt";
		#endif
	}

	input_weight(dataPath, weightArr);

	save_time(begProg);
	solve(fileName);
	save_time(endProg);

	double usedTime = calc_time(begProg, endProg);
	#ifdef WATCH_MEM
	printf("TGOA_Greedy %s %.6lf %.6lfs %dKB\n", fileName.c_str(), utility, usedTime, usedMemory);
	#else
	printf("TGOA_Greedy %s %.6lf %.6lfs\n", fileName.c_str(), utility, usedTime);
	#endif
	fflush(stdout);
	
	return 0;
}
