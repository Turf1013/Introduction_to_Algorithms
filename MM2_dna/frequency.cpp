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

// #define WINDOWS
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

struct Freq_t {
	double a, g, c, t;
	
	Freq_t() {}
	Freq_t(double a, double g, double c, double t):
		a(a), g(g), c(c), t(t) {}
		
	double len4() const {
		return sqrt(a*a+g*g+c*c+t*t);
	}
	
	double len2() const {
		return sqrt((a+t)*(a+t) + (c+g)*(c+g));
	}
};

#define LOGFILENAME "freq.log"

typedef vector<string> vstr;
typedef long long LL;
FILE *logout;
LL C[26];
vi chrIds;
vector<Freq_t> vfreq_chr(25, Freq_t());

/**
	\brief	calculate the frequency of chromat
*/
void calcFreq_chr(int chrId) {
	string filename = REFE_PATH + to_string(chrId) + ".fa";
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
		if (line.back() == '\r') line.erase(line.length() - 1);
		int len = line.length();
		rep(i, 0, len) ++C[line[i]-'A'];
	}
	
	LL tot = 0;
	rep(i, 0, 26) tot += C[i];
	
	printf("\nchromatId = %d\n", chrId);
	// frequency of character
	puts("\nFrequency of characters:");
	rep(i, 0, 26) {
		if (C[i]) {
			printf("%c: %.4lf  ", i+'A', C[i]/(double)tot);
		}
	}
	putchar('\n');
	tot -= C['N'-'A'];
	assert(tot > 0);
	printf("A+T: %.4lf  C+G: %.4lf\n", (C['A'-'A']+C['T'-'A'])/(double)tot, (C['C'-'A']+C['G'-'A'])/(double)tot);
	vfreq_chr[chrId].a = C['A'-'A'] / (double) tot;
	vfreq_chr[chrId].c = C['C'-'A'] / (double) tot;
	vfreq_chr[chrId].g = C['G'-'A'] / (double) tot;
	vfreq_chr[chrId].t = C['T'-'A'] / (double) tot;

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
    \brief	Cosine similarity of 4
*/
double similarity4(const Freq_t& a, const Freq_t& b) {
	return (a.a*b.a + a.c*b.c+ a.g*b.g + a.t*b.t) / (a.len4() * b.len4());
}

double similarity2(const Freq_t& a, const Freq_t& b) {
	return ((a.a+a.t)*(b.a+b.t) + (a.c+a.g)*(b.c+b.g)) / (a.len2() * b.len2());
}

/**
	\brief	split the line with ','
*/
vstr split(const string& line, char ch) {
	int len = line.length();
	int i = 0, j = 0;
	vstr ret;
	
	while (1) {
		if (i==len || line[i]==ch) {
			string str = line.substr(j, i-j);
			ret.pb(str);
			j = i + 1;
		}
		
		if (i++ == len)	break;
	}
	
	return ret;
}


