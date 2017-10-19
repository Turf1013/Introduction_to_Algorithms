/**
	\author: 	Sky_xuan
	\date: 		2017.10.20
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

struct TreeNode {
    int l, r, level;
    TreeNode(int _l = 0, int _r = 0, int _le = 0) : l(_l), r(_r), level(_le) {}
};

vector <vector <int> > E;
vector <TreeNode> Tree;
vector <int> deep;
vector <int> anc[20];
vector <double> dst;

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

double euclidean_metric(int a, int b) {
    return sqrt(sqr(p[a].x - p[b].x) + sqr(p[a].y - p[b].y));
}

int PI[POSITION_NUMBER], idx[POSITION_NUMBER], tmp_idx[POSITION_NUMBER];

int ref[POSITION_NUMBER];

bool tag[POSITION_NUMBER];

int new_node(int l, int r, int lv) {
    vector <int> ept;
    Tree.push_back(TreeNode(l, r, lv));
    E.push_back(ept);
    deep.push_back(0);
    dst.push_back(0.);
    for (int i = 0; i < 20; ++ i) {
        anc[i].push_back(0);
    }
    return Tree.size() - 1;
}


void build_HST() {
    for (int i = 0; i < d; ++ i) {
        PI[i] = i;
        idx[i] = i;
    }

    // random_shuffle(PI, PI + d);
    double beta = 1; // todo: choose beta randomly from the distribution p(x) = 1/(xln2)

    double Delta = 0.;
    for (int i = 0; i < d; ++ i) {
        for (int j = i + 1; j < d; ++ j) {
            Delta = max(Delta, euclidean_metric(i, j));
        }
    }
    int delta = ceil(log(Delta) / log(2.));
    int root = new_node(0, d, delta);
    int st = 0, ed = Tree.size();
    for (int dep = delta - 1; ~ dep; -- dep) {
        double r = beta * (1ll << dep);
        memset(tag, 0, sizeof tag);
        int tmp_len = 0;
        for (int i = st; i < ed; ++ i) {
            int L = tmp_len, R = tmp_len;
            for (int j = 0; j < d; ++ j) {
                for (int t = Tree[i].l; t < Tree[i].r; ++ t) {
                    if (!tag[idx[t]] && euclidean_metric(idx[t], PI[j]) < r) {
                        tag[idx[t]] = true;
                        tmp_idx[R ++] = idx[t];
                        tmp_len ++;
                    }
                }
                if (L < R) {
                    int id = new_node(L, R, dep);
                    E[i].push_back(id);
                    dst[id] = dst[i] + (1ll << (dep + 1));
                    if (dep == 0) {
                        ref[tmp_idx[L]] = id;
                    }
                    L = R;
                }
            }
            assert(tmp_len == Tree[i].r);
        }
        st = ed;
        ed = Tree.size();
        for (int i = 0; i < d; ++ i) {
            idx[i] = tmp_idx[i];
        }
    }
}

void dfs(int x, int pre) {
    for (int i = 0; i < E[x].size(); ++i) {
        int v = E[x][i];
        if (v != pre) {
            anc[0][v] = x;
            deep[v] = deep[x] + 1;
            dfs(v, x);
        }
    }
}

void prepare() {
    deep[0] = 0;
    dfs(0, -1);
    int N = Tree.size();
    for (int i = 0; i < N; i++) {
        for (int j = 1; (1 << j) <= N; ++ j) { 
            anc[j][i] = -1;
        }
    }
    for (int j = 1; (1 << j) <= N; ++ j) {
        for (int i = 0; i < N; ++ i) {
            if (anc[j - 1][i] != -1) {
                int a = anc[j - 1][i];
                anc[j][i] = anc[j - 1][a];
            }
        }
    }
}

int LCA_tree_node(int p, int q) {
    int lo;
    if (deep[p] < deep[q]) swap(p, q);
    for (lo = 1; (1 << lo) <= deep[p]; lo++); lo--;
    for (int i = lo; i >= 0; i--)
        if (deep[p] - (1 << i) >= deep[q])
            p = anc[i][p];
    if (p == q)
        return p;
    for (int i = lo; i >= 0; i--) {
        if (anc[i][p] != -1 && anc[i][p] != anc[i][q]) {
            p = anc[i][p];
            q = anc[i][q];
        }
    }
    return anc[0][p];
}

double distance_tree_node(int p, int q) {
    return dst[p] + dst[q] - 2. * dst[LCA_tree_node(p, q)];
}

int LCA_true_point(int p, int q) {
    p = ref[p], q = ref[q];
    return LCA_tree_node(p, q);
}

double distance_true_point(int p, int q) {
    p = ref[p], q = ref[q];
    return distance_tree_node(p, q);
}

void test_print() {
    int l = 0, r = 0;
    while (l < Tree.size()) {
        while (r < Tree.size() && Tree[r].level == Tree[l].level) {
            r ++;
        }
        printf("%d\n", r - l);
        for (int i = l; i < r; ++ i) {
            for (int j = Tree[i].l; j < Tree[i].r; ++ j) {
                printf("%d ", idx[j]);
            }
            puts("");
        }
        l = r;
    }
}

struct FIFO_cmp {
    bool operator() (const int &A, const int &B) {
        if (dcmp(order[A].t - order[B].t) == 0) return A < B;
        return order[A].t < order[B].t;
    }
};

struct SJF_cmp {
    bool operator () (const int &A, const int &B) {
        if (dcmp(euclidean_metric(order[A].s, order[A].d) - euclidean_metric(order[B].s, order[B].d)) == 0) return A < B;
        return euclidean_metric(order[A].s, order[A].d) < euclidean_metric(order[B].s, order[B].d);
    }
};

set <int, FIFO_cmp> FIFO_order_pool[POSITION_NUMBER];
set <int, SJF_cmp> SJF_order_pool[POSITION_NUMBER];

// for one driver
vector <int> TSP[DRIVER_NUMBER];

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
		dis[i] = euclidean_metric(st, v);
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
			double tmp = euclidean_metric(idxs[v], idxs[j]);
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

int cycle_num;
vector <int> orderid[DRIVER_NUMBER];

void FIFO(int x) {
    TSP[x] = calcRoute(TSP[x]);
    int nw = 0;
    for (int i = 0; i < 1; ++ i) {
        driver[i].pid = 0;
        driver[i].Sd.clear();
        Q.push(DriverStatus(i, 0.));
    }
    int diliver_num = 0;
    while (diliver_num < orderid[x].size()) {
        DriverStatus best = Q.top();
        Q.pop();
        double tim = best.f_time;
        while (nw < orderid[x].size() && order[orderid[x][nw]].t < tim + EPS) {
            FIFO_order_pool[order[orderid[x][nw]].s].insert(orderid[x][nw]);
            nw ++;
        }
        int did = best.id;
        set <int> &Sd = driver[did].Sd;
        set <int> :: iterator it = Sd.begin();
        int pos = driver[did].pid;
        while (it != Sd.end()) {
            if (order[*it].d == TSP[x][pos]) {
                ans += tim - order[*it].t;
                Sd.erase(it ++);
                diliver_num ++;
            } else {
                it ++;
            }
        }
        while (Sd.size() < c && !FIFO_order_pool[TSP[x][pos]].empty()) {
            Sd.insert(*(FIFO_order_pool[TSP[x][pos]].begin()));
            FIFO_order_pool[TSP[x][pos]].erase(FIFO_order_pool[TSP[x][pos]].begin());
        }
        driver[did].pid = (pos + 1) % TSP[x].size();
        Q.push(DriverStatus(did, tim + euclidean_metric(pos, driver[did].pid)));
    }
}

void SJF(int x) {
    TSP[x] = calcRoute(TSP[x]);
    int nw = 0;
    for (int i = 0; i < 1; ++ i) {
        driver[i].pid = 0;
        driver[i].Sd.clear();
        Q.push(DriverStatus(i, 0.));
    }
    int diliver_num = 0;
    while (diliver_num < orderid[x].size()) {
        DriverStatus best = Q.top();
        Q.pop();
        double tim = best.f_time;
        while (nw < orderid[x].size() && order[orderid[x][nw]].t < tim + EPS) {
            SJF_order_pool[order[orderid[x][nw]].s].insert(orderid[x][nw]);
            nw ++;
        }
        int did = best.id;
        set <int> &Sd = driver[did].Sd;
        set <int> :: iterator it = Sd.begin();
        int pos = driver[did].pid;
        while (it != Sd.end()) {
            if (order[*it].d == TSP[x][pos]) {
                ans += tim - order[*it].t;
                Sd.erase(it ++);
                diliver_num ++;
            } else {
                it ++;
            }
        }
        while (Sd.size() < c && !SJF_order_pool[TSP[x][pos]].empty()) {
            Sd.insert(*(SJF_order_pool[TSP[x][pos]].begin()));
            SJF_order_pool[TSP[x][pos]].erase(SJF_order_pool[TSP[x][pos]].begin());
        }
        driver[did].pid = (pos + 1) % TSP[x].size();
        Q.push(DriverStatus(did, tim + euclidean_metric(pos, driver[did].pid)));
    }
}

int main(int argc, char **argv) {
	string execName("staticHSTfifo");

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
    
    build_HST();
    prepare();
    
    cycle_num = 0;
    for (int i = 0; i < Tree.size(); ++ i) {
        if (Tree[i].r - Tree[i].l <= 1) continue;
        for (int j = Tree[i].l; j < Tree[i].r; ++ j) {
            TSP[cycle_num].push_back(idx[j]);
        }
        sort(TSP[cycle_num].begin(), TSP[cycle_num].end());
        cycle_num ++;
        if (cycle_num == m) break;
    }

    for (int i = 0; i < n; ++ i) {
        for (int j = cycle_num - 1; j >= 0; -- j) {
            int pos1, pos2;
            pos1 = lower_bound(TSP[j].begin(), TSP[j].end(), order[i].s) - TSP[j].begin();
            pos2 = lower_bound(TSP[j].begin(), TSP[j].end(), order[i].d) - TSP[j].begin();
            if (pos1 < TSP[j].size() && pos2 < TSP[j].size() && TSP[j][pos1] == order[i].s && TSP[j][pos2] == order[i].d) {
                orderid[j].push_back(i);
                break;
            }
        }
    }
    for (int i = 0; i < cycle_num; ++ i) {
        FIFO(i);
        //SJF(i);
    }
	
	endTime = clock();

    double usedTime = (endTime - begTime)*1.0 / CLOCKS_PER_SEC;
	printf("%s %.3lf %.3lf\n", execName.c_str(), ans, usedTime);

	fflush(stdout);
	
    return 0;
}