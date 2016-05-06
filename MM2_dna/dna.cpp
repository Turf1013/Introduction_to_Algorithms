/**
	\author	Trasier
	\brief	TCO-MM-DNA
*/
#include <bits/stdc++.h>
using namespace std;

/**
	`Comment this line when submit`
*/
// #define LOCAL_DEBUG
// #define DEBUG
//#define TRAIN_DEBUG

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

// #define getComplement(ch) Complements[(ch)]
// #define getCharId(ch)	charId[(ch)]

typedef unsigned int uint;
typedef long long LL;

// info
struct info_t {
	int id;			/* ChromatidSequenceId */
	int st;			/* Start position */
	int ed; 		/* End position */
	char strand;	/* strand */
	float conf;

	string toString() const {
		return ',' + to_string(id) + ',' + to_string(st+1) + ',' + to_string(ed+1) + ',' + strand + ',' + to_string(conf);
	}
};

// trie
typedef struct trie_t* trie_ptr;
struct trie_t {
	trie_ptr fa;
	trie_ptr nxt[5];

	trie_t(trie_ptr fa=NULL):fa(fa) {
		rep(i, 0, 5) nxt[i] = NULL;
	}
};

trie_ptr trie_root = NULL;
uint nleaf = 0;

struct feature_t {
	int c;
	int id;

	feature_t() {}
	feature_t(int c, int id):
		c(c), id(id) {}

	bool operator< (const feature_t& oth) const {
		return id < oth.id;
	}
};

bool feat_compc(const feature_t& a, const feature_t& b) {
	return a.c > b.c;
}


bool feat_compid(const feature_t& a, const feature_t& b) {
	return a.id < b.id;
}

struct sep_t {
	trie_ptr leaf;
	uint idx;

	sep_t() {}
	sep_t(trie_ptr leaf, int idx):
		leaf(leaf), idx(idx) {}

	bool operator< (const sep_t& oth) const {
		return idx > oth.idx;
	}
};

struct slice_t {
	int idx;
	vector<feature_t> feat;

	inline void push_back(const feature_t& f) {
		feat.push_back(f);
	}

	inline void sorted() {
		sort(all(feat));
	}

	inline int size() const {
		return SZ(feat);
	}

	inline void resize(const int n) {
		feat.resize(n);
	}

	inline void clear() {
		feat.clr();
	}

	bool operator< (const slice_t& oth) const {
		return idx < oth.idx;
	}

	#ifdef DEBUG
	void print() const {
		cout << "idx = " << idx << ", SZ(feat) = " << SZ(feat) << "." << endl;
	}
	#endif
};

typedef slice_t sgroup_t;
typedef slice_t group_t;

// about score
//typedef long long score_type;
typedef int score_type;

struct read_chr_t {
	int idx;
	score_type score;

	read_chr_t() {}
	read_chr_t(int idx, score_type score):
		idx(idx), score(score) {}

	bool operator< (const read_chr_t& oth) const {
		return score > oth.score;
	}

	#ifdef DEBUG
	void print() const {
		cout << "idx = " << idx << ", score = " << score << endl;
	}
	#endif
};

struct readpair_chr_t {
	int lidx, ridx;
	score_type score;

	readpair_chr_t() {}
	readpair_chr_t(int lidx, int ridx, score_type score):
		lidx(lidx), ridx(ridx), score(score) {}

	bool operator< (const readpair_chr_t& oth) {
		return score > oth.score;
	}

	#ifdef DEBUG
	void print() const {
		cout << "[" << lidx  << ", " << ridx << "], score = " << score << endl;
	}
	#endif
};

struct read_t {
	int chrId, lidx, ridx;
	score_type score;

	read_t() {}
	read_t(int chrId, const readpair_chr_t& rp):chrId(chrId) {
		lidx = rp.lidx;
		ridx = rp.ridx;
		score = rp.score;
	}
	read_t(int chrId, int lidx, int ridx, score_type score):
		chrId(chrId), lidx(lidx), ridx(ridx), score(score) {}


	bool operator< (const read_t& oth) const {
		return score > oth.score;
	}

	#ifdef DEBUG
	void print() const {
		cout << "chrId = " << chrId << ", score = " << score << ", [" << lidx << ", " << ridx << "]." << endl;
	}
	#endif
};

// aboud layer
struct layer_t {
	uint feature_num;
	uint feature_lbound;
	uint len;
	uint topk;
	score_type score_bound;
};

// about acgt
struct acgt_t {
	unsigned short c[4];

	acgt_t() {c[0] = c[1] = c[2] = c[3] = 0;}
	acgt_t(unsigned short a, unsigned short cc, unsigned short g, unsigned short t) {
		c[0] = a;
		c[1] = cc;
		c[2] = g;
		c[3] = t;
	}

	inline void clear() {
		c[0] = c[1] = c[2] = c[3] = 0;
	}

	acgt_t operator+ (const acgt_t& oth) const {
		return acgt_t(c[0]+oth.c[0], c[1]+oth.c[1], c[2]+oth.c[2], c[3]+oth.c[3]);
	}

	#ifdef DEBUG
	void print() const {
		printf("a = %d, c = %d, g = %d, t = %d\n", c[0], c[1], c[2], c[3]);
	}
	#endif
};


// global parameter
const char* acgtn_s = "acgtn";
int sep_len = 10;
const score_type POS_INF = 0x3f3f3f3f;
const score_type NEG_INF = -POS_INF;
char Complements[128];
int charId[128];
char buffer[1600];
const int max_ibuffer = 1e8;
int ibuffer[max_ibuffer];
const char* acgt_s = "ACGTN";

// sep
layer_t layer_sep;

// slice
layer_t layer_slice;

// about sub-group
layer_t layer_sgroup;

// about group
layer_t layer_group;

// about read
layer_t layer_read;


// store feature of chromat
vector<acgt_t> acgtChromat[25];
vector<slice_t> sliceChromat[25];
vector<sgroup_t> sgroupChromat[25];
vector<group_t> groupChromat[25];
vector<sep_t> sepChromat[25];


#ifdef DEBUG
/**
	\brief	check if ibuffer's item is all < 0
*/
bool check_ibuffer() {
	rep(i, 0, max_ibuffer)
		if (ibuffer[i] != -1)
			return false;
	return true;
}

/**
	\brief	check acgtChromat
*/
bool check_acgt() {
	LL tot = 0;
	bool ret = true;
	
	rep(i, 0, 25) {
		int sz = SZ(acgtChromat[i]);
		if (sz == 0)	continue;
		
		const vector<acgt_t>& vacgt = acgtChromat[i];
		int tmp;
		rep(i, 0, sz) {
			const acgt_t& acgt = vacgt[i];
			tmp = acgt.c[0] + acgt.c[1] + acgt.c[2] + acgt.c[3];
			if (tmp >= layer_read.len+10)
				ret = false;
		}
		cout << "sizeof acgtChromat[" << i << "] = " << sz * sizeof(acgt_t) << endl;
		tot += sz;
	}
	cout << "tot sizeof acgtCrhomat = " << tot * sizeof(acgt_t) << endl;
	
	return ret;
}

/**
	\brief check sepChromat
*/
bool check_sep() {
	LL tot = 0;
	bool ret = true;
	
	rep(i, 0, 25) {
		int sz = SZ(sepChromat[i]);
		if (sz == 0)	continue;
		
		const vector<sep_t> vsep = sepChromat[i];
		bool flag = true;
		rep(i, 1, sz) {
			if (vsep[i].idx < vsep[i-1].idx) {
				flag = false;
				break;
			}
		}
		ret &= flag;
		if (!flag)
			cout << "sepChromat[" << i << "] is not `Increasing`." << endl;
		cout << "sizeof sepChromat[" << i << "] = " << sz * sizeof(sep_t) << endl;
		tot += sz;
	}
	cout << "tot sizeof sepChromat = " << tot * sizeof(sep_t) << endl;
	
	return ret;
}

/**
	\brief check sliceChromat
*/
bool check_slice() {
	LL tot = 0, tmp;
	bool ret = true;
	
	rep(i, 0, 25) {
		int sz = SZ(sliceChromat[i]);
		if (sz == 0)	continue;
		
		const vector<slice_t> vslc = sliceChromat[i];
		bool flag = true;
		rep(i, 1, sz) {
			if (vslc[i].idx < vslc[i-1].idx) {
				flag = false;
				break;
			}
		}
		ret &= flag;
		tmp = 0;
		rep(i, 0, sz) {
			tmp += sizeof(int);
			tmp += SZ(vslc[i]) * sizeof(feature_t);
		}
		if (!flag)
			cout << "sliceChromat[" << i << "] is not `Increasing`." << endl;
		cout << "sizeof sliceChromat[" << i << "] = " << tmp << endl;
		tot += tmp;
	}
	cout << "tot sizeof sliceChromat = " << tot << endl;
	
	return ret;
}