/**
	\brief	calculate the frequency of read
*/
void calcFreq_read(const int testDifficulty) {
	const TestCase_t& tcase = (testDifficulty==0) ? smallCase :
							  (testDifficulty==1) ? mediumCase : largeCase;
	int nread = 0;
	vector<Freq_t> vfreq_read[25];
	const string& filename = tcase.minisam;
	ifstream fin(filename);
	string line;
	
	if (!fin.is_open()) {
		fprintf(stderr, "%s not exists.\n", filename.c_str());
		abort();
	}
	
	while (getline(fin, line)) {
		vstr vsub = split(line, ',');
		int chrId = stoi(vsub[1]);
		const string& read = vsub[SZ(vsub) - 1];
		const int len = read.length();
		C['A'-'A'] = C['C'-'A'] = C['G'-'A'] = C['T'-'A'] = 0;
		rep(i, 0, len) ++C[read[i] - 'A'];
		vfreq_read[chrId].pb(
			Freq_t(
				C['A'-'A'] / (double) len,
				C['G'-'A'] / (double) len,
				C['C'-'A'] / (double) len,
				C['T'-'A'] / (double) len
			)
		);
		++nread;
	}

	double sim4_tot = 0, sim2_tot = 0;

	for (int chrId : chrIds) {
		int sz = SZ(vfreq_read[chrId]);
		if (sz == 0)
			continue;

		const Freq_t& freq_chr = vfreq_chr[chrId];
		rep(i, 0, sz) {
			const Freq_t& freq_read = vfreq_read[chrId][i];
			double sim4 = similarity4(freq_chr, freq_read);
			double sim2 = similarity2(freq_chr, freq_read);
			fprintf(logout, "[chr%d-%d] sim2 = %.4lf, sim4 = %.4lf\n", chrId, i, sim2, sim4);
			sim4_tot += sim4;
			sim2_tot += sim2;

			// compare to other chr;
			if (SZ(chrIds) == 1)
				continue;
			fprintf(logout, "\t");
			double mx4 = sim4, mx4_ = -1;
			double mx2 = sim2, mx2_ = -1;
			int v4 = chrId, v4_ = -1;
			int v2 = chrId, v2_ = -1;

			for (int j : chrIds) {
				if (j == chrId)
					continue;
				double sim4 = similarity4(vfreq_chr[j], freq_read);
				double sim2 = similarity2(vfreq_chr[j], freq_read);
				fprintf(logout, " (%.4lf, %.4lf)", sim2, sim4);

				if (sim4 > mx4) {
					mx4_ = mx4;
					v4_ = v4;
					mx4 = sim4;
					v4 = j;
				} else if (sim4 > mx4_) {
					mx4_ = sim4;
					v4_ = j;
				}

				if (sim2 > mx2) {
					mx2_ = mx2;
					v2_ = v2;
					mx2 = sim2;
					v2 = j;
				} else if (sim2 > mx2_) {
					mx2_ = sim2;
					v2_ = j;
				}
			}
			fprintf(logout, "\n");
			fprintf(logout, "\tmx4 = %.4lf, v4 = %d, mx4_ = %.4lf, v4_ = %d, "
						"mx2 = %.4lf, v2 = %d, mx2_ = %.4lf, v2_ = %d\n",
						mx4, v4, mx4_, v4_, mx2, v2, mx2_, v2_);
		}
	}

	double sim4_avg = sim4_tot / nread;
	double sim2_avg = sim2_tot / nread;
	printf("sim4_avg = %.4lf, sim2_avg = %.4lf\n", sim4_avg, sim2_avg);
	fprintf(logout, "sim4_avg = %.4lf, sim2_avg = %.4lf\n", sim4_avg, sim2_avg);
}

void init(const int testDifficulty) {
	chrIds.clr();

	if (testDifficulty == 0) {
		chrIds.pb(20);
	} else if (testDifficulty == 1) {
		chrIds.pb(1);
		chrIds.pb(11);
		chrIds.pb(20);
	} else {
		rep(i, 1, 25) chrIds.pb(i);
	}
}

void _calcFrequency(const int testDifficulty) {

	/**
		\step 0: initial
	*/
	init(testDifficulty);

	/**
		\step 1: calculate `AGCT` frequency in chromatid
	*/
	calcFreq_chr();
	
	/**
		\step 2: calculate `AGCT` frequency in chromatid
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

void dumpFreq_chr() {
	chrIds.clr();
	rep(i, 1, 25) chrIds.pb(i);
	calcFreq_chr();

	rep(chrId, 1, 25) {
		const Freq_t& f = vfreq_chr[chrId];
		fprintf(logout, "a = %.4lf, t = %.4lf, c = %.4lf, g = %.4lf, a+t = %.4lf, c+g = %.4lf\n",
			f.a, f.t, f.c, f.g, f.a+f.t, f.c+f.g);
	}
	fflush(logout);
}

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	
	init_log();
	
	int testCase = (argc > 1) ? stoi(argv[1]) : 1;
	
	calcFrequency(testCase);

	// dumpFreq_chr();
	
	close_log();
	
	#ifndef ONLINE_JUDGE
		printf("time = %lds.\n", clock()/CLOCKS_PER_SEC);
	#endif
	
	return 0;
}
