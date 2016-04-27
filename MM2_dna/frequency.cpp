/**
	Calculate the frequencey about `MM-DNA`
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

#define DEBUG

#define WINDOWS
// #define LINUX

#ifdef WINDOWS
	const string DATA_PREFIX = "I:/TCO-MM/";
#else 
	const string DATA_PREFIX = "/home/turf/Code/Introduction_to_Algorithms/MM2_dna/";
#endif /* WINDOWS */

struct TestCase_t {
	const string fa1, fa2, minisam;
	
	TestCase_t(const string fa1, const string fa2, const string minisam):
		fa1(fa1), fa2(fa2), minisam(minisam) {}
};

const string READ_PATH = DATA_PREFIX + "example/";
const string REFE_PATH = READ_PATH + "chromatid";
TestCase_t smallCase (
	READ_PATH + "small5.fa1", 
	READ_PATH + "small5.fa2", 
	READ_PATH + "small5.minisam"
);
TestCase_t mediumCase (
	READ_PATH + "medium5.fa1", 
	READ_PATH + "medium5.fa2", 
	READ_PATH + "medium5.minisam"
);
TestCase_t largeCase (
	READ_PATH + "large5.fa1",
	READ_PATH + "large5.fa2", 
	READ_PATH + "large5.minisam"
);

struct Chars_t {
	double a, g, c, t;
	Chars_t() {}
	Chars_t(double a, double g, double c, double t):
		a(a), g(g), c(c), t(t) {}
};

#define LOGFILENAME "freq.log"

typedef vector<string> vstr;
typedef long long LL;
FILE *logout;
LL C[26];
vi chrIds;

/**
	\brief	calculate the frequency of chromat
*/
void calcFreq_chr(int chrId) {
	char ss[24];
	
	sprintf(ss, "%d", chrId);
	string filename = REFE_PATH + string(ss) + ".fa";
	ifstream fin(filename);
	
	if (!fin.is_open()) {
		fprintf(stderr, "%s not exists.\n", filename.c_str());
		abort();
	}
	
	string line;
	
	// skip the header
	getline(fin, line);
	
	memset(C, 0, sizeof(C));
	while (getline(fin, line)) {
		if (line.rbegin() == '\r') line.erase(line.length() - 1);
		int len = line.length();
		rep(i, 0, len) ++C[line[i]-'A'];
	}
	
	LL tot = 0;
	rep(i, 0, 26) tot += C[i];
	
	printf("\nchromatId = %d\n", chrId);
	// frequency of character
	puts("\nFrequency of characters:")
	rep(i, 0, 26) {
		if (C[i]) {
			printf("%c: %.4lf  ", i+'A', C[i]/(double)tot);
		}
	}
	putchar('\n');
	tot -= C['N'-'A'];
	printf("A+T: %.4lf  C+G: %.4lf\n", (C['A'-'A']+C['T'-'A'])/(double)tot, (C['C'-'A']+C['G'-'A'])/(double)tot);
	
	// 
	
	putchar('\n');
}

void calcFreq_chr() {
	int sz = SZ(chrIds);
	
	rep(i, 0, sz) {
		calcFreq_chr(chrIds[i]);
	}
}

/**
	\brief	calculate the frequency of read
*/
void calcFreq_read(const int testDifficulty) {
	const TestCase_t& tcase = (testDifficulty==0) ? smallCase :
							  (testDifficulty==1) ? mediumCase : largeCase;
	
}

void _calcFrequency(const int testDifficulty) {
	/**
		\step 1: calculate `AGCT` frequency in chromatid
	*/
	calcFreq_chr();
	
	/**
		\step 1: calculate `AGCT` frequency in chromatid
	*/
	calcFreq_read(testDifficulty);
}

void calcFrequency(const int testCase) {
	bool visit[10];
	int x = testCase;
	
	memset(visit, false, sizeof(visit));
	while (x) {
		visit[x % 10] = true;
		x /= 10;
	}
	
	rep(i, 1, 4) if (visit[i]) _calcFrequency(i - 1);
}

void init_log() {
	logout = fopen(LOGFILENAME, "w");
	if (!logout) {
		fprintf(stderr, "%s not exists.\n", LOGFILENAME);
		abort();
	}
}

void close_log() {
	fclose(logout);
}

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	#ifndef ONLINE_JUDGE
		freopen("data.in", "r", stdin);
		freopen("data.out", "w", stdout);
	#endif
	
	init_log();
	
	const int testCase = 1;
	
	calcFrequency(testCase);
	
	close_log();
	
	#ifndef ONLINE_JUDGE
		printf("time = %ldms.\n", clock());
	#endif
	
	return 0;
}
