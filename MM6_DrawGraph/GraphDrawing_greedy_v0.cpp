// C++11
#include <bits/stdc++.h>
using namespace std;

struct edge_t {
    int u, v, w;

    edge_t(int u=0, int v=0, int w=0):
        u(u), v(v), w(w) {}

    bool operator<(const edge_t& o) const {
        return w < o.w;
    }
};

typedef pair<int,int> pii;
const double inf = 1e20;
const int maxn = 1005;
const int maxm = 701;
vector<pii> g[maxn];
pii pos[maxn];
set<pii> posSet;
bool visitVer[maxn];
bool visitPos[maxn][maxn];
vector<edge_t> ve;

class GraphDrawing {
public:
    int N;

    void init(int n) {
        N = n;
        ve.clear();
        posSet.clear();
        memset(visitVer, false, sizeof(visitVer));
        memset(visitPos, false, sizeof(visitPos));
        for (int i=0; i<n; ++i)
            g[i].clear();
    }

    void getAvaliablePos(int& vx, int& vy) {
        int x = vx, y = vy;

        for (int ds=0; ds<maxm; ++ds) {
            for (int dx=0; dx<=ds; ++dx) {
                int dy = ds - dx;
                for (int signx=-1; signx<=1; signx+=2) {
                    vx = x + signx * dx;
                    for (int signy=-1; signy<=1; signy+=2) {
                        vy = y + signy * dy;
                        if (posSet.count(make_pair(vx, vy)) == 0) {
                            return ;
                        }
                    }
                }
            }
        }

        assert(false);
    }
    
    void getAvaliablePos(int ux, int uy, int& vx, int& vy, int w) {
        int x = vx, y = vy, w2 = w * w;
        int bstX = vx, bstY = vy;
        double bstV = inf;

        for (int dx=0; dx<=10; ++dx) {
            for (int dy=0; dy<=dx; ++dy) {
                for (int signx=-1; signx<=1; signx+=2) {
                    vx = x + signx * dx;
                    for (int signy=-1; signy<=1; signy+=2) {
                        vy = y + signy * dy;
                        if (posSet.count(make_pair(vx, vy)) == 0) {
                            double tmp = fabs((vx-ux)*(vx-ux) + (vy-uy)*(vy-uy) - w2);
                            if (tmp < bstV) {
                                bstV = tmp;
                                bstX = vx;
                                bstY = vy;
                            }
                        }
                    }
                }
            }
        }

        vx = bstX;
        vy = bstY;
    }

    double calcRatio(int v, int vx, int vy) {
        const int sz = g[v].size();
        int u, w, ux, uy;
        double tmp, mn = inf, mx = -inf;

        for (int i=0; i<sz; ++i) {
            u = g[v][i].first;
            w = g[v][i].second;
            if (visitVer[u]) {
                ux = pos[u].first; 
                uy = pos[u].second;
                tmp = sqrt((ux-vx)*(ux-vx) + (uy-vy)*(uy-vy));
                tmp = tmp / w;
                mn = min(mn, tmp);
                mx = max(mx, tmp);
            }
        }

        double ret = mn / mx;
        return ret;
    }

    void setVertexPosition(int u, int v, int w) {
        int ux = pos[u].first, uy = pos[u].second, w2 = w * w;
        int bstX, bstY;
        double bstRatio = -inf;

        for (int dx=0; dx*dx<=w2; ++dx) {
            int dy2 = w2 - dx * dx;
            int dy = sqrt((double) dy2);
            for (int signx=-1; signx<=1; signx+=2) {
                int x = ux + signx * dx;
                for (int signy=-1; signy<=1; signy+=2) {
                    int y = uy + signy * dy;
                    getAvaliablePos(ux, uy, x, y, w);
                    double ratio = calcRatio(v, x, y);
                    if (ratio > bstRatio) {
                        bstX = x;
                        bstY = y;
                        bstRatio = ratio;
                    }
                }
            }
        }

        visitVer[v] = true;
        pos[v].first = bstX;
        pos[v].second = bstY;
        posSet.insert(make_pair(bstX, bstY));
    }

