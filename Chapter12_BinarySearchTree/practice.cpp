#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stack>
using namespace std;

typedef struct Node_t {
	int key;
	Node_t *p, *l, *r;
	Node_t() {}
	Node_t(int k) {
		key = k;
		p = l = r = NULL;
	}
} Node_t;

typedef struct Tree_t {
	Node_t *root;
	Tree_t() {
		root = NULL;
	}
} Tree_t;

Tree_t *t;

void Inorder_Tree_Walk(Node_t *x) {
	if (x != NULL) {
		Inorder_Tree_Walk(x->l);
		printf("%d ", x->key);
		Inorder_Tree_Walk(x->r);
	}
}

void Inorder_Tree_Walk_Nonrecursive_1(Node_t *x) {
	stack<Node_t *> S;
	bool mid = false;

	printf("Using stack to implement Inorder_Tree_Walk:\n");
	S.push(x);
	while (!S.empty()) {
		if (x->l == NULL || mid) {
			printf("%d ", x->key);
			S.pop();
			if (x->r == NULL) {
				if (S.empty())
					break;
				x = S.top();
				mid = true;
			} else {
				x = x->r;
				S.push(x);
				mid = false;
			}
		} else {
			x = x->l;
			S.push(x);
		}
	}
	printf("\n");
}
void Inorder_Tree_Walk_Nonrecursive_2(Node_t *x) {
	printf("Using nonstack to implement Inorder_Tree_Walk:\n");
	Node_t *p = x->p, *y = NULL;
	bool ret = false, retr = false;

	while (!retr || y!=p) {
		if (x->l == NULL || ret) {
			if (!retr)
				printf("%d ", x->key);
			if (x->r == NULL || retr) {
				retr = (x == y->r);
				x = y;
				y = y->p;
				ret = true;
			} else {
				y = x;
				x = x->r;
				ret = false;
			}
		} else {
			y = x;
			x = x->l;
		}
	}
	printf("\n");
}

void Preorder_Tree_Walk(Node_t *x) {
	if (x != NULL) {
		printf("%d ", x->key);
		Preorder_Tree_Walk(x->l);
		Preorder_Tree_Walk(x->r);
	}
}

void Postorder_Tree_Walk(Node_t *x) {
	if (x != NULL) {
		Postorder_Tree_Walk(x->l);
		Postorder_Tree_Walk(x->r);
		printf("%d ", x->key);
	}
}

Node_t *Tree_Search(Node_t *x, int k) {
	if (x==NULL || x->key==k)
		return x;
	if (k < x->key)
		return Tree_Search(x->l, k);
	else
		return Tree_Search(x->r, k);
}

Node_t *Iterative_Tree_Search(Node_t *x, int k) {
	while (x!=NULL && k!=x->key) {
		if (k < x->key)
			x = x->l;
		else
			x = x->r;
	}
	return x;
}

Node_t *Tree_Minimum(Node_t *x) {
	while (x->l != NULL)
		x = x->l;
	return x;
}

Node_t *Tree_Minimum_2(Node_t *x) {
	if (x->l == NULL)
		return x;
	return Tree_Minimum_2(x->l);
}

Node_t *Tree_Maximum(Node_t *x) {
	while (x->r != NULL)
		x = x->r;
	return x;
}

Node_t *Tree_Maximum_2(Node_t *x) {
	if (x->r == NULL)
		return x;
	return Tree_Maximum_2(x->r);
}

Node_t *Tree_Successor(Node_t *x) {
	if (x->r != NULL)
		return Tree_Minimum(x->r);
	Node_t *y = x->p;
	while (y!=NULL && x==y->r) {
		x = y;
		y = x->p;
	}
	return y;
}

Node_t *Tree_Predecessor(Node_t *x) {
	if (x->l != NULL)
		return Tree_Maximum(x->l);
	Node_t *y = x->p;
	while (y!=NULL && x==y->l) {
		x = y;
		y = x->p;
	}
	return y;
}

void Tree_Insert(Tree_t *t, Node_t *z) {
	Node_t *y = NULL;
	Node_t *x = t->root;
	while (x != NULL) {
		y = x;
		if (z->key < x->key)
			x = x->l;
		else
			x = x->r;
	}
	z->p = y;
	if (y == NULL) {
		t->root = z;	// tree t was empty
	} else if (z->key < y->key) {
		y->l = z;
	} else {
		y->r = z;
	}
}

void Tree_Insert_Recursive(Tree_t *t, Node_t *p, Node_t *x, Node_t *z) {
	if (x == NULL) {
		z->p = p;
		if (p == NULL)
			t->root = z;
		else if (z->key < p->key)
			p->l = z;
		else
			p->r = z;
	} else if (z->key < x->key) {
		Tree_Insert_Recursive(t, x, x->l, z);
	} else {
		Tree_Insert_Recursive(t, x, x->r, z);
	}
}

