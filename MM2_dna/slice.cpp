/*  */
#include <iostream>
#include <sstream>
#include <fstream>
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

typedef unsigned int uint;
typedef long long LL;
typedef struct trie_t* trie_ptr;
struct trie_t {
	trie_ptr nxt[5];

	trie_t() {
		memset(nxt, 0, sizeof(nxt));
	}
};

const string DATA_PATH = "./example/";
const string CHR_PATH = DATA_PATH + "chromatid";
const int maxn = 205;
int slice_len = 10;
char qs[maxn];
trie_ptr root = NULL;
const string atcgn = "ATCGN";
vector<pair<uint, string> > freq;
vi chrIds;

inline int getId(char ch) {
	if (ch == 'A')	return 0;
	if (ch == 'T')	return 1;
	if (ch == 'C')	return 2;
	if (ch == 'G')	return 3;
	return 4;
}

void Init_trie() {
	root = new trie_t();
}

void Delete(trie_ptr rt, int dep) {
	if (dep == slice_len)	return ;
	rep(i, 0, 5) if (rt->nxt[i]) Delete(rt->nxt[i], dep+1);
	delete rt;
}

void Delete_trie() {
	if (root)
		Delete(root, 0);
}

void Insert() {
	const int& len = slice_len;
	int i = 0, id;
	trie_ptr p = root;

	while (i < len) {
		id = getId(qs[i]);
		if (!p->nxt[id]) break;
		p = p->nxt[id];
		++i;
	}

	while (i < len) {
		id = getId(qs[i++]);
		p->nxt[id] = new trie_t();
		p = p->nxt[id];
	}

	++p->nxt[0];
}

void dumpSlice(trie_ptr rt, int dep) {
	if (dep == slice_len) {
		uint tmp = rt->nxt[0] - (trie_ptr)NULL;
		qs[dep] = '\0';
		freq.pb(mp(tmp, string(qs)));
		return ;
	}

	rep(i, 0, 5) {
		if (rt->nxt[i]) {
			qs[dep] = atcgn[i];
			dumpSlice(rt->nxt[i], dep+1);
		}
	}
}

void readChromatid(const int chrId, vstr& lines) {
	char filename[55];

	lines.clr();
	sprintf(filename, "%s%d.fa", CHR_PATH.c_str(), chrId);
	ifstream fin(filename);

	if (!fin.is_open()) {
		cerr << filename << " not exists." << endl;
		abort();
	}

	string line;

	// skip header
	getline(fin, line);

	while (getline(fin, line)) {
		if (*line.rbegin() == '\r')	line.erase(SZ(line) - 1);
		if (line.length())
			lines.pb(line);
	}

	fin.close();
}

void Insert_chr(const int chrId) {
	vstr chrSeq;

	readChromatid(chrId, chrSeq);
	int sz = SZ(chrSeq);
	int bi = 0, bpos = 0;

	while (bi < sz) {
		const string& line = chrSeq[bi];
		const int len = line.length();
		int j = 0;

		while (j<len && line[j]=='N') ++j;

		if (j < len) {
			bpos = j;
			break;
		}
		++bi;
	}

	int ei = sz - 1, epos = SZ(chrSeq[ei]) - 1;

	while (ei > bi) {
		const string& line = chrSeq[ei];
		const int len = line.length();
		int j = len - 1;

		while (j>=0 && line[j]=='N') --j;

		if (j >= 0) {
			epos = j;
			break;
		}
		--ei;
	}

	int i = bi, j = bpos;
	#ifdef DEBUG
	LL nslice = 0;
	// printf("bi = %d, bpos = %d, ei = %d, epos = %d\n", bi, bpos, ei, epos);
	#endif

	while (i <= ei) {
		int len = i==ei ? epos+1 : chrSeq[i].length();

		rep(k, 0, slice_len) {
			if (j == len) {
				if (++i > ei) {
					while (k < slice_len) qs[k++] = 'N';
					break;
				}
				len = i==ei ? epos : chrSeq[i].length();
				j = 0;
			}
			qs[k] = chrSeq[i][j++];
		}

		Insert();
		#ifdef DEBUG
		nslice += 1;
		// if (nslice%100 == 0) {
			// printf("nslice = %lld\n", nslice);
			// fflush(stdout);
		// }
		#endif
	}

	#ifdef DEBUG
	printf("chrId = %d, nslice = %lld\n", chrId, nslice);
	#endif
}

void _dumpFreq_Slice() {
	Delete_trie();
	Init_trie();
	int sz_chrIds = SZ(chrIds);

	rep(i, 0, sz_chrIds) {
		const int chrId = chrIds[i];
		Insert_chr(chrId);
	}

	// return ;
	freq.clr();
	dumpSlice(root, 0);
	sort(all(freq), greater<pair<LL,string> >());

	int sz_cnt = SZ(freq);
	printf("\nslice frequency:\n");
	rep(i, 0, sz_cnt) {
		printf("%u: %s\n", freq[i].fir, freq[i].sec.c_str());
	}
}

void dumpFreq_Slice(const int testDifficulty) {
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

	_dumpFreq_Slice();
}

void dumpAllFreq() {
	rep(i, 1, 25) {
		chrIds.clr();	
		chrIds.pb(i);
		printf("\n\nchrId = %d\n", i);
		_dumpFreq_Slice();
	}
}

bool startswith(const string& sa, const string& sb) {
	int alen = sa.length(), blen = sb.length();

	if (alen < blen)	return false;

	rep(i, 0, blen) if (sa[i] != sb[i]) return false;
	return true;
}

void mergeAllFreq(int topn = 360) {
	const string filename = "slice.out";
	ifstream fin(filename);
	Init_trie();
	string line;
	int chrId;

	if (!fin.is_open()) {
		cerr << filename << " not exits." << endl;
		abort();
	}

	while (getline(fin, line)) {
		//cout << line << endl;
		if (startswith(line, "chrId")) {
			const int len = line.length();
			chrId = 0;
			rep(i, 8, len) {
				if (!isdigit(line[i]))
					break;
				chrId = chrId * 10 + line[i]-'0';
			}
		//	printf("chrId = %d\n", chrId);
		} else if (startswith(line, "slice")) {
			rep(i, 0, topn) {
				if (!getline(fin, line))
					break;

				int len = line.length();
				if (len < slice_len)	break;
				int l = 0;
				rep(j, len-slice_len, len)
					qs[l++] = line[j];

				Insert();
			}
		}
	}

	dumpSlice(root, 0);
	sort(all(freq), greater<pair<LL,string> >());

	int sz_cnt = SZ(freq);
	printf("\ntop-%d slice frequency:\n", topn);
	rep(i, 0, sz_cnt) {
		printf("%u: %s\n", freq[i].fir, freq[i].sec.c_str());
	}
}

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	#ifdef DEBUG
		freopen("data.in", "r", stdin);
		freopen("data.out", "w", stdout);
	#endif

	// int testDifficulty;

	// cin >> slice_len >> testDifficulty;

	// assert(slice_len>=5 && slice_len<=20);
	// assert(testDifficulty==1 || testDifficulty==2 || testDifficulty==3);
	// dumpFreq_Slice(testDifficulty - 1);

	//dumpAllFreq();
	int topn = 256;

	if (argc > 1) {
		sscanf(argv[1], "%d", &topn);
	}
	cerr << topn << endl;
	mergeAllFreq(topn);

	return 0;
}
