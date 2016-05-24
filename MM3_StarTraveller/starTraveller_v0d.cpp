/**
    \author Trasier
    \source TopCoder-MM-StarTraverller
    \data   2016-05-17
*/
#include <bits/stdc++.h>
using namespace std;

#define sti             set<int>
#define stpii           set<pair<int, int> >
#define mpii            map<int,int>
#define vi              vector<int>
#define pii             pair<int,int>
#define pdi				pair<double,int>
#define vpii            vector<pair<int,int> >
#define rep(i, a, n)    for (int i=a;i<n;++i)
#define per(i, a, n)    for (int i=n-1;i>=a;--i)
#define clr             clear
#define pb              push_back
#define mp              make_pair
#define fir             first
#define sec             second
#define all(x)          (x).begin(),(x).end()
#define SZ(x)           ((int)(x).size())

#define DEBUG
#define LOCAL_DEBUG

FILE *logout;

struct Star_t {
    int x, y;

	bool operator< (const Star_t& o) const {
		if (x != o.x) return x < o.x;
		return y < o.y;
	}

	bool operator== (const Star_t& o) const {
		return x==o.x && y==o.y;
	}

    void print(FILE *out=stdout) const {
        fprintf(out, "x = %d, y = %d\n", x, y);
        fflush(out);
    }
};

struct Ufo_t {
    int idx[3];

    void dump(map<pii,int>& decay1, map<pii,int>& decay2) {
        ++decay1[mp(idx[0], idx[1])];
        ++decay2[mp(idx[1], idx[2])];
    }

    void print(FILE *out=stdout) const {
        fprintf(out, "%d -> %d -> %d\n", idx[0], idx[1], idx[2]);
        fflush(out);
    }
};

struct Node_t {
	int idx;
	double cufo;
    double gain, cost;
    vi path;

    vi::const_reverse_iterator rbegin() const{
    	return path.rbegin();
    }

    vi::reverse_iterator rbegin() {
    	return path.rbegin();
    }

    bool empty() {
        return SZ(path) == 0;
    }

    void clear() {
        path.clr();
    }

    size_t size() const {
    	return SZ(path);
    }

    void push_back(int x) {
        path.pb(x);
    }

    void print(FILE *out=stdout) const {
    	int sz = SZ(path);
        fprintf(out, "No. = %d, cost = %.6lf, gain = %.6lf, Nhops = %d: ", idx, cost, gain, sz-1);
        rep(i, 0, sz) {
            if (i == 0)
                fprintf(out, "%d", path[i]);
            else
                fprintf(out, "->%d", path[i]);
        }
        fprintf(out, "\n");
        fflush(out);
    }

    bool operator< (const Node_t& o) const {
		if (cost != o.cost)
			return cost < o.cost;
		else
			return gain > o.gain;
    }

    int operator[] (const int idx) const {
        return path[idx];
    }
};

struct path_t {
	double cost, gain;
	vi path;

	void print(FILE* out=stdout) const {
		fprintf(out, "cost = %.6lf\n", cost);
		per(i, 0, SZ(path)) {
			fprintf(out, "->%d", path[i]);
		}
		fprintf(out, "\n");
		fflush(out);
	}

	size_t size() const {
		return SZ(path);
	}

	bool empty() {
		return path.empty();
	}

	bool empty() const {
		return path.empty();
	}

	void pop_back() {
		path.pop_back();
	}

	void push_back(const int idx) {
		path.pb(idx);
	}

	void clear() {
		path.clr();
	}

	void resize(const int n) {
		path.resize(n);
	}

	vi::reverse_iterator rbegin() {
		return path.rbegin();
	}

	vi::const_reverse_iterator rbegin() const {
		return path.rbegin();
	}

	int& operator[](const int idx) {
		return path[idx];
	}

	const int& operator[](const int idx) const {
		return path[idx];
	}
};

const double POS_INF = 1e16;
const double NEG_INF = -POS_INF;
const int maxn = 2005;
const char *LOG_FILENAME = "starlog.out";
int NStars, NShips, NUfos;
double M[maxn][maxn], Base[25];
bool visit[maxn], visit2[maxn];
Star_t stars[maxn];
Ufo_t ufos[maxn/100+5];
int ships[15];
path_t paths[15];
vpii E1[maxn], E1_[maxn];
vpii E2[maxn], E2_[maxn];
map<pii, int> decay1, decay2;
set<int> ust, _ust;

inline void init_log() {
    logout = fopen(LOG_FILENAME, "w");
}

inline void close_log() {
    fclose(logout);
}

double Length(const Star_t& sa, const Star_t& sb) {
    return sqrt((sa.x-sb.x)*(sa.x-sb.x) + (sa.y-sb.y)*(sa.y-sb.y));
}

