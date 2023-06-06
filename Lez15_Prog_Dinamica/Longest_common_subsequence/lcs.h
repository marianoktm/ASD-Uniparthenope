//
// Created by apont on 1/12/2023.
//

#ifndef ASD_LCS_H
#define ASD_LCS_H


#include <string>
#include <utility>
#include <vector>



class lcs {
private:
    std::string T;
    std::string S;

    int d_index(int idx) {return idx+1;}
    int ed_min(int v, int h, int d) { return std::min(v, std::min(h, d)); }

public:
    lcs(std::string T, std::string S): T(T), S(S) {};

    int calculate_distance();
};

int lcs::calculate_distance() {
    // Initialization
    int t_size = T.length();
    int s_size = S.length();

    int distance_arr[s_size+1][t_size+1];
    distance_arr[0][0] = 0;

    for (int col = 1; col <= t_size; ++col) { distance_arr[0][col] = col;}
    for (int row = 1; row <= s_size; ++row) { distance_arr[row][0] = row;}

    // Horizontal = insert, Vertical = Delete, Diagonal = substitution or match
    for (int i = 0; i < s_size; ++i) {
        for (int j = 0; j < t_size; ++j) {
            if (S.at(i) == T.at(j)) {
                distance_arr[d_index(i)][d_index(j)] = distance_arr[d_index(i-1)][d_index(j-1)];
            }
            else {
                int vertical_delete = distance_arr[d_index(i - 1)][d_index(j)];
                int horizontal_insert = distance_arr[d_index(i)][d_index(j - 1)];
                int diagonal_substitute = distance_arr[d_index(i - 1)][d_index(j - 1)];

                distance_arr[d_index(i)][d_index(j)] = 1 + ed_min(vertical_delete, horizontal_insert, diagonal_substitute);
            }
        }
    }

    return distance_arr[s_size-1][t_size-1];
}




#endif //ASD_LCS_H
