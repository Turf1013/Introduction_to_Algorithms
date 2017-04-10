/**
	\author: Trasier
	\date: 2017.04.02
*/
#include <bits/stdc++.h>
using namespace std;
//#pragma comment(linker,"/STACK:102400000,1024000")
#include "monitor.h"
#include "input.h"

//#define AT_THE_SERVER
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
		 	printf("id = %d, loc = (%.2lf, %.2lf), rad = %.2lf, cap = %d, flow = %d, time = (%d, %d)\n",
		 			id, loc.first, loc.second, rad, cap, flow, begTime, endTime);
		else
			printf("id = %d, loc = (%.2lf, %.2lf), flow = %d, time = (%d, %d)\n",
		 			id, loc.first, loc.second, flow, begTime, endTime);
	}
};

typedef long long LL;
int n, m, umax;
double utility;
int usedMemory;
vector<vector<double> > weightArr;

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

inline double calcCost(const node_t& task, const node_t& worker) {
	#ifdef LOCAL_DEBUG
	//printf("task.id = %d, worker.id = %d\n", task.id, worker.id);
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

int chosenNextTask(const vector<node_t>& tasks, node_t& worker) {
	int taskN = tasks.size();
	double tmpCost;
	double mxCost = -1e8;
	int ret = -1;

	//puts("chosenNextTask");
	for (int i=0; i<taskN; ++i) {
		tmpCost = calcCost(tasks[i], worker);
		//printf("tmpCost = %.4lf, costBound = %.4lf, dis = %.4lf\n", tmpCost, costBound, Length(worker.loc, tasks[i].loc));
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
		//printf("tmpCost = %.4lf, costBound = %.4lf, dis = %.4lf\n", tmpCost, costBound, Length(workers[i].loc, task.loc));
		if (satisfy(workers[i], task) && tmpCost>mxCost) {
			mxCost = tmpCost;
			ret = i;
		}
	}
	return ret;
}

void addOneMatch(node_t& task, node_t& worker) {
	#ifdef LOCAL_DEBUG
	assert(satisfy(worker, task));
	#endif

	// add cost to utility
	utility += calcCost(task, worker);
	// update the capacity of task & worker
	++task.flow;
	++worker.flow;

	// double tmp = calcCost(task, worker);
	// printf("tmp = %.2lf\n", tmp);
}

void Pure_Greedy(ifstream& fin, int seqN) {
	node_t node;
	vector<node_t> tasks, workers;
	int taskId, workerId;
	
	while (seqN--) {
		nextSeq(fin, node);

		if (node.type == task) { // node is task
			taskId = tasks.size();
			tasks.push_back(node);
			workerId = chosenNextWorker(workers, node);
		} else {
			workerId = workers.size();
			workers.push_back(node);
			taskId = chosenNextTask(tasks, node);
		}
		
		if (workerId>=0 && taskId>=0) {
			#ifdef LOCAL_DEBUG
			assert(taskId>=0 && taskId<((int)tasks.size()));
			assert(workerId>=0 && workerId<((int)workers.size()));
			if (!satisfy(workers[workerId], tasks[taskId])) {
				putchar('\t');
				tasks[taskId].print();
				putchar('\t');
				workers[workerId].print();
			}
			assert(satisfy(workers[workerId], tasks[taskId]));
			#endif

			addOneMatch(tasks[taskId], workers[workerId]);

			#ifdef LOCAL_DEBUG
			assert(!satisfy(workers[workerId], tasks[taskId]));
			#endif
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
	Pure_Greedy(fin, seqN);

	#ifdef LOCAL_DEBUG
	assert(weightArr.size() == workerN);
	for (int i=0; i<weightArr.size(); ++i) {
		assert(weightArr[i].size() == taskN);
		for (int j=0; j<weightArr[i].size(); ++j)
			assert(weightArr[i][j] < Umax+0.1);
	}
	#endif
}

vector<string> split(string fileName, char ch) {
	vector<string> vstr;
	int len = fileName.length();

	for (int i=0,j=0; i<=len; ++i) {
		if (i==len || fileName[i]==ch) {
			if (i > j) {
				string str = fileName.substr(j, i-j);
				// puts(str.c_str());
				// fflush(stdout);
				vstr.push_back(str);
			}
			j = i + 1;
		}
	}

	return vstr;
}

int strToInt(string s) {
	int len = s.length(), ret = 0;

	for (int i=0; i<len; ++i)
		ret = ret * 10 + s[i]-'0';

	return ret;
}

string getParaStr(string fileName, double mu) {
	vector<string> vname = split(fileName, '/');
	string info = vname[vname.size()-2];
	vector<string> vinfo = split(info, '_');
	double degrate = strToInt(vinfo[vinfo.size()-2]) * 1.0 / 1000.0;

	string ret = "degrate=" + to_string(degrate) + ",mu=" + to_string(mu);

	// for (int i=0; i<vname.size(); ++i)
	// 	puts(vname[i].c_str());
	// for (int i=0; i<vinfo.size(); ++i)
	// 	puts(vinfo[i].c_str());

	return ret;
}

int main(int argc, char* argv[]) {
	cin.tie(0);
	ios::sync_with_stdio(false);

	string edgeFileName, weightFileName;
	program_t begProg, endProg;
	double mu = 0.005;

	if (argc >= 4) {
		weightFileName = string(argv[1]);
		edgeFileName = string(argv[2]);
		sscanf(argv[3], "%lf", &mu);
	} else {
		#ifdef AT_THE_SERVER
		weightFileName = "/home/server/zyx/Data0/7";
		edgeFileName = "/home/server/zyx/Data0/7/order14.txt";
		#else
		weightFileName = "/home/turf/tmp/dataz/1000_1000_5_100/weight.txt";
		edgeFileName = "/home/turf/tmp/dataz/1000_1000_5_100/order0.txt";
		#endif
	}

	//printf("[%d]: fileName = %s\n", getpid(), fileName.c_str());
	input_weight(edgeFileName, weightFileName, weightArr);

	save_time(begProg);
	solve(edgeFileName);
	save_time(endProg);

	double usedTime = calc_time(begProg, endProg);
	string paraStr = getParaStr(edgeFileName, mu);
	printf("Pure %s %.6lf\n", paraStr.c_str(), utility);
	fflush(stdout);
	
	return 0;
}
