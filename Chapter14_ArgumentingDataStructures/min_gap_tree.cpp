#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define LOCAL_DEBUG
#define RED		true
#define BLACK	false
#define INF		9999999

typedef struct Node_t {
	bool color;
	int key, mmax, mmin;
	Node_t *p, *left, *right;
	Node_t() {}
	Node_t(int kkey) {
		key = kkey;
	}
} Node_t;

typedef struct Tree_t {
	Node_t *NIL;
	Node_t *root;
	Tree_t() {
		NIL = new Node_t();
		NIL->key = 0;
		NIL->mmax = -INF;
		NIL->mmin = INF;
		NIL->color = BLACK;
		NIL->p = NIL->left = NIL->right = NIL;
		root = NIL;
	}
} Tree_t;

Tree_t *t;

void Inorder_RBTree_Walk(Tree_t *t, Node_t *x) {
	if (x != t->NIL) {
		Inorder_RBTree_Walk(t, x->left);
		printf("key=%d, mmin=%d, mmax=%d\n", x->key, x->mmin, x->mmax);
		Inorder_RBTree_Walk(t, x->right);
	}
}

void Preorder_RBTree_Walk(Tree_t *t, Node_t *x) {
	if (x != t->NIL) {
		printf("key=%d, mmin=%d, mmax=%d\n", x->key, x->mmin, x->mmax);
		Preorder_RBTree_Walk(t, x->left);
		Preorder_RBTree_Walk(t, x->right);
	}
}

void Postorder_RBTree_Walk(Tree_t *t, Node_t *x) {
	if (x != t->NIL) {
		Postorder_RBTree_Walk(t, x->left);
		Postorder_RBTree_Walk(t, x->right);
		printf("key=%d, mmin=%d, mmax=%d\n", x->key, x->mmin, x->mmax);
	}
}

void Inorder_RBTree_Walk_WithColor(Tree_t *t, Node_t *x) {
	if (x != t->NIL) {
		Inorder_RBTree_Walk_WithColor(t, x->left);
		printf("%s: key=%d, mmin=%d, mmax=%d\n", x->color?"Red":"Black", x->key, x->mmin, x->mmax);
		Inorder_RBTree_Walk_WithColor(t, x->right);
	}
}

void Preorder_RBTree_Walk_WithColor(Tree_t *t, Node_t *x) {
	if (x != t->NIL) {
		printf("%s: key=%d, mmin=%d, mmax=%d\n", x->color?"Red":"Black", x->key, x->mmin, x->mmax);
		Preorder_RBTree_Walk_WithColor(t, x->left);
		Preorder_RBTree_Walk_WithColor(t, x->right);
	}
}

void Postorder_RBTree_Walk_WithColor(Tree_t *t, Node_t *x) {
	if (x != t->NIL) {
		Postorder_RBTree_Walk_WithColor(t, x->left);
		Postorder_RBTree_Walk_WithColor(t, x->right);
		printf("%s: key=%d, mmin=%d, mmax=%d\n", x->color?"Red":"Black", x->key, x->mmin, x->mmax);
	}
}

Node_t *RBTree_Minimum(Tree_t *t, Node_t *x) {
	while (x->left != t->NIL)
		x = x->left;
	return x;
}

Node_t *RBTree_Maximum(Tree_t *t, Node_t *x) {
	while (x->right != t->NIL)
		x = x->right;
	return x;
}

Node_t *RBTree_Search(Tree_t *t, int key) {
	Node_t *x = t->root;
	while (x!=t->NIL && x->key!=key) {
		if (key < x->key) {
			x = x->left;
		} else {
			x = x->right;
		}
	}
	return x;
}

void Left_Rotate(Tree_t *t, Node_t *x) {
	Node_t *y = x->right;
	x->right = y->left;
	if (y->left != t->NIL)
		y->left->p = x;
	y->p = x->p;
	if (x->p == t->NIL) {
		// x is root
		t->root = y;	
	} else if (x == x->p->left) {
		x->p->left = y;
	} else {
		x->p->right = y;
	}
	y->left = x;
	x->p = y;
	// maintenance attr mmax & mmin
	y->mmin = x->mmin;
	x->mmax = max(x->key, x->right->mmax);
}

void Right_Rotate(Tree_t *t, Node_t *y) {
	Node_t *x = y->left;
	y->left = x->right;
	if (x->right != t->NIL)
		x->right->p = y;
	x->p = y->p;
	if (y->p == t->NIL) {
		// y is root
		t->root = x;
	} else if (y == y->p->left) {
		y->p->left = x;
	} else {
		y->p->right = x;
	}
	x->right = y;
	y->p = x;
	// maintenance attr mmax & mmin
	x->mmax = y->mmax;
	y->mmin = min(y->key, y->left->mmin);
}

void RBTree_Transplant(Tree_t *t, Node_t *u, Node_t *v) {
	if (u->p == t->NIL) {
		t->root = v;
	} else if (u == u->p->left) {
		u->p->left = v;
	} else {
		u->p->right = v;
	}
	v->p = u->p;
}

