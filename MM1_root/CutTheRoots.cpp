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

#define makeCuts        makeCuts_Trasier_v1
#define LOG_FILENAME    "makeCuts.log"
#define LOCAL_DEBUG
#define DEBUG

typedef long long LL;

const double eps = 1e-7;
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
};

typedef Point_t<double> Point;
typedef Point_t<int> IPoint;
typedef Point Vector;


typedef struct Circle {
    Point c;
    double r;

    Circle() {}
    Circle(Point c, double r=0):c(c), r(r) {}
    Circle(double x, double y, double rr=0) {
        c.x = x;
        c.y = y;
        r = rr;
    }

    bool operator== (const Circle& oth) const {
        return c==oth.c && r==oth.r;
    }

    Point point(double a) const {
        return Point(c.x+cos(a)*r, c.y+sin(a)*r);
    }

} Circle;

typedef struct Segment {
    double k, b;
	int st;

    Segment() {}
    Segment(double k, double b, int st=0):k(k), b(b), st(st) {}

	int cmp(double x, double y) {
		if (st)
			return dcmp(b-x);
		else
			return dcmp(k*x+b - y);
	}

	int cmp(const Circle& c) const {
		if (st)
			return dcmp(b-c.c.x);
		else
			return dcmp(k*c.c.x+b - c.c.y);
	}

    bool operator== (const Segment& oth) const {
        return k==oth.k && b==oth.b;
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

} Cut_t;


const double PI = acos(-1.0);
const int maxp = 110;
const int maxrt = 105110;
int cid[maxp];
double rad[maxrt];
int pre[maxrt];
Point pts[maxrt];
vi pid[maxp];
FILE* logout;

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
	\brief calculate the 2*Area of the triangle
*/
inline double Area2(Point a, Point b, Point c) {
    return Cross(b-a, c-a);
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
    \brief calculate the distance from point P to Segment(A, B).
*/
inline double DistanceToSegment(Point &P, Point &A, Point &B) {
    if (A == B) return Length(P - A);
    Vector v1 = B - A, v2 = P - A, v3 = P - B;

    if (dcmp(Dot(v1, v2)) < 0)      return Length(v2);
    else if (dcmp(Dot(v1, v3)) > 0) return Length(v3);
    else                            return fabs(Cross(v1, v2)) / Length(v1);
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
    \brief calculate the internal common tangent
*/
int getTangents(Circle &A, Circle &B, vector<Point>& ip) {
    #ifdef LOCAL_DEBUG
    assert(dcmp(A.r-B.r) >= 0);
    assert(SZ(ip) == 0);
    #endif

    double d2 = Length2(A.c, B.c);
    double rdif = A.r - B.r;
    double rsum = A.r + B.r;

    #ifdef LOCAL_DEBUG
    assert(dcmp(d2-rdif*rdif) >= 0);
    #endif
    // if (d2 < rdif*rdif) {
    //     return 0;
    // }

    double base = angle(B.c - A.c);
    // if (dcmp(d2)==0 && A.r==B.r) {
    //     return -1;
    // }
    if (d2 == rdif*rdif) {
        ip.pb(A.point(base));
        ip.pb(B.point(base));
        return 1;
    }

    // external common tangent
    // double ang = acos((A.r-B.r) / sqrt(d2));
    // ip.pb(A.point(base + ang));
    // ip.pb(B.point(base + ang));
    // ip.pb(A.point(base - ang));
    // ip.pb(B.point(base - ang));
    int d = dcmp(d2 - rsum*rsum);
    if (d == 0) {
        ip.pb(A.point(base));
        ip.pb(B.point(PI+base));
    } else if (d > 0) {
        double ang = acos((A.r+B.r) / sqrt(d2));
        ip.pb(A.point(base+ang));
        ip.pb(B.point(PI+base+ang));
        ip.pb(A.point(base-ang));
        ip.pb(B.point(PI+base-ang));
    }

    return SZ(ip) >> 1;
}

class CutTheRoots {
public:
    int NR, NP, npt;
    vector<Circle> cir;
    vector<Cut_t> ans;

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
    }

    /**
        \brief makeCuts function provided by TCO.
    */
    vector<int> makeCuts_raw(int NP, vector<int> points, vector<int> roots) {
        // first NP points give coordinates of the bases of the plants, written as x, y
        // get x-coordinates of the bases, sort them, make cuts along y-axis to separate x-coordinates
        vector<int> xs(NP);
        for (int i = 0; i < NP; ++i) {
            xs[i] = points[2 * i];
        }
        sort(xs.begin(), xs.end());
        vector<int> ret(4 * (NP - 1));
        for (int i = 0; i < NP - 1; ++i) {
            int x = (xs[i] + xs[i + 1]) / 2;
            ret[4 * i] = x;
            ret[4 * i + 1] = 1;
            ret[4 * i + 2] = x;
            ret[4 * i + 3] = 2;
        }
        return ret;
    }

    /**
        \brief disjoint-set
    */
    int find(int x) {
        if (x == pre[x])
            return x;
        return pre[x] = find(pre[x]);
    }

    /**
        \brief initial the points to global double array.
    */
    void init(vi& points) {
        #ifdef LOCAL_DEBUG
        assert(SZ(points)%2 == 0);
        #endif

        npt = SZ(points) >> 1;
        cir.clr();
        ans.clr();

        #ifdef LOCAL_DEBUG
        assert(npt < maxrt);
        #endif

        rep(i, 0, npt) {
            pts[i].x = points[i<<1];
            pts[i].y = points[i<<1|1];
        }

        rep(i, 0, NP) {
            cir.pb(Circle(pts[i]));
            pid[i].clr();
        }

        rep(i, 0, npt)   pre[i] = i;
    }

    /**
        \brief collect the plant's root.
    */
    void collect(vi& roots) {
        #ifdef LOCAL_DEBUG
        assert(SZ(roots)%2 == 0);
        #endif

        NR = SZ(roots) >> 1;

        #ifdef LOCAL_DEBUG
        assert(NR < maxrt);
        #endif

        rep(i, 0, NR) {
            const int& u = roots[i<<1];
            const int& v = roots[i<<1|1];
            int fu = find(u);
            int fv = find(v);
            if (fu != fv) {
                pre[fv] = fu;
            }
        }

        #ifdef LOCAL_DEBUG
        int ngroup = 0;
        #endif

        rep(i, 0, NP) {
            #ifdef LOCAL_DEBUG
            assert(pre[i] == i);
            #endif
            pid[i].pb(i);
        }

        rep(i, 0, NR) {
            find(i);
            if (pre[i] != i) {
                pid[pre[i]].pb(i);
            }
            #ifdef LOCAL_DEBUG
            else {
                ++ngroup;
            }
            #endif
        }
        #ifdef LOCAL_DEBUG
        assert(ngroup == NP);
        #endif
    }

    /**
        \brief random partiton for find the kth radius.
    */
    int partition(int l, int r) {
        int n = r-l+1;
        int pos = rand()%n+l;

        swap(rad[pos], rad[r]);
        pos = r;
        --r;

        while (l <= r) {
            while (l<pos && rad[l]<=rad[pos])
                ++l;
            while (r>l && rad[r]>rad[pos])
                --r;
            if (l >= r)
                break;
            swap(rad[l], rad[r]);
        }
        swap(rad[l], rad[pos]);

        return l;
    }

    /**
        \brief find the kth radius.
    */
    double findKth(int n, int kth) {
        int l = 0, r = n - 1;
        int idx = 0;

        #ifdef DEBUG
        // printf("l = %d, r = %d, kth = %d\n", l, r, kth);
        // fflush(stdout);
		#endif
		#ifdef LOCAL_DEBUG
        assert(r>=l && kth>=l && kth<=r);
        #endif

        while (idx != kth) {
            idx = partition(l, r);
            if (idx < kth) {
                l = idx + 1;
            } else if (idx > kth) {
                r = idx -1;
            } else {
                break;
            }
        }

        #ifdef LOCAL_DEBUG
        assert(idx == kth);
        #endif

        return rad[idx];
    }

    /**
        \brief find the median-distance from root to center of circle.
            As the radius of the circumcircle of the plant.
    */
    double findMid(int sz) {
        if (sz & 1)
            return findKth(sz, sz >> 1);
        else
            return (findKth(sz, sz >> 1) + findKth(sz, (sz>>1)-1)) / 2.0;
    }

    /**
        \brief Regard the plant as circle, so we need to calculate the radius of the circle.
    */
    void calRadius(int l, int r) {
        rep(i, l, r) {
            const int& id = cid[i];
            const int sz = SZ(pid[id]);
            rep(j, 0, sz) {
                const int& k = pid[id][j];
                rad[j] = Length2(cir[id].c, pts[k]);
            }
            cir[id].r = sqrt( findMid(sz) );
        }
    }

    /**
        \brief Heuristic choose two circle to split.
            Heuristic function: two biggest circle two split, because I would realy keep more area of them.
    */
    void chooseTwoCircle(int l, int r, int& mxidx, int& mxidx_) {
        if (dcmp(cir[cid[l]].r - cir[cid[l+1]].r) >= 0) {
            mxidx = l;
            mxidx_ = l+1;
        } else {
            mxidx = l+1;
            mxidx_ = l;
        }

        rep(i, l+2, r) {
            if (dcmp(cir[cid[i]].r - cir[cid[mxidx]].r) >= 0) {
                mxidx_ = mxidx;
                mxidx = i;
            } else if (dcmp(cir[cid[i]].r - cir[cid[mxidx_]].r) >= 0) {
                mxidx_ = i;
            }
        }
    }

    /**
        \brief calculate the relative
    */
    int circle_circle_intersection(Circle &c1, Circle &c2, vector<Point>& ip) {
        double d = Length(c1.c, c2.c);

        ip.clr();
        #ifdef LOCAL_DEBUG
        assert(dcmp(d) != 0);                   // two circles concide, never happens, because different base point.
        #endif
        // if (dcmp(d) == 0) {
        //     #ifdef LOCAL_DEBUG
        //     assert(dcmp(c1.r - c2.r) != 0);     // two circles concide
        //     #endif
        //     return 0;                          // big circle cover small circle and have same center
        // }

        if (dcmp(c1.r+c2.r-d) < 0) {
            return -1;                          // two circles separated.
        }

        if (dcmp(fabs(c1.r-c2.r)-d) >= 0) {       // big circle cover small circle
            return -2;
        }

        double a = angle(c2.c - c1.c);
        double tmp = (c1.r*c1.r + d*d - c2.r*c2.r) / (2.0*c1.r*d);
        tmp = min(1.0, tmp);
        tmp = max(-1.0, tmp);
        double da = acos(tmp);

        Point p1 = c1.point(a - da);
        Point p2 = c1.point(a + da);
        ip.pb(p1);

        if (p1 == p2)
            return 1;                           // two circles tangent
        ip.pb(p2);
        return 2;                               // two circles intersect
    }

    /**
        \brief get the best cut point due to relative position of two circles.
    */
    Point getBestCutPoint(Circle &c1, Circle &c2, int& status, vector<Point>& pvc) {
        Point p0;

        status = circle_circle_intersection(c1, c2, pvc);

        if (status == 2) {
            // intersect
            p0 = (pvc[0] + pvc[1]) * 0.5;

        } else if (status == 1) {
            // tangent
            p0 = pvc[0];

        } else if (status == -1) {
            // separated
            int n_tangents = getTangents(c1, c2, pvc);

            #ifdef LOCAL_DEBUG
            assert(n_tangents >= 1);
            #endif

            if (n_tangents == 1) {
                p0 = pvc[0];
            } else {
                #ifdef LOCAL_DEBUG
                // any internal common tangents must intersection.
                Vector v1 = pvc[1] - pvc[0];
                Vector v2 = pvc[3] - pvc[2];
                assert(Cross(v1, v2) != 0);
                #endif
                p0 = GetLineIntersection(pvc[0], v1, pvc[2], v2);
                #ifdef LOCAL_DEBUG
                assert(SegmentIntersection(pvc[0], pvc[1], pvc[2], pvc[3]));
                #endif
            }

        } else if (status == -2) {
            // cover
            p0 = (c1.c + c2.c) * 0.5;

        }
        #ifdef LOCAL_DEBUG
        else {
            assert(0/*never goes there*/);
        }
        #endif

        return p0;
    }

    /**
        \brief calculate the coefficient of the equation.
    */
    inline void updateCoef(int x0, int y0, Point& p, LL &A, LL &B, LL &C) {
        LL x = (int)(p.x) - x0;
        LL y = y0 - (int)(p.y);
        A += x * x;
        B += 2 * x * y;
        C += y * y;
    }

    /**
        \brief calculate the best k due to Monotonic.
            I'm not absolutely sure about the range [-\inf, -1].
    */
    inline void getEquationK(LL A, LL B, LL C, vector<double>& kvc) {
        if (B == 0)   {
            kvc.pb(0);
            return ;
        }

        LL D = C - A;
        C = -B;
        A = B;
        B = D+D;

        #ifdef LOCAL_DEBUG
        assert(1.0*B*B - 4.0*A*C > 0);
        #endif
        double delta = sqrt(1.0*B*B - 4.0*A*C);

        double k1 = (-B+delta) / (A+A);
        double k2 = (-B-delta) / (A+A);
        kvc.pb(k1);
        kvc.pb(k2);
    }

    /**
        \brief get the Extreme point of the `W` function.
    */
    void getExtremeK(int l, int r, Point &p0, LL& A, LL& B, LL& C, vector<double>& kvc) {
        /*
            I just find the cut point must be int ......., so corret them here.
        */
        int x0 = (int)(p0.x + .5);
        int y0 = (int)(p0.y + .5);

        A = B = C = 0;
        rep(i, l, r) {
            const int& id = cid[i];
            const int sz = SZ(pid[id]);
            rep(j, 0, sz) {
                const int& k = pid[id][j];
                updateCoef(x0, y0, pts[k], A, B, C);
            }
        }

        getEquationK(A, B, C, kvc);
    }

    /**
        \brief get the best split due to `W` function and best cut point.
    */
    double getBestK(LL A, LL B, LL C, vector<double>& kvc) {
        double mn = 0;
        int sz = SZ(kvc), idx = -1;

        #ifdef LOCAL_DEBUG
        assert(sz > 0);
        #endif

        rep(i, 0, sz) {
            const double& k = kvc[i];
            double tmp = (A*k*k + B*k + C) / (k*k+1);
            if (idx==-1 || dcmp(tmp-mn)>0) {
                mn = tmp;
                idx = i;
            }
            #ifdef LOCAL_DEBUG
                fprintf(logout, "k = %.3lf, w = %.6lf\n", k, tmp);
                fflush(logout);
            #endif
        }

        return kvc[idx];
    }

	/**
		\breif Due IPoint is needed, then we need to find the most similar IPoint.
	*/
	void getIPoint(Point& p, double k, Cut_t& ct) {
		// int base = 1e3;
		// double b = p.y - k * p.x;

		// if (dcmp(k) <= 0) {
			// while (base<=1000000 && k*base+b > 0x3f3f3f3f)	base *= 10;
		// } else {
			// while (base>0 && k*base+b > 0x3f3f3f3f)	base /= 10;
		// }

		// #ifdef LOCAL_DEBUG
			// assert(base > 0 && base<=1000000);
		// #endif
		// ct.a.x = (int)base;
		// ct.a.y = (int)(k*base+b + .5);

		// if (dcmp(k) <= 0) {
			// base *= 5;
		// } else {
			// base /= 5;
		// }
		//base += 10;
		// ct.b.x = (int)base;
		// ct.b.y = (int)(k*base+b + .5);
		double b = p.y - k * p.x;
		int i;
		#ifdef LOCAL_DEBUG
		int cnt = 0;
		#endif
		
		for (i=0; i<=1024; ++i) {
			double y = k*i+b;
			if (y>=0 && y<=1024) {
				ct.a.x = i;
				ct.a.y = (int)(k*i+b);
				#ifdef LOCAL_DEBUG
				++cnt;
				#endif
				break;
			}
		}
		
		for (i=1024; i>=0; --i) {
			double y = k*i+b;
			if (y>=0 && y<=1024) {
				ct.b.x = i;
				ct.b.y = (int)(k*i+b);
				#ifdef LOCAL_DEBUG
				++cnt;
				#endif
				break;
			}
		}
		
		#ifdef LOCAL_DEBUG
		assert(cnt >= 2);
		#endif
	}

    /**
        \brief make a cut to split two circles
            due to relative position of these two circles.
    */
    Cut_t splitTwoCircle(int l, int r, int idx, int idx_) {
        Circle &c1 = cir[cid[idx]];
        Circle &c2 = cir[cid[idx_]];
        Cut_t ret;
        int status;
        vector<Point> pvc;
        vector<double> kvc;
        LL A, B, C;

        Point p0 = getBestCutPoint(c1, c2, status, pvc);
        getExtremeK(l, r, p0, A, B, C, kvc);

        if (status == 2) {
            // intersect
            Point p = pvc[0];
            // double ang1 = Angle(p-c1.c, c2.c-c1.c);
            // double ang2 = Angle(p-c2.c, c1.c-c2.c);
            // double k1 = tan(ang1);
            // double k2 = tan(ang2);
            double k1 = (c1.c.y-p.y) / (p.x-c1.c.x);
            double k2 = (c2.c.y-p.y) / (p.x-c2.c.x);
            kvc.pb(k1);
            kvc.pb(k2);

        } else if (status == 1) {
            // tangent
            double ang = atan((c1.c.y-c2.c.y) / (double)(c1.c.x-c2.c.x)) * 180 / PI;
            if (ang < 0)    ang += 180.0;
            double lbound = 75, rbound = 120;
            double k1 = tan((lbound + ang) / 180.0 * PI);
            double k2 = tan((rbound + ang) / 180.0 * PI);
            kvc.pb(k1);
            kvc.pb(k2);

        } else if (status == -1) {
            // separated
            double k1 = (pvc[0].y-pvc[1].y) / (pvc[1].x -pvc[0].x);
            double k2 = (pvc[2].y-pvc[3].y) / (pvc[3].x -pvc[2].x);
            kvc.pb(k1);
            kvc.pb(k2);

        } else if (status == -2) {
            // cover
            double ang = atan((c1.c.y-c2.c.y) / (double)(c1.c.x-c2.c.x)) * 180 / PI;
            if (ang < 0)    ang += 180.0;
            double lbound = 75, rbound = 105;
            double k1 = tan((lbound + ang) / 180.0 * PI);
            double k2 = tan((rbound + ang) / 180.0 * PI);
            kvc.pb(k1);
            kvc.pb(k2);

        }
        #ifdef LOCAL_DEBUG
        else {
            assert(0/*never goes there*/);
        }
        #endif

        double k = getBestK(A, B, C, kvc);
		getIPoint(p0, k, ret);

        return ret;
    }

    /**
        \brief update the plant because of the cut.
    */
    int updatePlant(int l, int r) {
		#ifdef LOCAL_DEBUG
		assert(SZ(ans) > 0);
		#endif
		Segment seg = (*ans.rbegin()).toSegment();

		int ll = l, rr = r - 1;

		while (ll <= rr) {
			#ifdef DEBUG
				// printf("ll = %d, rr = %d\n", ll, rr);
				// fflush(stdout);
			#endif
			while (ll<rr && seg.cmp(cir[cid[ll]])<0)
				++ll;
			while (rr>ll && seg.cmp(cir[cid[rr]])>=0)
				--rr;
			if (ll >= rr)
				break;
			swap(cid[ll], cid[rr]);
		}
		#ifdef DEBUG
			// printf("ll = %d, rr = %d\n", ll, rr);
			// fflush(stdout);
		#endif

		return ll;
    }

	/**
		\brief update the root because of the current cut.
	*/
	void updateRoot(int l, int r, int mid) {
		/**
			update the root due to the relative position to the cut with the center of circle.
				Obviously, it's just a similar to accurate.
		*/
		Segment seg = (*ans.rbegin()).toSegment();

		rep(i, l, mid) {
			const int& id = cid[i];
			int sz = SZ(pid[id]), n = 1;
			rep(j, 1, sz) {
				const int& k = pid[id][j];
				if (seg.cmp(pts[k]) < 0)
					pid[id][n++] = k;
			}
			pid[id].resize(n);
		}

		rep(i, mid, r) {
			const int& id = cid[i];
			int sz = SZ(pid[id]), n = 1;
			rep(j, 1, sz) {
				const int& k = pid[id][j];
				if (seg.cmp(pts[k]) >= 0)
					pid[id][n++] = k;
			}
			pid[id].resize(n);
		}
	}

    /**
        \brief split the plants using Divide and Conquer.
        \prop How to conquer???
    */
    void dfs_split(int l, int r) {
        if (r-l <= 1) return ;

        /**
            \step 1: calculate the median distance from root to o.
        */
        calRadius(l, r);

        /**
            \step 2: split the two biggest circle
        */
        int idx1, idx2;
        chooseTwoCircle(l, r, idx1, idx2);
        Cut_t ct = splitTwoCircle(l, r, idx1, idx2);
        ans.pb(ct);

        /**
            \step 3: update the position of the plant
				due to the position to the cut
        */
        int mid = updatePlant(l, r);
		#ifdef LOCAL_DEBUG
		assert(mid>l && mid<r);
		#endif

		/**
			\step 4: update the root
		*/
		updateRoot(l, r, mid);

		/**
			\step 5: Divide
		*/
		dfs_split(l, mid);
		dfs_split(mid, r);

		/**
			\step 6: Conquer later.
		*/
    }

    /**
        \brief Traser's v1.0 algorithm to make the cuts.
    */
	vi makeCuts_Trasier_v1(int NP, vi points, vi roots) {
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
        rep(i, 0, NP)   cid[i] = i;
        dfs_split(0, NP);

        /**
            \step 4:
        */

        vi ret;
        int sz = SZ(ans);
        rep(i, 0, sz) {
            ret.pb(ans[i].a.x);
            ret.pb(ans[i].a.y);
            ret.pb(ans[i].b.x);
            ret.pb(ans[i].b.y);
        }
        #ifdef LOCAL_DEBUG
        fprintf(logout, "|ans| = %d\n", (int)SZ(ret));
        #endif

        return ret;
	}
};


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
    #ifdef LOCAL_DEBUG
		// freopen("data.in", "r", stdin);
		// freopen("data.out", "w", stdout);
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

    cout << ret.size() << endl;
    for (int i = 0; i < (int)ret.size(); ++i) {
        cout << ret[i] << endl;
    }
    cout.flush();
    close_log();

	return 0;
}

