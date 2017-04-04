/**
	\author: Trasier
	\date: 2017.04.02
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

vector<vector<double> > weightArr;
inline double calcCost(const node_t& task, const node_t& worker) {
	#ifdef LOCAL_DEBUG
	assert(worker.id>=0 && worker.id<weightArr.size());
	assert(task.id>=0 && task.id<weightArr[worker.id].size());
	#endif
	return weightArr[worker.id][task.id];
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

struct Hungarian_t {
	struct vertex_t {
		int v;
		double w;
		
		vertex_t(int v=0, double w=0):
			v(v), w(w) {}
	};
	
	const double INF = 1e18;
	vector<vector<vertex_t> > g;
	vector<int> yx, xy;
	vector<double> lx, ly;
	vector<bool> S, T;
	vector<double> slack;
	int n;
	
	Hungarian_t() {
		init();
	}
	
	void init(int n=0) {
		clear();
		this->n = n;
		g.resize(n, vector<vertex_t>());
		yx.resize(n, -1);
		xy.resize(n, -1);
		lx.resize(n, 0);
		ly.resize(n, 0);
		S.resize(n, false);
		T.resize(n, false);
		slack.resize(n, 0);
	}
	
	void clear() {
		g.clear();
		yx.clear();
		xy.clear();
		lx.clear();
		ly.clear();
		S.clear();
		T.clear();
		slack.clear();
	}
	
	void build(const vector<int>& T_delta, const vector<int>& W_delta, const vector<node_t>& tasks, 
				const vector<node_t>& workers, const node_t& node) {
		const int Tsz = T_delta.size();
		const int Wsz = W_delta.size();
		int vertexN = max(Tsz+(node.type==task), Wsz+(node.type==worker));
		
		init(vertexN);
		for (int i=0; i<vertexN; ++i) {
			const int workerId = (i < Wsz) ? W_delta[i] : 
								 (node.type==worker) ? -1 : -2;

			for (int j=0; j<vertexN; ++j) {
				const int taskId = (j < Tsz) ? T_delta[j]:
								 (node.type==task) ? -1 : -2;

				double cost;
				if (workerId==-2 || taskId==-2) {
					cost = 0.0;
				} else if (workerId == -1) {
					cost = calcCost(tasks[taskId], node);
				} else if (taskId == -1) {
					cost = calcCost(node, workers[workerId]);
				} else {
					cost = calcCost(tasks[taskId], workers[workerId]);
				}

				g[i].push_back(vertex_t(j, cost));
			}

			// #ifdef LOCAL_DEBUG
			// printf("%d: sz = %d, vertexN = %d\n", i, (int)g[i].size(), vertexN);
			// assert(g[i].size() == vertexN);
			// #endif
		}

		#ifdef LOCAL_DEBUG
		assert(g.size() == vertexN);
		assert(yx.size() == vertexN);
		assert(xy.size() == vertexN);
		assert(lx.size() == vertexN);
		assert(ly.size() == vertexN);
		assert(slack.size() == vertexN);
		for (int i=0; i<vertexN; ++i) {
			assert(g[i].size() == vertexN);
		}
		#endif
	}

	bool dfs(int x) {

		int sz = g[x].size(), y;
		S[x] = true;
		// #ifdef LOCAL_DEBUG
		// printf("\tx = %d, sz = %d\n", x, sz);
		// #endif
		
		for (int i=0; i<sz; ++i) {
			y = g[x][i].v;
			if (T[y]) continue;
			
			double tmp = lx[x] + ly[y] - g[x][i].w;
			// #ifdef LOCAL_DEBUG
			// printf("\t\ty = %d, tmp = %.2lf\n", y, tmp);
			// #endif
			if (dcmp(tmp) == 0) {
				T[y] = true;
				if (yx[y]==-1 || dfs(yx[y])) {
					yx[y] = x;
					xy[x] = y;
					return true;
				}
			} else {
				slack[y] = min(slack[y], fabs(tmp));
			}
		}
		
		return false;
	}
	
	void update() {
		double mn = INF;
		
		for (int i=0; i<n; ++i) {
			if (!T[i]) {
				mn = min(mn, slack[i]);
			}
		}
		
		for (int i=0; i<n; ++i) {
			if (S[i]) lx[i] -= mn;
			if (T[i]) ly[i] += mn;
			//else	  slack[i] -= mn;
		}
	}
	
	void weightedMaximumMatch() {
		int i, j, k;
		
		// #ifdef LOCAL_DEBUG
		// printf("n = %d\n", n);
		// #endif
		fill(lx.begin(), lx.end(), 0.0);
		fill(ly.begin(), ly.end(), 0.0);
		fill(xy.begin(), xy.end(), -1);
		fill(yx.begin(), yx.end(), -1);
		for (int x=0; x<n; ++x) {
			int sz = g[x].size();
			for (int i=0; i<sz; ++i) {
				lx[x] = max(lx[x], g[x][i].w);
			}
		}
		
		for (int x=0; x<n; ++x) {
			// #ifdef LOCAL_DEBUG
			// printf("x = %d\n", x);
			// #endif
			for (;;) {
				fill(slack.begin(), slack.end(), INF);
				fill(S.begin(), S.end(), false);
				fill(T.begin(), T.end(), false);
				if (dfs(x))
					break;
				else
					update();
			}
		}
	}
	
	void match() {
		weightedMaximumMatch();
	}
};

typedef long long LL;
int n, m, umax;
double utility;
Hungarian_t hung;

void init(int taskN, int workerN, int Umax) {
	n = workerN;
	m = taskN;
	umax = Umax;
	utility = 0;
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

	#ifdef LOCAL_DEBUG
	nd.print();
	#endif
}

bool satisfy(const node_t& worker, const node_t& task) {
	// 2&3. capacity of worker & task
	if (worker.cap<=worker.flow || task.cap<=task.flow)
		return false;
	
	// 1. condition of deadline
	if (!(worker.begTime<=task.endTime && task.begTime<=worker.endTime))
		return false;
	
	// 4. condition of location
	if (Length2(worker.loc, task.loc) > worker.rad * worker.rad)
		return false;
	
	return true;
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
		if (satisfy(task, workers[i]) && tmpCost>mxCost) {
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

void TGOA_Filter(ifstream& fin, int seqN) {
	int k = (m + n) / 2;
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
		
		if (W_delta.size() + T_delta.size() < k) {
			/* do nothing */
			
		} else {
			#ifdef LOCAL_DEBUG
			puts("before build");
			#endif
			hung.build(T_delta, W_delta, tasks, workers, node);
			#ifdef LOCAL_DEBUG
			puts("after build");
			#endif

			#ifdef LOCAL_DEBUG
			puts("before match");
			#endif
			hung.match();
			#ifdef LOCAL_DEBUG
			puts("after match");
			fflush(stdout);
			#endif
			
			const int Tsz = T_delta.size();
			const int Wsz = W_delta.size();
			
			if (node.type == task) {
				if (hung.yx[Tsz]!=-1 && hung.yx[Tsz]<W_delta.size()) {
					workerId = W_delta[hung.yx[Tsz]];
					if (satisfy(node, workers[workerId])) {
						/* valid, do nothing*/
					} else {
						workerId = -1;
					}
				}
				
			} else {
				if (hung.xy[Wsz]!=-1 && hung.xy[Wsz]<T_delta.size()) {
					taskId = T_delta[hung.xy[Wsz]];
					if (satisfy(tasks[taskId], node)) {
						/* valid, do nothing*/
					} else {
						taskId = -1;
					}
				}
			}
			
			#ifdef LOCAL_DEBUG
			printf("workerId = %d, taskId = %d\n", workerId, taskId);
			#endif
		}
		
		if (workerId>=0 && taskId>=0) {
			addOneMatch(tasks[taskId], workers[workerId]);
		}
		
		if (node.type == task) {
			for (int i=0; i<node.cap; ++i)
				T_delta.push_back(taskId);
		} else {
			for (int i=0; i<node.cap; ++i)
				W_delta.push_back(workerId);
		}
		
		#ifdef WATCH_MEM
		watchSolutionOnce(getpid(), usedMemory);
		#endif
	}

	#ifdef LOCAL_DEBUG
	int freeTask = 0, freeWorker = 0;
	for (int i=0; i<tasks.size(); ++i)
		freeTask += tasks[i].cap;
	for (int i=0; i<workers.size(); ++i)
		freeWorker += workers[i].cap;

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

	fin >> taskN >> workerN >> Umax >> sumC;
	seqN = taskN + workerN;
	init(taskN, workerN, Umax);
	TGOA_Filter(fin, seqN);
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
		dataPath = "/home/turf/Code/Data/9";
		fileName = "/home/turf/Code/Data/9/order10.txt";
	}

	input_weight(dataPath, weightArr);

	save_time(begProg);
	solve(fileName);
	save_time(endProg);

	double usedTime = calc_time(begProg, endProg);
	#ifdef WATCH_MEM
	printf("TGOA_Filter %s %.6lf %.6lfs %dKB\n", fileName.c_str(), utility, usedTime, usedMemory);
	#else
	printf("TGOA_Filter %s %.6lf %.6lfs\n", fileName.c_str(), utility, usedTime);
	#endif
	fflush(stdout);
	
	return 0;
}
