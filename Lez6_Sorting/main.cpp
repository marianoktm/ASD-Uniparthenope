//
// Created by apont on 1/4/2023.
//
#include <iostream>
#include "sorting.h"
#include "lez6es.h"

void print(std::vector<int> v) {
    for (auto i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> v = {32, 43, 43, 55, 55, 55, 22, 22, 22, 2, 12, 3, 22, 1, 1, 34};
    print(v);

    std::cout << "3rd bigger of v: " << lez6es::k_bigger(v, 3).second << std::endl;

    sorting<int>::insertion_sort(v);

    print(v);

    lez6es::delete_duplicates(v);

    print(v);

    return 0;
}

