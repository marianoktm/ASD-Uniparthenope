#include <iostream>
#include <fstream>
#include <string>

#include <chrono>
#include <thread>


class readers {
private:
    static void read_from_file1(std::istream & fileread) {
        char ch;
        while (fileread.get(ch))
            std::cout << ch;
        std::cout << std::endl;
    }

public:
    static void read_from_file(std::ifstream & fileread) {
        read_from_file1(fileread);
    }

    static void read_from_file(std::fstream & fileread) {
        read_from_file1(fileread);
    }

    static void read_words_from_fstream(std::fstream & file) {
        file.seekg(std::ios::beg);
        std::string word;
        while (file >> word) {
            std::cout << word;
        }
        std::cout << std::endl;
    }

    static void read_all_lines(std::fstream & file) {
        std::string read_buffer;
        while (getline(file, read_buffer)) {
            std::cout << read_buffer << std::endl;
        }
    }

};

void easycout(const std::string& str) {
    std::cout << str << std::endl;
}

int main() {
    std::string path = R"(file1.txt)";


    // Output file stream
    easycout(">> OUTPUT FILE STREAM");
    std::ofstream filewrite;
    filewrite.open(path.c_str());
    filewrite << "Test!!!" << std::endl;
    filewrite.close();


    // Input file stream
    easycout(">> INPUT FILESTREAM");
    std::ifstream fileread;
    fileread.open(path.c_str());
    readers::read_from_file(fileread);
    fileread.close();


    // Opening a generic file reference
    easycout(">> OPENING GENERIC REFERENCE");
    std::fstream file;

    // Writing
    easycout(">> WRITING USING GENERIC REFERENCE");
    file.open(path.c_str(), std::ios::out); // Only write
    file << "Only writing to file..." << std::endl;
    file.close();

    // Reading
    easycout(">> READING FROM GENERIC REFERNECE");
    file.open(path.c_str(), std::ios::in | std::ios::out); // Read and write
    readers::read_from_file(file);
    file.close();


    // Append mode
    easycout(">> APPEND MODE WRITE AND READ");
    file.open(path.c_str(), std::ios::in | std::ios::out | std::ios::app);

    file << "Adding a line..." << std::endl;
    file << "Adding another line..." << std::endl;

    readers::read_words_from_fstream(file);

    file.close();


    // Reading with getline and open fail check
    easycout(">> READING WITH GETLINE AND OPEN FAIL CHECK");
    std::fstream opts;
    opts.open(path, std::ios::in | std::ios::out | std::ios::app);
    if (opts.fail()) {
        std::cout << "An error occurred while opening " << path << std::endl;
    }
    else {
        readers::read_all_lines(opts);
    }

    opts.close();

    // Stringstream test


    return 0;
}
