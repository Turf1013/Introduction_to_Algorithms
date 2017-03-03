/**
	\author: 	Traiser
	\content:	Suffix Tree implemented by Ukkonen's method
	\compile:	compile with `-std=c++11`
*/
#include <bits/stdc++.h>
using namespace std;

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
#define getBits(x)		__builtin_popcount(x)
#define getBitIdx(x)	__builtin_ffs(x)

#define DEBUG

const int maxch = 26;

inline int getId(char c) {
	return c - 'a';
}

namespace Trie {
	struct node_t {
		string w;
		int nxt[maxch];
		int link;
	};

	const int head = 1;
	const int root = 2;
	const int maxn = 1e4+5;
	node_t nd[maxn];
	int m, top;

	int newNode() {
		#ifdef DEBUG
		assert(m < maxn);
		#endif
		nd[m].link = 0;
		nd[m].w = "";
		memset(nd[m].nxt, 0, sizeof(nd[m].nxt));
		return m++;
	}

	void init() {
		m = 0;
		newNode();
		// initial \perp
		newNode();
		rep(i, 0, maxch) nd[head].nxt[i] = root;
		newNode();
		nd[root].link = head;
		top = root;
	}

	inline int g(int p, int id) {
		return nd[p].nxt[id];
	}

	void Insert(char ch) {
		int id = getId(ch);
		int p = top, q, oldq = -1;

		while (!g(p, id)) {
			q = newNode();
			nd[p].nxt[id] = q;
			nd[q].w = nd[p].w + ch;
			if (p != top)
				nd[oldq].link = q;
			oldq = q;
			p = nd[p].link;
		}
		#ifdef DEBUG
		assert(oldq != -1);
		#endif
		nd[oldq].link = g(p, id);
		top = g(top, id);
	}

	void Build(char *s) {
		init();
		while (*s) {
			Insert(*s);
			++s;
		}
	}

	void Build(string s) {
		init();
		int len = s.length();

		for (int i=0; i<len; ++i) {
			Insert(s[i]);
		}
	}

	void traverse() {
		int p = top;

		while (p != root) {
			printf("%s\n", nd[p].w.c_str());
			p = nd[p].link;
		}
	}
};

namespace Tree {
	struct node_t {
		int nxt[maxch];
		int link;
		int l, r;
	};

	const int inf = 0x3f3f3f3f;
	const int head = 1;
	const int root = 2;
	const int maxn = 1e4+5;
	const int maxl = 205;
	char T[maxl];
	node_t nd[maxn];
	int m, last;

	int newNode() {
		memset(nd[m].nxt, 0, sizeof(nd[m].nxt));
		nd[m].l = nd[m].r = 0;
		nd[m].link = 0;
		return m++;
	}

	void init() {
		m = 0;
		newNode();
		newNode();
		newNode();
		rep(i, 0, maxch)
			nd[head].nxt[i] = root;
		nd[root].link = head;
	}

	pair<bool,int> testAndSplit(int s, pii pi, int t) {
		int k, p;
		tie(k, p) = pi;

		if (k <= p) {
			int _s = nd[s].nxt[getId(T[k])];
			int _k = nd[_s].l, _p = nd[_s].r;
			if (t == T[_k+p-k+1])
				return mp(true, s);

			int r = newNode();
			nd[r].l = _k, nd[r].r = _k+p-k;

			nd[s].nxt[getId(T[k])] = r;
			nd[_s].l = _k+p-k+1;
			nd[_s].r = _p;
			nd[r].nxt[getId(T[_k+p-k+1])] = _s;

			return mp(false, r);

		} else if (!nd[s].nxt[getId(t)]) {
			return mp(false, s);
		} else {
			return mp(true, s);
		}
	}

	pii canonize(int s, pii pi) {
		int k, p;

		tie(k, p) = pi;
		if (p < k)
			return mp(s, k);

		int _s = nd[s].nxt[getId(T[k])];
		int _k = nd[_s].l, _p = nd[_s].r;

		while (_p-_k <= p-k) {
			k = k + _p - _k + 1;
			s = _s;
			if (k <= p) {
				_s = nd[s].nxt[getId(T[k])];
				_k = nd[_s].l, _p = nd[_s].r;
			}
		}

		return mp(s, k);
	}

	pii update(int s, pii p) {
		int k, i;
		int oldr = root;
		bool ep;
		int r, _r;

		tie(k, i) = p;
		int id = getId(T[i]);
		tie(ep, r) = testAndSplit(s, mp(k, i-1), T[i]);

		while (!ep) {
			_r = newNode();
			nd[_r].l = i, nd[_r].r = inf;
			nd[r].nxt[id] = _r;
			if (oldr != root)
				nd[oldr].link = r;
			oldr = r;
			tie(s, k) = canonize(nd[s].link, mp(k, i-1));
			tie(ep, r) = testAndSplit(s, mp(k, i-1), T[i]);
		}

		if (oldr != root)
			nd[oldr].link = s;

		return mp(s, k);
	}

	void Build(const char* T) {
		init();
		int len = strlen(T);
		#ifdef DEBUG
		assert(len+1 < maxl);
		#endif
		strcpy(Tree::T+1, T);
		int s = root, k = 1;

		rep(i, 1, len+1) {
			tie(s, k) = update(s, mp(k, i));
			tie(s, k) = canonize(s, mp(k, i));
		}
	}

	void Build(string T) {
		init();
		int len = T.length();
		#ifdef DEBUG
		assert(len+1 < maxl);
		#endif
		strcpy(Tree::T+1, T.c_str());
		int s = root, k = 1;

		rep(i, 1, len+1) {
			tie(s, k) = update(s, mp(k, i));
			tie(s, k) = canonize(s, mp(k, i));
		}

		last = 3;
	}

	void traverse() {
		int p = last;

		while (p != root) {
			int l = nd[p].l;
			int r = nd[p].r;
			string s(T+l, r-l+1);
			cout << s << endl;
			p = nd[p].link;
		}
	}
};

void test_trie(string s) {
	Trie::Build(s);
	Trie::traverse();
}

void test_tree(string s) {
	Tree::Build(s);
	Tree::traverse();
}

int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	#ifdef DEBUG
		freopen("data.in", "r", stdin);
		freopen("data.out", "w", stdout);
	#endif

	string s;

	cin >> s;
	//test_trie(s);
	test_tree(s);

	#ifdef DEBUG
		printf("time = %ldms.\n", clock());
	#endif

	return 0;
}
