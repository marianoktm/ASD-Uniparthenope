//
// Created by apont on 1/2/2023.
//
#include <iostream>
#include <fstream>
#include <string>
#include "rispettaiversichecker.h"

// Checks the number of arguments
bool argumentcheck(int argc) {
    if (argc == 1) {
        std::cout << "You must provide a filepath and filenames!" << std::endl;
        return false;
    } else if (argc == 2) {
        std::cout << "You must provide filenames!" << std::endl;
        return false;
    } else if (argc > 2 and argc < 4) {
        std::cout << "You must provide all filenames!" << std::endl;
        return false;
    }
    return true;
}


/**
 * @param argc
 * @param argv argv[1]: filepath, argv[2]: problema, argv[3]: soluzione
 * @return
 */
int main(int argc, char * argv[]) {
    // Argument check
    if (!argumentcheck(argc)) exit(-1);


    // Argument transformation
    std::string filepath(argv[1]);
    std::string problema(argv[2]);
    std::string soluzione(argv[3]);

    std::string problemapath = filepath + '\\' + problema;
    std::string soluzionepath = filepath + '\\' + soluzione;

    std::string esitoname = "Esito.txt";
    std::string esitopath = filepath + '\\' + esitoname;

    std::cout <<
    "Using parameters: " << std::endl <<
    "File Path: " << filepath << std::endl <<
    "Problema: " << problema << std::endl <<
    "Problema path: " << problemapath << std::endl <<
    "Soluzione: " << soluzione << std::endl <<
    "Soluzione path: " << soluzionepath << std::endl <<
    "Esito path: " << esitopath << std::endl;


    // Trying to open all files
    std::ifstream file_problema;
    file_problema.open(problemapath);
    if (file_problema.fail()) {
        std::cout << "Error opening " << problemapath << std::endl;
        return -1;
    }

    std::ifstream file_soluzione;
    file_soluzione.open(soluzionepath);
    if (file_soluzione.fail()) {
        std::cout << "Error opening " << soluzionepath << std::endl;
        file_problema.close();
        return -1;
    }

    std::ofstream file_esito;
    file_esito.open(esitopath, std::ios::app);
    if (file_esito.fail()) {
        std::cout << "Error opening " << esitopath << std::endl;
        file_problema.close();
        file_soluzione.close();
        return -1;
    }

    rispettaiversichecker checker(file_problema, file_soluzione, file_esito);
    checker.check();

    file_soluzione.close();
    file_problema.close();
    file_esito.close();

    return 0;
}

