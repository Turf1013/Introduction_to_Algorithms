#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define LOCAL_DEBUG
#define RED		true
#define BLACK	false

typedef struct Node_t {
	bool color;
	int key;
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
		NIL->color = BLACK;
		NIL->p = NIL->left = NIL->right = NIL;
		root = NIL;
	}
} Tree_t;

Tree_t *t;

void Inorder_RBTree_Walk(Tree_t *t, Node_t *x) {
	if (x != t->NIL) {
		Inorder_RBTree_Walk(t, x->left);
		printf("%d ", x->key);
		Inorder_RBTree_Walk(t, x->right);
	}
}

void Preorder_RBTree_Walk(Tree_t *t, Node_t *x) {
	if (x != t->NIL) {
		printf("%d ", x->key);
		Preorder_RBTree_Walk(t, x->left);
		Preorder_RBTree_Walk(t, x->right);
	}
}

void Postorder_RBTree_Walk(Tree_t *t, Node_t *x) {
	if (x != t->NIL) {
		Postorder_RBTree_Walk(t, x->left);
		Postorder_RBTree_Walk(t, x->right);
		printf("%d ", x->key);
	}
}

void Inorder_RBTree_Walk_WithColor(Tree_t *t, Node_t *x) {
	if (x != t->NIL) {
		Inorder_RBTree_Walk_WithColor(t, x->left);
		printf("key: %d color: %s\n", x->key, x->color?"Red":"Black");
		Inorder_RBTree_Walk_WithColor(t, x->right);
	}
}

void Preorder_RBTree_Walk_WithColor(Tree_t *t, Node_t *x) {
	if (x != t->NIL) {
		printf("key: %d color: %s\n", x->key, x->color?"Red":"Black");
		Preorder_RBTree_Walk_WithColor(t, x->left);
		Preorder_RBTree_Walk_WithColor(t, x->right);
	}
}

void Postorder_RBTree_Walk_WithColor(Tree_t *t, Node_t *x) {
	if (x != t->NIL) {
		Postorder_RBTree_Walk_WithColor(t, x->left);
		Postorder_RBTree_Walk_WithColor(t, x->right);
		printf("key: %d color: %s\n", x->key, x->color?"Red":"Black");
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
	bool y_original_color = y->color;
	
	if (z->left == t->NIL) {
		x = z->right;
		RBTree_Transplant(t, y, x);
	} else if (z->right == t->NIL) {
		x = z->left;
		RBTree_Transplant(t, y, x);
	} else {
		y = RBTree_Minimum(t, z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->p == z) {
			x->p = y;
		} else {
			RBTree_Transplant(t, y, x);
			y->right = z->right;
			y->right->p = y;
		}
		RBTree_Transplant(t, z, y);
		y->left = z->left;
		y->left->p = y;
		y->color = z->color;
	}
	
	if (y_original_color == BLACK)
		RBTree_Delete_Fixup(t, x);	// use x replace y
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

bool check_RBTree(Tree_t *t) {
	bool ret = true;
	
	if (t->NIL->color != BLACK)
		return false;
	if (t->root == t->NIL)
		return ret;
	if (t->root->color != BLACK)
		return false;
	
	ret = check_RNode(t, t->root);
	if (ret == false)
		return false;
	
	check_BHeight(t, t->root, ret);
	
	return ret;
}

void init() {
	t = new Tree_t();
	int a[] = {26, 17, 41, 14, 21, 30, 47, 10, 16, 19, 23, 28, 38, 7, 12, 15, 20, 35, 39, 3};
	int n = sizeof(a) / sizeof(int);
	Node_t *p;
	
	printf("n = %d\n", n);
	for (int i=0; i<n; ++i) {
		p = new Node_t(a[i]);
		RBTree_Insert(t, p);
		printf("\n\nafter insert %d nums(%d):\n", i+1, a[i]);
		Inorder_RBTree_Walk_WithColor(t, t->root);
	}
	
	Inorder_RBTree_Walk_WithColor(t, t->root);
	
	printf("\n");
	if (check_RBTree(t))
		puts("Right");
	else
		puts("Wrong");
}

void test_1304_07() {
	int n = 10;
	int x;
	Node_t *p;
	
	Inorder_RBTree_Walk_WithColor(t, t->root);
	while (n--) {
		x = rand()%50;
		p = new Node_t(x);
		RBTree_Insert(t, p);
		RBTree_Delete(t, p);
		printf("\n\nx=%d\n", x);
		Inorder_RBTree_Walk_WithColor(t, t->root);
		if (check_RBTree(t))
			puts("Right");
		else
			puts("Wrong");
	}
}

void test_1303_02() {
	Tree_t *t = new Tree_t();
	int a[] = {41, 38, 31, 12, 19, 8};
	int n = sizeof(a) / sizeof(int);
	Node_t *p;
	
	printf("n = %d\n", n);
	for (int i=0; i<n; ++i) {
		p = new Node_t(a[i]);
		RBTree_Insert(t, p);
		printf("\n\nafter insert %d nums(%d):\n", i+1, a[i]);
		Inorder_RBTree_Walk_WithColor(t, t->root);
	}
}

void test_1304_03() {
	Tree_t *t = new Tree_t();
	int a[] = {41, 38, 31, 12, 19, 8};
	int b[] = {8, 12, 19, 31, 38, 41};
	int n = sizeof(a) / sizeof(int);
	Node_t *p;
	
	printf("n = %d\n", n);
	for (int i=0; i<n; ++i) {
		p = new Node_t(a[i]);
		RBTree_Insert(t, p);
	}
	
	Inorder_RBTree_Walk_WithColor(t, t->root);
	for (int i=0; i<n; ++i) {
		p = RBTree_Search(t, b[i]);
		printf("\n\nafter delete %d, RBTree is ", p->key);
		RBTree_Delete(t, p);
		if (check_RBTree(t))
			puts("Right.");
		else
			puts("Wrong.");
		Inorder_RBTree_Walk_WithColor(t, t->root);
	}
}

int main() {
	
	#ifdef LOCAL_DEBUG
		freopen("data.in", "r", stdin);
		freopen("data.out", "w", stdout);
	#endif
	
	//init();
	test_1304_03();
	//test_1304_07();
	
	return 0;
}
