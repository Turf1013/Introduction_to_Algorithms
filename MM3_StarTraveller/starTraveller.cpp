/**
    \author Trasier
    \source TopCoder-MM-StarTraverller
    \data   2016-05-20
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
		fprintf(out, "%d: ", idx);
        rep(i, 0, sz) {
            if (i == 0)
                fprintf(out, "%d", path[i]);
            else
                fprintf(out, "->%d", path[i]);
        }
        fprintf(out, "\n");
        fflush(out);
    }

    int& operator[] (const int idx) {
        return path[idx];
    }

    const int& operator[] (const int idx) const {
    	return path[idx];
    }
};

struct Chromosome_t {
	double cost;
	vector<Node_t> vnode;

	Node_t& find(const int idx) {
		int id = -1;

		rep(i, 0, SZ(vnode)) {
			if (vnode[i].idx == idx) {
				id = i;
				break;
			}
		}

		#ifdef DEBUG
		assert(id >= 0);
		#endif

		return vnode[id];
	}

	const Node_t& find(const int idx) const {
		int id = -1;

		rep(i, 0, SZ(vnode)) {
			if (vnode[i].idx == idx) {
				id = i;
				break;
			}
		}

		#ifdef DEBUG
		assert(id >= 0);
		#endif

		return vnode[id];
	}

	void resize(const int n) {
		vnode.resize(n);
	}

	void clear() {
		vnode.clr();
	}

	size_t size() const {
		return SZ(vnode);
	}

	void push_back(const Node_t& nd) {
		vnode.pb(nd);
	}

	const Node_t& operator[] (const int idx) const {
		return vnode[idx];
	}

	Node_t& operator[] (const int idx) {
		return vnode[idx];
	}

	bool operator< (const Chromosome_t& o) const {
		return cost < o.cost;
	}

	void print(FILE *out=stdout) const {
		const int sz = SZ(vnode);
		fprintf(out, "cost = %.6lf\n", cost);
		rep(i, 0, sz)
			vnode[i].print(out);
		fflush(out);
	}
};

const double eps = 5e-5;
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
vi paths[15];
vpii E1[maxn], E1_[maxn];
vpii E2[maxn], E2_[maxn];
map<pii, int> decay1, decay2;
set<int> ust, _ust;
vi visited;

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

struct GA {
	const int POP_SIZE;
	const int MAX_ITERATION;
	const int P_Crossover = 400;
	const int P_Mutation = 50;
	typedef vector<Chromosome_t> vChromosome;
	vChromosome vchroms[2];
	vi vIdx;
	vector<double> vfitness;
	int bst, wst, finalIdx;
	int taken[maxn], replace[maxn];
	#ifdef DEBUG
	double pcost;
	#endif

	#ifdef DEBUG
	GA(int pop_size, int max_iter):POP_SIZE(pop_size), MAX_ITERATION(max_iter) {pcost=0.;}
	#else
	GA(int pop_size, int max_iter):POP_SIZE(pop_size), MAX_ITERATION(max_iter) {}
	#endif

	/**
		\brief	organize the framework
	*/
	void solve() {
		int p = 0, q = 1;

		GenInitPopulation();
		EvaluatePopulation(p);
		rep(i, 0, MAX_ITERATION) {
			GenNextPopulation(q);
			EvaluatePopulation(q);
			PerformEvolution(q);
			// PrintReport(q);
			p ^= 0;
			q ^= 1;
		}

		finalIdx = p;
		dumpToPath();
		#ifdef DEBUG
		PrintBest();
		updatePcost();
		#endif
	}

	/**
		\brief	dump the final population to path
	*/
	void dumpToPath() {
		const vChromosome& vchro = vchroms[finalIdx];
		const Chromosome_t& chr = vchro[bst];
		const int sz = SZ(chr);

		rep(i, 0, sz) {
			const Node_t& nd = chr[i];
			const int shipIdx = nd.idx;
			findBstPath(nd, paths[shipIdx]);
		}
	}

	/**
		\brief	find the best path of current ship
		\note	best path means using least cost with least turns
	*/
	void findBstPath(const Node_t& src, vi& des) {
		/**
			if $vIdx \in src \gt 2$, we only append it to des,
			which means only top-2 vnode may encounter with `UFO`.
			Of course, we reverse-insert the vIdx
		*/
		const int sz = SZ(src);

		des.clr();
		per(i, 3, sz) des.pb(src[i]);

		if (sz >= 3) {
			findBstPath(src[0], src[1], src[2], des);
		} else if (sz == 2) {
			findBstPath(src[0], src[1], des);
		} else {
			/* sz <= 1, stay */
			des.pb(ships[src.idx]);
		}
	}

	/**
		\brief find the best path of prefix hop3
	*/
	void findBstPath(const int u, const int a, const int v, vi& des) {
		double mn = POS_INF, tmp;
		int x;
		vi vtmp;

		/**
			\case 1: `u ~> a ~> v`
		*/
		tmp = Hop(u, a, v);
		if (tmp < mn) {
			mn = tmp;
			vtmp.clr();
			vtmp.pb(u);
			vtmp.pb(a);
			vtmp.pb(v);
		}

		/**
			\case 2: `u ~> x ~> a -> v`
		*/
		tmp = minCost1(u, a, x) + Length(a, v);
		if (tmp < mn) {
			mn = tmp;
			vtmp.clr();
			vtmp.pb(u);
			vtmp.pb(x);
			vtmp.pb(a);
			vtmp.pb(v);
		}

		/**
			\case 3: `u ~> a ~> x -> v`
		*/
		tmp = Hop1(u, a) + minCost2(a, v, x);
		if (tmp < mn) {
			mn = tmp;
			vtmp.clr();
			vtmp.pb(u);
			vtmp.pb(a);
			vtmp.pb(x);
			vtmp.pb(v);
		}

		const int sz = SZ(vtmp);
		per(i, 0, sz) des.pb(vtmp[i]);
	}

	/**
		\brief	find the best path of prefix hop2
	*/
	void findBstPath(const int u, const int v, vi& des) {
		double mn = POS_INF, tmp;
		int x, y;
		vi vtmp;

		/**
			\case 1: `u ~> v`
		*/
		tmp = Hop1(u, v);
		if (tmp < mn) {
			mn = tmp;
			vtmp.clr();
			vtmp.pb(u);
			vtmp.pb(v);
		}

		/**
			\case 2: `u ~> x ~> v`
		*/
		tmp = minCost1(u, v, x);
		if (tmp < mn) {
			mn = tmp;
			vtmp.clr();
			vtmp.pb(u);
			vtmp.pb(x);
			vtmp.pb(v);
		}

		/**
			\case 3: `u ~> x ~> y -> v`
		*/
		tmp = minCost3(u, v, x, y);
		if (tmp < mn) {
			mn = tmp;
			vtmp.clr();
			vtmp.pb(u);
			vtmp.pb(x);
			vtmp.pb(y);
			vtmp.pb(v);
		}

		const int sz = SZ(vtmp);
		per(i, 0, sz) des.pb(vtmp[i]);
	}

	/**
		\brief	generate the initial population
	*/
	void GenInitPopulation() {
		vChromosome& vchrom = vchroms[0];
		bool mark[15];
		vi shipHead[15];

		/**
			\step 1: collect all unvisit node
		*/
		vi unvisit;
		for (sti::iterator iter=_ust.begin(); iter!=_ust.end(); ++iter) {
			unvisit.pb(*iter);
		}

		/**
			\step 2: initial the priori head of path
		*/
		rep(j, 0, NShips) {
			const int u = ships[j];
			vi& vhead = shipHead[j];

			int sz;
			sz = SZ(E1[u]);
			rep(i, 0, sz) {
				const int& v = E1[u][i].fir;
				if (!visit[v])
					vhead.pb(v);
			}
			sz = SZ(E2[u]);
			rep(i, 0, sz) {
				const int& v = E2[u][i].fir;
				if (!visit[v])
					vhead.pb(v);
			}
			if (!visit[u])
				vhead.pb(u);

			#ifdef DEBUG
			sz = SZ(shipHead[j]);
			rep(i, 0, sz)
				assert(shipHead[j][i]>=0 && shipHead[j][i]<NStars && !visit[shipHead[j][i]]);
			#endif
		}

		memset(taken, -1, sizeof(taken));
		const int n_unvisit = SZ(unvisit);

		/**
			\step 3: initial POP_SIZE population
		*/
		vchrom.clr();
		rep(ii, 0, POP_SIZE) {
			Chromosome_t chr;

			chr.resize(NShips);
			memset(mark, false, sizeof(mark));
			int n_taken = n_unvisit;
			per(nship, 1, NShips+1) {
				int skip = rand() % nship;
				int cnt = (n_taken==0||nship==1) ? n_taken : rand()%(n_taken+1);
				int idx = -1;
				n_taken -= cnt;

				rep(i, 0, NShips) {
					if (mark[i]) continue;
					if (skip-- == 0) {
						idx = i;
						break;
					}
				}

				#ifdef DEBUG
				assert(idx>=0 && idx<NShips);
				#endif
				mark[idx] = true;

				// add path meet UFO first
				Node_t& nd = chr[idx];
				nd.idx = idx;
				nd.pb(ships[idx]);
				if (cnt == 0) continue;

				/**
					1/3 rate using the priority head node
				*/
				if (SZ(shipHead[idx]) && rand()%3==0) {
					rep(j, 0, 3) {
						int nxt = shipHead[idx][rand() % SZ(shipHead[idx])];
						if (taken[nxt] != ii) {
							taken[nxt] = ii;
							nd.pb(nxt);
							--cnt;
							break;
						}
					}
				}

				// add all not taken node randomly
				int pump = cnt/2;
				while (cnt) {
					int idx = rand() % n_unvisit;
					if (taken[unvisit[idx]] == ii) {
						if (pump-- == 0)
							break;
						continue;
					}
					taken[unvisit[idx]] = ii;
					nd.pb(unvisit[idx]);
					--cnt;
				}

				// add not taken node from beginning
				if (cnt) {
					rep(j, 0, n_unvisit) {
						if (taken[unvisit[j]] == ii) continue;
						taken[unvisit[j]] = ii;
						nd.pb(unvisit[j]);
						if (--cnt == 0) break;
					}
				}

				#ifdef DEBUG
				assert(cnt == 0);
				#endif
			}

			#ifdef DEBUG
			rep(j, 0, n_unvisit)
				assert(taken[unvisit[j]] == ii);
			#endif

			vchrom.pb(chr);
			#ifdef DEBUG
			// chr.print();
			#endif
		}
	}

	/**
		\brief	generate next population
	*/
	void GenNextPopulation(const int q) {
		SelectionOperator(q ^ 1);
		CrossoverOperator(q);
		MutationOperator(q);
	}

	/**
		\brief evaluate current population
	*/
	void EvaluatePopulation(const int q) {
		CalcCost(q);
		CalcFitness(q);
		FindExtremeIndividual();
	}

	/**
		\brief calculate the cost of current population
	*/
	void CalcCost(const int id) {
		CalcCost(vchroms[id]);
	}

	void CalcCost(vChromosome& vchrom) {
		const int sz = SZ(vchrom);

		rep(i, 0, sz) {
			Chromosome_t& chr = vchrom[i];
			const int sz_chr = SZ(chr);
			chr.cost = 0;
			rep(j, 0, sz_chr) {
				chr.cost += CalcCost(chr[j]);
			}
		}
	}

	/**
		\brief calculate the cost of current node
		\return cost
	*/
	double CalcCost(const Node_t& nd) {
		double ret = 0.0;
		const int sz = SZ(nd);

		if (sz >= 3) {
			ret = CalcHop2(nd[0], nd[1], nd[2]);
			rep(i, 3, sz) {
				ret += Length(nd[i-1], nd[i]);
			}
		} else if (sz == 2) {
			ret = CalcHop1(nd[0], nd[1]);
		}

		return ret;
	}

	double Hop(const int u, const int a, const int v) {
		int c1 = decay1[mp(u, a)], c2 = decay2[mp(a, v)];
		return Length(u, a) * Base[c1] + Length(a, v) * Base[c2];
	}

	double Hop1(const int u, const int v) {
		int c = decay1[mp(u, v)];
		return Length(u, v) * Base[c];
	}

	double Hop2(const int u, const int v) {
		int c = decay2[mp(u, v)];
		return Length(u, v) * Base[c];
	}

	/**
		\brief	calculate minimum cost at 1-st turn from u to v
	*/
	double minCost1(const int u, const int v) {
		double ret = POS_INF, tmp;
		int a, c1, c2;

		// handle outgoing edge from u
		const vpii& e1 = E1[u];
		const int sz1 = SZ(e1);

		rep(i, 0, sz1) {
			a = e1[i].fir;
			c1 = e1[i].sec;
			if (visit[a]) {
				c2 = decay2[mp(a, v)];
				tmp = Length(u, a) * Base[c1] + Length(a, v) * Base[c2];
				ret = min(ret, tmp);
			}
		}

		// handle incident edge from v
		const vpii& e2 = E1_[v];
		const int sz2 = SZ(e2);

		rep(i, 0, sz2) {
			a = e2[i].fir;
			c2 = e2[i].sec;
			if (visit[a]) {
				c1 = decay1[mp(u, a)];
				tmp = Length(u, a) * Base[c1] + Length(a, v) * Base[c2];
				ret = min(ret, tmp);
			}
		}

		return ret;
	}

	double minCost1(const int u, const int v, int& ansa) {
		double ret = POS_INF, tmp;
		int a, c1, c2;

		// handle outgoing edge from u
		const vpii& e1 = E1[u];
		const int sz1 = SZ(e1);

		rep(i, 0, sz1) {
			a = e1[i].fir;
			c1 = e1[i].sec;
			if (visit[a]) {
				c2 = decay2[mp(a, v)];
				tmp = Length(u, a) * Base[c1] + Length(a, v) * Base[c2];
				if (tmp < ret) {
					ret = tmp;
					ansa = a;
				}
			}
		}

		// handle incident edge from v
		const vpii& e2 = E1_[v];
		const int sz2 = SZ(e2);

		rep(i, 0, sz2) {
			a = e2[i].fir;
			c2 = e2[i].sec;
			if (visit[a]) {
				c1 = decay1[mp(u, a)];
				tmp = Length(u, a) * Base[c1] + Length(a, v) * Base[c2];
				if (tmp < ret) {
					ret = tmp;
					ansa = a;
				}
			}
		}

		return ret;
	}
	/**
		\brief	calculate minimum cost at 2-nd turn from u to v
	*/
	double minCost2(const int u, const int v) {
		double ret = POS_INF, tmp;
		int a, c;

		// handle outgoing edge from u
		const vpii& e1 = E2[u];
		const int sz1 = SZ(e1);

		rep(i, 0, sz1) {
			a = e1[i].fir;
			c = e1[i].sec;
			if (visit[a]) {
				tmp = Length(u, a) * Base[c] + Length(a, v);
				ret = min(ret, tmp);
			}
		}

		// handle incident edge from v
		const vpii& e2 = E2_[v];
		const int sz2 = SZ(e2);

		rep(i, 0, sz2) {
			a = e2[i].fir;
			c = e2[i].sec;
			if (visit[a]) {
				tmp = Length(u, a) * Base[c] + Length(a, v);
				ret = min(ret, tmp);
			}
		}

		return ret;
	}

	double minCost2(const int u, const int v, int& ansa) {
		double ret = POS_INF, tmp;
		int a, c;

		// handle outgoing edge from u
		const vpii& e1 = E2[u];
		const int sz1 = SZ(e1);

		rep(i, 0, sz1) {
			a = e1[i].fir;
			c = e1[i].sec;
			if (visit[a]) {
				tmp = Length(u, a) * Base[c] + Length(a, v);
				if (tmp < ret) {
					ret = tmp;
					ansa = a;
				}
			}
		}

		// handle incident edge from v
		const vpii& e2 = E2_[v];
		const int sz2 = SZ(e2);

		rep(i, 0, sz2) {
			a = e2[i].fir;
			c = e2[i].sec;
			if (visit[a]) {
				tmp = Length(u, a) * Base[c] + Length(a, v);
				if (tmp < ret) {
					ret = tmp;
					ansa = a;
				}
			}
		}

		return ret;
	}

	/**
		\brief	calculate the minimum cost of `u ~> x ~> y -> v`
	*/
	double minCost3(const int u, const int v) {
		const vpii& e1 = E1[u];
		const int sz1 = SZ(e1);
		double ret = POS_INF, tmp;
		int x, y, c1, c2;

		rep(i, 0, sz1) {
			x = e1[i].fir;
			if (!visit[x]) continue;
			c1 = e1[i].sec;
			const vpii& e2 = E2[x];
			const int sz2 = SZ(e2);
			rep(j, 0, sz2) {
				y = e2[j].fir;
				if (!visit[y]) continue;
				c2 = e2[j].sec;
				tmp = Length(u, x) * Base[c1] + Length(x, y) * Base[c2] + Length(y, v);
				ret = min(ret, tmp);
			}
		}

		return ret;
	}

	/**
		\brief	calculate the minimum cost of `u ~> x ~> y -> v`
	*/
	double minCost3(const int u, const int v, int& ansx, int& ansy) {
		const vpii& e1 = E1[u];
		const int sz1 = SZ(e1);
		double ret = POS_INF, tmp;
		int x, y, c1, c2;

		rep(i, 0, sz1) {
			x = e1[i].fir;
			if (!visit[x]) continue;
			c1 = e1[i].sec;
			const vpii& e2 = E2[x];
			const int sz2 = SZ(e2);
			rep(j, 0, sz2) {
				y = e2[j].fir;
				if (!visit[y]) continue;
				c2 = e2[j].sec;
				tmp = Length(u, x) * Base[c1] + Length(x, y) * Base[c2] + Length(y, v);
				if (tmp < ret) {
					ret = tmp;
					ansx = x;
					ansy = y;
				}
			}
		}

		return ret;
	}

	/**
		\brief	calculate the minimum cost of 2-hop using UFO
	*/
	double CalcHop2(const int u, const int a, const int v) {
		double ret = POS_INF;

		/**
			\case 1: `u ~> a ~> v`
		*/
		ret = min(ret, Hop(u, a, v));

		/**
			\case 2: `u ~> x ~> a -> v`
		*/
		ret = min(ret, minCost1(u, a) + Length(a, v));

		/**
			\case 3: `u ~> a ~> x -> v`
		*/
		ret = min(ret, Hop1(u, a) + minCost2(a, v));

		return ret;
	}

	/**
		\brief	calculate the minimum cost of 1-hop using UFO
	*/
	double CalcHop1(const int u, const int v) {
		double ret = POS_INF;

		/**
			\case 1: `u ~> v`
		*/
		ret = min(ret, Hop1(u, v));

		/**
			\case 2: `u ~> x ~> v`
		*/
		ret = min(ret, minCost1(u, v));

		/**
			\case 3: `u ~> x ~> y -> v`
		*/
		ret = min(ret, minCost3(u, v));

		return ret;
	}

	/**
		\brief calculate the fitness of current population
	*/
	void CalcFitness(const int p) {
		CalcFitness(vchroms[p]);
	}

	void CalcFitness(const vChromosome& vchro) {
		const int sz = SZ(vchro);

		vfitness.clr();
		double sum = 0., tmp;

		rep(i, 0, sz) sum += vchro[i].cost;

		rep(i, 0, sz) {
			tmp = 1.0 - vchro[i].cost / (sum + eps);
			vfitness.pb(tmp);
		}
	}

	void FindExtremeIndividual() {
		const int sz = SZ(vfitness);

		bst = wst = 0;
		rep(i, 1, sz) {
			if (vfitness[i] < vfitness[wst]) wst = i;
			if (vfitness[i] > vfitness[bst]) bst = i;
		}
	}

	void PerformEvolution(const int p) {
		PerformEvolution(vchroms[p]);
	}

	void PerformEvolution(vChromosome& vchro) {
		vchro[wst] = vchro[bst];
	}

	/**
		\brief	selection chromosome
	*/
	void SelectionOperator(const int p) {
		SelectionOperator(vchroms[p]);
	}

	void SelectionOperator(const vChromosome& src) {
		#ifdef DEBUG
		assert(SZ(vfitness) == SZ(src));
		#endif

		const int sz = SZ(vfitness);
		int cfit[POP_SIZE];

		vIdx.clr();
		cfit[0] = 0;
		rep(i, 0, sz) cfit[i+1] = cfit[i] + vfitness[i] * 1000;
		cfit[sz] = 2000;

		rep(i, 0, POP_SIZE) {
			int x = rand() % 1000;
			int k = upper_bound(cfit, cfit+sz, x) - cfit;
			vIdx.pb(k - 1);
		}
	}

	/**
		\brief	Crossover the chromosome by replace the subsequence
	*/
	void CrossoverOperator(const int q) {
		CrossoverOperator(vchroms[q^1], vchroms[q]);
	}

	/**
		\brief	self-bred crossover we cause we want path unique
	*/
	void Crossover(const vChromosome& src, const int id, vChromosome& des) {
		const int idx = vIdx[id];
		const int sid1 = rand() % NShips;
		const int sid2 = rand() % NShips;
		const int sza = src[idx].find(sid1).size();
		const int szb = src[idx].find(sid2).size();
		const int mn = min(sza, szb);
		Chromosome_t chr;

		if (mn<=1 || sid1==sid2) {
			des.pb(src[idx]);
			return ;
		}

		int b = rand() % (mn - 1) + 1;
		int e = rand() % (mn - 1) + 1;
		if (b > e) swap(b, e);

		chr = src[idx];
		Node_t& nda = chr.find(sid1);
		Node_t& ndb = chr.find(sid2);
		rep(j, b, e+1)
			swap(nda[j], ndb[j]);
		des.pb(chr);
	}

	/**
		\brief serious error with following function.
			No better Crossover operator
	*/
	void Crossover(const vChromosome& src, const int id1, const int id2, vChromosome& des) {
		const int aidx = vIdx[id1];
		const int bidx = vIdx[id2];
		int sid = rand() % NShips;
		const Node_t& nda = src[aidx].find(sid);
		const Node_t& ndb = src[bidx].find(sid);
		const int sza = SZ(nda);
		const int szb = SZ(ndb);
		const int mn = min(sza, szb);
		Chromosome_t chr;

		if (mn <= 1) {
			des.pb(src[aidx]);
			des.pb(src[bidx]);
			return ;
		}

		int b = rand() % (mn - 1) + 1;
		int e = rand() % (mn - 1) + 1;
		if (b > e) swap(b, e);

		// handle id1
		chr = src[aidx];
		rep(j, b, e+1) {
			replace[ndb[j]] = nda[j];
			taken[ndb[j]] = id1;
		}
		rep(i, 0, NShips) {
			Node_t& nd = chr[i];
			if (nd.idx == sid) {
				rep(j, b, e+1) {
					nd[j] = ndb[j];
				}
			} else {
				const int sz = SZ(nd);
				rep(j, 0, sz) {
					if (taken[nd[j]] == id1)
						taken[nd[j]] = replace[nd[j]];
				}
			}
		}
		des.pb(chr);
		#ifdef DEBUG
		// fprintf(stdout, "[Crossover] A: b = %d, e = %d\n", b, e);
		// src[aidx].print();
		// des.rbegin()->print();
		#endif

		// handle id2
		chr = src[bidx];
		rep(j, b, e+1) {
			replace[nda[j]] = ndb[j];
			taken[nda[j]] = id2;
		}
		rep(i, 0, NShips) {
			Node_t& nd = chr[i];
			if (nd.idx == sid) {
				rep(j, b, e+1) {
					nd[j] = nda[j];
				}
			} else {
				const int sz = SZ(nd);
				rep(j, 0, sz) {
					if (taken[nd[j]] == id2)
						taken[nd[j]] = replace[nd[j]];
				}
			}
		}
		des.pb(chr);
		#ifdef DEBUG
		// fprintf(stdout, "[Crossover] B:\n");
		// des.rbegin()->print();
		#endif
	}

	void CrossoverOperator(const vChromosome& src, vChromosome& des) {
		const int sz = SZ(vIdx);

		memset(taken, -1, sizeof(taken));
		des.clr();
		for (int i=0; i<sz; i+=2) {
			int x = rand() % 1000;
			if (x < P_Crossover) {
				// Crossover(src, i, i+1, des);
				Crossover(src, i, des);
				Crossover(src, i+1, des);
			} else {
				des.pb(src[vIdx[i]]);
				des.pb(src[vIdx[i+1]]);
			}
		}

		#ifdef DEBUG
		check_after_Crossover(des);
		#endif
	}

	void check_after_Crossover(const vChromosome& des) {
		const int sz = SZ(des);

		memset(taken, -1, sizeof(taken));
		rep(i, 0, sz) {
			const Chromosome_t& chr = des[i];
			#ifdef DEBUG
			// chr.print();
			#endif
			assert(SZ(chr) == NShips);
			rep(j, 0, NShips) {
				assert(SZ(chr[j])>=0 && chr[j][0]==ships[chr[j].idx]);
				rep(k, 1, SZ(chr[j])) {
					assert(taken[chr[j][k]] != i);
					taken[chr[j][k]] = i;
				}
			}

			rep(j, 0, NStars) {
				assert(visit[j] || taken[j]==i);
			}
		}
	}

	/**
		\brief	mutation the chromosome by reverse some subsequence
	*/
	void MutationOperator(const int q) {
		MutationOperator(vchroms[q]);
	}

	void MutationOperator(vChromosome& vchro) {
		const int sz = SZ(vchro);

		rep(i, 0, sz) {
			int x = rand() % 1000;
			if (x > P_Mutation) continue;

			int sid = rand() % NShips;
			Chromosome_t& chr = vchro[i];
			Node_t& nd = chr[sid];
			int len = SZ(nd);
			if (len <= 1) continue;

			int b = rand() % (len-1) + 1;
			int e = rand() % (len-1) + 1;
			if (b > e) swap(b, e);
			for (int j=b,k=e; j<k; ++j,--k) {
				swap(nd[j], nd[k]);
			}
		}
	}

	void PrintReport(const int p, FILE* out=stdout) {
		const vChromosome& vchro = vchroms[p];
		const int sz = SZ(vchro);

		fprintf(out, "BstIdx = %d\n", bst);
		rep(i, 0, sz) {
			fprintf(out, "(%d): \n", i);
			vchro[i].print(out);
			fprintf(out, "n");
		}
		fflush(out);
	}
	
	void PrintBest(FILE* out=stdout) {
		const vChromosome& vchro = vchroms[finalIdx];
		
		fprintf(out, "BstIdx = %d\n", bst);
		vchro[bst].print(out);
		fprintf(out, "\n");
		fflush(out);
	}

	#ifdef DEBUG
	void updatePcost() {
		double tmp = 0;

		rep(i, 0, NShips) {
			tmp += Hop1(ships[i], *paths[i].rbegin());
		}

		pcost += tmp;
	}
	#endif

	void print(FILE* out=stdout) const {

	}
};

