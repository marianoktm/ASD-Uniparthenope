//
// Created by apont on 12/30/2022.
//

#include "point.h"

/* 2D Point class methods implementation */

point::point(double _x, double _y) {
    this->x = _x;
    this->y = _y;
}

double point::getx() {
    return this->x;
}

double point::gety() {
    return this->y;
}

void point::setx(double _x) {
    this->x = _x;
}

void point::sety(double _y) {
    this->y = _y;
}


/* 3D Point class methods implementation */

point3D::point3D(double _x, double _y, double _z): point(_x, _y) {
    this->z = _z;
}

double point3D::getz() {
    return this->z;
}

void point3D::setz(double _z) {
    this->z = _z;
}
