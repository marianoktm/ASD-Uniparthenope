//
// Created by apont on 3/9/2023.
//

#ifndef ASD_GRAPH_H
#define ASD_GRAPH_H

#include <climits>
#include <vector>
#include <queue>
#include "min_priority_queue.h"

using namespace std;

/** Vertex struct **/
template<class T> struct vertex {
public:
    T data;
    int d = INT_MAX;
    int index = -1;
    vertex<T> * p = nullptr;

    vertex() = default;
    explicit vertex(T new_data, int new_index): data(new_data), index(new_index) {}

    bool operator>(vertex & cmp) const {return this->d > cmp.d; }
    bool operator<(vertex & cmp) const {return this->d < cmp.d; }
    bool operator>=(vertex & cmp) const {return this->d >= cmp.d; }
    bool operator<=(vertex & cmp) const {return this->d <= cmp.d; }

    friend ostream & operator<<(ostream & os, vertex & v) {
        os << v.data << "-" << v.d;
        return os;
    }
};


/** Graph class **/
template<class T> class graph {
private:
    int no_of_vertices;
    vector<vertex<T>*> vertices;
    vector<vector<int>> edges;

public:
    graph() = default;
    explicit graph(vector<vertex<T>*> new_vertices): vertices(new_vertices), no_of_vertices(new_vertices.size()) {
        for (int i = 0; i < no_of_vertices; ++i) {
            vertices.at(i)->index = i;
        }

        // Initializing adj matrix
        for (int i = 0; i < no_of_vertices; i++) {
            auto new_row = new vector<int>(no_of_vertices, INT_MAX);
            edges.push_back(*new_row);
        }
        print_edges();
    }

    vector<vertex<T>*> get_vertices() { return this->vertices; }
    vector<vector<int>> get_edges() { return this->edges; }

    void print_edges() {
        for (int i = 0; i < no_of_vertices; i++) {
            for (int j = 0; j < no_of_vertices; j++) {
                cout << "[" << edges.at(i).at(j) << "] ";
            }
            cout << endl;
        }
    }

    bool add_edge(int index_src, int index_dst, int edge_weight) {
        if ((index_src > -1 and index_src < no_of_vertices) and (index_dst > -1 and index_dst < no_of_vertices)) {
            edges.at(index_src).at(index_dst) = edge_weight;
            return true;
        }
        else {
            return false;
        }

    }

    void print_dijkstra_tree(int src_index) {
        // INITIALIZE SINGLE SOURCE
        for (int i = 0; i < no_of_vertices; ++i) {
            vertices.at(i)->d = INT_MAX;
            vertices.at(i)->p = nullptr;
        }
        vertices.at(src_index)->d = 0;
        vertices.at(src_index)->p = nullptr;

        // PRIORITY QUEUE
        min_priority_queue<vertex<T>*> Q(vertices);

        // ACTUAL DIJKSTRA
        while (!Q.empty()) {
            auto u = Q.extract_min();
            for (int i = 0; i < no_of_vertices; i++) {
                // IF THERE'S AN EDGE BETWEEN u AND v
                if (edges.at(u->index).at(i) != INT_MAX) {
                    // RELAX
                    if (vertices.at(i)->d > u->d + edges.at(u->index).at(i)) {
                        vertices.at(i)->d = u->d + edges.at(u->index).at(i);
                        vertices.at(i)->p = u;
                        Q.re_heap();
                        Q.print();
                    }
                }
            }
        }

        // PRINT
        for (int i = 0; i < no_of_vertices; ++i) {
            auto u = vertices.at(i)->p;
            auto v = vertices.at(i);
            if (u != nullptr) {
                cout << u->data << "--[" << edges.at(u->index).at(v->index) << "]-->" << v->data << endl;
            }
        }
        cout << endl;
    }
};


#endif //ASD_GRAPH_H
