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

typedef struct interval_t {
	int low, high;
	interval_t() {}
	interval_t(int l, int h) {
		low = l; high = h;
	}
	friend bool operator ==(const interval_t &a, const interval_t &b) {
		return a.low==b.low && a.high==b.high;
	}
} interval_t;

typedef struct Node_t {
	bool color;
	int key, mmax;
	interval_t intr;
	Node_t *p, *left, *right;
	Node_t() {}
	Node_t(interval_t iintr) {
		intr = iintr;
		key = iintr.low;
	}
} Node_t;

typedef struct Tree_t {
	Node_t *NIL;
	Node_t *root;
	Tree_t() {
		NIL = new Node_t();
		NIL->key = 0;
		NIL->mmax = -INF;
		NIL->color = BLACK;
		NIL->p = NIL->left = NIL->right = NIL;
		root = NIL;
	}
} Tree_t;

Tree_t *t;

void Inorder_RBTree_Walk(Tree_t *t, Node_t *x) {
	if (x != t->NIL) {
		Inorder_RBTree_Walk(t, x->left);
		printf("[%d, %d] | %d\n", x->intr.low, x->intr.high, x->mmax);
		Inorder_RBTree_Walk(t, x->right);
	}
}

void Preorder_RBTree_Walk(Tree_t *t, Node_t *x) {
	if (x != t->NIL) {
		printf("[%d, %d] | %d\n", x->intr.low, x->intr.high, x->mmax);
		Preorder_RBTree_Walk(t, x->left);
		Preorder_RBTree_Walk(t, x->right);
	}
}

void Postorder_RBTree_Walk(Tree_t *t, Node_t *x) {
	if (x != t->NIL) {
		Postorder_RBTree_Walk(t, x->left);
		Postorder_RBTree_Walk(t, x->right);
		printf("[%d, %d] | %d\n", x->intr.low, x->intr.high, x->mmax);
	}
}

void Inorder_RBTree_Walk_WithColor(Tree_t *t, Node_t *x) {
	if (x != t->NIL) {
		Inorder_RBTree_Walk_WithColor(t, x->left);
		printf("%s: [%d, %d] | %d\n", x->color?"Red":"Black", x->intr.low, x->intr.high, x->mmax);
		Inorder_RBTree_Walk_WithColor(t, x->right);
	}
}

void Preorder_RBTree_Walk_WithColor(Tree_t *t, Node_t *x) {
	if (x != t->NIL) {
		printf("%s: [%d, %d] | %d\n", x->color?"Red":"Black", x->intr.low, x->intr.high, x->mmax);
		Preorder_RBTree_Walk_WithColor(t, x->left);
		Preorder_RBTree_Walk_WithColor(t, x->right);
	}
}