void RBTree_Insert_Fixup(Tree_t *t, Node_t *z) {
	Node_t *y;
	
	while (z->p->color == RED) {
		// means z->p->p->color == BLACK
		if (z->p == z->p->p->left) {
			y = z->p->p->right;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			} else {
				// y->color is BLACK
				if (z == z->p->right) {
					z = z->p;
					Left_Rotate(t, z);
				}
				z->p->color = BLACK;	// break later
				z->p->p->color = RED;
				Right_Rotate(t, z->p->p);
			}
		} else {
			y = z->p->p->left;
			if (y->color == RED) {
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			} else {
				// y->color is BLACK
				if (z == z->p->left) {
					z = z->p;
					Right_Rotate(t, z);
				}
				z->p->color = BLACK;	// break later
				z->p->p->color = RED;
				Left_Rotate(t, z->p->p);
			}
		}
	}
	t->root->color = BLACK;
}

void RBTree_Insert(Tree_t *t, Node_t *z) {
	Node_t *y = t->NIL;
	Node_t *x = t->root;
	Node_t *q;
	
	while (x != t->NIL) {
		y = x;
		if (z->key < x->key) {
			x = x->left;
		} else {
			x = x->right;
		}
	}
	z->p = y;
	if (y == t->NIL) {
		// tree is empty
		t->root = z;
	} else if (z->key < y->key) {
		y->left = z;
	} else {
		y->right = z;
	}
	z->left = z->right = t->NIL;
	z->color = RED;
	// maintence the [mmax] of tree
	q = z;
	while (q != t->NIL) {
		q->mmax = max(q->right->mmax, q->key);
		q->mmin = min(q->left->mmin, q->key);
		q = q->p;
	}
	RBTree_Insert_Fixup(t, z);
}

void RBTree_Delete_Fixup(Tree_t *t, Node_t *x) {
	Node_t *w;
	
	while (x!=t->root && x->color==BLACK) {
		if (x == x->p->left) {
			w = x->p->right;
			if (w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				Left_Rotate(t, x->p);
				w = x->p->right;
			}
			// means w->color == BLACK
			if (w->left->color==BLACK && w->right->color==BLACK) {
				w->color = RED;
				x = x->p;	// fetch the black in w & x and pass it to x->p
			} else {
				if (w->right->color == BLACK) {
					// means w->left->color == RED
					w->left->color = BLACK;
					w->color = RED;
					Right_Rotate(t, w);
					w = x->p->right;
				}
				// means w->right->color == RED && w->left->color == uncertain
				w->color = x->p->color;
				x->p->color = BLACK;
				w->right->color = BLACK;
				Left_Rotate(t, x->p);
				x = t->root;
			}
		} else {
			w = x->p->left;
			if (w->color == RED) {
				w->color = BLACK;
				x->p->color = RED;
				Right_Rotate(t, x->p);
				w = x->p->left;
			}
			// means w->color == BLACK
			if (w->left->color==BLACK && w->right->color==BLACK) {
				w->color = RED;
				x = x->p; // fetch the black in w & x and pass it to x->p
			} else {
				if (w->left->color == BLACK) {
					// means x->right->color == RED
					w->right->color = BLACK;
					w->color = RED;
					Left_Rotate(t, w);
					w = x->p->left;
				}
				// means w->left->color == RED && w->right->color = ANY
				w->color = x->p->color;
				x->p->color = BLACK;
				w->left->color = BLACK;
				Right_Rotate(t, x->p);
				x = t->root;
			}
		}
	}
	x->color = BLACK;
}

void RBTree_Delete(Tree_t *t, Node_t *z) {
	Node_t *x, *y = z;
	Node_t *q;	// q used to back trace for maintening the [mmax] of Node_t
	bool y_original_color = y->color;
	
	if (z->left == t->NIL) {
		x = z->right;
		q = y->p;
		RBTree_Transplant(t, y, x);
	} else if (z->right == t->NIL) {
		x = z->left;
		RBTree_Transplant(t, y, x);
		q = y->p;
	} else {
		y = RBTree_Minimum(t, z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->p == z) {
			x->p = y;
			q = y;
		} else {
			RBTree_Transplant(t, y, x);
			q = y->p;
			y->right = z->right;
			y->right->p = y;
		}
		RBTree_Transplant(t, z, y);
		y->left = z->left;
		y->left->p = y;
		y->color = z->color;
	}
	
	// maintence the [size] of Node_t
	while (q != t->NIL) {
		q->mmax = max(q->right->mmax, q->key);
		q->mmin = min(q->left->mmin, q->key);
		q = q->p;
	}
	
	if (y_original_color == BLACK)
		RBTree_Delete_Fixup(t, x);	// use x replace y
}

int Min_Gap(Tree_t *t, Node_t *x) {
	if (x == t->NIL)
		return INF;
	int lgap = Min_Gap(t, x->left);
	int rgap = Min_Gap(t, x->right);
	int gap;
	if (x->right->mmin == INF)
		gap = x->key - x->left->mmax;
	else
		gap = min(
			x->key - x->left->mmax, x->right->mmin - x->key
		);
	int ret = min(
		min(lgap, rgap), gap
	);
	
	return ret;
}

