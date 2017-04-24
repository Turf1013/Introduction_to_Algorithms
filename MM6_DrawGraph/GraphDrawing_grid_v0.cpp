// C++11
#include <bits/stdc++.h>
using namespace std;

#define LOCAL_DEBUG

struct edge_t {
    int u, v, w;

    edge_t(int u=0, int v=0, int w=0):
        u(u), v(v), w(w) {}

    bool operator<(const edge_t& o) const {
        return w < o.w;
    }
};

typedef pair<int,int> pii;
typedef set<pii, greater<pii> > degSet;
const double inf = 1e20;
const int maxn = 1005;
const int glen = 35;
const int maxm = 700;
const int gnum = maxm / glen - 1;
pii pos[maxn];
set<pii> posSet;
bool visitVer[maxn];
bool visitPos[maxm+1][maxm+1];
int degs[maxn];
int g[maxn][maxn], V[maxn];
int cgrid[maxm/glen+1][maxm/glen+1];
vector<int> E[maxn];
vector<int> vdis;
vector<vector<pii> > vdir;

class GraphDrawing {
public:
    int N;

    int getDisId(int x) {
        int idx = distance(vdis.begin(), upper_bound(vdis.begin(), vdis.end(), x));
        return idx==0 ? idx : idx-1;
    }

    void init(int n) {
        N = n;
        posSet.clear();
        memset(degs, 0, sizeof(degs));
        memset(visitVer, false, sizeof(visitVer));
        memset(visitPos, false, sizeof(visitPos));
        for (int i=0; i<n; ++i) E[i].clear();

        for (int i=0; i<=gnum; ++i) {
            for (int j=0; j<=gnum; ++j) {
                int r = i * i + j * j;
                vdis.push_back(r);
            }
        }
        sort(vdis.begin(), vdis.end());
        vdis.erase(unique(vdis.begin(), vdis.end()), vdis.end());
        // #ifdef LOCAL_DEBUG
        // for (int i=0; i<vdis.size(); ++i)
        //     printf("%d ", vdis[i]);
        // puts("");
        // #endif

        for (int i=0; i<vdis.size(); ++i)
            vdir.push_back(vector<pii>());

        for (int i=0; i<=gnum; ++i) {
            for (int j=0; j<=gnum; ++j) {
                int idx = getDisId(i*i + j*j);
                vdir[idx].push_back(make_pair(i, j));
            }
        }
    }

    void initEdge(const vector<int>& edges) {
        const int sz = edges.size();
        int u, v, w;

        for (int i=0; i<sz; i+=3) {
            u = edges[i];
            v = edges[i+1];
            w = edges[i+2];
            g[u][v] = g[v][u] = w;
            E[u].push_back(v);
            E[v].push_back(u);
            ++degs[u];
            ++degs[v];
        }
    }

