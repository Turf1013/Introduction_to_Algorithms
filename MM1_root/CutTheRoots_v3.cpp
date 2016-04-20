#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <climits>
#include <cctype>
#include <cassert>
#include <functional>
#include <iterator>
#include <iomanip>
using namespace std;

#define sti				set<int>
#define stpii			set<pair<int, int> >
#define mpii			map<int,int>
#define vi				vector<int>
#define pii				pair<int, int>
#define pdd             pair<double, double>
#define vpii			vector<pair<int,int> >
#define rep(i, a, n) 	for (int i=a;i<n;++i)
#define per(i, a, n) 	for (int i=n-1;i>=a;--i)
#define clr				clear
#define pb 				push_back
#define mp 				make_pair
#define fir				first
#define sec				second
#define all(x) 			(x).begin(),(x).end()
#define SZ(x) 			((int)(x).size())

#define LOG_FILENAME    "makeCuts.log"
#define LOCAL_DEBUG
#define DEBUG
#define pre itmp

typedef long long LL;

const double eps = 1e-7;
const double PI = acos(-1.0);
const int maxp = 106;
const int maxrt = 105115;
int itmp[maxrt], idTb[maxrt], pid[maxrt], son[maxrt];
double dbtmp[maxrt];
double W[maxrt], len[maxrt];
double ltB[maxp];
double sumB[maxp];
bool mark[maxp];
bool dead[maxrt];
bool visit[maxp][maxp];
FILE* logout;
int cNR;

int dcmp(double x) {
    if (fabs(x) < eps)  return 0;
    return x<0 ? -1:1;
}

template <typename T=double>
struct Point_t {
    T x, y;

    Point_t() {}
    Point_t(double x, double y): x(x), y(y) {}

    bool operator== (const Point_t& oth) const {
        return x==oth.x && y==oth.y;
    }

    bool operator!= (const Point_t& oth) const {
        return x!=oth.x || y!=oth.y;
    }

    bool operator< (const Point_t& oth) const {
        return x<oth.x || (x==oth.x && y<oth.y);
    }

    Point_t<T> operator- (const Point_t& oth) const {
        return Point_t<T>(x-oth.x, y-oth.y);
    }

    Point_t<T> operator+ (const Point_t& oth) const {
        return Point_t<T>(x+oth.x, y+oth.y);
    }

    Point_t<T> operator* (T k) const {
        return Point_t<T>(x*k, y*k);
    }

    Point_t<T> operator/ (T k) const {
        return Point_t<T>(x/k, y/k);
    }

    Point_t<int> toIPoint() const {
        return Point_t<int>(int(x), (int)y);
    }

	void print() const {
		printf("x = %.4lf, y = %.4lf\n", (double)x, (double)y);
	}
};

typedef Point_t<double> Point;
typedef Point_t<int> IPoint;
typedef Point Vector;
Point pts[maxrt];

typedef struct Segment {
    double k, b;
	int st;

    Segment() {}
    Segment(double k, double b, int st=0):k(k), b(b), st(st) {}

    int cmp(Point& p) {
    	if (st)
			return dcmp(b-p.x);
		else
			return dcmp(k*p.x+b - p.y);
    }

	int cmp(double x, double y) {
		if (st)
			return dcmp(b-x);
		else
			return dcmp(k*x+b - y);
	}

    bool operator== (const Segment& oth) const {
        return k==oth.k && b==oth.b;
    }

	void print() {
		printf("st = %d, k = %.4lf, b = %.4lf\n", st, k, b);
	}

} Segment;

typedef struct Cut_t {
    IPoint a, b;

    Cut_t() {}
    Cut_t(IPoint a, IPoint b):a(a), b(b) {}

    Segment toSegment() const {
        if (a.x == b.x) {
            return Segment(0, a.x, 1);
        } else {
            double k = ((double)b.y-a.y) / ((double)b.x-a.x);
            double bb = a.y - k*a.x;
            return Segment(k, bb, 0);
        }
    }

	void print() {
		a.print();
		b.print();
	}

} Cut_t;

