/**
	\author: Trasier
	\date: 2017.05.12
*/
#include <bits/stdc++.h>
using namespace std;
//#pragma comment(linker,"/STACK:102400000,1024000")
#include "input.h"
#include "monitor.h"

// #define LOCAL_DEBUG

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
bool satisfy(const node_t& worker, const node_t& task);


inline double calcCost(const node_t& task, const node_t& worker) {
	if (task.type != rule_t::task) return calcCost(worker, task);
	#ifdef LOCAL_DEBUG
	assert(task.type==rule_t::task && worker.type==rule_t::worker);
	#endif
	return (satisfyLoc(worker, task) && satisfyTime(worker, task)) ? task.cost.pay * worker.cost.rate : 0.0;
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
	
	void init() {
		clear();
		yx.resize(Tsz, -1);
		xy.resize(Wsz, -1);
		lx.resize(Wsz, 0.0);
		ly.resize(Tsz, 0.0);
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
	
	double getCost(int workerId, int taskId, const vector<node_t>& tasks, const vector<node_t>& workers) {
		const node_t& task = tasks[taskId];
		const node_t& worker = workers[workerId];
		return calcCost(task, worker);
	}
	
	void build(const vector<node_t>& tasks, const vector<node_t>& workers) {
		Tsz = tasks.size();
		Wsz = workers.size();
		#ifdef LOCAL_DEBUG
		assert(Tsz >= Wsz);
		#endif
		init();
	}
	
	bool dfs(int x, const vector<node_t>& tasks, const vector<node_t>& workers) {
		int y;
		S[x] = true;
		
		for (y=0; y<Tsz; ++y) {
			if (T[y]) continue;
			
			double tmp = lx[x] + ly[y] - getCost(x, y, tasks, workers);
			if (dcmp(tmp) == 0) {
				T[y] = true;
				if (yx[y]==-1 || dfs(yx[y], tasks, workers)) {
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
			else	  slack[i] -= mn;
		}
	}
	
	void KM(const vector<node_t>& tasks, const vector<node_t>& workers) {
		for (int x=0; x<Wsz; ++x) {
			for (int y=0; y<Tsz; ++y) {
				double tmp = getCost(x, y, tasks, workers);
				lx[x] = max(lx[x], tmp);
			}
		}
		
		for (int x=0; x<Wsz; ++x) {
			fill(slack.begin(), slack.end(), INF);
			for (;;) {
				fill(S.begin(), S.end(), false);
				fill(T.begin(), T.end(), false);
				if (dfs(x, tasks, workers))
					break;
				else
					update();
			}
		}
	}
	
	void match(const vector<node_t>& tasks, const vector<node_t>& workers) {
		KM(tasks, workers);
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
#ifdef WATCH_MEM
int usedMemory = 0;
#endif
int numBound;

void init(int taskN, int workerN, double Umax, int SumC) {
	n = workerN;
	m = taskN;
	umax = Umax;
	sumC = SumC;
	utility = 0;
	#ifdef WATCH_MEM
	usedMemory = 0;
	#endif
}

void nextSeq(ifstream& fin, node_t& nd) {
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
	// if (!(worker.begTime<=task.endTime && task.begTime<=worker.endTime))
	if (!(worker.begTime<task.endTime && task.begTime<worker.endTime))
		return false;
	return true;
}

bool satisfy(const node_t& worker, const node_t& task) {
	return satisfyCap(worker, task) && satisfyTime(worker, task) && satisfyLoc(worker, task);
	//return satisfyCap(worker, task) && satisfyLoc(worker, task);
}

void removeNode(vector<node_t>& nodes, int idx) {
	#ifdef LOCAL_DEBUG
	assert(idx>=0 && idx<nodes.size());
	#endif
	nodes[idx] = *nodes.rbegin();
	nodes.pop_back();
}

void markDeadNode(vector<bool>& visit, const vector<node_t>& nodes, const int timeBound) {
	
	#ifdef LOCAL_DEBUG
	assert(visit.size() == nodes.size());
	#endif
	const int sz = nodes.size();
	for (int i=0; i<sz; ++i) {
		if (nodes[i].endTime - timeBound < 0) {
			visit[i] = true;
		}
	}
}

void Mei(ifstream& fin, int seqN) {
	vector<node_t> tasks, workers;
	node_t node;
	int curNum = 0;
	
	while (seqN--) {
		nextSeq(fin, node);
		int cap = node.cap;
		node.flow = 0;
		node.cap = 1;
		curNum += cap;

		while (cap--) {
			if (node.type == task) { // node is task
				tasks.push_back(node);
			} else {
				workers.push_back(node);
			}
		}

		// Execute KM once when condition is satisfied
		if (seqN==0 || curNum>=numBound) {
			const int Tsz = tasks.size();
			const int Wsz = workers.size();

			if (Tsz >= Wsz) {
				hung.build(tasks, workers);
				hung.match(tasks, workers);
			} else {
				hung.build(workers, tasks);
				hung.match(workers, tasks);
			}

			// if any edge is matched, then remove the tasks & workers;
			int x, y;
			vector<bool> visitX(min(Wsz, Tsz), false);
			vector<bool> visitY(max(Wsz, Tsz), false);
			double cost, sumCost = 0.0;
			vector<node_t> workersTmp, tasksTmp;

			if (Tsz >= Wsz) {// x is worker
				for (x=0; x<Wsz; ++x) {
					y = hung.xy[x];
					cost = calcCost(tasks[y], workers[x]);
					#ifdef LOCAL_DEBUG
					assert(dcmp(cost) >= 0);
					#endif
					if (dcmp(cost) > 0) {
						sumCost += cost;
						visitX[x] = visitY[y] = true;
					}
				}

				// remove node which is beyond deadline
				markDeadNode(visitX, workers, node.begTime);
				markDeadNode(visitY, tasks, node.begTime);

				// remove matched workers and tasks, trick is remove from the tail
				// for (x=Wsz-1; x>=0; --x) {
					// if (visitX[x]) 
					// 	removeNode(workers, x);
				// }
				// for (y=Tsz-1; y>=0; --y) {
					// if (visitY[y])
					// 	removeNode(tasks, y);
				// }
				for (x=0; x<Wsz; ++x) {
					if (!visitX[x])
						workersTmp.push_back(workers[x]);
				}
				for (y=0; y<Tsz; ++y) {
					if (!visitY[y])
						tasksTmp.push_back(tasks[y]);
				}
			} else {// x is task
				for (x=0; x<Tsz; ++x) {
					y = hung.xy[x];
					cost = calcCost(tasks[x], workers[y]);
					#ifdef LOCAL_DBEUG
					assert(dcmp(cost) >= 0);
					#endif
					if (dcmp(cost) > 0) {
						sumCost += cost;
						visitX[x] = visitY[y] = true;
					}
				}

				// remove node which is beyond deadline
				markDeadNode(visitX, tasks, node.begTime);
				markDeadNode(visitY, workers, node.begTime);

				// remove matched workers and tasks, trick is remove from the tail
				// for (x=Wsz-1; x>=0; --x) {
					// if (visitX[x])
					// 	removeNode(tasks, x);
				// }
				// for (y=Tsz-1; y>=0; --y) {
					// if (visitY[y])
					// 	removeNode(workers, y);
				// }
				for (x=0; x<Tsz; ++x) {
					if (!visitX[x])
						tasksTmp.push_back(tasks[x]);
				}
				for (y=0; y<Wsz; ++y) {
					if (!visitY[y])
						workersTmp.push_back(workers[y]);
				}
			}

			utility += sumCost;
			workers = workersTmp;
			tasks = tasksTmp;
			curNum = 0;

			#ifdef WATCH_MEM
			watchSolutionOnce(getpid(), usedMemory);
			#endif

			#ifdef LOCAL_DEBUG
			printf("sumCost = %.4lf\n", sumCost);
			#endif
		}
	}
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
	Mei(fin, seqN);
}

int main(int argc, char* argv[]) {
	cin.tie(0);
	ios::sync_with_stdio(false);

	string edgeFileName;

	if (argc > 1) {
		edgeFileName = string(argv[1]);
	} else {
		edgeFileName = "order.in";
	}
	if (argc > 2) {
		sscanf(argv[2], "%d", &numBound);
	} else {
		numBound = 5000;
	}

	program_t begProg, endProg;
	save_time(begProg);
	solve(edgeFileName);
	save_time(endProg);

	double usedTime = calc_time(begProg, endProg);
	#ifdef WATCH_MEM
	printf("MeiNum %.6lf %.6lf %.4lf\n", utility, usedTime, usedMemory/1024.0);
	#else
	printf("MeiNum %.6lf %.6lf\n", utility, usedTime);
	#endif
	fflush(stdout);
	
	return 0;
}

