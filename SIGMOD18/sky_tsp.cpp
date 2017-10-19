/**
	\author: 	Trasier
	\date: 		2017.10.16
*/
#include <bits/stdc++.h>
using namespace std;

const int POSITION_NUMBER = 8192;
const int DRIVER_NUMBER = 1024;
const int ORDER_NUMBER = 5000;
const int MINI_BATCH = 5;
const int CAP = 128;
const double INF = 1e60;
const double EPS = 1e-8;

int dcmp(double x) {
    if (fabs(x) < 1e-8) return 0;
    if (x > 0.) return 1;
    return -1;
}

int d, m, c, n; // d: position number, m: driver number, c: driver capacity, n: order number
double ans = 0.; // total completion time

struct Position {
    double x, y;
} p[POSITION_NUMBER];

struct Driver {
    int pid;
    vector <int> schedule;
    Driver (int _p = 1) : pid(_p) {}
} driver[DRIVER_NUMBER];

struct DriverStatus {
    int id;
    double f_time;
    DriverStatus (int _id = 0, double _f = 0.) : id(_id), f_time(_f) {}
};

bool operator < (const DriverStatus &A, const DriverStatus &B) {
    if (dcmp(A.f_time - B.f_time) == 0) return A.id > B.id;
    return A.f_time > B.f_time;
}

struct Order {
    double t;
    int s, d;
} order[ORDER_NUMBER];

double sqr(double x) {
    return x * x;
}

double dist(int a, int b) {
    return sqrt(sqr(p[a].x - p[b].x) + sqr(p[a].y - p[b].y));
}

struct FIFO_cmp {
    bool operator() (const int &A, const int &B) {
        if (dcmp(order[A].t - order[B].t) == 0) return A < B;
        return order[A].t < order[B].t;
    }
};

struct SJF_cmp {
    bool operator () (const int &A, const int &B) {
        if (dcmp(dist(order[A].s, order[A].d) - dist(order[B].s, order[B].d)) == 0) return A < B;
        return dist(order[A].s, order[A].d) < dist(order[B].s, order[B].d);
    }
};

set <int, FIFO_cmp> FIFO_order_pool;
set <int, SJF_cmp> SJF_order_pool;

priority_queue <DriverStatus> Q;

int perm_num;
int perm[200010][2 * MINI_BATCH];

vector <int> cluster[MINI_BATCH];
bool in_cluster[CAP];

void random_sorting(int x) {
    random_shuffle(cluster[x].begin(), cluster[x].end());
}

// TODO: implement the optimal_sorting
void optimal_sorting(int x) {
    ;
}

// return : (sum flow time, finish time, finish position)
pair <double, pair <double, int> > attempt(int permid, int did, double tim) {
    pair <double, pair <double, int> > ret = make_pair(0, make_pair(tim, 0));
    int *PR = perm[permid];
    int pos = driver[did].pid;
    for (int i = 0; i < 2 * MINI_BATCH; ++ i) {
        int cid = PR[i] >> 1;
        if (cluster[cid].size() == 0) continue;
        if (PR[i] & 1) {
            //optimal_sorting(cid);
            random_sorting(cid);
        } else {
            random_sorting(cid);
        }
        for (int j = 0; j < cluster[cid].size(); ++ j) {
            if (PR[i] & 1) {
                ret.second.first += dist(pos, order[cluster[cid][j]].d);
                ret.first += ret.second.first - order[cluster[cid][j]].t;
                pos = order[cluster[cid][j]].d;
            } else {
                ret.second.first += dist(pos, order[cluster[cid][j]].d);
                pos = order[cluster[cid][j]].d;
            }
        }
    }
    ret.second.second = pos;
    return ret;
}

double calc_diff(int i, int j) {
    return dist(order[i].s, order[j].s) + dist(order[i].d, order[j].d);
}

/**
	A.K.A. Using Prim to approximate TSP
*/
void dfsInTSP(int u, vector<vector<int> >& g, vector<int>& idxs, vector<int>& ret) {
	const int sz = g[u].size();

	ret.push_back(idxs[u]);
	for (int i=0; i<sz; ++i) {
		int v = g[u][i];
		dfsInTSP(v, g, idxs, ret);
	}
}

vector<int> calcRoute(vector<int>& idxs) {
	const int n = idxs.size();
	vector<double> dis(n, 1e20);
	vector<bool> visit(n, false);
	vector<int> pre(n, -1);
	vector<vector<int> > g(n, vector<int>());

	int oid = rand() % n, st = idxs[oid];
	for (int i=0; i<n; ++i) {
		int v = idxs[i];
		dis[i] = dist(st, v);
		pre[i] = oid;
	}
	pre[oid] = -1;
	visit[oid] = true;
	dis[oid] = 0;

	for (int i=1; i<n; ++i) {
		int v = -1;
		double mnVal = 1e20;
		for (int j=0; j<n; ++j) {
			if (!visit[j] && dis[j]<mnVal) {
				mnVal = dis[j];
				v = j;
			}
		}

		int u = pre[v];
		g[u].push_back(v);
		visit[v] = true;
		for (int j=0; j<n; ++j) {
			if (visit[j]) continue;
			double tmp = dist(idxs[v], idxs[j]);
			if (dis[j] > tmp) {
				dis[j] = tmp;
				pre[j] = v;
			}
		}
	}

	vector<int> ret;

	dfsInTSP(oid, g, idxs, ret);

	return ret;
}

double TSP() {
	vector<int> idxs;

	for (int i=1; i<=d; ++i) {
		idxs.push_back(i);
	}
	vector<int> routeId = calcRoute(idxs);
	double ret = 0;

	// assert(routeId.size() == d);
	for (int i=0; i<d; ++i) {
		int j = (i+1) % d;
		int u = routeId[i], v = routeId[j];
		ret += dist(u, v);
		printf("%d ", u);
	}
	putchar('\n');

	return ret;
}

int main(int argc, char **argv) {
	string execName("TSP");

	if (argc > 1) {
		freopen(argv[1], "r", stdin);
	}
	if (argc > 2) {
		freopen(argv[2], "w", stdout);
	}


    scanf("%d", &d);
    for (int i = 1; i <= d; ++ i) {
        scanf("%lf%lf", &p[i].x, &p[i].y);
    }
//    for (int i = 0; i < n; ++ i) {
//        scanf("%lf%d%d", &order[i].t, &order[i].s, &order[i].d);
//    }

	clock_t begTime, endTime;
	begTime = clock();

	double routeLen = TSP();

	endTime = clock();

    double usedTime = (endTime - begTime)*1.0 / CLOCKS_PER_SEC;
	ans = routeLen;
	printf("%s %.3lf %.3lf\n", execName.c_str(), ans, usedTime);

	fflush(stdout);

    return 0;
}
