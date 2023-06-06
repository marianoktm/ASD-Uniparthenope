//
// Created by apont on 3/7/2023.
//

#ifndef ASD_GRAPH_H
#define ASD_GRAPH_H

#include <vector>

#include "min_priority_queue.h"

#define INT_INF numeric_limits<int>::max()

using namespace std;

/// Vertex template class
template<class T> class vertex {
private:
    T vertex_data;
    vector<pair<vertex<T> *, int>> vertex_adj; // vertex_adj[i].first = destination, vertex_adj[i].second = weight

public:
    vertex() = default;
    explicit vertex(T new_data): vertex_data(new_data) {}

    T getVertexData() { return this->vertex_data; }
    void setVertexData(T new_data) { this->vertex_data = new_data; }

    vector<pair<vertex<T>*, int>> getVertexAdj() { return this->vertex_adj; }
    void addVertexToAdj(vertex<T> * to_add, int w) { this->vertex_adj.push_back(*new pair<vertex<T>*, int>(to_add, w)); }
};

/// Graph template class
template<class T> class graph {
private:
    vector<vertex<T>*> V;

public:
    graph() = default;
    explicit graph(vector<vertex<T>*> new_V): V(new_V) {}

    void print_graph() {
        cout << "Printing whole graph: " << endl;
        for (auto u : V) {
            cout << u->getVertexData() << endl;
            for (auto edge : u->getVertexAdj()) {
                cout << "- " << edge.first->getVertexData() << " (" << edge.second << ")" << endl;
            }
        }
        cout << endl;
    }

    vertex<T> * get_vertex_from_data(T data) {
        for (auto v : V) {
            if (v->getVertexData() == data) {
                return v;
            }
        }
        return nullptr;
    }

    void print_prim_mst(vertex<T> * src) {
        cout << ">>>> BUILDING PRIM'S MST <<<<" << endl;
        cout << "source: " << src->getVertexData() << endl;

        cout << endl;

        // Anonymous class for prim MST
        class prim_vertex {
        public:
            vertex<T> * base_vertex;
            vertex<T> * p;
            int d;

            explicit prim_vertex(vertex<T> * in_base_vertex, vertex<T> * in_p, int in_d): base_vertex(in_base_vertex), p(in_p), d(in_d) {}

            bool operator>(prim_vertex & comp) const { return this->d > comp.d; }
            bool operator<(prim_vertex & comp) const { return this->d < comp.d; }
            bool operator>=(prim_vertex & comp) const { return this->d >= comp.d; }
            bool operator<=(prim_vertex & comp) const { return this->d <= comp.d; }
        };

        // Initialization
        vector<prim_vertex> prim_vertices;
        unordered_map<vertex<T>*, prim_vertex*> vertex_to_prim_map;
        for (auto v : V) {
            if (v != src) {
                auto new_prim_vertex = new prim_vertex(v, nullptr, INT_INF);
                cout << "initialized " << new_prim_vertex->base_vertex->getVertexData() << ": " << endl << "- p: " << new_prim_vertex->p << endl << "- d: "<< new_prim_vertex->d << endl;

                vertex_to_prim_map[v] = new_prim_vertex;
                cout << "mapped " << v->getVertexData() << " to " << vertex_to_prim_map[v]->base_vertex->getVertexData() << endl;
                cout << endl;

                prim_vertices.push_back(*new_prim_vertex);
            }
        }
        auto prim_vertex_src = new prim_vertex(src, nullptr, 0);
        cout << "initialized " << prim_vertex_src->base_vertex->getVertexData() << ": " << endl << "- p: " << prim_vertex_src->p << endl << "- d: "<< prim_vertex_src->d << endl;\
        vertex_to_prim_map[src] = prim_vertex_src;
        cout << "mapped " << src->getVertexData() << " to " << vertex_to_prim_map[src]->base_vertex->getVertexData() << endl;
        prim_vertices.push_back(*prim_vertex_src);
        cout << endl;

        // Queue
        min_priority_queue<prim_vertex> Q(prim_vertices);

        // Actual algorithm
        while (!Q.is_empty()) {
            prim_vertex u = Q.extract_min();
            cout << "extracted " << u.base_vertex->getVertexData() << " from Q:" << endl;
            cout << "parent: " << u.p << endl;
            cout << "estimation: " << u.d << endl;
            cout << endl;

            for (auto edge : u.base_vertex->getVertexAdj()) {
                vertex<T> * v = edge.first;
                int w = edge.second;
                prim_vertex * v_prim = vertex_to_prim_map[v];

                cout << "found edge " <<  u.base_vertex->getVertexData() << "--[" << w << "]--" << v->getVertexData() << "" << endl;

                if (v_prim->d > w + u.d) {
                    cout << "update of v.d for edge " <<  u.base_vertex->getVertexData() << "--[" << w << "]--" << v->getVertexData() << endl;
                    v_prim->d = w + u.d;
                    v_prim->p = u.base_vertex;
                    cout << "new v.d: " << v_prim->d << endl << "new v.p: " << v_prim->p->getVertexData() << endl;
                    Q.decrease_key();
                    cout << endl;
                }
            }
            cout << endl;
        }

        // Print
        for (auto elem : vertex_to_prim_map) {
            auto vtpm_elem = elem.second;
            if (vtpm_elem->p != nullptr) {
                std::cout << vtpm_elem->base_vertex->getVertexData() << "->" << vtpm_elem->p->getVertexData() << endl;
            }
        }
    }
};


#endif //ASD_GRAPH_H
