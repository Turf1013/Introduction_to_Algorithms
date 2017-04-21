// C++11
#include <bits/stdc++.h>
using namespace std;

// #define LOCAL_DEBUG
typedef pair<int,int> pii;

struct node_t {
    double w;
    int x, y;

    node_t(double w=0., int x=0, int y=0):
        w(w), x(x), y(y) {}

    bool operator< (const node_t& o) const {
        return w < o.w;
    }
};

const int maxn = 1015;
const int maxm = 701;
const double eps = 1e-7;
int degs[maxn];
bool visit[maxn];
bool visitPos[maxm][maxm];
int g[maxn][maxn], mark[maxn][maxn], markCnt = 0;
int w[maxn][maxn], w2[maxn][maxn];
pii best[maxn], cur[maxn];
int gsz[maxn];
double sx, sxx;
double sy, syy;
double sl, sll;
double sx2, sxx2;
double sy2, syy2;
double sl2, sll2;

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

class GraphDrawing {
private:
    typedef set<pii> degSet;
    int N;
    int sx, sy, sxx, syy;

    double calcResult(const pii* positions, const vector<int>& edges) {
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
        return x>=0 && x<maxm;
    }

    bool judge(int x, int y) {
        return x>=0 && x<maxm && y>=0 && y<maxm;
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

		memset(visit, false, sizeof(visit));
		memset(visitPos, false, sizeof(visitPos));
    }

    vector<int> toReturn(const pii *vp) {
        vector<int> ret;

        #ifdef LOCAL_DEBUG
        set<pii> st;
        assert(vp.size() == N);
        #endif
        for (int i=0; i<N; ++i) {
            pii p = vp[i];
		#ifdef LOCAL_DEBUG
			assert(st.count(p) == 0);
            st.insert(p);
        #endif
            ret.push_back(p.first);
            ret.push_back(p.second);
        }

        return ret;
    }

    void init(degSet& st) {
        memcpy(degs, gsz, sizeof(gsz));
        memset(visit, false, sizeof(visit));

		st.clear();
		for (int i=0; i<N; ++i) {
			st.insert(make_pair(degs[i], i));
		}
    }

	void sampleOneEdge(int u, int v, int l, pii* vp, degSet& st) {
		double sqrt2 = sqrt(2.0);
		double delta = (l / 2.0) / sqrt2;
		int x1, x2, y1, y2;
		double bstV = 1e20;
		pii bstu, bstv;

		for (int dx1=-1; dx1<=1; ++dx1) {
			x1 = 350.0 - delta + dx1;
			for (int dy1=-1; dy1<=1; ++dy1) {
				y1 = 350.0 + delta + dy1;

				for (int dx2=-1; dx2<=1; ++dx2) {
					x2 = 350.0 + delta + dx2;

					for (int dy2=-1; dy2<=1; ++dy2) {
						y2 = 350.0 - delta + dy2;

						double curl = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
						double tmp = fabs(curl - l);
						if (dcmp(tmp-bstV) < 0) {
							bstV = tmp;
							bstu = make_pair(x1, y1);
							bstv = make_pair(x2, y2);
						}
					}
				}
			}
		}

		#ifdef LOCAL_DEBUG
			assert(bstV < 1e20);
		#endif

		updateVertex(u, bstu.first, bstu.second, vp, st);
		updateVertex(v, bstv.first, bstv.second, vp, st);
	}

	void sampleOneEdge(pii* vp, const vector<int>& edges, degSet& st) {
		const int sz = edges.size();
		int v = -1, c = 0;

		for (int i=2; i<sz; i+=3) {
			if (v==-1 || edges[i]>edges[v]) {
				v = i;
				c = 1;
			} else if (edges[i] == edges[v]) {
				++c;
			}
		}

		int idx = rand() % c + 1;

		for (int i=2; i<sz; i+=3) {
			if (edges[i]==edges[v] && --idx==0) {
				sampleOneEdge(edges[i-2], edges[i-1], edges[i], vp, st);
				return ;
			}
		}

		#ifdef LOCAL_DEBUG
			assert(false);
		#endif
	}

