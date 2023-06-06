#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <unordered_map>

#include "graph.h"

using namespace std;

graph<int> * graph_from_file(ifstream & file) {
    /// Reading n of nodes and edges
    int n_nodes;
    file >> n_nodes;
    int m_edges;
    file >> m_edges;
    cout << "Graph has " << n_nodes << " nodes and " << m_edges << " edges." << endl;

    cout << endl;

    /// Reading actual nodes data and edges data
    int curr_src;
    int curr_dst;
    int curr_w;
    vector<int> nodes;
    unordered_map<int, int> node_to_i_map;
    vector<pair<pair<int, int>, int>> edges; // edges.first.first = src, edges.first.second = dst, edges.second = w
    while (file.good()) {
        // Reading from file
        file >> curr_src;
        cout << "current src is " << curr_src << endl;
        file >> curr_dst;
        cout << "current dst is " << curr_dst << endl;
        file >> curr_w;
        cout << "current w is " << curr_w << endl;

        // Checking if node is new or not
        if (find(nodes.begin(), nodes.end(), curr_src) == nodes.end()) {
            nodes.push_back(curr_src);
            cout << "new node found: " << curr_src << endl;
            node_to_i_map[curr_src] = nodes.size() - 1;
            cout << "mapped " << curr_src << " to " << node_to_i_map[curr_src] << endl;
        }
        if (find(nodes.begin(), nodes.end(), curr_dst) == nodes.end()) {
            nodes.push_back(curr_dst);
            cout << "new node found: " << curr_dst << endl;
            node_to_i_map[curr_dst] = nodes.size() - 1;
            cout << "mapped " << curr_dst << " to " << node_to_i_map[curr_dst] << endl;
        }

        // Creating the weighted edge
        auto new_edge_pair = new pair<int, int>(curr_src, curr_dst);
        cout << "created new_edge_pair: " << new_edge_pair->first << " -> " << new_edge_pair->second << endl;
        auto new_weighted_edge_pair = new pair<pair<int, int>, int>(*new_edge_pair, curr_w);
        cout << "created new_weighted_edge_pair: " << new_weighted_edge_pair->first.first << " --["
             << new_weighted_edge_pair->second << "]--> " << new_weighted_edge_pair->first.second << endl;
        edges.push_back(*new_weighted_edge_pair);

        cout << endl;
    }

    /// Creating the graph data
    vector<vertex<int> *> graph_vertices_vctr;

    // Creating all the vertices
    unordered_map<int, vertex<int> *> data_to_node_map;
    for (int data : nodes) {
        auto new_vertex = new vertex<int>(data); cout << "created new vertex with data " << new_vertex->getVertexData() << endl;
        graph_vertices_vctr.push_back(new_vertex);
        data_to_node_map[data] = new_vertex; cout << "mapped data " << data << " to vertex " << new_vertex->getVertexData() << endl;
        cout << endl;
    }

    // Creating the adj of vertices
    for (auto & edge : edges) {
        // edge.first.first = src, edge.first.second = dst, edge.second = w
        int edge_1_data = edge.first.first; int edge_2_data = edge.first.second; int edge_w = edge.second;

        auto vertex_1 = data_to_node_map[edge_1_data];
        auto vertex_2 = data_to_node_map[edge_2_data];

        vertex_1->addVertexToAdj(vertex_2, edge_w); cout << "added to " << vertex_1->getVertexData() << "'s adj the vertex " << vertex_2->getVertexData() << " with edge weight " << edge_w << endl;
        vertex_2->addVertexToAdj(vertex_1, edge_w); cout << "added to " << vertex_2->getVertexData() << "'s adj the vertex " << vertex_1->getVertexData() << " with edge weight " << edge_w << endl;
        cout << endl;
    }

    auto * new_grap = new graph<int>(graph_vertices_vctr);
    return new_grap;
}


int main() {
    // File opening
    string filepath = R"(C:\Archive\Programming\CLion projects\ASD\src\Lez18_Graphs\prim_good\)";
    string filename = "prim_graph.txt";
    ifstream file(filepath + filename);

    // Graph creation from file
    graph<int> * g = nullptr;
    if (file.is_open()) {
        g = graph_from_file(file);
    }
    else {
        cerr << "No file is open..." << endl;
        return -1;
    }
    graph<int> & G = *g;
    G.print_graph();

    // Printing Prim mst
    G.print_prim_mst(G.get_vertex_from_data(3));


    return 0;
}