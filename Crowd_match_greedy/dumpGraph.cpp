#include <bits/stdc++.h>
using namespace std;

//#define LOCAL_DEBUG

struct edge_t {
	int u, v;
	double w;
	
	edge_t(int u=0, int v=0, double w=0.):
		u(u), v(v), w(w) {}
};

struct worker_t {
	int id;
	double x, y, r;
	
	worker_t(int id=0, double x=0., double y=0., double r=0.):
		id(id), x(x), y(y), r(r) {}
};

struct task_t {
	int id;
	double x, y;
	
	task_t(int id=0, double x=0., double y=0.):
		id(id), x(x), y(y) {}
};

vector<edge_t> E;
vector<vector<double> > weightArr;

bool satisfyLoc(const worker_t& worker, const task_t& task) {
	return (worker.x-task.x)*(worker.x-task.x) + (worker.y-task.y)*(worker.y-task.y) <= worker.r*worker.r;
}

void input_basic(const string& fileName, int& taskN, int& workerN, int& Umax, int& sumC, int& seqN) {
	ifstream fin(fileName.c_str(), ios::in);

	if (!fin.is_open()) {
		printf("Error openning FILE %s.\n", fileName.c_str());
		exit(1);
	}

	fin >> workerN >> taskN >> Umax >> sumC;
	seqN = workerN + taskN;

	fin.close();
}

void input_weight(const string& path, vector<vector<double> >& weightArr) {
	int taskN, workerN, sumC, seqN, Umax;

	// get basic parameter from any order file 
	string dataFileName = path + "/" + "order0.txt";
	input_basic(dataFileName, taskN, workerN, Umax, sumC, seqN);

	// get weight array
	string fileName = path + "/" + "weight.txt";
	ifstream fin(fileName.c_str(), ios::in);
	weightArr.clear();
	vector<double> weightRow(taskN, 0);

	if (!fin.is_open()) {
		printf("Error openning FILE %s.\n", fileName.c_str());
		exit(1);
	}

	weightArr.clear();
	for (int i=0; i<workerN; ++i) {
		for (int j=0; j<taskN; ++j) {
			fin >> weightRow[j];
		}
		weightArr.push_back(weightRow);
	}


	fin.close();
}

void input_edge(ifstream& fin, vector<edge_t>& E, int edgeN) {
	E.clear();
	int timeId, begTime, endTime, cap;
	double rate, payback;
	string stype;
	vector<worker_t> workers;
	vector<task_t> tasks;
	
	while (edgeN--) {
		fin >> begTime >> stype;
		if (stype[0] == 'w') {
			worker_t worker;
			fin >> worker.id >> worker.x >> worker.y >> worker.r >> cap >> endTime >> rate;
			workers.push_back(worker);
		} else {
			task_t task;
			fin >> task.id >> task.x >> task.y >> endTime >> payback;
			tasks.push_back(task);
		}
	}
	
	const int workerN = workers.size();
	const int taskN = tasks.size();
	
	for (int i=0; i<workerN; ++i) {
		const int workerId = workers[i].id;
		#ifdef LOCAL_DEBUG
		int c = 0;
		#endif
		for (int j=0; j<taskN; ++j) {
			const int taskId = tasks[j].id;
			if (satisfyLoc(workers[i], tasks[j])) {
				E.push_back(edge_t(workerId, taskId, weightArr[workerId][taskId]));
				#ifdef LOCAL_DEBUG
				++c;
				#endif
			}
		}
		#ifdef LOCAL_DEBUG
			printf("%d: c = %d\n", workerId, c);
		#endif
	}
}

void dumpEdge(string fileName) {
	ofstream fout(fileName.c_str(), ios::out);
	
	if (!fout.is_open()) {
		printf("Error openning FILE %s.\n", fileName.c_str());
		exit(1);
	}
	
	const int workerN = weightArr.size();
	const int taskN = (workerN==0) ? 0 : weightArr[0].size();
	// worker: [0, workerN-1) task: [workerN, taskN+workerN)
	
	const int vertexN = workerN + taskN;
	const int edgeN = E.size();
	
	fout << vertexN << " " << edgeN << endl;
	for (int i=0; i<edgeN; ++i) {
		fout << E[i].u << " " << E[i].v+workerN-1 << " " << E[i].w << endl;
	}
	
	fout.close();
}

