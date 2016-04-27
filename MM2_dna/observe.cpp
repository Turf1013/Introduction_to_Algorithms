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

// #define WINDOWS
// #define LINUX

#ifdef WINDOWS
	const string DATA_PREFIX = "I:/TCO-MM/";
#else 
	const string DATA_PREFIX = "~/Code/Introduction_to_Algorithms/MM2_dna/";
#endif /* WINDOWS */

struct TestCase_t {
	const string fa1, fa2, minisam;
	
	TestCase_t(const string fa1, const string fa2, const string minisam):
		fa1(fa1), fa2(fa2), minisam(minisam) {}
};

const string READ_PATH = DATA_PREFIX + "example/";
const string REFE_PATH = READ_PATH;
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
	
	void print() {
		cout << simId+1 << '/' << faId+1 << ','
			 << chrId << ',' << from << ',' << to << ','
			 << strand << ',' << read << endl;
	}
};

typedef vector<Entry_t> ventry;
ventry vent;
vector<string> vread[2];

/**
	\brief get the complement of char
*/
char getComplement(char ch) {
	if (ch == 'A')	return 'T';
	if (ch == 'T')	return 'A';
	if (ch == 'G')	return 'C';
	if (ch == 'C')	return 'G';
	return ch;
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
void init(const testCase_t& tcase) {
	getRead(tcase.fa1, vread[0]);
	getRead(tcase.fa2, vread[1]);
	getEntry(tcase.minisam);
}

/**
	\brief check the entry[-]'s string equal to his `Reverse Complement`
*/
bool check_RC(const Entry_t& entry) {
	assert(entry.faId>=0 && entry.faId<2);
	assert(entry.simId>=0 && entry.simId<SZ(vread[entry.faId]));

	const string& org = vread[entry.faId][entry.simId];
	string tmp = getReverseComplement(org);

	return org == tmp;
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

	printf("observe-strand [+/-]: %s", flag ? "YES":"NO");
}

void observe_positionLen() {
	int sz = SZ(vent);
	vi vc;

	for (int i=0; i<sz; ++i) {
		const Entry_t &entry = vent[i];
		vc.pb(entry.to - entry.from);
	}

	sort(all(vc));
	int n = unqiue(all(vc)) - vc.begin();
	if (n == 1) {
		printf("observe-positionLen : all equal, %d\n", vc[0]);
	} else {
		printf("observe-positionLen : [%d, %d]\n", vc[0], vc[n-1]);
	}
}

void observe_pairDis() {

}

void observe_refeUndef() {

}

void observe_alignScore() {

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
	if (testDifficulty == 0)
		init(smallCase);
	else if (testDifficulty == 1)
		init(mediumCase);
	else
		init(largeCase);

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
		_observation(i - 1);
	}
}

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	
	freopen("data.in", "r", stdin);

	int testCase = (argc>1) ? stoi(argv[1]) : 1;
	
	observation(testCase);
	
	return 0;
}
