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
		return c > oth.c;
	}
};

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
		sort(all(feat), feat_compid);
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
typedef long long score_type;

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
	uint feature_ubound, feature_lbound;
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
const float NEG_INF = -1e9;
const float POS_INF = 1e9;
char Complements[128];
int charId[128];
char buffer[1024];
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

inline int calcScore(char a, char b) {
	return (a==b) ? 1:-1;
}

inline int getCharId(char c) {
	return charId[c];
}

inline char getComplement(char c) {
	return Complements[c];
}

inline bool isACGT(char ch) {
	return ch=='A' || ch=='G' || ch=='C' || ch=='T';
}


inline string getReverseComplement(const string& line) {
	int len = line.length();
	string ret;

	per(i, 0, len)	ret.pb(getComplement(line[i]));
	return ret;
}

void Delete_trie(trie_ptr rt, int dep) {
	if (dep == sep_len)	return ;
	rep(i, 0, 5) if (rt->nxt[i]) Delete_trie(rt->nxt[i], dep+1);
	delete rt;
}

trie_ptr Insert_chr(char *s) {
	int i = 0, id;
	trie_ptr p = trie_root;

	while (i < sep_len) {
		id = getCharId(s[i]);
		if (!p->nxt[id]) break;
		p = p->nxt[id];
		++i;
	}

	while(i < sep_len) {
		id = getCharId(s[i++]);
		p->nxt[id] = new trie_t(p);
		p = p->nxt[id];
	}

	return p;
}

int Insert_read(char *s) {
	int i = 0, id;
	trie_ptr p = trie_root;

	while (i < sep_len) {
		id = getCharId(s[i]);
		if (!p->nxt[id]) break;
		p = p->nxt[id];
		++i;
	}

	while(i < sep_len) {
		id = getCharId(s[i++]);
		p->nxt[id] = new trie_t(p);
		p = p->nxt[id];
	}
	id = (char *)p->nxt[1] - (char *)NULL;
	if (id == 0) {
		p->nxt[1] = (trie_ptr) (++nleaf);
		id = nleaf;
	}

	return id;
}

void init_trie_chr() {
	if (trie_root)
		Delete_trie(trie_root, 0);
	trie_root = new trie_t();
}

int mapc[5];
void map_trie_chr(trie_ptr rt, int dep) {
	if (dep == sep_len) {
		int k = (char *)rt->nxt[1] - (char *)NULL;
		if (k == 0) {
			rt->nxt[1] = (trie_ptr) (++nleaf);
			uint tmp = (mapc[3]<<24) | (mapc[2]<<16) | (mapc[1]<<8) | mapc[0];
			rt->nxt[0] = (trie_ptr) tmp;
		}
		return ;
	}

	rep(i, 0, 5) {
		if (rt->nxt[i]) {
			++mapc[i];
			map_trie_chr(rt->nxt[i], dep+1);
			--mapc[i];
		}
	}
}

void clear_trie_chr() {
	/* do nothing */;
}

