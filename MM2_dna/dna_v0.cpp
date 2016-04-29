#include <bits/stdc++.h>
using namespace std;

/**
	`Comment this line when submit`
*/
#define LOCAL_DEBUG
#define DEBUG

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


#define getComplement(ch) Complements[(ch)]
#define getCharId(ch)	charId[(ch)]
#define NEG_INF -1e16

typedef struct trie_t* trie_ptr;
struct trie_t {
	trie_ptr fa;
	trie_ptr nxt[5];

	trie_t(trie_ptr fa = NULL):fa(fa) {
		rep(i, 0, 5) nxt[i] = NULL;
	}
};

struct node_t {
	trie_ptr leaf;
	int chrId;
	int pos;

	node_t() {}
	node_t(trie_ptr leaf, int chrId, int pos):
		leaf(leaf), chrId(chrId), pos(pos) {}
};

struct sliceNode_t {
	trie_ptr leaf;
	unsigned int atcg;
	int pos;

	sliceNode_t() {}
	sliceNode_t(trie_ptr leaf, unsigned int atcg, int pos):
		leaf(leaf), atcg(atcg), pos(pos) {}

	friend bool operator< (const sliceNode_t& a, const sliceNode_t& b) {
		return ((a.atcg & 255) + ((a.atcg>>8)&255)) < ((b.atcg & 255) + ((b.atcg>>8)&255));
	}
};

struct info_t {
	int id;			/* ChromatidSequenceId */
	int st;			/* Start position */
	int ed; 		/* End position */
	char strand;	/* strand */
	double conf;

	string toString() const {
		return ',' + to_string(id) + ',' + to_string(st) + ',' + to_string(ed) + ',' + strand + ',' + to_string(conf);
	}
};

struct endNode_t {
	int c[24];

	endNode_t() {
		memset(c, 0, sizeof(c));
	}
};

const int max_apt = 100;
const int max_slice_length = 200;
int slice_len;						/* max_slice_length */
char slice_container[2][max_slice_length];
typedef long long LL;
char Complements[128];
int charId[128];
vector<sliceNode_t> Slices[25];
vector<trie_ptr> leafs;
trie_ptr trie_root = NULL;

void Delete(trie_t *rt) {
	rep(i, 0, 5) if (rt->nxt[i]) Delete(rt->nxt[i]);
	delete rt;
}

void Delete_trie() {
	int sz = SZ(leafs);

	rep(i, 0, sz) {
		endNode_t *p = (endNode_t *) leafs[i]->nxt[0];
		delete p;
		leafs[i]->nxt[0] = NULL;
	}
	leafs.clr();

	if (trie_root)
		Delete(trie_root);
}

#ifdef DEBUG
static LL trie_node_n = 0;
#endif
inline trie_ptr newNode(trie_ptr fa) {
	#ifdef DEBUG
	++trie_node_n;
	#endif
	return new trie_t(fa);
}

trie_ptr Insert(char *s, const int len, const int chrId) {
	int i = 0, id;
	trie_ptr p = trie_root;

	#ifdef DEBUG
	assert(len == slice_len);
	#endif

	while (i < len) {
		id = getCharId(s[i]);
		if (!p->nxt[id]) break;
		p = p->nxt[id];
		++i;
	}

	#ifdef DEBUG
	// static int cnt = 0;
	// cnt += i<len;
	// printf("cnt = %d\n", cnt);
	#endif

	bool newPath = i < len;
	while (i < len) {
		id = getCharId(s[i++]);
		p->nxt[id] = newNode(p);
		p = p->nxt[id];
	}

	// make the leaf->nxt[0] point to endNode to calculate the confidence
	if (newPath) leafs.pb(p);

	if (p->nxt[0] == NULL) {
		p->nxt[0] = (trie_ptr)new endNode_t();
	}
	++((endNode_t *)(p->nxt[0]))->c[chrId];

	return p;
}

