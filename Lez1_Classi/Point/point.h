//
// Created by apont on 12/30/2022.
//

#ifndef ASD_POINT_H
#define ASD_POINT_H


/* 2D Point class */
class point {
private:
    double x;
    double y;

public:
    point(double _x = 0, double _y = 0);

    double getx();
    double gety();
    void setx(double _x);
    void sety(double _y);
};


/* 3D Point class */
class point3D: public point {
private:
    double z;

public:
    point3D(double _x = 0, double _y = 0, double _z = 0);

    double getz();
    void setz(double _z);
};

#endif //ASD_POINT_H
