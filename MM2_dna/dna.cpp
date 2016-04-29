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

typedef struct trie_t* trie_ptr;
struct trie_t {
	trie_ptr fa;
	trie_ptr nxt[5];

	trie_t(trie_ptr fa = NULL):fa(fa) {
		rep(i, 0, 5) nxt[i] = NULL;
	}
} trie_t;

struct node_t {
	trie_ptr leaf;
	int chrId;
	int pos;

	node_t() {}
	node_t(trie_t leaf, int chrId, int pos):
		leaf(ed), chrId(chrId), pos(pos);
};

struct info_t {
	int id;			/* ChromatidSequenceId */
	int st;			/* Start position */
	int ed; 		/* End position */
	char strand;	/* strand */
	double conf;

	string to_string() const {
		return ',' + to_string(id) + ',' + to_string(st), + ',' + to_string(ed) + ',' + strand + ',' + to_string(conf);
	}
};

const int maxq = 180;
struct Queue_t {
	int l, r;
	char qs[maxq];

	inline void init() {
		l = r = 0;
	}

	inline void push(char ch) {
		qs[r++] = ch;
		if (r == maxq) r = 0;
	}

	inline void pop() {
		if (++l == maxq) l = 0;
	}

	inline void front() {
		return qs[l];
	}
};

const int max_apt = 100;
Queue_t qs;
typedef long long LL;
char Complements[128];
int charId[128];
vector<node_t> Sequence[25][max_apt];
trie_t *root = NULL;

void Delete(trie_t *rt) {
	rep(i, 0, 5) if (rt->nxt[i]) Delete(rt->nxt[i]);
	delete rt;
}

inline trie_ptr newNode(trie_ptr fa) {
	return new trie_t(fa);
}

trie_ptr Insert() {
	int i = qs.l, id;
	trie_ptr p = root, q;

	while (i != r) {
		id = getCharId(qs.Q[i]);
		if (!p->nxt[id]) break;
		++i;
		if (i == maxq) i = 0;
	}

	while (i != r) {
		id = getCharId(qs.Q[i]);
		p->nxt[id] = newNode(p);
		++i;
		if (i == maxq) i = 0;
		p = p->nxt[id];
	}

	return p;
}

class DNASequencing {
public:
	// constant parameter
	int at_cg_maxdif;
	int split_seq_len;	/* pay attention to update qsize */
	int C[26];

	vi chrIds;

	void init_param(const int testDifficulty) {
		at_cg_maxdif = 20;
		split_seq_len = 150;
	}

	inline int calcScore(char c1, char c2) {
		return c1==c2 ? 1:0;
	}

	string getReverseComplement(const string& line) {
		int len = line.lenght();
		string ret;

		per(i, 0, len)	ret.pb(getComplement(line[i]));
		return ret;
	}

	void init_trie() {
		if (root)
			Delete(root);
		root = newNode();
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
		rep(i, 1, 25) {
			rep(j, 0, max_apt) {
				Sequence[i][j].clr();
			}
		}	

		// init the trie
		init_trie();

		return 0;
	}

	int preProcessing() {
		return 0;
	}

	void splitReferenceGenome(const int chrId, const vstr& chromatidSequence) {
		int nline = SZ(chromatidSequence);
		int i = 0, j = 0, idx = 1;
		int len = chromatidSequence[i].length();
		int apt = 0, cpg = 0;

		#ifdef DEBUG
		assert(nline > 3);
		#endif

		qs.init();
		// fill first split_seq_len
		while (idx < split_seq_len) {
			const char& ch = chromatidSequence[i][j];
			qs.push(ch);
			if (ch=='A' || ch=='T')
				++apt;
			else if (ch=='C' || ch=='G')
				++cpg;
			++j;
			if (j == len) {
				++i;
				len = chromatidSequence[i].length();
				j = 0;
			}
			++idx;
		}

		// dynamic calculate the gap between `A+T` and `C+G`
		while (i < nline) {
			const char& ch = chromatidSequence[i][j];
			qs.push(ch);
			if (ch=='A' || ch=='T')
				++apt;
			else if (ch=='C' || ch=='G')
				++cpg;
			if (abs(apt-cpg) <= at_cg_maxdif) {
				#ifdef DEBUG
				assert(apt < max_apt);
				#endif
				trie_ptr leaf = Insert();
				Sequence_beg[apt].pb(node_t(leaf, chrId, idx));
			}
			++j;
			if (j == len) {
				++i;
				len = chromatidSequence[i].length();
				j = 0;
			}
			++idx;

			// pop the character queue
			const char _ch = qs.top();
			qs.pop();
			if (_ch=='A' || _ch=='T')
				--apt;
			else if (_ch=='C' || _ch=='G')
				--cpg;

			#ifdef DEBUG
			assert(apt>=0 && cpg>=0);
			#endif
		}
	}

	int passReferenceGenome(int chromatidSequenceId, const vector<string>& chromatidSequence) {
		chrIds.pb(chromatidSequenceId);
		splitReferenceGenome(chromatidSequenceId, chromatidSequence);
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

	void alignRead(const string& read, info_t& info) {
		int apt, cpg;

		/*
			\step 1: count the number of atcg
		*/
		count_atcg(read, apt, cpg);

		/*
			\step 2: find all possible result
		*/
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