double Length(const int a, const int b) {
    return M[a][b];
}

const double tolLength = 20.0;
int stillBound = 20;
const double eps = 1e-6;
class StarTraveller {
public:
    int NTurns;
    int mark[maxn], still[maxn];
	bool taken[maxn];
	bool busy[15], more[15];
	double mnCost[maxn];
	vector<Node_t> vnode;
	vi neighbours;
	vi nxtHop;

    void Init() {
        memset(mark, -1, sizeof(mark));
        NTurns = 0;
        ust.clr();
        _ust.clr();
        rep(i, 0, NStars) {
            _ust.insert(i);
            M[i][i] = 0.;
            rep(j, 0, i)
                M[i][j] = M[j][i] = Length(stars[i], stars[j]);
        }
        Base[0] = 1;
        rep(i, 1, 11) Base[i] = Base[i-1] * 0.001;
		memset(more, false, sizeof(more));
		memset(busy, false, sizeof(busy));
        memset(visit2, false, sizeof(visit2));
		memset(still, 0, sizeof(still));
		rep(i, 0, NStars) mnCost[i] = POS_INF;
		nxtHop.clr();
    }

    /**
        \brief  init the coordinate of all stars
        \return useless
    */
    int init(vector<int> vstar) {
        const int sz = SZ(vstar);
        NStars = sz >> 1;

        rep(i, 0, NStars) {
            stars[i].x = vstar[i<<1];
            stars[i].y = vstar[(i<<1)|1];
        }

        Init();

        return 0;
    }

    /**
        \brief  initialize decay with current vufo
    */
    void init_ufos(const vi& vufo) {
        const int sz = SZ(vufo);
        NUfos = sz / 3;
        map<pii,int>::iterator iter;

		for (iter=decay1.begin(); iter!=decay1.end(); ++iter) {
            E1[iter->fir.fir].clr();
            E1_[iter->fir.sec].clr();
        }

        for (iter=decay2.begin(); iter!=decay2.end(); ++iter) {
            E2[iter->fir.fir].clr();
            E2_[iter->fir.sec].clr();
        }

        decay1.clr();
        decay2.clr();

        for (int i=0,j=0; i<NUfos; ++i,j+=3) {
            ufos[i].idx[0] = vufo[j];
            ufos[i].idx[1] = vufo[j+1];
            ufos[i].idx[2] = vufo[j+2];
            ufos[i].dump(decay1, decay2);
			#ifdef DEBUG
			printf("[UFO-%d] %d->%d->%d\n", i+1, vufo[j], vufo[j+1], vufo[j+2]);
			#endif
        }

        for (iter=decay1.begin(); iter!=decay1.end(); ++iter) {
            E1[iter->fir.fir].pb(mp(iter->fir.sec, iter->sec));
            E1_[iter->fir.sec].pb(mp(iter->fir.fir, iter->sec));
        }

        for (iter=decay2.begin(); iter!=decay2.end(); ++iter) {
            E2[iter->fir.fir].pb(mp(iter->fir.sec, iter->sec));
            E2_[iter->fir.sec].pb(mp(iter->fir.fir, iter->sec));
        }
    }

    /**
        \brief initialize the ship
    */
    void init_ships(const vi& vship) {
        const int sz = SZ(vship);
        NShips = sz;

        rep(i, 0, sz) ships[i] = vship[i];
    }

    /**
        \brief  update the visit set according current turn
    */
    void Update(const vi& vnxt) {
        const int sz = SZ(vnxt);

        #ifdef DEBUG
        assert(sz == NShips);
        rep(i, 0, sz) assert (vnxt[i]>=0 && vnxt[i]<NStars);
        #endif

        rep(i, 0, sz) {
            const int v = vnxt[i];
            if (!visit2[v]) {
                visit2[v] = true;
                ust.insert(v);
                _ust.erase(v);
				more[i] = false;
            }
            if (!paths[i].empty()) {
				paths[i].cost -= Hop1(ships[i], v);
                paths[i].pop_back();
			}
        }
        ++NTurns;
    }

	double calcCufo(const int c, const int potential=0) {
		return c * 0.7 + potential * 1.0;
	}

	double Hop1(const int u, const int v) {
		return Length(u, v) * decay1[mp(u, v)];
	}

	double Hop2(const int u, const int vv, const int v) {
		return Length(u, vv) * decay1[mp(u, vv)] + Length(vv, v) * decay2[mp(vv, v)];
	}

