# Binary Search Tree (BST) Implementation

This project contains an implementation of a Binary Search Tree (BST) in C. The BST supports various operations such as insertion, deletion, searching, balancing, and in-order traversal.

## Files

- `BSTree.h`: Header file containing the declarations of the BST functions and structures.
- `BSTree.c`: Source file containing the implementations of the BST functions.
- `demo.c`: Demo file to demonstrate the usage of the BST functions.
- `makefile`: Makefile to compile and run the test program.

## Functions

### BSTree.h

- `Node* createNode(int value)`: Creates a new node with the given value.
- `BSTree* createBSTree()`: Creates a new empty BST.
- `void insertBST(BSTree* tree, int value)`: Inserts a value into the BST.
- `void removeBST(BSTree* tree, int value)`: Removes a value from the BST.
- `Node* searchBST(BSTree* tree, int value)`: Searches for a value in the BST.
- `void balanceBST(BSTree* tree)`: Balances the BST.
- `void printInOrderBST(BSTree* tree)`: Prints the BST in in-order traversal.
- `int getHeightBST(Node* root)`: Returns the height of the BST.
- `int countNodes(Node* root)`: Counts the number of nodes in the BST.
- `void clearBST(BSTree* tree)`: Clears the BST, and frees the nodes.
- `void destroyBST(BSTree* tree)`: Destroys the BST and frees the memory.

### BSTree.c

Contains the implementations of the functions declared in `BSTree.h`.

### demo.c

A demo program that demonstrates the usage of the BST functions. It performs the following operations:

1. Creates a new BST.
2. Inserts values into the BST.
3. Prints the BST in in-order traversal.
4. Removes values from the BST.
5. Searches for values in the BST.
6. Balances the BST.
7. Destroys the BST.

## Usage

To compile and run the test program, use the following commands:

```sh
make
```