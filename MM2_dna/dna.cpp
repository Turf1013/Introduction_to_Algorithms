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
	trie_ptr nxt[5];

	trie_t() {
		rep(i, 0, 5) nxt[i] = NULL;
	}
};

trie_ptr root_chr = NULL;
uint nleaf = 0;

struct feature_t {
	int c;
	int id;
	
	feature_t() {}
	feature_t(int c, int id):
		c(c), id(id) {}
		
	bool operator< (const node_t& oth) const {
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
};

typedef slice_t sgroup_t;
typedef slice_t group_t;

struct layer {
	uint feature_num;
	uint feature_ubound, feature_lbound;
	uint len;
	uint topk;
};

// hash
const char* acgtn_s = "acgtn";
const int max_hash_size = 1020;
const int max_sep_len = 12;
unsigned int hash_seed, hash_size;
uint hash_base[max_sep_len];

// global parameter
const float NEG_INF = -1e9;
const float POS_INF = 1e9;
char Complements[128];
int charId[128];
char buffer[1005];
const int max_ibuffer = 1e8;
int ibuffer[max_ibuffer];

// sep
layer layer_sep;
int sep_id[max_hash_size];
int all_id[max_hash_size];
uint sep_cnt[max_hash_size], sep_cnt_[max_hash_size];
char buffer[max_sep_len];

// slice
layer layer_slice;

// about sub-group
layer layer_sgroup;

// about group
layer layer_group;

vector<slice_t> sliceChromat[25];
vector<sgroup_t> sgroupChromat[25];
vector<group_t> groupChromat[25];
vector<sep_t> sepChromat;

inline int getCharId(char c) {
	return charId[c];
}

inline char getComplement(char c) {
	return Complements[c];
}

inline bool isACGT(char ch) {
	return ch=='A' || ch=='G' || ch=='C' || ch=='T';
}


inline string getRC(const string& line) {
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
	trie_ptr p = root_chr;

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

	return p;
}

void init_trie_chr() {
	if (root_chr)
		Delete_trie(root_chr, 0);
	root_chr = new trie_t();
}

void map_trie_chr(trie_ptr rt, int dep) {
	if (dep == sep_len) {
		int k = (char *)rt->nxt[1] - (char *)NULL;
		if (k == 0) rt->nxt[1] = (trie_ptr) (++nleaf);
		return ;
	}
	
	rep(i, 0, 5) if (rt->nxt[i]) map_trie_chr(rt->nxt[i], dep+1);
}

void clear_trie_chr() {
	/* do nothing */;
}

class DNASequencing {
public:
	int C[26];
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
		hash_seed = 31;
		hash_size = 1009;
		if (testDifficulty == 0) {
			sep_len = 10;
			slice_len = 10 * 15;
			sgroup_len = slice_len * 7;
			group_len = sgroup_len * 96;	
			
		} else if (testDifficulty == 1) {
			sep_len = 10;
			slice_len = 10 * 15;
			sgroup_len = slice_len * 7;
			group_len = sgroup_len * 96;	
			
		} else {
			abort();
		}

		hash_base[0] = 1;
		rep(i, 1, sep_len) hash_base[i] = hash_base[i-1] * hash_seed % hash_size;
		reverse(hash_base, hash_base+sep_len);
	}

	int initTest(int testDifficulty) {
		// init the parameter
		init_param(testDifficulty);

		// clear the chrIds
		chrIds.clr();

		// clear the feature & presents of chromatid
		rep(i, 1, 25) {
			sliceChromat[i].clr();
			sgroupChromat[i].clr();
			groupChromat[i].clr();
		}

		// init the trie
		init_trie_chr();

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
		int nline = SZ(chromatidSequence);
		int idx = 0, l = 0;
		sep_t sep;

		#ifdef DEBUG
		assert(sepChromat.size() == 0);
		#endif
		rep(k, 0, nline) {
			const string& line = chromatidSequence[k];
			const int len = line.length();

			rep(i, 0, len) {
				buffer[l++] = line[i];
				if (l == sep_len) {
					sep.leaf = Insert_chr(buffer);
					sep.idx = idx + i - sep_len + 1;
					sepChromat.pb(sep);
					l = 0;
				}
			}
			idx += len;
		}
	}
	
