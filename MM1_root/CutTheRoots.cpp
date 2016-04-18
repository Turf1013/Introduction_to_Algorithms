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

#define LOCAL_DEBUG

typedef struct Point {
    double x, y;

    Point() {}
    Point(double x, double y): x(x), y(y) {}

    bool operator== (const Point& oth) const {
        return x==oth.x && y==oth.y;
    }

    bool operator< (const Point& oth) const {
        return x<oth.x || (x==oth.x && y<oth.y);
    }

} Point;

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

} Circle;

const double eps = 1e-7;
const int maxp = 110
const int maxrt = 105010;
int cid[maxp];
double rad[maxrt];
int pre[maxrt];
Point pts[maxrt+maxp];
vi pid[maxp];

int dcmp(double x) {
    if (fabs(x) < eps)  return 0;
    return x<0 ? -1:1;
}

class CutTheRoots {
public:
    int NR, npt;
    vector<Circle> cir;

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
        cir.clear();

        #ifdef LOCAL_DEBUG
        assert(npt < maxrt+maxp);
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
        int idx;

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
        \brief make a cur to split two circles 
            due to relative position of these two circles.
    */
    void splitTwoCircle(int idx, int idx_) {

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
        splitTwoCircle(idx1, idx2);

        /**
            \step 3: update the root of plat
        */
        updateRoot(l, r);
    }
	
    /**
        \brief Traser's v1.0 algorithm to make the cuts.
    */
	vi makeCuts_Trasier_v1(int NP, vi points, vi roots) {
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
        rep(i, 0, NP)   cid[i] = NP;
        dfs_split(0, NP);

        calcRadius();
	}
};


// -------8<------- end of solution submitted to the website -------8<-------

template<class T> void getVector(vector<T>& v) {
    for (int i = 0; i < v.size(); ++i)
        cin >> v[i];
}

int main() {
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
    for (int i = 0; i < ret.size(); ++i) {
        cout << ret[i] << endl;
    }
    cout.flush();

	return 0;
}

