/**
    \author Trasier
    \source TopCoder-MM-StarTraverller
    \data   2016-05-25
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
    double x, y;
	
	bool operator< (const Star_t& o) const {
		if (x != o.x) return x < o.x;
		return y < o.y;
	}
	
	bool operator== (const Star_t& o) const {
		return x==o.x && y==o.y;
	}

    void print(FILE *out=stdout) const {
        fprintf(out, "x = %.0lf, y = %.0lf\n", x, y);
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
    double cost;
    vi path;
	
	Node_t(int idx=0):idx(idx) {}

    bool empty() {
        return SZ(path) == 0;
    }

    void clear() {
        path.clr();
    }
	
	vi::reverse_iterator rbegin() {
		return path.rbegin();
	}
	
	vi::const_reverse_iterator rbegin() const {
		return path.rbegin();
	}
	
    size_t size() const {
    	return SZ(path);
    }

    void push_back(int x) {
        path.pb(x);
    }

    void print(FILE *out=stdout) const {
    	int sz = SZ(path);
        fprintf(out, "No. = %d, Nhops = %d: ", idx, sz-1);
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
        return cost < o.cost;
    }

    int operator[] (const int idx) const {
        return path[idx];
    }
};

const double tolLength = 10.0;
const int stillBound = 30;
const double POS_INF = 1e16;
const int maxn = 2005;
const char *LOG_FILENAME = "starlog.out";
int NStars, NShips, NUfos;
int unvisit[maxn];
double M[maxn][maxn], Base[25];
bool visit[maxn];
Star_t stars[maxn];
Ufo_t ufos[maxn/100+5];
int ships[15];
vi paths[15];
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

inline double Length(const Star_t& sa, const Star_t& sb) {
    return sqrt((sa.x-sb.x)*(sa.x-sb.x) + (sa.y-sb.y)*(sa.y-sb.y));
}

inline double Length(const int a, const int b) {
    return M[a][b];
}

class StarTraveller {
public:
    int NTurns;
    int mark[maxn];
	int still[15];
	bool taken[maxn];
    vi visited;
	vi nxtHop;
	vector<Node_t> vnode;
	
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
		memset(visit, false, sizeof(visit));
		memset(taken, false, sizeof(taken));
		memset(still, 0, sizeof(still));
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
    void Update() {
		const vi& vc = nxtHop;
        const int sz = SZ(vc);
		#ifdef DEBUG
		double cost = 0;
		#endif
		
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
            }
			#ifdef DEBUG
			cost += Hop1(ships[i], vc[i]);
			#endif
            if (!paths[i].empty())
                paths[i].pop_back();
        }
		// fprintf(stderr, "Move #%d: cost = %.6lf\n", NTurns, cost);
		// fflush(stderr);
		// if (NTurns%100 == 0) {
			// fprintf(stderr, "time = %ldms.\n", clock());
			// fflush(stderr);
		// }
        ++NTurns;
    }
	
	double Hop1(const int u, const int v) {
		int c = decay1[mp(u, v)];
        return Length(u, v) * Base[c];
	}
	
	double Hop2(const int u, const int vv, const int v) {
		int c1 = decay1[mp(u, vv)], c2 = decay2[mp(vv, v)];
        return Length(u, vv) * Base[c1] + Length(vv, v) * Base[c2];
	}

    /**
        \brief calculate the cost of hop 1
    */
	void costHop1(const int idx, const int v) {
		const int u = ships[idx];
		const int c = decay1[mp(u, v)];
		
		Node_t nd(idx);
		nd.pb(u);
		nd.pb(v);
		nd.cost = Length(u, v) * Base[c];
		vnode.pb(nd);
	}

    /**
        \brief calculate the cost of hop 2, there must meet UFO between medium node and end-points
        \prob  what if `medium node` is also unvisited, then may be we should add some `bonus`.
    */
    void costHop2(const int idx, const int v) {
		const int u = ships[idx];
        const vpii& e1 = E1[u];
        const int sz1 = SZ(e1);
        const vpii& e2 = E2_[v];
        const int sz2 = SZ(e2);
        double cost = POS_INF, tmp;
        int ansa = -1;
        int c1, c2;

        rep(i, 0, sz1) {
            const int a = e1[i].fir;
            if (a == v) continue;
            c1 = e1[i].sec;
            c2 = decay2[mp(a, v)];
            tmp = Length(u, a) * Base[c1] + Length(a, v) * Base[c2];
            if (tmp < cost) {
                ansa = a;
                cost = tmp;
            }
        }

        rep(i, 0, sz2) {
            const int a = e2[i].fir;
            if (a == v) continue;
            c2 = e2[i].sec;
            c1 = decay1[mp(u, a)];
            tmp = Length(u, a) * Base[c1] + Length(a, v) * Base[c2];
            if (tmp < cost) {
                ansa = a;
                cost = tmp;
            }
        }
		
        if (ansa >= 0) {
			Node_t nd(idx);
            nd.pb(u);
            nd.pb(ansa);
            nd.pb(v);
            nd.cost = cost;
			vnode.pb(nd);
        }
    }

    /**
        \brief calculate the cost of hop3, there must meet UFO between medium node and end-points
            `u -> a -> b -> v`
    */
    void costHop3(const int idx, const int v) {
		const int u = ships[idx];
        const vpii& e1 = E1[u];
        const int sz1 = SZ(e1);
        double cost = POS_INF, tmp;
        int ansa = -1, ansb = -1;
        int c1, c2;

        rep(i, 0, sz1) {
            const int a = e1[i].fir;
            const vpii& e2 = E2[a];
            const int sz2 = SZ(e2);
            c1 = e1[i].sec;
            if (a == v) continue;
            rep(j, 0, sz2) {
                const int b = e2[j].fir;
                if (b == v) continue;
                c2 = e2[j].sec;
                tmp = Length(u, a) * Base[c1] + Length(a, b) * Base[c2] + Length(b, v);
                if (tmp < cost) {
                    ansa = a;
                    ansb = b;
                    cost = tmp;
                }
            }
        }

        if (ansa >= 0) {
			Node_t nd(idx);
            nd.pb(u);
            nd.pb(ansa);
            nd.pb(ansb);
            nd.pb(v);
            nd.cost = cost;
			vnode.pb(nd);
        }
    }
	
	/**
		\brief	calculate the tolerance length according current turn
	*/
	double getTolLength() {
		if (SZ(_ust)>NStars*0.8 && NTurns<NStars*2)
			return tolLength;
		if (SZ(_ust)>NStars*0.6 && NTurns<NStars*2)
			return tolLength * 1.2;
		return tolLength * 1.5;
	}
	
	double getUfoTolLength() {
		if (NUfos >= NShips) {
			if (SZ(_ust)>NStars*0.8 && NTurns<NStars*2)
				return tolLength;
			if (SZ(_ust)>NStars*0.6 && NTurns<NStars*2)
				return tolLength * 1.2;
			if (NTurns < NStars*2)
				return tolLength * 1.5;
			else
				return tolLength * 2;
		} else {
			if (SZ(_ust)>NStars*0.9 && NTurns<NStars*2)
				return tolLength;
			if (SZ(_ust)>NStars*0.7 && NTurns<NStars*2)
				return tolLength * 1.2;
			if (NTurns < NStars*2)
				return tolLength * 1.5;
			else
				return tolLength * 2;
		}
	}
	
	bool judge(const Node_t& nd) {
		if (NUfos == 0) return true;
		// if (SZ(_ust)>NStars*0.5 && NTurns<NStars*2) {
			// if (nd.cost < 10) return true;
		// } else {
			// if (nd.cost < 15) return true;
		// }
		if (nd.cost < getTolLength()) return true;
		if (nd.cost > getTolLength()*1.5) return false;
		const int sz = SZ(nd) - 1;
		const int v = *nd.rbegin();
		if (sz==1 && SZ(E2[v])) return true;
		if (sz==2 && SZ(E2_[v])) return true;
		return false;
	}
	
	/**
		\brief	Init next turn's position
	*/
	void InitNextTurn() {
		vi& ret = nxtHop;
		if (NTurns == 0)
			ret.resize(NShips, 0);
		
        rep(i, 0, NShips) {
            if (paths[i].empty())
                ret[i] = ships[i];
            else
                ret[i] = *paths[i].rbegin();
        }
	}
	
	/**
		\brief	Generate unvisit stars
	*/
	int GenUnvisitStar() {
		int c = 0;
		
		rep(i, 0, NShips) {
			rep(j, 0, SZ(paths[i]))
				taken[paths[i][j]] = true;
		}
		rep(i, 0, NStars) {
			if (!taken[i])
				unvisit[c++] = i;
		}
		
		return c;
	}
	
	
	/**
		\brief	Generate next hop
	*/
	void GenNextHop(int sz) {
		vnode.clr();
		
		rep(j, 0, NShips) {
            if (!paths[j].empty())
                continue;
            rep(i, 0, sz) {
                const int v = unvisit[i];
                /**
                    \case 1: one hop
                */
                costHop1(j, v);

                /**
                    \case 2: two hop
                */
                costHop2(j, v);

                /**
                    \case 3: three hop
                */
                costHop3(j, v);
            }
        }
	}
	
	/**
		\brief	check current turn in `EesyPeriod`
	*/
	bool isEasyPeriod() {
		const double step = 2.3;
		const double weight = 0.2;
		return (NStars*4-NTurns)>SZ(_ust)*step && SZ(_ust)>NStars*weight;
	}
	
	/**
		\brief	update the taken node
	*/
	void UpdateTaken() {
		rep(i, 0, NShips) {
			if (paths[i].empty()) {
				taken[nxtHop[i]] = true;
			} else {
				const int sz = SZ(paths[i]);
				rep(j, 0, sz) taken[paths[i][j]] = true;
			}
		}
	}
	
	/**
		\brief	choose next turn 
	*/
	void ChooseNextTurn() {	
		int topk;
		
        if (NTurns == 0)
            topk = NShips;
        else
            topk = 1;
		
		sort(all(vnode));
		const int sz = SZ(vnode);
		
		rep(i, 0, sz) {
			const int idx = vnode[i].idx;
			if (mark[idx] == NTurns) continue;
			if (isEasyPeriod() && !judge(vnode[i])) {
				continue;
			}
			mark[idx] = NTurns;
			#ifdef LOCAL_DEBUG
			// vnode[i].print();
			assert(paths[idx].empty());
			#endif
			per(j, 1, SZ(vnode[i])) {
				paths[idx].pb(vnode[i][j]);
			}
			nxtHop[idx] = *paths[idx].rbegin();
			if (--topk == 0)
				break;
		}
		
		// fprintf(stderr, "topk = %d: ", topk);
		// rep(i, 0, min(5, sz)) {
			// fprintf(stderr, " %.03lf", vnode[i].cost);
		// }
		// fprintf(stderr, "\n");
		// fflush(stderr);
	}
	
	/**
		\brief	move still ship
	*/
	void MoveStillShip() {
		rep(i, 0, NShips) {
			if (mark[i]==NTurns || !paths[i].empty()) continue;
			if (NUfos == 0) {
				nxtHop[i] = ships[i];
				continue;
			}
			#ifdef DEBUG
			assert(paths[i].empty());
			#endif
			const int u = ships[i];
			{
				const vpii& e = E1[u];
				int mx = 0, mxv = -1;
				const int sz = SZ(e);
				rep(j, 0, sz) {
					const int& v = e[j].fir;
					assert(e[j].sec > 0);
					if (e[j].sec > mx) {
						mx = e[j].sec;
						mxv = v;
					}
				}
				if (mxv != -1) {
					paths[i].pb(mxv);
					nxtHop[i] = *paths[i].rbegin();
					continue;
				}
			}
			#ifdef DEBUG
			assert(paths[i].empty());
			#endif
			{
				const vpii& e = E2[u];
				int mx = 0, mxv = -1;
				const int sz = SZ(e);
				rep(j, 0, sz) {
					const int& v = e[j].fir;
					assert(e[j].sec > 0);
					if (e[j].sec > mx) {
						mx = e[j].sec;
						mxv = v;
					}
				}
				if (mxv != -1) {
					paths[i].pb(mxv);
					paths[i].pb(u);
					nxtHop[i] = *paths[i].rbegin();
					continue;
				}
			}
			#ifdef DEBUG
			assert(paths[i].empty());
			#endif
			{
				vi vtmp;
				double tmp;
				
				rep(j, 0, NUfos) {
					if (!vtmp.empty()) break;
					tmp = Hop1(u, ufos[j].idx[1]);
					if (tmp < tolLength) {
						vtmp.pb(ufos[j].idx[1]);
						break;
					}
					
					tmp = Hop2(u, u, ufos[j].idx[2]);
					if (tmp < tolLength) {
						vtmp.pb(u);
						vtmp.pb(ufos[j].idx[2]);
						break;
					}
				}
				
				if (!vtmp.empty()) {
					per(j, 0, SZ(vtmp)) paths[i].pb(vtmp[j]);
					nxtHop[i] = *paths[i].rbegin();
				}
			}
		}
		
		if (NUfos == 0) return ;
		
		vi vIdx;
		
		rep(i, 0, NShips) {
			if (!paths[i].empty()) {
				still[i] = 0;
				continue;
			}
			if (++still[i] >= stillBound) {
				vIdx.pb(i);
			}
		}
		
		const int sz_vIdx = SZ(vIdx);
		const double weight = NShips<5 ? 1.0 : 0.7;
		
		if (sz_vIdx >= NShips*weight) {
			// we force one of the ships closet to some UFO and then move.
			double mn = POS_INF, tmp;
			int mnv = -1;
			vi vtmp;
			
			rep(i, 0, sz_vIdx) {
				const int u = ships[vIdx[i]];
				rep(j, 0, NUfos) {
					tmp = Hop1(u, ufos[j].idx[1]);
					if (tmp < mn) {
						mn = tmp;
						mnv = vIdx[i];
						vtmp.clr();
						vtmp.pb(ufos[j].idx[1]);
					}
					
					tmp = Hop2(u, u, ufos[j].idx[2]);
					if (tmp < mn) {
						mn = tmp;
						mnv = vIdx[i];
						vtmp.clr();
						vtmp.pb(u);
						vtmp.pb(ufos[j].idx[2]);
					}
				}
			}
			
			if (mn <= getUfoTolLength()) {
				assert(mnv>=0 && mnv<NShips);
				rep(i, 0, sz_vIdx)
					still[vIdx[i]] >>= 1;
					
				still[mnv] = 0;
				per(i, 0, SZ(vtmp)) paths[mnv].pb(vtmp[i]);
				nxtHop[mnv] = *paths[mnv].rbegin();
			}
		}
	}
	
	/**
		\brief print path
	*/
	void printPath() {
		rep(i, 0, NShips) {
			printf("%d", ships[i]);
			if (paths[i].empty()) {
				printf("->%d", nxtHop[i]);
			} else {
				per(j, 0, SZ(paths[i]))
					printf("->%d", paths[i][j]);
			}
			putchar('\n');
		}
	}
	
    /**
        \brief  make a valid hop according current layout
        \return vector<int> present the next move of ships
    */
    void Hop() {
        /**
            \step 1: using current position of ships to initialize `ret`
        */
		InitNextTurn();
		
		
		/**
			\step 2: Generate candidate star
		*/
		int sz_unvisit = GenUnvisitStar();
		
		
		/**
			\step 3: Generate next hop path
		*/
		GenNextHop(sz_unvisit);
		
        /**
			\step 4: Choose next turn
		*/
		ChooseNextTurn();

        /**
			\step 5: Move still ship along with UFO
		*/
		MoveStillShip();
		
		/**
			\step 6: update taken node
		*/
		UpdateTaken();
		
		/**
			\step 7: print path
		*/
		#ifdef DEBUG
		printPath();
		#endif
    }

    /**
        \brief  make a turn according current ufos' and ships' position.
        \return next position foreach ships
    */
    vector<int> makeMoves(vector<int> ufos, vector<int> ships) {
        init_ufos(ufos);
        init_ships(ships);
        Hop();
        Update();

        return nxtHop;
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
			NStar = 145;
			NShip = 5;
			NUfo = 0;
			NG = 3;
		} else {
			NStar = 100 + rand()%1901;
			NShip = 1 + rand()%10;
			NUfo = max(4, rand()%(NStar/100));
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
			fflush(stdout);
			
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
		// debug(seed);
		debugAll();
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

