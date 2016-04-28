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

#define DEBUG

const int INF = 0x3f3f3f3f;
const int maxn = 405;
int dp[maxn][maxn];

inline int calcScore(char a, char b) {
	if (a == b)	return 1;
	return -1;
}

int needlman(const string& sa, const string& sb) {
	const int alen = sa.length();
	const int blen = sb.length();
	const int mlen = min(alen, blen);

	rep(i, 0, alen+1) dp[0][i] = -i;
	rep(j, 0, blen+1) dp[j][0] = -j;

	rep(i, 1, alen+1) {
		rep(j, 1, blen+1) {
			dp[i][j] = max(dp[i-1][j-1]+calcScore(sa[i-1], sb[j-1]), max(dp[i-1][j], dp[i][j-1])-1);
		}
	}

	#ifdef DEBUG
	rep(i, 1, mlen+1) {
		rep(j, 1, mlen+1) {
			printf("%3d ", dp[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');
	#endif

	return dp[mlen][mlen];
}

int myfunc(const string& sa, const string& sb) {
	const int alen = sa.length();
	const int blen = sb.length();
	const int mlen = min(alen, blen);
	vi dp[2];
	int p = 0, q = 1;

	rep(i, 0, 5) dp[0].pb(0), dp[1].pb(0);

	dp[0][2] = 0;
	dp[0][3] = -1;
	dp[0][4] = -2;
	rep(i, 1, alen+1) {
		int bj = max(1, i-2);
		for (int j=bj; j<=mlen&&j<=i+2; ++j) {
			int k = j - i + 2;
			dp[q][k] = dp[p][k] + calcScore(sa[i-1], sb[j-1]);
			if (j <= i+1)
				dp[q][k] = max(dp[q][k], dp[p][k+1]-1);
			if (j > bj)
				dp[q][k] = max(dp[q][k], dp[q][k-1]-1);
		}
		p ^= 1;
		q ^= 1;
		#ifdef DEBUG
		{
			int j = 0;

			while (j++ < i-2) printf("    ");
			while (j<=mlen && j<=i+2) {
				int k = j - i + 2;
				printf("%3d ", dp[p][k]);
				++j;
			}
			while (j++ <= mlen) printf("    ");
			putchar('\n');
		}
		#endif
	}

	return dp[p][2];
}

int main(int argc, char **argv) {
	freopen("data.out", "w", stdout);

	string filename("/home/turf/Code/Introduction_to_Algorithms/MM2_dna/data2.in");

	if (argc > 1) filename = string(argv[1]);

	ifstream fin(filename.c_str());
	string read, ref;
	int s1, s2;

	while (getline(fin, read)) {
		getline(fin, ref);
		s1 = needlman(ref, read);
		s2 = myfunc(ref, read);
		printf("s1 = %d, s2 = %d\n", s1, s2);
		break;
	}
	return 0;
}