    void greedy(const vector<int>& edges) {
        const int sz = edges.size();
        int u, v, w;

        for (int i=0; i<sz; i+=3) {
            u = edges[i];
            v = edges[i+1];
            w = edges[i+2];
            ve.push_back(edge_t(u, v, w));
            g[u].push_back(make_pair(v, w));
            g[v].push_back(make_pair(u, w));
        }
        sort(ve.begin(), ve.end());
        vector<int> Q[2];

        for (int i=ve.size()-1; i>=0; --i) {
            u = ve[i].u;
            v = ve[i].v;
            w = ve[i].w;
            if (i+1 == ve.size()) {
                visitVer[u] = true;
                pos[u].first = pos[u].second = 350;  
                posSet.insert(pos[u]);
            }
            if (visitVer[u] && visitVer[v]) continue;
            if (!visitVer[u] && !visitVer[v]) {
                Q[0].push_back(i);
                continue;
            }

            if (!visitVer[u]) {
                swap(u, v);
            }

            setVertexPosition(u, v, w);
        }

        int p = 0, q = 1;

        while (!Q[p].empty()) {
            Q[q].clear();
            const int sz = Q[p].size();
            for (int j=0; j<sz; ++j) {
                int i = Q[p][j];
                u = ve[i].u;
                v = ve[i].v;
                w = ve[i].w;
                if (visitVer[u] && visitVer[v]) continue;
                if (!visitVer[u] && !visitVer[v]) {
                    Q[q].push_back(i);
                    continue;
                }

                if (!visitVer[u]) {
                    swap(u, v);
                }

                setVertexPosition(u, v, w);
            }

            swap(p, q);
        }
    }

    void transfer() {
        int mny = INT_MAX, mnx = INT_MAX;

        for (int i=0; i<N; ++i) {
            mnx = min(mnx, pos[i].first);
            mny = min(mny, pos[i].second);
        }
        for (int i=0; i<N; ++i) {
            pos[i].first -= mnx;
            pos[i].second -= mny;
        }

        int mxx = INT_MIN, mxy = INT_MIN;

        for (int i=0; i<N; ++i) {
            mxx = max(mxx, pos[i].first);
            mxy = max(mxy, pos[i].second);
        }

        posSet.clear();
        for (int i=0; i<N; ++i) {
            pos[i].first = 700.0 * pos[i].first / mxx;
            pos[i].second = 700.0 * pos[i].second / mxy;
            getAvaliablePos(pos[i].first, pos[i].second);
            posSet.insert(pos[i]);
        }
    }

    bool judge(int x) {
        return x>=0 && x<=700;
    }

    bool judge(int x, int y) {
        return judge(x) && judge(y);
    }

public:
    vector<int> plot(int N, const vector<int>& edges) {
        init(N);
        vector<int> ret;
        
        greedy(edges);
        transfer();

        for (int i=0; i<N; ++i) {
            ret.push_back(pos[i].first);
            assert(judge(*ret.rbegin()));
            ret.push_back(pos[i].second);
            assert(judge(*ret.rbegin()));
        }

        return ret;
    }
};
// -------8<------- end of solution submitted to the website -------8<-------
#include "monitor.h"


int main(int argc, char **argv) {
    GraphDrawing gd;
    int N;
    int E;
    program_t begProg, endProg;

    if (argc > 1) 
        freopen(argv[1], "r", stdin);
    if (argc > 2)
        freopen(argv[2], "w", stdout);

    scanf("%d", &N);
    scanf("%d", &E);
    vector<int> edges(E, 0);
    for (int i=0; i<E; ++i) {
        scanf("%d", &edges[i]);
    }
    
    save_time(begProg);
    vector<int> ret = gd.plot(N, edges);
    save_time(endProg);

    assert(ret.size() == N*2);
    printf("%d\n", ret.size());
    for (int i=0; i<N; ++i)
        printf("%d\n%d\n", ret[2*i], ret[2*i+1]);
    

    // double usedTime = calc_time(begProg, endProg);
    // printf("time = %.3lfs\n", usedTime);

    fflush(stdout);

    return 0;
}
