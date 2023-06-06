#ifndef ASD_GRAPH_H
#define ASD_GRAPH_H

#include <vector>
#include <iostream>
#include "disjointset.h"

#define gnptr graph_node<T> *
#define tpt template<class T>

tpt class graph_node {
private:
    T data;
    std::vector<gnptr> adj;

public:
    graph_node() = default;
    explicit graph_node(T new_data): data(new_data) {};

    void setData(T new_data) { this->data = new_data; }
    T getData() { return this->data; }

    void pushOnAdj(gnptr topush) { this->adj.push_back(topush); }
    std::vector<gnptr> getAdj() { return this->adj; }

    friend std::ostream &operator<<(std::ostream &os, const graph_node &node) {
        os << node.data;
        return os;
    }
};

tpt class graph {
private:
    std::vector<gnptr> V;

public:
    graph() = default;

    void addVertex(gnptr to_add) { this->V.push_back(to_add); }
    std::vector<gnptr> getVertices() { return this->V; }

    gnptr findNodeFromData(T tofind_data) {
        for (auto v: V) {
            if (v->getData() == tofind_data) {
                return v;
            }
        }
        return nullptr;
    }

    void print_graph() {
        for (auto u : V) {
            std::cout << "[" << u->getData() << "] ";
            for (auto v : u->getAdj()) {
                std::cout << "[" << v->getData() << "] ";
            }
            std::cout << std::endl;
        }
    }

    void print_connected_components() {
        disjointset_pool<gnptr> set;

        int i = 0;
        for (auto v : V) {
            set.make_set(i, v);
            i=i+1;
        }

        for (auto u : V) {
            std::cout << "Node: " << u->getData() << std::endl;
            for (auto v : u->getAdj()) {
                std::cout << "[" << v->getData() << "] ";
                if (set.find_set_from_nodedata(u) != set.find_set_from_nodedata(v)) {
                    std::cout << "UNION: " << u->getData() << " + " << v->getData();
                    set.union_set_from_data(u, v);
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        set.print_map();
    }
};

#endif //ASD_GRAPH_H
