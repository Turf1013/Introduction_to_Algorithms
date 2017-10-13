#include <bits/stdc++.h>
using namespace std;

#include "output.h"

const int POSITION_NUMBER = 8192;
const int DRIVER_NUMBER = 1024;
const int ORDER_NUMBER = 5000;
const int BATCH = 20;
const int MINI_BATCH = 4;
const double INF = 1e60;
const double EPS = 1e-8;

int d, m, c, n; // d: position number, m: driver number, c: driver capacity, n: order number
double ans = 0.; // total completion time

struct Position {
    double x, y;
    Driver(int pid=1):pid(pid) {}
} p[POSITION_NUMBER];

struct Driver {
    int pid;
    vector <int> schedule;
} driver[DRIVER_NUMBER];

struct Order {
    double t;
    int s, d;
} order[ORDER_NUMBER];

bool check(const vector <int> & p) {
    assert(p.size() <= MINI_BATCH * 2);
    bool tag[MINI_BATCH << 1];
    memset(tag, 0, sizeof tag);
    for (int i = 0; i < p.size(); ++ i) {
        if (p[i] & 1) {
            if (!tag[p[i] >> 1]) return false;
        } else {
            tag[p[i] >> 1] = true;
        }
    }
    return true;
}

double sqr(double x) {
    return x * x;
}

double dist(int a, int b) {
    return sqrt(sqr(p[a].x - p[b].x) + sqr(p[a].y - p[b].y));
}

// get one driver's optimal solution
double run_driver(int did, double tim) {
    vector <int> perm;
    for (int i = 0; i < 2 * driver[did].schedule.size(); ++ i) {
        perm.push_back(i);
    }
    double t_ans = INF, t_tim = tim;
    do {
        if (check(perm)) {
            double tmp_ans = 0., tmp_tim = tim;
            for (int i = 0; i < perm.size(); ++ i) {
                int to_id;
                if (perm[i] & 1) {
                    to_id = order[driver[did].schedule[perm[i] >> 1]].d;
                } else {
                    to_id = order[driver[did].schedule[perm[i] >> 1]].s;
                }
                tmp_tim += dist(driver[did].pid, to_id);
                if (perm[i] & 1) {
                    tmp_ans += tmp_tim - order[driver[did].schedule[perm[i] >> 1]].t;
                }
            }
            if (tmp_ans < t_ans) {
                t_ans = tmp_ans, t_tim = tmp_tim;
            }
        }
    } while (next_permutation(perm.begin(), perm.end()));
    ans += t_ans;
    return t_tim - tim;
}

bool cmp(int a, int b) {
    return order[a].t < order[b].t;
}

// simulating: dispatch one batch orders to drivers
double simulate(int L, int R, double tim) {
    int len = R - L;
    int batch_len = MINI_BATCH * m;
    int st = L, ed;
    vector <int> cont;
    for (int i = L; i < R; ++ i) {
        cont.push_back(i);
    }
    sort(cont.begin(), cont.end(), cmp);
    while (st < R) {
        for (int i = 0; i < m; ++ i) {
            driver[i].schedule.clear();
        }
        ed = min(R, st + batch_len);
        for (int i = st; i < ed; ++ i) {
            driver[i % m].schedule.push_back(cont[i - L]);
        }
        double pass_time = 0.;
        for (int i = 0; i < m; ++ i) {
            double tmp = run_driver(i, tim);
            pass_time = max(pass_time, tmp);
        }
        tim += pass_time;
        st = ed;
    }
    return tim;
}

int main() {
  string execName("SJF");

  string srcFileName;
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

    clock_t begTime, endTime;
  	begTime = clock();

    double pre = 0., nw = 0.;
    int pos = 0;
    ans = 0.;
    while (pos < n) {
        if (nw < pre + BATCH) {
            nw = pre + BATCH;
        }
        int L = pos, R = pos;
        while (R - L <= m * c && order[R].t < nw) {
            R ++;
        }
        pos = R;
        double pending = simulate(L, R, nw);
        pre = nw, nw = pending;
    }
    printf("Short Job First: %.3f\n", ans);

    endTime = clock();

    double usedTime = (endTime - begTime)*1.0 / CLOCKS_PER_SEC;
    #ifdef WATCH_MEM
    dumpResult(execName, ans, usedTime, -1);
    #else
    dumpResult(execName, ans, usedTime);
    #endif

    fflush(stdout);

    return 0;
}
