// C++11
#include <bits/stdc++.h>
using namespace std;

#define LOCAL_DEBUG
typedef pair<int,int> pii;

const int maxn = 1015;
const double eps = 1e-7;
int degs[maxn];
bool visit[maxn];
int g[maxn][maxn];
int w[maxn][maxn], w2[maxn][maxn];
int gsz[maxn];

class GraphDrawing {
private:
    typedef set<pii, greater<pii> > degSet;
    int N;
    int sx, sy, sxx, syy;

    int dcmp(double x) {
        if (fabs(x) < eps)
            return 0;
        return x>0 ? 1:-1;
    }

    int Length2(const pii& a, const pii& b) {
        return (a.first-b.first)*(a.first-b.first) + (a.second-b.second)*(a.second-b.second);
    }

    double Length(const pii& a, const pii& b) {
        return sqrt((double)((a.first-b.first)*(a.first-b.first) + (a.second-b.second)*(a.second-b.second)));
    }

    double calcResult(const vector<pii>& positions, const vector<int>& edges) {
        #ifdef LOCAL_DEBUG
        assert(positions.size() == N);
        #endif
        double mn = 1.0, mx = 0.0, tmp;
        const int sz = edges.size();

        for (int i=0; i<sz; i+=3) {
            tmp = Length(positions[edges[i]], positions[edges[i+1]]) / edges[i+2];
            mn = min(mn, tmp);
            mx = max(mx, tmp);
        }

        return (mx==0) ? 0.0 : mn/mx;
    }

    bool judge(int x) {
        return x>=0 && x<maxn;
    }

    bool judge(int x, int y) {
        return x>=0 && x<maxn && y>=0 && y<maxn;
    }

    void initEdge(const vector<int>& edges) {
        const int sz = edges.size();
        int u, v;

        memset(gsz, 0, sizeof(gsz));
        for (int i=0; i<sz; i+=3) {
            u = edges[i];
            v = edges[i+1];
            g[u][gsz[u]] = v;
            g[v][gsz[v]] = u;
            w[u][gsz[u]] = edges[i+2];
            w[v][gsz[v]] = edges[i+2];
            ++gsz[u];
            ++gsz[v];
        }

        for (u=0; u<N; ++u) {
            for (int i=0; i<gsz[u]; ++i)
                w2[u][i] = w[u][i] * w[u][i];
        }
    }

    vector<int> toReturn(const vector<pii>& vp) {
        vector<int> ret;
        set<pii> st;

        #ifdef LOCAL_DEBUG
        assert(vp.size() == N*2);
        #endif
        for (int i=0; i<vp; ++i) {
            pii p = vp[i];
            if (st.count(p) > 0) {
                bool flag = false;
                for (int dx=0; dx<maxn; ++dx) {
                    if (judge(x + dx)) {
                        p.fir += dx;
                        for (int dy=0; y<maxn; ++dy) {
                            if (judge(y + dy)) {
                                p.sec += dy;
                                if (st.count(p) > 0) {
                                    flag = true;
                                    break;
                                }
                                p.sec -= dy;
                            }
                            if (judge(y - dy)) {
                                p.sec -= dy;
                                if (st.count(p) > 0) {
                                    flag = true;
                                    break;
                                }
                                p.sec += dy;
                            }   
                        }
                        if (flag) break;
                        p.fir -= dx;
                    }
                    if (judge(x - dx)) {
                        p.fir -= dx;
                        for (int dy=0; y<maxn; ++dy) {
                            if (judge(y + dy)) {
                                p.sec += dy;
                                if (st.count(p) > 0) {
                                    flag = true;
                                    break;
                                }
                                p.sec -= dy;
                            }
                            if (judge(y - dy)) {
                                p.sec -= dy;
                                if (st.count(p) > 0) {
                                    flag = true;
                                    break;
                                }
                                p.sec += dy;
                            }   
                        }
                        if (flag) break;
                        p.fir += dx;
                    }
                }
            }
            st.insert(p);
            ret.push_back(p.fir);
            ret.push_back(p.sec);
        }

        return ret;
    }

    void init() {
        sx = sy = sxx = syy = 0;
        memcpy(degs, gsz, sizeof(gsz));
        memset(visit, false, sizeof(visit));        
    }

