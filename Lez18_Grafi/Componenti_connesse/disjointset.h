#ifndef ASD_DISJOINTSET_H
#define ASD_DISJOINTSET_H

#include <unordered_map>
#include <algorithm>
#include <iostream>

#define setnodeptr set_node<T> *
#define setitemptr set_item<T> *
#define tpt template<class T>

tpt class set_item;



/** Set Node class **/
tpt class set_node {
private:
    T data;
    int rank;
    setnodeptr next;
    setitemptr set;

public:
    // Constructors
    set_node() = default;
    explicit set_node(T new_data): data(new_data), rank(0), next(nullptr), set(nullptr) {}

    // Data setters and getters
    void setData(T new_data) { this->data = new_data; }
    T getData() { return this->data; }

    // Next setters and getters
    void setNext(setnodeptr new_next) { this->next = new_next; }
    setnodeptr getNext() { return this->next; }

    // Set item setters and getters
    void setSet(setitemptr new_set) { this->set = new_set; }
    setitemptr getSet() { return this->set; }

    // Rank setters and getters
    void setRank(int new_rank) { this->rank = new_rank; }
    int getRank() { return this->rank; }

    //Equality operator
    bool operator==(set_node<T> & comp) const { return comp.data == data and comp.next == next; }

    //Stream operator
    friend std::ostream &operator<<(std::ostream &os, const set_node &node) {
        os << "data: " << node.data;
        return os;
    }
};



/** Set Head (representative) class**/
tpt class set_item {
private:
    setnodeptr head;
    setnodeptr tail;

public:
    set_item() = default;
    explicit set_item(setnodeptr new_head, setnodeptr new_tail): head(new_head), tail(new_tail) {}

    void setHead(setnodeptr new_head) { this->head = new_head; }
    setnodeptr getHead() { return this->head; }

    void setTail(setnodeptr new_tail) { this->tail = new_tail; }
    setnodeptr getTail() { return this->tail; }
};



/** Disjoint set pool class for contextual uses **/
tpt class disjointset_pool {
private:
    std::unordered_map<int, setnodeptr> nodeMap;
    std::unordered_map<setnodeptr, int> nodeIdMap;

    void link(setitemptr x, setitemptr y);
    void insert_node_in_maps(int key, setnodeptr node);

    void change_whole_list_rep(setnodeptr list_head, setitemptr new_rep) {
        auto curr = list_head;
        while (curr) {
            curr->setSet(new_rep);
            curr = curr->getNext();
        }
    }
    void concat_lists(setitemptr x_left, setitemptr y_right) {
        auto xtail = x_left->getTail();
        auto ytail = y_right->getTail();
        auto yhead = y_right->getHead();

        xtail->setNext(yhead);
        x_left->setTail(ytail);
    }

public:
    disjointset_pool() = default;

    void make_set(int key, T new_data);
    void union_set(setnodeptr x, setnodeptr y);
    void union_set_from_data(T xdata, T ydata);
    set_item<T> * find_set_from_key(int xkey);
    set_item<T> * find_set_from_setnode(setnodeptr xnode);
    set_item<T> * find_set_from_nodedata(T xdata);

    int find_key_from_data(T set_node_data);
    int find_key_from_node(setnodeptr node);
    setnodeptr find_node_from_key(int key);
    T find_data_from_key(int key);

    void print_map();

};


/// Insert node in maps helper function
tpt void disjointset_pool<T>::insert_node_in_maps(int key, setnodeptr node) {
    nodeMap[key] = node;
    nodeIdMap[node] = key;
}

/// Prints the map
tpt void disjointset_pool<T>::print_map() {
    for (auto & elem : nodeMap) {
        std::cout << "Id: " << elem.first << " Data: " << elem.second->getData()->getData();
        std::cout << " Rep: " << elem.second->getSet()->getHead()->getData()->getData() << std::endl;
    }
}

/// Make Set definition
tpt void disjointset_pool<T>::make_set(int key, T new_data) {
    // New node
    auto newnode = new set_node<T>(new_data);
    newnode->setData(new_data);

    // New set item
    auto newset = new set_item<T>(newnode, newnode);
    newnode->setSet(newset);

    insert_node_in_maps(key, newnode);
}

/// Finds map key from data in the node
tpt int disjointset_pool<T>::find_key_from_data(T set_node_data) {
    for (auto & elem : nodeMap) {
        if (elem.second->getData() == set_node_data) {
            return elem.first;
        }
    }
    return -1;
}

/// Finds the key from the set node
tpt int disjointset_pool<T>::find_key_from_node(set_node<T> * node) {
    return nodeIdMap[node];
}

/// Finds the set node from the key
tpt set_node<T> *disjointset_pool<T>::find_node_from_key(int key) {
    return nodeMap[key];
}

/// Finds the set node content from the key
tpt T disjointset_pool<T>::find_data_from_key(int key) {
    return find_node_from_key(key)->getData();
}

/// Find set from set node
tpt set_item<T> *disjointset_pool<T>::find_set_from_setnode(set_node<T> *xnode) {
    return xnode->getSet();
}

/// Find set from key
tpt set_item<T> * disjointset_pool<T>::find_set_from_key(int xkey) {
    auto node = find_node_from_key(xkey);
    return find_set_from_setnode(node);
}

/// Find set from node data
tpt set_item<T> * disjointset_pool<T>::find_set_from_nodedata(T xdata) {
    auto key = find_key_from_data(xdata);
    return find_set_from_key(key);
}

/// Link (union by rank)
tpt void disjointset_pool<T>::link(set_item<T> *x, set_item<T> *y) {
    auto xhead = x->getHead();
    auto yhead = y->getHead();
    auto xtail = x->getTail();
    auto ytail = y->getTail();

    if (xhead->getRank() > yhead->getRank()) {
        change_whole_list_rep(yhead, x);
        concat_lists(x, y);
        delete y;
    }
    else {
        change_whole_list_rep(xhead, y);
        concat_lists(y, x);
        if (yhead->getRank() == xhead->getRank()) {
            yhead->setRank(yhead->getRank() + 1);
        }
        delete x;
    }
}

/// Union (helped by link)
tpt void disjointset_pool<T>::union_set(set_node<T> *x, set_node<T> *y) {
    link(find_set_from_setnode(x), find_set_from_setnode(y));
}

/// Union from data
tpt void disjointset_pool<T>::union_set_from_data(T xdata, T ydata) {
    auto repx = find_set_from_nodedata(xdata);
    auto repy = find_set_from_nodedata(ydata);

    link(repx, repy);
}

#endif //ASD_DISJOINTSET_H