string restoreFromLeaf(trie_ptr leaf) {
	char *s = slice_container[0];
	int l = 0;
	static string acgtn = "ATCGN";
	trie_ptr p, q = leaf;

	while ((p=q->fa) != NULL) {
		#ifdef DEBUG
		bool flag = false;
		#endif
		rep(i, 0, 5) {
			if (p->nxt[i] == q) {
				s[l++] = acgtn[i];
				#ifdef DEBUG
				flag = true;
				#endif
				break;
			}
		}
		#ifdef DEBUG
		assert(flag);
		#endif
		q = p;
	}

	s[l] = '\0';
	#ifdef DEBUG
	assert(l == slice_len);
	#endif
	reverse(s, s+l);

	return string(s);
}

inline bool isAGCT(char ch) {
	return ch=='A' || ch=='C' || ch=='G' || ch=='T';
}

inline int calcScore(char a, char b) {
	if (a == b)	return 1;
	return -1;
}

int dp[155][155];
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
	}

	return dp[p][2];
}


class DNASequencing {
public:

	// constant parameter
	int at_cg_maxdif;
	int mn_acgt_tot;
	int mx_acgt_dif;
	int mx_cpg_dif;
	int C[26];

	vi chrIds;

	void init_param(const int testDifficulty) {
		at_cg_maxdif = 20;
		slice_len = 150;
		mn_acgt_tot = slice_len/2;
		mx_acgt_dif = slice_len/5;
		mx_cpg_dif = 4;
	}

	inline int calcScore(char c1, char c2) {
		return c1==c2 ? 1:0;
	}

	string getReverseComplement(const string& line) {
		int len = line.length();
		string ret;

		per(i, 0, len)	ret.pb(getComplement(line[i]));
		return ret;
	}

	void init_trie() {
		Delete_trie();
		trie_root = newNode(NULL);
	}

	int initTest(int testDifficulty) {
		// init the parameter
		init_param(testDifficulty);

		// init the complement array
		rep(i, 0, 128) Complements[i] = 'N';
		Complements['A'] = 'T';
		Complements['T'] = 'A';
		Complements['C'] = 'G';
		Complements['G'] = 'C';

		// init the id
		rep(i, 0, 128) charId[i] = 4;
		charId['A'] = 0;
		charId['T'] = 1;
		charId['C'] = 2;
		charId['G'] = 3;


		// clear the chrIds
		chrIds.clr();

		// clear the begin position of sequence part
		rep(i, 1, 25)
			Slices[i].clr();
		// rep(i, 1, 25) {
		// 	rep(j, 0, max_apt) {
		// 		Sequence[i][j].clr();
		// 	}
		// }

		// init the trie
		init_trie();

		return 0;
	}

	int preProcessing() {
		for(int chrId : chrIds)
			sort(all(Slices[chrId]));
		return 0;
	}

	inline bool check_validSlice(const int a, const int t, const int c, const int g) {
		// printf("a = %d, t = %d, c = %d, g = %d\n", a, t, c, g);
		// return true;
		if (a+c+g+t < mn_acgt_tot)	return false;
		int mn = min(min(a, c), min(g, t));
		int mx = max(max(a, c), max(g, t));
		return mx-mn < mx_acgt_dif;
	}

