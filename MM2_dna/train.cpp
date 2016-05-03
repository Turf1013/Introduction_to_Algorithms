#include <bits/stdc++.h>
using namespace std;

#define sti				set<int>
#define stpii			set<pair<int, int> >
#define mpii			map<int,int>
#define vi				vector<int>
#define vstr			vector<string>
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

// #define DEBUG

struct Entry_t {
	int from, to;
	char strand;
	string read;
	
	void print() const {
		cout << from << ',' << to << ','
			 << strand << ',' << read << endl;
	}

	friend bool operator< (const Entry_t& a, const Entry_t& b) {
		return a.from < b.from;
	}
};

const string FILE_PATH = "./example/";
const int slice_len = 1050;
const int read_len = 150;
const int sep_len = 10;
int charId[128];
vector<Entry_t> vread[25];
vi score[25];
vi read_dif[25];
vi slice_dif[25];
string seq;

void init() {
	rep(i, 0, 128) charId[i] = 4;
	charId['A'] = 0;
	charId['C'] = 1;
	charId['G'] = 2;
	charId['T'] = 3;
}

/**
	\brief get the complement of char
*/
inline char getComplement(char ch) {
	if (ch == 'A')	return 'T';
	if (ch == 'T')	return 'A';
	if (ch == 'G')	return 'C';
	if (ch == 'C')	return 'G';
	return ch;
}

/**
	\brief check if is the valid char
*/
inline bool isValid(char ch) {
	return (ch=='A') || (ch=='G') || (ch=='C') || (ch=='T');
}

/**
	\brief	get the reverse complement of original string
*/
string getReverseComplement(const string& s) {
	int len = SZ(s);
	string ret;
	
	per(i, 0, len) ret.pb(getComplement(s[i]));
	
	return ret;
}

/**
	\brief	parse the line into entry
*/
int parseEntry(const string& line, Entry_t& entry) {
	int len = line.length();
	int i = 0, j = 0, cnt = 0;
	int ret = 0;

	while (1) {
		if (i==len || line[i]==',') {
			string str = line.substr(j, i-j);
			if (cnt == 1) {
				ret = stoi(str);
			} else if (cnt == 2) {
				entry.from = stoi(str);
			} else if (cnt == 3) {
				entry.to = stoi(str);
			} else if (cnt == 4) {
				entry.strand = str[0];
			} else if (cnt == 5) {
				entry.read = str;
			}
			j = i + 1;
			++cnt;
		}
		
		if (i++ == len)	break;
	}

	return (cnt==6) ? ret : 0;
}

void getRead(const string& filename) {
	ifstream fin(filename);
	Entry_t e;
	string line;

	if (!fin.is_open())	{
		cout << filename << " not exists." << endl;
		return ;
	}

	while (getline(fin, line)) {
		if (line.back() == '\r')	line.erase(SZ(line) - 1);
		int id = parseEntry(line, e);
		if (id)
			vread[id].pb(e);
	}

	fin.close();
}

void getChromatSeq(const int chrId) {
	const string filename = FILE_PATH + "chromatid" + to_string(chrId) + ".fa";
	ifstream fin(filename);
	string line;

	if (!fin.is_open()) {
		cout << filename << " not exists" << endl;
		abort();
	}

	seq.clr();

	// skip header
	getline(fin, line);

	while (getline(fin, line)) {
		if (line.back() == '\r') line.erase(SZ(line) - 1);
		if (line.length())
			seq.append(line);
	}

	fin.close();
}

inline int calcScore(char a, char b) {
	if (a == b)	return 1;
	return -1;
}

int calcScore(const string& sa, const string& sb) {
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
	}

	return dp[p][2];
}

int calcSliceDiff(const string& a, const string& b) {
	const int alen = a.length();
	const int blen = b.length();
	unordered_map<string,int> tba;
	unordered_map<string,int> tbb;
	unordered_map<string,int>::iterator itera, iterb;

	for (int i=0; i<alen-sep_len+1; ++i) {
		string str = a.substr(i, sep_len);
		++tba[str];
	}

	for (int i=0; i<blen-sep_len+1; ++i) {
		string str = b.substr(i, sep_len);
		++tbb[str];
	}

	int ret = 0;

	for (iterb=tbb.begin(); iterb!=tbb.end(); ++iterb) {
		itera = tba.find(iterb->fir);
		if (itera == tba.end()) {
			ret += iterb->sec;
		} else {
			ret += itera->sec > iterb->sec ? 0 : iterb->sec - itera->sec;
			tba.erase(itera);
		}
	}

	for (itera=tba.begin(); itera!=tba.end(); ++itera)
		ret += itera->sec >> 2;
	
	return ret;
}