	/**
		\brief calculate the case of `1-hop`
	*/
	void calcHop1(const int idx, const int v) {
		const int u = ships[idx];
		const int c = decay1[mp(u, v)];
		Node_t nd;

		nd.idx = idx;
		nd.pb(u);
		nd.pb(v);
		nd.cost = Length(u, v) * Base[c];
		nd.gain = Length(u, v) - nd.cost;
		nd.cufo = calcCufo(c, SZ(E2[v]));
		vnode.pb(nd);
	}

	/**
		\brief calculate the case of `2-hop`
	*/
	void calcHop2(const int idx, const int v) {
		const int u = ships[idx];
		const vpii& e1 = E1[u];
		const int sz1 = SZ(e1);
		int c1, c2;
		Node_t nd;
		double& gain = nd.gain;
		double& cost = nd.cost;
		double& cufo = nd.cufo;
		double tmp;

		nd.idx = idx;

		rep(i, 0, sz1) {
			const int a = e1[i].fir;
			// We had already visited v, why not visit again?
			c1 = e1[i].sec;
			c2 = decay2[mp(a, v)];
			if (visit[a])
				tmp = Length(u, v);
			else
				tmp = Length(u, a) + Length(a, v);
			cost = Length(u, a) * Base[c1] + Length(a, v) * Base[c2];
			gain = tmp - cost;
			cufo = calcCufo(c1+c2, SZ(E2_[v]));
			nd.clr();
			nd.pb(u);
			nd.pb(a);
			nd.pb(v);
			vnode.pb(nd);
		}

		// other option is stay at u
		{
			const int a = u;
			c1 = decay1[mp(u, a)];
			c2 = decay2[mp(a, v)];
			if (visit[a])
				tmp = Length(u, v);
			else
				tmp = Length(u, a) + Length(a, v);
			cost = Length(u, a) * Base[c1] + Length(a, v) * Base[c2];
			gain = tmp - cost;
			cufo = calcCufo(c1+c2, SZ(E2_[v]));
			nd.clr();
			nd.pb(u);
			nd.pb(a);
			nd.pb(v);
			vnode.pb(nd);
		}

		const vpii& e2 = E1_[v];
		const int sz2 = SZ(e2);
		rep(i, 0, sz2) {
            const int a = e2[i].fir;
            c2 = e2[i].sec;
            c1 = decay1[mp(u, a)];
			if (visit[a])
				tmp = Length(u, v);
			else
				tmp = Length(u, a) + Length(a, v);
			cost = Length(u, a) * Base[c1] + Length(a, v) * Base[c2];
			gain = tmp - cost;
			cufo = calcCufo(c1+c2, SZ(E2_[v]));
			nd.clr();
			nd.pb(u);
			nd.pb(a);
			nd.pb(v);
			vnode.pb(nd);
        }
	}

	void calcHop2(const int idx, const int vv, const int v) {
		const int u = ships[idx];
		const int c1 = decay1[mp(u, vv)];
		const int c2 = decay2[mp(vv, v)];
		Node_t nd;

		nd.idx = idx;
		nd.cost = Length(u, vv) * Base[c1] + Length(vv, v) * Base[c2];
		nd.gain = Length(u, vv) + Length(vv, v) - nd.cost;
		nd.cufo = calcCufo(c1+c2, SZ(E2_[v]));
		nd.pb(u);
		nd.pb(vv);
		nd.pb(v);
	}

	/**
        \brief calculate the gain of hop3, there must meet UFO between medium node and end-points
            `u -> a -> b -> v`
    */
    void calcHop3(const int idx, const int v) {
		const int u = ships[idx];
		Node_t nd;
        const vpii& e1 = E1[u];
        const int sz1 = SZ(e1);
        double tmp;
        int c1, c2;
		double& gain = nd.gain;
		double& cost = nd.cost;
		double& cufo = nd.cufo;

		nd.idx = idx;

        rep(i, 0, sz1) {
            const int a = e1[i].fir;
            c1 = e1[i].sec;
            const vpii& e2 = E2[a];
            const int sz2 = SZ(e2);
            rep(j, 0, sz2) {
                const int b = e2[j].fir;
                c2 = e2[j].sec;
				if (visit[a] && visit[b]) {
					tmp = Length(u, v);
				} else if (visit[a] && !visit[b]) {
					tmp = Length(u, b) + Length(b, v);
				} else if (!visit[a] && visit[b]) {
					tmp = Length(u, a) + Length(a, v);
				} else {
					tmp = Length(u, a) + Length(a, b) + Length(b, v);
				}
                cost = Length(u, a) * Base[c1] + Length(a, b) * Base[c2] + Length(b, v);
				gain = tmp - cost;
				cufo = calcCufo(c1+c2);
				nd.clr();
				nd.pb(u);
				nd.pb(a);
				nd.pb(b);
				nd.pb(v);
            }
        }

		// other option is stay at u first
		{
			const int a = u;
			c1 = decay1[mp(u, a)];
			const vpii& e2 = E2[a];
			const int sz2 = SZ(e2);
			rep(j, 0, sz2) {
				const int b = e2[j].fir;
				if (b == v) continue;
				c2 = e2[j].sec;
				if (visit[a] && visit[b]) {
					tmp = Length(u, v);
				} else if (visit[a] && !visit[b]) {
					tmp = Length(u, a) + Length(a, v);
				} else if (!visit[a] && visit[b]) {
					tmp = Length(u, b) + Length(b, v);
				} else {
					tmp = Length(u, a) + Length(a, b) + Length(b, v);
				}
				cost = Length(u, a) * Base[c1] + Length(a, b) * Base[c2] + Length(b, v);
				gain = tmp - cost;
				cufo = calcCufo(c1+c2);
				nd.clr();
				nd.pb(u);
				nd.pb(a);
				nd.pb(b);
				nd.pb(v);
			}
		}
    }

