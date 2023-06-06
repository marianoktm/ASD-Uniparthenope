//
// Created by apont on 1/6/2023.
//

#include <utility>

#include "maxheap.h"
#include "minheap.h"

std::vector<int> heapsort(std::vector<int> v) {
    maxheap<int> heap(std::move(v));
    heap.build_heap();

    for (int i = (int) heap.getDataset().size() - 1; i >= 0; i--) {
        heap.heapsort_swap(0, i);
        heap.setHeapsize(heap.getHeapsize()-1);
        heap.heapify(0);
    }

    return heap.getDataset();
}


int main() {
    std::vector<int> vctr = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};

    maxheap<int> heap(vctr);
    heap.print_array();
    heap.build_heap();
    heap.print_tree();

    minheap<int> minheap(vctr);
    minheap.print_array();
    minheap.build_heap();
    minheap.print_tree();

    vctr = heapsort(vctr);
    for (auto x : vctr) std::cout << x << " ";
    std::cout << std::endl;

    return 0;
}

