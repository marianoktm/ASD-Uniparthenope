#include <iostream>
#include <unordered_map>

#include "graph.h"


using namespace std;

int main() {
    int dijkstra_vertices_no = 5;
    string dijkstra_vertices_data = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    vector<vertex<char>*> dijkstra_vertices;
    dijkstra_vertices.reserve(dijkstra_vertices_no);

    for (int i = 0; i < dijkstra_vertices_no; ++i) {
        dijkstra_vertices.push_back(new vertex<char>(dijkstra_vertices_data.at(i), i));
    }

    graph<char> g(dijkstra_vertices);
    cout << endl;

    g.print_edges();

    unordered_map<char, int> dim;
    dim['A'] = 0;
    dim['B'] = 1;
    dim['C'] = 2;
    dim['D'] = 3;
    dim['E'] = 4;

    g.add_edge(dim['A'], dim['B'], 10);
    g.add_edge(dim['A'], dim['C'], 2);
    g.add_edge(dim['B'], dim['D'], 1);
    g.add_edge(dim['C'], dim['B'], 3);
    g.add_edge(dim['C'], dim['E'], 50);
    g.add_edge(dim['D'], dim['C'], 4);
    g.add_edge(dim['D'], dim['E'], 80);

    g.print_edges();

    g.print_dijkstra_tree(0);

    return 0;
}