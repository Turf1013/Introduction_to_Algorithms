#include <bits/stdc++.h>
using namespace std;

///////////////////control//////////////////////
const int FOCS = 0;
const int FIFO = 1;
const int SJF  = 0;
////////////////////////////////////////////////
const int POSITION_NUMBER = 8192;
const int DRIVER_NUMBER = 1024;
const int ORDER_NUMBER = 5000;
const int MINI_BATCH = 5;
const int CAP = 128;
const double INF = 1e60;
const double EPS = 1e-8;

int dcmp(double x) {
    if (fabs(x) < EPS) return 0;
    if (x > 0.) return 1;
    return -1;
}

int d, m, c, n; // d: position number, m: driver number, c: driver capacity, n: order number
double ans = 0.; // total completion time

struct TreeNode {
    int l, r, level, L, R;
    set <int> orderList;
    TreeNode(int _l = 0, int _r = 0, int _le = 0) : l(_l), r(_r), level(_le) {}
};

vector <vector <int> > E;
vector <TreeNode> Tree;
vector <int> deep;
vector <int> anc[20];
vector <double> dst;

const int BIT_NUM = 1e6 + 7;

int bit[BIT_NUM];
int dfn;
void upd(int x, int y) {
    while (x <= dfn) {
        bit[x] += y;
        x += x & -x;
    }
}
int get(int x) {
    int ret = 0;
    while (x) {
        ret += bit[x];
        x -= x & -x;
    }
    return ret;
}
int get(int l, int r) {
    return get(r) - get(l - 1);
}

struct Position {
    double x, y;
} p[POSITION_NUMBER];

struct Driver {
    int pid;
    vector <int> schedule;
    Driver (int _p = 1) : pid(_p) {}
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
    dfn ++;
    Tree[x].L = dfn;
    for (int i = 0; i < E[x].size(); ++i) {
        int v = E[x][i];
        if (v != pre) {
            anc[0][v] = x;
            deep[v] = deep[x] + 1;
            dfs(v, x);
        }
    }
    Tree[x].R = dfn;
}

void prepare() {
    deep[0] = 0;
    dfn = 0;
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
    p = ref[p - 1], q = ref[q - 1];
    return LCA_tree_node(p, q);
}

double distance_true_point(int p, int q) {
    p = ref[p - 1], q = ref[q - 1];
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

bool FIFO_cmp(const int &A, const int &B) {
    if (dcmp(order[A].t - order[B].t) == 0) return A < B;
    return order[A].t < order[B].t;
}
bool SJF_cmp(const int &A, const int &B) {
    if (dcmp(euclidean_metric(order[A].s, order[A].d) - euclidean_metric(order[B].s, order[B].d)) == 0) return A < B;
    return euclidean_metric(order[A].s, order[A].d) < euclidean_metric(order[B].s, order[B].d);
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

void middle_dfs(int x, int pre, vector <int> & V) {
    int i;
    for (i = 0; i < E[x].size() / 2; ++i) {
        int v = E[x][i];
        if (v != pre) {
            middle_dfs(v, x, V);
        }
    }
    for (set <int> :: iterator it = Tree[x].orderList.begin(); it != Tree[x].orderList.end(); ++ it) {
        V.push_back(*it);
    }
    for (; i < E[x].size(); ++i) {
        int v = E[x][i];
        if (v != pre) {
            middle_dfs(v, x, V);
        }
    }
}


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
            tim += euclidean_metric(nw, order[C[enum_perm[i]]].d);
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
            //random_sorting(cid);
        } else {
            random_sorting(cid);
        }
        for (int j = 0; j < cluster[cid].size(); ++ j) {
            if (PR[i] & 1) {
                ret.second.first += euclidean_metric(pos, order[cluster[cid][j]].d);
                ret.first += ret.second.first - order[cluster[cid][j]].t;
                pos = order[cluster[cid][j]].d;
            } else {
                ret.second.first += euclidean_metric(pos, order[cluster[cid][j]].d);
                pos = order[cluster[cid][j]].d;
            }
        }
    }
    ret.second.second = pos;
    return ret;
}

