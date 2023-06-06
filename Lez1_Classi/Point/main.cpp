//
// Created by apont on 12/30/2022.
//
#include <iostream>
#include "point.h"

int main() {
    auto * point = new class point3D(2, 3, 4);
    std::cout << point->getx() << " " << point->gety() << " " << point->getz() << std::endl;
    delete point;

    return 0;
}

