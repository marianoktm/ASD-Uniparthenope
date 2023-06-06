//
// Created by apont on 2/27/2023.
//

#include "includes.h"
#include "graph.h"

void vctr_buf_build(std::ifstream & file, std::vector<char> & vertex_buf, std::vector<char> & edges_src_buf, std::vector<char> & edges_dest_buf) {
    char src_node;
    char dest_node;

    while (file) {
        file >> src_node;
        file >> dest_node;

        if (std::find(vertex_buf.begin(), vertex_buf.end(), src_node) == vertex_buf.end()) {
            vertex_buf.push_back(src_node);
            std::cout << "Pushed back on vertex_buf " << src_node << std::endl;
        }
        if (std::find(vertex_buf.begin(), vertex_buf.end(), dest_node) == vertex_buf.end()) {
            vertex_buf.push_back(dest_node);
            std::cout << "Pushed back on vertex_buf " << dest_node << std::endl;
        }

        edges_src_buf.push_back(src_node);
        std::cout << "Pushed back on edges_src_buf " << src_node << std::endl;
        edges_dest_buf.push_back(dest_node);
        std::cout << "Pushed back on edges_dest_buf " << src_node << std::endl;
    }
}

vertex<char> * find_node(std::vector<vertex<char> *> & V, char key) {
    for (auto v : V) {
        if (v->data() == key) {
            return v;
        }
    }
    return nullptr;
}

void build_graph_vectors(std::ifstream & file, std::vector<vertex<char> *> & V) {
    std::vector<char> vertex_buf;
    std::vector<char> src_buf;
    std::vector<char> dest_buf;

    vctr_buf_build(file, vertex_buf, src_buf, dest_buf);

    for (auto v : vertex_buf) {
        auto newvertex = new vertex<char>(v);
        V.push_back(newvertex);
        std::cout << "Pushed back on V a vertex with data: " << newvertex->data() << std::endl;
    }

    for (int i = 0; i < src_buf.size(); ++i) {
        auto src_node = find_node(V, src_buf.at(i));
        std::cout << "Found src_node " << src_node->data() << std::endl;
        auto dest_node = find_node(V, dest_buf.at(i));
        std::cout << "Found dest_node " << dest_node->data() << std::endl;

        src_node->push_to_adj(dest_node);
        std::cout << "Pushed back " << dest_node->data() << " on " << src_node->data() << std::endl;
    }
}

int main() {
    std::string filepath = R"(C:\Archive\Programming\CLion projects\ASD\src\Lez18_Graphs\DFS_BFS\)";
    std::ifstream input_file(filepath + "graph.txt");

    std::cout << "opening file in " << filepath + "graph.txt" << std::endl;

    std::vector<vertex<char> *> V;

    if (input_file.is_open())
        build_graph_vectors(input_file, V);
    else
        return -1;

    input_file.close();

    graph<char> G(V);

    G.print_all_adj();
    G.DFS();
    G.BFS('A');

    return 0;
}
