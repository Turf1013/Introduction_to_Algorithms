/**
	\author:	Trasier
	\date:		2017.10.28
*/
#ifndef SKY_XUAN_H
#define SKY_XUAN_H

const int ORDER_NUMBER = 5000;
const int MINI_BATCH = 5;
const int CAP = 128;
int perm_num;
int perm[200010][2 * MINI_BATCH];
int enum_perm[CAP / MINI_BATCH + 4];
int best_perm[CAP / MINI_BATCH + 4];

void optimal_sorting(position_t& pos, vector<int>& orderIds, vector<order_t>& orders, vector<position_t>& points) {
	int n = orderIds.size();
	for (int i=0; i<n; ++i)
		enum_perm[i] = i;

	int pid;
	double mnVal = inf, tmp, tid, orderId;
	position_t curPos = pos, nextPos;

	do {
		tmp = tid = 0.;
		for (int i=0; i<n; ++i) {
			orderId = orderIds[enum_perm[i]];
			order_t& order = orders[orderId];
			nextPos = points[order.eid];
			tid += Length(curPos, nextPos);
			curPos = nextPos;
			tmp += tid - order.tid;
		}
		if (tmp < mnVal) {
			mnVal = tmp;
			for (int i=0; i<n; ++i) {
				best_perm[i] = orderIds[enum_perm[i]];
			}
		}
	} while (next_permutation(enum_perm, enum_perm+n));

	for (int i=0; i<n; ++i) {
		enum_perm[i] = best_perm[i];
	}
}

void read_permutation(string fileName="permutations_5.in");
    FILE *fp = fopen(fileName.c_str(), "r");
    fscanf(fp, "%d", &perm_num);
    for (int i = 0; i < perm_num; ++ i) {
        for (int j = 0; j < 2 * MINI_BATCH; ++ j) {
            fscanf(fp, "%d", &perm[i][j]);
        }
    }
	fclose(fp);
}

#endif
