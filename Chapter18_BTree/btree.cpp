#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

#define INF		999999
#define MAXKN   10
#define BTREE_TN 2

typedef struct Node_t {
    int n;
    int key[MAXKN];
    bool leaf;
    Node_t *c[MAXKN+1];
} Node_t;

typedef struct {
    Node_t *root;
    int t;
} BTree_t;

int L = 0;
int b[1005], bn;

pair<Node_t *, int>BTree_Search(Node_t *x, int key) {
    int i = 1;
    while (i<=x->n && key>x->key[i])
        ++i;
    if (i<=x->n && key==x->key[i])
        return make_pair(x, i);
    else if (x->leaf)
        return make_pair((Node_t *)NULL, 0);
    else
        return BTree_Search(x->c[i], key);
}

void BTree_Create(BTree_t *t) {
    t->root = new Node_t();
    t->root->n = 0;
    t->root->leaf = true;
    t->t = BTREE_TN;
}

int BTree_Minimum(Node_t *x) {
    if (x->leaf)
        return x->key[1];
    else
        return BTree_Minimum(x->c[1]);
}

int BTree_Maximum(Node_t *x) {
    if (x->leaf)
        return x->key[x->n];
    else
        return BTree_Maximum(x->c[x->n+1]);
}

int BTree_Predecessor(Node_t *x, int i) {
    if (x->leaf) {
        if (i == 1)
            return -INF;
        else
            return x->key[i-1];
    } else {
        return BTree_Maximum(x->c[i]);
    }
}

int BTree_Successor(Node_t *x, int i) {
    if (x->leaf) {
        if (i == x->n)
            return INF;
        else
            return x->key[i+1];
    } else {
        return BTree_Minimum(x->c[i+1]);
    }
}

void BTree_Split_Child(Node_t *x, int i) {
    Node_t *z = new Node_t();
    Node_t *y = x->c[i];
    int j, k;
    int t = BTREE_TN;

    z->leaf = y->leaf;
    z->n = t-1;
    for (j=1; j<t; ++j)
        z->key[j] = y->key[t+j];
    if (!z->leaf) {
        for (j=1; j<=t; ++j)
            z->c[j] = y->c[t+j];
    }
    y->n = t-1;
    for (j=x->n+1; j>i; --j)
        x->key[j] = x->key[j-1];
    for (j=x->n+1; j>i; --j)
        x->c[j+1] = x->c[j];
    x->key[i] = y->key[t];
    x->c[i+1] = z;
    ++x->n;
}

void BTree_Insert_Nonfull(Node_t *x, int key) {
    int i = x->n;
    if (x->leaf) {
        while (i>=1 && x->key[i]>key) {
            x->key[i+1] = x->key[i];
            --i;
        }
        x->key[i+1] = key;
        ++x->n;
    } else {
        while (i>=1 && x->key[i]>key)
            --i;
        ++i;
        if (x->c[i]->n == 2*BTREE_TN-1) {
            BTree_Split_Child(x, i);
            if (key > x->key[i])
                ++i;
        }
        BTree_Insert_Nonfull(x->c[i], key);
    }
}

void BTree_Insert(BTree_t *T, int key) {
    Node_t *r = T->root;
    if (r->n == T->t*2-1) {
        Node_t *s = new Node_t();
        T->root = s;
        s->leaf = false;
        s->n = 0;
        s->c[1] = r;
        ++L;
        BTree_Split_Child(s, 1);
        BTree_Insert_Nonfull(s, key);
    } else {
        BTree_Insert_Nonfull(r, key);
    }
}

void BTree_Merge_Child(Node_t *x, int i) {
    // merge x->c[i] and x->c[i+1]
    int j, k;
    Node_t *y = x->c[i], *z = x->c[i+1];
    int yn = ++y->n, zn = z->n;

    // merge key[i] & z to y
    y->key[yn] = x->key[i];
    for (j=1; j<=zn; ++j)
        y->key[yn+j] = z->key[j];
    for (j=1; j<=zn+1; ++j)
        y->c[yn+j] = z->c[j];
    y->n += zn;

    // handle x
    --x->n;
    for (j=i; j<=x->n; ++j) {
        x->key[j] = x->key[j+1];
        x->c[j+1] = x->c[j+2];
    }
    delete(z);
}