/**
	\brief check sgroupChromat
*/
bool check_sgroup() {
	LL tot = 0, tmp;
	bool ret = true;
	
	rep(i, 0, 25) {
		int sz = SZ(sgroupChromat[i]);
		if (sz == 0)	continue;
		
		const vector<sgroup_t> vsgrp = sgroupChromat[i];
		bool flag = true;
		rep(i, 1, sz) {
			if (vsgrp[i].idx < vsgrp[i-1].idx) {
				flag = false;
				break;
			}
		}
		ret &= flag;
		tmp = 0;
		rep(i, 0, sz) {
			tmp += sizeof(int);
			tmp += SZ(vsgrp[i]) * sizeof(feature_t);
		}
		if (!flag)
			cout << "sgroupChromat[" << i << "] is not `Increasing`." << endl;
		cout << "sizeof sgroupChromat[" << i << "] = " << tmp << endl;
		tot += tmp;
	}
	cout << "tot sizeof sgroupChromat = " << tot << endl;
	
	return ret;
}

/**
	\brief check groupChromat
*/
bool check_group() {
	LL tot = 0, tmp;
	bool ret = true;
	
	rep(i, 0, 25) {
		int sz = SZ(groupChromat[i]);
		if (sz == 0)	continue;
		
		const vector<group_t> vgrp = groupChromat[i];
		bool flag = true;
		rep(i, 1, sz) {
			if (vgrp[i].idx < vgrp[i-1].idx) {
				flag = false;
				break;
			}
		}
		ret &= flag;
		tmp = 0;
		rep(i, 0, sz) {
			tmp += sizeof(int);
			tmp += SZ(vgrp[i]) * sizeof(feature_t);
		}
		if (!flag)
			cout << "groupChromat[" << i << "] is not `Increasing`." << endl;
		cout << "sizeof groupChromat[" << i << "] = " << tmp << endl;
		tot += tmp;
	}
	cout << "tot sizeof groupChromat = " << tot << endl;
	
	return ret;
}
#endif

/**
	\brief	calculate the score for needman's function updated.
*/
inline int calcScore(char a, char b) {
	return (a==b) ? 1:-1;
}

/**
	\brief	get the id of char
*/
inline int getCharId(char c) {
	return charId[c];
}

/**
	\brief get the reverse complement of char
*/
inline char getComplement(char c) {
	return Complements[c];
}

/**
	\brief check if the char is `ACGT`
	\note	using charId[ch]==4 may be faster
*/
inline bool isACGT(char ch) {
	return ch=='A' || ch=='G' || ch=='C' || ch=='T';
}

/**
	\brief get the reverse complement of string
*/
inline string getReverseComplement(const string& line) {
	int len = line.length();
	string ret;

	per(i, 0, len)	ret.pb(getComplement(line[i]));
	return ret;
}

/**
	\brief 	delete the trie
	\param	rt: root of current sub-tree
			dep: depth of current node, if dep==sep_len, obviously a leaf node.
*/
void Delete_trie(trie_ptr rt, int dep) {
	if (dep == sep_len)	return ;
	rep(i, 0, 5) if (rt->nxt[i]) Delete_trie(rt->nxt[i], dep+1);
	delete rt;
}

#ifdef TRAIN_DEBUG
	LL leaf_num = 0, node_num = 0;
#endif
/**
	\brief	Insert the string into trie with return value
	\return	the leaf node of the string
*/
trie_ptr Insert_chr(char *s) {
	int i = 0, id;
	trie_ptr p = trie_root;

	while (i < sep_len) {
		id = getCharId(s[i]);
		if (!p->nxt[id]) break;
		p = p->nxt[id];
		++i;
	}
	#ifdef TRAIN_DEBUG
	node_num += sep_len - i;
	assert(node_num < 12207050);
	if (i < sep_len) ++leaf_num;
	#endif
	while(i < sep_len) {
		id = getCharId(s[i++]);
		p->nxt[id] = new trie_t(p);
		p = p->nxt[id];
	}

	return p;
}

/**
	\brief Insert the string into trie without return value
*/
void Insert(char *s) {
	int i = 0, id;
	trie_ptr p = trie_root;

	while (i < sep_len) {
		id = getCharId(s[i]);
		if (!p->nxt[id]) break;
		p = p->nxt[id];
		++i;
	}
#ifdef TRAIN_DEBUG
	node_num += sep_len - i;
	assert(node_num < 12207050);
	if (i < sep_len) ++leaf_num;
#endif

	while(i < sep_len) {
		id = getCharId(s[i++]);
		p->nxt[id] = new trie_t(p);
		p = p->nxt[id];
	}
}

/**
	\brief Insert the string into trie with return value
	\return	int, id of the string.
*/
int Insert_read(char *s) {
	int i = 0, id;
	trie_ptr p = trie_root;

	while (i < sep_len) {
		id = getCharId(s[i]);
		if (!p->nxt[id]) break;
		p = p->nxt[id];
		++i;
	}
#ifdef TRAIN_DEBUG
	node_num += sep_len - i;
	assert(node_num < 12207050);
	if (i < sep_len) ++leaf_num;
#endif
	while(i < sep_len) {
		id = getCharId(s[i++]);
		p->nxt[id] = new trie_t(p);
		p = p->nxt[id];
	}

	id = (char *)p->nxt[1] - (char *)NULL;
	if (id == 0) {
		int c[5];
		memset(c, 0, sizeof(c));
		rep(j, 0, sep_len) ++c[getCharId(s[j])];
		
		uint tmp = (c[3]<<24) | (c[2]<<16) | (c[1]<<8) | c[0];
		p->nxt[0] = (trie_ptr) tmp;
		p->nxt[1] = (trie_ptr) (++nleaf);
		id = nleaf;
	}

	return id;
}

/**
	\brief	init the trie, if root not NULL, then delete the whole tree
*/
void init_trie() {
	if (trie_root)
		Delete_trie(trie_root, 0);
	trie_root = new trie_t();
}

/**
	\brief	insert the haiming distance <= 1's node with same id.
*/
//#define USE_EXISTS_SEP
void Insert_grp(char *d) {
	#ifdef DEBUG
	static int cnt = 0;
	++cnt;
	if (cnt%10000 == 0)
		cout << cnt << endl;
	#endif
	const int gid = ++nleaf;
	char s[16];
	int c[5];
	int i, j, k, id;
	trie_ptr p;

	memset(c, 0, sizeof(c));
	for (i=1; i<=sep_len; ++i) ++c[s[i] = d[i-1]];

	// shift right 1
	--c[s[sep_len]];
	for (j=0; j<4; ++j) {
		++c[s[0] = j];
		i = 0;
		p = trie_root;

		while (i < sep_len) {
			id = s[i];
			if (!p->nxt[id]) break;
			p = p->nxt[id];
			++i;
		}

	#ifndef USE_EXISTS_SEP
	#ifdef TRAIN_DEBUG
		node_num += sep_len - i;
		assert(node_num < 12207050);
		if (i < sep_len) ++leaf_num;
	#endif
		while (i < sep_len) {
			id = s[i++];
			p->nxt[id] = new trie_t(p);
			p = p->nxt[id];
		}
		if (p->nxt[1] == NULL) {
			p->nxt[1] = (trie_ptr) gid;
			p->nxt[0] = (trie_ptr) ((c[3]<<24) | (c[2]<<16) | (c[1]<<8) | c[0]);
		}
	#else
		if (i>=sep_len && p->nxt[1]==NULL) {
			p->nxt[1] = (trie_ptr) gid;
			p->nxt[0] = (trie_ptr) ((c[3]<<24) | (c[2]<<16) | (c[1]<<8) | c[0]);
		}
	#endif
		--c[j];
	}
	++c[s[sep_len]];

	// shift left 1
	--c[s[1]];
	for (j=0; j<4; ++j) {
		++c[s[sep_len+1] = j];
		i = 2;
		p = trie_root;

		while (i <= sep_len+1) {
			id = s[i];
			if (!p->nxt[id]) break;
			p = p->nxt[id];
			++i;
		}

	#ifndef USE_EXISTS_SEP
	#ifdef TRAIN_DEBUG
		node_num += sep_len + 2 - i;
		assert(node_num < 12207050);
		if (i <= sep_len+1) ++leaf_num;
	#endif
		while (i <= sep_len+1) {
			id = s[i++];
			p->nxt[id] = new trie_t(p);
			p = p->nxt[id];
		}
		if (p->nxt[1] == NULL) {
			p->nxt[1] = (trie_ptr) gid;
			p->nxt[0] = (trie_ptr) ((c[3]<<24) | (c[2]<<16) | (c[1]<<8) | c[0]);
		}
	#else
		if (i>sep_len+1 && p->nxt[1]==NULL) {
			p->nxt[1] = (trie_ptr) gid;
			p->nxt[0] = (trie_ptr) ((c[3]<<24) | (c[2]<<16) | (c[1]<<8) | c[0]);
		}
	#endif
		--c[j];
	}
	++c[s[1]];

	// replace
	int tmp;
	for (k=1; k<=sep_len; ++k) {
		--c[tmp = s[k]];
		for (j=0; j<4; ++j) {
			++c[s[k] = j];
			i = 1;
			p = trie_root;

			while (i <= sep_len) {
				id = s[i];
				if (!p->nxt[id]) break;
				p = p->nxt[id];
				++i;
			}
		#ifndef USE_EXISTS_SEP
		#ifdef TRAIN_DEBUG
			node_num += sep_len +1 - i;
			assert(node_num < 12207050);
			if (i <= sep_len) ++leaf_num;
		#endif
			while (i <= sep_len) {
				id = s[i++];
				p->nxt[id] = new trie_t(p);
				p = p->nxt[id];
			}
			if (p->nxt[1] == NULL) {
				p->nxt[1] = (trie_ptr) gid;
				p->nxt[0] = (trie_ptr) ((c[3]<<24) | (c[2]<<16) | (c[1]<<8) | c[0]);
			}
		#else
			if (i>sep_len && p->nxt[1]==NULL) {
				p->nxt[1] = (trie_ptr) gid;
				p->nxt[0] = (trie_ptr) ((c[3]<<24) | (c[2]<<16) | (c[1]<<8) | c[0]);
			}
		#endif
			--c[j];
		}
		++c[s[k] = tmp];
	}

	// replace 2
	{
		int kk, jj;
		int tmp1, tmp2;
		for (k=1; k<=sep_len; ++k) {
			--c[tmp1 = s[k]];
			for (kk=k+1; kk<=sep_len; ++kk) {
				--c[tmp2 = s[kk]];
				for (j=0; j<4; ++j) {
					++c[s[k] = j];
					for (jj=0; jj<4; ++jj) {
						++c[s[kk] = jj];
						i = 1;
						p = trie_root;

						while (i <= sep_len) {
							id = s[i];
							if (!p->nxt[id]) break;
							p = p->nxt[id];
							++i;
						}
					#ifndef USE_EXISTS_SEP
					#ifdef TRAIN_DEBUG
						node_num += sep_len +1 - i;
						assert(node_num < 12207050);
						if (i <= sep_len) ++leaf_num;
					#endif
						while (i <= sep_len) {
							id = s[i++];
							p->nxt[id] = new trie_t(p);
							p = p->nxt[id];
						}
						if (p->nxt[1] == NULL) {
							p->nxt[1] = (trie_ptr) gid;
							p->nxt[0] = (trie_ptr) ((c[3]<<24) | (c[2]<<16) | (c[1]<<8) | c[0]);
						}
					#else
						if (i>sep_len && p->nxt[1]==NULL) {
							p->nxt[1] = (trie_ptr) gid;
							p->nxt[0] = (trie_ptr) ((c[3]<<24) | (c[2]<<16) | (c[1]<<8) | c[0]);
						}
					#endif
						--c[jj];
					}
					--c[j];
				}
				++c[s[k] = tmp2];
			}
			++c[s[k] = tmp1];
		}
	}
}

