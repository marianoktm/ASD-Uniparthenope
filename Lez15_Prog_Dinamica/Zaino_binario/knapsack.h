//
// Created by apont on 1/12/2023.
//

#ifndef ASD_KNAPSACK_H
#define ASD_KNAPSACK_H

#include <vector>
#include <iostream>

class knapsack_problem {
public:
    std::vector<int> value;
    std::vector<int> weight;

    knapsack_problem(std::vector<int> v, std::vector<int> w): value(v), weight(w) {};
};

class knapsack {
private:
    knapsack_problem object;
    int capacity_W = 0;


    int obj_idx(int i) {return i-1;}

public:
    knapsack(knapsack_problem p, int W): object(p), capacity_W(W) {};

    void solve();
};

void knapsack::solve() {
    /* Actual Knapsack Algorithm */
    int num_of_objects = object.value.size();

    int V[num_of_objects+1][capacity_W+1];
    for (int i = 0; i <= num_of_objects; i++) V[i][0] = 0;
    for (int w = 0; w <= capacity_W; w++) V[0][w] = 0;

    // V[i][w] = max between V[i-1][w] and V[i-1][w-w[i] + value[i]
    for (int i = 1; i <= num_of_objects; i++) {
        // Checking for each capacity up to W
        for (int w = 1; w <= capacity_W; w++) {
            // If the object weights more than the current weight, it can't be taken.
            if (w < object.weight.at(obj_idx(i)))
                V[i][w] = V[i-1][w];
            // Else pick the previous solution
            else
                V[i][w] = std::max(V[i-1][w], V[i-1][w - object.weight[i-1]] + object.value[i-1]);
        }
    }

    /* Matrix Print */
    for (int i = 0; i < num_of_objects+1; i++) {
        for (int j = 0; j < capacity_W+1; j++) {
            std::cout << V[i][j] << "\t\t";
        }
        std::cout << std::endl;
    }


    std::cout << std::endl;


    /* Which to pick */
    int to_pick_idx[num_of_objects];

    int row_i = num_of_objects+1;
    int col_j = capacity_W+1;
    while (V[row_i][col_j] != 0 and row_i > 0 and col_j > 0) {
        if (V[row_i][col_j] == V[row_i-1][col_j]) {
            to_pick_idx[row_i-1] = 0;
            row_i--;
        }
        else if (V[row_i][col_j] == V[row_i][col_j-1]) {
            col_j--;
        }
        else {
            to_pick_idx[row_i-1] = 1;
            row_i--;
            col_j--;
        }
    }

    for (int i : to_pick_idx)
        std::cout << i << "\t";
    std::cout << std::endl;
}


#endif //ASD_KNAPSACK_H