typedef struct edge_t {
	int v;
	double w;

	edge_t() {}
	edge_t(int v, double w):v(v), w(w) {}

	void print() const {
		printf("v = %d, w = %.4lf\n", v, w);
	}

} edge_t;

typedef struct node_t {
	double b, w;
	int ptId;

	node_t() {}
	node_t(double b, double w, double ptId):
		b(b), w(w), ptId(ptId) {}

	bool operator< (const node_t& oth) const {
		return b < oth.b;
	}

} node_t;

vector<edge_t> E[maxrt];

typedef struct Graph_t {
	vi son;
	vector<int> S;
	Segment seg;
	int vn, rtd, top, ptId;

	Graph_t() {
		vn = 0;
	}

	void init(int ptId, int n) {
		this->ptId = ptId;
		E.reserve(n);
		W.reserve(n);
		son.reserve(n);
		len.reserve(n);
		S.reserve(n);
	}

	inline int getId(int u) {
		if (idTb[u] == -1)
			idTb[u] = vn++;
		return idTb[u];
	}

	inline int getPid(int v) {
		return pid[v];
	}

	void addEdge(int u, int v, double w) {
		int uid = getId(u), vid = getId(v);
		E[uid].pb(edge_t(vid, w));
	}

	double calWeight(int u) {
		return len[u] * son[u] / cNR;
	}

	void refresh(Segment& seg) {
		this->seg = seg;
		top = 0;
		rtd = getPos(0);
		dfs_refresh(0);
		S.resize(top);

		rep(i, 0, top) {
			W[i] = calWeight(S[i]);
			S[i] = getPid(S[i]);
		}

		#ifdef DEBUG
		assert(son[0] > 0);
		#endif
	}

	inline int getPos(int v) {
		return seg.cmp(pts[getPid(v)])<=0 ? 0:1;
	}

	void dfs_refresh(int u) {
		int d = getPos(u);

		son[u] = 0;
		len[u] = 0.;
		if (d != rtd) {
			dead[u] = true;
			return ;
		}

		// S[top++] = getPid(u);
		son[u] = 1;
		S[top++] = u;
		int sz = SZ(E[u]), m = 0;

		rep(i, 0, sz) {
			const int& v = E[u][i].v;
			dfs_refresh(v);
			if (!dead[v]) {
				E[u][m++] = E[u][i];
				son[u] += son[v];
				len[u] += len[v] + E[u][i].w;
			}
		}
		E[u].resize(m);
	}

	void dumpKxy(vector<node_t >& vc, double k) {
		rep(i, 0, top) {
			// int pid = getPid(S[i]);
			const int& pid = S[i];
			double b = pts[pid].y - pts[pid].x * k;
			double w = W[i];
			vc.pb(node_t(b, w, ptId));
		}
	}

	void dumpX(double x, double &w) {
		int d = dcmp(pts[getPid(0)].x - x) <= 0 ? 0 : 1;
		rep(i, 0, top) {
			int d2 = dcmp(pts[S[i]].x - x) <= 0 ? 0 : 1;
			if (d == d2) {
				w += W[i];
			}
		}
	}

	void dumpY(double y, double &w) {
		int d = dcmp(pts[getPid(0)].y - y) <= 0 ? 0 : 1;
		rep(i, 0, top) {
			int d2 = dcmp(pts[S[i]].y - y) <= 0 ? 0 : 1;
			if (d == d2) {
				w += W[i];
			}
		}
	}

} Graph_t;

Graph_t G[maxp];

/**
    \brief Dot
*/
inline double Dot(Point a, Point b) {
    return a.x*b.x + a.y*b.y;
}