/**
	\brief	traverse the trie and fuzzy match the node with same id.
*/
void map_trie_chr(trie_ptr rt, int dep) {
	if (dep == sep_len) {
		// cout << (char *)rt->nxt[1] - (char *)NULL << endl;
		if (rt->nxt[1] == NULL) {
			Insert_grp(buffer);
		}
		return ;
	}

	rep(i, 0, 5) {
		if (rt->nxt[i]) {
			buffer[dep] = i;
			map_trie_chr(rt->nxt[i], dep+1);
		}
	}
}

/**
	\brief	restore the string of sep
*/
inline void restore_sep(trie_ptr leaf, char *s) {
	trie_ptr p = leaf, q;
	int i;
	
	while ((q=p->fa) != NULL) {	
	#ifdef DEBUG
		bool flag = false;
	#endif
		for (i=0; i<5; ++i) {
			if (q->nxt[i] == p) {
				#ifdef DEBUG
					flag = true;
				#endif
				*s = acgt_s[i];
				--s;
				break;
			}
		}
	#ifdef DEBUG
		assert(flag);
	#endif
		p = q;
	}
}

/**
	\brief void function
*/
void clear_trie_chr(void) {
	/* do nothing */;
}

/**
	\brief 	calculate the score between `group a` and `read-pair b`
	\return	score
*/
score_type score_group(const group_t& a, const slice_t& b) {
	const vector<feature_t>& afeat = a.feat;
	const vector<feature_t>& bfeat = b.feat;
	const int sza = SZ(afeat);
	const int szb = SZ(bfeat);
	score_type ret = 0;
	vector<feature_t>::const_iterator iter;

	int i = 0, j = 0;

	while (j < szb) {
		iter = lower_bound(all(afeat), bfeat[j]);
		if (iter!=afeat.end() && iter->id==bfeat[j].id) {
			ret += iter->c>=bfeat[j].c ? 0:bfeat[j].c-iter->c;
		} else {
			ret += bfeat[j].c;
		}
		++j;
	}

	// while (i<sza && j<szb) {
	// 	if (afeat[i].id == bfeat[j].id) {
	// 		ret += afeat[i].c>=bfeat[j].c ? 0:bfeat[j].c-afeat[i].c;
	// 		++i;
	// 		++j;
	// 	} else if (afeat[i].id < bfeat[j].id) {
	// 		++i;
	// 	} else {
	// 		ret += bfeat[j].c;
	// 		++j;
	// 	}
	// }
	// while (j < szb) ret += bfeat[j++].c;

	return ret;
}

/**
	\brief	calculate the score between `sgroup a` and `read-pair b`
	\return score
*/
score_type score_sgroup(const sgroup_t& a, const slice_t& b) {
	const vector<feature_t>& afeat = a.feat;
	const vector<feature_t>& bfeat = b.feat;
	const int sza = SZ(afeat);
	const int szb = SZ(bfeat);
	score_type ret = 0;
	vector<feature_t>::const_iterator iter;

	int i = 0, j = 0;

	// while (j < szb) {
	// 	iter = lower_bound(all(afeat), bfeat[j]);
	// 	if (iter!=afeat.end() && iter->id==bfeat[j].id) {
	// 		ret += iter->c>=bfeat[j].c ? 0:bfeat[j].c-iter->c;
	// 	} else {
	// 		ret += bfeat[j].c;
	// 	}
	// 	++j;
	// }

	while (i<sza && j<szb) {
		if (afeat[i].id == bfeat[j].id) {
			ret += afeat[i].c>=bfeat[j].c ? 0:bfeat[j].c-afeat[i].c;
			++i;
			++j;
		} else if (afeat[i].id < bfeat[j].id) {
			++i;
		} else {
			ret += bfeat[j].c;
			++j;
		}
	}
	while (j < szb) ret += bfeat[j++].c;

	return ret;
}

/**
	\brief 	calculate the score between `slice a` and `read-pair b`
	\return score
*/
score_type score_slice(const slice_t& a, const slice_t& b) {
	const vector<feature_t>& afeat = a.feat;
	const vector<feature_t>& bfeat = b.feat;
	const int sza = SZ(afeat);
	const int szb = SZ(bfeat);
	score_type ret = 0;
	vector<feature_t>::const_iterator iter;

	int i = 0, j = 0;

	// while (j < szb) {
	// 	iter = lower_bound(all(afeat), bfeat[j]);
	// 	if (iter!=afeat.end() && iter->id==bfeat[j].id) {
	// 		ret += iter->c>=bfeat[j].c ? 0:bfeat[j].c-iter->c;
	// 	} else {
	// 		ret += bfeat[j].c;
	// 	}
	// 	++j;
	// }

	while (i<sza && j<szb) {
		if (afeat[i].id == bfeat[j].id) {
			ret += afeat[i].c>=bfeat[j].c ? 0:bfeat[j].c-afeat[i].c;
			++i;
			++j;
		} else if (afeat[i].id < bfeat[j].id) {
			//ret += afeat[i].c >> 2;
			++i;
		} else {
			ret += bfeat[j].c;
			++j;
		}
	}
	while (j < szb) ret += bfeat[j++].c;
//	while (i < sza) ret += afeat[i++].c >> 2;

	return ret;
}

/**
	\brief 	calculate the score between `chromat-read a` and `query-read b`
	\return score
*/
score_type score_acgt(const acgt_t& a, const acgt_t& b) {
	score_type ret = 0;

	rep(i, 0, 4) {
		ret += abs(a.c[i] - b.c[i]);
	}

	return ret;
}

class DNASequencing {
public:
	vi chrIds;
	int chrId;

	DNASequencing() {
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
	}
	
