/**
	\author: 	Sky_xuan
	\date: 		2017.10.17
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
    set <int> Sd;
    Driver (int _p = 0) : pid(_p) {}
} driver[DRIVER_NUMBER];

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

set <int, FIFO_cmp> FIFO_order_pool[POSITION_NUMBER];
set <int, SJF_cmp> SJF_order_pool[POSITION_NUMBER];

// for one driver
vector <int> TSP;

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
struct DriverStatus {
    int id;
    double f_time;
    DriverStatus (int _id = 0, double _f = 0.) : id(_id), f_time(_f) {}
};

bool operator < (const DriverStatus &A, const DriverStatus &B) {
    if (dcmp(A.f_time - B.f_time) == 0) return A.id > B.id;
    return A.f_time > B.f_time;
}

priority_queue <DriverStatus> Q;

void FIFO() {
    for (int i = 1; i <= d; ++ i) {
        TSP.push_back(i);
    }
    TSP = calcRoute(TSP);
    int nw = 0;
    for (int i = 0; i < m; ++ i) {
        driver[i].Sd.clear();
        Q.push(DriverStatus(i, 0.));
    }
    int diliver_num = 0;
    while (diliver_num < n) {
        DriverStatus best = Q.top();
        Q.pop();
        double tim = best.f_time;
        while (nw < n && order[nw].t < tim + EPS) {
            FIFO_order_pool[order[nw].s].insert(nw);
            nw ++;
        }
        int did = best.id;
        set <int> &Sd = driver[did].Sd;
        set <int> :: iterator it = Sd.begin();
        int pos = driver[did].pid;
        while (it != Sd.end()) {
            if (order[*it].d == TSP[pos]) {
                ans += tim - order[*it].t;
                Sd.erase(it ++);
                diliver_num ++;
            } else {
                it ++;
            }
        }
        while (Sd.size() < c && !FIFO_order_pool[TSP[pos]].empty()) {
            Sd.insert(*(FIFO_order_pool[TSP[pos]].begin()));
            FIFO_order_pool[TSP[pos]].erase(FIFO_order_pool[TSP[pos]].begin());
        }
        driver[did].pid = (pos + 1) % d;
        Q.push(DriverStatus(did, tim + dist(pos, driver[did].pid)));
    }
}

void SJF() {
    for (int i = 1; i <= d; ++ i) {
        TSP.push_back(i);
    }
    TSP = calcRoute(TSP);
    int nw = 0;
    for (int i = 0; i < m; ++ i) {
        driver[i].Sd.clear();
        Q.push(DriverStatus(i, 0.));
    }
    int diliver_num = 0;
    while (diliver_num < n) {
        DriverStatus best = Q.top();
        Q.pop();
        double tim = best.f_time;
        while (nw < n && order[nw].t < tim + EPS) {
            SJF_order_pool[order[nw].s].insert(nw);
            nw ++;
        }
        int did = best.id;
        set <int> &Sd = driver[did].Sd;
        set <int> :: iterator it = Sd.begin();
        int pos = driver[did].pid;
        while (it != Sd.end()) {
            if (order[*it].d == TSP[pos]) {
                ans += tim - order[*it].t;
                Sd.erase(it ++);
                diliver_num ++;
            } else {
                it ++;
            }
        }
        while (Sd.size() < c && !SJF_order_pool[TSP[pos]].empty()) {
            Sd.insert(*(SJF_order_pool[TSP[pos]].begin()));
            SJF_order_pool[TSP[pos]].erase(SJF_order_pool[TSP[pos]].begin());
        }
        driver[did].pid = (pos + 1) % d;
        Q.push(DriverStatus(did, tim + dist(pos, driver[did].pid)));
    }
}

int main(int argc, char **argv) {
	string execName("staticfifos");

	if (argc > 1) {
		freopen(argv[1], "r", stdin);
	}
	if (argc > 2) {
		freopen(argv[2], "w", stdout);
	}
	
    scanf("%d%d%d%d", &d, &m, &c, &n);
    for (int i = 1; i <= d; ++ i) {
        scanf("%lf%lf", &p[i].x, &p[i].y);
    }
    for (int i = 0; i < n; ++ i) {
        scanf("%lf%d%d", &order[i].t, &order[i].s, &order[i].d);
    }
    int lenn = (d + m - 1) / m;
    for (int i = 0; i < m; ++ i) {
        driver[i].pid = i * lenn % d;
    }
	
	clock_t begTime, endTime;
	begTime = clock();

	FIFO();

	endTime = clock();

    double usedTime = (endTime - begTime)*1.0 / CLOCKS_PER_SEC;
	printf("%s %.3lf %.3lf\n", execName.c_str(), ans, usedTime);

	fflush(stdout);
	
    return 0;
}