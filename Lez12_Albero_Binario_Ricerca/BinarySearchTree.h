//
// Created by apont on 1/7/2023.
//

#ifndef ASD_BINARYSEARCHTREE_H
#define ASD_BINARYSEARCHTREE_H

#include <ostream>
#include "BinaryTree.h"


/* Data class for bst */
template<class T> class bstData {
private:
    int key;
    T value;

public:
    bstData() = default;
    bstData(T value, int key): value(value), key(key) {};

    int getKey() const { return key; }
    void setKey(int key) { bstData::key = key; }

    T getValue() const { return value; }
    void setValue(T value) { bstData::value = value; }

    friend std::ostream & operator<<(std::ostream &os, const bstData &data) {
        os << "key: " << data.key << " value: " << data.value;
        return os;
    }
};


/* !!!!! DEPRECATED !!!!! */
/* BST NODE Class derived from binary tree node. */
/*
template<class T> class bstNode: public btNode<T> {
private:
    int key;

public:
    bstNode() = default;
    bstNode(T data, int key = 0, bstNode<T> * left = nullptr, bstNode<T> * right = nullptr, bstNode<T> * parent = nullptr): btNode<T>(data, left, right, parent), key(key) {};

    int getKey() { return key; }
    void setKey(int key) { bstNode::key = key; }

    friend std::ostream &operator<<(std::ostream &os, const bstNode &node) {
        os << static_cast<const btNode<T> &>(node) << " key: " << node.key;
        return os;
    }
};
*/


/* Actual binary search tree class */
template<class T> class BinarySearchTree: public BinaryTree<bstData<T>> {
private:
    btNode<bstData<T>> * search_from_key_helper(int key, btNode<bstData<T>> * node);

    void transplant(btNode<bstData<T>> * destination, btNode<bstData<T>> * from);

public:
    BinarySearchTree(): BinaryTree<bstData<T>>(nullptr) {};
    explicit BinarySearchTree(btNode<bstData<T>> * rootNode): BinaryTree<bstData<T>>(rootNode){};

    void insert_node(btNode<bstData<T>> * to_insert_z);
    void insert_from_data(T data, int key);
    void delete_node(btNode<bstData<T>> * to_remove_z);

    btNode<bstData<T>> * search_from_key(int key);

    btNode<bstData<T>> * min_from(btNode<bstData<T>> * node);
    btNode<bstData<T>> * max_from(btNode<bstData<T>> * node);
    btNode<bstData<T>> * minimum();
    btNode<bstData<T>> * maximum();

    btNode<bstData<T>> * successor(btNode<bstData<T>> * node);
    btNode<bstData<T>> * predecessor(btNode<bstData<T>> * node);
};

/* BST Class functions implementation */
// Node insert
template<class T>
void BinarySearchTree<T>::insert_node(btNode<bstData<T>> * to_insert_z) {
    // Find and set to_insert parent such as to_insert will be a leaf
    btNode<bstData<T>> * parent_y = nullptr;
    btNode<bstData<T>> *  current_x = this->getRoot();
    while (current_x != nullptr) {
        parent_y = current_x;
        if (to_insert_z->getData().getKey() < current_x->getData().getKey())
            current_x = current_x->getLeft();
        else
            current_x = current_x->getRight();
    }
    to_insert_z->setParent(parent_y);

    // Set to_insert as child of found parent node, or root if the tree is empty.
    // 1. Tree is empty, to_insert will become the root.
    if (parent_y == nullptr)
        this->setRoot(to_insert_z);
    // 2. key[to_insert] < key[parent[to_insert]], to_insert will become the left child of parent
    else if (to_insert_z->getData().getKey() < parent_y->getData().getKey())
        parent_y->setLeft(to_insert_z);
    // 3. key[to_insert] > key[parent[to_insert]], to_insert will become the right child of parent
    else
        parent_y->setRight(to_insert_z);
}

// Node insert, as data
template<class T>
void BinarySearchTree<T>::insert_from_data(T data, int key) {
    auto node_data = new bstData<T>(data, key);
    auto to_insert = new btNode<bstData<T>>(*node_data);
    insert_node(to_insert);
}

// Helper recurrent function for bst search
template<class T>
btNode<bstData<T>> * BinarySearchTree<T>::search_from_key_helper(int key, btNode<bstData<T>> * node) {
    if (node == nullptr or key == node->getData().getKey())
        return node;
    if (key < node->getData().getKey())
        return search_from_key_helper(key, node->getLeft());
    else
        return search_from_key_helper(key, node->getRight());
}