    void locateVertex(int u) {
        int v, szv = 0;
        const int sz = E[u].size();
        int bstx = -1, bsty = -1, c = 0;

        memset(cgrid, 0, sizeof(cgrid));
        for (int i=0; i<sz; ++i) {
            v = E[u][i];
            if (!visitVer[v])
                continue;
            V[szv++] = v;

            int idx = getDisId((g[u][v]/glen)*(g[u][v]/glen));
            int vdirSz = vdir[idx].size();
            int vgx = pos[v].first / glen, vgy = pos[v].second / glen;
            int ugx, ugy;

            // choose best grid
            for (int j=0; j<vdirSz; ++j) {
                int dx = vdir[idx][j].first, dy = vdir[idx][j].second;
                for (int signx=-1; signx<=1; signx+=2) {
                    ugx = vgx + (signx==-1 ? -dx:dx);
                    if (!judgeg(ugx)) continue;
                    for (int signy=-1; signy<=1; signy+=2) {
                        ugy = vgy + (signy==-1 ? -dy:dy);
                        if (!judgeg(ugy)) continue;

                        if (++cgrid[ugx][ugy] > c) {
                            c = cgrid[ugx][ugy];
                            bstx = ugx;
                            bsty = ugy;
                        }
                    }
                }
            }
        }    

        #ifdef LOCAL_DEBUG
        if (c == 0) {
            for (int i=0; i<sz; ++i) {
                v = E[u][i];
                if (!visitVer[v])
                    continue;
                V[szv++] = v;

                int idx = getDisId((g[u][v]/glen)*(g[u][v]/glen));
                int vdirSz = vdir[idx].size();
                int vgx = pos[v].first / glen, vgy = pos[v].second / glen;
                int ugx, ugy;

                // choose best grid
                for (int j=0; j<vdirSz; ++j) {
                    int dx = vdir[idx][j].first, dy = vdir[idx][j].second;
                    for (int signx=-1; signx<=1; signx+=2) {
                        ugx = vgx + (signx==-1 ? -dx:dx);
                        for (int signy=-1; signy<=1; signy+=2) {
                            ugy = vgy + (signy==-1 ? -dy:dy);
                            if (!judgeg(ugx) && !judgeg(ugy)) continue;

                            ugx = max(ugx, 0);
                            ugx = min(ugx, gnum);
                            ugy = max(ugy, 0);
                            ugy = min(ugy, gnum);

                            if (++cgrid[ugx][ugy] > c) {
                                c = cgrid[ugx][ugy];
                                bstx = ugx;
                                bsty = ugy;
                            }
                        }
                    }
                }
            }    

            if (c == 0) {
                bstx = rand() % gnum;
                bsty = rand() % gnum;
            }
        }
        #endif

        // choose best position
        double bstRatio = -inf;
        int bstX = -1, bstY = -1;

        for (int i=0; i<glen; ++i) {
            for (int j=0; j<glen; ++j) {
                int x = bstx * glen + i;
                int y = bsty * glen + j;
                double mn = inf, mx = -inf, ratio;

                getAvaliablePos(x, y);

                for (int k=0; k<szv; ++k) {
                    v = V[k];
                    ratio = sqrt(1.0*(pos[v].first-x)*(pos[v].first-x) + 1.0*(pos[v].second-y)*(pos[v].second-y)) / g[u][v];
                    mn = min(mn, ratio);
                    mx = max(mx, ratio);
                }

                ratio = mn / mx;
                if (ratio > bstRatio) {
                    bstRatio = ratio;
                    bstX = x;
                    bstY = y;
                }
            }
        }

        #ifdef LOCAL_DEBUG
        assert(judge(bstX, bstY));
        #endif

        pos[u].first = bstX;
        pos[u].second = bstY;
        visitVer[u] = true;
        posSet.insert(pos[u]);
    }

    void updateVertex(int u, degSet& st) {
        const int sz = E[u].size();
        int v;

        st.erase(make_pair(degs[u], u));
        for (int i=0; i<sz; ++i) {
            v = E[u][i];
            if (visitVer[v]) continue;
            st.erase(make_pair(degs[v], v));
            --degs[v];
            st.insert(make_pair(degs[v], v));
        }
    }

    void locate(const vector<int>& edges) {
        initEdge(edges);
        degSet st;

        int u = 0;

        for (int i=0; i<N; ++i) {
            if (degs[i] > degs[u])
                u = i;
        }
        pos[u].first = pos[u].second = glen/2;
        visitVer[u] = true;
        posSet.insert(pos[u]);
        updateVertex(u, st);

        for (int i=1; i<N; ++i) {
            int u = st.begin()->second;

            locateVertex(u);
            updateVertex(u, st);
        }
    }

    void getAvaliablePos(int& vx, int& vy) {
        int x = vx, y = vy;

        for (int ds=0; ds<maxm; ++ds) {
            for (int dx=0; dx<=ds; ++dx) {
                int dy = ds - dx;
                for (int signx=-1; signx<=1; signx+=2) {
                    vx = x + signx * dx;
                    if (!judge(vx)) continue;
                    for (int signy=-1; signy<=1; signy+=2) {
                        vy = y + signy * dy;
                        if (!judge(vy)) continue;
                        if (posSet.count(make_pair(vx, vy)) == 0) {
                            return ;
                        }
                    }
                }
            }
        }

        #ifdef LOCAL_DEBUG
        assert(false);
        #endif
    }

    bool judgeg(int x) {
        return x>=0 && x<=gnum;
    }

    bool judgeg(int x, int y) {
        return judgeg(x) && judgeg(y);
    }

    bool judge(int x) {
        return x>=0 && x<=maxm;
    }

    bool judge(int x, int y) {
        return judge(x) && judge(y);
    }

    bool lastJudge() {
        set<pii> st;

        for (int i=0; i<N; ++i) {
            if (st.count(pos[i])) {
                puts("multiple vertex");
                return false;
            }
            if (!visitVer[i]) {
                puts("unvisit vertedx");
                return false;
            }
            st.insert(pos[i]);
        }

        return true;
    }

public:
    vector<int> plot(int N, const vector<int>& edges) {
        init(N);
        vector<int> ret;
        

        locate(edges);
        #ifdef LOCAL_DEBUG
        assert(lastJudge());
        #endif

        for (int i=0; i<N; ++i) {
            ret.push_back(pos[i].first);
            ret.push_back(pos[i].second);
            #ifdef LOCAL_DEBUG
            assert(judge(ret[ret.size()-2]));
            assert(judge(ret[ret.size()-1]));
            #endif
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