void dumpInfo() {
	const int workerN = weightArr.size();
	const int taskN = (workerN==0) ? 0 : weightArr[0].size();
	vector<int> workerDeg(workerN, 0);
	vector<int> taskDeg(taskN, 0);
	int workerSumDeg = 0, taskSumDeg = 0;
	const int edgeN = E.size();
	set<int> taskSet;
	
	for (int i=0; i<edgeN; ++i) {
		const int workerId = E[i].u;
		const int taskId = E[i].v;
		++workerDeg[workerId];
		++taskDeg[taskId];
		++workerSumDeg;
		++taskSumDeg;
		taskSet.insert(E[i].v);
	}

	#ifdef LOCAL_DEBUG
	for (int i=0; i<taskN; ++i) {
		if (i>0 && i%10==0)
			putchar('\n');
		printf("%d ", taskDeg[i]);
	}
	putchar('\n');
	#endif

	double workerAvgDeg = workerSumDeg * 1.0 / workerN, taskAvgDeg = taskSumDeg * 1.0 / taskN;
	double workerVarDeg = 0., taskVarDeg = 0.;

	for (int i=0; i<workerN; ++i) {
		workerVarDeg += (workerDeg[i] - workerAvgDeg) * (workerDeg[i] - workerAvgDeg);
	}
	if (workerN > 0) workerVarDeg /= workerN;

	for (int i=0; i<taskN; ++i) {
		taskVarDeg += (taskDeg[i] - taskAvgDeg) * (taskDeg[i] - taskAvgDeg);
	}
	if (taskN > 0) taskVarDeg /= taskN;

	assert(taskSet.size() <= taskN);
	double aloneTaskRate = (taskN==0) ? 0.0 : (taskN-taskSet.size())*1.0 / taskN;

	printf("workerAvgDeg=%.2lf workerVarDeg=%.2lf taskAvgDeg=%.2lf taskVarDeg=%.2lf aloneTaskRate=%.2lf\n", 
		workerAvgDeg, workerVarDeg, taskAvgDeg, taskVarDeg, aloneTaskRate);
}

void dumpGraph(string srcFileName, string desFileName) {
	int workerN, taskN, Umax, sumC;
	
	ifstream fin(srcFileName.c_str(), ios::in);
	
	if (!fin.is_open()) {
		printf("Error openning FILE %s.\n", srcFileName.c_str());
		exit(1);
	}
	
	fin >> workerN >> taskN >> Umax >> sumC;
	input_edge(fin, E, workerN+taskN);
	dumpEdge(desFileName);
	dumpInfo();
	
	fin.close();
}

int main(int argc, char **argv) {
	cin.tie(0);
	ios::sync_with_stdio(false);
#ifdef LOCAL_DEBUG
	//freopen("data.in", "r", stdin);
	freopen("data.out", "w", stdout);
#endif

	string dataPath, fileName, desFileName;

	if (argc > 2) {
		fileName = string(argv[1]);
		for (int i=fileName.length()-1; i>=0; --i) {
			if (fileName[i] == '/') {
				dataPath = fileName.substr(0, i);
				break;
			}
		}
		desFileName = string(argv[2]);
	} else {
		dataPath = "/home/turf/Code/SmallData/data0/1000_1000_100_100/0";
		fileName = "/home/turf/Code/SmallData/data0/1000_1000_100_100/0/order0.txt";
		desFileName = "/home/turf/tmp";
		for (int i=dataPath.length()-1; i>=0; --i) {
			if (dataPath[i] == '/') {
				desFileName += "/" + dataPath.substr(i+1, dataPath.length()) + ".txt";
				break;
			}
		}
		// cout << dataPath << " " << fileName << " " << desFileName << endl;
	}
	
	input_weight(dataPath, weightArr);
	dumpGraph(fileName, desFileName);
	
	return 0;
}
