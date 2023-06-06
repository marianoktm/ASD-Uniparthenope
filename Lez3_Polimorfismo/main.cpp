//
// Created by apont on 1/2/2023.
//

#include <list>
#include <iostream>
#include "employee.h"
#include "manager.h"

int main() {
    std::list<employee *> employees_list;

    employees_list.push_back(new employee("Gennaro", 100));
    employees_list.push_back(new employee("Antonio", 400));
    employees_list.push_back(new manager("Aurelio", 300, 200));

    for (auto empl : employees_list) {
        std::cout << empl->get_name() << " " << empl->get_salary() << std::endl;
    }
}
