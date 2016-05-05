#include <bits/stdc++.h>
using namespace std;

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
#define INF				0x3f3f3f3f


#define result_map unordered_map<string, Result_t>
const int MAX_DIF_DIST = 300;

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
	float conf;	/* condfidence */
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
		printf("|ans| = N\n");
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


void calcResult(const vstr& ans, const string& filename) {
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
		correct += r;
	}

	printf("Number of correct answers: %d/%d = %.4lf\n", correct, sz, correct*1.0/sz);
}

vstr readAns(const int testDifficulty) {
	string filename;

	if (testDifficulty == 0)
		filename = "result_small.log";
	else if (testDifficulty == 1)
		filename = "result_medium.log";
	else
		filename = "result_large.log";
	ifstream fin(filename.c_str());

	if (!fin.is_open()) {
		fprintf(stderr, "%s can't open.\n", filename.c_str());
		abort();
	}
	vstr ret;
	string line;

	while (getline(fin, line)) {
		if (line.length() > 0)
			ret.pb(line);
	}

	fin.close();
	return ret;
}

void _test(const int testDifficulty) {
	string filename;

	if (testDifficulty == 0) {
		filename = "./example/small5.minisam";
	} else if (testDifficulty == 1) {
		filename = "./example/medium5.minisam";
	} else {
		filename = "./example/large5.minisam";
	}

	vstr ans = readAns(testDifficulty);

	calcResult(ans, filename);
}

void test(int testcase) {
	bool visit[10];

	memset(visit, false, sizeof(visit));
	while (testcase) {
		visit[testcase%10] = true;
		testcase /= 10;
	}

	for (int i=1; i<=3; ++i) {
		if (!visit[i])	continue;

		_test(i-1);
	}
}

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	// freopen("data.out", "w", stdout);

	int testcase = argc > 1 ? stoi(argv[1]) : 1;

	test(testcase);

	return 0;
}