    void init(const vector<int>& edges) {
        const int sz = edges.size();
        int u, v;

        sx = sy = sxx = syy = 0;
        memcpy(degs, gsz, sizeof(gsz));
        memset(visit, false, sizeof(visit));
        for (int i=0; i<sz; i+=3) {
            u = edges[i];
            v = edges[i+1];
            ++degs[u];
            ++degs[v];
        }
    }

    void setBeginVertex(int bx, int by, int& u) {
        int mx = -1, c = 0;

        for (int i=0; i<N; ++i) {
            if (deg[i] > mx) {
                mx = deg[i];
                c = 1;
            } else if (deg[i] == mx) {
                ++c;
            }
        }

        int idx = rand() % c;
        for (int i=0; i<N; ++i) {
            if (deg[i]==mx && --c==0) {
                u = i;
                return ;
            }
        }

        #ifdef LOCAL_DEBUG
        assert(false);
        #endif
        u = -1;
    }

    void udapteVertex(const int u, int bx, int by, vector<int>& vp, degSet& st) {
        #ifdef LOCAL_DEBUG
        assert(u>=0 && u<vp.size());
        #endif

        vp[u].first = bx;
        vp[u].second = by;
        visit[u] = true;
        st.erase(make_pair(degs[u], u));

        int v;

        for (int i=0; i<gsz[u]; ++i) {
            v = g[u][i];
            if (!visit[v]) {
                st.erase(make_pair(degs[v], v));
                --degs[v];
                st.insert(make_pair(degs[v], v));
            }
        }

        sx += bx;
        sy += by;
        sxx += bx * bx;
        syy += by * by;
    }