	/**
		\brief	init the parameter of layer
		\param	testDifficulty: 0, small case; 1, medium case; 2, large case.
	*/
	void init_param(const int testDifficulty) {

		if (testDifficulty == 0) {
			sep_len = 10;
			layer_read.len = 150;
			layer_slice.len = 1500;
			layer_sgroup.len = 15000;
			layer_group.len = 300000;

			layer_slice.feature_num = 200;
			layer_sgroup.feature_num = 400;
			layer_group.feature_num = 4000;

			layer_read.topk = 200;
			layer_slice.topk = 2;
			layer_sgroup.topk = 10;
			layer_group.topk = 100;

			layer_slice.feature_lbound = 2;
			layer_sgroup.feature_lbound = 3;
			layer_group.feature_lbound = 3;
			#ifdef TRAIN_DEBUG
			layer_slice.feature_lbound = 2;
			layer_sgroup.feature_lbound = 3;
			layer_group.feature_lbound = 3;
			#endif

			layer_read.score_bound = 40;
			layer_slice.score_bound = 240;
			layer_sgroup.score_bound = 230;
			layer_group.score_bound = 220;


		} else if (testDifficulty == 1) {
			sep_len = 10;
			layer_read.len = 150;
			layer_slice.len = 1050;
			layer_sgroup.len = 10500;
			layer_group.len = 105000;
			abort();
		} else {
			abort();
		}

	}
	
	/**
		\brief	init the environment according `testDifficulty`
		\param	testDifficulty: 0, small case; 1, medium case; 2, large case.
	*/
	int initTest(int testDifficulty) {
		// init the parameter
		init_param(testDifficulty);

		// clear the chrIds
		chrIds.clr();

		// clear the feature & presents of chromatid
		rep(i, 1, 25) {
			acgtChromat[i].clr();
			sepChromat[i].clr();
			sliceChromat[i].clr();
			sgroupChromat[i].clr();
			groupChromat[i].clr();
		}

		// init the trie
		init_trie();

		// clear the ibuffer
		memset(ibuffer, -1, sizeof(ibuffer));

		return 0;
	}

	/**
		\brief 	separate the chromat into sep, and store trie's leaf node into `SepChromat`
		\param	chromatidSequence, sequence of the chromat
	*/
	void separateChromat(const vstr& chromatidSequence) {
		char s[24];
		vector<sep_t>& vsep = sepChromat[chrId];
		int slice_ed = layer_slice.len - sep_len + 1;
		int nline = SZ(chromatidSequence);
		int idx = 0, l;
		int ll = 0;
		int i, j, k;
		bool flag;
		sep_t sep;

		/*
		for (k=0; k<nline; ++k) {
			const string& line = chromatidSequence[k];
			const int len = line.length();

			// check line is all 'N'
			flag = true;
			if (line[0] == 'N') {
				flag = false;
				for (i=0; i<len; ++i) {
					if (line[i] != 'N')	{
						flag = true;
						break;
					}
				}
			}

			if (flag) {
				l = 0;
				for (i=0; i<len; ++i) {
					buffer[ll++] = line[i];
					s[l++] = line[i];
					if (l == sep_len) {
						sep.leaf = Insert_chr(s);
						sep.idx = idx + i - sep_len + 1;
						vsep.pb(sep);
						l = 0;
					}
					if (ll == layer_slice.len) {

					}
				}
			} else {
				for (i=0; i<len; ++i)
					buffer[ll++] = line[i];
			}

			if (ll >= layer_slice.len) {
				int ed = layer_slice.len - sep_len + 1;
				i = 0;

				while (i < ed) {
					Insert(buffer+i);
					++i;
				}

				for (j=0,i=ed+sep_len-1; i<ll; ++i,++j) buffer[j] = buffer[i];
				ll = j;
			}
			idx += len;
		}
		if (ll >= sep_len) {
			int ed = ll - sep_len + 1;
			i = 0;

			while (i < ed) {
				Insert(buffer+i);
				++i;
			}
		}
		*/
		// find the begin index
		int begIdx = 0;
		flag = true;
		while (begIdx < nline) {
			const string& line = chromatidSequence[begIdx];
			const int len = line.length();
			for (i=0; i<len; ++i) {
				if (line[i] != 'N') {
					flag = false;
					break;
				}
			}
			if (!flag) break;
			++begIdx;
			idx += len;
		}

		// find the end index
		int endIdx = nline - 1;
		flag = true;
		while (endIdx > begIdx) {
			const string& line = chromatidSequence[endIdx];
			const int len = line.length();
			for (i=len-1; i>=0; --i) {
				if (line[i] != 'N') {
					flag = false;
					break;
				}
			}
			if (!flag) break;
			--endIdx;
		}

		for (k=begIdx; k<=endIdx; ++k) {
			const string& line = chromatidSequence[k];
			const int len = line.length();

			for (i=l=0; i<len; ++i) {
				buffer[ll++] = line[i];
				s[l++] = line[i];
				if (l == sep_len) {
					sep.leaf = Insert_chr(s);
					sep.idx = idx + i - sep_len + 1;
					vsep.pb(sep);
					l = 0;
				}
			}

			if (ll >= layer_slice.len) {
				for (i=0; i<slice_ed; ++i) Insert(buffer+i);
				for (j=0,i=slice_ed+sep_len-1; i<ll; ++i,++j) buffer[j] = buffer[i];
				ll = j;
			}
			idx += len;
		}
		if (ll >= sep_len) {
			slice_ed = ll - sep_len + 1;
			for (i=0; i<slice_ed; ++i) Insert(buffer+i);
		}
	}

	/**
		\brief pile up the sep to read
	*/
	void pileChromat_read() {
		const vector<sep_t>& vsep = sepChromat[chrId];
		const int nsep = SZ(vsep);
		vector<acgt_t>& vacgt = acgtChromat[chrId];
		const int m = layer_read.len / sep_len;
		acgt_t acgt;
		int i = 0, j;

		while (i < nsep) {
			acgt.clr();

			for (j=0; j<m&&i<nsep; ++j,++i) {
				const trie_ptr& leaf = vsep[i].leaf;
				uint val = (char *)leaf->nxt[0] - (char *)NULL;
				acgt.c[0] += val & 255;
				acgt.c[1] += (val>>8) & 255;
				acgt.c[2] += (val>>16) & 255;
				acgt.c[3] += (val>>24) & 255;
			}

			vacgt.pb(acgt);

			#ifdef LOCAL_DEBUG
			if (i>0 && i%10000==0)
				acgt.print();
			#endif
		}
	}

	/**
		\brief pile up the sep to slice
	*/
	void pileChromat_slice() {
		const vector<sep_t>& vsep = sepChromat[chrId];
		const int nsep = SZ(vsep);
		vector<slice_t>& vslc = sliceChromat[chrId];
		const int nfeature = layer_slice.feature_num;
		const int feature_lbound = layer_slice.feature_lbound;
		const int m = layer_slice.len / sep_len;
		int bidx, szvf, l, szfeature;
		vector<feature_t> vfeat;
		slice_t slice;
		int i = 0, j = 0, k;

		while (i < nsep) {
			bidx = vsep[i].idx;
			l = 0;
			
			for (j=0; j<m&&i<nsep; ++j,++i) {
				restore_sep(vsep[i].leaf, buffer+l+sep_len-1);
				l += sep_len;
			}

			// #ifdef LOCAL_DEBUG
				// cout << "bidx: " << bidx << endl;
				// rep(ii, 0, l) cout << buffer[ii];
				// cout << endl;
			// #endif
			szvf = 0;
			for (k=0; k<l-sep_len+1; ++k) {
				int id = Insert_read(buffer+k);
				// #ifdef LOCAL_DEBUG
				// cout << id << ": ";
				// rep(ii, 0, sep_len) cout << buffer[k+ii];
				// cout << endl;
				// #endif
				if (ibuffer[id] < 0) {
					ibuffer[id] = szvf++;
					vfeat.pb(feature_t(1, id));
				} else {
					++vfeat[ibuffer[id]].c;
				}
			}

			#ifdef DEBUG
			assert(SZ(vfeat) == szvf);
			#endif
			// resize vfeat according the bound of feature
			{
				int ii = 0, jj = 0;

				while (ii < szvf) {
					if (vfeat[ii].c>=feature_lbound)
						vfeat[jj++] = vfeat[ii];
					ibuffer[vfeat[ii].id] = -1;
					++ii;
				}

				szvf = jj;
				vfeat.resize(szvf);
			}
			sort(all(vfeat), feat_compc);
			#ifdef DEBUG
			assert(SZ(vfeat) == szvf);
			#endif

			szfeature = min(nfeature, szvf);
			slice.idx = bidx;
			rep(ii, 0, szfeature) {
				slice.pb(vfeat[ii]);
			}
			slice.sorted();
			vslc.pb(slice);

			#ifdef DEBUG
			if (i>0 && i%1000 == 0)
				slice.print();
			#endif

			slice.clr();
			vfeat.clr();
		}
	}

