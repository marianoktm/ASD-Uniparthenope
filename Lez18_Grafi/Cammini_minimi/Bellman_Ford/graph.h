//
// Created by apont on 3/11/2023.
//

#ifndef ASD_GRAPH_H
#define ASD_GRAPH_H

#include <climits>
#include <vector>
#include <iostream>

using namespace std;

/** Vertex struct **/
template<class T> struct vertex {
public:
    T data;
    int index = -1;
    int d = INT_MAX;
    vertex<T> * p = nullptr;

    vertex() = default;
    vertex(T new_data, int new_index): data(new_data), index(new_index) {}
};

/** Graph class **/
template<class T> class graph {
private:
    int no_of_vertices;
    vector<vertex<T>*> vertices;
    vector<vector<int>> edges;

    void initialize_single_source(int src_idx) {
        for (int i = 0; i < no_of_vertices; ++i) {
            vertices.at(i)->d = INT_MAX;
            vertices.at(i)->p = nullptr;
        }
        vertices.at(src_idx)->d = 0;
        vertices.at(src_idx)->p = nullptr;
    }

    void relax(int u_idx, int v_idx, int w) {
        if (vertices.at(v_idx)->d > vertices.at(u_idx)->d + w) {
            vertices.at(v_idx)->d = vertices.at(u_idx)->d + w;
            vertices.at(v_idx)->p = vertices.at(u_idx);
        }
    }

    bool is_valid_idx(int idx) {
        return idx < no_of_vertices;
    }

    bool is_valid_edge(int src_idx, int dst_idx) {
        return is_valid_idx(src_idx) and is_valid_idx(dst_idx);
    }

public:
    graph() = default;
    explicit graph(vector<vertex<T>*> new_vertices): vertices(new_vertices), no_of_vertices(new_vertices.size()) {
        // Initializing edges (no edges in the class)
        for (int i = 0; i < no_of_vertices; ++i) {
            auto new_row = new vector<int>(no_of_vertices, INT_MAX);
            edges.push_back(*new_row);
        }
        print_edges();
    }

    void print_edges() {
        for (int i = 0; i < no_of_vertices; ++i) {
            for (int j = 0; j < no_of_vertices; ++j) {
                cout << edges.at(i).at(j) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    bool add_edge(int src_idx, int dst_idx, int weight) {
        if (is_valid_edge(src_idx, dst_idx)) {
            edges.at(src_idx).at(dst_idx) = weight;
            return true;
        }
        else {
            return false;
        }
    }

    void print_mpt() {
        for (int i = 0; i < no_of_vertices; ++i) {
            auto u = vertices.at(i)->p;
            auto v = vertices.at(i);
            if (u != nullptr) {
                cout << u->data << "--[" << edges.at(u->index).at(v->index) << "]-->" << v->data << endl;
            }
        }
        cout << endl;
    }

    bool bellman_ford(int src_idx) {
        initialize_single_source(src_idx);
        for (int i = 0; i < no_of_vertices-1; ++i) {
            for (int u_idx = 0; u_idx < no_of_vertices; u_idx++) {
                for (int v_idx = 0; v_idx < no_of_vertices; ++v_idx) {
                    if (edges.at(u_idx).at(v_idx) < INT_MAX) {
                        relax(u_idx, v_idx, edges.at(u_idx).at(v_idx));
                    }
                }
            }
        }

        for (int u_idx = 0; u_idx < no_of_vertices; ++u_idx) {
            for (int v_idx = 0; v_idx < no_of_vertices; ++v_idx) {
                if (edges.at(u_idx).at(v_idx) < INT_MAX) {
                    if (vertices.at(v_idx)->d > vertices.at(u_idx)->d + edges.at(u_idx).at(v_idx)) {
                        return false;
                    }
                }
            }
        }

        print_mpt();
        return true;
    }
};


#endif //ASD_GRAPH_H