double calc_diff(int i, int j) {
    return euclidean_metric(order[i].s, order[j].s) + euclidean_metric(order[i].d, order[j].d);
}

/////////debug
//bool test[ORDER_NUMBER];
//int tottttt, tot11;
/////////

double run_driver(int id, double tim) {
    vector <int> &S = driver[id].schedule;
    /*
    for (int i = 0; i < S.size(); ++ i) assert(order[S[i]].t < tim + EPS);
    for (int i = 0; i < S.size(); ++ i) {
        assert(!test[S[i]]);
        test[S[i]] = true;
        tottttt ++;
    }
    */
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
        //assert(j < S.size());
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
            //assert(choose != -1);
            cluster[i].push_back(S[choose]);
            in_cluster[choose] = true;
        }
    }
    for (int i = R; D && i < MINI_BATCH; ++ i) {
        int j = 0;
        for (; j < S.size(); ++ j) {
            if (!in_cluster[j]) break;
        }
        //assert(j < S.size());
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
            //assert(choose != -1);
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

void solve() {
    for (int i = 0; i < m; ++ i) {
        Q.push(DriverStatus(i, 0.));
    }
    int pos = 0, diliver_num = 0;
    while (diliver_num < n) {
        DriverStatus best = Q.top();
        Q.pop();
        double tim = best.f_time;
        while (pos < n && order[pos].t < tim + EPS) {
            int lca = LCA_true_point(order[pos].s, order[pos].d);
            Tree[lca].orderList.insert(pos);
            upd(Tree[lca].L, 1);
            pos ++;
        }
        if (get(Tree[0].L, Tree[0].R) == 0) {
            assert(pos < n);
            tim = order[pos].t;
            int lca = LCA_true_point(order[pos].s, order[pos].d);
            Tree[lca].orderList.insert(pos);
            upd(Tree[lca].L, 1);
            pos ++;
        }
        int did = best.id;
        driver[did].schedule.clear();
        vector <int> cand_list;
        //printf("%d %d\n",get(Tree[0].L, Tree[0].R),  c);
        if (get(Tree[0].L, Tree[0].R) <= c) {
            //puts("abc");
            middle_dfs(0, -1, cand_list);
        } else {
            for (int i = Tree.size() - 1; i >= 0; -- i) {
                if (get(Tree[i].L, Tree[i].R) >= c) {
                    middle_dfs(i, anc[0][i], cand_list);
                    break;
                }
            }
        }
        if (FIFO) {
            sort(cand_list.begin(), cand_list.end(), FIFO_cmp);
        } else if (SJF) {
            sort(cand_list.begin(), cand_list.end(), FIFO_cmp);
        }
        for (int i = 0; i < c && i < cand_list.size(); ++ i) {
            int oid = cand_list[i];
            driver[did].schedule.push_back(oid);
            int lca = LCA_true_point(order[oid].s, order[oid].d);
            Tree[lca].orderList.erase(oid);
            upd(Tree[lca].L, -1);
        }
        //printf("%d\n", (int)cand_list.size());
        diliver_num += driver[did].schedule.size();

        Q.push(DriverStatus(did, run_driver(did, tim)));
        //printf("%d %d \n", diliver_num, pos);
        //return;
    }
}

int main(int argc, char **argv) {
	string execName("FOCS98_Pure");

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
    scanf("%d%d%d%d", &d, &m, &c, &n);
    for (int i = 1; i <= d; ++ i) {
        scanf("%lf%lf", &p[i].x, &p[i].y);
    }
    for (int i = 0; i < n; ++ i) {
        scanf("%lf%d%d", &order[i].t, &order[i].s, &order[i].d);
    }

    for (int i = 0; i < d; ++ i) {
        p[i] = p[i + 1];
    }

	clock_t begTime, endTime;
	begTime = clock();

    build_HST();
    prepare();

    for (int i = d; i > 0; -- i) {
        p[i] = p[i - 1];
    }

    solve();

	endTime = clock();

    double usedTime = (endTime - begTime)*1.0 / CLOCKS_PER_SEC;
	printf("%s %.3lf %.3lf\n", execName.c_str(), ans, usedTime);

	fflush(stdout);

    return 0;
}
