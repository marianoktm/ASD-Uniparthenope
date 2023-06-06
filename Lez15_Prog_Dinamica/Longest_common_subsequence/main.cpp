//
// Created by apont on 1/12/2023.
//

#include <string>
#include <iostream>
#include "lcs.h"

int main() {
    std::string T = "TGCATA";
    std::string S = "ATCTGAT";

    lcs ed(T, S);

    std::cout << ed.calculate_distance() << std::endl;

    return 0;
}

