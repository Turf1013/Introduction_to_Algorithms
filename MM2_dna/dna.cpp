#include <bits/stdc++.h>
using namespace std;

/**
	`Comment this line when submit`
*/ 
#define LOCAL_DEBUG
#define DEBUG

// #define SLICE_USE_CNT
#define SLICE_USE_FREQ

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

typedef unsigned int uint;
typedef long long LL;

typedef struct trie_t* trie_ptr;
struct trie_t {
	trie_ptr nxt[5];

	trie_t() {
		rep(i, 0, 5) nxt[i] = NULL;
	}
} trie_t;

struct sep_t {
	trie_ptr leaf;
	int idx;

	sep_t() {}
	sep_t(trie_t leaf, int pos):
		leaf(ed), pos(pos);
};

struct info_t {
	int id;			/* ChromatidSequenceId */
	int st;			/* Start position */
	int ed; 		/* End position */
	char strand;	/* strand */
	double conf;

	string to_string() const {
		return ',' + to_string(id) + ',' + to_string(st+1), + ',' + to_string(ed+1) + ',' + strand + ',' + to_string(conf);
	}
};

struct slice_t {
	int idx;
	vector<double> freq;

	void clear() {
		freq.clr();
	}
};

struct group_t {
	int idx;
	vector<double> freq;

	void clear() {
		freq.clr();
	}
}

// constant parameter
int sep_len;		/* pay attention to update qsize */

// about sep
const char* acgtn_s = "acgtn";
const int max_hash_size = 1050;
const int max_sep_len = 50;
unsigned int hash_seed, has_size;
int hash_base[max_sep_len];
bool sep_id[max_hash_size];
unsigned int sep_cnt[max_hash_size];
unsigned int sep_cnt_ubound, sep_cnt_lbound;
unsigned int topk_sep_chr;
vector<pair<uint,uint> > sep_freq;
char buffer[max_sep_len];

// about slice
int slice_len;

// about group
int group_len;

typedef long long LL;
char Complements[128];
int charId[128];
vector<slice_t> sliceChromat[25];
vector<group_t> groupChromat[25];
vector<sep_t> sepChromat;
trie_ptr root = NULL;
trie_ptr root_chr = NULL;

void Delete(trie_t *rt, int dep) {
	if (dep == sep_len)	return ;
	rep(i, 0, 5) if (rt->nxt[i]) Delete(rt->nxt[i], dep+1);
	delete rt;
}

trie_ptr Insert(char *s) {
	int i = 0; 
	trie_t p = root;

	while (i < sep_len) {
		id = getCharId(s[i]);
		if (!p->nxt[id]) break;
		p = p->nxt[id];
		++i;
	}

	while(i < sep_len) {
		id = getCharId(s[i++]);
		p->nxt[id] = new trie_t();
		p = p->nxt[id];
	}
	++p->nxt[0];

	return p;
}

trie_ptr Insert_chr(char *s) {
	int i = 0; 
	trie_t p = root_chr;

	while (i < sep_len) {
		id = getCharId(s[i]);
		if (!p->nxt[id]) break;
		p = p->nxt[id];
		++i;
	}

	while(i < sep_len) {
		id = getCharId(s[i++]);
		p->nxt[id] = new trie_t();
		p = p->nxt[id];
	}
	++p->nxt[0];

	return p;
}

inline bool isACGT(char ch) {
	return ch=='A' || ch=='G' || ch=='C' || ch=='T';
}

void init_trie() {
	if (root)
		Delete(root, 0);
	root = new trie_t();
}

void init_trie_chr() {
	if (root_chr)
		Delete(root_chr, 0);
	root_chr = new trie_t();
}

void trav_trie_chr(trie_ptr rt, int dep, unsigned int val) {
	if (dep == sep_len) {
		unsigned int h = val % hash_sizel
		sep_cnt[h] += (rt->nxt[0] - (trie_ptr)NULL);
		rt->nxt[1] += h;
		return ;
	}

	unsigned int _val = val * hash_seed;
	rep(i, 0, 5) if (rt->nxt[i]) trav_trie_chr(rt->nxt[i], dep+1, _val+acgtn_s[i]);
}

class DNASequencing {
public:
	int C[26];
	vi chrIds;

	void init_param(const int testDifficulty) {
		if (testDifficulty == 0) {
			sep_len = 10;
			slice_len = 170;	// slice_len%sep_len = 0
			group_len = 1020;	// group_len%slice_len = 0;	
			hash_seed = 31;
			hash_size = 123;
			sep_cnt_ubound = 1e8;
			sep_cnt_lbound = 0;
			topk_sep_chr = 100;
		} else if (testDifficulty == 1) {
			sep_len = 10;
			slice_len = 170;		// slice_len%sep_len = 0
			group_len = 1020;	// group_len%slice_len = 0;	
			hash_seed = 31;
			hash_size = 123;
			sep_cnt_ubound = 1e8;
			sep_cnt_lbound = 0;
			topk_sep_chr = 100;
		} else {
			sep_len = 10;
			slice_len = 170;		// slice_len%sep_len = 0
			group_len = 1020;	// group_len%slice_len = 0;	
			hash_seed = 31;
			hash_size = 123;
			sep_cnt_ubound = 1e8;
			sep_cnt_lbound = 0;
			topk_sep_chr = 100;
		}
	}

