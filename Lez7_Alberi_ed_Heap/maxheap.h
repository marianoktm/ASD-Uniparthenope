//
// Created by apont on 1/6/2023.
//

#ifndef ASD_MAXHEAP_H
#define ASD_MAXHEAP_H


#include <vector>
#include <iostream>

template<class T> class maxheap {
protected:
    std::vector<T> dataset;
    int heapsize;
public:
    const std::vector<T> &getDataset() const;

    void setDataset(const std::vector<T> &dataset);

    int getHeapsize() const;

    void setHeapsize(int heapsize);

    bool isIsheap() const;

    void setIsheap(bool isheap);

protected:
    bool isheap;

    int parent(int i);
    int left(int i);
    int right(int i);

public:
    maxheap() {
        this->heapsize = 0;
        this->isheap = true;
    }

    maxheap(std::vector<T> newdataset);

    void build_heap();
    virtual void heapify(int i);
    void insert(T data);

    void print_tree();
    void print_array();

    virtual bool check_max_heap() final;
    void heapsort_swap(int i, int j);

    T heapmax() { return dataset.at(0); }
    T heap_extract_max();
};

/* maxheap functions */
// Parent
template<class T>
 int maxheap<T>::parent(int i) {
    return (i-1) / 2;
}

// Left
template<class T>
 int maxheap<T>::left(int i) {
    return (2*i)+1;
}

// Right
template<class T>
 int maxheap<T>::right(int i) {
    return (2*i)+2;
}

// Heapify as max
template<class T>
void maxheap<T>::heapify(int i) {
    int max_i = i;
    int left_i = left(i);
    int right_i = right(i);
    

    // Check if left element is greater than i element
    if (left_i < heapsize and dataset.at(left_i) > dataset.at(max_i))
        max_i = left_i;

    // Check if right element is greater than i element
    if (right_i < heapsize and dataset.at(right_i) > dataset.at(max_i))
        max_i = right_i;

    // Swap max index if radix is not the greater one and re-check heap property
    if (max_i != i) {
        std::swap(dataset.at(i), dataset.at(max_i));
        heapify(max_i);
    }

    this->isheap = true;
}

// Builds an heap applying heapify to all nodes (as max heap)
template<class T>
void maxheap<T>::build_heap() {
    this->heapsize = dataset.size();

    for (int j = (heapsize / 2) - 1; j >= 0; j--) {
        heapify(j);
    }
}

// Inserts a node in the heap
template<class T>
void maxheap<T>::insert(T data) {
    // Pushes the node as a leaf and increases heap size
    dataset.push_back(data);
    heapsize++;

    // Checks if heapify is granted on the new node
    if (heapsize > 1) heapify(heapsize - 1);
}

// Prints the array
template<class T>
void maxheap<T>::print_array() {
    for (auto x : dataset) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}

// Prints the tree
template<class T>
void maxheap<T>::print_tree() {
    for (int i = 0; i <= heapsize/2 - 1; i++) {
        std::cout << "[Node " << i << "]: ";
        std::cout << "Root: " << dataset.at(i) << "; ";
        if (left(i) < heapsize) std::cout << "Left: " << dataset.at(left(i)) << "; ";
        if (right(i) < heapsize) std::cout << "Right: " << dataset.at(right(i)) << ".";
        std::cout << std::endl;
    }
}

template<class T>
maxheap<T>::maxheap(std::vector<T> newdataset) {
    this->dataset = newdataset;
    this->heapsize = 0;
    this->isheap = false;
}

template<class T>
bool maxheap<T>::check_max_heap() {
    for (int i = 0; i < heapsize / 2; ++i) {
        if (left(i) < heapsize) if (dataset.at(i) < dataset.at(left(i))) return false;
        if (right(i) < heapsize) if (dataset.at(i) < dataset.at(right(i))) return false;
    }

    return true;
}

template<class T>
const std::vector<T> &maxheap<T>::getDataset() const {
    return dataset;
}

template<class T>
void maxheap<T>::setDataset(const std::vector<T> &dataset) {
    maxheap::dataset = dataset;
}

template<class T>
int maxheap<T>::getHeapsize() const {
    return heapsize;
}

template<class T>
void maxheap<T>::setHeapsize(int heapsize) {
    maxheap::heapsize = heapsize;
}

template<class T>
bool maxheap<T>::isIsheap() const {
    return isheap;
}

template<class T>
void maxheap<T>::setIsheap(bool isheap) {
    maxheap::isheap = isheap;
}

template<class T>
void maxheap<T>::heapsort_swap(int i, int j) {
    std::swap(dataset.at(i), dataset.at(j));
}

template<class T>
T maxheap<T>::heap_extract_max() {
    if (heapsize == 0)
        return nullptr;

    T max = dataset.at(0);
    std::swap(dataset.at(0), dataset.at(heapsize-1));
    heapsize--;
    heapify(0);

    return max;
}




#endif //ASD_MAXHEAP_H