// Actual callable bst search function
template<class T>
btNode<bstData<T>> * BinarySearchTree<T>::search_from_key(int key) {
    return search_from_key_helper(key, this->getRoot());
}

// Returns the min element of the tree with radix "node"
template<class T>
btNode<bstData<T>> * BinarySearchTree<T>::min_from(btNode<bstData<T>> * node) {
    while (node->getLeft() != nullptr)
        node = node->getLeft();

    return node;
}

// Returns the max element of the tree with radix "node"
template<class T>
btNode<bstData<T>> * BinarySearchTree<T>::max_from(btNode<bstData<T>> * node) {
    while (node->getRight() != nullptr)
        node = node->getRight();

    return node;
}

// Returns the min of the whole tree
template<class T>
btNode<bstData<T>> * BinarySearchTree<T>::minimum() {
    return min_from(this->getRoot());
}

// Returns the max of the whole tree
template<class T>
btNode<bstData<T>> * BinarySearchTree<T>::maximum() {
    return max_from(this->getRoot());
}

// Returns the successor (the smallest element bigger than node)
template<class T>
btNode<bstData<T>> * BinarySearchTree<T>::successor(btNode<bstData<T>> * node) {
    // Easy case: getting the smallest of the right subtree
    if (node->getRight() != nullptr)
        return BinarySearchTree<T>::min_from(node->getRight());

    // Hard case: the successor is an ancestor
    btNode<bstData<T>> * parent_y = node->getParent();
    // Ancestor found if parent == nullptr OR node is in parent right subtree
    while (parent_y != nullptr and node == parent_y->getRight()) {
        node = parent_y;
        parent_y = parent_y->getParent();
    }
    return parent_y;
}

// Returns the predecessor (the bigger element smaller than node)
template<class T>
btNode<bstData<T>> * BinarySearchTree<T>::predecessor(btNode<bstData<T>> * node) {
    // Easy case: getting the bigger of the left subtree
    if (node->getLeft() != nullptr)
        return BinarySearchTree<T>::max_from(node->getLeft());

    // Hard case: the successor is an ancestor
    btNode<bstData<T>> * parent_y = node->getParent();
    // Ancestor found if parent == nullptr OR node is in parent left subtree
    while (parent_y != nullptr and node == parent_y->getLeft()) {
        node = parent_y;
        parent_y = parent_y->getParent();
    }
    return parent_y;
}

// Transplants the "from" subtree into "destination"
template<class T>
void BinarySearchTree<T>::transplant(btNode<bstData<T>> * destination, btNode<bstData<T>> * from) {
    // If destination.parent does not exist, destination is the root and from will become the root
    if (destination->getParent() == nullptr)
        this->setRoot(from);

    // If destination is a left child of it's parent, from becomes the new left child. Else, it's a right child and happens the same but at right
    btNode<bstData<T>> * destination_parent = destination->getParent();
    if (destination == destination_parent->getLeft())
        destination_parent->setLeft(from);
    else
        destination_parent->setRight(from);

    // Set new from.parent
    if (from != nullptr)
        from->setParent(destination_parent);
}

// Deletes to_remove_z node from the tree
template<class T>
void BinarySearchTree<T>::delete_node(btNode<bstData<T>> * to_remove_z) {
    // If no left child, just move right subtree to to_remove position
    if (to_remove_z->getLeft() == nullptr)
        transplant(to_remove_z, to_remove_z->getRight());
    // If no right child, just move left subtree to to_remove position
    else if (to_remove_z->getRight() == nullptr)
        transplant(to_remove_z, to_remove_z->getLeft());
    // Hard case:
    else {
        btNode<bstData<T>> * right_tree_min_y = min_from(to_remove_z->getRight());

        if (right_tree_min_y->getParent() != to_remove_z) {
            transplant(right_tree_min_y, right_tree_min_y->getRight());
            right_tree_min_y->setRight(to_remove_z->getRight());
            (right_tree_min_y->getRight())->setParent(right_tree_min_y);
        }

        transplant(to_remove_z, right_tree_min_y);
        right_tree_min_y->setLeft(to_remove_z->getLeft());
        (right_tree_min_y->getLeft())->setParent(right_tree_min_y);
    }
}


#endif //ASD_BINARYSEARCHTREE_H