	string getReverseComplement(const string& line) {
		int len = line.length();
		string ret;

		per(i, 0, len)	ret.pb(getComplement(line[i]));
		return ret;
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
		charId['C'] = 1;
		charId['G'] = 2;
		charId['T'] = 3;

		// clear the chrIds
		chrIds.clr();

		// clear the begin position of sequence part
		rep(i, 1, 25) {
			sliceChromat[i].clr();
			groupChromat[i].clr();
		}	

		// init the trie
		init_trie();

		return 0;
	}

	int preProcessing() {
		return 0;
	}

	void separateChromat(const vstr& chromatidSequence) {
		const int unkown_bound = 2;
		const int chrId = *chrIds.rbegin();
		int nline = SZ(chromatidSequence);
		int l = 0, unknown = 0;
		int idx = 0;
		sep_t sep;

		rep(idx, 0, nline) {
			const string& line = chromatidSequence[idx];
			const int len = line.length();

			rep(i, 0, len) {
				if (!isACGT(line[i])) {
					if (++unknown == unknown_bound) {
						l = 0;
						unkown = 0;
					}
				}
				if (l == sep_len) {
					sep.leaf = Insert_chr(buffer);
					sep.idx = idx + i;
					sepChromat.pb(sep);
					Insert_glb(buffer);
					l = 0;
					unkown = 0;
				}
			}
			idx += len;
		}
	}

	int extractFeatureChromat() {
		memset(sep_cnt, 0, sizeof(sep_cnt));
		memset(sep_id, -1, sizeof(sep_id));
		trav_trie_chr(root_chr, 0);

		rep(i, 0, hash_size) {
			if (sep_cnt[i]>sep_cnt_lbound && sep_cnt[i]<sep_cnt_ubound) {
				sep_freq.pb(mp(sep_cnt[i], i));
			}
		}

		sort(all(sep_freq), greater<pair<uint,uint> >());
		int mn_sz = min(topk_slice_chr, SZ(sep_freq));

		rep(i, 0, mn_sz) {
			sep_id[sep_freq[i].sec] = i;
		}
		sep_freq.clr();

		return mn_sz;
	}

	void mergeChromat(int nfeature) {
		const int chrId = *chrIds.rbegin();
		int nsep = SZ(sepChromat);

		// merge the sep into slice
		{
			int i = 0, j;
			int bi;
			uint tot;
			slice_t slice;

			memset(sep_cnt, 0, sizeof(sep_cnt));
			rep(ii, 0, nfeature) slice.freq.pb(0.);

			while (i < nsep) {
				j = i;
				bi = sepChromat[i].idx;
				tot = 0;

				while (i<nsep && sepChromat[i].idx-bi<=slice_len) {
					int h = sepChromat[i].leaf->nxt[1] - (trie_ptr)NULL;
					if (sep_id[h] >= 0) {
						++sep[sep_id[h]];
					}
					++tot;
					++i;
				}

				slice.idx = bi;
				rep(k, 0, nfeature) {
					#ifdef SLICE_USE_FREQ
					slice[k] = sep_cnt[k] / (double) tot;
					#else
					slice[k] = sep_cnt[k];
					#endif
					sep_cnt[k] = 0;
					sliceChromat[chrId].pb(slice);
				}
			}
		}

		// release sepChromat, we don't need them
		sepChromat.clr();

		// merge the slice into group
		int nslice = SZ(sliceChromat[chrId]);
		{
			int i = 0, j;
			int bi;
			group_t grp;

			rep(ii, 0, nfeature) grp.freq.pb(0.);
			while (int < nslice) {
				j = i;
				bi = sliceChromat[chrId][i].idx;

				while (i<nslice && sliceChromat[chrId][i].idx-bi<=group_len) {
					const vector<double>& vc = sliceChromat[chrId][i].freq;
					rep(ii, 0, nfeature) grp.freq[ii] += vc[ii];
					++i;
				}

				#ifdef DEBUG
				assert(i > j);
				#endif
				j = i - j;
				grp.idx = bi;
				rep(ii, 0, nfeature) grp.freq[ii] /= j;
				groupChromat[chrId].pb(grp);
				rep(ii, 0, nfeature) grp.freq[ii] = 0;
			}
		}
	}

	int passReferenceGenome(int chromatidSequenceId, const vector<string>& chromatidSequence) {
		// push chrId into chrIds
		chrIds.pb(chromatidSequenceId);

		// split the chromat into slices, may exists bad separated
		separateChromat(chromatidSequenceId, chromatidSequence);

		// Find the feature of current chromat
		nfeature = extractFeatureChromat()

		// release the memory of chr's trie
		init_trie_chr();

		// merge the slice to present the chromat
		mergeChromat(nfeature);

		return 0;
	}

	/**
		\brief Generate a failure but format right answer
	*/
	inline string getFailureResult(const int simId, const int faId) {
		string qname = "sim" + to_string(simId) + '/' + to_string(faId);
		#ifdef DEBUG
		return qname + ",20,1,150,+,0.9";
		#else
		return qname + ",20,1,150,+,0.9";
		#endif
	}

	inline string getFailureResult(const string& qname) {
		#ifdef DEBUG
		return qname + ",20,1,150,+,0.9";
		#else
		return qname + ",20,1,150,+,0.9";
		#endif
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

	void alignRead(const string& read, info_t& info) {
		int apt, cpg;

		
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
				line = qname + info.to_string();
			} else {
				line = getFailureResult(qname);
				#ifdef DEBUG
				++fail;
				#endif
			}
			ret.pb(line);
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
		r = 1;
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