/**
    \brief calculate the length^2 between to points
*/
inline double Length2(const Point& a, const Point& b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

/**
    \brief calculate the length between to points
*/
inline double Length(const Point& a, const Point& b) {
    return sqrt( (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) );
}

inline double Length(const Point& a) {
    return sqrt(a.x*a.x + a.y*a.y);
}

/**
    \brief calculate the angle of the point p and (0,0)
*/
inline double angle(const Point& p) {
    return atan2(p.y, p.x);
}

/**
    \brief calculate the angle of 2-vector
*/
inline double Angle(Vector a, Vector b) {
    return acos(Dot(a, b) / Length(a) / Length(b));
}

/**
	\brief calculate the Cross of two vector
*/
inline double Cross(Vector a, Vector b) {
    return a.x*b.y - a.y*b.x;
}

/**
	\brief calculate the intersection point of two lines
*/
inline Point GetLineIntersection(Point P, Vector v, Point Q, Vector w) {
    Vector u = P - Q;
    double t = Cross(w, u) / Cross(v, w);
    return P + v * t;
}

/**
    \brief calculate the distance from point P to Line(A, B).
*/
inline double DistanceToLine(Point P, Point A, Point B) {
    Vector v1 = B - A, v2 = P - A;
    return fabs(Cross(v1, v2)) / Length(v1);
}

/**
    \brief judge segment intersection.
*/
inline bool SegmentIntersection(Point &a1, Point &a2, Point &b1, Point &b2) {
    double c1 = Cross(a2-a1, b1-a1);
    double c2 = Cross(a2-a1, b2-a1);
    double c3 = Cross(b2-b1, a1-b1);
    double c4 = Cross(b2-b1, a2-b1);
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

/**
    \brief judge the point on the segment
*/
inline bool onSegment(Point &p, Point &a1, Point &a2) {
    return dcmp(Cross(a1-p, a2-p))==0 && dcmp(Dot(a1-p, a2-p))==0;
}

/**
	\brief disjoint-set
*/
int find(int x) {
	if (x == pre[x])
		return x;
	return pre[x] = find(pre[x]);
}

vector<vi> group;
vector<Cut_t> ans;
vector<double> kvc;

class CutTheRoots {
public:
	// static const double NEG_INF = -1e16;
	// static const double POS_INF = 1e16;
	// static const double w_incut = 1.0;
	// static const double w_outcut = 0.0;
	// static const double xy_step = 10;
	// static const double alpha_step = 1.0;
	static const double NEG_INF;
	static const double POS_INF;
	static const double w_incut;
	static const double w_outcut;
	static const double xy_step;
	static const double alpha_step;
    int NR, NP, npt;

	/**
		\breif K to choose according the step
	*/
	inline void init_kvc() {
		double alpha;

		for (alpha=0; alpha<90.; alpha+=alpha_step) {
			kvc.pb(tan(alpha*PI/180.0));
		}
		for (alpha=90+alpha_step; alpha<180.; alpha+=alpha_step) {
			kvc.pb(tan(alpha*PI/180.0));
		}
	}

    /**
        \brief dump the data to the logout.
    */
    void dumpInputToLog(int NP, vi& points, vi& roots) {
        fprintf(logout, "%d\n", NP);

        int npoints = SZ(points);
        fprintf(logout, "%d\n", npoints);
        rep(i, 0, npoints) {
            fprintf(logout, "%d ", points[i]);
        }
        fprintf(logout, "\n");

        int nroots = SZ(roots);
        fprintf(logout, "%d\n", nroots);
        rep(i, 0, nroots)  {
            fprintf(logout, "%d ", roots[i]);
        }
        fprintf(logout, "\n");
        fflush(stdout);
    }

    /**
        \brief initial the points to global double array.
    */
    void init(vi& points) {
        npt = SZ(points) >> 1;

        #ifdef LOCAL_DEBUG
        assert(npt < maxrt);
        #endif

        rep(i, 0, npt) {
            pts[i].x = points[i<<1];
            pts[i].y = points[i<<1|1];
        }

		init_kvc();
    }

    /**
        \brief collect the plant's root.
    */
    void collect(vi& roots) {
        cNR = NR = SZ(roots) >> 1;
		vi Sz(npt, 1);
        #ifdef LOCAL_DEBUG
        assert(NR < maxrt);
        #endif

        memset(idTb, -1, sizeof(idTb));
        rep(i, 0, npt)   pre[i] = i;
        rep(i, 0, NR) {
            const int& u = roots[i<<1];
            const int& v = roots[i<<1|1];
            int fu = find(u);
            int fv = find(v);
            if (fu != fv) {
                pre[fv] = fu;
				Sz[fu] += Sz[fv];
            }
        }

		#ifdef DEBUG
		// vi Sz_(npt, 0);
		// rep(i, 0, npt)
		// 	++Sz_[find(i)];
		#endif

        rep(i, 0, NP) {
			#ifdef DEBUG
			// assert(Sz[i] == Sz_[i] && pre[i]==i);
			// printf("Sz[%d] = %d, Sz_[%d] = %d\n", i, Sz[i], i, Sz_[i]);
			#endif
			G[i].init(i, Sz[i]);
            G[i].getId(i);
        }
		#ifdef DEBUG
		// fflush(stdout);
		// exit(0);
		#endif

        rep(i, 0, NR) {
            const int& u = roots[i<<1];
            const int& v = roots[i<<1|1];
            int ptId = find(u);
            double w = Length(pts[u], pts[v]);
            #ifdef DEBUG
            assert(ptId>=0 && ptId<NP);
            #endif
			G[ptId].addEdge(u, v, w);
        }

		/**
			using y = 2048 to refresh the graph
		*/
		Segment seg(0, 2048);
		rep(i, 0, NP) {
			G[i].refresh(seg);
			#ifdef DEBUG
			assert(G[i].vn == Sz[i]);
			#endif
		}
    }

	/**
		\breif Heuristic function: two smallest and closet circle two split,
				because they always need a cut to split them, why don't we cut early???
	*/
	double HForChoosePlant(int idx1, int idx2) {
		Point &p1 = pts[idx1];
		Point &p2 = pts[idx2];

		/**
			H = |c1.c - c2.c| + (|c1| + |c2|) / NR
		*/

		return Length2(p1, p2) + (G[idx1].top + G[idx2].top) / (double)(cNR);
	}

    /**
        \brief choose two smallest circle to split
			due to Heuristic function.
    */
    void chooseTwoPlant(int &idx, int &idx_) {
		int szGp = SZ(group);
		double mn = POS_INF;

		rep(k, 0, szGp) {
			int sz = SZ(group[k]);
			if (sz <= 1)
				continue;

			rep(i, 0, sz) {
				rep(j, i+1, sz) {
					double tmp = HForChoosePlant(group[k][i], group[k][j]);
					if (dcmp(tmp-mn) < 0) {
						idx = group[k][i];
						idx_ = group[k][j];
					}
				}
			}
		}
    }

	/**
		\brief choose the best cut according K
			Heuristic function: sum the weight of root with same side of plant's base-point,
				plus |le plant| * |gt plant|
		\	Because first item we want to protect more roots,
				second item we really need less cut, so we want a cut which can split more plant.
	*/
	void chooseBestSplit(double K, double lb, double rb, double &B, double &W) {
		vector<node_t> vc;
		vector<pair<double,int> > ptB;
		double h = 0;

		W = NEG_INF;
		memset(sumB, 0, sizeof(sumB));
		memset(ltB, 0, sizeof(ltB));
		memset(mark, 0, sizeof(mark));

		int szGp = SZ(group);

		rep(ii, 0, szGp) {
			int ptSz = SZ(group[ii]);
			vector<pair<double,int> > gpB;

			rep(jj, 0, ptSz) {
				int ptId = group[ii][jj];

				int psz = SZ(vc);
				G[ptId].dumpKxy(vc, K);
				int sz = SZ(vc);
				double &sum = sumB[ptId];
				double &lt = ltB[ptId];
				rep(j, psz, sz) {
					if (dcmp(vc[j].b - vc[psz].b) <= 0)
						lt += vc[j].w;
					sum += vc[j].w;
				}

				ptB.pb(mp(vc[psz].b, ptId));
				gpB.pb(mp(vc[psz].b, ptId));

				itmp[NP+ptId] = ptSz;
			}

			// calculate the plant in the same group whose B < current plant's B
			sort(all(gpB));
			itmp[group[ii][0]] = 0;
			rep(jj, 1, ptSz) {
				itmp[group[ii][jj]] = itmp[group[ii][jj-1]] + 1;
			}
			gpB.clr();
		}

		sort(all(vc));
		sort(all(ptB));
		int sz = SZ(vc);
		int i = 0, k = 0, lt = 0;
		/**
			following is the bug of CDT.
		*/
		{
			node_t nd = vc[sz-1];
			vc.pb(nd);
		}

		while (i < sz) {
			int j = i;

			while (i<sz && dcmp(vc[i].b - vc[j].b)==0) {
				if (visit[vc[i].ptId])
					h += vc[i].w;
				else
					h -= vc[i].w;
				++i;
			}
			while (k<NP && dcmp(ptB[k].fir - vc[j].b)==0) {
				int ptId = ptB[k].sec;
				mark[ptId] = true;
				/**
					update the weight of root
				*/
				h += ltB[ptId] + ltB[ptId] - sumB[ptId];
				/**
					update the weight of split same group
				*/
				h += w_incut * (itmp[ptId+NP] - itmp[ptId] - 1 - itmp[ptId]);
				/**
					update the weight of split different group
				*/
				int difSum = NP - itmp[ptId+NP];
				int diflt = lt - itmp[ptId];
				h += w_outcut * (difSum - diflt - diflt);
				++lt;
				++k;
			}

			double bb = (vc[j].b + vc[i].b) / 2.0;
			if (dcmp(h-W)>0 && dcmp(bb-lb)>0 && dcmp(bb-rb)<0) {
				B = bb;
				W = h;
			}
		}
	}


	/**
		\brief choose the best split due to cut
			x = ???, step = 10
	*/
	void chooseBestSplitX(double lx, double rx, double &x, double &w) {
		if (dcmp(lx-rx) == 0) {
			x = (lx + rx) / 2.0;
			w = 0;
			rep(i, 0, NP) {
				G[i].dumpX(x, w);
			}
			return ;
		}

		if (lx > rx)	swap(lx, rx);
		double delta = (rx-lx) / xy_step;
		double xx, tmp;

		w = NEG_INF;
		for (xx=lx; xx<=rx; xx+=delta) {
			tmp = 0;
			rep(i, 0, NP)
				G[i].dumpX(xx, tmp);
			if (dcmp(tmp-w) > 0) {
				w = tmp;
				x = xx;
			}
		}
	}

	/**
		\brief choose the best split due to
			y = ???, step = 10
	*/
	void chooseBestSplitY(double ly, double ry, double &y, double &w) {
		if (dcmp(ly-ry) == 0) {
			y = (ly + ry) / 2.0;
			w = 0;
			rep(i, 0, NP) {
				G[i].dumpY(y, w);
			}
			return ;
		}

		if (ly > ry)	swap(ly, ry);
		double delta = (ry - ly) / xy_step;
		double yy, tmp;

		w = NEG_INF;
		for (yy=ly+delta; yy<ry; yy+=delta) {
			tmp = 0;
			rep(i, 0, NP)
				G[i].dumpY(yy, tmp);
			if (dcmp(tmp-w) > 0) {
				w = tmp;
				y = yy;
			}
		}
	}

	/**
		\brief return a raw which split two plants
	*/
	inline Cut_t getRawCut(int idx1, int idx2) {
		int x = (pts[idx1].x + pts[idx2].x) / 2.0;
		return Cut_t(IPoint(x, 1), IPoint(x, 2));
	}

	/**
		\brief split two chosen plant
	*/
	Cut_t splitTwoPlant(int idx, int idx_) {
		double bestk, bestb, bestw = NEG_INF;
		double k, b, w;
		double lb, rb;
		int sz = SZ(kvc);

		rep(i, 0, sz) {
			k = kvc[i];
			lb = pts[idx].y - k*pts[idx].x;
			rb = pts[idx_].y - k*pts[idx_].x;
			int d = dcmp(lb - rb);
			if (d == 0) {
				/**
					which proves the center's of two plant two close.
				*/
				continue;
			}

			if (d > 0)
				swap(lb, rb);

			chooseBestSplit(k, lb, rb, b, w);
			if (dcmp(w-bestw) > 0) {
				bestw = w;
				bestb = b;
				bestk = k;
			}
		}

		/**
			need to check horizontal and vertical
		*/
		chooseBestSplitY(pts[idx].y, pts[idx_].y, b, w);
		if (dcmp(w-bestw) > 0) {
			bestw = w;
			bestb = b;
			bestk = 0.;
		}

		/**
			no better cut, using horizontal or vertial instead.
		*/
		chooseBestSplitX(pts[idx].x, pts[idx_].x, b, w);
		if (dcmp(w-bestw) > 0) {
			return Cut_t(IPoint((int)b, 1), IPoint((int)b, 2));
		}

		if (w <= NEG_INF)
			return getRawCut(idx, idx_);

		return chooseBestCut(bestk, bestb, idx, idx_);
	}

	/**
		\brief calculate the disntance between
			`y = k * x + b` and `y = k'x + b'`
	*/
	double HForKxy(double k, double b, double kk, double bb) {
		return fabs(k-kk) + fabs(b-bb);
	}


	/**
		\brief choose the best cut due to
			y = k * x + b.
	*/
	Cut_t chooseBestCut(double k, double b, int idx, int idx_) {
		vector<IPoint> vp;
		int x, y;

		for (x=0; x<=1024; ++x) {
			y = k * x + b;
			if (y>=0 && y<=1024)
				vp.pb(IPoint(x, y));
		}

		int sz = SZ(vp);
		#ifdef DEBUG
		printf("[BestCut] SZ(vp) = %d\n", sz);
		#endif

		if (sz <= 1)
			return getRawCut(idx, idx_);

		Point& p1 = pts[idx];
		Point& p2 = pts[idx_];
		int d1, d2;
		Cut_t ret, ct;
		double mn = POS_INF, tmp;

		rep(i, 0, sz) {
			ct.a = vp[i];
			rep(j, i+1, sz) {
				ct.b = vp[j];
				Segment seg = ct.toSegment();
				d1 = seg.cmp(p1)<=0 ? 0:1;
				d2 = seg.cmp(p2)<=0 ? 0:1;
				if (d1 ^ d2) {
					tmp = HForKxy(k, b, seg.k, seg.b);
					if (dcmp(tmp-mn) < 0) {
						ret = ct;
						mn = tmp;
					}
				}
			}
		}

		return mn<POS_INF ? ret : getRawCut(idx, idx_);
	}


	/**
		\brief update the group of plant
			due to current ct
	*/
	void updatePlant() {
		const Cut_t& ct = *ans.rbegin();
		Segment seg = ct.toSegment();
		int szGp = SZ(group);

		rep(i, 0, szGp) {
			int sz = SZ(group[i]);
			if (sz <= 1)
				continue;

			int c[2];

			c[0] = c[1] = 0;
			rep(j, 0, sz) {
				itmp[j] = (seg.cmp(pts[group[i][j]]) <= 0 ? 0 : 1);
				++c[itmp[j]];
			}
			if (c[0]>0 && c[1]>0) {
				int d = c[1]>=c[0], m = 0;
				vi vc;

				rep(j, 0, sz) {
					if (itmp[j] == d) {
						group[i][m++] = group[i][j];
					} else {
						vc.pb(group[i][j]);
					}
				}

				#ifdef DEBUG
				assert(SZ(vc) > 0);
				#endif
				group[i].resize(m);
				group.pb(vc);
			}
		}
	}

	/**
		\brief update the root of plant
			due to current ct
	*/
	void updateRoot() {
		const Cut_t& ct = *ans.rbegin();
		Segment seg = ct.toSegment();

		cNR = 0;
		rep(i, 0, NP) {
			G[i].refresh(seg);
			cNR += G[i].top;
		}
		#ifdef DEBUG
		assert(cNR >= NP);
		#endif
	}

	/**
		\brief check if we can reduce some unnessary cut.
		\prob not sure about if can reduce some cut.
	*/
	void reduceCut(int bsz=0, int esz=-1) {
		if (esz < 0)	esz = SZ(ans);

		int n = bsz;
		vpii vp;

		memset(visit, false, sizeof(visit));
		rep(i, bsz, esz) {
			Segment seg = ans[i].toSegment();
			int lt = 0, ge = 0;

			rep(j, 0, NP) {
				if (seg.cmp(pts[j]) <= 0)
					++lt;
				else
					++ge;
			}

			if (lt && ge) {
				vp.pb(mp(lt*ge, i));
			}
		}

		sort(all(vp));
		int sz = SZ(vp);
		vi keep;

		rep(i, 0, sz) {
			const int& k = vp[i].sec;
			Segment seg = ans[k].toSegment();
			int le = 0, gt = NP, cnt = 0;

			rep(j, 0, NP) {
				if (seg.cmp(pts[j]) <= 0) {
					itmp[le++] = j;
				} else {
					itmp[gt++] = j;
				}
			}

			rep(j, 0, le) {
				rep(k, NP, gt) {
					if (!visit[j][k]) {
						visit[itmp[j]][itmp[k]] = visit[itmp[k]][itmp[j]] = true;
						++cnt;
					}
				}
			}

			if (cnt > 0) keep.pb(k);
		}

		sort(all(keep));
		rep(i, 0, SZ(keep))	ans[n++] = ans[keep[i]];

		#ifdef DEBUG
		printf("[reduceCut] reduce = %d\n", esz-bsz-n);
		#endif
		ans.resize(n);
	}

    /**
        \brief split the plants using
			Heuristics function.
    */
	void split() {
		#ifdef DEBUG
		int cnt = 0;
		#endif
		
		while (SZ(group) < NP) {
			#ifdef DEBUG
			// if (++cnt == NP) {
			// 	puts("wrong");
			// 	fflush(stdout);
			// 	return ;
			// }
			#endif
			/**
				\step 1. choose two fittest plant
			*/
			int idx = -1, idx_ = -1;
			chooseTwoPlant(idx, idx_);

			#ifdef DEBUG
			assert(idx>=0 && idx_>=0);
			int szGp = SZ(group);
			printf("szGp = %d, idx = %d, idx_ = %d\n", szGp, idx, idx_);
			#endif

			/**
				\step 2. cut the choosen plant
			*/
			Cut_t ct = splitTwoPlant(idx, idx_);
			ans.pb(ct);

			/**
				\step 3. update the group of plant
			*/
			updatePlant();

			/**
				\step 4. update the root of plant
			*/
			updateRoot();

			/**
				\step 5. reduce the cut
			*/
			// reduceCut();

			#ifdef DEBUG
			assert(SZ(group) > szGp);
			#endif
		}
	}

	/**
		\brief check if all separated.
	*/
	void check_separated() {
		int sz = SZ(ans);

		memset(visit, false, sizeof(visit));
		rep(k, 0, sz) {
			Segment seg = ans[k].toSegment();
			rep(i, 0, NP) {
				if (seg.cmp(pts[i]) <= 0) {
					rep(j, i+1, NP) {
						if (seg.cmp(pts[j]) > 0) {
							visit[i][j] = visit[j][i] = true;
						}
					}
				} else {
					rep(j, i+1, NP) {
						if (seg.cmp(pts[j]) <= 0) {
							visit[i][j] = visit[j][i] = true;
						}
					}
				}
			}
		}

		int nsz = sz;
		rep(i, 0, NP) {
			rep(j, i+1, NP) {
				if (visit[i][j])
					continue;

				int k = 0;
				for (k=sz; k<nsz; ++k) {
					Cut_t& ct = ans[k];
					if ((ct.a.x-pts[i].x) * (ct.a.x-pts[j].x) < 0)
						break;
				}

				if (k >= nsz) {
					Cut_t ct;
					ct.a.x = ct.b.x = (pts[i].x + pts[j].x) / 2;
					ct.a.y = 1;
					ct.b.y = 2;
					ans.pb(ct);
					++nsz;
				}
			}
		}
	}

    /**
        \brief Traser's v2.0 algorithm to make the cuts.
    */
	vi makeCuts(int NP, vi points, vi roots) {
        #ifdef LOCAL_DEBUG
        dumpInputToLog(NP, points, roots);
        #endif

        this->NP = NP;
        /**
            \step 1: initial union-find & pid vector & base point
        */
        init(points);

        /**
            \step 2: which plan the root belongs to.
        */
        collect(roots);

        /**
            \step 3: separate the circle
        */
		vi vc;
		rep(i, 0, NP) vc.pb(i);
		group.pb(vc);
        split();
        #ifdef LOCAL_DEBUG
        fprintf(logout, "after split |Cut| = %d\n", SZ(ans));
        #endif

		/**
            \step 5: chekc if can reduce some cut
        */
		reduceCut();
		#ifdef LOCAL_DEBUG
        fprintf(logout, "after reduce |Cut| = %d\n", SZ(ans));
        #endif

        /**
            \step 6: check if all separated
        */
		check_separated();
		#ifdef LOCAL_DEBUG
        fprintf(logout, "after check |Cut| = %d\n", SZ(ans));
        #endif

		/**
			\step 7: dump to return
		*/
		vi ret;
        dump_result(ret);

        return ret;
	}

	/**
		\brief dump the coordinates of ans to the result vector.
			Make sure that no two points concide.
	*/
	void dump_result(vi& res) {
        int sz = SZ(ans);

        rep(i, 0, sz) {
            res.pb(ans[i].a.x);
            res.pb(ans[i].a.y);
            res.pb(ans[i].b.x);
            res.pb(ans[i].b.y);
			#ifdef DEBUG
			assert(ans[i].a != ans[i].b);
			#endif
        }
        
        #ifdef DEBUG
		printf("|Cut| = %d\n", sz);
        #endif

        #ifdef LOCAL_DEBUG
        fprintf(logout, "|Cut| = %d\n", sz);
        #endif
	}
};
const double CutTheRoots::NEG_INF = -1e16;
const double CutTheRoots::POS_INF = 1e16;
const double CutTheRoots::w_incut = 1.0;
const double CutTheRoots::w_outcut = 0.0;
const double CutTheRoots::xy_step = 10;
const double CutTheRoots::alpha_step = 1.0;

// -------8<------- end of solution submitted to the website -------8<-------

template<class T>
void getVector(vector<T>& v) {
    for (int i = 0; i < v.size(); ++i)
        cin >> v[i];
}

void init_log() {
    logout = fopen(LOG_FILENAME, "w");

    if (logout == NULL) {
        fprintf(stderr, "%s not exists.", LOG_FILENAME);
        exit(1);
    }
}

void close_log() {
    fclose(logout);
}

int main() {
    #ifdef DEBUG
		freopen("data.in", "r", stdin);
		freopen("data.out", "w", stdout);
    #endif

    init_log();

    int NP;
    cin >> NP;

    int Npoints;
    cin >> Npoints;
    vector<int> points(Npoints);
    getVector(points);

    int Nroots;
    cin >> Nroots;
    vector<int> roots(Nroots);
    getVector(roots);

    CutTheRoots cr;
    vector<int> ret = cr.makeCuts(NP, points, roots);

	#ifdef DEBUG
	cout << "sz = ";
	#endif
    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i) {
        cout << ret[i] << endl;
    }
    cout.flush();
    close_log();

	return 0;
}

