class Node:
    def __init__(self, key):
        self.left = None
        self.right = None
        self.val = key

class BSTree:
    def __init__(self):
        self.root = None

    def insert(self, key):
        if self.root is None:
            self.root = Node(key)
        else:
            self._insert(self.root, key)

    def _insert(self, root, key):
        if key < root.val:
            if root.left is None:
                root.left = Node(key)
            else:
                self._insert(root.left, key)
        else:
            if root.right is None:
                root.right = Node(key)
            else:
                self._insert(root.right, key)

    def remove(self, key):
        self.root = self._remove(self.root, key)

    def _remove(self, root, key):
        if root is None:
            return root
        
        if key < root.val:
            root.left = self._remove(root.left, key)
        elif key > root.val:
            root.right = self._remove(root.right, key)
        else:
            if root.left is None:
                return root.right
            elif root.right is None:
                return root.left

            root.val = self._min_value_node(root.right)
            root.right = self._remove(root.right, root.val)
        return root
    
    def _min_value_node(self, root):
        current = root
        while current.left is not None:
            current = current.left
        return current.val
    
    def print_inorder(self):
        self._print_inorder(self.root)

    def _print_inorder(self, root):
        if root:
            self._print_inorder(root.left)
            print(root.val, end=" ")
            self._print_inorder(root.right)

    def balance(self):
        nodes = []
        self._store_inorder(self.root, nodes)
        self.root = self._build_balanced_tree(nodes, 0, len(nodes) - 1)

    def _store_inorder(self, root, nodes):
        if root:
            self._store_inorder(root.left, nodes)
            nodes.append(root.val)
            self._store_inorder(root.right, nodes)

    def _build_balanced_tree(self, nodes, start, end):
        if start > end:
            return None

        mid = (start + end) // 2
        node = Node(nodes[mid])

        node.left = self._build_balanced_tree(nodes, start, mid - 1)
        node.right = self._build_balanced_tree(nodes, mid + 1, end)

        return node

if __name__ == "__main__":
    tree = BSTree()

    values = [10, 20, 30, 40, 50, 25]

    for value in values:
        tree.insert(value)
    
    tree.print_inorder()
    print()

    tree.remove(25)
    tree.balance()
    
    tree.print_inorder()
    print()