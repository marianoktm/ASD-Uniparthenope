//
// Created by apont on 1/7/2023.
//

#ifndef ASD_MINHEAP_H
#define ASD_MINHEAP_H


#include "maxheap.h"

template <class T> class minheap: public maxheap<T> {
public:
    minheap() = default;
    explicit minheap(std::vector<T> newdataset);

    void heapify(int i);

    virtual T find_sum_min_x(int x) final;
};

template<class T>
void minheap<T>::heapify(int i) {
    int max_i = i;
    int left_i = maxheap<T>::left(i);
    int right_i = maxheap<T>::right(i);


    // Check if left element is greater than i element
    if (left_i < maxheap<T>::heapsize and maxheap<T>::dataset.at(left_i) < maxheap<T>::dataset.at(max_i))
        max_i = left_i;

    // Check if right element is greater than i element
    if (right_i < maxheap<T>::heapsize and maxheap<T>::dataset.at(right_i) < maxheap<T>::dataset.at(max_i))
        max_i = right_i;

    // Swap max index if radix is not the greater one and re-check heap property
    if (max_i != i) {
        std::swap(maxheap<T>::dataset.at(i), maxheap<T>::dataset.at(max_i));
        heapify(max_i);
    }

    this->isheap = true;
}

template<class T>
minheap<T>::minheap(std::vector<T> newdataset): maxheap<T>(newdataset) {}

template<class T>
T minheap<T>::find_sum_min_x(int x) {
    // If dataset[i] is a leaf or it would cause a segfault
    if (x > (this->heapsize/2) - 1) return 0;

    for (int i = x; i < (this->heapsize / 2) - 1; i++) {
        return 1;
    }
}

#endif //ASD_MINHEAP_H
