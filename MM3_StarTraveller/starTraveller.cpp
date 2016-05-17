/**
    \author Trasier
    \brief  TopCoder-MM-StarTraverller
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

const int maxn = 2005;
const char *LOG_FILENAME = "starlog.out"
int NStars, NShips, NUfos;
double M[maxn][maxn];
bool visit[maxn];
Star_t stars[maxn];
Ufo_t ufos[maxn/100];
int ships[15];
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

void Init() {
    ust.clr();
    _ust.clr();
    rep(i, 0, NStars) {
        _ust.insert(i);
        M[i][i] = 0.;
        rep(j, 0, i)
            M[i][j] = M[j][i] = Length(i, j);
    }
}

class StarTraveller {
public:

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
                ust.insert(v);
                _ust.erase(v);
            }
        }
    }

    /**
        \brief  make a valid hop according current layout
        \return vector<int> present the next move of ships
    */
    vi Hop() {
        vi ret(NShips, 0);

        /**
            \step 1: using current position of ships to initialize ret
        */
        rep(i, 0, NShips) ret[i] = ships[i];


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