	void calcHop3(const int idx, const int vv, const int v) {
		const int u = ships[idx];
		int c1, c2;
		Node_t nd;
		double tmp;
		double& gain = nd.gain;
		double& cost = nd.cost;
		double& cufo = nd.cufo;

		nd.idx = idx;

		// `u ~> a -> vv ->v`
		{
			const vpii& e1 = E1[u];
			const int sz1 = SZ(e1);

			rep(i, 0, sz1) {
				const int a = e1[i].fir;
				c1 = e1[u].sec;
				c2 = decay2[mp(a, vv)];
				if (visit[a]) {
					tmp = Length(u, vv) + Length(vv, v);
				} else {
					tmp = Length(u, a) + Length(a, vv) + Length(vv, v);
				}
				cost = Length(u, a) * Base[c1] + Length(a, vv) * Base[c2] + Length(vv, v);
				gain = tmp - cost;
				cufo = calcCufo(c1+c2);
				nd.clr();
				nd.pb(u);
				nd.pb(a);
				nd.pb(vv);
				nd.pb(v);
			}
		}

		// `u -> a ~> vv -> v`
		{
			const vpii& e2 = E2_[u];
			const int sz2 = SZ(e2);

			rep(i, 0, sz2) {
				const int a = e2[i].fir;
				c2 = e2[i].sec;
				c1 = decay1[mp(u, a)];
				if (visit[a]) {
					tmp = Length(u, vv) + Length(vv, v);
				} else {
					tmp = Length(u, a) + Length(a, vv) + Length(vv, v);
				}
				cost = Length(u, a) * Base[c1] + Length(a, vv) * Base[c2] + Length(vv, v);
				gain = tmp - cost;
				cufo = calcCufo(c1+c2);
				nd.clr();
				nd.pb(u);
				nd.pb(a);
				nd.pb(vv);
				nd.pb(v);
			}
		}
	}

	/**
		\brief	judge current ship is busy
	*/
	bool judgeBusy(const int idx) {
		if (paths[idx].empty()) return false;
		// if (!more[idx]) return true;

		const int u = ships[idx];
		const int v = *paths[idx].rbegin();

		return !visit[v] && decay1[mp(u, v)]>0;
	}

	/**
		\brief	generate next turn's position
	*/
	void InitNextTurn() {
		memcpy(visit, visit2, sizeof(visit2));

		rep(i, 0, NShips) {
			if (paths[i].empty()) {
				// the better choice than stay is moving along with UFO.
				// int mx = -1, v = ships[i];
				// const vpii& e1 = E1[ships[i]];
				// const int sz = SZ(e1);
				// rep(j, 0, sz) {
					// if (e1[j].sec > mx) {
						// mx = e1[j].sec;
						// v = e1[j].fir;
					// } else if (e1[j].sec==mx && Length(ships[i],e1[j].fir)<Length(ships[i],v)) {
						// v = e1[j].fir;
					// }
				// }
				// nxtHop[i] = v;
				nxtHop[i] = ships[i];
			} else {
				nxtHop[i] = *paths[i].rbegin();
			}

			busy[i] = judgeBusy(i);
			if (busy[i]) {
				// update visit
				const int sz = SZ(paths[i]);
				int u = ships[i], v, c = 0;
				per(j, 0, sz) {
					v = paths[i][j];
					if (c==0 && !visit[v] && decay1[mp(u, v)]>0) visit[v] = true;
					if (c==1 && !visit[v] && decay2[mp(u, v)]>0) visit[v] = true;
					if (++c == 2) break;
					u = v;
				}
			}
		}
	}

