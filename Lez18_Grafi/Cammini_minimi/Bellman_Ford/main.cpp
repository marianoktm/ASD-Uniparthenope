//
// Created by apont on 3/11/2023.
//
#include <string>
#include <unordered_map>
#include "graph.h"

using namespace std;

int main() {
    int bf_vertices_no = 5;
    string bf_vertices_data = "ZXYUV";

    vector<vertex<char>*> bf_vertices;
    bf_vertices.reserve(bf_vertices_no);

    for (int i = 0; i < bf_vertices_no; ++i) {
        bf_vertices.push_back(new vertex<char>(bf_vertices_data.at(i), i));
    }

    graph<char> g(bf_vertices);
    cout << endl;

    g.print_edges();

    unordered_map<char, int> dim;
    dim['Z'] = 0;
    dim['X'] = 1;
    dim['Y'] = 2;
    dim['U'] = 3;
    dim['V'] = 4;

    int z = dim['Z'];
    int x = dim['X'];
    int y = dim['Y'];
    int u = dim['U'];
    int v = dim['V'];

    g.add_edge(z, u, 6);
    g.add_edge(z, x, 7);

    g.add_edge(x, y, 9);
    g.add_edge(x, v, -3);

    g.add_edge(y, v, 7);
    g.add_edge(y, z, 2);

    g.add_edge(u, v, 5);
    g.add_edge(u, x, 8);

    g.add_edge(v, u, -2);

    g.print_edges();

    g.bellman_ford(z);

    return 0;
}
