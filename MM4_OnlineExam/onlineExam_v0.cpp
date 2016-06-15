#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <deque>
#include <bitset>
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

// #define DEBUG
#define SLICELEN 41

const int n = 5000;
const int K = 2000;
const int Bound = 4000;
char s[n + 1];
int visit[n + 1];

#ifdef DEBUG
char d[n+5];
int res = 0;
#endif

#ifdef DEBUG
void putln(char *s) {
	int c = 0;
	
	assert(s[n] == '\0');
	rep(i, 0, n)
		assert(s[i]=='0' || s[i]=='1');
	
	rep(i, 0, n) {
		if (s[i] != d[i]) ++c;
		if (c == K) {
			res = i + 1;
			return ;
		}
	}
	
	res = n + 1;
}
#else
void putln(char *s) {
	puts(s);
	fflush(stdout);
}
#endif

#ifdef DEBUG
int getResult() {
	return res;
}
#else
int getResult() {
	int ret = 0;
	scanf("%d", &ret);
	return ret;
}
#endif

void flip(const int b, const int l) {
	rep(j, 0, l) {
		s[b+j] = ((s[b+j]-'0')^1) + '0';
	}
}

void solve() {
	const int l = SLICELEN;
	int k, kk;
	
	memset(visit, -1, sizeof(visit));
	memset(s, '0', sizeof(s));
	s[n] = '\0';
	putln(s);
	kk = getResult();
	if (kk > n) return ;
	visit[kk-1] = (s[kk-1] - '0') ^ 1;
	int c = 1, b = 0;
	
	while (c < 99) {
		if (b+l >= kk) {
			int tmpl = kk - 1 - b;
			#ifdef DEBUG
			assert(visit[kk-1] != -1);
			#endif
			s[kk-1] = visit[kk-1] + '0';
			flip(b, tmpl);
			putln(s);
			k = getResult();
			if (k > n) return ;
			if (k < kk+1) flip(b, tmpl);
			visit[k-1] = (s[k-1] - '0') ^ 1;
			++c;
			b = kk;
		} else {
			flip(b, l);
			putln(s);
			k = getResult();
			if (k > n) return ;
			if (k < kk) flip(b, l);
			visit[k-1] = (s[k-1] - '0') ^ 1;
			++c;
			b += l;
		}
		
	#ifdef DEBUG
	fprintf(stdout, "b = %d, kk = %d, k = %d\n", b, kk, k);
	fflush(stdout);
	#endif
		kk = max(k, kk);
	}

	rep(i, 0, n)
		if (visit[i] != -1)
			s[i] = visit[i] + '0';
	putln(s);
	k = getResult();
	
	kk = max(k, kk);
	
	#ifdef DEBUG
	fprintf(stdout, "Bestscore = %d\n", kk);
	#endif
}

int main() {
	ios::sync_with_stdio(false);
	#ifdef DEBUG
		freopen("data.in", "r", stdin);
		freopen("data.out", "w", stdout);
	#endif
	
#ifdef DEBUG
	int t;
	
	scanf("%d", &t);
	while (t--) {
		scanf("%s", d);
		solve();
	}
#else
	solve();
#endif
	
	
	#ifdef DEBUG
		printf("time = %ldms.\n", clock());
	#endif
	
	return 0;
}
