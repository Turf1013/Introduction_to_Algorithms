/** 
 * first build HST, then run prepare()
 * then can use LCA(x, y) and d_tree(x, y)
 */

#include <bits/stdc++.h>
using namespace std;

const int MAX_NODE = 1e5 + 7;

struct TreeNode {
    int l, r, level;
    TreeNode(int _l = 0, int _r = 0, int _le = 0) : l(_l), r(_r), level(_le) {}
};

vector <vector <int> > E;
vector <TreeNode> Tree;
vector <int> deep;
vector <int> anc[20];
vector <double> dst;

int n;

struct Position {
    double x, y;
} p[MAX_NODE];

double sqr(double x) {
    return x * x;
}

double euclidean_metric(int a, int b) {
    return sqrt(sqr(p[a].x - p[b].x) + sqr(p[a].y - p[b].y));
}

int PI[MAX_NODE], idx[MAX_NODE], tmp_idx[MAX_NODE];

int ref[MAX_NODE];

bool tag[MAX_NODE];

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
    for (int i = 0; i < n; ++ i) {
        PI[i] = i;
        idx[i] = i;
    }

    // random_shuffle(PI, PI + n);
    double beta = 1; // todo: choose beta randomly from the distribution p(x) = 1/(xln2)

    double Delta = 0.;
    for (int i = 0; i < n; ++ i) {
        for (int j = i + 1; j < n; ++ j) {
            Delta = max(Delta, euclidean_metric(i, j));
        }
    }
    int delta = ceil(log(Delta) / log(2.));
    int root = new_node(0, n, delta);
    int st = 0, ed = Tree.size();
    for (int dep = delta - 1; ~ dep; -- dep) {
        double r = beta * (1ll << dep);
        memset(tag, 0, sizeof tag);
        int tmp_len = 0;
        for (int i = st; i < ed; ++ i) {
            int L = tmp_len, R = tmp_len;
            for (int j = 0; j < n; ++ j) {
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
        for (int i = 0; i < n; ++ i) {
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

int LCA(int p, int q) {
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

double d_tree(int p, int q) {
	return dst[p] + dst[q] - 2.0 * dst[LCA(p, q)];
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
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        scanf("%lf%lf", &p[i].x, &p[i].y);
    }

    build_HST();
    prepare();

    /* query the LCA between x and y 
     * printf("%f\n", LCA(x, y));
     */
    
    /* query the distance between x and y on tree 
     * printf("%f\n", d_tree(x, y));
     */
    
    return 0;
}