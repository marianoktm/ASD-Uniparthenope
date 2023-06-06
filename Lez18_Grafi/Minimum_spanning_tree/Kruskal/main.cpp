#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>

#include "graph.h"

#define NEGATIVE_INFINITY INFINITY*-1


using namespace std;

/** Reads the file **/
graph * read_file(ifstream & file) {
    /// READING LINE FOR NODES AND EDGES
    // Nodes
    int n_of_nodes;
    string n_buf;
    file >> n_buf;
    n_of_nodes = stoi(n_buf);

    // Edges
    int m_of_edges;
    string m_buf;
    file >> m_buf;
    m_of_edges = stoi(m_buf);

    // Print
    cout << "Nodes #: " << n_of_nodes << endl << "Edges #: " << m_of_edges << endl;

    /// CREATING NODE AND EDGES
    vector<int> nodes(n_of_nodes);
    // edges[i].first -> w
    // edges[i].second.first -> u
    // edges[i].second.second -> v
    auto * edges = new vector<pair<weight,edge>>();

    while (file.good()) {
        string src_buf;
        string dst_buf;
        string w_buf;

        // src id
        file >> src_buf;
        // dst id
        file >> dst_buf;
        // weight of src dst edge
        file >> w_buf;

        // Checking if src and dest are new
        if (find(nodes.begin(), nodes.end(), stoi(src_buf)) == nodes.end()) {
            nodes[stoi(src_buf)-1] = stoi(src_buf);
            cout << "! Added as src at " << stoi(src_buf)-1 << " the node " << stoi(src_buf) << endl;
        }
        if (find(nodes.begin(), nodes.end(), stoi(dst_buf)) == nodes.end()) {
            nodes[stoi(dst_buf)-1] = stoi(dst_buf);
            cout << "! Added as dst at " << stoi(dst_buf)-1 << " the node " << stoi(dst_buf) << endl;
        }

        // Creating and pushing the edge
        auto * newsrcdst = new edge(stoi(src_buf), stoi(dst_buf));
        auto * newedge = new pair<weight,edge>(stoi(w_buf), *newsrcdst);

        edges->push_back(*newedge);
        cout << "> Pushed back edge: " << endl <<
        "- Src: " << newedge->second.first << endl <<
        "- Dst: " << newedge->second.second << endl <<
        "- W:   " << newedge->first << endl;
    }

    /// CREATING A GRAPH
    auto out_graph = new graph(*edges, nodes);
    return out_graph;

}


/** Main **/
int main() {
    string filepath = R"(C:\Archive\Programming\CLion projects\ASD\src\Lez18_Graphs\kruskal\)";
    string filename = "ksk_graph.txt";

    ifstream file(filepath + filename);
    graph * g;

    if (file.is_open()) {
        g = read_file(file);
    }
    else {
        return -1;
    }

    graph & gr = *g;
    gr.print_kruskal_mst();

    return 0;
}
