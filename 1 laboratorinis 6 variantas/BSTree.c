#include "BSTree.h"
#include <stdio.h>
#include <stdlib.h>

Node* createNode(int value){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

BSTree* createBSTree(){
    BSTree* newTree = (BSTree*)malloc(sizeof(BSTree));
    newTree->root = NULL;
    return newTree;
}

void insertBST(BSTree* tree, int value){
    Node* newNode = createNode(value);
    if(tree->root == NULL){
        tree->root = newNode;
    }else{
        Node* current = tree->root;
        Node* parent = NULL;
        while(1){
            parent = current;
            if(value < current->value){
                current = current->left;
                if(current == NULL){
                    parent->left = newNode;
                    return;
                }
            }else{
                current = current->right;
                if(current == NULL){
                    parent->right = newNode;
                    return;
                }
            }
        }
    }
}

void removeBST(BSTree* tree, int value){
    Node* current = tree->root;
    Node* parent = NULL;
    while(current != NULL){
        if(value == current->value){
            break;
        }
        parent = current;
        if(value < current->value){
            current = current->left;
        }else{
            current = current->right;
        }
    }
    if(current == NULL){
        return;
    }
    if(current->left == NULL && current->right == NULL){
        if(current == tree->root){
            tree->root = NULL;
        }else{
            if(parent->left == current){
                parent->left = NULL;
            }else{
                parent->right = NULL;
            }
        }
        free(current);
    }else if(current->left == NULL || current->right == NULL){
        Node* child = current->left == NULL ? current->right : current->left;
        if(current == tree->root){
            tree->root = child;
        }else{
            if(parent->left == current){
                parent->left = child;
            }else{
                parent->right = child;
            }
        }
        free(current);
    }else{
        Node* successor = current->right;
        Node* successorParent = current;
        while(successor->left != NULL){
            successorParent = successor;
            successor = successor->left;
        }
        if(successorParent->left == successor){
            successorParent->left = successor->right;
        }else{
            successorParent->right = successor->right;
        }
        current->value = successor->value;
        free(successor);
    }
}

void printInOrderRecBST(Node* node){
    if(node != NULL){
        printInOrderRecBST(node->left);
        printf("%d ", node->value);
        printInOrderRecBST(node->right);
    }
}

void printInOrderBST(BSTree* tree){
    printInOrderRecBST(tree->root);
    printf("\n");
}

Node* buildBalancedTree(int* nodes, int start, int end) {
    if (start > end) 
        return NULL;

    int mid = (start + end) / 2;
    Node* root = createNode(nodes[mid]);

    root->left = buildBalancedTree(nodes, start, mid - 1);
    root->right = buildBalancedTree(nodes, mid + 1, end);

    return root;
}

void storeInorderBST(Node* root, int* nodes, int* index) {
    if (root == NULL) {
        return;
    }
    storeInorderBST(root->left, nodes, index);
    nodes[(*index)++] = root->value;
    storeInorderBST(root->right, nodes, index);
}

void balanceBST(BSTree *tree) {
    Node *root = tree->root;
    int nodeCount = countNodes(root);
    int* nodes = (int*)malloc(nodeCount * sizeof(int));
    if (nodes == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    int index = 0;

    storeInorderBST(root, nodes, &index);

    Node* balancedRoot = buildBalancedTree(nodes, 0, index - 1);
    free(nodes);

    tree->root = balancedRoot;
}

Node* searchBST(BSTree* tree, int value) {
    Node* current = tree->root;
    while (current != NULL) {
        if (value == current->value) {
            return current;
        } else if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;
}

int getHeightBST(Node* root) {
    if (root == NULL) {
        return -1;
    } else {
        int leftHeight = getHeightBST(root->left);
        int rightHeight = getHeightBST(root->right);

        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
}

int countNodes(Node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

void clearBSTRec(Node* node) {
    if (node == NULL) {
        return;
    }
    clearBSTRec(node->left);
    clearBSTRec(node->right);
    free(node);
}

void clearBST(BSTree* tree) {
    if (tree->root != NULL) {
        clearBSTRec(tree->root);
        tree->root = NULL;
    }
}

void destroyBSTRec(Node* root) {
    if (root == NULL) {
        return;
    }
    destroyBSTRec(root->left);
    destroyBSTRec(root->right);
    free(root);
}

void destroyBST(BSTree *tree) {
    Node* root = tree->root;
    if (root != NULL) {
        destroyBSTRec(root);
    }
    free(tree);
}