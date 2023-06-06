//
// Created by apont on 2/28/2023.
//

#ifndef ASD_DISJOINTSET_H
#define ASD_DISJOINTSET_H

#include <vector>
#include <unordered_map>

/** Disjoint Set List declaration **/
template<class T> class disjoint_set_rep;

/** Disjoint Set Node definition **/
template<class T> class disjoint_set_node {
private:
    T node_data;
    int node_rank;
    disjoint_set_node<T> * node_next;
    disjoint_set_rep<T> * node_rep;

public:
    explicit disjoint_set_node(T data): node_data(data), node_rank(0) {}

    void data(T new_data) { this->node_data = new_data; }
    T data() { return this->node_data; }

    void rank(int new_rank) { this->node_rank = new_rank; }
    int rank() { return this->node_rank; }

    void next(disjoint_set_node<T> * new_next) { this->node_next = new_next; }
    disjoint_set_node<T> * next() { return this->node_next; }

    void rep(disjoint_set_rep<T> * new_rep) { this->node_rep = new_rep; }
    disjoint_set_rep<T> * rep() { return this->node_rep; }
};

/** Disjoint Set Representative definition **/
template<class T> class disjoint_set_rep {
private:
    disjoint_set_node<T> * list_head;
    disjoint_set_node<T> * list_tail;

public:
    disjoint_set_rep() = default;
    explicit disjoint_set_rep(disjoint_set_node<T> * head): list_head(head), list_tail(head) {}

    void head(disjoint_set_node<T> * new_head) { this->list_head = new_head; }
    disjoint_set_node<T> * head() { return this->list_head; }

    void tail(disjoint_set_node<T> * new_tail) { this->list_tail = new_tail; }
    disjoint_set_node<T> * tail() { return this->list_tail; }
};

/** Disjoint Set definition **/
template<class T> class disjoint_set {
private:
    std::unordered_map<int, disjoint_set_node<T> *> set_nodes_addresses;

    void change_list_rep(disjoint_set_node<T> * list_head_node, disjoint_set_rep<T> * new_rep);
    void list_concat(disjoint_set_rep<T> * left_list, disjoint_set_rep<T> * right_list);

    disjoint_set_node<T> * find_node(int node_key);

    void link_set(disjoint_set_rep<T> * x_rep, disjoint_set_rep<T> * y_rep);

public:
    disjoint_set() = default;

    void make_set(int set_id, T node_data);

    disjoint_set_rep<T> * find_set(int set_id);
    disjoint_set_rep<T> * find_set(disjoint_set_node<T> * x);

    void union_set(disjoint_set_node<T> * x, disjoint_set_node<T> * y);
    void union_set(int x_id, int y_id);

    void print_set(int node_id);

};

/// Make Set
template<class T>
void disjoint_set<T>::make_set(int set_id, T node_data) {
    // New node rep because making a new set
    auto new_rep = new disjoint_set_rep<T>();

    // New node
    auto new_node = new disjoint_set_node<T>(node_data);

    // Setting new rep head and tail
    new_rep->head(new_node);
    new_rep->tail(new_node);

    // Setting node properties
    new_node->data(node_data);
    new_node->next(nullptr);
    new_node->rep(new_rep);

    // Putting node in the pool
    this->set_nodes_addresses[set_id] = new_node;
}

/// Find Set from id
template<class T>
disjoint_set_rep<T> * disjoint_set<T>::find_set(int set_id) {
    auto found_node = set_nodes_addresses[set_id];
    return found_node->rep();
}

/// Find set from set node
template<class T>
disjoint_set_rep<T> * disjoint_set<T>::find_set(disjoint_set_node<T> *x) {
    return x->rep();
}

/// Concat two disjoint set lists
template<class T>
void disjoint_set<T>::list_concat(disjoint_set_rep<T> * left_list, disjoint_set_rep<T> *right_list) {
    auto left_tail = left_list->tail();
    auto right_head = right_list->head();
    auto right_tail = right_list->tail();

    left_tail->next(right_head);
    left_list->tail(right_tail);
}

/// Change list rep
template<class T>
void disjoint_set<T>::change_list_rep(disjoint_set_node<T> * list_head_node, disjoint_set_rep<T> * new_rep) {
    while (list_head_node) {
        list_head_node->rep(new_rep);
        list_head_node = list_head_node->next();
    }
}

/// Find node from key
template<class T>
disjoint_set_node<T> * disjoint_set<T>::find_node(int node_key) {
    return set_nodes_addresses[node_key];
}

/// Link (union by rank)
template<class T>
void disjoint_set<T>::link_set(disjoint_set_rep<T> *x_rep, disjoint_set_rep<T> *y_rep) {
    auto x = x_rep->head();
    auto y = y_rep->head();

    if (x->rank() > y->rank()) {
        change_list_rep(y, x_rep);
        list_concat(x_rep, y_rep);
        delete y_rep;
    }
    else {
        change_list_rep(x, y_rep);
        list_concat(y_rep, x_rep);
        delete x_rep;
        if (x->rank() == y->rank()) {
            y->rank(y->rank() + 1);
        }
    }
}

/// Union from set node
template<class T>
void disjoint_set<T>::union_set(disjoint_set_node<T> *x, disjoint_set_node<T> *y) {
    link_set(find_set(x), find_set(y));
}

/// Union from node id
template<class T>
void disjoint_set<T>::union_set(int x_id, int y_id) {
    union_set(find_node(x_id), find_node(y_id));
}

template<class T>
void disjoint_set<T>::print_set(int node_id) {
    auto node = find_node(node_id);
    auto rep = node->rep();
    auto head = rep->head();

    while (head) {
        std::cout << " [" << head->data() << "] ";
        head = head->next();
    }
    std::cout << std::endl;
}




#endif //ASD_DISJOINTSET_H
