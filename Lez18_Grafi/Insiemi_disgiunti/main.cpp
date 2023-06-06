//
// Created by apont on 2/28/2023.
//
#include <vector>
#include <iostream>

#include "disjointset.h"

void cout_helper_makeset();

int main() {
    disjoint_set<int> disjointSet;
    std::cout << ">>> First for sets: " << std::endl;
    for (int i = 1; i <= 16; i++) {
        disjointSet.make_set(i, i);
        disjointSet.print_set(i);
    }

    std::cout << ">>> Second for sets: " << std::endl;
    for (int i = 1; i <= 15; i=i+2) {
        disjointSet.union_set(i, i+1);
        disjointSet.print_set(i);
    }

    std::cout << ">>> Third for sets: " << std::endl;
    for (int i = 1; i <= 13; i=i+4) {
        disjointSet.union_set(i, i+2);
        disjointSet.print_set(i);
    }

    std::cout << ">>> First outer union sets: " << std::endl;
    disjointSet.union_set(1, 5);
    disjointSet.print_set(1);

    std::cout << ">>> Second outer union sets: " << std::endl;
    disjointSet.union_set(11, 13);
    disjointSet.print_set(11);

    std::cout << ">>> Third outer union sets: " << std::endl;
    disjointSet.union_set(1, 10);
    disjointSet.print_set(1);

    auto find1 = disjointSet.find_set(2);
    auto find2 = disjointSet.find_set(9);

    std::cout << ">>> Findset 2 and 9: " << std::endl;
    std::cout << find1->head()->data() << " " << find2->head()->data() << std::endl;

    std::cout << ">>> Printing whole set of 2 and 9: " << std::endl;
    disjointSet.print_set(2);
    disjointSet.print_set(9);
}