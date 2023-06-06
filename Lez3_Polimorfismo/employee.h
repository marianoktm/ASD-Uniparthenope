//
// Created by apont on 1/2/2023.
//

#ifndef ASD_EMPLOYEE_H
#define ASD_EMPLOYEE_H


#include <string>

class employee {
private:
    std::string name;
    double salary;

public:
    employee(std::string _name, double _salary) {
        this->name = _name;
        this->salary = _salary;
    }

    // Setters
    void set_name(std::string new_name) { this->name = new_name; }

    void set_salary(double new_salary) { this->salary = new_salary; }

    // Getters
    std::string get_name() { return this->name; }

    virtual double get_salary() { return this->salary; }

    // Operators
    double operator+(employee a) {
        return a.get_salary();
    }

};


#endif //ASD_EMPLOYEE_H
