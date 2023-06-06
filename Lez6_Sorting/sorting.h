//
// Created by apont on 1/4/2023.
//

#ifndef ASD_SORTING_H
#define ASD_SORTING_H


#include <vector>

template <class T> class sorting {
public:
    // Insertion sort
    static void insertion_sort(std::vector<T> & v) {
        // First element is already sorted.
        for (auto j = 1; j < v.size(); j++) {
            // Checking where the j element belongs in the ordered subarray
            auto key = v.at(j);

            auto i = j-1;
            while (i >= 0 and v.at(i) > key) {
                // Swapping if v(i) > v(j)
                v.at(i+1) = v.at(i);
                i--;
            }

            // Swapping v(i+1) and v(j)
            v.at(i+1) = key;
        }
    }
};


#endif //ASD_SORTING_H
