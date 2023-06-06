//
// Created by apont on 1/2/2023.
//

#ifndef ASD_NODE_H
#define ASD_NODE_H


/**
 * A node of a linked list, containing data of type T
 * @tparam T the datatype.
 */
template <class T> class node {
private:
    T data; // The data
    node<T> * next; // Pointer to next node

public:
    // Constructor
    node(T _data, node<T> * _next);
    explicit node(T _data);
    node() = default;

    // Setters
    void set_data(T _data);
    void set_next(node<T> * _next);

    // Getters
    T get_data();
    node<T> * get_next();
};


/* NODE METHODS */
// Constructor
template <class T>
node<T>::node(T _data, node<T> * _next) {
    node<T>::data = _data;
    node<T>::next = _next;
}

template <class T>
node<T>::node(T _data) {
    node<T>::data = _data;
    node<T>::next = nullptr;
}

// Setter: T data
template <class T>
void node<T>::set_data(T _data) {
    node<T>::data = _data;
}

// Setter: node<T> * next
template <class T>
void node<T>::set_next(node<T> * _next) {
    node<T>::next = _next;
}

// Getter: T data
template <class T>
T node<T>::get_data() {
    return this->data;
}

// Getter: node<T> * next
template <class T>
node<T> * node<T>::get_next() {
    return this->next;
}
#endif //ASD_NODE_H
