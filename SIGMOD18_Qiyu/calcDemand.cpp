/**
	\author: 	Trasier
	\date: 		2017.10.22
*/
#include <bits/stdc++.h>
using namespace std;

//#define LOCAL_DEBUG

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

const int itemSize = 3;
const int maxn = 8e4;
const double eps = 1e-7;
const double inf = 1e25;
double timeWindow = 5 * 60;
double radius = 1000, radius2;
int nV, nE;
position_t points[maxn];
double maxX, minX, maxY, minY;
int nrow, ncol, ngrid;
vector<vector<int> > vnodes;
int dir[9][2] = {
	{0,0},
	{-1,0},{1,0},{0,-1},{0,1},
	{-1,-1},{-1,1},{1,-1},{1,1}
};

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
		fin >> points[i].x >> points[i].y;
	}

	fin.close();
}

inline int calcCid(double x) {
	double dx = x - minX;
	return (int)(dx / radius);
}

inline int calcRid(double y) {
	double dy = y - minY;
	return (int)(dy / radius);
}

inline int calcGid(int rid, int cid) {
	return rid*ncol + cid;
}

void initGrid() {
	int rid, cid, gid;
	int ngrid = nrow * ncol;

	for (int i=0; i<ngrid; ++i)
		vnodes.push_back(vector<int>());

	for (int i=1; i<=nV; ++i) {
		cid = calcCid(points[i].x);
		rid = calcRid(points[i].y);
		gid = calcGid(rid, cid);
		vnodes[gid].push_back(i);
	}

	//printf("radius = %.2lf, timeWindow = %.2lf\n", radius, timeWindow);
}

/**
	x \in [298817.300504, 451432.597873]
	y \in [3386711.87457, 3524904.91576]
*/
void init() {
	radius2 = radius * radius;
	maxX = maxY = -inf;
	minX = minY = inf;
	for (int i=1; i<=nV; ++i) {
		maxX = max(maxX, points[i].x);
		minX = min(minX, points[i].x);
		maxY = max(maxY, points[i].y);
		minY = min(minY, points[i].y);
	}
	maxX = ceil(maxX + radius);
	minX = floor(minX - radius);
	maxY = ceil(maxY + radius);
	minY = floor(minY - radius);
	ncol = ceil((maxX - minX) / radius);
	nrow = ceil((maxY - minY) / radius);
	initGrid();
}

inline double Length2(position_t& pa, position_t& pb) {
	return ((pa.x-pb.x)*(pa.x-pb.x) + (pa.y-pb.y)*(pa.y-pb.y));
}

inline double Length(position_t& pa, position_t& pb) {
	return sqrt((pa.x-pb.x)*(pa.x-pb.x) + (pa.y-pb.y)*(pa.y-pb.y));
}

inline bool judge(double x, double y) {
	return x>=minX && x<=maxX && y>=minY && y<=maxY;
}

int findNN(double x, double y) {
	if (!judge(x, y))
		return 0;

	position_t po(x, y);
	int rid = calcRid(y);
	int cid = calcCid(x);
	double mnVal = inf, tmp;
	int ret = 0;

	for (int i=0; i<9; ++i) {
		int _rid = rid + dir[i][0], _cid = cid + dir[i][1];
		int _gid = calcGid(_rid, _cid);
		vector<int>& vp = vnodes[_gid];
		int sz = vp.size();
		for (int j=0; j<sz; ++j) {
			tmp = Length2(points[vp[j]], po);
			if (tmp < mnVal) {
				mnVal = tmp;
				ret = vp[j];
			}
		}
	}

	return ret;
}

void parseDateStr(string& s, string& d, int& tid) {
	int len = s.length(), i;

	for (i=0; i<len; ++i) {
		if (s[i] == ' ') {
			d = s.substr(0, i);
			break;
		}
	}

	int t = 0, dt;

	for (int j=i+1,k=0; k<3; j+=3,++k) {
		dt = 10 * (s[j]-'0') + (s[j+1]-'0');
		#ifdef LOCAL_DEBUG
		printf("dt[%d]=%d, ", k, dt);
		#endif
		if (k <= 1)
			t = (t + dt) * 60;
		else
			t = t + dt;
	}
	#ifdef LOCAL_DEBUG
	putchar('\n');
	#endif

	tid = t / timeWindow;
}

void count() {
	string line;
	stringstream stream;
	char buf[200];
	double xpos, ypos;

	while (gets(buf) != NULL) {
		string line(buf);
		vector<string> items = split(line, ',');
		if (items.size() < itemSize)
			continue;
		stream.clear();
		stream << items[itemSize-2] << ' ' << items[itemSize-1];
		stream >> xpos >> ypos;
		int id = findNN(xpos, ypos);
		string dateStr;
		int tid;
		parseDateStr(items[itemSize-3], dateStr, tid);
		printf("%s %d %d\n", dateStr.c_str(), tid, 1);
	}
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
