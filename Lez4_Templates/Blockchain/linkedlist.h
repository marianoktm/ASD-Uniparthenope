//
// Created by apont on 1/2/2023.
//

#ifndef ASD_LINKEDLIST_H
#define ASD_LINKEDLIST_H

#include "node.h"


/**
 * A linked list made of nodes.
 * @tparam T the datatype the nodes will hold.
 */
template <class T> class linkedlist {
private:
    // Attributes
    node<T> * head = nullptr; // First node of the list.
    int size = 0; // Numbers of nodes in the list.

public:
    // Constructors
    linkedlist() = default;
    linkedlist(node<T> * _head);

    // Getters
    int get_size();

    // Push (from node)
    void push_back(node<T> * _node);

    // Push (from data)
    void push_back(T _data);

    // Get head
    node<T> * get_head();

    // Get i-th element
    node<T> * get(unsigned int i);

    // Get i-th element data
    T get_data(unsigned int i);
};


/* LINKED LIST METHODS */
// Constructors
template <class T>
linkedlist<T>::linkedlist(node<T> * _head) {
    linkedlist<T>::head = _head;

    if (_head != nullptr) {
        node<T> * temp = _head;
        do {
            linkedlist<T>::size++;
            temp = temp->get_next();
        } while (temp != nullptr);
    }
}

// Getter: size
template <class T>
int linkedlist<T>::get_size() {
    return linkedlist<T>::size;
}

// Push (node)
template <class T>
void linkedlist<T>::push_back(node<T> * _node) {
    if (linkedlist<T>::head == nullptr) {
        linkedlist<T>::head = _node;
    }
    else {
        auto temp_node = linkedlist<T>::head;
        while (temp_node->get_next() != nullptr)
            temp_node = temp_node->get_next();
        temp_node->set_next(_node);
    }
    size++;
}

// Push (data)
template <class T>
void linkedlist<T>::push_back(T _data) {
    auto to_push = new node<T>(_data, nullptr);
    push_back(to_push);
}

// Get head
template <class T>
node<T> * linkedlist<T>::get_head() {
    return linkedlist<T>::head;
}

// Get i-th element
template <class T>
node<T> * linkedlist<T>::get(unsigned int i) {
    if (size == 0) return nullptr;

    auto temp = head;
    int k = 0;
    while ((temp->get_next() != nullptr) and (k < i)) {
        temp = temp->get_next();
        k++;
    }

    return temp;
}

// Get i-th element data
template <class T>
T linkedlist<T>::get_data(unsigned int i) {
    node<T> * node = get(i);
    return node->get_data();
}

#endif //ASD_LINKEDLIST_H