int calcReadDiff(const string& a, const string& b) {
	int ca[5], cb[5];

	memset(ca, 0, sizeof(ca));
	int alen = a.length();
	rep(i, 0, alen) ++ca[charId[a[i]]];

	memset(cb, 0, sizeof(cb));
	int blen = b.length();
	rep(i, 0, blen) ++cb[charId[b[i]]];

	int ret = 0;

	rep(i, 0, 5) ret += abs(ca[i] - cb[i]) << 2;

	return ret;
}

void train(const int chrId) {
	const vector<Entry_t> vent = vread[chrId];
	const int sz = SZ(vent);
	string read;

	getChromatSeq(chrId);
	rep(i, 0, sz) {
		const int from = vent[i].from - 1;
		const int to = vent[i].to - 1;
		if (vent[i].strand == '+')
			read = vent[i].read;
		else
			read = vent[i].read;	//getReverseComplement(vent[i].read);
		string str = seq.substr(from, read_len);

		#ifdef DEBUG
		cout << from+1 << " " << to+1 << endl;
		cout << read << endl;
		cout << str << endl;
		cout << endl;
		#endif
		
		score[chrId].pb(calcScore(str, read));
		read_dif[chrId].pb(calcReadDiff(str, read));
		str.clr();

		str = seq.substr(from/slice_len*slice_len, slice_len);
		slice_dif[chrId].pb(calcSliceDiff(str, read));

		if (i>0 && i%500==0) {
			cerr << "train: " << i << endl;
		}
	}
	seq.clr();
}

void train(const string& prefix, const vi& vid) {
	const int sz = SZ(vid);

	rep(i, 0, sz) {
		const string filename = FILE_PATH + prefix + "/" + prefix + to_string(vid[i]) + ".minisam";
		getRead(filename);
	}

	rep(i, 1, 25) {
		if (SZ(vread[i]) == 0)
			continue;

		train(i);
	}
}

void dumpResult(const string& prefix) {
	int sz;

	// dumpscore
	{
		const string filename = "./" + prefix + "_func_score.log";
		ofstream fout(filename);

		if (!fout.is_open()) {
			cerr << filename << " can't open." << endl;
			abort();
		}
		rep(j, 1, 25) {
			sz = SZ(score[j]);
			fout << "--->" << j << "<---" <<endl;
			rep(i, 0, sz) {
				fout << score[j][i] << " ";
			}
			fout << endl;
		}

		fout.close();
	}

	// dump read diff
	{
		const string filename = "./" + prefix + "_read_score.log";
		ofstream fout(filename);

		if (!fout.is_open()) {
			cerr << filename << " can't open." << endl;
			abort();
		}
		rep(j, 1, 25) {
			sz = SZ(read_dif[j]);
			fout << "--->" << j << "<---" <<endl;
			rep(i, 0, sz) {
				fout << read_dif[j][i] << " ";
			}
			fout << endl;
		}

		fout.close();
	}

	// dump slice diff
	{
		const string filename = "./" + prefix + "_slice_score.log";
		ofstream fout(filename);

		if (!fout.is_open()) {
			cerr << filename << " can't open." << endl;
			abort();
		}
		rep(j, 1, 25) {
			sz = SZ(slice_dif[j]);
			fout << "--->" << j << "<---" <<endl;
			rep(i, 0, sz) {
				fout << slice_dif[j][i] << " ";
			}
			fout << endl;
		}

		fout.close();
	}
}

void _train(int testDifficulty) {
	vi vc;

	if (testDifficulty == 0) {
		#ifdef DEBUG
		rep(i, 5, 6) vc.pb(i);
		train("test", vc);
		dumpResult("test");
		#else
		rep(i, 5, 11) vc.pb(i);
		train("small", vc);
		dumpResult("small");
		#endif

		
	} else if (testDifficulty == 1) {
		rep(i, 5, 11) vc.pb(i);
		train("medium", vc);
		dumpResult("medium");
	}
}

int main(int argc, char **argv) {
	#ifdef DEBUG
	freopen("data.out", "w", stdout);
	#endif

	int testDifficulty = 1;

	if (argc > 1) testDifficulty = stoi(argv[1]);

	init();
	_train(testDifficulty - 1);

	return 0;
}