void Postorder_RBTree_Walk_WithColor(Tree_t *t, Node_t *x) {
	if (x != t->NIL) {
		Postorder_RBTree_Walk_WithColor(t, x->left);
		Postorder_RBTree_Walk_WithColor(t, x->right);
		printf("%s: [%d, %d] | %d\n", x->color?"Red":"Black", x->intr.low, x->intr.high, x->mmax);
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

bool overlap(interval_t a, interval_t b) {
	return b.low<=a.high && a.low<=b.high;
}

Node_t *RBTree_Search(Tree_t *t, interval_t intr) {
	Node_t *x = t->root;
	while (x!=t->NIL && !overlap(intr, x->intr)) {
		if (x->left!=t->NIL && x->left->mmax>=intr.low) {
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
	// maintenance attr mmax
	x->mmax = max(
		max(x->left->mmax, x->right->mmax), x->intr.high
	);
	y->mmax = max(
		max(y->left->mmax, y->right->mmax), y->intr.high
	);
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
	// maintenance attr mmax
	y->mmax = max(
		max(y->left->mmax, y->right->mmax), y->intr.high
	);
	x->mmax = max(
		max(x->left->mmax, x->right->mmax), x->intr.high
	);
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
		q->mmax = max(
			max(q->left->mmax, q->right->mmax), q->intr.high
		);
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
		q->mmax = max(
			max(q->left->mmax, q->right->mmax), q->intr.high
		);
		q = q->p;
	}
	
	if (y_original_color == BLACK)
		RBTree_Delete_Fixup(t, x);	// use x replace y
}

Node_t *RBTree_Search_Min(Tree_t *t, Node_t *z, interval_t intr) {
	Node_t *x;	
	
	if (z == t->NIL)
		return t->NIL;
	
	if (z->left!=t->NIL && z->left->mmax>=intr.low) {
		x = RBTree_Search_Min(t, z->left, intr);
		if (x != t->NIL)
			return x;
	}
	
	if (overlap(intr, z->intr))
		return z;
	
	if (z->right != t->NIL)
		return RBTree_Search_Min(t, z->right, intr);
	
	return t->NIL;
}

void RBTree_Search_All(Tree_t *t, Node_t *z, interval_t intr) {
	Node_t *x;
	
	if (z == t->NIL)
		return ;
	
	if (z->left!=t->NIL && z->left->mmax>=intr.low) {
		RBTree_Search_All(t, z->left, intr);
	}
	
	if (overlap(intr, z->intr)) {
		printf("[%d, %d]\n", z->intr.low, z->intr.high);
	}
	
	if (z->right!=t->NIL && z->right->mmax>=intr.low) {
		RBTree_Search_All(t, z->right, intr);
	}
}

Node_t *RBTree_Seach_Exactly(Tree_t *t, interval_t intr) {
	Node_t *x = t->root;
	
	while (x != t->NIL) {
		if (overlap(intr, x->intr)) {
			if (intr == x->intr)
				break;
			if (x->left!=t->NIL && intr.low<x->key)
				x = x->left;
			else
				x = x->right;
		} else {
			if (x->left!=t->NIL && x->left->mmax>=intr.low)
				x = x->left;
			else
				x = x->right;
		}
	}
	return x;
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
		return x->mmax == -INF;
	if (x->intr.high>x->mmax || x->left->mmax>x->mmax || x->right->mmax>x->mmax) {
		return false;
	}
	return check_OthAttr(t, x->left) && check_OthAttr(t, x->right);
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
		puts("mmax attr is not right.");
		return false;
	}
	
	return true;
}

void init() {
	int i, j, k;
	Tree_t *t = new Tree_t();
	interval_t intrs[10] = {
		interval_t(16, 21),
		interval_t(8 , 9 ),
		interval_t(25, 30),
		interval_t(5 , 8 ),
		interval_t(15, 23),
		interval_t(17, 19),
		interval_t(26, 26),
		interval_t(0 , 3 ),
		interval_t(6 , 10),
		interval_t(19, 20)
	};
	int n = sizeof(intrs) / sizeof(interval_t);
	Node_t *p;
	
	printf("n = %d\n", n);
	for (i=0; i<n; ++i) {
		p = new Node_t(intrs[i]);
		printf("key=%d, intr=[%d, %d]\n", p->key, p->intr.low, p->intr.high);
		RBTree_Insert(t, p);
	}
	
	printf("\n\nInorder the tree with color:\n");
	Inorder_RBTree_Walk_WithColor(t, t->root);
	if (check_RBTree(t))
		puts("\nRight");
	else
		puts("\nWrong");
	printf("\n");
}

void check_delete() {
	int i, j, k;
	Tree_t *t = new Tree_t();
	interval_t intrs[10] = {
		interval_t(16, 21),
		interval_t(8 , 9 ),
		interval_t(25, 30),
		interval_t(5 , 8 ),
		interval_t(15, 23),
		interval_t(17, 19),
		interval_t(26, 26),
		interval_t(0 , 3 ),
		interval_t(6 , 10),
		interval_t(19, 20)
	};
	Node_t *nds[10];
	bool visit[10];
	int n = sizeof(intrs) / sizeof(interval_t);
	Node_t *p;
	
	printf("n = %d\n", n);
	for (i=0; i<n; ++i) {
		p = new Node_t(intrs[i]);
		nds[i] = p;
		RBTree_Insert(t, p);
	}
	
	memset(visit, false, sizeof(visit));
	for (i=0; i<n; ++i) {
		while (1) {
			j = rand()%n;
			if (!visit[j])
				break;
		}
		visit[j] = true;
		RBTree_Delete(t, nds[j]);
		if (check_RBTree(t))
			puts("Right");
		else
			puts("Wrong");
	}
}

void check_Search() {
	int i, j, k;
	Tree_t *t = new Tree_t();
	interval_t intrs[10] = {
		interval_t(16, 21),
		interval_t(8 , 9 ),
		interval_t(25, 30),
		interval_t(5 , 8 ),
		interval_t(15, 23),
		interval_t(17, 19),
		interval_t(26, 26),
		interval_t(0 , 3 ),
		interval_t(6 , 10),
		interval_t(19, 20)
	};
	int n = sizeof(intrs) / sizeof(interval_t);
	Node_t *p;
	
	printf("n = %d\n", n);
	for (i=0; i<n; ++i) {
		p = new Node_t(intrs[i]);
		RBTree_Insert(t, p);
	}
	
	interval_t tmp = interval_t(15, 28);
	// // test 14.3-3
	// p = RBTree_Search_Min(t, t->root, tmp);
	// if (p == t->NIL) {
		// puts("no overlap interval");
	// } else {
		// printf("[%d, %d]\n", p->intr.low, p->intr.high);
	// }
	
	// // test 14.3-4
	// RBTree_Search_All(t, t->root, tmp);
	// test 14.3-5
	printf("\n\nInorder the tree with color:\n");
	Inorder_RBTree_Walk_WithColor(t, t->root);
	printf("\n\nsearch exactly [%d, %d]\n", tmp.low, tmp.high);
	p = RBTree_Seach_Exactly(t, tmp);
	if (p == t->NIL)
		puts("not found such exactly intr");
	else
		puts("found a exactly intr");
	tmp = interval_t(17, 19);
	printf("\n\nsearch exactly [%d, %d]\n", tmp.low, tmp.high);
	p = RBTree_Seach_Exactly(t, tmp);
	if (p == t->NIL)
		puts("not found such exactly intr");
	else
		puts("found a exactly intr");
}

int main() {
	
	#ifdef LOCAL_DEBUG
		freopen("data.in", "r", stdin);
		freopen("data.out", "w", stdout);
	#endif
	
	// init();
	// check_delete();
	check_Search();
	
	return 0;
}