	void splitReferenceGenome(const int chrId, const vstr& chrSeq) {
		int sz = SZ(chrSeq);
		int i = 0, idx = 1;
		int len = chrSeq[i].length();
		int bid = 0, bpos = 0, eid = sz - 1, epos = chrSeq[sz-1].length()-1;
		int apt = 0, cpg = 0;

		#ifdef DEBUG
		assert(sz > 3);
		#endif

		while (i < sz) {
			const string& line = chrSeq[i];
			const int len = line.length();
			int j = 0;

			while (j<len && line[j]=='N') {
				++j;
				++idx;
			}
			if (j < len) {
				bid = i;
				bpos = j;
				break;
			}
			++i;
		}

		i = sz - 1;
		while (i > bid) {
			const string& line = chrSeq[i];
			const int len = line.length();
			int j = len - 1;

			while (j>=0 && line[j]=='N') --j;
			if (j >= 0) {
				eid = i;
				epos = j;
				break;
			}
			--i;
		}

		// cut the chromatidSequence[bid][bpos:] ~ chromatidSequence[eid][:epos], both ending included.
		{
			int p = 0, q = 1;
			int i = bid, j = bpos, k;


			while (i <= eid) {
				int len = i==eid ? epos : chrSeq[i].length();

				C['A'-'A'] = C['C'-'A'] = C['G'-'A'] = C['T'-'A'] = 0;
				for (k=0; k<slice_len; ++k) {
					if (j == len) {
						if (++i > eid)	break;
						len = (i==eid) ? epos : chrSeq[i].length();
						j = 0;
					}
					++C[chrSeq[i][j] - 'A'];
					slice_container[q][k] = chrSeq[i][j++];
				}

				if (k < slice_len/3) {
					break;
				} else {
					// not eough, fill them with 'N'
					while (k < slice_len) slice_container[q][k++] = 'N';
				}

				const int& a = C['A'-'A'];
				const int& t = C['T'-'A'];
				const int& c = C['C'-'A'];
				const int& g = C['G'-'A'];

				#ifdef DEBUG
				// static int cnt = 0;
				// printf("cnt = %d\n", ++cnt);
				// slice_container[q][slice_len] = '\0';
				// fprintf(stdout, "%s\n", slice_container[q]);
				#endif

				if (check_validSlice(a, t, c, g)) {
					trie_ptr leaf = Insert(slice_container[q], slice_len, chrId);
					unsigned int atcg = (a<<24) || (t<<16) || (c<<8) || g;
					Slices[chrId].pb(sliceNode_t(leaf, atcg, idx));

					// #ifdef DEBUG
					// static int cnt = 0;
					// printf("cnt = %d\n", ++cnt);
					// #endif
				}

				p ^= 1;
				q ^= 1;
				idx += slice_len;
			}
		}
	}

	int passReferenceGenome(int chromatidSequenceId, const vector<string>& chromatidSequence) {
		chrIds.pb(chromatidSequenceId);
		splitReferenceGenome(chromatidSequenceId, chromatidSequence);

		#ifdef DEBUG
		printf("trie_node_n = %lld\n", trie_node_n);
		printf("leafs = %d\n", SZ(leafs));
		#endif

		return 0;
	}

	/**
		\brief Generate a failure but format right answer
	*/
	inline string getFailureResult(const int simId, const int faId) {
		string qname = "sim" + to_string(simId) + '/' + to_string(faId);
		return qname + ",20,1,150,+,0.9";
	}

	inline string getFailureResult(const string& qname) {
		return qname + ",20,1,150,+,0.9";
	}

	inline void count_atcg(const string& read, int& a, int& t, int& c, int& g) {
		int len = read.length();

		C['A'-'A'] = C['T'-'A'] = C['C'-'A'] = C['G'-'A'] = 0;
		rep(i, 0, len) ++C[read[i]-'A'];

		a = C['A'-'A'];
		t = C['T'-'A'];
		c = C['C'-'A'];
		g = C['G'-'A'];
	}


	inline void count_atcg(const string& read, int& apt, int& cpg) {
		int len = read.length();

		C['A'-'A'] = C['T'-'A'] = C['C'-'A'] = C['G'-'A'] = 0;
		rep(i, 0, len) ++C[read[i]-'A'];

		apt = C['A'-'A'] + C['T'-'A'];
		cpg = C['C'-'A'] + C['G'-'A'];
	}

