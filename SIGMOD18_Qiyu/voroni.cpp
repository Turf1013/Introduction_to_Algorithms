/**
	\author: 	Trasier
	\date:		2017.10.31
*/

#include "voroni.h"

const double inf = 1e30;
vector<point_t> points;
vector<point_t> centers;
int nV, nE;

void init_points() {
	string fileName("roadNetwork.txt");
	ifstream fin(fileName.c_str(), ios::in);
	
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}
	
	point_t p;
	fin >> nV >> nE;
	for (int i=0; i<nV; ++i) {
		fin >> p.x >> p.y;
		points.push_back(p);
	}
	
	fin.close();
}

void init_centers() {
	string fileName("centers.txt");
	ifstream fin(fileName.c_str(), ios::in);
	
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}
	
	int n;
	point_t p;
	fin >> n;
	for (int i=0; i<n; ++i) {
		fin >> p.x >> p.y;
		centers.push_back(p);
	}
	
	fin.close();
}

void init() {
	init_points();
	init_centers();
}
	
int main(int argc, char **argv) {
	if (argc > 1)
		freopen(argv[1], "w", stdout);
	
	init();
	vector<vector<int> > res = voroniSplit(points, centers);
	int c = 0;
	for (int i=0; i<res.size(); ++i) {
		if (res[i].size() > 0)
			++c;
	}
	
	printf("%d\n", c);
	for (int i=0; i<res.size(); ++i) {
		if (res[i].size() == 0)
			continue;
		int sz = res[i].size();
		printf("%d\n", sz);
		for (int j=0; j<sz; ++j) {
			printf("%d ", res[i][j]);
		}
		putchar('\n');
	}
	fflush(stdout);
	
	return 0;
}

double calc_distance(const point_t& a, const point_t& b) {
	return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

vector<vector<int> > voroniSplit(const vector<point_t>& points, const vector<point_t>& center) {
	vector<vector<int> > ret(center.size(), vector<int>());

	for (int i=0; i<points.size(); ++i) {
		double mnVal = inf, tmp;
		int v = -1;
		for (int j=0; j<center.size(); ++j) {
			tmp = calc_distance(points[i], center[j]);
			if (tmp < mnVal) {
				mnVal = tmp;
				v = j;
			}
		}
		ret[v].push_back(i);
	}

	return ret;
}
