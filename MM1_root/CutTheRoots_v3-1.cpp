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
#pragma comment(linker,"/STACK:102400000,1024000")

#define sti				set<int>
#define stpii			set<pair<int, int> >
#define mpii			map<int,int>
#define vi				vector<int>
#define pii				pair<int, int>
#define pdd             pair<float, float>
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
// #define LOCAL_DEBUG
// #define DEBUG

typedef long long LL;

const float eps = 1e-5;
const float PI = acos(-1.0);
const int maxp = 106;
const int maxrt = 105115;
int itmp[maxp*3];
int S[maxrt], top;
float W[maxrt];
float ltB[maxp];
float sumB[maxp];
bool mark[maxp];
bool visit[maxp][maxp];
FILE* logout;
int cNR;

int dcmp(float x) {
    if (fabs(x) < eps)  return 0;
    return x<0 ? -1:1;
}

template <typename T=float>
struct Point_t {
    T x, y;

    Point_t() {}
    Point_t(float x, float y): x(x), y(y) {}

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
		printf("x = %.4lf, y = %.4lf\n", (float)x, (float)y);
	}
};

typedef Point_t<float> Point;
typedef Point_t<int> IPoint;
typedef Point Vector;
Point pts[maxrt];

typedef struct Segment {
    float k, b;
	int st;

    Segment() {}
    Segment(float k, float b, int st=0):k(k), b(b), st(st) {}

    int cmp(Point& p) {
    	if (st)
			return dcmp(p.x - b);
		else
			return dcmp(p.y - (k*p.x+b));
    }

	int cmp(float x, float y) {
		if (st)
			return dcmp(x - b);
		else
			return dcmp(y - (k*x+b));
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
            float k = ((float)b.y-a.y) / ((float)b.x-a.x);
            float bb = a.y - k*a.x;
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
	float w;
	int nxt;

	edge_t() {}
	edge_t(int v, float w):v(v), w(w) {}

	void print() const {
		printf("v = %d, w = %.4lf\n", v, w);
	}

} edge_t;

typedef struct node_t {
	float b, w;
	int ptId;

	node_t() {}
	node_t(float b, float w, float ptId):
		b(b), w(w), ptId(ptId) {}

	bool operator< (const node_t& oth) const {
		return b < oth.b;
	}

} node_t;

const float len_son_weight = 1.0;
int head[maxrt], l = 1, rtd;
edge_t E[maxrt];
node_t nd[maxrt];
Segment seg;

inline void addEdge(int u, int v, float w) {
	#ifdef DEBUG
	printf("u = %d, v = %d\n", u, v);
	fflush(stdout);
	#endif
	#ifdef LOCAL_DEBUG
	assert(u != v);
	#endif
	E[l].v = v;
	E[l].w = w;
	E[l].nxt = head[u];
	head[u] = l++;
	#ifdef DEBUG
	assert(l <= maxrt);
	#endif
}

inline float calWeight(int len, int son) {
	return len * son / cNR;
}

inline int getPos(Point p)	 {
	return seg.cmp(p)<=0 ? 0:1;
}

inline int getPos(int pid) {
	return seg.cmp(pts[pid])<=0 ? 0:1;
}

bool dfs_refresh(int u, int& son, float& len) {
	int d = getPos(u);

	#ifdef DEBUG
		// printf("u = %d, d = %d\n", u, d);
	#endif

	if (d != rtd) {
		W[u] = 0;
		return false;
	}

	son = 1;
	len = 0;
	S[top++] = u;
	int sson, pk = 0;
	float llen;

	#ifdef DEBUG
	// printf("u = %d\n", u);
	#endif

	for (int k=head[u]; k; k=E[k].nxt) {
		const int& v = E[k].v;
		if (dfs_refresh(v, sson, llen)) {
			son += sson;
			len += llen + E[k].w;
			if (pk)
				E[pk].nxt = k;
			pk = k;
		}
	}

	W[u] = calWeight(len, son);
	if (!pk)
		head[u] = 0;
	else
		E[pk].nxt = 0;
	return true;
}

typedef struct Graph_t {
	int l, r;
	int ptId;

	void refresh() {
		int son;
		float len;

		l = top;
		rtd = getPos(ptId);
		#ifdef DEBUG
		bool flag = dfs_refresh(ptId, son, len);
		#else
		dfs_refresh(ptId, son, len);
		#endif
		r = top;

		#ifdef DEBUG
		assert(r<=maxrt && flag && son>=1);
		#endif
	}

	void dumpKxy(int& sz, float k) {
		rep(i, l, r) {
			// int pid = getPid(S[i]);
			const int& pid = S[i];
			nd[sz].b = pts[pid].y - pts[pid].x * k;
			nd[sz].w = W[pid];
			nd[sz].ptId = ptId;
			++sz;
		}
	}

	void dumpX(float x, float &w) {
		int d = dcmp(pts[ptId].x - x) <= 0 ? 0 : 1;
		rep(i, l, r) {
			const int& pid = S[i];
			int d2 = dcmp(pts[pid].x - x) <= 0 ? 0 : 1;
			if (d == d2) {
				w += W[pid];
			}
		}
	}

	void dumpY(float y, float &w) {
		int d = dcmp(pts[ptId].y - y) <= 0 ? 0 : 1;
		rep(i, l, r) {
			const int& pid = S[i];
			int d2 = dcmp(pts[pid].y - y) <= 0 ? 0 : 1;
			if (d == d2) {
				w += W[pid];
			}
		}
	}

} Graph_t;

/**
    \brief calculate the length^2 between to points
*/
inline float Length2(const Point& a, const Point& b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

/**
    \brief calculate the length between to points
*/
inline float Length(const Point& a, const Point& b) {
    return sqrt( (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) );
}

inline float Length(const Point& a) {
    return sqrt(a.x*a.x + a.y*a.y);
}

Graph_t G[maxp];
vector<vi> group;
vector<Cut_t> ans;
vector<float> kvc;

class CutTheRoots {
public:
	float NEG_INF;
	float POS_INF;
	float w_incut;
	float w_outcut;
	float xy_step;
	float alpha_step;
    int NR, NP, npt;
	
	/**
		\brief the parameter
	*/
	void init_para() {
		NEG_INF = -1e16;
		POS_INF = 1e16;
		w_incut = 30.0  / NP;
		w_outcut = 2.0 * (npt / (NP * 300.0));
		xy_step = 10;
		alpha_step = 2.0;
	}

	/**
		\brief K to choose according the step
	*/
	inline void init_kvc() {
		float alpha;

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
        fflush(logout);
    }

    /**
        \brief initial the points to global float array.
    */
    void init(vi& points) {
        npt = SZ(points) >> 1;

        #ifdef LOCAL_DEBUG
        assert(npt < maxrt);
        #endif

        rep(i, 0, npt) {
            pts[i].x = points[i<<1];
            pts[i].y = points[(i<<1)|1];
        }

		init_kvc();
		init_para();
    }

    /**
        \brief collect the plant's root.
    */
    void collect(vi& roots) {
        NR = SZ(roots) >> 1;
		cNR = npt;
        #ifdef LOCAL_DEBUG
        assert(NR < maxrt);
        #endif

		memset(head, 0, sizeof(head));
		rep(i, 0, NP)	G[i].ptId = i;
		#ifdef DEBUG
		printf("NR = %d\n", NR);
		#endif
        rep(i, 0, NR) {
            const int& u = roots[i<<1];
            const int& v = roots[(i<<1)|1];
			float w = Length(pts[u], pts[v]);
			addEdge(u, v, w);
        }
		#ifdef DEBUG
		printf("addEdge end.\n");
		#endif
		
		#ifdef DEBUG
        puts("update Root start");
		fflush(stdout);
		#endif
        updateRoot(Segment(0, 2048));
		#ifdef DEBUG
        puts("update Root end");
		fflush(stdout);
		#endif
		#ifdef DEBUG
        assert(cNR == npt);
		#endif
    }

	/**
		\breif Heuristic function: two smallest and closet circle two split,
				because they always need a cut to split them, why don't we cut early???
	*/
	float HForChoosePlant(int idx1, int idx2) {
		Point &p1 = pts[idx1];
		Point &p2 = pts[idx2];

		/**
			H = |c1.c - c2.c| + (|c1| + |c2|) / NR
		*/

		return Length(p1, p2) + (G[idx1].r - G[idx1].l + G[idx2].r - G[idx2].l) / (float)(cNR);
	}

    /**
        \brief choose two smallest circle to split
			due to Heuristic function.
    */
    void chooseTwoPlant(int &idx, int &idx_) {
		int szGp = SZ(group);
		float mn = POS_INF;

		rep(k, 0, szGp) {
			int sz = SZ(group[k]);
			if (sz <= 1)
				continue;

			rep(i, 0, sz) {
				rep(j, i+1, sz) {
					float tmp = HForChoosePlant(group[k][i], group[k][j]);
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
	void chooseBestSplit(float K, float lb, float rb, float &B, float &W) {
		int szNd = 0;
		vector<pair<float,int> > ptB;
		float h = 0;

		W = NEG_INF;
		memset(sumB, 0, sizeof(sumB));
		memset(ltB, 0, sizeof(ltB));
		memset(mark, 0, sizeof(mark));

		int szGp = SZ(group);

		rep(ii, 0, szGp) {
			int ptSz = SZ(group[ii]);
			vector<pair<float,int> > gpB;

			rep(jj, 0, ptSz) {
				int ptId = group[ii][jj];

				int psz = szNd;
				G[ptId].dumpKxy(szNd, K);

				float &sum = sumB[ptId];
				float &lt = ltB[ptId];
				rep(j, psz, szNd) {
					if (dcmp(nd[j].b - nd[psz].b) <= 0)
						lt += nd[j].w;
					sum += nd[j].w;
				}

				ptB.pb(mp(nd[psz].b, ptId));
				gpB.pb(mp(nd[psz].b, ptId));

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

		sort(nd, nd+szNd);
		sort(all(ptB));
		int i = 0, k = 0, lt = 0;
		nd[szNd] = nd[szNd-1];

		while (i < szNd) {
			int j = i;

			while (i<szNd && dcmp(nd[i].b - nd[j].b)==0) {
				if (visit[nd[i].ptId])
					h += nd[i].w;
				else
					h -= nd[i].w;
				++i;
			}
			while (k<NP && dcmp(ptB[k].fir - nd[j].b)==0) {
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

			float bb = (nd[j].b + nd[i].b) / 2.0;
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
	void chooseBestSplitX(float lx, float rx, float &x, float &w) {
		if (dcmp(lx-rx) == 0) {
			x = (lx + rx) / 2.0;
			w = 0;
			rep(i, 0, NP) {
				G[i].dumpX(x, w);
			}
			return ;
		}

		if (lx > rx)	swap(lx, rx);
		float delta = (rx-lx) / xy_step;
		float xx, tmp;

		w = NEG_INF;
		for (xx=lx+delta; xx<=rx; xx+=delta) {
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
	void chooseBestSplitY(float ly, float ry, float &y, float &w) {
		if (dcmp(ly-ry) == 0) {
			y = (ly + ry) / 2.0;
			w = 0;
			rep(i, 0, NP) {
				G[i].dumpY(y, w);
			}
			return ;
		}

		if (ly > ry)	swap(ly, ry);
		float delta = (ry - ly) / xy_step;
		float yy, tmp;

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
		float bestk, bestb, bestw = NEG_INF;
		float k, b, w;
		float lb, rb;
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
	float HForKxy(float k, float b, float kk, float bb) {
		return fabs(k-kk) + fabs(b-bb);
	}


	/**
		\brief choose the best cut due to
			y = k * x + b.
	*/
	Cut_t chooseBestCut(float k, float b, int idx, int idx_) {
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
		float mn = POS_INF, tmp;

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
				#ifdef DEBUG
				int pid = group[i][j];
				Point pt = pts[pid];
				#endif
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
		seg = ct.toSegment();

		top = 0;
		rep(i, 0, NP) {
			G[i].refresh();
		}
		cNR = top;
		#ifdef DEBUG
		assert(cNR >= NP);
		#endif
	}

	void updateRoot(Segment seg_) {
		seg = seg_;

		top = 0;
		rep(i, 0, NP) {
			G[i].refresh();
		}
		cNR = top;
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
		int cnt = 0;

		while (SZ(group) < NP) {
			if (++cnt == NP) {
			#ifdef LOCAL_DEBUG			
				fprintf(logout, "output of NP.\n");
				fflush(logout);
			#endif
				break ;
			}
			/**
				\step 1. choose two fittest plant
			*/
			int idx = -1, idx_ = -1;
			int pszGp = SZ(group);
			chooseTwoPlant(idx, idx_);

			#ifdef DEBUG
			assert(idx>=0 && idx_>=0);
			printf("szGp = %d, idx = %d, idx_ = %d\n", pszGp, idx, idx_);
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

			if (SZ(group) == pszGp)
				break;
			#ifdef DEBUG
			assert(SZ(group) > pszGp);
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
		#ifdef DEBUG
		puts("initial points start.");
		fflush(stdout);
		#endif
        init(points);
		#ifdef DEBUG
		puts("initial points end.");
		fflush(stdout);
		#endif

        /**
            \step 2: which plan the root belongs to.
        */
		#ifdef DEBUG
		puts("collect roots start.");
		fflush(stdout);
		#endif
        collect(roots);
		#ifdef DEBUG
		puts("collect roots end.");
		fflush(stdout);
		#endif
		
        /**
            \step 3: separate the circle
        */
		vi vc;
		rep(i, 0, NP) vc.pb(i);
		group.pb(vc);
		#ifdef DEBUG
		puts("separate plants start.");
		fflush(stdout);
		#endif
        split();
		#ifdef DEBUG
		puts("separate plants end.");
		fflush(stdout);
		#endif
        #ifdef LOCAL_DEBUG
        fprintf(logout, "after split |Cut| = %d\n", SZ(ans));
        #endif

		/**
            \step 5: chekc if can reduce some cut
        */
		#ifdef DEBUG
		puts("reduce Cut start.");
		fflush(stdout);
		#endif
		reduceCut();
		#ifdef DEBUG
		puts("reduce Cut end.");
		fflush(stdout);
		#endif
		#ifdef LOCAL_DEBUG
        fprintf(logout, "after reduce |Cut| = %d\n", SZ(ans));
        #endif

        /**
            \step 6: check if all separated
        */		
		#ifdef DEBUG
		puts("check Separated start.");
		fflush(stdout);
		#endif
		check_separated();
		#ifdef DEBUG
		puts("check Separated end.");
		fflush(stdout);
		#endif
		#ifdef LOCAL_DEBUG
        fprintf(logout, "after check |Cut| = %d\n", SZ(ans));
        #endif

		/**
			\step 7: dump to return
		*/
		#ifdef DEBUG
		puts("dump Result start.");
		fflush(stdout);
		#endif
		vi ret;
        dump_result(ret);
		#ifdef DEBUG
		puts("dump Result end.");
		fflush(stdout);
		#endif
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