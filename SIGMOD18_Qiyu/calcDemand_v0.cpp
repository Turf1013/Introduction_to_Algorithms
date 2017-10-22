/**
	\author: 	Trasier
	\date: 		2017.10.22
*/
#include <bits/stdc++.h>
using namespace std;

#define LOCAL_DEBUG

struct position_t {
	double x, y;

	position_t(double x=0., double y=0.):
		x(x), y(y) {}

	bool operator< (const position_t& a) const {
		if (a.x == x)
			return y < a.y;
		return x < a.x;
	}

	bool operator== (const position_t& a) const {
		return x==a.x && y==a.y;
	}
};

const int maxn = 8e4;
const double eps = 1e-7;
const double inf = 1e25;
double timeWindow = 15;
double radius = 1000;
int nV, nE;
position_t pos[maxn];
int sum[maxn];

inline int dcmp(int x) {
	if (fabs(x) < eps)
		return 0;
	return x<0 ? -1 : 1;
}

vector<string> split(string s, char ch) {
	int len = s.length(), i = 0, j;
	vector<string> ret;

	while (i < len) {
		j = i;
		while (i<len && s[i]!=ch) {
			++i;
		}
		ret.push_back(s.substr(j, i-j));
		++i;
	}

	return ret;
}

vector<string> split(char *s, char ch) {
	return split(string(s), ch);
}

void readNetwork() {
	string srcFileName("Shanghai_roadnetwork.txt");
	ifstream fin(srcFileName.c_str(), ios::in);

	fin >> nV >> nE;
	for (int i=1; i<=nV; ++i) {
		fin >> pos[i].x >> pos[i].y;
	}

	fin.close();
}

void init() {
	memset(sum, 0, sizeof(sum));
}

void dump() {
	for (int i=1; i<=nV; ++i) {
		if (sum[i] == 0)
			continue;
		printf("%d %d\n", i, sum[i]);
	}
}

inline double Length2(position_t& pa, position_t& pb) {
	return ((pa.x-pb.x)*(pa.x-pb.x) + (pa.y-pb.y)*(pa.y-pb.y));
}

inline double Length(position_t& pa, position_t& pb) {
	return sqrt((pa.x-pb.x)*(pa.x-pb.x) + (pa.y-pb.y)*(pa.y-pb.y));
}

int findNN(double x, double y) {
	position_t po(x, y);
	double mnVal = inf, tmp;
	int ret = 0;

	for (int i=1; i<=nV; ++i) {
		tmp = Length2(pos[i], po);
		if (tmp < mnVal) {
			mnVal = tmp;
			ret = i;
		}
	}
	mnVal = sqrt(mnVal);
	#ifdef LOCAL_DEBUG
	fprintf(stderr, "%.3lf\n", mnVal);
	#endif

	return (mnVal>radius) ? 0:ret;
}

void count() {
	string line;
	stringstream stream;
	char buf[200];
	double xpos, ypos;

	while (gets(buf) != NULL) {
		string line(buf);
		vector<string> items = split(line, ',');
		if (items.size() < 3)
			continue;
		// #ifdef LOCAL_DEBUG
		// for (int i=0; i<items.size(); ++i) {
		// 	if (i == 0)
		// 		fprintf(stderr, "%s", items[i].c_str());
		// 	else
		// 		fprintf(stderr, ",%s", items[i].c_str());
		// }
		// fprintf(stderr, "\n");
		// #endif
		stream.clear();
		stream << items[1] << ' ' << items[2];
		stream >> xpos >> ypos;
		int id = findNN(xpos, ypos);
		// #ifdef LOCAL_DEBUG
		// if (id > 0)
		// 	fprintf(stderr, "(%.6lf, %.6lf) %d\n", xpos, ypos, id);
		// #endif
		++sum[id];
	}

	dump();
}

int main(int argc, char **argv) {
	if (argc > 1) {
		freopen(argv[1], "r", stdin);
	}
	if (argc > 2) {
		freopen(argv[2], "w", stdout);
	}
	if (argc > 3)
		sscanf(argv[3], "%lf", &timeWindow);
	if (argc > 4)
		sscanf(argv[4], "%lf", &radius);

	#ifdef LOCAL_DEBUG
	clock_t begTime, endTime;
	begTime = clock();
	#endif

	readNetwork();
	init();
	count();

	#ifdef LOCAL_DEBUG
	endTime = clock();
	double usedTime = (endTime - begTime) * 1000.0 / CLOCKS_PER_SEC ;
	fprintf(stderr, "time = %.2lfms.\n", usedTime);
	#endif

	fflush(stdout);

	return 0;
}
