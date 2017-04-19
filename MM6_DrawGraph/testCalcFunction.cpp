#include <bits/stdc++.h>
using namespace std;

#define LOCAL_DEBUG

typedef pair<int,int> pii;
const int maxn = 701;
const double eps = 1e-7;
int n;
int sx, sxx;
int sy, syy;    
int sl, sll;
int bx, by;
vector<int> vx, vy, vl;

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

void printResult(int bstx, int bsty) {
    pii bp(bstx, bsty);
    double mn = 1e20, mx = -1e20;

    printf("shouldx = %d, shouldy = %d\n", bx, by);
    printf("calcx = %d, calcy = %d\n", bstx, bsty);

    for (int i=0; i<n; ++i) {
        double tmp = Length(bp, make_pair(vx[i], vy[i]));
        printf("val = %.3lf, should = %d\n", tmp, vl[i]);
        tmp /= vl[i];
        mn = min(mn, tmp);
        mx = max(mx, tmp);
    }

    printf("%.3lf\n", mn/mx);
}

void gao() {
	int x, y;
	int sa = sx*2, sa2 = sxx;
    int sb = sy*2, sb2 = syy;
    int sc = sl, sc2 = sll;
    int bstX = -1, bstY = -1;
    double bestVal = 1e20;


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

    printResult(bstX, bstY);
}

void initData(int N=400) {
	pii p;
	set<pii> st;

	vx.clear();
	vy.clear();
	vl.clear();
	n = rand() % N + 1;

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
	bx = vx[n];
	by = vy[n];
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

    for (int i=0; i<n; ++i) {
        sx += vx[i];
        sy += vy[i];
        sxx += vx[i] * vx[i];
        syy += vy[i] * vy[i];
        sl += vl[i];
        sll += vl[i] * vl[i];
    }
}

void init(int N) {
    initData(N);
    initParameter();
}

int main() {
	int t = 10;

	for (int tt=1; tt<=t; ++tt) {
        int n = rand() % 5 + 1;
        init(n);
        gao();
    }

	return 0;
}