	/**
		\brief	choose extreme best and worst stars
	*/
	void ChooseExtremeStars() {
		vi unvisit;
        rep(i, 0, NStars) {
			if (!visit[i])
				unvisit.pb(i);
        }
		const int sz_unvisit = SZ(unvisit);

		memset(taken, false, sizeof(taken));

		// choose some from ufo's path
		rep(i, 0, NUfos) {
			if (!visit[ufos[i].idx[1]]) taken[ufos[i].idx[1]] = true;
			if (!visit[ufos[i].idx[2]]) taken[ufos[i].idx[2]] = true;
		}

		// choose node close to ufo's
		int topk = 5;
		priority_queue<pdi, vector<pdi>, less<pdi> > q;

		rep(i, 0, NUfos) {
			rep(k, 1, 3) {
				#ifdef DEBUG
				assert(q.empty());
				#endif
				rep(j, 0, sz_unvisit) {
					double tmp = Length(ufos[i].idx[k], unvisit[j]);
					if (SZ(q) < topk) {
						q.push(mp(tmp, unvisit[j]));
					} else if (tmp < q.top().fir) {
						q.pop();
						q.push(mp(tmp, unvisit[j]));
					}
				}
				while (!q.empty()) {
					taken[q.top().sec] = true;
					q.pop();
				}
			}
		}

		// choose star close to or futher to ships
		priority_queue<pdi, vector<pdi>, greater<pdi> > Q;
		topk = 5;
		rep(i, 0, NShips) {
			#ifdef DEBUG
			assert(q.empty() && Q.empty());
			#endif
			rep(j, 0, sz_unvisit) {
				double tmp = Length(ships[i], unvisit[j]);
				if (SZ(q) < topk) {
					q.push(mp(tmp, unvisit[j]));
				} else if (tmp < q.top().fir) {
					q.pop();
					q.push(mp(tmp, unvisit[j]));
				}

				if (SZ(Q) < topk) {
					Q.push(mp(tmp, unvisit[j]));
				} else if (tmp > Q.top().fir) {
					Q.pop();
					Q.push(mp(tmp, unvisit[j]));
				}
			}

			while (!q.empty()) {
				taken[q.top().sec] = true;
				q.pop();
			}
			while (!Q.empty()) {
				taken[Q.top().sec] = true;
				Q.pop();
			}
		}

		neighbours.clr();
		rep(j, 0, sz_unvisit) {
			if (taken[unvisit[j]])
				neighbours.pb(unvisit[j]);
		}
	}

	/**
		\brief 	generate next hop
	*/
	void GenNextHop() {
		const int sz = SZ(neighbours);

		vnode.clr();

		rep(i, 0, NShips) {
			if (busy[i]) continue;
			rep(j, 0, sz) {
				const int v = neighbours[j];

				/**
					\case 1: one hop
				*/
				calcHop1(i, v);

				/**
					\case 2: two hop
				*/
				calcHop2(i, v);

				/**
					\case 3: three hop
				*/
				calcHop3(i, v);
			}
		}
	}

	double BestNode(const Node_t& nd) {
		if (SZ(ust) <= NStars*0.2)
			return nd.cost<10 || nd.cufo>=3 || nd.gain>=nd.cost*0.7;
		if (SZ(ust) <= NStars*0.5)
			return nd.cost<50 || nd.cufo>=2 || nd.gain>=nd.cost*0.5;
		if (SZ(ust) <= NStars*0.8)
			return nd.cost<150 || nd.cufo>=1 || nd.gain>=nd.cost*0.3;
		if (SZ(ust) <= NStars*0.9)
			return nd.cost<300 || nd.cufo>=1 || nd.gain>=nd.cost*0.1;
		return false;
	}

	bool comp(const Node_t& a, const Node_t& b) {
		const int sza = SZ(a) - 1;
		const int szb = SZ(b) - 1;
		const int va = *a.rbegin();
		const int vb = *a.rbegin();
		int ca = 0, cb = 0;

		if (sza == 1) ca = SZ(E2[va]);
		if (szb == 1) cb = SZ(E2[vb]);
		if (sza == 2) ca = SZ(E2_[va]);
		if (szb == 2) cb = SZ(E2_[vb]);

		if (ca != cb) return ca < cb;
		return a.cost < b.cost;
	}

	bool judge(const Node_t& nd) {
		const int sz = SZ(nd);

		rep(i, 1, sz) {
			if (!visit[nd[i]] && !taken[nd[i]])
				return true;
		}

		return false;
	}

	void updateTaken(const Node_t& nd) {
		const int sz = SZ(nd);

		rep(i, 1, sz) taken[nd[i]] = true;
	}

