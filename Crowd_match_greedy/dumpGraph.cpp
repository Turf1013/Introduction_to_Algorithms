#include <bits/stdc++.h>
using namespace std;

#include "input.h"

#define LOCAL_DEBUG

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
vector<vector<int> > weightArr;

bool satisfyLoc(const worker_t& worker, const task_t& task) {
	return (worker.x-task.x)*(worker.x-task.x) + (worker.y-task.y)*(worker.y-task.y) <= worker.r*worker.r;
}

void input_edge(ifstream& fin, vector<edge_t>& E, edgeN) {
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
			tasks.push_back(tas);
		}
	}
	
	const int workerN = workers.size();
	const int taskN = tasks.size();
	
	for (int i=0; i<workerN; ++i) {
		const int workerId = workers[i].id;
		for (int j=0; j<taskN; ++j) {
			const int taskId = tasks[j].id;
			if (satisfyLoc(workers[i], tasks[j])) {
				E.push_back(edge_t(workerId, taskId, weightArr[workerId][taskId]));
			}
		}
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
	
	fin.close();
}

int main(int argc, char **argv) {
	cin.tie(0);
	ios::sync_with_stdio(false);

	string dataPath, fileName, desFileName;
	program_t begProg, endProg;

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
		dataPath = "I:\\zyx\\0_0";
		fileName = "I:\\zyx\\0_0\\order0.txt";
		desFileName = "I:\\zyx\\gra";
		for (int i=dataPath.length()-1; i>=0; --i) {
			if (fileName[i] == '\\') {
				desFileName += "\\" + fileName.substr(i+1, dataPath.length()) + "\\.txt";
				break;
			}
		}
	}
	
	input_weight(dataPath, weightArr);
	dumpGraph(fileName, desFileName);
	
	return 0;
}