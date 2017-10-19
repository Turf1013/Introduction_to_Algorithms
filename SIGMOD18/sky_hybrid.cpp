/**
	\author: 	Sky_xuan
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
int enum_perm[CAP / MINI_BATCH + 4];
int best_perm[CAP / MINI_BATCH + 4];
void optimal_sorting(int x, int pos) {
    vector <int> &C = cluster[x];
    int len = C.size();
    for (int i = 0; i < len; ++ i) enum_perm[i] = i;
    double glob = INF;
    do {
        double tmp = 0., tim = 0.;
        int nw = pos;
        for (int i = 0; i < len; ++ i) {
            tim += dist(nw, order[C[enum_perm[i]]].d);
            tmp += tim;
            nw = order[C[enum_perm[i]]].d;
        }
        if (tmp < glob) {
            glob = tmp;
            for (int i = 0; i < len; ++ i) {
                best_perm[i] = C[enum_perm[i]];
            }
        }
    } while (next_permutation(enum_perm, enum_perm + len));
    for (int i = 0; i < len; ++ i) {
        C[i] = best_perm[i];
    }
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
            optimal_sorting(cid, pos);
            // random_sorting(cid);
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

/////////debug
/////////

double run_driver(int id, double tim) {
    vector <int> &S = driver[id].schedule;

    int R = S.size() % MINI_BATCH;
    int D = S.size() / MINI_BATCH;
    for (int i = 0; i < MINI_BATCH; ++ i) {
        cluster[i].clear();
    }
    memset(in_cluster, 0, sizeof in_cluster);
    for (int i = 0; i < R; ++ i) {
        int j = 0;
        for (; j < S.size(); ++ j) {
            if (!in_cluster[j]) break;
        }
        cluster[i].push_back(S[j]);
        in_cluster[j] = true;
        for (int num = 0; num < D; ++ num) {
            double mn = INF;
            int choose = -1;
            for (int t = 0; t < S.size(); ++ t) {
                if (in_cluster[t]) continue;
                if (mn > calc_diff(S[t], S[j])) {
                    choose = t;
                    mn = calc_diff(S[t], S[j]);
                }
            }
            cluster[i].push_back(S[choose]);
            in_cluster[choose] = true;
        }
    }
    for (int i = R; D && i < MINI_BATCH; ++ i) {
        int j = 0;
        for (; j < S.size(); ++ j) {
            if (!in_cluster[j]) break;
        }
        cluster[i].push_back(S[j]);
        in_cluster[j] = true;
        for (int num = 0; num < D - 1; ++ num) {
            double mn = INF;
            int choose = -1;
            for (int t = 0; t < S.size(); ++ t) {
                if (in_cluster[t]) continue;
                if (mn > calc_diff(S[t], S[j])) {
                    choose = t;
                    mn = calc_diff(S[t], S[j]);
                }
            }
            cluster[i].push_back(S[choose]);
            in_cluster[choose] = true;
        }
    }
    pair <double, pair <double, int> > ch = make_pair(INF, make_pair(INF, 0));
    for (int i = 0; i < perm_num; ++ i) {
        pair <double, pair <double, int> > cas = attempt(i, id, tim);
        ch = min(ch, cas);
    }
    ans += ch.first;
    driver[id].pid = ch.second.second;
    return ch.second.first;
}

void FIFO() {
    for (int i = 0; i < m; ++ i) {
        Q.push(DriverStatus(i, 0.));
    }
    int pos = 0;
    while (pos < n || FIFO_order_pool.size() > 0) {
        DriverStatus best = Q.top();
        Q.pop();
        double tim = best.f_time;
        while (pos < n && order[pos].t < tim + EPS) {
            FIFO_order_pool.insert(pos);
            pos ++;
        }
        if (FIFO_order_pool.empty()) {
            tim = order[pos].t;
            FIFO_order_pool.insert(pos);
            pos ++;
        }
        int did = best.id;
        driver[did].schedule.clear();
        int cnt = 0;
        set <int, FIFO_cmp> :: iterator FIFO_it = FIFO_order_pool.begin();
        while (cnt < c && FIFO_it != FIFO_order_pool.end()) {
            driver[did].schedule.push_back(*FIFO_it);
            FIFO_order_pool.erase(FIFO_it ++);
            cnt ++;
        }

        Q.push(DriverStatus(did, run_driver(did, tim)));
    }
}

void SJF() {
    for (int i = 0; i < m; ++ i) {
        Q.push(DriverStatus(i, 0.));
    }
    int pos = 0;
    while (pos < n || SJF_order_pool.size() > 0) {
        DriverStatus best = Q.top();
        Q.pop();
        double tim = best.f_time;
        while (pos < n && order[pos].t < tim + EPS) {
            SJF_order_pool.insert(pos);
            pos ++;
        }
        if (SJF_order_pool.empty()) {
            tim = order[pos].t;
            SJF_order_pool.insert(pos);
            pos ++;
        }
        int did = best.id;
        driver[did].schedule.clear();
        int cnt = 0;
        set <int, SJF_cmp> :: iterator SJF_it = SJF_order_pool.begin();
        while (cnt < c && SJF_it != SJF_order_pool.end()) {
            driver[did].schedule.push_back(*SJF_it);
            SJF_order_pool.erase(SJF_it ++);
            cnt ++;
        }

        Q.push(DriverStatus(did, run_driver(did, tim)));
    }
}

// hybrid FIFO and SJF
void Hybrid() {
    for (int i = 0; i < m; ++ i) {
        Q.push(DriverStatus(i, 0.));
    }
    int pos = 0;
    while (pos < n || FIFO_order_pool.size() > 0) {
        DriverStatus best = Q.top();
        Q.pop();
        double tim = best.f_time;
        while (pos < n && order[pos].t < tim + EPS) {
            FIFO_order_pool.insert(pos);
            SJF_order_pool.insert(pos);
            pos ++;
        }
        if (FIFO_order_pool.empty()) {
            tim = order[pos].t;
            FIFO_order_pool.insert(pos);
            SJF_order_pool.insert(pos);
            pos ++;
        }
        int did = best.id;
        driver[did].schedule.clear();
        int cnt = 0;
        set <int, FIFO_cmp> :: iterator FIFO_it = FIFO_order_pool.begin();
        while (cnt < c/2 && FIFO_it != FIFO_order_pool.end()) {
            driver[did].schedule.push_back(*FIFO_it);
            SJF_order_pool.erase(*FIFO_it);
            FIFO_order_pool.erase(FIFO_it ++);
            cnt ++;
        }
        set <int, SJF_cmp> :: iterator SJF_it = SJF_order_pool.begin();
        while (cnt < c && SJF_it != SJF_order_pool.end()) {
            driver[did].schedule.push_back(*SJF_it);
            FIFO_order_pool.erase(*SJF_it);
            SJF_order_pool.erase(SJF_it ++);
            cnt ++;
        }

        Q.push(DriverStatus(did, run_driver(did, tim)));
    }
}

int main(int argc, char **argv) {
	string execName("hybrid");

	if (argc > 1) {
		freopen(argv[1], "r", stdin);
	}
	if (argc > 2) {
		freopen(argv[2], "w", stdout);
	}

    FILE *fp = fopen("permutations_5.in", "r");
    fscanf(fp, "%d", &perm_num);
    for (int i = 0; i < perm_num; ++ i) {
        for (int j = 0; j < 2 * MINI_BATCH; ++ j) {
            fscanf(fp, "%d", &perm[i][j]);
        }
    }
	fclose(fp);
    scanf("%d%d%d%d", &d, &m, &c, &n);
    for (int i = 1; i <= d; ++ i) {
        scanf("%lf%lf", &p[i].x, &p[i].y);
    }
    for (int i = 0; i < n; ++ i) {
        scanf("%lf%d%d", &order[i].t, &order[i].s, &order[i].d);
    }

	clock_t begTime, endTime;
	begTime = clock();

	Hybrid();

	endTime = clock();

    double usedTime = (endTime - begTime)*1.0 / CLOCKS_PER_SEC;

	printf("%s %.3lf %.3lf\n", execName.c_str(), ans, usedTime);

	fflush(stdout);

    return 0;
}
