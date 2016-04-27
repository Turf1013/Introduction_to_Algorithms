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

struct Entry_t {
	int simId, faId;
	int chrId;
	int from, to;
	char strand;
	string read;
	
	void print() const {
		cout << simId+1 << '/' << faId+1 << ','
			 << chrId << ',' << from << ',' << to << ','
			 << strand << ',' << read << endl;
	}
};

typedef long long LL;
typedef vector<Entry_t> ventry;
ventry vent;
vector<string> vread[2];
vector<string> vrefe;
vi chrIds;
int chScore[5][5];

void initScore() {
	rep(i, 0, 5) {
		rep(j, 0, 5)
			chScore[i][j] = -1;
		chScore[i][i] = 1;
	}
}

inline int getCharId(char ch) {
	if (ch == 'A')	return 0;
	if (ch == 'G')	return 1;
	if (ch == 'C')	return 2;
	if (ch == 'T')	return 3;
	return 4;
}

int calcScore(char a, char b) {
	return chScore[getCharId(a)][getCharId(b)];
}

/**
	\brief get the content of chromatid
*/
void getRefer(const int chrId, vstr& refe) {
	refe.clr();
	string filename = REFE_PATH + to_string(chrId) + ".fa";
	string line;
	ifstream fin(filename);

	if (!fin.is_open()) {
		cerr << filename << " not exists." << endl;
		abort();
	}

	// skip header
	getline(fin, line);

	while (getline(fin, line)) {
		if (line.back() == '\r') line.erase(SZ(line) - 1);
		refe.pb(line);
	}

	fin.close();
}

void getRefer(const string& filename, vstr& refe) {
	refe.clr();
	string line;
	ifstream fin(filename);

	if (!fin.is_open()) {
		cerr << filename << " not exists." << endl;
		abort();
	}

	// skip header
	getline(fin, line);

	while (getline(fin, line)) {
		if (line.back() == '\r') line.erase(SZ(line) - 1);
		refe.pb(line);
	}

	fin.close();
}

vstr getRefer(const string& filename) {
	vstr refe;
	string line;
	ifstream fin(filename);

	if (!fin.is_open()) {
		cerr << filename << " not exists." << endl;
		abort();
	}

	// skip header
	getline(fin, line);

	while (getline(fin, line)) {
		if (line.back() == '\r') line.erase(SZ(line) - 1);
		refe.pb(line);
	}

	fin.close();

	return refe;
}

