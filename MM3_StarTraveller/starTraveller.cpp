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

#define DEBUG

FILE *logout;

struct Star_t {
    int x, y;

    void print() const {
        fprintf(logout, "x = %d, y = %d\n", x, y);
        fflush(logout);
    }
};

struct Ufo_t {
    int idx[3];

    void dump(map<pii,int>& decay1, map<pii,int>& decay2) {
        ++decay1[mp(idx[0], idx[1])];
        ++decay2[mp(idx[1], idx[2])];
    }

    void print() const {
        fprintf(logout, "%d -> %d -> %d\n", idx[0], idx[1], idx[2]);
        fflush(logout);
    }
};

struct Node_t {
    double cost;
    vi path;

    bool isEmpty() {
        return SZ(path) == 0;
    }

    void clear() {
        path.clr();
    }

    void push_back(int x) {
        path.pb(x);
    }

    void print() const {
        fprintf(logout, "st = %d: ", st);
        rep(i, 0, SZ(path)) {
            if (i == 0)
                fprintf(logout, "%d", path[i]);
            else
                fprintf(logout, "->%d", path[i]);
        }
        fprintf(lgout, "\n");
        fflush(logout);
    }

    bool operator< (const Node_t& o) const {
        return cost < o.cost;
    }
};

const double POS_INF = 1e16;
const int maxn = 2005;
const char *LOG_FILENAME = "starlog.out"
int NStars, NShips, NUfos;
double M[maxn][maxn], base[25];
bool visit[maxn];
Star_t stars[maxn];
Ufo_t ufos[maxn/100];
int ships[15];
vpii E1[maxn], E1_[maxn];
vpii E2[maxn], E2_[maxn];
map<pii, int> decay1, decay2;
map<int> ust, _ust;

inline void init_log() {
    logout = fopen(LOG_FILENAME, "w");
}

inline void close_log() {
    fclose(logout);
}

double Length(const Star_t& sa, const Star_t& sb) {
    return sqrt((sa[i].x-sb[i].x)*(sa[i].x-sb[i].x) + (sa[i].y-sb[i].y)*(sa[i].y-sb[i].y));
}

double Length(const int a, const int b) {
    return M[a][b];
}

class StarTraveller {
public:
    int curTurn;
    int topk;
    vi visited;

