#include "BSTree.h"

int main(){
    BSTree* tree = createBSTree();
    insertBST(tree, 5);
    insertBST(tree, 3);
    insertBST(tree, 7);
    insertBST(tree, 2);
    insertBST(tree, 4);
    insertBST(tree, 6);
    insertBST(tree, 8);
    printInOrderBST(tree);
    removeBST(tree, 5);
    printInOrderBST(tree);
    removeBST(tree, 3);
    balanceBST(tree);
    printInOrderBST(tree);
    return 0;
}