	/**
		\brief pile up the slice to sub-group
	*/
	void pileChromat_sgroup() {
		const vector<slice_t>& vslc = sliceChromat[chrId];
		const int nslice = SZ(vslc);
		vector<sgroup_t>& vsgrp = sgroupChromat[chrId];
		const int m = layer_sgroup.len / layer_slice.len;
		const int nfeature = layer_sgroup.feature_num;
		const int feature_lbound = layer_sgroup.feature_lbound;
		int bidx, szvf, szfeature;
		vector<feature_t> vfeat;
		sgroup_t sgroup;
		int i = 0, j;

		while (i < nslice) {
			bidx = i;
			szvf = 0;

			for (j=0; j<m&&i<nslice; ++i,++j) {
				const slice_t& slice = vslc[i];
				szfeature = SZ(slice);
				rep(ii, 0, szfeature) {
					const int& k = slice.feat[ii].id;
					if (ibuffer[k] < 0) {
						ibuffer[k] = szvf++;
						vfeat.pb(slice.feat[ii]);
					} else {
						vfeat[ibuffer[k]].c += slice.feat[ii].c;
					}
				}
			}

			#ifdef DEBUG
			assert(SZ(vfeat) == szvf);
			#endif
			// resize vfeat according the bound of feature
			{
				int ii = 0, jj = 0;

				while (ii < szvf) {
					if (vfeat[ii].c>=feature_lbound)
						vfeat[jj++] = vfeat[ii];
					ibuffer[vfeat[ii].id] = -1;
					++ii;
				}

				szvf = jj;
				vfeat.resize(szvf);
			}
			sort(all(vfeat), feat_compc);
			
			#ifdef DEBUG
			assert(SZ(vfeat) == szvf);
			#endif

			szfeature = min(nfeature, szvf);
			sgroup.idx = bidx;
			rep(ii, 0, szfeature) {
				sgroup.pb(vfeat[ii]);
			}
			sgroup.sorted();
			vsgrp.pb(sgroup);

			#ifdef DEBUG
			if (i>0 && i%1000 == 0)
				sgroup.print();
			#endif

			sgroup.clr();
			vfeat.clr();
		}
	}

	/**
		\brief pile up the sgroup to group
	*/
	void pileChromat_group() {
		const vector<sgroup_t> vsgrp = sgroupChromat[chrId];
		const int nsgrp = SZ(vsgrp);
		vector<group_t>& vgrp = groupChromat[chrId];
		const int m = layer_group.len / layer_sgroup.len;
		const int nfeature = layer_group.feature_num;
		const int feature_lbound = layer_group.feature_lbound;
		int bidx, szvf, szfeature;
		group_t group;
		vector<feature_t> vfeat;
		int i = 0, j;

		while (i < nsgrp) {
			bidx = i;
			szvf = 0;

			for (j=0; j<m&&i<nsgrp; ++i,++j) {
				const sgroup_t& sgrp = vsgrp[i];
				szfeature = SZ(sgrp);
				rep(ii, 0, szfeature) {
					const int& k = sgrp.feat[ii].id;
					if (ibuffer[k] < 0) {
						ibuffer[k] = szvf++;
						vfeat.pb(sgrp.feat[ii]);
					} else {
						vfeat[ibuffer[k]].c += sgrp.feat[ii].c;
					}
				}
			}

			#ifdef DEBUG
			assert(SZ(vfeat) == szvf);
			#endif
			// resize vfeat according the boundary of feature
			{
				int ii = 0, jj = 0;

				while (ii < szvf) {
					if (vfeat[ii].c>=feature_lbound)
						vfeat[jj++] = vfeat[ii];
					ibuffer[vfeat[ii].id] = -1;
					++ii;
				}

				szvf = jj;
				vfeat.resize(szvf);
			}
			sort(all(vfeat), feat_compc);
			
			#ifdef DEBUG
			assert(SZ(vfeat) == szvf);
			#endif

			szfeature = min(nfeature, szvf);
			group.idx = bidx;
			rep(ii, 0, szfeature) {
				group.pb(vfeat[ii]);
			}
			group.sorted();
			vgrp.pb(group);

			#ifdef DEBUG
			if (i>0 && i%100 == 0)
				group.print();
			#endif
			group.clr();
			vfeat.clr();
		}
	}

	/**
		\brief pile up the chromat to form 4 layers:
			`group`、`sgroup`、`slice`, `read`(aka acgt)
	*/
	void pileChromat() {
		/**
			\step 0: pile up the layer 0 -- read
		*/
		#ifdef DEBUG
			cout << "pileChromat_read" << endl;
		#endif
		pileChromat_read();
		#ifdef DEBUG
		if( !check_ibuffer() )
			cout << "check ibuffer wrong" << endl;
		if ( !check_acgt() )
			cout << "check acgt wrong" << endl;
		#endif

		/**
			\step 1: pile up layer 1 -- `slice`
		*/
		#ifdef DEBUG
			cout << "pileChromat_slice" << endl;
		#endif
		pileChromat_slice();
		#ifdef DEBUG
		if( !check_ibuffer() )
			cout << "check ibuffer wrong" << endl;
		if ( !check_slice() )
			cout << "check slice wrong" << endl;
		#endif

		// /**
			// \step 1.5: clear sepChromat to release memory
		// */
		// sepChromat.clr();

		/**
			\step 2: pile up layer 2 -- `sgroup`
		*/
		#ifdef DEBUG
			cout << "pileChromat_sgroup" << endl;
		#endif
		pileChromat_sgroup();
		#ifdef DEBUG
		if( !check_ibuffer() )
			cout << "check ibuffer wrong" << endl;
		if ( !check_sgroup() )
			cout << "check sgroup wrong" << endl;
		#endif

		/**
			\step 3: pile up layer 3 -- `group`
		*/
		#ifdef DEBUG
			cout << "pileChromat_group" << endl;
		#endif
		pileChromat_group();
		#ifdef DEBUG
		if( !check_ibuffer() )
			cout << "check ibuffer wrong" << endl;
		if ( !check_group() )
			cout << "check group wrong" << endl;
		#endif
	}
	
	/**
		\brief	pass the reference chromat
		\note	store the `chromatidSequenceId` into chrIds and compress the `chromatidSequence`
	*/
	int passReferenceGenome(int chromatidSequenceId, const vector<string>& chromatidSequence) {
		// push chrId into chrIds
		chrIds.pb(chrId = chromatidSequenceId);

		// split the chromat into sep.
		separateChromat(chromatidSequence);

		return 0;
	}
	
	/**
		\brief	preprecessing the trie and chromat
		\note	1. map all leaf node of trie with same id if their haiming distance is less than 1.
				2. pile up all the chromat to form 4 layers each.
	*/
	int preProcessing() {
		int sz = SZ(chrIds);

		// mapping the similar leaf with same id
		map_trie_chr(trie_root, 0);
		#ifdef TRAIN_DEBUG
		cout << "nleaf = " << nleaf << "leaf_num = " << leaf_num << ", node_num = " << node_num << "." << endl;
		#endif
		cout << "nleaf = " << nleaf << endl;
		
		// pile up the chromat to form layers
		rep(i, 0, sz) {
			chrId = chrIds[i];
			pileChromat();
		}

		// release the memory of chr's trie
		clear_trie_chr();

		return 0;
	}

	/**
		\brief	Generate a failure but format right answer
		\param	prefix: prefix of read
				strand: flag of read pair
	*/
	inline string getFailureResult(const string& prefix, const char strand='+') {
		#ifdef LOCAL_DEBUG
		return prefix + ",0,1,150," + strand + ",0.0001";
		#else
		return prefix + ",20,1,150," + strand + ",0.0001";
		#endif
	}
	
	/**
		\brief	calculate the `acgt` num of string
	*/
	void calcACGT(const string& s, acgt_t& acgt) {
		const int len = s.length();
		int c[5];

		memset(c, 0, sizeof(c));
		rep(i, 0, len) ++c[getCharId(s[i])];
		
		rep(i, 0, 4) acgt.c[i] = c[i];
	}
	
	/**
		\brief	calculate the `acgt` num of string pair
	*/
	void calcACGT(const string& s1, const string& s2, acgt_t& acgt) {
		int len;
		int c[5];

		memset(c, 0, sizeof(c));

		len = s1.length();
		rep(i, 0, len) ++c[getCharId(s1[i])];
		len = s2.length();
		rep(i, 0, len) ++c[getCharId(s2[i])];

		rep(i, 0, 4) acgt.c[i] = c[i];
	}

