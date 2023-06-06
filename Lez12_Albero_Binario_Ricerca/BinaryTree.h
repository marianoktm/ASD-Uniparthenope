//
// Created by apont on 1/7/2023.
//

#ifndef ASD_BINARYTREE_H
#define ASD_BINARYTREE_H

#include <iostream>
#include <vector>


/* Binary Tree Node Class */
template<class T> class btNode {
private:
    T data;
    btNode<T>* left = nullptr;
    btNode<T>* right = nullptr;
    btNode<T>* parent = nullptr;

    friend std::ostream & operator<<(std::ostream &os, const btNode &node) {
        os << node.data;
        return os;
    }

public:
    btNode() = default;
    explicit btNode(T data, btNode<T>* left = nullptr, btNode<T>* right = nullptr, btNode<T>* parent = nullptr) : data(data), left(left), right(right), parent(parent) {}

    T getData() { return data; }
    void setData(T data) { btNode::data = data; }

    btNode<T>* getLeft() { return left; }
    void setLeft(btNode<T>* left) { btNode::left = left; }

    btNode<T>* getRight() { return right; }
    void setRight(btNode<T>* right) { btNode::right = right; }

    btNode<T>* getParent() { return parent; }
    void setParent(btNode<T>* parent) { btNode::parent = parent; }
};


/* Actual Binary Tree Class */
template<class T> class BinaryTree {
private:
    btNode<T> * root;

    void preorder_help(btNode<T>* node);
    void inorder_help(btNode<T>* node);
    void postorder_help(btNode<T>* node);
    void preorder_showall_helper(btNode<T>* node);

public:
    BinaryTree() = default;
    explicit BinaryTree(btNode<T> * rootNode = nullptr);

    void preorder_print(); // radix then left subtree then right subtree => RAD -> LST -> RST
    void inorder_print(); // left subtree then radix then right subtree => LST -> RAD -> RST
    void postorder_print(); // left subtree then right subtree then radix => LST -> RST -> RAD
    void preorder_showall(); // like preorder but shows parent, left child and right child of each node

    btNode<T> * getRoot() { return this->root; }
    void setRoot(btNode<T> * newroot) { this->root = newroot; }
};

// Binary Tree constructor
template<class T>
BinaryTree<T>::BinaryTree(btNode<T> * rootNode) {
    this->root = rootNode;
}

// Preorder print help
template<class T>
void BinaryTree<T>::preorder_help(btNode<T> *node) {
    if (node != nullptr) {
        std::cout << *node << " ";
        preorder_help(node->getLeft());
        preorder_help(node->getRight());
    }
}

// Inorder print help
template<class T>
void BinaryTree<T>::inorder_help(btNode<T> *node) {
    if (node != nullptr) {
        inorder_help(node->getLeft());
        std::cout << *node << " ";
        inorder_help(node->getRight());
    }
}

// Postorder print help
template<class T>
void BinaryTree<T>::postorder_help(btNode<T> *node) {
    if (node != nullptr) {
        postorder_help(node->getLeft());
        postorder_help(node->getRight());
        std::cout << *node << " ";
    }
}

// Preorder print
template<class T>
void BinaryTree<T>::preorder_print() {
    preorder_help(root);
    std::cout << std::endl;
}

// Inorder print
template<class T>
void BinaryTree<T>::inorder_print() {
    inorder_help(root);
    std::cout << std::endl;
}

// Postorder print
template<class T>
void BinaryTree<T>::postorder_print() {
    postorder_help(root);
    std::cout << std::endl;
}


#endif //ASD_BINARYTREE_H
