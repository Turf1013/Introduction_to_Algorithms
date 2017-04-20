#include <bits/stdc++.h>
using namespace std;

// #define LOCAL_DEBUG
#define RANDOM_DATA_IN

typedef pair<int,int> pii;
const int maxn = 701;
const double eps = 1e-7;
int n;
double sx, sxx;
double sy, syy;
double sl, sll;
double sx2, sxx2;
double sy2, syy2;
double sl2, sll2;
int bx, by;
vector<int> vx, vy, vl;
int mark[maxn][maxn], markCnt = 0;

int dcmp(double x) {
    if (fabs(x) < eps)
        return 0;
    return x>0 ? 1:-1;
}

double Length(const pii& a, const pii& b) {
    return sqrt((a.first-b.first)*(a.first-b.first) + (a.second-b.second)*(a.second-b.second));
}

bool judge(int x) {
    return x>=0 && x<maxn;
}

bool judge(int x, int y) {
    return x>=0 && x<maxn && y>=0 && y<maxn;
}

int cornerCaseN = 0, totCaseN;
void printResult(int bstx, int bsty) {
    pii bp(bstx, bsty);
    double mn = 1e20, mx = -1e20;

    printf("shouldx = %d, shouldy = %d\n", bx, by);
    printf("calcx = %d, calcy = %d\n", bstx, bsty);

    for (int i=0; i<n; ++i) {
        double tmp = Length(bp, make_pair(vx[i], vy[i]));
		#ifdef LOCAL_DEBUG
        printf("val = %.3lf, should = %d\n", tmp, vl[i]);
		#endif
        tmp /= vl[i];
        mn = min(mn, tmp);
        mx = max(mx, tmp);
    }

    printf("%.3lf\n", mn/mx);

	if (mn/mx <= 0.5) {
		puts("corner case.");
		++cornerCaseN;
		// printf("%d\n", n);
		// for (int i=0; i<n; ++i)
			// printf("%d %d\n", vx[i], vy[i]);
		// printf("%d %d\n", bx, by);
	}
	++totCaseN;
}

struct node_t {
	double w;
	int x, y;

	node_t(double w=0., int x=0, int y=0):
		w(w), x(x), y(y) {}

	bool operator< (const node_t& o) const {
		return w < o.w;
	}
};

void gao() {
	int x, y;
    int bstX = -1, bstY = -1;
    double bestVal = 1e20;
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
                    for (int d=0; d<=5; ++d) {
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
                for (int d=-5; d<=0; ++d) {
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
                    for (int d=0; d<=5; ++d) {
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
                for (int d=-5; d<=0; ++d) {
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
                for (int d=-2; d<=2; ++d) {
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
                    for (int d=0; d<=5; ++d) {
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
                    for (int d=-5; d<=0; ++d) {
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
	int threshSz = 100;
	sz = min(sz, threshSz);

	// #ifdef LOCAL_DEBUG
	// printf("sz = %d, threshSz = %d\n", sz, threshSz);
	// fflush(stdout);
	// #endif
	nth_element(vtmp.begin(), vtmp.begin()+sz, vtmp.end());

	for (int i=0; i<sz; ++i) {
		x = vtmp[i].x, y = vtmp[i].y;
		double tmp = 0;
		for (int j=0; j<n; ++j) {
			double xx = vx[j], yy = vy[j];
			double l0 = (x-xx)*(x-xx) + (y-yy)*(y-yy);
			l0 /= (vl[j] * vl[j]);
			// double l0 = ((x - vx[j])*(x - vx[j]) + (y-vy[j])*(y-vy[j])) / (vl[j] * vl[j]);
			tmp += fabs(l0 - 1.0);
		}
		if (tmp < bestVal) {
			bestVal = tmp;
			bstX = x;
			bstY = y;
		}
	}

	// #ifdef LOCAL_DEBUG
		// printf("bestVal = %.3lf\n", bestVal);
	// #endif
    printResult(bstX, bstY);
}

void initData(int N=400) {
	pii p;
	set<pii> st;

	vx.clear();
	vy.clear();
	vl.clear();
#ifdef RANDOM_DATA_IN
	n = rand() % N + 201;

	for (int i=0; i<=n; ++i) {
		while (true) {
			p.first = rand() % maxn;
			p.second = rand() % maxn;
			if (st.count(p) == 0) {
				break;
			}
		}
		st.insert(p);
		vx.push_back(p.first);
		vy.push_back(p.second);
	}
#else
	scanf("%d", &n);
	for (int i=0; i<=n; ++i) {
		scanf("%d %d", &p.first, &p.second);
		st.insert(p);
		vx.push_back(p.first);
		vy.push_back(p.second);
	}
#endif

	bx = vx[n] % 10;
	by = vy[n] % 10;
	pii bp(bx, by);
	vx.pop_back();
	vy.pop_back();
	st.clear();

	for (int i=0; i<n; ++i) {
		int l = Length(bp, make_pair(vx[i], vy[i]));
		vl.push_back(l);
	}
}

void initParameter() {
    assert(vx.size()==n && vy.size()==n);

    sx = sxx = 0;
    sy = syy = 0;
    sl = sll = 0;
	sx2 = sxx2 = 0;
    sy2 = syy2 = 0;
    sl2 = sll2 = 0;

    for (int i=0; i<n; ++i) {
        sx += vx[i];
        sy += vy[i];
        sxx += vx[i] * vx[i];
        syy += vy[i] * vy[i];
        sl += vl[i];
        sll += vl[i] * vl[i];

		double ll =  vl[i] * vl[i];
		sx2 += vx[i] / ll;
		sxx2 += vx[i]*vx[i] / ll;
		sy2 += vy[i] / ll;
		syy2 += vy[i]*vy[i] / ll;
		sl2 += 1.0 / vl[i];
		sll2 += 1.0 / ll;
    }
}

void init(int N) {
    initData(N);
    initParameter();
}

int main() {
#ifdef LOCAL_DEBUG
	freopen("data.in", "r", stdin);
	freopen("data.out", "w", stdout);
#else
	freopen("data.out", "w", stdout);
#endif

	int t;
#ifdef RANDOM_DATA_IN
	t = 100;
#else
	scanf("%d", &t);
#endif

	for (int tt=1; tt<=t; ++tt) {
        int n = rand() % 3 + 3;
        init(500);
        gao();
    }
	
	printf("%.2lf%%\n", 100.0*cornerCaseN/t);

	return 0;
}
