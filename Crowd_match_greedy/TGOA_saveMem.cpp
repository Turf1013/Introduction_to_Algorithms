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
	rule_t type;		// 0: task, 1: worker
	pair<double, double> loc;	// location
	int	cap;			// capacity
	int flow;			// flow
	double rad;			// radius	
	W_un cost;			// cost
	int begTime, endTime;	// time interval

	void print() {
		if (type == worker)
		 	printf("w: loc = (%.2lf, %.2lf), rad = %.2lf, cap = %d, time = (%d, %d), ratio = %.2lf\n",
		 			loc.first, loc.second, rad, cap, begTime, endTime, cost.rate);
		else
			printf("t: loc = (%.2lf, %.2lf), time = (%d, %d), pay = %.2lf\n",
		 			loc.first, loc.second, begTime, endTime, cost.pay);
	}
};

bool satisfyLoc(const node_t& worker, const node_t& task);
bool satisfyTime(const node_t& worker, const node_t& task);

inline double calcCost(const node_t& atask, const node_t& aworker) {
	assert(atask.type==task && aworker.type==worker);
	if (satisfyLoc(aworker, atask) && satisfyTime(aworker, atask)) 
		return atask.cost.pay * aworker.cost.rate;
	else
		return 0.0;
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

const double INF = 1e18;
struct Hungarian_t {
	struct vertex_t {
		int v;
		double w;
		
		vertex_t(int v=0, double w=0):
			v(v), w(w) {}
	};
	
	vector<int> yx, xy;
	vector<double> lx, ly;
	vector<bool> S, T;
	vector<double> slack;
	int Tsz, Wsz;
	
	Hungarian_t() {
		init();
	}
	
	void init(int n=0) {
		clear();
		yx.resize(Tsz, -1);
		xy.resize(Wsz, -1);
		lx.resize(Wsz, 0);
		ly.resize(Tsz, 0);
		S.resize(Wsz, false);
		T.resize(Tsz, false);
		slack.resize(Tsz, 0);
	}
	
	void clear() {
		yx.clear();
		xy.clear();
		lx.clear();
		ly.clear();
		S.clear();
		T.clear();
		slack.clear();
	}
	
	double getCost(int i, int j, const vector<int>& T_delta, const vector<int>& W_delta, 
				const vector<node_t>& tasks, const vector<node_t>& workers) {
		const int workerId = (i < Wsz) ? W_delta[i] : -2;
		const int taskId = (j < Tsz) ? T_delta[j] : -2;
		
		double cost;
		if (workerId==-2 || taskId==-2) {
			cost = 0.0;
		} else {
			if (tasks[taskId].type == task)
				cost = calcCost(tasks[taskId], workers[workerId]);
			else
				cost = calcCost(workers[workerId], tasks[taskId]);
		}
		return cost;
	}
	
	void build(const vector<int>& T_delta, const vector<int>& W_delta, 
				const vector<node_t>& tasks, const vector<node_t>& workers) {
		Tsz = T_delta.size();
		Wsz = W_delta.size();
		assert(Tsz >= Wsz);
		int vertexN = max(Tsz, Wsz);
		
		init(vertexN);
		// for (int i=0; i<vertexN; ++i) {
			// const int workerId = (i < Wsz) ? W_delta[i] : -2;

			// for (int j=0; j<vertexN; ++j) {
				// const int taskId = (j < Tsz) ? T_delta[j] : -2;

				// double cost;
				// if (workerId==-2 || taskId==-2) {
					// cost = 0.0;
				// } else {
					// cost = calcCost(tasks[taskId], workers[workerId]);
				// }

				// g[i].push_back(vertex_t(j, cost));
			// }
		// }
	}
	
	bool dfs(int x, const vector<int>& T_delta, const vector<int>& W_delta, 
				const vector<node_t>& tasks, const vector<node_t>& workers) {
		int y;
		S[x] = true;
		
		for (y=0; y<Tsz; ++y) {
			if (T[y]) continue;
			
			double tmp = lx[x] + ly[y] - getCost(x, y, T_delta, W_delta, tasks, workers);
			if (dcmp(tmp) == 0) {
				T[y] = true;
				if (yx[y]==-1 || dfs(yx[y], T_delta, W_delta, tasks, workers)) {
					yx[y] = x;
					xy[x] = y;
					return true;
				}
			} else {
				slack[y] = min(slack[y], tmp);
			}
		}
		
		return false;
	}
	
	void update() {
		double mn = INF;
		
		for (int i=0; i<Tsz; ++i) {
			if (!T[i]) {
				mn = min(mn, slack[i]);
			}
		}
		
		for (int i=0; i<Wsz; ++i) {
			if (S[i]) lx[i] -= mn;
		}
		
		for (int i=0; i<Tsz; ++i) {
			if (T[i]) ly[i] += mn;
			//else	  slack[i] -= mn;
		}
	}
	
	void weightedMaximumMatch(const vector<int>& T_delta, const vector<int>& W_delta, 
				const vector<node_t>& tasks, const vector<node_t>& workers) {
		int i, j, k;
		
		fill(lx.begin(), lx.end(), 0.0);
		fill(ly.begin(), ly.end(), 0.0);
		fill(xy.begin(), xy.end(), -1);
		fill(yx.begin(), yx.end(), -1);
		for (int x=0; x<Wsz; ++x) {
			for (int y=0; y<Tsz; ++y) {
				double tmp = getCost(x, y, T_delta, W_delta, tasks, workers);
				lx[x] = max(lx[x], tmp);
			}
		}
		
		for (int x=0; x<Wsz; ++x) {
			for (;;) {
				fill(slack.begin(), slack.end(), INF);
				fill(S.begin(), S.end(), false);
				fill(T.begin(), T.end(), false);
				if (dfs(x, T_delta, W_delta, tasks, workers))
					break;
				else
					update();
			}
		}
	}
	
	void match(const vector<int>& T_delta, const vector<int>& W_delta, 
				const vector<node_t>& tasks, const vector<node_t>& workers) {
		weightedMaximumMatch(T_delta, W_delta, tasks, workers);
		#ifdef LOCAL_DEBUG
		for (int x=0; x<Wsz; ++x) {
			assert(xy[x] != -1);
		}
		#endif
	}
};

typedef long long LL;
int n, m, sumC;
double umax;
double utility;
Hungarian_t hung;
int usedMemory;

void init(int taskN, int workerN, double Umax, int SumC) {
	n = workerN;
	m = taskN;
	umax = Umax;
	sumC = SumC;
	utility = 0;
	usedMemory = 0;
}

void nextSeq(ifstream& fin, node_t& nd) {
	int timeId;
	string stype;

	fin >> nd.begTime >> stype;
	if (stype[0] == 'w') {
		nd.type = worker;
		fin >> nd.loc.first >> nd.loc.second >> nd.rad >> nd.cap >> nd.endTime >> nd.cost.rate;
		nd.endTime += nd.begTime;
	} else {
		nd.type = task;
		fin >> nd.loc.first >> nd.loc.second >> nd.endTime >> nd.cost.pay;
		nd.endTime += nd.begTime;
		nd.cap = 1;
	}

	nd.flow = 0;
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
	if (!(worker.begTime<task.endTime && task.begTime<worker.endTime))
		return false;
	return true;
}

bool satisfy(const node_t& worker, const node_t& task) {
	return satisfyCap(worker, task) && satisfyTime(worker, task) && satisfyLoc(worker, task);
	//return satisfyCap(worker, task) && satisfyLoc(worker, task);
}

int chosenNextTask(const vector<node_t>& tasks, node_t& worker) {
	int taskN = tasks.size();
	double tmpCost;
	double mxCost = 0.0;
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
	double mxCost = 0.0;
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

void TGOA(ifstream& fin, int seqN) {
	int k = sumC / 2;
	vector<int> W_delta, T_delta;
	node_t node;
	vector<node_t> tasks, workers;
	int taskId, workerId;
	bool isSecondHalf = false;

	while (seqN--) {
		
		nextSeq(fin, node);
		int cap = node.cap;
		node.cap = 1;
		
		while (cap--) {
			workerId = taskId = -1;
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
			
			if (!isSecondHalf) {
				if (node.type == task) {
					workerId = chosenNextWorker(workers, node);
				} else {
					taskId = chosenNextTask(tasks, node);
				}
				
			} else {
				if (T_delta.size() >= W_delta.size()) {
					hung.build(T_delta, W_delta, tasks, workers);
					hung.match(T_delta, W_delta, tasks, workers);

					const int Tsz = T_delta.size();
					const int Wsz = W_delta.size();
					assert(Wsz <= Tsz);
					if (node.type == task) {
						if (hung.yx[Tsz-1]>=0 && hung.yx[Tsz-1]<Wsz) {
							workerId = W_delta[hung.yx[Tsz-1]];
							#ifdef LOCAL_DEBUG
							assert(workerId < workers.size());
							#endif
							if (satisfy(workers[workerId], tasks[taskId])) {
								/* valid, do nothing*/
							} else {
								workerId = -1;
							}
						}
						
					} else {
						if (hung.xy[Wsz-1]>=0 && hung.xy[Wsz-1]<Tsz) {
							taskId = T_delta[hung.xy[Wsz-1]];
							#ifdef LOCAL_DEBUG
							assert(taskId < tasks.size());
							#endif
							if (satisfy(workers[workerId], tasks[taskId])) {
								/* valid, do nothing*/
							} else {
								taskId = -1;
							}
						}
					}
					#ifdef LOCAL_DEBUG
					printf("1 %d %d\n", workerId, taskId);
					#endif
				} else {
					hung.build(W_delta, T_delta, workers, tasks);
					hung.match(W_delta, T_delta, workers, tasks);

					const int Tsz = T_delta.size();
					const int Wsz = W_delta.size();
					assert(Wsz >= Tsz);
					if (node.type == task) {
						if (hung.xy[Tsz-1]>=0 && hung.xy[Tsz-1]<Wsz) {
							workerId = W_delta[hung.xy[Tsz-1]];
							#ifdef LOCAL_DEBUG
							assert(workerId < workers.size());
							#endif
							if (satisfy(workers[workerId], tasks[taskId])) {
								/* valid, do nothing*/
							} else {
								workerId = -1;
							}
						}
						
					} else {
						if (hung.yx[Wsz-1]>=0 && hung.yx[Wsz-1]<Tsz) {
							taskId = T_delta[hung.yx[Wsz-1]];
							#ifdef LOCAL_DEBUG
							assert(taskId < tasks.size());
							#endif
							if (satisfy(workers[workerId], tasks[taskId])) {
								/* valid, do nothing*/
							} else {
								taskId = -1;
							}
						}
					}

				}
				#ifdef LOCAL_DEBUG
				printf("2 %d %d\n", workerId, taskId);
				#endif
			}
			
			if (workerId>=0 && taskId>=0) {
				#ifdef LOCAL_DEBUG
				assert(satisfy(workers[workerId], tasks[taskId]));
				#endif
				addOneMatch(tasks[taskId], workers[workerId]);
			}

			if (!isSecondHalf && T_delta.size()+W_delta.size()>=k) {
				isSecondHalf = true;
				T_delta.clear();
				W_delta.clear();
			}
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
	int taskN, workerN, seqN, sumC;
	double Umax;
	ifstream fin(fileName.c_str(), ios::in);

	if (!fin.is_open()) {
		printf("Error openning FILE %s.\n", fileName.c_str());
		exit(1);
	}

	fin >> workerN >> taskN >> Umax >> sumC;
	seqN = taskN + workerN;
	init(taskN, workerN, Umax, sumC);
	TGOA(fin, seqN);
}

int main(int argc, char* argv[]) {
	cin.tie(0);
	ios::sync_with_stdio(false);

	string edgeFileName;
	program_t begProg, endProg;

	if (argc > 1) {
		edgeFileName = string(argv[1]);
	} else {
		#ifdef AT_THE_SERVER
		edgeFileName = "/home/server/zyx/Data0/7/order14.txt";
		#else
		edgeFileName = "/home/turf/TmpTest/data2.txt";
		#endif
	}

	save_time(begProg);
	solve(edgeFileName);
	save_time(endProg);

	double usedTime = calc_time(begProg, endProg);
	#ifdef WATCH_MEM
	printf("TGOA %.6lf %.6lfs %dKB\n", utility, usedTime, usedMemory);
	#else
	printf("TGOA %.6lf %.6lfs\n", utility, usedTime);
	#endif
	fflush(stdout);
	
	return 0;
}