	void ChooseNextTurn() {
		int topk = NShips;

		vector<Node_t> bvc;
		const int sz_vnode = SZ(vnode);

		rep(i, 0, sz_vnode) {
			if (BestNode(vnode[i]))
				bvc.pb(vnode[i]);
		}
		const int sz_bvc = SZ(bvc);
		sort(all(bvc));
		sort(all(vnode));

		#ifdef DEBUG
		printf("SZ(Best-vnode) = %d, SZ(vnode) = %d\n", SZ(bvc), SZ(vnode));
		#endif

		memset(taken, false, sizeof(taken));

		rep(i, 0, sz_bvc) {
			const int idx = bvc[i].idx;
			if (mark[idx] == NTurns) continue;
			if (!judge(bvc[i])) continue;
			#ifdef DEBUG
			bvc[i].print();
			#endif
			mark[idx] = NTurns;
			busy[idx] = true;
			more[idx] = false;
			paths[idx].clr();
			paths[idx].cost = bvc[i].cost;
			paths[idx].gain = bvc[i].gain;
			per(j, 1, SZ(bvc[i])) {
				paths[idx].pb(bvc[i][j]);
			}
			nxtHop[idx] = *paths[idx].rbegin();
			if (--topk == 0)
				break;
		}

		/**
			\if enough turns left we choose some ufo path to visit
		*/
		if (NUfos>0 && (NStars*4-NTurns)>SZ(_ust)*3)  {
			rep(i, 0, NShips) {
				if (busy[i] || !paths[i].empty()) continue;

				double mn = POS_INF, tmp;

				rep(j, 0, NUfos) {
					tmp = Hop1(ships[i], ufos[j].idx[1]);
					if (tmp < tolLength) {
						paths[i].cost = tmp;
						paths[i].gain = -10000;
						paths[i].pb(ufos[j].idx[1]);
						nxtHop[i] = ufos[j].idx[1];
						#ifdef DBEUG
						paths[i].print();
						#endif
						break;
					}
					mn = min(tmp, mn);
				}
				if (!paths[i].empty()) continue;

				rep(j, 0, NUfos) {
					tmp = Hop2(ships[i], ships[i], ufos[j].idx[2]);
					if (tmp < tolLength) {
						paths[i].cost = tmp;
						paths[i].gain = -10000;
						paths[i].pb(ufos[j].idx[2]);
						paths[i].pb(ships[i]);
						#ifdef DBEUG
						paths[i].print();
						#endif
						nxtHop[i] = ships[i];
						break;
					}
					mn = min(tmp, mn);
					tmp = Hop2(ships[i], ufos[j].idx[2], ufos[j].idx[2]);
					if (tmp < tolLength) {
						paths[i].cost = tmp;
						paths[i].gain = -10000;
						paths[i].pb(ufos[j].idx[2]);
						paths[i].pb(ufos[j].idx[2]);
						#ifdef DBEUG
						paths[i].print();
						#endif
						nxtHop[i] = ufos[j].idx[2];
						break;
					}
					mn = min(tmp, mn);
				}

				if (!paths[i].empty()) continue;
				nxtHop[i] = ships[i];
				#ifdef DEBUG
				printf("still[%d] = %d\n", i, still[i]);
				#endif
				if (++still[i] == stillBound) {
					still[i] = 0;
					mn += eps;
					rep(j, 0, NUfos) {
						tmp = Hop1(ships[i], ufos[j].idx[1]);
						if (tmp < mn) {
							paths[i].cost = tmp;
							paths[i].gain = -10000;
							paths[i].pb(ufos[j].idx[1]);
							nxtHop[i] = ufos[j].idx[1];
							#ifdef DBEUG
							paths[i].print();
							#endif
							break;
						}
					}
					if (paths[i].empty()) {
						rep(j, 0, NUfos) {
							tmp = Hop2(ships[i], ships[i], ufos[j].idx[2]);
							if (tmp < mn) {
								paths[i].cost = tmp;
								paths[i].gain = -10000;
								paths[i].pb(ufos[j].idx[2]);
								paths[i].pb(ships[i]);
								#ifdef DBEUG
								paths[i].print();
								#endif
								nxtHop[i] = ships[i];
								break;
							}
							tmp = Hop2(ships[i], ufos[j].idx[2], ufos[j].idx[2]);
							if (tmp < tolLength) {
								paths[i].cost = tmp;
								paths[i].gain = -10000;
								paths[i].pb(ufos[j].idx[2]);
								paths[i].pb(ufos[j].idx[2]);
								#ifdef DBEUG
								paths[i].print();
								#endif
								nxtHop[i] = ufos[j].idx[2];
								break;
							}
						}
					}
				}
			}

		} else {
			#ifdef DEBUG
			static bool flag = true;
			if (flag)
				printf("not enough turn\n");
			flag = false;
			#endif
			
			if (topk) {
				rep(i, 0, sz_vnode) {
					const int idx = vnode[i].idx;
					if (mark[idx] == NTurns) continue;
					if (!judge(vnode[i])) continue;
					#ifdef DEBUG
					vnode[i].print();
					#endif
					mark[idx] = NTurns;
					busy[idx] = true;
					more[idx] = false;
					paths[idx].clr();
					paths[idx].cost = vnode[i].cost;
					paths[idx].gain = vnode[i].gain;
					per(j, 1, SZ(vnode[i])) {
						paths[idx].pb(vnode[i][j]);
					}
					nxtHop[idx] = *paths[idx].rbegin();
					if (--topk == 0)
						break;
				}
			}
		}
	}

