//
// Created by apont on 1/7/2023.
//


#include <vector>
#include "BinaryTree.h"
#include "BinarySearchTree.h"


btNode<char> * genBinaryTree() {
    auto f = new btNode<char>('f');
    auto e = new btNode<char>('e');
    auto d = new btNode<char>('d');
    auto c = new btNode<char>('c');
    auto b = new btNode<char>('b');
    auto a = new btNode<char>('a');

    a->setLeft(b);

    b->setParent(a);
    b->setLeft(d);
    b->setRight(c);

    c->setParent(b);

    d->setParent(b);
    d->setRight(e);

    e->setParent(d);
    e->setRight(f);

    f->setParent(e);

    return a;
}

BinarySearchTree<char> * genBST() {
    auto bst = new BinarySearchTree<char>();

    bst->insert_from_data('a', 12);
    bst->insert_from_data('b', 5);
    bst->insert_from_data('c', 18);
    bst->insert_from_data('d', 19);
    bst->insert_from_data('e', 15);
    bst->insert_from_data('f', 2);
    bst->insert_from_data('g', 9);

    return bst;
}

int main() {
    // Binary Tree Test
    BinaryTree<char> bt(genBinaryTree());

    bt.inorder_print();
    bt.preorder_print();
    bt.postorder_print();


    // BST Test
    BinarySearchTree<char> bst = *genBST();

    bst.inorder_print();
    std::cout << *bst.search_from_key(19) << std::endl;

    std::cout << "min:" << *bst.minimum() << std::endl << "max: " << *bst.maximum() << std::endl;

    std::cout << "predecessor of 19: " << *bst.predecessor(bst.search_from_key(19)) << std::endl;
    std::cout << "successor of 2: " << *bst.successor(bst.search_from_key(2)) << std::endl;

    bst.delete_node(bst.search_from_key(15));
    bst.inorder_print();

    return 0;
}