    void Init() {
        curTurn = 0;
        ust.clr();
        _ust.clr();
        rep(i, 0, NStars) {
            _ust.insert(i);
            M[i][i] = 0.;
            rep(j, 0, i)
                M[i][j] = M[j][i] = Length(i, j);
        }
        base[0] = 1;
        rep(i, 1, 11) base[i] = base[i-1] * 0.001;
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

        decay1.clr();
        decay2.clr();

        for (int i=0,j=0; i<NUfos; ++i,j+=3) {
            ufos[i].idx[0] = vfuo[j];
            ufos[i].idx[1] = vfuo[j+1];
            ufos[i].idx[2] = vfuo[j+2];
            ufos[i].dump(decay1, decay2);
        }

        rep(i, 0, NStars) {
            E[i].clr();
            E_[i].clr();
        }

        map<pii,int>::iterator iter;
        for (iter=decay1.begin(); iter!=decay1.end(); ++iter) {
            E1[iter->fir->fir].pb(mp(iter->fir->sec, iter->sec));
            E1_[iter->fir->sec].pb(mp(iter->fir->fir, iter->sec));
        }

        for (iter=decay2.begin(); iter!=decay2.end(); ++iter) {
            E2[iter->fir->fir].pb(mp(iter->fir->sec, iter->sec));
            E2_[iter->fir->sec].pb(mp(iter->fir->fir, iter->sec));
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
        rep(i, 0, sz) assert (vc[i]>=00 && vc[i]<NStars);
        #endif

        rep(i, 0, sz) {
            const int& v = sz[i];
            if (!visit[v]) {
                visit[v] = true;
                visited.pb(v);
                ust.insert(v);
                _ust.erase(v);
            }
        }
    }

    /**
        \brief calculate the decay num of move idx
    */
    int Decay(const int u, const int v, const int idx) {
        if (idx == 1) {
            return decay1[mp(u, v)];
        } else {
            return decay2[mp(u, v)];
        }
    }

    /**
        \brief calculate the cost of hop 1
    */
    void costHop1(const int u, const int v, Node_t& nd) {
        nd.clr();
        nd.pb(u);
        nd.pb(v);
        int dec = Decay(u, v, 1);
        nd.cost = Length(u, v) * Base[dec];
    }

    /**
        \brief calculate the cost of hop 2, there must meet UFO between medium node and end-points
        \prob  what if `medium node` is also unvisited, then may be we should add some `bonus`.
    */
    void costHop2(const int u, const int v, Node_t& nd) {
        const vpii& e1 = E1[u];
        const int sz1 = SZ(e1);
        const vpii& e2 = E2_[v];
        const int sz2 = SZ(e2);
        double cost = POS_INF, tmp;
        int ansa = -1;
        int c1, c2;

        rep(i, 0, sz1) {
            const int a = e1[i].fir;
            // if (a==v || a==u) continue;
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
            // if (a==u || a==v) continue;
            c2 = e2[i].sec;
            c1 = decay1[mp(u, a)];
            tmp = Length(u, a) * Base[c1] + Length(a, v) * Base[c2];
            if (tmp < cost) {
                ansa = a;
                cost = tmp;
            }
        }

        nd.clr();
        if (ansa >= 0) {
            nd.pb(u);
            nd.pb(ansa);
            nd.pb(v);
            nd.cost = cost;
        }
    }

    /**
        \brief calculate the possibility of exists b -> v in next turn
    */
    double PnxtHop(const int a, const int b) {
        int c = 0, sz = E2_[a];
        double ret = 1.0;

        rep(i, 0, sz) c += E2_[a][i].sec;

        if (c) {
            double p = 1.0 * c / NStars;
            ret = 1.0 * (1.0 - p) + 0.001 * p;
        }

        return ret;
    }

    /**
        \brief calculate the cost of hop3, there must meet UFO between medium node and end-points
            `u -> a -> b -> v`
    */
    void costHop3(const int u, const int v, Node_t& nd) {
        const vpii& e1 = E1[u];
        const int sz1 = SZ(e1);
        double cost = POS_INF, tmp;
        int ansa = -1, ansb = -1;
        int c1, c2, c3;

        rep(i, 0, sz1) {
            const int a = e1[i].fir;
            const vpii& e2 = E2[a];
            const int sz2 = SZ(e2);
            c1 = e1[i].sec;
            // if (a==v || a==u) continue;
            rep(j, 0, sz2) {
                const int b = e2[j].fir;
                // if (b==a || b==u || b==v) continue;
                c2 = e2[j].sec;
                tmp = Length(u, a) * Base[c1] + Length(a, b) * Base[c2] + Length(b, v) * PnxtHop(b, v);
                if (tmp < cost) {
                    cost = tmp;
                    ansa = a;
                    ansb = b;
                }
            }
        }

        nd.clr();
        if (ansa >= 0) {
            nd.pb(u);
            nd.pb(ansa);
            nd.pb(ansb);
            nd.pb(v);
            nd.cost = cost;
        }
    }

    /**
        \brief  make a valid hop according current layout
        \return vector<int> present the next move of ships
    */
    vi Hop() {
        if (curTurn == 0)
            topk = NShips;
        else
            topk = 1;

        vi ret(NShips, 0);

        /**
            \step 1: using current position of ships to initialize `ret`
        */
        rep(i, 0, NShips) ret[i] = ships[i];

        vi unvisit;
        for (sti::iterator iter=_ust.begin(); iter!=_ust.end(); ++iter) {
            unvisit.pb(*iter);
        }

        int sz = SZ(unvisit), sz_ = SZ(visited);
        vector<Node_t> vc;
        Node_t nd;

        rep(j, 0, sz_) {
            const int u = visited[j];
            rep(i, 0, sz) {
                const int v = unvisit[i];
                {
                    /**
                        \case 1: one hop
                    */ 
                    costHop1(u, v, nd);
                    if (!nd.isEmpty())
                        vc.pb(nd);

                    /**
                        \case 2: two hop 
                    */
                    costHop2(u, v, nd);
                    if (!nd.isEmpty())
                        vc.pb(nd);

                    /**
                        \case 3: three hop
                    */
                    costHop3(u, v, nd);
                    if (!nd.isEmpty())
                        vc.pb(nd);

                    /**
                        \case 4: four hop
                    */
                    costHop4(u, v, nd);
                    if (!nd.isEmpty())
                        vc.pb(nd);
                }
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

int main() {
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

    return 0;
}