    /**
        \brief  make a valid hop according current layout
        \return vector<int> present the next move of ships
    */
    vi Hop() {
		if (SZ(nxtHop) != NShips)
			nxtHop.resize(NShips, 0);

        /**
            \step 1: using current position of ships to initialize `ret`
        */
		InitNextTurn();

		/**
			\step 2: choose Best and Worst unvisit node
		*/
		ChooseExtremeStars();

		/**
			\step 3: generate next hop
		*/
		GenNextHop();

		/**
			\step 4: choose next hop
		*/
		ChooseNextTurn();

		#ifdef DEBUG
		rep(i, 0, NShips)
			printf("%d-nxtHop: %d - > %d\n", i, ships[i], nxtHop[i]);
		#endif

        return nxtHop;
    }

    /**
        \brief  make a turn according current ufos' and ships' position.
        \return next position foreach ships
    */
    vector<int> makeMoves(vector<int> ufos, vector<int> ships) {
        init_ufos(ufos);
        init_ships(ships);
        vi ret = Hop();
        Update(ret);

        return ret;
    }
};
// -------8<------- end of solution submitted to the website -------8<-------

template <typename T>
void getVector(vector<T>& v) {
    for (int i = 0; i < v.size(); ++i)
        cin >> v[i];
}

struct Pnt {
	int x, y;
	bool visited;
	Pnt() {}
	Pnt(int x, int y) {
		this->x = x;
		this->y = y;
		visited = false;
	}

	bool operator== (const Pnt& o) const {
		return x==o.x && y==o.y;
	}
};

class StarTravellerVis {
public:
	static const int mod;
	int NStar, NShip, NUfo, NG;
	vector<Pnt> star;
	vi ship;
	vi ufoParm;
	vector<int> starParm;
	int *ufoRange;

	void generate(int seed) {
		srand(seed);

		if (seed == 1) {
			NStar = 20;
			NShip = 1;
			NUfo = 2;
			NG = 3;
		} else {
			NStar = 100 + rand()%1901;
			NShip = 1 + rand()%10;
			NUfo = rand()%(NStar/100);
			NG = 1 + rand()%16;
		}

		star.clr();
		ship.clr();
		ufoParm.clr();
		starParm.clr();

		ufoParm.resize(3*NUfo);

		printf("NStar = %d, NShip = %d, NUfo = %d\n", NStar, NShip, NUfo);

		// Generate stars
		// Generate galaxy center positions
		Pnt *galaxy = new Pnt[NG];
		rep(i, 0, NG) {
			galaxy[i].x = rand()%mod;
			galaxy[i].y = rand()%mod;
		}

		// Generate star locations
		rep(i, 0, NStar) {
			int x = 0, y = 0;
			int g = rand() % NG;
			do {
				x = rand()%100 + galaxy[g].x;
				y = rand()%100 + galaxy[g].y;
			} while (x<0 || y<0 || x>=mod || y>=mod);
			star.pb( Pnt(x, y) );
		}

		// Assign initial space ship locations
		rep(i, 0, NShip) {
			ship.pb( rand() % NStar );
		}

		// Generate UFO
		ufoRange = new int[NUfo];
		rep(i, 0, NUfo) {
			ufoRange[i] = 10 + rand() % (NStar / 10);
			ufoParm[i*3] = rand() % NStar;
		}
		calculateNextStar(1);
		calculateNextStar(2);

		// convert to parameter array
		rep(i, 0, NStar) {
			starParm.pb( star[i].x );
			starParm.pb( star[i].y );
		}
	}