	/**
		\brief	calculate the slice of string
	*/
	void calcSlice(const string& s, slice_t& slice, const int idx=0) {
		int len = s.length();
		int szvf = 0, k;
		vector<feature_t>& vfeat = slice.feat;
		
		vfeat.clr();
		
		strncpy(buffer, s.c_str(), len);
		// len = len - sep_len + 1;
		// rep(i, 0, len) {
		// 	k = Insert_read(buffer + i);
		// 	if (ibuffer[k] < 0) {
		// 		ibuffer[k] = szvf++;
		// 		vfeat.pb(feature_t(1, k));
		// 	} else {
		// 		++vfeat[ibuffer[k]].c;
		// 	}
		// }
		#ifdef TRAIN_DEBUG
		int cnt = 0;
		#endif
		for (int i=0; i+sep_len<=len; i+=sep_len) {
			#ifdef TRAIN_DEBUG
			int leaf_num_ = leaf_num;
			#endif
			k = Insert_read(buffer + i);
			#ifdef TRAIN_DEBUG
			cnt += leaf_num > leaf_num_;
			#endif
			if (ibuffer[k] < 0) {
				ibuffer[k] = szvf++;
				vfeat.pb(feature_t(1, k));
			} else {
				++vfeat[ibuffer[k]].c;
			}
		}

		#ifdef TRAIN_DEBUG
		cout << "delta_leaf = " << cnt << endl;
		#endif

		#ifdef DEBUG
		assert(SZ(vfeat) == szvf);
		#endif
		rep(i, 0, szvf) ibuffer[vfeat[i].id] = -1;
		slice.idx = idx;
		slice.sorted();
	}
	
	/**
		\brief	calculate the slice of string pair
	*/
	void calcSlice(const string& l1, const string& l2, slice_t& slice) {
		int len, szvf;
		int k;
		vector<feature_t>& vfeat = slice.feat;
		
		vfeat.clr();
		
		// handle first string
		len = l1.length();
		szvf = 0;
		strncpy(buffer, l1.c_str(), len);
		// len = len - sep_len + 1;
		// rep(i, 0, len) {
		// 	k = Insert_read(buffer + i);
		// 	if (ibuffer[k] < 0) {
		// 		ibuffer[k] = szvf++;
		// 		vfeat.pb(feature_t(1, k));
		// 	} else {
		// 		++vfeat[ibuffer[k]].c;
		// 	}
		// }
		#ifdef TRAIN_DEBUG
		int cnt = 0;
		#endif
		for (int i=0; i+sep_len<=len; i+=sep_len) {
			#ifdef TRAIN_DEBUG
			int leaf_num_ = leaf_num;
			#endif
			k = Insert_read(buffer + i);
			#ifdef TRAIN_DEBUG
			cnt += leaf_num > leaf_num_;
			#endif
			if (ibuffer[k] < 0) {
				ibuffer[k] = szvf++;
				vfeat.pb(feature_t(1, k));
			} else {
				++vfeat[ibuffer[k]].c;
			}
		}

		// handle second string
		len = l2.length();
		strncpy(buffer, l2.c_str(), len);
		// len = len - sep_len + 1;
		// rep(i, 0, len) {
		// 	const int k = Insert_read(buffer + i);
		// 	if (ibuffer[k] < 0) {
		// 		ibuffer[k] = szvf++;
		// 		vfeat.pb(feature_t(1, k));
		// 	} else {
		// 		++vfeat[ibuffer[k]].c;
		// 	}
		// }
		
		for (int i=0; i+sep_len<=len; i+=sep_len) {
			#ifdef TRAIN_DEBUG
			int leaf_num_ = leaf_num;
			#endif
			k = Insert_read(buffer + i);
			#ifdef TRAIN_DEBUG
			cnt += leaf_num > leaf_num_;
			#endif
			if (ibuffer[k] < 0) {
				ibuffer[k] = szvf++;
				vfeat.pb(feature_t(1, k));
			} else {
				++vfeat[ibuffer[k]].c;
			}
		}

		#ifdef TRAIN_DEBUG
		cout << "delta_leaf = " << cnt << endl;
		#endif

		#ifdef DEBUG
		assert(SZ(vfeat) == szvf);
		#endif
		rep(i, 0, szvf) ibuffer[vfeat[i].id] = -1;
		slice.sorted();
	}

	/**
		\brief choose the best group
	*/
	void chooseBstGrp(const slice_t& slice, vi& ret) {
		const vector<group_t>& vgrp = groupChromat[chrId];
		int sz = SZ(vgrp);
		const int topk = layer_group.topk;
		const int score_bound = layer_group.score_bound;
		priority_queue<read_chr_t> Q;
		score_type score;
		int szQ = 0;
		

		ret.clr();
		rep(i, 0, sz) {
			score = score_group(vgrp[i], slice);
			// #ifdef DEBUG
			// cout << "group score = " << score << endl;
			// #endif
			if (score <= score_bound) {
				if (szQ < topk) {
					szQ++;
					Q.push(read_chr_t(vgrp[i].idx, score));
				} else if (score < Q.top().score) {
					Q.pop();
					Q.push(read_chr_t(vgrp[i].idx, score));
				}
			}
		}

		#ifdef DEBUG
		assert(SZ(Q) == szQ);
		#endif

		#ifdef TRAIN_DEBUG
			cout << "chooseBstGrp" << endl;
		#endif
		while (!Q.empty()) {
			// #ifdef DEBUG
			// Q.top().print();
			// #endif
			ret.pb(Q.top().idx);
			#ifdef TRAIN_DEBUG
			cout << Q.top().score << " ";
			#endif
			Q.pop();
		}
		#ifdef TRAIN_DEBUG
			cout << endl;
		#endif
		sort(all(ret));
	}

	/**
		\brief choose the best sub-group
	*/ 
	void chooseBstSgrp(const slice_t& slice, const vi& bstGrp, vi& ret) {
		const vector<sgroup_t>& vsgrp = sgroupChromat[chrId];
		int sz = SZ(vsgrp), szgp = SZ(bstGrp);
		const int topk = layer_sgroup.topk;
		const int score_bound = layer_sgroup.score_bound;
		const int m = layer_group.len / layer_sgroup.len;
		priority_queue<read_chr_t> Q;
		score_type score;
		int szQ;
		vi vtmp;

		ret.clr();
		rep(j, 0, szgp) {
			szQ = 0;
			#ifdef DEBUG
			assert(SZ(Q) == szQ);
			#endif

			for (int i=bstGrp[j],k=0; k<m&&i<sz; ++k,++i) {
				score = score_sgroup(vsgrp[i], slice);
				// #ifdef DEBUG
				// cout << "sgroup score = " << score << endl;
				// #endif
				if (score <= score_bound) {
					if (szQ < topk) {
						szQ++;
						Q.push(read_chr_t(vsgrp[i].idx, score));
					} else if (score < Q.top().score) {
						Q.pop();
						Q.push(read_chr_t(vsgrp[i].idx, score));
					}
				}
			}
			#ifdef DEBUG
			assert(SZ(Q) == szQ);
			#endif

		#ifdef TRAIN_DEBUG
			cout << "chooseBstSgrp" << " ";
			cout << Q.top().score << " " << endl;
		#endif
			while (!Q.empty()) {
				// #ifdef DEBUG
				// Q.top().print();
				// #endif
				vtmp.pb(Q.top().idx);
				// #ifdef TRAIN_DEBUG
				// cout << Q.top().score << " ";
				// #endif
				Q.pop();
			}
		// #ifdef TRAIN_DEBUG
		// 	cout << endl;
		// #endif

			sort(all(vtmp));
			int sz_vtmp = SZ(vtmp);
			rep(ii, 0, sz_vtmp) ret.pb(vtmp[ii]);
			vtmp.clr();

			// #ifdef DEBUG
			// cout << "sz_vtmp = " << sz_vtmp << endl;
			// cout << "SZ(ret) = " << SZ(ret) << endl;
			// #endif
		}
	}

	/**
		\brief choose the best slice
	*/
	void chooseBstSlc(const slice_t& slice, const vi& bstSgrp, vi& ret) {
		const vector<slice_t>& vslc = sliceChromat[chrId];
		int sz = SZ(vslc), szsgp = SZ(bstSgrp);
		const int topk = layer_slice.topk;
		const int score_bound = layer_slice.score_bound;
		const int m = layer_sgroup.len / layer_slice.len;
		priority_queue<read_chr_t> Q;
		score_type score;
		int szQ;
		vi vtmp;

		ret.clr();
		rep(j, 0, szsgp) {
			szQ = 0;
			#ifdef DEBUG
			assert(SZ(Q) == szQ);
			#endif

			for (int i=bstSgrp[j],k=0; k<m&&i<sz; ++k,++i) {
				score = score_slice(vslc[i], slice);
				// #ifdef DEBUG
				// cout << "slice score = " << score << endl;
				// #endif
				if (score <= score_bound) {
					if (szQ < topk) {
						szQ++;
						Q.push(read_chr_t(vslc[i].idx, score));
					} else if (score < Q.top().score) {
						Q.pop();
						Q.push(read_chr_t(vslc[i].idx, score));
					}
				}
			}
			#ifdef DEBUG
			assert(SZ(Q) == szQ);
			#endif

		#ifdef TRAIN_DEBUG
			cout << "chooseBstSlice" << " ";
			cout << Q.top().score << " ";
		#endif
			while (!Q.empty()) {
				// #ifdef DEBUG
				// Q.top().print();
				// #endif
				vtmp.pb(Q.top().idx);
				// #ifdef TRAIN_DEBUG
				// cout << Q.top().score << " ";
				// #endif
				Q.pop();
			}
		// #ifdef TRAIN_DEBUG
		// 	cout << endl;
		// #endif

			sort(all(vtmp));
			int sz_vtmp = SZ(vtmp);
			rep(ii, 0, sz_vtmp) ret.pb(vtmp[ii]);
			vtmp.clr();
		}
	}