class StarTraveller {
public:
    int NTurns;
    int topk;
    int mark[maxn];
	GA *ga;
	bool more;

    void Init() {
    	ga = new GA(300, 300);
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
		more = false;
		
        rep(i, 0, sz) {
            const int& v = vc[i];
            if (!visit[v]) {
                visit[v] = true;
				more = true;
                visited.pb(v);
                ust.insert(v);
                _ust.erase(v);
            }
            if (!paths[i].empty())
                paths[i].pop_back();
        }
        ++NTurns;
    }

    /**
        \brief  make a valid hop according current layout
        \return vector<int> present the next move of ships
    */
    vi Hop() {
        if (NTurns == 0)
            topk = NShips;
        else
            topk = 1;

        vi ret(NShips, 0);

        /**
            \step 1: using current position of ships to initialize `ret`
        */
		if (more) {
		/**
			\If we have already visit some unvisit node then, we call GA to reEvaluate.
				\Else we wait until visit some unvisit node.
		*/
			ga->solve();
		}
		
        rep(i, 0, NShips) {
            if (paths[i].empty())
                ret[i] = ships[i];
            else
                ret[i] = *paths[i].rbegin();
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

			printf("Move #%d: visit %d more stars, energy = %.06lf.\n", turns, delta, energy);

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
		// debug(seed);
		debugAll();
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

	#ifndef ONLINE_JUDGE
		printf("time = %ldms.\n", clock());
	#endif

    return 0;
}