	void calculateNextStar(int idx) {
		rep(i, 0, NUfo) {
			int from = ufoParm[i*3 + idx - 1];
			int bdst = 1<<30;
			int bj = rand() % NStar;
			// Pick [range] random stars and select the nearest one to travel to.
			rep(j, 0, ufoRange[i]) {
				int p = rand() % NStar;
				int dst = (star[p].x-star[from].x)*(star[p].x-star[from].x) + (star[p].y-star[from].y)*(star[p].y-star[from].y);
				if (dst<bdst && dst>0) {
					bdst = dst;
					bj = p;
				}
			}
			ufoParm[i*3+idx] = bj;
		}
	}

	double runTest(const int seed) {
		StarTraveller ST;
		generate(seed);
		int turns = 0;
		int visited = 0;
		double energy = 0.;

		ST.init(starParm);

		// Perform moves until all stars visited or number of maximum turns reached.
		while (turns<NStar*4 && visited<NStar) {
			vi ret;
			try {
				ret = ST.makeMoves(ufoParm, ship);
			} catch (...) {
				fprintf(stdout, "Move #%d: Failed to get result from makeMoves.", turns);
				return -1.0;
			}
			if (SZ(ret) != NShip) {
				fprintf(stdout, "Move #%d: Return should have one move for each ship. "
					"Length is %d and should be %d.", turns, SZ(ret), NShip);
				return -1.0;
			}

			int delta = 0;

			// move ship
			rep(i, 0, NShip) {
				if (ret[i]<0 || ret[i]>=NStar) {
					fprintf(stdout, "Move #%d: Return values should in the range of [0,%d]. "
									"Your value was %d.", turns, NStar-1, ret[i]);
					return -1.0;
				}

				if (star[ship[i]].x!=star[ret[i]].x || star[ship[i]].y!=star[ret[i]].y) {
					double dst = sqrt(
						(star[ship[i]].x-star[ret[i]].x)*(star[ship[i]].x-star[ret[i]].x) +
						(star[ship[i]].y-star[ret[i]].y)*(star[ship[i]].y-star[ret[i]].y)
					);
					for (int j=0; j<NUfo; ++j) {
						if (ufoParm[j*3]==ship[i] && ufoParm[j*3+1]==ret[i]) {
							dst *= 0.001;
						}
					}
					energy += dst;
				}


				ship[i] = ret[i];
				if (!star[ship[i]].visited) {
					star[ship[i]].visited = true;
					visited++;
					++delta;
				}
			}

			printf("Move #%d: visit %d more stars, energy = %.6lf.\n", turns, delta, energy);

			// move UFO
			for (int i=0; i<NUfo*3; i+=3) {
				ufoParm[i] = ufoParm[i+1];
				ufoParm[i+1] = ufoParm[i+2];
			}
			calculateNextStar(2);

			++turns;
		}

		if (visited != NStar) {
			fprintf(stdout, "All stars not visited after %d turns.", NStar*4);
			return -1.0;
		}

		printf("turns = %d\n", turns);
		return energy;
	}

};

const int StarTravellerVis::mod = 1024;

void debug(const int seed) {
	StarTravellerVis stv;

	double energy = stv.runTest(seed);
	printf("energy = %.6lf\n", energy);
}

void debugAll() {
	rep(seed, 1, 11) {
		StarTravellerVis stv;

		double energy = stv.runTest(seed);
		printf("energy = %.6lf\n\n", energy);
	}
}

int main(int argc, char **argv) {
	#ifdef LOCAL_DEBUG
		freopen("data.in", "r", stdin);
		freopen("data.out", "w", stdout);
		int seed = 1;
		if (argc > 1)
			sscanf(argv[1], "%d", &seed);
		#ifdef DEBUG
		debug(seed);
		#else
		debugAll();
		#endif

		printf("time = %ldms.\n", clock());
		return 0;
	#endif

    #ifdef DEBUG
        init_log();
    #endif

    int NStars;
    cin >> NStars;
    vector<int> stars(NStars);
    getVector(stars);

    StarTraveller algo;
    int ignore = algo.init(stars);
    cout << ignore << endl;
    cout.flush();

    while (true)
    {
        int NUfo;
        cin >> NUfo;
        if (NUfo < 0) break;
        vector<int> ufos(NUfo);
        getVector(ufos);
        int NShips;
        cin >> NShips;
        vector<int> ships(NShips);
        getVector(ships);
        vector<int> ret = algo.makeMoves(ufos, ships);
        cout << ret.size() << endl;
        for (int i = 0; i < ret.size(); ++i) {
            cout << ret[i] << endl;
        }
        cout.flush();
    }

    #ifdef DEBUG
        close_log();
    #endif

	#ifdef DEBUG
		printf("time = %ldms.\n", clock());
	#endif

    return 0;
}

