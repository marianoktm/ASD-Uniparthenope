//
// Created by apont on 1/2/2023.
//

#ifndef ASD_RISPETTAIVERSICHECKER_H
#define ASD_RISPETTAIVERSICHECKER_H

#define BUFFERSIZE 1024

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

class rispettaiversichecker {
private:
    std::ifstream * solutionfile;
    std::ifstream * problemfile;
    std::ofstream * resultfile;

    // Returns a list of ints of the current line
    std::vector<int> * get_int_list (char * line) {
        auto * out = new std::vector<int>();
        std::string linestr(line);
        std::string int_to_convert;


        for (int i = 0; i < linestr.size(); i++) {
            char currentchar;
            currentchar = linestr.at(i);
            if ((currentchar >= 48 and currentchar <= 57) or currentchar == '-') {
                int_to_convert.push_back(currentchar);
            }
            if (currentchar == '>' or currentchar == '<' or i == linestr.size()-1) {
                out->push_back(std::stol(int_to_convert));
                int_to_convert = "";
            }
            std::cout << "Int to convert at step " << i << ": " << int_to_convert << std::endl;
        }

        return out;
    }

    // Prints an int vector
    void print_int_vector(const std::vector<int> * v) {
        for (auto & i : *v) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    // Checks whether the solution is wrong or correct
    bool check_solution(const std::string & problemline, std::vector<int> * int_list) {
        for (int i = 0; i < problemline.size(); i++) {
            if (problemline.at(i) == '>') {
                if (!greater_than(int_list->at(i), int_list->at(i+1))) return false;
            }
            else if (problemline.at(i) == '<') {
                if (!smaller_than(int_list->at(i), int_list->at(i+1))) return false;
            }
        }
        return true;
    }

    // checks if a > b
    bool greater_than(int a, int b) {
        if (a > b) return true;
        else return false;
    }

    // checks if a < b
    bool smaller_than(int a, int b) {
        if (a < b) return true;
        else return false;
    }


public:
    rispettaiversichecker(std::ifstream & problem, std::ifstream & solution, std::ofstream & result) {
        this->problemfile = &problem;
        this->solutionfile = &solution;
        this->resultfile = &result;
    }

    void check() {
        char problemline[BUFFERSIZE];
        char solutionline[BUFFERSIZE];

        while (!problemfile->eof() and !solutionfile->eof()) {
            // Getting lines
            problemfile->getline(problemline, BUFFERSIZE);
            solutionfile->getline(solutionline, BUFFERSIZE);

            std::cout <<
            "EXTRACTED: " << std::endl <<
            problemline << std::endl <<
            solutionline << std::endl;

            // Extracting all integers in the line
            std::vector<int> * int_list = get_int_list(solutionline);
            std::cout << "Integers in this line: ";
            print_int_vector(int_list);

            if (check_solution(problemline, int_list)) {
                *resultfile << "Corretto!" << std::endl;
            }
            else {
                *resultfile << "Errato!" << std::endl;
            }

            delete int_list;
        }
    }

};


#endif //ASD_RISPETTAIVERSICHECKER_H
