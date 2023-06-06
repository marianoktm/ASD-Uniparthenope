//
// Created by apont on 1/2/2023.
//

#ifndef ASD_MANAGER_H
#define ASD_MANAGER_H


#include "employee.h"

class manager: public employee {
private:
    double bonus;

public:
    manager(std::string name, double salary, double bonus) : employee(name, salary) {
        this->bonus = bonus;
    }

    // Setters
    void set_bonus(double new_bonus) { this->bonus = new_bonus; }

    // Getters
    double get_salary() { return employee::get_salary() + this->bonus; }


};


#endif //ASD_MANAGER_H