vstr getRefer(const int chrId) {
	vstr refe;
	string filename = REFE_PATH + to_string(chrId) + ".fa";
	string line;
	ifstream fin(filename);

	if (!fin.is_open()) {
		cerr << filename << " not exists." << endl;
		abort();
	}

	// skip header
	getline(fin, line);

	while (getline(fin, line)) {
		if (line.back() == '\r') line.erase(SZ(line) - 1);
		refe.pb(line);
	}

	fin.close();

	return refe;
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
	\brief 	get the read from *.fa
	\param	filename: name of *.fa
			vc: container to store the genome
*/
void getRead(const string& filename, vstr& vc) {
	ifstream fin(filename);
	vc.clr();
	string line;
	
	if (!fin.is_open()) {
		cerr << filename << " not exists." << endl;
		abort();
	}
	
	while (getline(fin, line)) {
		// skip the header
		getline(fin, line);
		if (line.back() == '\r')	line.erase(SZ(line) - 1);
		vc.pb(line);
	}
	
	fin.close();
}

/**
	\brief	parse the line into entry
*/
bool parseEntry(const string& line, Entry_t& entry) {
	int len = line.length();
	int i = 0, j = 0, cnt = 0;
	
	while (1) {
		if (i==len || line[i]==',') {
			string str = line.substr(j, i-j);
			if (cnt == 0) {
				entry.faId = str.back() - '1';
				entry.simId = stoi(str.substr(3, str.length()-5)) - 1;
			} else if (cnt == 1) {
				entry.chrId = stoi(str);
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

	return cnt==6;
}

/**
	\brief 	get the entry from *.minisam
	\param	filename of *.minisam
*/
void getEntry(const string& filename) {
	ifstream fin(filename);
	vent.clr();
	Entry_t entry;
	string line;
	
	if (!fin.is_open()) {
		cerr << filename << " not exists." << endl;
		abort();
	}
	
	while (getline(fin, line)) {
		if (parseEntry(line, entry))
			vent.pb(entry);
	}
	
	fin.close();
}

/**
	\brief init
*/
void init(int testDifficulty) {
	const TestCase_t& tcase = (testDifficulty==0) ? smallCase :
							  (testDifficulty==1) ? mediumCase : largeCase;

	getRead(tcase.fa1, vread[0]);
	getRead(tcase.fa2, vread[1]);
	getEntry(tcase.minisam);

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

/**
	\brief check the entry[-]'s string equal to his `Reverse Complement`
*/
bool check_RC(const Entry_t& entry) {
	assert(entry.faId>=0 && entry.faId<2);
	assert(entry.simId>=0 && entry.simId<SZ(vread[entry.faId]));

	const string& org = vread[entry.faId][entry.simId];
	string tmp = getReverseComplement(org);

	// #ifdef DEBUG
	// 	static int cnt = 0;
	// 	if (cnt++ <= 3) {
	// 		entry.print();
	// 		printf("rc = %s\n", tmp.c_str());
	// 	}
	// #endif
	return tmp == entry.read;
}

/**
	\brief obsevation the [-]是否表示原串的Reverse Complement
*/
void observe_RC() {
	int sz = SZ(vent);
	int tot = 0, correct = 0;

	rep(i, 0, sz) {
		const Entry_t& entry = vent[i];
		if (entry.strand == '-') {
			if (check_RC(entry))
				++correct;
			++tot;
		}
	}

	printf("observe-RC [-]: tot = %d, correct = %d\n", tot, correct);
}

void observe_strand() {
	int sz = SZ(vent);
	bool flag = true;

	for (int i=0; i<sz; i+=2) {
		const Entry_t& entry_1 = vent[i];
		const Entry_t& entry_2 = vent[i+1];
		if (entry_1.strand == entry_2.strand) {
			flag = false;
			break;
		}
	}

	printf("observe-strand [+/-]: %s\n", flag ? "YES":"NO");
}

void observe_positionLen() {
	int sz = SZ(vent);
	vi vc;

	rep(i, 0, sz) {
		const Entry_t& entry = vent[i];
		vc.pb(entry.to - entry.from + 1);
		// #ifdef DEBUG
		// if (entry.to - entry.from + 1 != 150)
		// 	printf("sim%d/%d\n", entry.simId+1, entry.faId+1);
		// #endif
	}

	sort(all(vc));
	int n = unique(all(vc)) - vc.begin();
	printf("observe-positionLen : [%d, %d]\n", vc[0], vc[n-1]);
}

void observe_pairDis() {
	int sz = SZ(vent);
	int tmp, overlap = 0;
	vi vc;

	for (int i=0; i<sz; i+=2) {
		const Entry_t& entry_1 = vent[i];
		const Entry_t& entry_2 = vent[i+1];
		if (entry_1.from > entry_2.to)
			tmp = entry_1.from - entry_2.to - 1;
		else if (entry_2.from > entry_1.to)
			tmp = entry_2.from - entry_1.to - 1;
		else
			++overlap, tmp = -1;
		if (tmp > 0) vc.pb(tmp);
	}

	sort(all(vc));
	int n = unique(all(vc)) - vc.begin();
	printf("observe-pairDistance : overlap = %d, dis = [%d, %d]\n", overlap, vc[0], vc[n-1]);
}

void observe_refeUndef() {
	vstr refe;
	bool has = false;

	rep(i, 0, SZ(chrIds)) {
		int chrId = chrIds[i];
		getRefer(chrId);

		int sz = SZ(refe);
		int i = 0;

		while (i < sz) {
			const string& line = refe[i];
			const int len = line.length();
			int j = 0;

			while (j<len && line[j]=='N') ++j;
			if (j < len) {
				while (j<len && isValid(line[j])) ++j;
				has = j < len;
				break;
			}
			++i;
		}
		if (has) break;

		int k = sz - 1;
		while (k > i) {
			const string& line = refe[k];
			const int len = line.length();
			int j = len-1;

			while (j>=0 && line[j]=='N') --j;
			if (j >= 0) {
				while (j>=0 && isValid(line[j])) --j;
				has = j >= 0;
				break;
			}
			--k;
		}
		if (has) break;

		for (++i; i<k; ++i) {
			const string& line = refe[i];
			const int len = line.length();
			int j = len - 1;

			while (j<len && isValid(line[j])) ++j;
			if (j < len) {
				has = true;
				break;
			}
		}
		if (has) break;
	}

	printf("observe-referUndef : %s\n", has ? "YES":"NO");
}

void observe_alignScore() {
	int sz_ent = SZ(vent);
	vi alignId[25];
	vstr refe;
	vi pos;
	LL ptot, stot, tot;

	ptot = stot = tot = 0;
	rep(i, 0, sz_ent) alignId[vent[i].chrId].pb(i);

	rep(chrId, 1, 25) {
		int sz = SZ(alignId[chrId]);
		if (sz == 0)
			continue;

		// #ifdef DEBUG
		// sz = min(sz, 2);
		// #endif

		getRefer(chrId, refe);
		int nline = SZ(refe);
		pos.clr();
		pos.pb(refe[0].length());
		rep(i, 1, nline) pos.pb(pos.back() + refe[i].length());

		LL ptmp, stmp, tmp;

		ptmp = stmp = tmp = 0;
		rep(i, 0, sz) {
			const int& entId = alignId[chrId][i];
			const Entry_t& entry = vent[entId];
			// #ifdef DEBUG
			// 	entry.print();
			// #endif
			const string& read = entry.read;
			const int rlen = read.length();
			LL score = 0;

			int p = lower_bound(all(pos), entry.from) - pos.begin();
			assert(p < nline);
			int j = entry.from - 1 - (p==0 ? 0:pos[p-1]), k = 0;
			int len = refe[p].length();
			// #ifdef DEBUG
			// printf("p = %d, j = %d\n", p, j);
			// printf("line = %s\n", refe[p].c_str());
			// #endif

			while (k < rlen) {
				score += calcScore(refe[p][j], read[k]);
				// #ifdef DEBUG
				// putchar(refe[p][j]);
				// #endif
				++j;
				++k;
				if (j == len) {
					++p;
					assert(p < nline);
					len = refe[p].length();
					j = 0;
				}
			}
			// #ifdef DEBUG
			// putchar('\n');
			// #endif

			if (entry.strand == '+') 
				ptmp += score;
			else
				stmp += score;
			tmp += score;

			#ifdef DEBUG
			if (entry.simId <= 3)
				printf("sim%d/%d score = %lld\n", entry.simId+1, entry.faId+1, score);
			#endif
		}

		printf("chrId = %d, [+]-Score = %lld, [-]-Score = %lld, tot-Score = %lld\n", chrId, ptmp, stmp, tmp);
		ptot += ptmp;
		stot += stmp;
		tot += tmp;
	}
	printf("[+]-Score = %lld, [-]-Score = %lld, tot-Score = %lld\n", ptot, stot, tot);
}

void observe_substrFreq() {
	
}

/**
	\brief	the info need to observe
	\param	testDifficuly: 0-small, 1-medium, 2-large
*/
void _observation(int testDifficulty) {

	/**
		\step 0: init according testDifficuly
	*/
	init(testDifficulty);

	/**
		\step 1: 是否一个为[+],另一个为[-]
	*/
	observe_strand();

	/**
		\step 2: 长度是否一定为150
	*/
	observe_positionLen();	

	/**
		\step 3: read对的间距情况
	*/
	observe_pairDis();

	/**
		\step 4: [-] presents `Reverse Complement` ???
	*/
	observe_RC();

	/**
		\step 5: reference undef
	*/
	observe_refeUndef();

	/**
		\step 6: align score
	*/
	observe_alignScore();

	/**
		\step 7: count substring's frequency
	*/
	observe_substrFreq();
}

void observation(int testCase) {
	bool visit[10];
	
	memset(visit, false, sizeof(visit));
	while (testCase) {
		visit[testCase % 10] = true;
		testCase /= 10;
	}
	
	rep(i, 1, 4) {
		if (visit[i])
			_observation(i - 1);
	}
}

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	
	freopen("data.in", "r", stdin);

	initScore();
	int testCase = (argc>1) ? stoi(argv[1]) : 1;
	
	observation(testCase = 1);

	// init(0);
	// observe_alignScore();

	// string tmp = "TTGTGATGTTTGCATTCAAGTCACAGAATTGAACACTCCCTTTCACAGAGCAGGTTTGAAACACTCTTTTTGTAGTGTCTATAAGTGAACATTTGGCGTGCTTTCAGGCCTAAGGTGAAAAAGGAAATCTCTTCCCATAAAAACTAGACA";
	// string rc = getReverseComplement(tmp);
	// printf("rc = %s\n", rc.c_str());
	
	return 0;
}
