//
// Created by apont on 1/4/2023.
//

#ifndef ASD_LEZ6ES_H
#define ASD_LEZ6ES_H


#include <vector>
#include <map>
#include "sorting.h"

class lez6es {
private:
    int i;

public:
    // Find k-th bigger number. k WORKS LIKE AN INDEX!!!
    static std::pair<int, int> k_bigger(std::vector<int> v, int k) {
        sorting<int>::insertion_sort(v);

        auto it = v.rbegin();
        auto kbigger = *it;
        auto kbigger_index = std::distance(it, v.rbegin());

        while (std::next(it) != v.rend() and kbigger_index < k) {
            std::cout << "Comparing: " << *it << " < " << *std::next(it) << std::endl;
            if (*it < *std::next(it)) {
                kbigger = *std::next(it);
                kbigger_index++;
            }
            std::advance(it, 1);
        }

        return *new std::pair<int, int>(kbigger_index, kbigger);
    }

    static void delete_duplicates(std::vector<int> & v) {
        sorting<int>::insertion_sort(v);

        for (auto it_left = v.begin(); it_left < std::prev(v.end()); std::advance(it_left, 1)) {
            for (auto it_right = std::next(it_left); it_right < v.end(); std::advance(it_right, 1)) {
                if (*it_left == *it_right) {
                    v.erase(it_right);
                    it_right = it_left;
                }
                if ((*it_left < *it_right)) break;
            }
        }
    }



};


#endif //ASD_LEZ6ES_H