	int sliceBinarySearch(const int chrId, const int cpg) {
		int l = 0, r = SZ(Slices[chrId]) - 1, mid;
		int ret = r;
		int tmp;

		while (l <= r) {
			mid = (l + r) >> 1;
			const sliceNode_t &nd = Slices[chrId][mid];
			tmp = (nd.atcg & 255) + ((nd.atcg>>8)&255);
			if (cpg <= tmp) {
				ret = mid;
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}

		return ret;
	}

	inline int dis_slice_cpg(const sliceNode_t& nd, int cpg) {
		return abs((nd.atcg & 255) + ((nd.atcg>>8)&255) - cpg);
	}

	double calcBestAlignScore(const string& read, const int cpg, const int apt, info_t& info) {
		double ret = NEG_INF;

		for (int chrId : chrIds) {
			int lid = 0, rid = SZ(Slices[chrId]) - 1;
			int mid = sliceBinarySearch(chrId, cpg);
			for (int i=mid; i<=rid; ++i) {
				if (dis_slice_cpg(Slices[chrId][i], cpg) <= mx_cpg_dif) {
					string slice = restoreFromLeaf(Slices[chrId][i].leaf);
					//double tmp = myfunc(slice, read);
					double tmp = NEG_INF;
					if (tmp > ret) {
						ret = tmp;
						info.id = chrId;
						info.st = Slices[chrId][i].pos;
					}
				} else {
					break;
				}
			}
			for (int i=mid-1; i>=lid; --i) {
				if (dis_slice_cpg(Slices[chrId][i], cpg) <= mx_cpg_dif) {
					string slice = restoreFromLeaf(Slices[chrId][i].leaf);
					// double tmp = myfunc(slice, read);
					double tmp = NEG_INF;
					if (tmp > ret) {
						ret = tmp;
						info.id = chrId;
						info.st = Slices[chrId][i].pos;
					}
				} else {
					break;
				}
			}
		}
	}

	bool alignRead(const string& read, info_t& info) {
		int apt, cpg;
		info_t info_tmp;

		/**	
			\step 1: count the number of atcg
		*/
		count_atcg(read, apt, cpg);

		/**
			\step 2: find all possible result
		*/
		double score = calcBestAlignScore(read, cpg, apt, info_tmp);
		if (score > NEG_INF) {
			info.id = info_tmp.id;
			info.st = info_tmp.st;
			info.strand = '+';
			info.conf = info_tmp.conf;
		}
		double rscore = calcBestAlignScore(getReverseComplement(read), apt, cpg, info_tmp);
		if (rscore > score) {
			info.id = info_tmp.id;
			info.st = info_tmp.st;
			info.strand = '-';
			info.conf = info_tmp.conf;
		}
		info.ed = info.st + read.length() - 1;

		/**
			\step : return align result
		*/
		return score>NEG_INF || rscore>NEG_INF;
	}

	vector<string> getAlignment(int N, double normA, double normS, const vector<string>& readName, const vector<string>& readSequence) {
		vstr ret;
		info_t info;
		bool flag;
		string line;
		#ifdef DEBUG
		LL fail = 0;
		#endif

		for(int i=0; i<N; ++i) {
			const string& qname = readName[i];
			flag = alignRead(readSequence[i], info);
			if (flag) {
				line = qname + info.toString();
			} else {
				line = getFailureResult(qname);
				#ifdef DEBUG
				++fail;
				#endif
			}
			ret.pb(line);
			#ifdef DEBUG
			printf("%d-th read handled.\n", i);
			#endif
		}

		#ifdef DEBUG
		printf("fail = %lld\n", fail);
		#endif

		return ret;
	}
};

//%-------------------------------------Cut from here-------------------------------------------

typedef struct {
	struct timespec real;
	struct timespec proc;
} program_t;

/**
	Constants from the problem statement
*/
const int MAX_DIF_DIST = 300;
const double NORM_A_SMALL = -3.392;
const double NORM_A_MEDIUM = -3.962;
const double NORM_A_LARGE = -2.710;
const double MAX_AUC = 0.999999;
FILE* logout;

#define LOGFILENAME "dna.log"
#define result_map unordered_map<string, Result_t>

/**
	\brief Reuslt of the align
*/
typedef struct Result_t {
	int id;			/* ChromatidSequenceId */
	int st;			/* Start position */
	int ed; 		/* End position */
	char strand;	/* strand */
} Result_t;


/**
	\brief Match of the align
*/
typedef struct Match_t {
	double conf;	/* condfidence */
	int r;			/* 0 or 1 */

	// bool operator< (const Match_t& oth) const {
	// 	return conf > oth.conf;
	// }

	friend bool operator< (const Match_t& a, const Match_t& b) {
		return a.conf > b.conf;
	}
} Match_t;


/**
	\brief Parse the string of result
	\param 	line: the line to parse
			res: the infomation to check matched
			match: the infomation to calculate the match
*/
void parse(const string& line, Result_t& res, Match_t& match) {
	int len = line.length();
	int i = 0, j = 0, cnt = 0;

	// #ifdef DEBUG
	// printf("line = %s\n", line.c_str());
	// #endif
	while (1) {
		if (i==len || line[i]==',') {
			string str = line.substr(j, i-j);
			if (cnt == 1) 		res.id = stoi(str);
			else if (cnt == 2)	res.st = stoi(str);
			else if (cnt == 3)	res.ed = stoi(str);
			else if (cnt == 4)	res.strand = str[0];
			else if (cnt == 5)	match.conf = stod(str);
			++cnt;
			j = i + 1;
		}

		if (i++ >= len)
			break;
	}

	#ifdef DEBUG
	assert(cnt == 6);
	#endif
}

void parse(const string& line, Result_t& res, string& readName) {
	int len = line.length();
	int i = 0, j = 0, cnt = 0;

	while (1) {
		if (i==len || line[i]==',') {
			string str = line.substr(j, i-j);
			if (cnt == 0)		readName = str;
			else if (cnt == 1) 	res.id = stoi(str);
			else if (cnt == 2)	res.st = stoi(str);
			else if (cnt == 3)	res.ed = stoi(str);
			else if (cnt == 4)	res.strand = str[0];
			++cnt;
			j = i + 1;
		}

		if (i++ >= len)
			break;
	}

	#ifdef DEBUG
	// if (cnt != 6) printf("cnt = %d, line = %s\n", cnt, line.c_str());
	assert(cnt == 6);
	#endif
}


void parse(const string& line, Result_t& res, Match_t& match, string& readName) {
	int len = line.length();
	int i = 0, j = 0, cnt = 0;

	// #ifdef DEBUG
	// printf("line = %s\n", line.c_str());
	// #endif
	while (1) {
		if (i==len || line[i]==',') {
			string str = line.substr(j, i-j);
			if (cnt == 0)		readName = str;
			else if (cnt == 1) 	res.id = stoi(str);
			else if (cnt == 2)	res.st = stoi(str);
			else if (cnt == 3)	res.ed = stoi(str);
			else if (cnt == 4)	res.strand = str[0];
			else if (cnt == 5)	match.conf = stod(str);
			++cnt;
			j = i + 1;
		}

		if (i++ >= len)
			break;
	}

	#ifdef DEBUG
	assert(cnt == 6);
	#endif
}

/**
	\brief parse the content of `Ground truth`
	\param	filename: name of the file, suffix with ".minisam"
	\return a unordered_map[readName] = result
*/
result_map parse_ground(const string& filename) {
	result_map ret;
	ifstream fin(filename);
	string line, readName;
	Result_t res;

	if (!fin.is_open()) {
		fprintf(stderr, "%s not exists.\n", filename.c_str());
		abort();
	}

	while (fin >> line) {
		parse(line, res, readName);
		#ifdef DEBUG
		assert(ret.count(readName) == 0);
		#endif
		ret[readName] = res;
	}

	return ret;
}


/**
	\brief check the format of each line from output
	\param	line: one line of output
*/
bool check_format(const string& line, const vi& chrId) {
	Result_t res;
	Match_t match;

	parse(line, res, match);
	/* check position \ge 1 */
	if (res.st<1 || res.ed<1 || res.ed<res.st)	return false;
	/* check strand */
	if (res.strand!='+' && res.strand!='-')	return false;
	/* check confidence */
	if (match.conf<0 || match.conf>1)	return false;
	/* check ChromatidSequenceId */
	{
		bool flag = false;
		for (int id : chrId) {
			if(id == res.id) {
				flag = true;
				break;
			}
		}
		if (!flag)	return false;
	}

	return true;
}

/**
	\brief check the output of the algorithm
	\param	ans: the output string of the algorithm
			readNames: the name of the read as input
*/
bool check_ans(const vstr& ans, int N, const vi& chrId, const vstr& readNames) {
	int sz = SZ(ans);
	unordered_set<string> st;
	string readName;

	if (sz != N)	{
		printf("|ans| != N\n");
		return false;
	}

	rep(i, 0, sz) {
		int idx = ans[i].find(',');
		readName = ans[i].substr(0, idx);
		if (!check_format(ans[i], chrId)) {
			printf("ans has wrong format: [%s]\n", ans[i].c_str());
			return false;
		}
		if (st.count(readName))	{
			printf("ans contains reapted read\n");
			return false;
		}
		st.insert(readName);
	}

	rep(i, 0, sz) {
		if (!st.count(readNames[i])) {
			printf("ans not contain [%s]\n", readNames[i].c_str());
			return false;
		}
	}

	return true;
}


/**
	\brief calculate the match
	\param	ans: the vector<string> of output from core algorithm
			filename: the name of the file contains `Ground truth`
	\return vector<Match_t>: confidence with R of output from core algorithm
*/
vector<Match_t> calcMatch(const vstr& ans, const string& filename) {
	vector<Match_t> ret;
	Result_t res;
	Match_t match;
	string readName;
	int sz = SZ(ans);
	result_map res_map = parse_ground(filename);
	result_map::iterator iter;
	int correct = 0;

	rep(i, 0, sz) {
		parse(ans[i], res, match, readName);
		iter = res_map.find(readName);
		const Result_t& _res = iter->sec;
		int& r = match.r;
		r = (	(res.id == _res.id) &&
				(res.strand == _res.strand) &&
				(abs(res.st-_res.st)<=MAX_DIF_DIST)
			) ? 1 : 0;
		// r = 1;
		correct += r;
		ret.pb(match);
	}

	printf("Number of correct answers: %d/%d = %.4lf\n", correct, sz, correct*1.0/sz);
	fprintf(logout, "Number of correct answers: %d/%d = %.4lf\n", correct, sz, correct*1.0/sz);

	return ret;
}

/**
	\breif calculate the `Accuracy` of the algorithm
*/
double calcAccuarcy(const double norm_a, const int n, vector<Match_t>& vmatch) {
	sort(all(vmatch));

	// merge results of equal confidence
	vi cumul_si;
	vi pos;

	pos.pb(0);
	cumul_si.pb(vmatch[0].r);
	rep(i, 1, n) {
		if (vmatch[i].conf == vmatch[i-1].conf) {
			cumul_si.back() += vmatch[i].r;
			pos.back() = i;
		} else {
			cumul_si.pb(cumul_si.back() + vmatch[i].r);
			pos.pb(i);
		}
	}

	// compute the AuC
	double auc = 0.0;
	double invn = 1.0 / n;
	double invnp1 = 1.0 / (n + 1.0);
	double lgnp1 = 1.0 / log(n + 1.0);
	int m = SZ(cumul_si);
	rep(i, 0, m) {
		// double fi = (2 + pos[i] - cumul_si[i]);
		// double fip1 = (i==m-1) ? (n+1) : (2 + pos[i+1] - cumul_si[i+1]);
		double fi = (2+pos[i] - cumul_si[i]) * invnp1;
		double fip1 = (i==m-1) ? 1.0 : (2+pos[i+1] - cumul_si[i+1]) * invnp1;
		double lgfi = log(fi) * lgnp1;
		double lgfip1 = log(fip1) * lgnp1;
		auc += cumul_si[i] * (lgfip1 - lgfi) * invn;
	}

	printf("auc = %.4lf\n", auc);
	fprintf(logout, "auc = %.4lf\n", auc);

	return log(1.0 - min(auc, MAX_AUC)) / norm_a;
}

/**
	\brief calculate the `Speed` of the algorithm
*/
double calcSpeed(const double norm_s, const double Time, const double TimeCutOff) {
	return (1.0 - Time/TimeCutOff) / norm_s;
}

/**
	\brief calculate the `Score` of the algorithm
*/
double calcScore(const double testNorm, const double accuracy, const double speed) {
	return max(0.0, testNorm * accuracy * speed);
}

/**
	\brief read the chromat
	\param	filename: name of the chromat file
	\return	vector<string>
*/
vstr getChromat(const string& filename) {
	vstr ret;
	string line;
	ifstream fin(filename);

	if (!fin.is_open()) {
		fprintf(stderr, "%s not exists.\n", filename.c_str());
		abort();
	}

	// skip the header
	getline(fin, line);
	while (getline(fin, line)) {
		if (line.back() == '\r')	line.erase(SZ(line)-1);
		ret.pb(line);
	}

	return ret;
}

static void save_time(program_t& prog) {
	clock_gettime(CLOCK_REALTIME, &prog.real);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &prog.proc);
}