	/**
		\brief choose best readpair
	*/
	void chooseBstRead( const vi& bstSlcIdx, const acgt_t& acgt1, const acgt_t& acgt2, vector<readpair_chr_t>& vread) {
		const vector<acgt_t>& vacgt = acgtChromat[chrId];
		const int sz = SZ(vacgt);
		const int szslc = SZ(bstSlcIdx);
		const int read_len = layer_read.len;
		const int m = layer_slice.len / read_len;
		int lidx, lidx_, ridx, ridx_;
		score_type mn, mn_, tmp1, tmp2;
		
		vread.clr();
		rep(i, 0, szslc) {
			mn = mn_ = POS_INF;
			for (int j=bstSlcIdx[i]/read_len,k=0; k<m&&j<sz; ++j,++k) {
				tmp1 = score_acgt(vacgt[j], acgt1);
				#ifdef DEBUG
				if (j+2<sz)
				#else
				if (j+3<sz)
				#endif
				{
					// l x x r
					#ifdef DEBUG
					tmp2 = score_acgt(vacgt[j+2], acgt2);
					#else
					tmp2 = score_acgt(vacgt[j+3], acgt2);
					#endif
					if (tmp1+tmp2 < mn) {
						lidx_ = lidx;
						ridx_ = ridx;
						mn_ = mn;

						lidx = j;
						#ifdef DEBUG
						ridx = j + 2;
						#else
						ridx = j + 3;
						#endif
						mn = tmp1 + tmp2;
					} else if (tmp1+tmp2 < mn_) {
						mn_ = tmp1 + tmp2;
						lidx_ = j;
						#ifdef DEBUG
						ridx_ = j + 2;
						#else
						ridx_ = j + 3;
						#endif
					}
					// l x x x r
					if (j+4<sz) {
						tmp2 = score_acgt(vacgt[j+4], acgt2);
						if (tmp1+tmp2 < mn) {
							lidx_ = lidx;
							ridx_ = ridx;
							mn_ = mn;

							lidx = j;
							ridx = j + 4;
							mn = tmp1 + tmp2;
						} else if (tmp1+tmp2 < mn_) {
							mn_ = tmp1 + tmp2;
							lidx_ = j;
							ridx_ = j + 4;
						}
					}
				}
			}

			// #ifdef DEBUG
			// cout << "mn = " << mn << ", mn_ = " << mn_ << "." << endl;
			// #endif

			if (mn  < POS_INF) vread.pb(readpair_chr_t(lidx, ridx, mn));
			//if (mn_ < POS_INF) vread.pb(readpair_chr_t(lidx_, ridx_, mn_));

			#ifdef TRAIN_DEBUG
			if (mn < POS_INF)
				cout << "chooseBstRead" << " " << mn << endl;
			#endif
		}
	}

	/**
		\brief fuzzy match the read with assigned chromat
		\note store pair of (position, score) into vread
	*/
	void alignRead_chrId(const slice_t& slice, vi& ret) {
		/**
			\step 1 choose best group
		*/
		vi vbst, vbst_;
		
		chooseBstGrp(slice, vbst_);
		#ifdef DEBUG
		int sz_bstGroup = SZ(vbst_);
		#endif

		/**
			\step 2 choose best sub-group
		*/
		chooseBstSgrp(slice, vbst_, vbst);
		vbst_.clr();
		#ifdef DEBUG
		int sz_bstSgroup = SZ(vbst);
		#endif

		/**
			\step 3 choose best slice
		*/
		chooseBstSlc(slice, vbst, ret);
		vbst.clr();
		#ifdef DEBUG
		int sz_bstSlc = SZ(ret);

		static int cnt = 0;
		++cnt;
		if (cnt%5000 == 0)
			cout << "bstGrp = " << sz_bstGroup << ", bstSgrp = " << sz_bstSgroup << ", sz_bstSlc = " << sz_bstSlc << endl;
		#endif
	}
	
	/**
		\brief	exact align the read with chromat
	*/
	score_type alignExactRead(const int chrId, const int idx, const string& line) {
		const vector<sep_t>& vsep = sepChromat[chrId];
		const int szsep = SZ(vsep);
		const int m = layer_read.len / sep_len;
		int l = 0;
		score_type ret
;
		// restore the string
		{
			for (int i=0,j=idx*m; i<m&&j<szsep; ++i,++j) {
				restore_sep(vsep[j].leaf, buffer+l+sep_len-1);
				l += sep_len;
			}
			buffer[l++] = '\0';
		}

		// calculate the score using dp
		{
			const int mlen = min(l, (int)line.length());
			int dp[2][5];
			int p = 0, q = 1;

			memset(dp, 0, sizeof(dp));
			dp[0][2] = 0;
			dp[0][3] = -1;
			dp[0][4] = -2;
			rep(i, 1, l+1) {
				int bj = max(1, i-2);
				for (int j=bj; j<=i+2&&j<=mlen; ++j) {
					int k = j - i + 2;
					dp[q][k] = dp[p][k] + calcScore(buffer[i-1], line[j-1]);
					if (j <= i+1)
						dp[q][k] = max(dp[q][k], dp[p][k+1]-1);
					if (j > bj)
						dp[q][k] = max(dp[q][k], dp[q][k-1]-1);
				}
				p ^= 1;
				q ^= 1;
			}

			ret = dp[p][2];
			// #ifdef DEBUG
			// cout << buffer << endl;
			// cout << line << endl;
			// cout << ret << endl << endl;
			// #endif
		}

		return ret;
	}

	/**
		\brief exact match the read with assigned read
		\note assign the best position to idx1 & idx2
		\return score of exact match
	*/
	inline score_type alignExactRead(const read_t& can_read, const string& read1, const string& read2) {
		return alignExactRead(can_read.chrId, can_read.lidx, read1) + alignExactRead(can_read.chrId, can_read.ridx, read2);
	}

	/**
		\brief align the readpair
		\return best score
	*/
	score_type alignRead(const string& read1, const string& read2, info_t& info1, info_t& info2) {
		const int topk = layer_read.topk;
		const int score_bound = layer_read.score_bound;
		slice_t slice;
		acgt_t acgt1, acgt2;
		score_type ret = NEG_INF, tmp;
		vector<readpair_chr_t> vreadpair;
		priority_queue<read_t> Q;
		int szQ = 0;
	
		/**
			\step 0: init
		*/
		calcSlice(read1, read2, slice);
		calcACGT(read1, acgt1);
		calcACGT(read2, acgt2);
		
		/**
			\step 1: foreach format find the best read
		*/
		int sz_chrIds = SZ(chrIds);
		vi bstSlc;
			
		rep(i, 0, sz_chrIds) {
			chrId = chrIds[i];
			/**
				\step 2: find the best slice
			*/
			alignRead_chrId(slice, bstSlc);

			/**
				\step 3: find the best readpair
			*/
			chooseBstRead(bstSlc, acgt1, acgt2, vreadpair);

			int sz = SZ(vreadpair);
			rep(i, 0, sz) {
				if (vreadpair[i].score <= score_bound) {
					if (szQ < topk) {
						Q.push(read_t(chrId, vreadpair[i]));
						++szQ;
					} else if (vreadpair[i].score < Q.top().score) {
						Q.pop();
						Q.push(read_t(chrId, vreadpair[i]));
					}
				}
			}
			vreadpair.clr();
		}

		#ifdef DEBUG
		assert(SZ(Q) == szQ);
		// cout << "candidate exact align = " << szQ << endl;
		#endif

		int bstChrId;
		int bstIdx1, bstIdx2;
		read_t read;
		
		#ifdef LOCAL_DEBUG
		bstChrId = 0;
		#else
		bstChrId = 20;
		#endif
		bstIdx1 = bstIdx2 = 0;
		while (!Q.empty()) {
			read = Q.top();
			Q.pop();
			tmp = alignExactRead(read, read1, read2);
			// #ifdef DEBUG
			// cout << "alignExact = " << tmp << "." << endl;
			// #endif
			if (tmp > ret) {
				bstChrId = read.chrId;
				bstIdx1 = read.lidx;
				bstIdx2 = read.ridx;
				ret = tmp;
			}
		}

		const int m = layer_read.len / sep_len;
		#ifdef DEBUG
		assert(bstIdx1*m < SZ(sepChromat[bstChrId]));
		assert(bstIdx2*m < SZ(sepChromat[bstChrId]));
		#endif
		info1.id = bstChrId;
		info1.st = sepChromat[bstChrId][bstIdx1 * m].idx;
		info2.id = bstChrId;
		info2.st = sepChromat[bstChrId][bstIdx2 * m].idx;

		return ret;
	}
	
