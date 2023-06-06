//
// Created by apont on 1/12/2023.
//

#include "knapsack.h"

int main() {

    knapsack_problem problem(
            {3, 4, 5, 6},
            {2, 3, 4, 5});

    knapsack k(problem, 5);

    k.solve();

    return 0;
}