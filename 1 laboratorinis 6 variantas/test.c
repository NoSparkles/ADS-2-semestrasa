#include "BSTree.h"
#include <stdio.h>

int main() {
    BSTree* tree = createBSTree();
    insertBST(tree, 5);
    insertBST(tree, 3);
    insertBST(tree, 7);
    insertBST(tree, 2);
    insertBST(tree, 4);
    insertBST(tree, 6);
    insertBST(tree, 8);

    Node* foundNode = searchBST(tree, 4);
    if (foundNode != NULL) {
        printf("Found node with value: %d\n", foundNode->value);
    } else {
        printf("Node not found.\n");
    }

    printf("In-order traversal of BST: ");
    printInOrderBST(tree);

    removeBST(tree, 5);
    printf("In-order traversal after removing 5: ");
    printInOrderBST(tree);

    removeBST(tree, 3);
    printf("In-order traversal after removing 3: ");
    printInOrderBST(tree);

    balanceBST(tree);
    printf("In-order traversal after balancing: ");
    printInOrderBST(tree);

    int height = getHeightBST(tree->root);
    printf("The height of the BST is %d\n", height);

    clearBST(tree);
    printf("The BST has been cleared.\n");

    destroyBST(tree);
    return 0;
}
