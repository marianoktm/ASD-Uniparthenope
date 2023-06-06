#include <utility>

//
// Created by apont on 3/2/2023.
//

#ifndef ASD_FILEREADER_H
#define ASD_FILEREADER_H

#include <fstream>
#include <algorithm>
#include "graph.h"

#define chvct std::vector<char>

/** Class for generating a vector of chars for a graph **/
class filereader {
private:
    std::string filepath;
    std::ifstream file;

    void generate_buffers(chvct & allnodes, chvct & sources, chvct & dests);
    static bool not_found(chvct & vct, char elem);

public:
    explicit filereader(std::string newfilepath): filepath(std::move(newfilepath)) { file.open(filepath); }

    graph<char> * generate_v_data();

};


/// generates vector buffers from file
void filereader::generate_buffers(std::vector<char> &allnodes, std::vector<char> &sources, std::vector<char> &dests) {
    char src;
    char dst;

    int i = 0;
    while (file) {
        std::cout << "ITERATION N: " << i++ << std::endl;
        file >> src;
        std::cout << "filereader read src: " << src << std::endl;
        if (std::find(allnodes.begin(), allnodes.end(), src) == allnodes.end()) {
            allnodes.push_back(src);
            std::cout << "filereader pushback on allnodes: " << src << std::endl;
        }

        if (file) {
            file >> dst;
            std::cout << "filereader read dest: " << dst << std::endl;
            if (std::find(allnodes.begin(), allnodes.end(), dst) == allnodes.end()) {
                allnodes.push_back(dst);
                std::cout << "filereader pushback on allnodes: " << dst << std::endl;
            }
        }


        sources.push_back(src);
        std::cout << "filereader pushback on sources: " << src << std::endl;
        if (file) {
            dests.push_back(dst);
            std::cout << "filereader pushback on dests: " << dst << std::endl;
        }
    }
}


/// generates V
graph<char> * filereader::generate_v_data() {
    auto out_graph = new graph<char>();
    chvct allnodes;
    chvct sources;
    chvct dests;

    if (file.is_open()) {
        generate_buffers(allnodes, sources, dests);
    }
    else {
        std::cerr << "Error reading the file" << std::endl;
        return nullptr;
    }

    for (char allnode : allnodes) {
        out_graph->addVertex(new graph_node<char>(allnode));
    }

    for (int i = 0; i < dests.size(); i++) {
        auto src = out_graph->findNodeFromData(sources.at(i));
        auto dst = out_graph->findNodeFromData(dests.at(i));

        src->pushOnAdj(dst);
    }

    return out_graph;
}




#endif //ASD_FILEREADER_H