	/**
		\brief pile up the sep to slice, and then clear the sepChromat
	*/
	void pileChromat_slice() {
		const int chrId = *chrIds.rbegin();
		vector<slice_t>& vslc = sliceChromat[chrId];
		const int nsep = SZ(sepChromat);
		const int nfeature = layer_slice.feature_num;
		int bidx, szvf;
		vector<feature_t> vfeat;
		slice_t slice;
		int i = 0, j;
		
		while (i < nsep) {
			bidx = sepChromat[j=i].idx;
			szvf = 0;
			
			while (i<nsep && sepChromat[i].idx-bidx<=layer_slice.len) {
				const trie_ptr& leaf = sepChromat[i].leaf;
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
			assert(SZ(feat) == szvf);
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
				const int& k = vslc[i].id;
				if (ibuffer[k] < 0) {
					ibuffer[k] = szvf++;
					vfeat.pb(vslc[i]);
				} else {
					vfeat[ibuffer[k]] += vslc[i].c;
				}
			}
			
			#ifdef DEBUG
			assert(SZ(vfeat) = szvf);
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
			assett(SZ(bfeat) == szvf);
			#endif
			
			int szfeature = min(nfeature, szvf);
			sgroup.idx = bidx;
			rep(ii, 0, szfeature) {
				sgroup.pb(vfeat[ii]);
			}
			sgroup.sorted();
			vsgrp.pb(sgroup);
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
		group_t grp;
		int i = 0, j;
		
		while (i < nsgrp) {
			bidx = i;
			szvf = 0;
			
			for (j=0; j<m&&i<nsgrp; ++i,++j) {
				const int& k = vsgrp[i].id;
				if (ibuffer[k] < 0) {
					ibuffer[k] = szvf++;
					vfeat.pb(vsgrp[i]);
				} else {
					vfeat[ibuffer[k]] += vsgrp[i].c;
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
			group.clr();
			
			vfeat.clr();
		}
	}

	void pileChromat() {
		memset(ibuffer, -1, sizeof(ibuffer));
		
		/**
			\step 1: pile up layer 1 -- `slice`
		*/
		pileChromat_slice();
		
		/**
			\step 1.5: clear sepChromat to release memory
		*/
		sepChromat.clr();
		
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
		map_trie_chr();

		// pile up the lowest sep into layers.
		pileChromat();

		// release the memory of chr's trie
		clear_trie_chr();

		return 0;
	}

	/**
		\brief Generate a failure but format right answer
	*/
	inline string getFailureResult(const string& qname, const char strand='+') {
		#ifdef DEBUG
		return qname + ",20,1,150," + strand + ",0.0001";
		#else
		return qname + ",20,1,150," + strand + ",0.0001";
		#endif
	}

	inline void init_read(const string& s) {
		const int len = s.length();
		uint val = 0;

		rep(i, 0, sep_len) val = (val + s[i]*hash_base[i]) % hash_size;

		for (int i=0,j=sep_len; j<len; ++i,++j) {
			++sep_cnt[val];
			val = val + hash_size - s[i]*hash_base[0]%hash_size;
			val = (val * hash_seed + s[j]) % hash_size;
		}

		++sep_cnt[val];
	}

	void init_readPair(const string& l1, const string& l2) {
		memset(sep_cnt, 0, sizeof(sep_cnt));
		init_read(l1);
		init_read(l2);

		float tot = l1.length() + l2.length() - (sep_len << 1) + 2;

		rep(i, 0, hash_size) {
			sepFreq_read[i] = sep_cnt[i] / tot;
		}
	}

	void init_readSeq(const string& s, float *sepFreq_read) {
		memset(sep_cnt, 0, sizeof(sep_cnt));
		init_read(s);

		float tot = s.length() - sep_len + 1;

		rep(i, 0, hash_size) {
			sepFreq_read[i] = sep_cnt[i] / tot;
		}
	}

	vi chooseBestChrId(float &conf) {
		conf = 1.0;
		slice_t slice_read;
		vector<float>& freq_read = slice_read.freq;
		vector<pair<float,int> > vp;
		vi ret;

		freq_read.resize(SZ(allFeatureH));
		for (map<uint,int>::iterator iter=allFeatureH.begin(); iter!=allFeatureH.end(); ++iter) {
			#ifdef DEBUG
			assert(iter->sec < SZ(freq_read) && iter->sec>=0);
			#endif
			freq_read[iter->sec] = sep_cnt[iter->fir]>0 ? 1:0;
		}

		float slice_read_len = slice_read.length();
		for (int chrId : chrIds) {
			const slice_t& slice_chr = allFeature[chrId];
			float simi = similarity(slice_read, slice_read_len, slice_chr);
			vp.pb(mp(simi, chrId));
		}

		sort(all(vp), greater<pair<float,int> >());
		int mnsz = min(SZ(vp), topk_chr);

		rep(i, 0, mnsz) ret.pb(vp[i].sec);

		return ret;
	}

	vi chooseBestGrpIdx(const int chrId, float& conf) {
		conf = 1.0;
		group_t grp_read;
		vector<float>& freq_read = grp_read.freq;
		vector<pair<float,int> > vp;
		vi ret;

		freq_read.resize(SZ(chrFeatureH[chrId]));
		for (map<uint,int>::iterator iter=chrFeatureH[chrId].begin(); iter!=chrFeatureH[chrId].end(); ++iter) {
			freq_read[iter->sec] = sepFreq_read[iter->fir];
		}

		int sz_grp = SZ(groupChromat[chrId]);
		float grp_read_len = grp_read.length();

		rep(i, 0, sz_grp) {
			const group_t& grp_chr = groupChromat[chrId][i];
			float simi = similarity(grp_read, grp_read_len, grp_chr);
			if (simi > grp_simi_lbound) {
				vp.pb(mp(simi, grp_chr.idx));
			}
		}

		sort(all(vp), greater<pair<float,int> >());
		int mnsz = min(SZ(vp), topk_grp);

		rep(i, 0, mnsz) ret.pb(vp[i].sec);

		return ret;
	}

	float chooseBestSliceIdx(const int chrId, const vi& bstGrpIdx, int& st1, int& st2, float& conf_slice) {
		conf_slice = 1.0;
		st1 = st2 = 0;
		int szGrp = SZ(bstGrpIdx);
		if (szGrp == 0)	return NEG_INF;

		slice_t slc_read1, slc_read2;
		vector<float>& freq_read1 = slc_read1.freq;
		vector<float>& freq_read2 = slc_read2.freq;
		vector<pair<float,int> > vp;
		vi ret;

		freq_read1.resize(SZ(chrFeatureH[chrId]));
		freq_read2.resize(SZ(chrFeatureH[chrId]));
		for (map<uint,int>::iterator iter=chrFeatureH[chrId].begin(); iter!=chrFeatureH[chrId].end(); ++iter) {
			freq_read1[iter->sec] = sepFreq_read[iter->fir];
			freq_read2[iter->sec] = sepFreq_read_[iter->fir];
		}
		float slc_read1_len = slc_read1.length();
		float slc_read2_len = slc_read2.length();

		vector<slice_t>& vslc = sliceChromat[chrId];
		vector<slice_t>::iterator iter;
		slice_t slc;
		float mx1 = NEG_INF, mx2 = NEG_INF;
		float tmp;

		rep(gid, 0, szGrp) {
			const int& idx = bstGrpIdx[gid];
			slc.idx = idx;
			iter = lower_bound(all(vslc), slc);
			while (iter != vslc.end()) {
				if (iter->idx-idx > group_len)	break;
				tmp = similarity(slc_read1, slc_read1_len, *iter);
				if (tmp > mx1) {
					mx1 = tmp;
					st1 = iter->idx;
				}
				tmp = similarity(slc_read2, slc_read2_len, *iter);
				if (tmp > mx2) {
					mx2 = tmp;
					st2 = iter->idx;
				}
				++iter;
			}
		}

		return mx1 + mx2;
	}

	float alignRead(const string& read1, const string& read2, info_t& info1, info_t& info2) {
		// init the slice for readpair
		init_readPair(read1, read2);
		float bst_conf_grp = 1, bst_conf_slice = 1;
		float conf_chr, conf_grp, conf_slice;
		int bstId = 20;
		int &bst_st1 = info1.st, &bst_st2 = info2.st;
		int st1, st2;
		float ret = NEG_INF;

		/**
			\step 1: find the best match chrId
		*/
		vi bstChrIds = chooseBestChrId(conf_chr);

		/**
			\step 1.5: init the frequence slice of each read
		*/
		init_readSeq(read1, sepFreq_read);
		init_readSeq(read2, sepFreq_read_);
		for (int chrId : bstChrIds) {
			/**
				\step 2: choose the best group
			*/
			vi bstGrpIdx = chooseBestGrpIdx(chrId, conf_grp);
			/**
				\step 3: choose the best slice
			*/
			double tmp = chooseBestSliceIdx(chrId, bstGrpIdx, st1, st2, conf_slice);
			if (tmp > ret) {
				ret = tmp;
				bstId = chrId;
				bst_st1 = st1;
				bst_st2 = st2;
				bst_conf_grp = conf_grp;
				bst_conf_slice = conf_slice;
			}
		}

		/**
			\step 4: calculate the confidence
		*/
		float conf = conf_chr * bst_conf_grp * bst_conf_slice;

		conf = max(0.0f, conf);
		conf = min(1.0f, conf);
		info1.conf = info2.conf = conf;
		info1.id = info2.id = bstId;

		return ret;
	}

	float alignReadPair(const string& read1, const string& read2, info_t& info1, info_t& info2) {
		info_t info1_, info2_;

		info1.id = info2.id = 20;
		info1.st = info2.st = 0;
		info1_.st = info2_.st = 0;
		info1.strand = '+';
		info2.strand = '-';
		info1_.strand = '-';
		info2_.strand = '+';
		float score1 = alignRead(read1, getReverseComplement(read2), info1, info2);
		float score2 = alignRead(getReverseComplement(read1), read2, info1_, info2_);

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
			float score = alignReadPair(readSequence[i], readSequence[i+1], info1, info2);
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
			ret.pb(line1);
			ret.pb(line2);
			#ifdef DEBUG
			if (i>0 && i%100==0) {
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