	void calcFitPosition(const int u, int bx, int by, pii* vp) {
		int x, y;

		for (int dx=0; dx<maxm; ++dx) {
			for (int dy=0; dy<=dx; ++dy) {
				for (int sx=-1; sx<=1; sx+=2) {
					x = (sx==-1) ? (bx-dx) : (bx+dx);
					if (!judge(x)) continue;
					for (int sy=-1; sy<=1; sy+=2) {
						y = (sy==-1) ? (by-dy) : (by+dy);
						if (!judge(y)) continue;

						if (!visitPos[x][y]) {
							vp[u] = make_pair(x, y);
							visitPos[x][y] = true;
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

    void updateVertex(const int u, int bx, int by, pii* vp, degSet& st) {
        #ifdef LOCAL_DEBUG
        assert(u>=0 && u<vp.size());
        //printf("u = %d\n", u);
        #endif

		// calculate the position
		calcFitPosition(u, bx, by, vp);
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
    }

    void initParameter(int u, const pii* vp, vector<int>& neighbours) {
        int v;
        sx = sxx = 0;
        sy = syy = 0;
        sl = sll = 0;
        sx2 = sxx2 = 0;
        sy2 = syy2 = 0;
        sl2 = sll2 = 0;

        for (int i=0; i<gsz[u]; ++i) {
            v = g[u][i];
            if (!visit[v])
                continue;
            neighbours.push_back(i);

            sx += vp[v].first;
            sy += vp[v].second;
            sxx += vp[v].first * vp[v].first;
            syy += vp[v].second * vp[v].second;
            sl += w[u][i];
            sll += w2[u][i];

            double ll =  w2[u][i];
            sx2 += vp[v].first / ll;
            sxx2 += vp[v].first * vp[v].first / ll;
            sy2 += vp[v].second / ll;
            syy2 += vp[v].second * vp[v].second / ll;
            sl2 += 1.0 / w[u][i];
            sll2 += 1.0 / ll;
        }
    }

    /**
        \function:  using drawn vertex to calculate the position of current vertex
    */
    void calcPosition(const int u, int& bx, int& by, const pii* vp, const vector<int>& edges) {
        vector<int> neighbours;
        initParameter(u, vp, neighbours);
        int n = neighbours.size();
        int x, y;
        int bstX = -1, bstY = -1;
        // int sa = sx*2, saa = sxx;
        // int sb = sy*2, sbb = syy;
        // int sc = sl, scc = sll;
        double sa = 2.0 * sx2, sb = 2.0 * sy2;
        double saa = sxx2, sbb = syy2;
        double scc = n * 1.0;
        node_t nd;
        vector<node_t> vtmp;

        ++markCnt;
        for (x=0; x<maxn; ++x) {
        // for (x=0; x<15; ++x) {
            // int nxx = n * x * x;
            // double A = n;
            // double B = -sb;
            // double C = saa + sbb - scc + nxx - sa * x;
            double A = sll2;
            double B = -sb;
            double C = x * x * sll2 - sa * x + saa + sbb - scc;


            // solve the equation Ax^2 + Bx + C = 0
            double delta = B * B - 4.0 * A * C;
            if (dcmp(delta) >= 0) {
                double sqrtDelta = sqrt(delta);
                for (int dy=-1; dy<=1; dy+=2) {
                    double tmpy = (-B + dy*sqrtDelta) / (A * 2.0);
                    for (int d=-2; d<=2; ++d) {
                        y = tmpy + d;
                        if (judge(y)) {
                            double tmp = fabs(A*y*y + B*y + C);
                            nd.w = tmp;
                            nd.x = x;
                            nd.y = y;
                            if (mark[x][y] != markCnt) {
                                mark[x][y] = markCnt;
                                vtmp.push_back(nd);
                            }
                            // if (tmp < bestVal) {
                                // bestVal = tmp;
                                // bstX = x;
                                // bstY = y;
                            // }
                        }
                    }
                }
            }

            // Via deviation to detec the bestVal
            double peakY = -B / A;
            double peakV = A*peakY*peakY + B*peakY + C;
            double V0 = C;
            double V700 = A*(maxn-1)*(maxn-1) + B*(maxn-1) + C;

            if (dcmp(peakY) < 0) {
                #ifdef LOCAL_DEBUG
                assert(dcmp(V0-V700) <= 0);
                #endif
                if (dcmp(V0) >= 0) {
                        for (int d=0; d<=1; ++d) {
                            y = d;
                            if (judge(y)) {
                                double tmp = fabs(A*y*y + B*y + C);
                                nd.w = tmp;
                                nd.x = x;
                                nd.y = y;
                                if (mark[x][y] != markCnt) {
                                    mark[x][y] = markCnt;
                                    vtmp.push_back(nd);
                                }
                                // if (tmp < bestVal) {
                                    // bestVal = tmp;
                                    // bstX = x;
                                    // bstY = y;
                                // }
                            }
                        }
                }
                if (dcmp(V700) <= 0) {
                    for (int d=-1; d<=0; ++d) {
                        y = maxn - 1 - d;
                        if (judge(y)) {
                            double tmp = fabs(A*y*y + B*y + C);
                            nd.w = tmp;
                            nd.x = x;
                            nd.y = y;
                            if (mark[x][y] != markCnt) {
                                mark[x][y] = markCnt;
                                vtmp.push_back(nd);
                            }
                            // if (tmp < bestVal) {
                                // bestVal = tmp;
                                // bstX = x;
                                // bstY = y;
                            // }
                        }
                    }
                }
            } else if (dcmp(peakY-maxn+1) >= 0) {
                #ifdef LOCAL_DEBUG
                assert(dcmp(V0-V700) >= 0);
                #endif
                if (dcmp(V0) <= 0) {
                        for (int d=0; d<=1; ++d) {
                            y = d;
                            if (judge(y)) {
                                double tmp = fabs(A*y*y + B*y + C);
                                nd.w = tmp;
                                nd.x = x;
                                nd.y = y;
                                if (mark[x][y] != markCnt) {
                                    mark[x][y] = markCnt;
                                    vtmp.push_back(nd);
                                }
                                // if (tmp < bestVal) {
                                    // bestVal = tmp;
                                    // bstX = x;
                                    // bstY = y;
                                // }
                            }
                        }
                }
                if (dcmp(V700) >= 0) {
                    for (int d=-1; d<=0; ++d) {
                        y = maxn - 1 - d;
                        if (judge(y)) {
                            double tmp = fabs(A*y*y + B*y + C);
                            nd.w = tmp;
                            nd.x = x;
                            nd.y = y;
                            if (mark[x][y] != markCnt) {
                                mark[x][y] = markCnt;
                                vtmp.push_back(nd);
                            }
                            // if (tmp < bestVal) {
                                // bestVal = tmp;
                                // bstX = x;
                                // bstY = y;
                            // }
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
                    for (int d=-1; d<=1; ++d) {
                        y = peakY + d;
                        if (judge(y)) {
                            double tmp = fabs(A*y*y + B*y + C);
                            nd.w = tmp;
                            nd.x = x;
                            nd.y = y;
                            if (mark[x][y] != markCnt) {
                                mark[x][y] = markCnt;
                                vtmp.push_back(nd);
                            }
                            // if (tmp < bestVal) {
                                // bestVal = tmp;
                                // bstX = x;
                                // bstY = y;
                            // }
                        }
                    }
                } else {
                    if (dcmp(V0) <= 0) {
                        for (int d=0; d<=1; ++d) {
                            y = d;
                            if (judge(y)) {
                                double tmp = fabs(A*y*y + B*y + C);
                                nd.w = tmp;
                                nd.x = x;
                                nd.y = y;
                                if (mark[x][y] != markCnt) {
                                    mark[x][y] = markCnt;
                                    vtmp.push_back(nd);
                                }
                                // if (tmp < bestVal) {
                                    // bestVal = tmp;
                                    // bstX = x;
                                    // bstY = y;
                                // }
                            }
                        }
                    }
                    if (dcmp(V700) <= 0) {
                        for (int d=-1; d<=0; ++d) {
                            y = maxn - 1 - d;
                            if (judge(y)) {
                                double tmp = fabs(A*y*y + B*y + C);
                                nd.w = tmp;
                                nd.x = x;
                                nd.y = y;
                                if (mark[x][y] != markCnt) {
                                    mark[x][y] = markCnt;
                                    vtmp.push_back(nd);
                                }
                                // if (tmp < bestVal) {
                                    // bestVal = tmp;
                                    // bstX = x;
                                    // bstY = y;
                                // }
                            }
                        }
                    }
                }
            }
        }

        int sz = vtmp.size();
        int threshSz = 40;
        sz = min(sz, threshSz);
        double bestVal = -1e20;

        // #ifdef LOCAL_DEBUG
        // printf("sz = %d, threshSz = %d\n", sz, threshSz);
        // fflush(stdout);
        // #endif
        nth_element(vtmp.begin(), vtmp.begin()+sz, vtmp.end());

        const int neighboursSz = neighbours.size();

        for (int i=0; i<sz; ++i) {
            x = vtmp[i].x, y = vtmp[i].y;
            double tmp = 0, mn = 1e20, mx = -1e20;
            for (int j=0; j<neighboursSz; ++j) {
                int idx = neighbours[j], v = g[u][idx];
                double xx = vp[v].first, yy = vp[v].second;
                double l0 = (x-xx)*(x-xx) + (y-yy)*(y-yy);
                l0 /= (w[u][idx] * w[u][idx]);
                mn = min(mn, l0);
                mx = max(mx, l0);
            }
            tmp = mn / mx;
            if (tmp > bestVal) {
                bestVal = tmp;
                bstX = x;
                bstY = y;
            }
        }

        bx = bstX;
        by = bstY;
    }

    void getVertex(pii* vp, const vector<int>& edges) {
        degSet vst;
        int u;
		int bx, by;
        pii p;

        /**
            \step 1: initialize degrees and visit
        */
        init(vst);     //init(edges);

        /**
            \step 2: first the most freqeunt vertex as the begin vertex
        */
        sampleOneEdge(vp, edges, vst);

        /**
            \step 3: iterate all the other vertex using the same strategy
        */
        for (int i=3; i<=N; ++i) {
            u = vst.begin()->second;
            /**
                \step 4: calculate the position of current vertex
            */
            calcPosition(u, bx, by, vp, edges);
            updateVertex(u, bx, by, vp, vst);
        }
    }


 public:
    static const int maxn = 701;

    vector<int> plot(int N, const vector<int>& edges) {
        this->N = N;

		initEdge(edges);
		getVertex(best, edges);

        return toReturn(best);
    }
};
// -------8<------- end of solution submitted to the website -------8<-------
#ifdef AT_LINUX
#include "monitor.h"
#endif

#define DEBUG

void calcRatio(const vector<int>& res, const vector<int>& edges) {
    double ratio, mn = 1e20, mx = -1e20;
    const int sz = edges.size();

    for (int i=0; i<sz; i+=3) {
        int u = edges[i], v = edges[i+1];
        pii pu = make_pair(res[u*2], res[u*2+1]);
        pii pv = make_pair(res[v*2], res[v*2+1]);
        ratio = Length(pu, pv) / edges[i+2];
        mn = min(mn, ratio);
        mx = max(mx, ratio);
    }

    printf("%.6lf\n", mn/mx*1000000);
}

int main(int argc, char **argv) {
    GraphDrawing gd;
    int N;
    int E;
	#ifdef AT_LINUX
    program_t begProg, endProg;
	#endif

    // if (argc > 1)
    //     freopen(argv[1], "r", stdin);
    // else
    // 	freopen("data.in", "r", stdin);
    // if (argc > 2)
    //     freopen(argv[2], "w", stdout);
    // else
    // 	freopen("data.out", "w", stdout);

    scanf("%d", &N);
    scanf("%d", &E);
    vector<int> edges(E, 0);
    for (int i=0; i<E; ++i) {
        scanf("%d", &edges[i]);
    }

	#ifdef AT_LINUX
    save_time(begProg);
	#endif
    vector<int> ret = gd.plot(N, edges);
	#ifdef AT_LINUX
    save_time(endProg);
	#endif

    #ifdef LOCA_DEBUG
    assert(ret.size() == N*2);
	#endif

    printf("%d\n", ret.size());
    for (int i=0; i<N; ++i)
        printf("%d\n%d\n", ret[2*i], ret[2*i+1]);


    #ifdef DEBUG
		#ifdef AT_LINUX
			double usedTime = calc_time(begProg, endProg);
		#else
			double usedTime = clock() / 1000.0;
		#endif
    printf("time = %.3lfs\n", usedTime);
    calcRatio(ret, edges);
    #endif

    fflush(stdout);

    return 0;
}