// use subTree v replace subTree v
void Transplant(Tree_t *t, Node_t *u, Node_t *v) {
	if (u->p == NULL) {
		t->root = v;	// u is root
	} else if (u == u->p->l) {
		u->p->l = v;
	} else {
		u->p->r = v;
	}
	if (v != NULL)
		v->p = u->p;
}

void Tree_Delete(Tree_t *t, Node_t *z) {
	if (z->l == NULL) {
		Transplant(t, z, z->r);
	} else if (z->r == NULL) {
		Transplant(t, z, z->l);
	} else {
		Node_t *y = Tree_Minimum(z->r);	// y->l == NULL
		if (y->p != z) {
			Transplant(t, y, y->r);
			y->r = z->r;
			y->r->p = y;
		}
		Transplant(t, z, y);
		y->l = z->l;
		y->l->p = y;
	}
}

void init() {
	int buf[11] = {15,6,18,3,7,17,20,2,4,13,9};
	int n = 11;
	t = new Tree_t();

	for (int i=0; i<n; ++i) {
		Node_t *p = new Node_t(buf[i]);
		printf("%d\n", p->key);
		Tree_Insert(t, p);
		printf("insert %d succeed.\n", buf[i]);
	}
}

void testInBook() {
	Node_t *p = t->root;

	printf("\n\nPrint Inorder:\n");
	Inorder_Tree_Walk(p);

	printf("\n\nPrint Preorder:\n");
	Preorder_Tree_Walk(p);

	printf("\n\nPrint Postorder:\n");
	Postorder_Tree_Walk(p);

	printf("\nMinimum of tree is %d\n", Tree_Minimum(p)->key);
	printf("Maximum of tree is %d\n", Tree_Maximum(p)->key);

	Node_t *a = Tree_Search(p, 15);
	Node_t *b = Iterative_Tree_Search(p, 15);
	if (a==NULL || b==NULL || a!=b) {
		printf("\nTree search is wrong.\n");
		return ;
	}
	b = Tree_Successor(a);
	printf("\n15's successor is %d\n", Tree_Successor(a)->key);
	printf("%d's predecessor is %d\n", b->key, Tree_Predecessor(b)->key);

	printf("\n\ndelete 4\n");
	a = Tree_Search(t->root, 4);
	Tree_Delete(t, a);
	printf("Print Inorder:\n");
	Inorder_Tree_Walk(t->root);
	printf("\n\n");

	printf("delete 7\n");
	a = Tree_Search(t->root, 7);
	Tree_Delete(t, a);
	printf("Print Inorder:\n");
	Inorder_Tree_Walk(t->root);
	printf("\n\n");

	printf("delete 6\n");
	a = Tree_Search(t->root, 6);
	Tree_Delete(t, a);
	printf("Print Inorder:\n");
	Inorder_Tree_Walk(t->root);
	printf("\n\n");
}

void test_1201_03() {
	printf("\n\ntest 12.1-3\n");
	printf("Inorder Tree Walk:\n");
	Inorder_Tree_Walk(t->root);
	printf("\n");
	printf("Inorder Tree Walk Nonrecursive:\n");
	Inorder_Tree_Walk_Nonrecursive_1(t->root);
	Inorder_Tree_Walk_Nonrecursive_2(t->root);
}

void test_1201_04() {
	printf("\n\nPreorder Tree Walk:\n");
	Preorder_Tree_Walk(t->root);
	printf("\n");
	printf("Postorder Tree Walk:\n");
	Postorder_Tree_Walk(t->root);
	printf("\n");
}

void test_1203_04() {
	int buf[6] = {15,6,3,8,7,9};
	int n = 6;
	Tree_t *tr = new Tree_t();
	Node_t *p;
	
	for (int i=0; i<n; ++i) {
		p = new Node_t(buf[i]);
		Tree_Insert(tr, p);
	}
	
	printf("first 6 then 3:\n");
	p = Tree_Search(tr->root, 6);
	Tree_Delete(tr, p);
	p = Tree_Search(tr->root, 3);
	Tree_Delete(tr, p);
	Preorder_Tree_Walk(tr->root);
	printf("\n");
	delete tr;
	
	tr = new Tree_t();
	
	for (int i=0; i<n; ++i) {
		p = new Node_t(buf[i]);
		Tree_Insert(tr, p);
	}
	
	printf("first 3 then 6:\n");
	p = Tree_Search(tr->root, 3);
	Tree_Delete(tr, p);
	p = Tree_Search(tr->root, 6);
	Tree_Delete(tr, p);
	Preorder_Tree_Walk(tr->root);
	printf("\n");
	delete tr;
}

void test_1201() {
	printf("\n\ntest 12.1\n");
	printf("test 12.1-3\n");
	test_1201_03();
	printf("test 12.1-4\n");
	test_1201_04();
}

void test_1203() {
	printf("\n\ntest 12.3\n");
	printf("test 12.3-4\n");
	test_1203_04();
}

int main() {

	init();
	test_1201();
	test_1203();
	
	return 0;
}
