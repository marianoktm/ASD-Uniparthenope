//
// Created by apont on 1/7/2023.
//

#ifndef ASD_MAXPRIORITYQUEUE_H
#define ASD_MAXPRIORITYQUEUE_H

#include <vector>

#include "maxheap.h"

/* Node of a max priority queue, holding a priority and satellite data */
template<class T> class mpqnode {
private:
    int priority;
    T data;

public:
    int getPriority() const { return priority; }
    void setPriority(int priority) { mpqnode::priority = priority; }

    T getData() const { return data; }
    void setData(T data) { mpqnode::data = data; }

    bool operator==(const mpqnode &rhs) const { return priority == rhs.priority; }
    bool operator!=(const mpqnode &rhs) const { return rhs != *this; }

    bool operator<(const mpqnode &rhs) const { return priority < rhs.priority; }
    bool operator>(const mpqnode &rhs) const { return rhs < *this; }
    bool operator<=(const mpqnode &rhs) const { return rhs >= *this; }
    bool operator>=(const mpqnode &rhs) const { return *this >= rhs; }
};

/* Actual max priority queue. It's basically a max heap with some fancy functions */
template<class T> class maxpriorityqueue: public maxheap<mpqnode<T>> {
public:
    void increase_key(int i, int newkey);
};

/* Max priority queue methods */
template<class T>
void maxpriorityqueue<T>::increase_key(int i, int newkey) {
    if (i >= this->heapsize or this->dataset.at(i).getPriority() >= newkey)
        return;
    this->dataset.at(i).setPriority(newkey);

    if (this->heapsize > 1) heapify(this->heapsize - 1);
}


#endif //ASD_MAXPRIORITYQUEUE_H
