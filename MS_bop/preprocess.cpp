/**
	\Author	Trasier
	\brief	calculate all possible valid type of path
*/
#include <bits/stdc++.h>
using namespace std;
//#pragma comment(linker,"/STACK:102400000,1024000")

#define sti				set<int>
#define stpii			set<pair<int, int> >
#define mpii			map<int,int>
#define vi				vector<int>
#define pii				pair<int,int>
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
#define lson			l, mid, rt<<1
#define rson			mid+1, r, rt<<1|1


const int maxn = 55;
vector<int> E[maxn];
map<string,int> tb;
vector<string> attr;

struct node_t {
	int u;
	vi path;

	node_t() {}
	node_t(const int u) {this->u = u;}
	node_t(const int u, const vi& path) {
		this->u = u;
		this->path = path;
	}

	void clr() {
		path.clr();
	}

	void pb(int x) {
		path.pb(x);
	}

	int size() const {
		return SZ(path);
	}

	friend ostream& operator<< (ostream& out, const node_t& o) {
		rep(i, 0, SZ(o)) {
			if (i == 0)
				out << attr[o.path[i]];
			else
				out << " -> " << attr[o.path[i]];
		}
		return out;
	}
};

void init() {
	tb.clr();
}

inline int getId(const string& s) {
	if (tb.find(s) == tb.end()) {
		tb[s] = SZ(attr);
		attr.pb(s);
	}
	return tb[s];
}

inline void addEdge(const string& su, const string& sv) {
	int uid = getId(su), vid = getId(sv);
	E[uid].pb(vid);
}

void solve(const string& st, const string& ed) {
	int stId = getId(st), edId = getId(ed);
	deque<node_t> Q;
	map<vi,int> visit;
	
	cout << "[" << st << ", " << ed << "]" << endl;
	Q.push_back(node_t(stId, vi(1, stId)));
	visit[vi(1, stId)] = 1;
	
	for (int hop=1; hop<=3; ++hop) {
		int szq = SZ(Q);
		while (szq--) {
			node_t nd = Q.front();
			node_t tmp = nd;
			tmp.pb(0);
			const int u = nd.u;
			int sz = SZ(E[u]);
			rep(i, 0, sz) {
				const int v = E[u][i];
				tmp.u = v;
				tmp.path[hop] = v;
				if (!visit[tmp.path]) {
					visit[tmp.path] = 1;
					Q.push_back(tmp);
				}
			}
			Q.pop_front();
		}

		// print the path which endpoint is edId
		cout << "hop " << hop << ":\n";
		szq = SZ(Q);
		rep(i, 0, szq) {
			node_t nd = Q[i];
			if (nd.u == edId) {
				cout << nd << endl;
			}
		}
		cout << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
		freopen("data.in", "r", stdin);
		freopen("data.out", "w", stdout);
	#endif

	int m, q;
	string su, sv;

	init();
	cin >> m;
	rep(i, 0, m) {
		cin >> su >> sv;
		addEdge(su, sv);
	}
	cin >> q;
	rep(i, 1, q+1) {
		cin >> su >> sv;
		cout << "Case #" << i << ":" << endl;
		solve(su, sv);
	}

	return 0;
}

/**
data.in

11
Id Id
Id F.FId
F.FId Id
Id C.CId
C.CId Id
Id J.JId
J.JId Id
AA.AuId AA.AfId
AA.AfId AA.AuId
AA.AuId Id
Id AA.AuId
4
Id Id
Id AA.AuId
AA.AuId Id
AA.AuId AA.AuId
*/