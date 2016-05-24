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

// #define DEBUG
// #define LOCAL_DEBUG

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
    double gain, cost;
    vi path;

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
bool visit[maxn];
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

const double tolLength = 100.0;
const double gainRate = 0.15;
const double eps = 1e-6;
class StarTraveller {
public:
    int NTurns;
    int topk, still;
    int mark[maxn];
    vi visited;
	bool more[15];
	bool taken[maxn];
	double gainRate;

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
		still = 0;
    }

    /**
        \brief  init the coordinate of all stars
        \return useless
    */
    int init(vector<int> vstar) {
        const int sz = SZ(vstar);
        NStars = sz >> 1;

        memset(visit, false, sizeof(visit));

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
    void Update(const vi& vc) {
        const int sz = SZ(vc);

        #ifdef DEBUG
        assert(sz == NShips);
        rep(i, 0, sz) assert (vc[i]>=0 && vc[i]<NStars);
        #endif

        rep(i, 0, sz) {
            const int& v = vc[i];
            if (!visit[v]) {
                visit[v] = true;
                visited.pb(v);
                ust.insert(v);
                _ust.erase(v);
				if (paths[i].cost>=tolLength || paths[i].gain<tolLength)
					more[i] = true;
            }
            if (!paths[i].empty())
                paths[i].pop_back();
        }
        ++NTurns;
    }

	/**
		\brief calculate the gain of hop 1
	*/
	void gainHop1(const int u, const int v, Node_t& nd) {
		nd.clr();
		nd.pb(u);
		nd.pb(v);
		int c = decay1[mp(u, v)];

		// nd.gain = Length(u, v) * Base[c] - Length(u, v);
		nd.cost = Length(u, v) * Base[c];
		nd.gain = Length(u, v) - nd.cost;
	}

    /**
       \brief calculate the gain of hop2
    */
	void gainHop2(const int u, const int v, Node_t& nd) {
		const vpii& e1 = E1[u];
		const int sz1 = SZ(e1);
		const vpii& e2 = E2_[v];
		const int sz2 = SZ(e2);
		double gain = NEG_INF, cost = POS_INF, tmp, sum;
		int ansa = -1;
		int c1, c2;

		rep(i, 0, sz1) {
			const int a = e1[i].fir;
			// We had already visited v, why not visit again?
			if (a == v)	continue;
			c1 = e1[i].sec;
			c2 = decay2[mp(a, v)];
			if (visit[a])
				tmp = Length(u, v);
			else
				tmp = Length(u, a) + Length(a, v);
			sum = Length(u, a) * Base[c1] + Length(a, v) * Base[c2];
			tmp -= sum;
			if (sum<cost || (sum==cost && tmp>gain)) {
				gain = tmp;
				cost = sum;
				ansa = a;
			}
		}

		// other option is stay at u
		{
			const int a = u;
			if (a != v) {
				c1 = decay1[mp(u, a)];
				c2 = decay2[mp(a, v)];
				tmp = Length(u, v);
				sum = Length(u, a) * Base[c1] + Length(a, v) * Base[c2];
				tmp -= sum;
				if (sum<cost || (sum==cost && tmp>gain)) {
					gain = tmp;
					cost = sum;
					ansa = a;
				}
			}
		}

		rep(i, 0, sz2) {
            const int a = e2[i].fir;
            if (a == v) continue;
            c2 = e2[i].sec;
            c1 = decay1[mp(u, a)];
			tmp = POS_INF;
			if (visit[a])
				tmp = Length(u, v);
			else
				tmp = Length(u, a) + Length(a, v);
			sum = Length(u, a) * Base[c1] + Length(a, v) * Base[c2];
			tmp -= sum;
			if (sum<cost || (sum==cost && tmp>gain)) {
				gain = tmp;
				cost = sum;
				ansa = a;
			}
        }

		nd.clr();
		if (ansa >= 0) {
			nd.pb(u);
			nd.pb(ansa);
			nd.pb(v);
			nd.gain = gain;
			nd.cost = cost;
		}
	}

    /**
        \brief calculate the possibility of exists b -> v in next turn
    */
    double PnxtHop(const int a, const int b) {
		return 1.0;

        int c = 0, sz = SZ(E2_[a]);
        double ret = 1.0;

        rep(i, 0, sz) c += E2_[a][i].sec;

        if (c) {
            double p = 1.0 * c / NStars;
            ret = 1.0 * (1.0 - p) + 0.001 * p;
        }

        return ret;
    }

    /**
        \brief calculate the gain of hop3, there must meet UFO between medium node and end-points
            `u -> a -> b -> v`
    */
    void gainHop3(const int u, const int v, Node_t& nd) {
        const vpii& e1 = E1[u];
        const int sz1 = SZ(e1);
        double gain = NEG_INF, cost = POS_INF, tmp, sum;
        int ansa = -1, ansb = -1;
        int c1, c2;

        rep(i, 0, sz1) {
            const int a = e1[i].fir;
            const vpii& e2 = E2[a];
            const int sz2 = SZ(e2);
            c1 = e1[i].sec;
            if (a == v)	continue;
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
                sum = Length(u, a) * Base[c1] + Length(a, b) * Base[c2] + Length(b, v) * PnxtHop(b, v);
				tmp -= sum;
				if (sum<cost || (sum==cost && tmp>gain)) {
					gain = tmp;
					cost = sum;
					ansa = a;
					ansb = b;
				}
            }
        }

		// other option is stay at u first
		{
			const int a = u;
			if (a != v) {
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
						tmp = Length(u, b) + Length(b, v);
					} else if (!visit[a] && visit[b]) {
						tmp = Length(u, a) + Length(a, v);
					} else {
						tmp = Length(u, a) + Length(a, b) + Length(b, v);
					}
					sum = Length(u, a) * Base[c1] + Length(a, b) * Base[c2] + Length(b, v) * PnxtHop(b, v);
					tmp -= sum;
					if (sum<cost || (sum==cost && tmp>gain)) {
						gain = tmp;
						cost = sum;
						ansa = a;
						ansb = b;
					}
				}
			}
		}

        nd.clr();
        if (ansa >= 0) {
            nd.pb(u);
            nd.pb(ansa);
            nd.pb(ansb);
            nd.pb(v);
            nd.gain = gain;
			nd.cost = cost;
        }
    }

    /**
     *	\brief judge current path is redundancy
     */
    bool judge(const Node_t& nd) {
		const int sz = SZ(nd);
		int c = 0;
		
		rep(i, 1, sz) {
			const int v = nd[i];
			if (!visit[v] && !taken[v])
				++c;
		}
		
		return c > 0;
    }
	
	bool updateTaken(const Node_t& nd) {
		const int sz = SZ(nd);
		int c = 0;
		
		rep(i, 1, sz) {
			const int v = nd[i];
			taken[v] = true;
		}
		
		return c > 0;
	}

    /**
        \brief  make a valid hop according current layout
        \return vector<int> present the next move of ships
    */
    vi Hop() {
        if (NTurns == 0)
            topk = NShips;
        else
            topk = NShips / 2;

        vi ret(NShips, 0);

        /**
            \step 1: using current position of ships to initialize `ret`
        */
        rep(i, 0, NShips) {
            if (paths[i].empty())
                ret[i] = ships[i];
            else
                ret[i] = *paths[i].rbegin();
        }

        vi unvisit;
        for (sti::iterator iter=_ust.begin(); iter!=_ust.end(); ++iter) {
            unvisit.pb(*iter);
        }

		const int sz_unvisit = SZ(unvisit);
        int sz = SZ(unvisit), sz_ = SZ(visited);
        vector<Node_t> vc;
        Node_t nd;

        rep(j, 0, NShips) {
			const int u = ships[j];
            if (!paths[j].empty() && !more[j])
                continue;
			nd.idx = j;
            rep(i, 0, sz) {
                const int v = unvisit[i];
                /**
                    \case 1: one hop
                */
                gainHop1(u, v, nd);
                if (!nd.empty())
                    vc.pb(nd);

                /**
                    \case 2: two hop
                */
                gainHop2(u, v, nd);
                if (!nd.empty())
                    vc.pb(nd);

                /**
                    \case 3: three hop
                */
                gainHop3(u, v, nd);
                if (!nd.empty())
                    vc.pb(nd);
            }
        }

        sort(all(vc));
        int sz_vc =  SZ(vc);
		bool flag = false;
		memset(taken, false, sizeof(taken));
		
        rep(i, 0, sz_vc) {
            const int idx = vc[i].idx;
            if (mark[idx] == NTurns) continue;
			if (!judge(vc[i])) continue;
			#ifdef DEBUG
			vc[i].print();
			#endif
			if (vc[i].cost>tolLength && vc[i].gain<50.0 && (vc[i].gain+eps)<gainRate*(vc[i].cost+eps) && (NStars*4-NTurns)*topk>sz_unvisit*3)
				continue;
			more[idx] = false;
			paths[idx].clr();
			updateTaken(vc[i]);
			flag = true;
            mark[idx] = NTurns;
			paths[idx].cost = vc[i].cost;
			paths[idx].gain = vc[i].gain;
			#ifdef LOCAL_DEBUG
			assert(paths[idx].empty());
			#endif
            per(j, 1, SZ(vc[i])) {
                paths[idx].pb(vc[i][j]);
            }
            ret[idx] = *paths[idx].rbegin();
            if (--topk == 0)
                break;
        }

		if (!flag) {
			#ifdef LOCAL_DEBUG
			printf("NTurns = %d, still = %d\n", NTurns, still);
			#endif
			++still;
			this->gainRate *= 0.8;
			// if (this->gainRate < eps)
				// this->gainRate = -1.0;
		} else {
			still = 0;
			this->gainRate = ::gainRate;
		}
		
		rep(i, 0, NShips) {
			if (more[i] && ret[i]!=ships[i] && taken[ret[i]]) {
				ret[i] = ships[i];
				paths[i].clr();
			}
		}

        return ret;
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
			NUfo = 4;
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
		// freopen("data.out", "w", stdout);
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