int check_BHeight(Tree_t *t, Node_t *x, bool &f) {
	if (x == t->NIL)
		return 1;
	int lBH = check_BHeight(t, x->left, f);
	int rBH = check_BHeight(t, x->right, f);
	
	if (f == false)
		return 0;
	
	if (lBH != rBH)
		f = false;
	if (x->color == BLACK)
		return lBH+1;
	return lBH;
}

bool check_RNode(Tree_t *t, Node_t *x) {
	if (x == t->NIL)
		return true;
	if (x->color==RED && (x->left->color!=BLACK || x->right->color!=BLACK)) {
		return false;
	}
	return check_RNode(t, x->left) && check_RNode(t, x->right);
}

bool check_OthAttr(Tree_t *t, Node_t *x) {
	if (x == t->NIL)
		return x->mmax==-INF && x->mmin==INF;
	Node_t *p = RBTree_Minimum(t, x);
	Node_t *q = RBTree_Maximum(t, x);
	
	return p->key==x->mmin && q->key==x->mmax && check_OthAttr(t, x->left) && check_OthAttr(t, x->right);
}

bool check_RBTree(Tree_t *t) {
	bool ret;
	
	if (t->NIL->color != BLACK) {
		puts("NIL color is not black.");
		return false;
	}
	
	if (t->root == t->NIL)
		return true;
	
	if (t->root->color != BLACK) {
		puts("root color is not black.");
		return false;
	}
	
	if (check_RNode(t, t->root) == false) {
		puts("color attr is not right.");
		return false;
	}
	
	ret = true;
	check_BHeight(t, t->root, ret);
	if (ret == false) {
		puts("black height is not right.");
		return false;
	}
	
	if (check_OthAttr(t, t->root) == false) {
		puts("mmax/mmin attr is not right.");
		return false;
	}
	
	return true;
}

void init() {
	int i, j, k, tmp;
	int gap;
	Tree_t *t = new Tree_t();
	int a[] = {26, 17, 41, 14, 21, 30, 47, 10, 16, 19, 23, 28, 38, 7, 12, 15, 20, 35, 39, 3};
	int n = sizeof(a) / sizeof(int);
	Node_t *p;
	
	printf("n = %d\n", n);
	for (i=0; i<n; ++i) {
		p = new Node_t(a[i]);
		RBTree_Insert(t, p);
	}
	
	printf("\n\nInorder the tree with color:\n");
	Inorder_RBTree_Walk_WithColor(t, t->root);
	if (check_RBTree(t))
		puts("\nRight");
	else
		puts("\nWrong");
	printf("\n");
	
	gap = Min_Gap(t, t->root);
	sort(a, a+n);
	k = INF;
	for (i=1; i<n; ++i) {
		tmp = a[i] - a[i-1];
		k = min(tmp, k);
	}
	printf("gap = %d, Min_gap = %d\n", k, gap);
}

int cal_Gap(int *a, bool *visit, int n) {
	int b[30], m = 0;
	int i, j, k;
	
	for (i=0; i<n; ++i)
		if (!visit[i])
			b[m++] = a[i];
	
	sort(b, b+m);
	k = INF;
	for (i=1; i<m; ++i) {
		j = b[i] - b[i-1];
		k = min(j, k);
	}
	return k;
}

void check_delete() {
	int i, j, k, tmp;
	int gap;
	Tree_t *t = new Tree_t();
	int a[] = {26, 17, 41, 14, 21, 30, 47, 10, 16, 19, 23, 28, 38, 7, 12, 15, 20, 35, 39, 3};
	int n = sizeof(a) / sizeof(int);
	bool visit[30];
	Node_t *p;
	
	printf("n = %d\n", n);
	for (i=0; i<n; ++i) {
		p = new Node_t(a[i]);
		RBTree_Insert(t, p);
	}
	
	// Inorder_RBTree_Walk_WithColor(t, t->root);
	// puts("");
	
	memset(visit, false, sizeof(visit));
	for (i=1; i<n; ++i) {
		while (1) {
			j = rand()%n;
			if (!visit[j])
				break;
		}
		visit[j] = true;
		p = RBTree_Search(t, a[j]);	
		RBTree_Delete(t, p);
		// Inorder_RBTree_Walk_WithColor(t, t->root);
		if (check_RBTree(t))
			puts("Right");
		else
			puts("Wrong");
		gap = Min_Gap(t, t->root);
		k = cal_Gap(a, visit, n);
		printf("delete = %d, gap = %d, Min_gap = %d\n\n", a[j], k, gap);
	}
}

int main() {
	
	#ifdef LOCAL_DEBUG
		freopen("data.in", "r", stdin);
		freopen("data.out", "w", stdout);
	#endif
	
	// init();
	check_delete();
	
	return 0;
}