void BTree_Delete(BTree_t *t, Node_t *x, int key) {
    int i = 1, j, k;
    Node_t *y, *z;

    while (i<=x->n && key>x->key[i])
        ++i;
    if (i<=x->n && key==x->key[i]) {
        if (x->leaf) {
            --x->n;
            while (i <= x->n) {
                x->key[i] = x->key[i+1];
                ++i;
            }
        } else {
            if (x->c[i]->n >= BTREE_TN) {
                // y is the predessor of x->c[]
                k = BTree_Predecessor(x, i);
                BTree_Delete(t, x->c[i], k);
                x->key[i] = k;
            } else if (i<=x->n && x->c[i+1]->n >= BTREE_TN) {
                k = BTree_Successor(x, i);
                BTree_Delete(t, x->c[i+1], k);
                x->key[i] = k;
            } else {
                BTree_Merge_Child(x, i);
                BTree_Delete(t, x->c[i], key);
            }
        }
    } else {
        if (x->c[i]->n == BTREE_TN-1) {
            y = x->c[i];
            if (i<=x->n && x->c[i+1]->n >= BTREE_TN) {
                z = x->c[i+1];
                // push x->key[i] to y
                ++y->n;
                y->key[y->n] = x->key[i];
                x->key[i] = z->key[1];
                y->c[y->n+1] = z->c[1];
                // adjust x->c[i+1]
                --z->n;
                for (j=1; j<=z->n; ++j)
                    z->key[j] = z->key[j+1];
                for (j=1; j<=z->n+1; ++j)
                    z->c[j] = z->c[j+1];
            } else if (i>1 && x->c[i-1]->n >= BTREE_TN) {
				z = x->c[i-1];
				// push x->key[i] to y
				++y->n;
				for (j=y->n; j>1; --j)
					y->key[j] = y->key[j-1];
				y->key[1] = x->key[i-1];
				x->key[i-1] = z->key[z->n];
				for (j=y->n+1; j>1; --j)
					y->c[j] = y->c[j-1];
				y->c[1] = z->c[z->n+1];
				// adjust x->c[i-1];
				--z->n;
            } else {
				if (i <= x->n) {
					BTree_Merge_Child(x, i);
				} else {
					--i;
					BTree_Merge_Child(x, i);
				}
				if (x==t->root && x->n==0)
					t->root = x->c[i];
            }
        }
        BTree_Delete(t, x->c[i], key);
    }
}

int BTree_Size(Node_t *x) {
    int i, ret = 1;

    if (x->leaf)
        return 1;
    for (i=1; i<=x->n+1; ++i)
        ret += BTree_Size(x->c[i]);
    return ret;
}

bool BTree_Check(BTree_t *t, Node_t *x) {
	int i, j, k;
	if (x!=t->root && (x->n+1<BTREE_TN || x->n+1>2*BTREE_TN))
		return false;
	if (!x->leaf) {
		for (i=1; i<=x->n; ++i) {
			BTree_Check(t, x->c[i]);
			b[bn++] = x->key[i];
		}
		BTree_Check(t, x->c[x->n+1]);
	} else {
		for (i=1; i<=x->n; ++i) {
			b[bn++] = x->key[i];
		}
	}
	return true;
}

void BTree_Print(BTree_t *t) {
	queue< pair<Node_t *,int> > Q;
	int i, j, k, d = 0;
	Node_t *x, *y;
	pair<Node_t *, int> nd;

	if (t->root->n==0) {
		puts("NULL BTree");
		return;
	}

	Q.push(make_pair(t->root, 0));
	while (!Q.empty()) {
		nd = Q.front();
		Q.pop();
		x = nd.first;
		k = nd.second;
		if (k != d) {
			putchar('\n');
			d = k;
		}
		putchar('[');
		putchar(' ');
		for (i=1; i<=x->n; ++i)
			printf("%d ", x->key[i]);// putchar(x->key[i]+'A');
		putchar(']');
		putchar('\t');
		if (!x->leaf) {
			for (i=1; i<=x->n+1; ++i)
				Q.push(make_pair(x->c[i], d+1));
		}
	}
	putchar('\n');
}

bool check_b() {
	int i;

	for (i=1; i<bn; ++i)
		if (b[i] < b[i-1])
			return false;
	return true;
}

void test_18_2_4() {
    BTree_t *t = new BTree_t();
    int i, j, k;
    int a[94];

    BTree_Create(t);
    for (i=1; i<=94; ++i) {
        BTree_Insert(t, i);
        L = BTree_Size(t->root);
        printf("%d: %d\n", i, L);
    }
}

void test_BTree() {
	BTree_t *t = new BTree_t();
	char str[] = "CNGAHEKQMFWLTZDPRXYS";
	int n = strlen(str);
	int i, j, k;

	BTree_Create(t);
	for(i=0; i<n; ++i) {
		BTree_Insert(t, str[i]-'A');
		printf("Insert %c:\n", str[i]);
		BTree_Print(t);
		bn = 0;
		if (BTree_Check(t, t->root) && check_b())
			puts("right");
		else
			puts("wrong");
		putchar('\n');
	}
}

void test_BTree_Delete() {
	BTree_t *t = new BTree_t();
	bool visit[1000];
	int n = 40;
	int a[40] = {41,467,334,500,169,724,478,358,962,464,705,145,281,827,961,491,995,942,436,391,604,902,153,292,382,421,716,718,895,447,726,771,538,869,912,667,299,35,894,703};
	int i, j, k;

	memset(visit, false, sizeof(visit));
	BTree_Create(t);
	for (j=0; j<n; ++j) {
		do {
			i = rand()%1000;
		} while (visit[i]);
		a[j] = i;
		visit[i] = true;
		BTree_Insert(t, a[j]);
	}
	BTree_Print(t);
	if (BTree_Check(t, t->root))
		puts("right");
	else
		puts("wrong");
	putchar('\n');
	// for (j=0; j<n; ++j)
		// printf("%d,", a[j]);
	k = n-1;
	memset(visit, false, sizeof(visit));
	while (k--) {
		do {
			i = rand()%n;
		} while (visit[i]);
		visit[i] = true;
		BTree_Delete(t, t->root, a[i]);
		printf("%d,Delete %d:\n", k, a[i]);
		BTree_Print(t);
		bn = 0;
		if (BTree_Check(t, t->root) && check_b())
			puts("right");
		else
			puts("wrong");
		putchar('\n');
		fflush(stdout);
	}
}

int main() {
    freopen("data.out", "w", stdout);

    // test_BTree();
	test_BTree_Delete();

    return 0;
}