static double calc_time(const program_t& st, const program_t& ed) {
	double ret;

	#ifdef USING_PROC_TIME
	double proc_st = st.proc.tv_sec + (double)st.proc.tv_nsec / 1e9;
	double proc_ed = ed.proc.tv_sec + (double)ed.proc.tv_nsec / 1e9;
	ret = proc_ed - proc_st;
	#else
	double real_st = st.real.tv_sec + (double)st.real.tv_nsec / 1e9;
	double real_ed = ed.real.tv_sec + (double)ed.real.tv_nsec / 1e9;
	ret = real_ed - real_st;
	#endif /* USING_PROC_TIME */

	return ret;
}

double norm_a;
double norm_s;
double prep_time, _prep_time;
double cut_time, _cut_time;
string fa1_path;
string fa2_path;
string minisam_path;
vstr perform_test(int seed, const vi& chrId, int& n, bool& flag) {
	program_t st_prog;
	program_t ed_prog;
	DNASequencing dna;
	vstr ret, readNames, readSeqs;

	/**
		Preprocess
	*/
	save_time(st_prog);

	/**
		\step 1: initTest
	*/
	#ifdef DEBUG
	puts("initTest");
	#endif
	dna.initTest(seed);

	/**
		\step 2: passReferenceGenome
	*/
	#ifdef DEBUG
	puts("passReferenceGenome");
	#endif
	for (int id : chrId) {
		string filename = "./example/chromatid" + to_string(id) + ".fa";
		vstr chromatidSeq = getChromat(filename);
		dna.passReferenceGenome(id, chromatidSeq);
	}

	/**
		\step 3: preProcessing
	*/
	#ifdef DEBUG
	puts("preProcessing");
	#endif
	dna.preProcessing();

	save_time(ed_prog);
	_prep_time = calc_time(st_prog, ed_prog);

	/**
		\step 4: getRead
	*/
	#ifdef DEBUG
	puts("getRead");
	#endif
	{
		ifstream fin1(fa1_path);
		ifstream fin2(fa2_path);

		if (!fin1.is_open()) {
			fprintf(stderr, "%s not exists.\n", fa1_path.c_str());
			abort();
		}
		if (!fin2.is_open()) {
			fprintf(stderr, "%s not exists.\n", fa2_path.c_str());
			abort();
		}
		string line1, line2;

		while (getline(fin1, line1) && getline(fin2, line2)) {
			if (line1.back() == '\r') line1.erase(SZ(line1)-1);
			if (line2.back() == '\r') line2.erase(SZ(line2)-1);
			readNames.pb(line1.substr(1));
			readNames.pb(line2.substr(1));
			getline(fin1, line1);
			getline(fin2, line2);
			if (line1.back() == '\r') line1.erase(SZ(line1)-1);
			if (line2.back() == '\r') line2.erase(SZ(line2)-1);
			readSeqs.pb(line1);
			readSeqs.pb(line2);
		}
	}
	n = SZ(readNames);

	/**
		CutOffTime
	*/
	save_time(st_prog);
	/**
		\step 5: align
	*/
	#ifdef DEBUG
	puts("align");
	#endif
	ret = dna.getAlignment(n, norm_a, norm_s, readNames, readSeqs);
	save_time(ed_prog);
	_cut_time = calc_time(st_prog, ed_prog);

	printf("prep_time = %.4lf, prep_bound = %.4lf\n", _prep_time, prep_time*3);
	printf("cut_time = %.4lf, cut_bound = %.4lf\n", _cut_time, cut_time*2);
	fprintf(logout, "prep_time = %.4lf, prep_bound = %.4lf\n", _prep_time, prep_time*3);
	fprintf(logout, "cut_time = %.4lf, cut_bound = %.4lf\n", _cut_time, cut_time*2);

	/**
		\step 6: check result
	*/
	#ifdef DEBUG
	puts("check result");
	#endif
	flag = check_ans(ret, n, chrId, readNames);

	return ret;
}

