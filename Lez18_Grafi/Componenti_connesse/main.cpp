#include <fstream>
#include <algorithm>
#include "graph.h"

#include "graph.h"
#include "filereader.h"
#include "disjointset.h"


int main() {
    std::string filepath = R"(C:\Archive\Programming\CLion projects\ASD\src\Lez18_Graphs\connectedcomponents\)";
    std::string filename = "cc_graph.txt";

    auto new_filereader = new filereader(filepath + filename);
    auto G = new_filereader->generate_v_data();

    G->print_graph();

    auto set_pool = new disjointset_pool<graph_node<char>*>();

    int i = 0;
    for (auto v : G->getVertices()) {
        set_pool->make_set(i, v);
        i++;

    }

    set_pool->print_map();
    std::cout << set_pool->find_key_from_data(G->getVertices().at(1)) << std::endl;
    std::cout << set_pool->find_data_from_key(1)->getData() << std::endl;

    G->print_connected_components();

    return 0;
}