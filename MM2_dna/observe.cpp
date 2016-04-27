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

#define WINDOWS
// #define LINUX

#ifdef WINDOWS
	const string DATA_PREFIX = "I:/";
#else 
	const string DATA_PREFIX = "~/Code/";
#endif /* WINDOWS */

struct TestCase_t {
	const string fa1, fa2, minisam;
	
	TestCase_t(const string fa1, const string fa2, const string minisam):
		fa1(fa1), fa2(fa2), minisam(minisam) {}
};

const string READ_PATH = DATA_PREFIX + "TCO-MM/example/";
const string REFE_PATH = READ_PATH;
TestCase_t small (
	READ_PATH + "small5.fa1", 
	READ_PATH + "small5.fa2", 
	READ_PATH + "small5.minisam"
);
TestCase_t medium (
	READ_PATH + "medium5.fa1", 
	READ_PATH + "medium5.fa2", 
	READ_PATH + "medium5.minisam"
);
TestCase_t large (
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
	
	rep(i, 0, len) ret.pb(getComplement(s[i]));
	
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
	\brief	the info need to observe
	\param	testDifficuly: 0-small, 1-medium, 2-large
*/
void _observation(int testDifficulty) {
	
}

void observation(int testCase) {
	bool visit[10];
	
	memset(visit, false, sizeof(visit));
	while (testCase) {
		visit[testCase % 10] = true;
		testCase /= 10;
	}
	
	rep(i, 1, 4) {
		_observation(i);
	}
}

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	
	int testCase = (argc>1) ? stoi(argv[1]) : 1;
	
	// observation(testCase);
	
	Entry_t entry;
	string line;
	
	cin >> line;
	parseEntry(line, entry);
	entry.print();
	
	
	return 0;
}
