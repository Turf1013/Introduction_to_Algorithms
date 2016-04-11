#ifndef RS_TST_H
#define RS_TST_H

/*
	Sort items using string as key.
*/
void swapn(int a, int b, int n, char *x[]);
void sortStr(char *x[], int n, int dep);
void sortedStr(char *x[], int n);


/*
	ternary search tree
*/
typedef struct Node* Ndptr;
typedef struct Node {
	char splitchar;
	Ndptr lokid, eqkid, hikid;
} Node;

void tst_hard_Insert(char *);
Ndptr tst_simple_Insert(Ndptr, char *);
int tst_Search(char *s);
void tst_Delete(Ndptr);


/*
	hash
*/
typedef struct HNode* Hdptr;
typedef struct HNode {
	char *s;
	Hdptr nxt;
} HNode;

void hash_init(int );
unsigned getH(char *);
void hash_Insert(char *);
int hash_Search(char *);
void hash_Delete();


/*
	trie
*/
#define MAXK 26
typedef struct TNode* Tdptr;
typedef struct TNode {
	int flag;
	Tdptr nxt[MAXK];
} TNode;

void trie_Init();
void trie_Insert_v1(char *);
void trie_Insert_v2(char *);
int trie_Search_v1(char *);
int trie_Search_v2(char *);
void trie_Delete(Tdptr);

/*
	Advanced String Search Algorithm
*/


#endif /* RS_TST_H */