/**
	\brief calculate the score between readpair and group
*/
score_type score_group(const group_t& a, const slice_t& b) {
	const vector<feature_t>& afeat = a.feat;
	const vector<feature_t>& bfeat = b.feat;
	const int sza = SZ(afeat);
	const int szb = SZ(bfeat);
	score_type ret = 0;

	int i = 0, j = 0;

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
	\brief calculate the score between readpair and sgroup
*/
score_type score_sgroup(const sgroup_t& a, const slice_t& b) {
	const vector<feature_t>& afeat = a.feat;
	const vector<feature_t>& bfeat = b.feat;
	const int sza = SZ(afeat);
	const int szb = SZ(bfeat);
	score_type ret = 0;

	int i = 0, j = 0;

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
	\brief calculate the score between readpair and slice
*/
score_type score_slice(const slice_t& a, const slice_t& b) {
	const vector<feature_t>& afeat = a.feat;
	const vector<feature_t>& bfeat = b.feat;
	const int sza = SZ(afeat);
	const int szb = SZ(bfeat);
	score_type ret = 0;

	int i = 0, j = 0;

	while (i<sza && j<szb) {
		if (afeat[i].id == bfeat[j].id) {
			ret += afeat[i].c>=bfeat[j].c ? 0:bfeat[j].c-afeat[i].c;
			++i;
			++j;
		} else if (afeat[i].id < bfeat[j].id) {
			ret += afeat[i].c >> 2;
			++i;
		} else {
			ret += bfeat[j].c;
			++j;
		}
	}
	while (j < szb) ret += bfeat[j++].c;
	while (i < sza) ret += afeat[i++].c >> 2;

	return ret;
}

/**
	\brief calculate the score between chromat-read and query-read
*/
score_type score_acgt(const acgt_t& a, const acgt_t& b) {
	score_type ret = 0;

	rep(i, 0, 4) {
		ret += abs(a.c[i] - b.c[i]) << 2;
	}

	return ret;
}

class DNASequencing {
public:
	vi chrIds;

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

	void init_param(const int testDifficulty) {

		if (testDifficulty == 0) {
			sep_len = 10;
			layer_read.len = 150;
			layer_slice.len = 1050;
			layer_sgroup.len = 10500;
			layer_group.len = 105000;

			layer_read.feature_num = 80;
			layer_slice.feature_num = 100;
			layer_sgroup.feature_num = 1000;
			layer_group.feature_num = 10000;

			layer_read.topk = 2400;
			layer_slice.topk = 2;
			layer_sgroup.topk = 30;
			layer_group.topk = 200;

			layer_read.feature_ubound = 80;
			layer_read.feature_lbound = 80;
			layer_slice.feature_ubound = 1050;
			layer_slice.feature_lbound = 100;
			layer_sgroup.feature_ubound = 10500;
			layer_sgroup.feature_lbound = 1000;
			layer_group.feature_ubound = 105000;
			layer_group.feature_lbound = 10000;

			layer_read.score_bound = 70;
			layer_slice.score_bound = 160;
			layer_sgroup.score_bound = 60;
			layer_group.score_bound = 40;


		} else if (testDifficulty == 1) {
			sep_len = 10;
			layer_read.len = 150;
			layer_slice.len = 1050;
			layer_sgroup.len = 10500;
			layer_group.len = 105000;

		} else {
			abort();
		}

	}

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
		init_trie_chr();

		// clear the ibuffer
		memset(ibuffer, -1, sizeof(ibuffer));

		return 0;
	}

	int preProcessing() {

		return 0;
	}

	/**
		\brief separate the chromat into sep, and store trie's leaf ptr into `SepChromat`
	*/
	void separateChromat(const vstr& chromatidSequence) {
		const int chrId = *chrIds.rbegin();
		vector<sep_t>& vsep = sepChromat[chrId];
		int nline = SZ(chromatidSequence);
		int idx = 0, l = 0;
		sep_t sep;

		#ifdef DEBUG
		assert(vsep.size() == 0);
		#endif
		rep(k, 0, nline) {
			const string& line = chromatidSequence[k];
			const int len = line.length();

			rep(i, 0, len) {
				buffer[l++] = line[i];
				if (l == sep_len) {
					sep.leaf = Insert_chr(buffer);
					sep.idx = idx + i - sep_len + 1;
					vsep.pb(sep);
					l = 0;
				}
			}
			idx += len;
		}
	}

	/**
		\brief pile up the sep to read
	*/
	void pileChromat_read() {
		const int chrId = *chrIds.rbegin();
		vector<sep_t>& vsep = sepChromat[chrId];
		vector<acgt_t>& vacgt = acgtChromat[chrId];
		const int nsep = SZ(vsep);
		const int m = layer_slice.len / layer_read.len;
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

			#ifdef DEBUG
			if (i>0 && i%2000==0)
				acgt.print();
			#endif
		}
	}

	/**
		\brief pile up the sep to slice
	*/
	void pileChromat_slice() {
		const int chrId = *chrIds.rbegin();
		vector<sep_t>& vsep = sepChromat[chrId];
		vector<slice_t>& vslc = sliceChromat[chrId];
		const int nsep = SZ(vsep);
		const int nfeature = layer_slice.feature_num;
		int bidx, szvf;
		vector<feature_t> vfeat;
		slice_t slice;
		int i = 0, j;

		while (i < nsep) {
			bidx = vsep[j=i].idx;
			szvf = 0;

			while (i<nsep && vsep[i].idx-bidx<=layer_slice.len) {
				const trie_ptr& leaf = vsep[i].leaf;
				int k = (char *)leaf->nxt[1] - (char*)NULL;
				#ifdef DEBUG
				assert(k > 0);
				#endif
				--k;
				if (ibuffer[k] < 0) {
					ibuffer[k] = szvf++;
					vfeat.pb(feature_t(1, k));
				} else {
					++vfeat[ibuffer[k]].c;
				}
				++i;
			}

			#ifdef DEBUG
			assert(SZ(vfeat) == szvf);
			#endif
			// resize vfeat according the bound of feature
			{
				int ii = 0, jj = 0;

				while (ii < szvf) {
					if (vfeat[ii].c>=layer_slice.feature_lbound && vfeat[ii].c<=layer_slice.feature_ubound)
						vfeat[jj++] = vfeat[ii];
					ibuffer[vfeat[ii].id] = -1;
					++ii;
				}

				szvf = jj;
				vfeat.resize(szvf);
			}
			sort(all(vfeat));
			#ifdef DEBUG
			assert(SZ(vfeat) == szvf);
			#endif

			int szfeature = min(nfeature, szvf);
			slice.idx = bidx;
			rep(ii, 0, szfeature) {
				slice.pb(vfeat[ii]);
			}
			slice.sorted();
			vslc.pb(slice);

			#ifdef DEBUG
			if (i>0 && i%2000 == 0)
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
		const int chrId = *chrIds.rbegin();
		vector<sgroup_t>& vsgrp = sgroupChromat[chrId];
		const vector<slice_t>& vslc = sliceChromat[chrId];
		const int m = layer_sgroup.len / layer_slice.len;
		const int nslice = SZ(vslc);
		const int nfeature = layer_sgroup.feature_num;
		int bidx, szvf;
		vector<feature_t> vfeat;
		sgroup_t sgroup;
		int i = 0, j;

		while (i < nslice) {
			bidx = i;
			szvf = 0;

			for (j=0; j<m&&i<nslice; ++i,++j) {
				const slice_t& slice = vslc[i];
				int sz_feat = SZ(slice);
				rep(ii, 0, sz_feat) {
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
					if (vfeat[ii].c>=layer_sgroup.feature_lbound && vfeat[ii].c<=layer_sgroup.feature_ubound)
						vfeat[jj++] = vfeat[ii];
					ibuffer[vfeat[ii].id] = -1;
					++ii;
				}

				szvf = jj;
				vfeat.resize(szvf);
			}

			#ifdef DEBUG
			assert(SZ(vfeat) == szvf);
			#endif

			int szfeature = min(nfeature, szvf);
			sgroup.idx = bidx;
			rep(ii, 0, szfeature) {
				sgroup.pb(vfeat[ii]);
			}
			sgroup.sorted();
			vsgrp.pb(sgroup);

			#ifdef DEBUG
			if (i>0 && i%2000 == 0)
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
		const int chrId = *chrIds.rbegin();
		vector<group_t>& vgrp = groupChromat[chrId];
		const vector<sgroup_t> vsgrp = sgroupChromat[chrId];
		const int m = layer_group.len / layer_sgroup.len;
		const int nsgrp = SZ(vsgrp);
		const int nfeature = layer_group.feature_num;
		int bidx, szvf;
		vector<feature_t> vfeat;
		group_t group;
		int i = 0, j;

		while (i < nsgrp) {
			bidx = i;
			szvf = 0;

			for (j=0; j<m&&i<nsgrp; ++i,++j) {
				const sgroup_t& sgrp = vsgrp[i];
				int sz_feat = SZ(sgrp);
				rep(ii, 0, sz_feat) {
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
					if (vfeat[ii].c>=layer_group.feature_lbound && vfeat[ii].c<=layer_group.feature_ubound)
						vfeat[jj++] = vfeat[ii];
					ibuffer[vfeat[ii].id] = -1;
					++ii;
				}

				szvf = jj;
				vfeat.resize(szvf);
			}
			#ifdef DEBUG
			assert(SZ(vfeat) == szvf);
			#endif

			int szfeature = min(nfeature, szvf);
			group.idx = bidx;
			rep(ii, 0, szfeature) {
				group.pb(vfeat[ii]);
			}
			group.sorted();
			vgrp.pb(group);

			#ifdef DEBUG
			if (i>0 && i%2000 == 0)
				group.print();
			#endif
			group.clr();
			vfeat.clr();
		}
	}

	/**
		\brief pile up the chromat to form 3 layers:
			`group`、`sgroup`、`slice`
	*/
	void pileChromat() {
		/**
			\step 0: pile up the layer 0 -- read
		*/
		pileChromat_read();

		/**
			\step 1: pile up layer 1 -- `slice`
		*/
		pileChromat_slice();

		// /**
			// \step 1.5: clear sepChromat to release memory
		// */
		// sepChromat.clr();

		/**
			\step 2: pile up layer 2 -- `sgroup`
		*/
		pileChromat_sgroup();

		/**
			\step 3: pile up layer 3 -- `group`
		*/
		pileChromat_group();
	}

	int passReferenceGenome(int chromatidSequenceId, const vector<string>& chromatidSequence) {
		// push chrId into chrIds
		chrIds.pb(chromatidSequenceId);

		// split the chromat into sep.
		separateChromat(chromatidSequence);

		// mapping the leaf with integer
		memset(mapc, 0, sizeof(mapc));
		map_trie_chr(trie_root, 0);

		// pile up the lowest sep into layers.
		pileChromat();

		// release the memory of chr's trie
		clear_trie_chr();

		return 0;
	}

	/**
		\brief Generate a failure but format right answer
	*/
	inline string getFailureResult(const string& qname, const char strand='+') const {
		#ifdef DEBUG
		return qname + ",20,1,150," + strand + ",0.0001";
		#else
		return qname + ",20,1,150," + strand + ",0.0001";
		#endif
	}

	acgt_t calcACGT(const string& s) {
		const int len = s.length();
		int c[5];

		memset(c, 0, sizeof(c));
		rep(i, 0, len) ++c[getCharId(s[i])];

		return acgt_t(c[0], c[1], c[2], c[3]);
	}

	acgt_t calcACGT(const string& s1, const string& s2) {
		int len;
		int c[5];

		memset(c, 0, sizeof(c));

		len = s1.length();
		rep(i, 0, len) ++c[getCharId(s1[i])];
		len = s2.length();
		rep(i, 0, len) ++c[getCharId(s2[i])];

		return acgt_t(c[0], c[1], c[2], c[3]);
	}

	slice_t calcSlice(const string& s, const int idx=0) {
		int len = s.length();
		int szvf = 0;
		slice_t ret;
		vector<feature_t>& vfeat = ret.feat;

		strncpy(buffer, s.c_str(), len);
		len = len - sep_len + 1;

		rep(i, 0, len) {
			const int k = Insert_read(buffer + i);
			if (ibuffer[k] < 0) {
				ibuffer[k] = szvf++;
				vfeat.pb(feature_t(1, k));
			} else {
				++vfeat[ibuffer[k]].c;
			}
		}

		#ifdef DEBUG
		assert(SZ(vfeat) == szvf);
		#endif
		rep(i, 0, szvf) ibuffer[vfeat[i].id] = -1;
		ret.idx = idx;
		ret.sorted();

		return ret;
	}

	slice_t calcSlice(const string& l1, const string& l2) {
		int len;
		int szvf;
		slice_t ret;
		vector<feature_t>& vfeat = ret.feat;

		// handle first string
		len = l1.length();
		szvf = 0;
		strncpy(buffer, l1.c_str(), len);
		len = len - sep_len + 1;
		rep(i, 0, len) {
			const int k = Insert_read(buffer + i);
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
		len = len - sep_len + 1;
		rep(i, 0, len) {
			const int k = Insert_read(buffer + i);
			if (ibuffer[k] < 0) {
				ibuffer[k] = szvf++;
				vfeat.pb(feature_t(1, k));
			} else {
				++vfeat[ibuffer[k]].c;
			}
		}

		#ifdef DEBUG
		assert(SZ(vfeat) == szvf);
		#endif
		rep(i, 0, szvf) ibuffer[vfeat[i].id] = -1;
		ret.sorted();

		return ret;
	}

	/**
		\brief choose the best group
	*/
	vi chooseBstGrp(const int chrId, const slice_t& slice) {
		const vector<group_t>& vgrp = groupChromat[chrId];
		int sz = SZ(vgrp);
		const int topk = layer_group.topk;
		const int score_bound = layer_group.score_bound;
		priority_queue<read_chr_t> Q;
		score_type score;
		int szQ = 0;

		rep(i, 0, sz) {
			score = score_group(vgrp[i], slice);
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
		vi ret;

		while (!Q.empty()) {
			#ifdef DEBUG
			Q.top().print();
			#endif
			ret.pb(Q.top().idx);
			Q.pop();
		}
		sort(all(ret));

		return ret;
	}

	/**
		\brief choose the best sub-group
	*/
	vi chooseBstSgrp(const int chrId, const slice_t& slice, const vi& bstGrp) {
		const vector<sgroup_t>& vsgrp = sgroupChromat[chrId];
		int sz = SZ(vsgrp), szgp = SZ(bstGrp);
		const int topk = layer_sgroup.topk;
		const int score_bound = layer_sgroup.score_bound;
		const int m = layer_group.len / layer_sgroup.len;
		priority_queue<read_chr_t> Q;
		score_type score;
		int szQ = 0;

		rep(j, 0, szgp) {
			for (int i=bstGrp[j],k=0; k<m&&i<sz; ++k,++i) {
				score = score_sgroup(vsgrp[i], slice);
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
		}

		#ifdef DEBUG
		assert(SZ(Q) == szQ);
		#endif
		vi ret;

		while (!Q.empty()) {
			#ifdef DEBUG
			Q.top().print();
			#endif
			ret.pb(Q.top().idx);
			Q.pop();
		}
		sort(all(ret));

		return ret;
	}

	/**
		\brief choose the best slice
	*/
	vi chooseBstSlc(const int chrId, const slice_t& slice, const vi& bstSgrp) {
		const vector<slice_t>& vslc = sliceChromat[chrId];
		int sz = SZ(vslc), szsgp = SZ(bstSgrp);
		const int topk = layer_slice.topk;
		const int score_bound = layer_slice.score_bound;
		const int m = layer_sgroup.len / layer_slice.len;
		priority_queue<read_chr_t> Q;
		score_type score;
		int szQ = 0;

		rep(j, 0, szsgp) {
			for (int i=bstSgrp[j],k=0; k<m&&i<sz; ++k,++i) {
				score = score_slice(vslc[i], slice);
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
		}

		#ifdef DEBUG
		assert(SZ(Q) == szQ);
		#endif
		vi ret;

		while (!Q.empty()) {
			#ifdef DEBUG
			Q.top().print();
			#endif
			ret.pb(Q.top().idx);
			Q.pop();
		}
		sort(all(ret));

		return ret;
	}

	/**
		\brief choose best readpair
	*/
	void chooseBstRead(const int chrId, const vi& bstSlcIdx, const acgt_t& acgt1, const acgt_t& acgt2, vector<readpair_chr_t>& vread) {
		// just random choose is fine
		const vector<acgt_t>& vacgt = acgtChromat[chrId];
		const int sz = SZ(vacgt);
		const int szslc = SZ(bstSlcIdx);
		const int m = layer_slice.len / layer_read.len;
		int lidx, lidx_, ridx, ridx_;
		score_type mn, mn_, tmp1, tmp2;

		rep(i, 0, szslc) {
			mn = mn_ = INF;
			for (int j=bstSlcIdx[i]/m,k=0; k<m&&j<sz; ++j,++k) {
				tmp1 = score_acgt(vacgt[j], acgt1);
				if (k+3<m && j+3<sz) {
					// l x x r
					tmp2 = score_acgt(vacgt[j+3], acgt2);
					if (tmp1+tmp2 < mn) {
						lidx_ = lidx;
						ridx_ = ridx;
						mn_ = mn;

						lidx = j;
						ridx = j + 3;
						mn = tmp1 + tmp2;
					} else if (tmp1+tmp2 < mn_) {
						mn_ = tmp1 + tmp2;
						lidx_ = j;
						ridx_ = j + 3;
					}
					// l x x x r
					if (k+4<m && j+4<sz) {
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
		}

		#ifdef DEBUG
		cout << "mn = " << mn << ", mn_ = " << mn_ << "." << endl;
		#endif

		if (mn  < INF) vread.pb(readpair_chr_t(lidx, ridx, mn));
		if (mn_ < INF) vread.pb(readpair_chr_t(lidx_, ridx_, mn_));
	}

	/**
		\brief fuzzy match the read with assigned chromat
		\note store pair of (position, score) into vread
	*/
	vi alignRead_chrId(const int chrId, const slice_t& slice) {
		/**
			\step 1 choose best group
		*/
		vi bstGroup = chooseBstGrp(chrId, slice);

		/**
			\step 2 choose best sub-group
		*/
		vi bstSgroup = chooseBstSgrp(chrId, slice, bstGroup);
		bstGroup.clr();

		/**
			\step 3 choose best slice
		*/
		vi bstSlc = chooseBstSlc(chrId, slice, bstSgroup);
		return bstSlc;
	}

	score_type alignExactRead(const int chrId, const int idx, const string& line) {
		const vector<sep_t>& vsep = sepChromat[chrId];
		const int szsep = SZ(vsep);
		const int m = layer_read.len / sep_len;
		int l = 0;
		score_type ret;

		// restore the string
		{
			for (int i=0,j=idx; i<m&&j<szsep; ++i,++j) {
				trie_ptr p = vsep[j].leaf, q;

				#ifdef DEBUG
				bool flag = false;
				#endif
				while (p->fa != NULL) {
					q = p->fa;
					rep(k, 0, 5) {
						if (q->nxt[k] == p) {
							#ifdef DEBUG
							flag = true;
							#endif
							buffer[l++] = acgt_s[k];
							break;
						}
					}
					p = q;
				}
				#ifdef DEBUG
				assert(flag);
				#endif
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
				for (int j=bj; j<=mlen&&j<=i+2; ++j) {
					int k = j - i + 2;
					dp[q][k] = dp[p][k] + calcScore(buffer[l-1], line[j-1]);
					if (j <= i+1)
						dp[q][k] = max(dp[q][k], dp[p][k+1]-1);
					if (j > bj)
						dp[q][k] = max(dp[q][k], dp[q][k-1]-1);
				}
				p ^= 1;
				q ^= 1;
			}

			ret = dp[p][2];
		}

		return ret;
	}

	/**
		\breif exact match the read with assigned read
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
		const slice_t slice = calcSlice(read1, read2);
		const acgt_t acgt1 = calcACGT(read1);
		const acgt_t acgt2 = calcACGT(read2);
		score_type ret = NEG_INF, tmp;
		vector<readpair_chr_t> vreadpair;
		priority_queue<read_t> Q;
		int szQ = 0;

		/**
			\step 1: foreach format find the best read
		*/
		for (int chrId : chrIds) {
			/**
				\step 2: find the best slice
			*/
			vi bstSlc = alignRead_chrId(chrId, slice);
			/**
				\step 3: find the best readpair
			*/
			chooseBstRead(chrId, bstSlc, acgt1, acgt2, vreadpair);

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
		assert(SZ(Q) <= topk);
		assert(SZ(Q) == szQ);
		#endif

		int bstChrId;
		int bstIdx1, bstIdx2;

		bstChrId = 20;
		bstIdx1 = bstIdx2 = 0;
		while (!Q.empty()) {
			read_t read = Q.top();
			Q.pop();
			tmp = alignExactRead(read, read1, read2);
			#ifdef DEBUG
			cout << "alignExact = " << tmp << "." << endl;
			#endif
			if (tmp > ret) {
				bstChrId = read.chrId;
				bstIdx1 = read.lidx;
				bstIdx2 = read.ridx;
				ret = tmp;
			}
		}
		info1.id = bstChrId;
		info1.st = bstIdx1;
		info2.id = bstChrId;
		info2.st = bstIdx2;

		return ret;
	}

	score_type alignReadPair(const string& read1, const string& read2, info_t& info1, info_t& info2) {
		info_t info1_, info2_;

		info1.id = info2.id = 20;
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
		info1.ed = info1.st + 149.;
		info2.ed = info2.st + 149.;
		info1.conf = info2.conf = 0.6;

		return max(score1, score2);
	}

	vector<string> getAlignment(int N, float normA, float normS, const vector<string>& readName, const vector<string>& readSequence) {
		vstr ret;
		info_t info1, info2;
		string line1, line2;
		#ifdef DEBUG
		int fail = 0;
		double tot = 0.0;
		#endif

		#ifdef DEBUG
		assert(N%2 == 0);
		#endif

		for(int i=0; i<N; i+=2) {
			score_type score = alignReadPair(readSequence[i], readSequence[i+1], info1, info2);
			if (score < POS_INF) {
				line1 = readName[i] + info1.toString();
				line2 = readName[i+1] + info2.toString();
			} else {
				line1 = getFailureResult(readName[i], '+');
				line2 = getFailureResult(readName[i+1], '-');
				#ifdef DEBUG
				++fail;
				#endif
			}
			ret.pb(line1);
			ret.pb(line2);
			#ifdef DEBUG
			if (i>0 && i%1000==0) {
				printf("%d finish, avg = %.12lf\n", i, tot/100);
				tot = 0;
			}
			tot += score;
			#endif
		}

		#ifdef DEBUG
		printf("fail = %d\n", fail);
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
		#ifdef DEBUG
		minisam_path = "./example/test5.minisam";
		fa1_path = "./example/test5.fa1";
		fa2_path = "./example/test5.fa2";
		#else
		minisam_path = "./example/small5.minisam";
		fa1_path = "./example/small5.fa1";
		fa2_path = "./example/small5.fa2";
		#endif

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
	int testcase = argc > 1 ? stoi(argv[1]) : 1;

	init_log();
	test(testcase);
	close_log();

	return 0;
}
