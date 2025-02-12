typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int);

typedef struct {
    Node* root;
} BSTree;

BSTree* createBSTree();
void insertBST(BSTree*, int);
void removeBST(BSTree*, int);
Node* searchBST(BSTree*, int);
void balanceBST(BSTree*);
void printInOrderBST(BSTree*);
int countNodes(Node*);