    /**
        \function:  using drawn vertex to calculate the position of current vertex
    */
    void calcPoisiton(const int u, int& bx, int& by, const vector<int>& edges) {
        int sa = sx*2, sa2 = sxx;
        int sb = sy*2, sb2 = syy;
        int sc = 0, v;
        int x, y, n = 0;
        double bestVal = 1e20;
        int bstX = -1, bstY = -1;

        for (int i=0; i<gsz[u]; ++i) {
            v = g[u][i];
            if (visit[v]) {
                sc += w2[u][i];
                ++n;
            }
        }

        for (x=0; x<maxn; ++x) {
            int nx2 = n * x * x;
            double A = n;
            double B = -sb;
            double C = sa2 + sb2 - sc2 + nx2 - sa * x;

            // solve the equation Ax^2 + Bx + C = 0
            double delta = B * B - 4.0 * A * C;
            double sqrtDelta = sqrt(delta);
            for (int dy=-1; dy<=1; dy+=2) {
                double tmpy = (-B + sqrtDelta) / (A * 2.0);
                for (int d=-2; d<=2; ++d) {
                    y = tmpy + d;
                    if (judge(y)) {
                        double tmp = fabs(A*y*y + B*y + C);
                        if (tmp < bestVal) {
                            bestVal = tmp;
                            bstX = x;
                            bstY = y;
                        }
                    }
                }
            }

            // Via deviation to detec the bestVal
            double peakY = -B / (A * 2.0);
            double peakV = A*peakY*peakY + B*peakY + C;
            double V0 = C;
            double V700 = A*(maxn-1)*(maxn-1) + B*(maxn-1) + C;

            if (dcmp(peakY) < 0) {
                #ifdef LOCAL_DEBUG
                assert(dcmp(V0-V700) <= 0);
                #endif
                if (dcmp(V0) >= 0) {
                        for (int d=0; d<=5; ++d) {
                            y = d;
                            if (judge(y)) {
                                double tmp = fabs(A*y*y + B*y + C);
                                if (tmp < bestVal) {
                                    bestVal = tmp;
                                    bstX = x;
                                    bstY = y;
                                }
                            }
                        }
                }
                if (dcmp(V700) <= 0) {
                    for (int d=-5; d<=0; ++d) {
                        y = maxn - 1 - d;
                        if (judge(y)) {
                            double tmp = fabs(A*y*y + B*y + C);
                            if (tmp < bestVal) {
                                bestVal = tmp;
                                bstX = x;
                                bstY = y;
                            }
                        }
                    }
                }
            } else if (dcmp(peakY-maxn+1) > 0) {
                #ifdef LOCAL_DEBUG
                assert(dcmp(V0-V700) >= 0);
                #endif
                if (dcmp(V0) <= 0) {
                        for (int d=0; d<=5; ++d) {
                            y = d;
                            if (judge(y)) {
                                double tmp = fabs(A*y*y + B*y + C);
                                if (tmp < bestVal) {
                                    bestVal = tmp;
                                    bstX = x;
                                    bstY = y;
                                }
                            }
                        }
                }
                if (dcmp(V700) >= 0) {
                    for (int d=-5; d<=0; ++d) {
                        y = maxn - 1 - d;
                        if (judge(y)) {
                            double tmp = fabs(A*y*y + B*y + C);
                            if (tmp < bestVal) {
                                bestVal = tmp;
                                bstX = x;
                                bstY = y;
                            }
                        }
                    }
                }
            } else {
                if (dcmp(peakV) >= 0) {
                    #ifdef LOCAL_DEBUG
                    assert(dcmp(V0) >= 0);
                    assert(dcmp(V700) >= 0);
                    #endif
                    // in this case peakY is the best value
                    for (int d=-2; d<=2; ++d) {
                        y = peakY + d;
                        if (judge(y)) {
                            double tmp = fabs(A*y*y + B*y + C);
                            if (tmp < bestVal) {
                                bestVal = tmp;
                                bstX = x;
                                bstY = y;
                            }
                        }
                    }
                } else {
                    if (dcmp(V0) >= 0) {
                        for (int d=0; d<=5; ++d) {
                            y = d;
                            if (judge(y)) {
                                double tmp = fabs(A*y*y + B*y + C);
                                if (tmp < bestVal) {
                                    bestVal = tmp;
                                    bstX = x;
                                    bstY = y;
                                }
                            }
                        }
                    }
                    if (dcmp(V700) >= 0) {
                        for (int d=-5; d<=0; ++d) {
                            y = maxn - 1 - d;
                            if (judge(y)) {
                                double tmp = fabs(A*y*y + B*y + C);
                                if (tmp < bestVal) {
                                    bestVal = tmp;
                                    bstX = x;
                                    bstY = y;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    void getVertex(int bx, int by, vector<pii>& vp, const vector<int>& edges) {
        degSet vst;
        int u, v;
        pii p;

        /**
            \step 1: initialize degrees and visit
        */
        init();     //init(edges);

        /**
            \step 2: first the most freqeunt vertex as the begin vertex
        */
        setBeginVertex(bx, by, u);
        updateVertex(u, bx, by, vp, vst);

        /**
            \step 3: iterate all the other vertex using the same strategy
        */
        for (int i=1; i<N; ++i) {
            u = vst.begin()->second;
            /**
                \step 4: calculate the position of current vertex
            */
            calcPosition(u, bx, by, edges);
            updateVertex(u, bx, by, vp, vst);
        }
    }


 public:
    static const int maxn = 701;

    vector<int> plot(int N, const vector<int>& edges) {
        this->N = N;
        vector<pii> best(N, make_pair(0,0)), cur(N, make_pair(0,0));
        int bestBx = -1, bestBy = -1;
        double bestRes = 2, curRes;

        initEdge(edges);
        for (int bx=0; bx<maxn; ++bx) {
            for (int by=0; by<maxn; ++by) {
                getVertex(bx, by, cur, edges);
                curRes = calcResult(cur, edges);
                if (bestBx<0 || dcmp(curRes-bestRes)>0) {
                    bestRes = curRes;
                    bestBx = bx;
                    bestBy = by;
                }
            }
        }
        calcResult(best, edges);

        return toReturn(best);
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
    vector<int> edges(3*E, 0);
    for (int i=0; i<3*E; ++i) {
        scanf("%d", &edges[i]);
    }
    
    save_time(begProg);
    vector<int> ret = gd.plot(N, edges);
    save_time(endProg);

    assert(ret.size() == N*2);
    printf("%d\n", N);
    for (int i=0; i<N; ++i)
        printf("%d %d\n", ret[2*i], ret[2*i+1]);
    

    double usedTime = calc_time(begProg, endProg);
    printf("time = %.3lfs\n", usedTime);

    fflush(stdout);

    return 0;
}