	/**
		\brief	align a pair of read
	*/
	score_type alignReadPair(const string& read1, const string& read2, info_t& info1, info_t& info2) {
		info_t info1_, info2_;

		#ifdef LOCAL_DEBUG
		info1.id = info2.id = 0;
		#else
		info1.id = info2.id = 20;
		#endif
		info1.st = info2.st = 0;
		info1_.st = info2_.st = 0;
		info1.strand = '+';
		info2.strand = '-';
		info1_.strand = '-';
		info2_.strand = '+';
		score_type score1 = alignRead(read1, getReverseComplement(read2), info1, info2);
		score_type score2 = alignRead(getReverseComplement(read1), read2, info1_, info2_);

		if (score1 < score2) {
			info1 = info1_;
			info2 = info2_;
		}
		info1.ed = info1.st + 149;
		info2.ed = info2.st + 149;
		info1.conf = info2.conf = 0.6;

		return max(score1, score2);
	}
	
	/**
		\brief	align all the read sequence
		\param	readName: name of the sequence, using as prefix of answer
	*/
	vector<string> getAlignment(int N, float normA, float normS, const vector<string>& readName, const vector<string>& readSequence) {
		vstr ret;
		info_t info1, info2;
		string line1, line2;
		score_type score = 0;
		#ifdef DEBUG
		int fail = 0;
		score_type tot = 0;
		#endif

		#ifdef DEBUG
		assert(N%2 == 0);
		#endif

		for(int i=0; i<N; i+=2) {
			//if (rand()%50 == 0) {
			score = alignReadPair(readSequence[i], readSequence[i+1], info1, info2);
			if (score > NEG_INF) {
				line1 = readName[i] + info1.toString();
				line2 = readName[i+1] + info2.toString();
			} else {
				line1 = getFailureResult(readName[i], '+');
				line2 = getFailureResult(readName[i+1], '-');
				#ifdef DEBUG
				++fail;
				#endif
			}
			//} else {
			//	line1 = getFailureResult(readName[i], '+');
			//	line2 = getFailureResult(readName[i+1], '-');
			//}
			ret.pb(line1);
			ret.pb(line2);
			#ifdef DEBUG
			tot += score;
			if (i>0 && i%1000==0) {
				cout << i << " finish, avg = " << setprecision(6) << tot/1000.0 << "\n";
				tot = 0;
			}
			#endif
		}

		#ifdef DEBUG
		cout << "fail = " << fail << endl;
		#endif

		return ret;
	}
};

//%-------------------------------------Cut from here-------------------------------------------

struct program_t{
	struct timespec real;
	struct timespec proc;
};

/**
	Constants from the problem statement
*/
const int MAX_DIF_DIST = 300;
const float NORM_A_SMALL = -3.392;
const float NORM_A_MEDIUM = -3.962;
const float NORM_A_LARGE = -2.710;
const float MAX_AUC = 0.999999;
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
float calcAccuarcy(const float norm_a, const int n, vector<Match_t>& vmatch) {
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
	float auc = 0.0;
	float invn = 1.0 / n;
	float invnp1 = 1.0 / (n + 1.0);
	float lgnp1 = 1.0 / log(n + 1.0);
	int m = SZ(cumul_si);
	rep(i, 0, m) {
		// float fi = (2 + pos[i] - cumul_si[i]);
		// float fip1 = (i==m-1) ? (n+1) : (2 + pos[i+1] - cumul_si[i+1]);
		float fi = (2+pos[i] - cumul_si[i]) * invnp1;
		float fip1 = (i==m-1) ? 1.0 : (2+pos[i+1] - cumul_si[i+1]) * invnp1;
		float lgfi = log(fi) * lgnp1;
		float lgfip1 = log(fip1) * lgnp1;
		auc += cumul_si[i] * (lgfip1 - lgfi) * invn;
	}

	printf("auc = %.4lf\n", auc);
	fprintf(logout, "auc = %.4lf\n", auc);

	return log(1.0 - min(auc, MAX_AUC)) / norm_a;
}

/**
	\brief calculate the `Speed` of the algorithm
*/
float calcSpeed(const float norm_s, const float Time, const float TimeCutOff) {
	return (1.0 - Time/TimeCutOff) / norm_s;
}

/**
	\brief calculate the `Score` of the algorithm
*/
float calcScore(const float testNorm, const float accuracy, const float speed) {
	return max(0.0f, testNorm * accuracy * speed);
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

void save_time(program_t& prog) {
	clock_gettime(CLOCK_REALTIME, &prog.real);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &prog.proc);
}

double calc_time(const program_t& st, const program_t& ed) {
	double ret;

	#ifdef USING_PROC_TIME
	double proc_st = st.proc.tv_sec + (float)st.proc.tv_nsec / 1e9;
	double proc_ed = ed.proc.tv_sec + (float)ed.proc.tv_nsec / 1e9;
	ret = proc_ed - proc_st;
	#else
	double real_st = st.real.tv_sec + (float)st.real.tv_nsec / 1e9;
	double real_ed = ed.real.tv_sec + (float)ed.real.tv_nsec / 1e9;
	ret = real_ed - real_st;
	#endif /* USING_PROC_TIME */

	return ret;
}

float norm_a;
float norm_s;
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
	cout << "initTest" <<endl;
	#endif
	dna.initTest(seed);

	/**
		\step 2: passReferenceGenome
	*/
	#ifdef DEBUG
	cout << "passReferenceGenome" <<endl;
	rep(ii, 0, SZ(chrId)) cout << chrId[ii] << " ";
	cout << endl;
	#endif
	rep(i, 0, SZ(chrId)) {
		const int id = chrId[i];
		string filename = "./example/chromatid" + to_string(id) + ".fa";
		vstr chromatidSeq = getChromat(filename);
		dna.passReferenceGenome(id, chromatidSeq);
		#ifdef DEBUG
		cout << id << " pass end" << endl;
		#endif
		chromatidSeq.clr();
	}

	/**
		\step 3: preProcessing
	*/
	#ifdef DEBUG
	cout << "preProcessing" <<endl;
	#endif
	dna.preProcessing();

	save_time(ed_prog);
	_prep_time = calc_time(st_prog, ed_prog);

	/**
		\step 4: getRead
	*/
	#ifdef DEBUG
	cout << "getRead" <<endl;
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
	cout <<"align"<<endl;
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
	cout <<"check result"<<endl;
	#endif
	flag = check_ans(ret, n, chrId, readNames);

	return ret;
}

void dumpAns(const int testDifficulty, const vstr& ans) {
	string filename;

	if (testDifficulty == 0)
		filename = "result_small.log";
	else if (testDifficulty == 1)
		filename = "result_medium.log";
	else
		filename = "result_large.log";
	ofstream fout(filename.c_str());

	if (!fout.is_open()) {
		fprintf(stderr, "%s can't open.\n", filename.c_str());
		abort();
	}

	int n = SZ(ans);
	rep(i, 0, n) fout << ans[i] << endl;

	fout.close();
}

void _test(int seed) {
	vi chrId;
	float testNorm;

	norm_s = 0.5;
	if (seed == 0) {
		#ifdef LOCAL_DEBUG
		minisam_path = "./example/test5.minisam";
		fa1_path = "./example/test5.fa1";
		fa2_path = "./example/test5.fa2";
		chrId.pb(0);
		#else
		minisam_path = "./example/small5.minisam";
		fa1_path = "./example/small5.fa1";
		fa2_path = "./example/small5.fa2";
		chrId.pb(20);
		#endif

		norm_a = NORM_A_SMALL;
		testNorm = 1000 / 1.05;
		prep_time = 201;
		cut_time = 16.1;

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
		minisam_path = "./example/large5.minisam";
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
	float score;

	if (!flag) {
		score = 0;
	} else {
		vector<Match_t> vmatch = calcMatch(ans, minisam_path);
		float accuracy = calcAccuarcy(norm_a, n, vmatch);
		float speed = calcSpeed(norm_s, _cut_time, cut_time*2);
		score = calcScore(testNorm, accuracy, speed);

		printf("accuracy = %.4lf\n", accuracy);
		printf("speed = %.4lf\n", speed);
		fprintf(logout, "accuracy = %.4lf\n", accuracy);
		fprintf(logout, "speed = %.4lf\n", speed);
	}

	printf("score = %.4lf\n", score);
	fprintf(logout, "score = %.4lf\n", score);

	dumpAns(seed, ans);
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

void init_log() {
	logout = fopen(LOGFILENAME, "w");
	if (!logout) {
		fprintf(stderr, "%s can not open.\n", LOGFILENAME);
		abort();
	}
}

void close_log() {
	fclose(logout);
}

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);

	#ifdef TRAIN_DEBUG
	freopen("data.out", "w", stdout);
	#endif

	int testcase = argc > 1 ? stoi(argv[1]) : 1;

	init_log();
	test(testcase);
	close_log();

	return 0;
}
