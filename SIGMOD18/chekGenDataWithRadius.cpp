#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-6;
typedef pair<double,double> pdd;
typedef pair<int,int> pii;
vector<pdd> points;
vector<pii> orders;
double r;
int V, N;

inline double Length(pdd a, pdd b) {
	return sqrt((a.first-b.first)*(a.first-b.first) + (a.second-b.second)*(a.second-b.second));
}

bool checkData() {
	int u, v;
	
	for (int i=0; i<N; ++i) {
		u = orders[i].first - 1;
		v = orders[i].second - 1;
		// if (!(u>=0 && u<V) || !(v>=0 && v<V)) {
			// printf("wrong at %d, %.3lf\n", i+1);
			// fflush(stdout);
		// }
		assert(u>=0 && u<V);
		assert(v>=0 && v<V);
		if (Length(points[u], points[v]) > r+eps)
			return false;
	}
	return true;
}

void checkFile(string fileName) {
	ifstream fin(fileName.c_str(), ios::in);
	
	if (!fin.is_open()) {
		printf("%s is invalid.\n", fileName.c_str());
	}
	
	points.clear();
	orders.clear();
	double x, y;
	int u, v;
	
	fin >> V;
	for (int i=0; i<V; ++i) {
		fin >> x >> y;
		points.push_back(make_pair(x, y));
	}
	fin >> N >> r;
	for (int i=0; i<N; ++i) {
		fin >> u >> v;
		orders.push_back(make_pair(u, v));
	}
	
	if (!checkData())
		printf("The data of %s is wrong.\n", fileName.c_str());
	
	fin.close();
}

string genFileName(string prefix, int nV) {
	stringstream stream;
	string ret;
	
	stream << prefix << "nv_" << nV << ".txt";
	stream >> ret;
	
	return ret;
}

void check() {
	string filePath = "F:\\tmp\\tmpData\\";
	int a[4] = {100, 500, 1000, 2000};
	for (int i=0; i<4; ++i) {
		string fileName = genFileName(filePath, a[i]);
		checkFile(fileName);
	}
}

int main() {
	check();
	
	return 0;
}