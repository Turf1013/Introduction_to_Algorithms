/**
	\author: Trasier
	\date: 2017.04.02
*/
#include <bits/stdc++.h>
using namespace std;
//#pragma comment(linker,"/STACK:102400000,1024000")

#define LOCAL_DEBUG

enum rule_t {
	worker, task
};

enum chosenStrategy_m {
	first, random, largest
};

chosenStrategy_m chosenStrategy = first; 

union W_un {
	double cost;
	double pay;
	double rate;
};
	
struct node_t {
	int id;				// id
	rule_t type;			// 0: task, 1: worker
	pair<double, double> loc;	// location
	int	cap;			// capacity
	int rad;			// radius	
	W_un cost;			// cost
	int begTime, endTime;	// time interval
};

typedef long long LL;
int n, m, umax;
double utility;

void init() {
	n = m = umax = 0;
	utility = 0;
}

bool hasNext(node_t& nd) {
	int timeId;
	char stype[4];
	
	if (scanf("%d", &timeId) == EOF) return false;
	scanf("%s", stype);
	
	nd.type = (stype[0]=='w') ? worker:task;
	
	if (stype[0] == 't') {
		
	} else {
		
	}
	
	return true;
}

inline double calcCost(const node_t& task, const node_t& worker) {
	return task.cost.pay * worker.cost.rate;
}

inline double Length(pair<double,double> pa, pair<double,double> pb) {
	return sqrt( (pa.first-pb.first)*(pa.first-pb.first) + (pa.second-pb.second)*(pa.second-pb.second) );
}

inline double Length2(pair<double,double> pa, pair<double,double> pb) {
	return (pa.first-pb.first)*(pa.first-pb.first) + (pa.second-pb.second)*(pa.second-pb.second);
}

bool satisfy(const node_t& worker, const node_t& task) {
	// 2&3. capacity of worker & task
	if (worker.cap<=0 || task.cap<=0)
		return false;
	
	// 1. condition of deadline
	if (!(worker.begTime<=task.endTime && task.begTime<=worker.endTime))
		return false;
	
	// 4. condition of location
	if (Length2(worker.loc, task.loc) > worker.rad * worker.rad)
		return false;
	
	return true;
}

int chosenNextTask(const vector<node_t>& tasks, node_t& worker, double costBound) {
	int taskN = tasks.size();
	double tmpCost;
	
#if (chosenStrategy == first)
	for (int i=0; i<taskN; ++i) {
		tmpCost = calcCost(tasks[i], worker);
		if (tmpCost>=costBound && satisfy(worker, tasks[i])) {
			return i;
		}
	}
#elif (chosenStrategy == random)
	vector<int> vc;
	for (int i=0; i<taskN; ++i) {
		tmpCost = calcCost(tasks[i], worker);
		if (tmpCost>=costBound && satisfy(worker, tasks[i])) {
			vc.push_back(i);
		}
	}
	if (!vc.empty())
		return vc[rand()%vc.size()];
#elif (chosenStrategy == largest)
	double mxCost = -1e8;
	int ret = -1;
	for (int i=0; i<taskN; ++i) {
		tmpCost = calcCost(tasks[i], worker);
		if (tmpCost>=costBound && satisfy(worker, tasks[i])) {
			if (tmpCost > mxCost) {
				mxCost = tmpCost;
				ret = i;
			}
		}
	}
	return ret;
#else
	/* never happen */
	assert(false);
#endif

	return -1;	// no valid task
}

int chosenNextWorker(const vector<node_t>& workers, node_t& task, double costBound) {
	int workerN = workers.size();
	double tmpCost;
	
#if (chosenStrategy == first)
	for (int i=0; i<workerN; ++i) {
		tmpCost = calcCost(task, workers[i]);
		if (tmpCost>=costBound && satisfy(task, workers[i])) {
			return i;
		}
	}
#elif (chosenStrategy == random)
	vector<int> vc;
	for (int i=0; i<workerN; ++i) {
		tmpCost = calcCost(task, workers[i]);
		if (tmpCost>=costBound && satisfy(task, workers[i])) {
			vc.push_back(i);
		}
	}
	if (!vc.empty())
		return vc[rand()%vc.size()];
#elif (chosenStrategy == largest)
	double mxCost = -1e8;
	int ret = -1;
	for (int i=0; i<workerN; ++i) {
		tmpCost = calcCost(task, workers[i]);
		if (tmpCost>=costBound && satisfy(task, workers[i])) {
			if (tmpCost > mxCost) {
				mxCost = tmpCost;
				ret = i;
			}
		}
	}
	return ret;
#else
	/* never happen */
	assert(false);
#endif

	return -1;	// no valid task
}

void addOneMatch(node_t& task, node_t& worker) {
	// add cost to utility
	utility += calcCost(task, worker);
	// update the capacity of task & worker
	--task.cap;
	--worker.cap;
}

void Extend_Greedy_RT() {
	int theta = ceil(log(umax + 1.0));
	int k = rand() % theta;
	double costBound = pow(exp(1.0), k);
	node_t node;
	vector<node_t> tasks, workers;
	int taskId, workerId;
	
	while (hasNext(node)) {
		if (node.type == task) { // node is task
			taskId = tasks.size();
			tasks.push_back(node);
			workerId = chosenNextWorker(workers, node, costBound);
		} else {
			workerId = workers.size();
			workers.push_back(node);
			taskId = chosenNextTask(tasks, node, costBound);
		}
		
		if (workerId>=0 && taskId>=0) {
			#ifdef LOCAL_DEBUG
			assert(taskId>=0 && taskId<((int)tasks.size()));
			assert(workerId>=0 && workerId<((int)workers.size()));
			#endif
			addOneMatch(tasks[taskId], workers[workerId]);
		}
	}
}

void solve() {
	int taskN, workerN;
	
	init();
	Extend_Greedy_RT();
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
		freopen("data.in", "r", stdin);
		freopen("data.out", "w", stdout);
	#endif
	
	
	
	#ifndef ONLINE_JUDGE
		printf("time = %ldms.\n", clock());
	#endif
	
	return 0;
}