static void _test(int seed) {
	vi chrId;
	double testNorm;

	norm_s = 0.5;
	if (seed == 0) {
		minisam_path = "./example/small5.minisam";
		fa1_path = "./example/small5.fa1";
		fa2_path = "./example/small5.fa2";

		norm_a = NORM_A_SMALL;
		testNorm = 1000 / 1.05;
		prep_time = 201;
		cut_time = 16.1;

		chrId.pb(20);
	} else if (seed == 1) {
		minisam_path = "./example/medium5.minisam";
		fa1_path = "./example/medium5.fa1";	
		fa2_path = "./example/medium5.fa2";

		norm_a = NORM_A_MEDIUM;
		testNorm = 1000000 / 1.05;
		prep_time = 1669;
		cut_time = 1102;

		chrId.pb(1);
		chrId.pb(11);
		chrId.pb(20);
	} else {
		minisam_path = "../example/large5.minisam";
		fa1_path = "./example/large5.fa1";
		fa2_path = "./example/large5.fa2";

		norm_a = NORM_A_LARGE;
		testNorm = 1000000 / 1.05;
		prep_time = 13239;
		cut_time = 13730;

		rep(i, 1, 25)	chrId.pb(i);
	}

	int n;
	bool flag;
	vstr ans = perform_test(seed, chrId, n, flag);
	double score;

	if (!flag) {
		score = 0;
	} else {
		vector<Match_t> vmatch = calcMatch(ans, minisam_path);
		double accuracy = calcAccuarcy(norm_a, n, vmatch);
		double speed = calcSpeed(norm_s, _cut_time, cut_time*2);
		score = calcScore(testNorm, accuracy, speed);

		printf("accuracy = %.4lf\n", accuracy);
		printf("speed = %.4lf\n", speed);
		fprintf(logout, "accuracy = %.4lf\n", accuracy);
		fprintf(logout, "speed = %.4lf\n", speed);
	}

	printf("score = %.4lf\n", score);
	fprintf(logout, "score = %.4lf\n", score);
}

static void test(int testcase) {
	bool visit[10];

	memset(visit, false, sizeof(visit));
	while (testcase) {
		visit[testcase%10] = true;
		testcase /= 10;
	}

	for (int i=1; i<=3; ++i) {
		if (!visit[i])	continue;
		if (i == 1) {
			printf("\ntest Small:\n");
			fprintf(logout, "\ntest Small:\n");
		} else if (i == 2) {
			printf("\ntest Medium:\n");
			fprintf(logout, "\ntest Medium:\n");
		} else {
			printf("\ntest Large:\n");
			fprintf(logout, "\ntest Large:\n");
		}
		_test(i-1);
	}
}

static void init_log() {
	logout = fopen(LOGFILENAME, "w");
	if (!logout) {
		fprintf(stderr, "%s can not open.\n", LOGFILENAME);
		abort();
	}
}

static void close_log() {
	fclose(logout);
}

int main(int argc, char **argv) {
	int testcase = argc > 1 ? stoi(argv[1]) : 1;

	init_log();
	test(testcase);
	close_log();

	return 0;
}
