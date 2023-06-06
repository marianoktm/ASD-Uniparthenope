#ifndef ASD_GRAPH_H
#define ASD_GRAPH_H

#include <utility>
#include <vector>
#include <cmath>

#include "set.h"

#define weight int
#define edge pair<int, int>

using namespace std;

class graph {
private:
    // edges[i].first -> w
    // edges[i].second.first -> u
    // edges[i].second.second -> v
    vector<pair<weight, edge>> edges;
    vector<int> nodes;

    bool samecomponent(set_pool<int> set, int u, int v) {
        return set.find_set(u) == set.find_set(v);
    }

public:
    graph(vector<pair<weight,edge>> edg, vector<int> nod): edges(move(edg)), nodes(move(nod)) {}

    void print_kruskal_mst() {
        // Make set
        set_pool<int> set;
        for (int v : nodes) {
            set.make_set(v);
        }

        // Edges sort
        sort(edges.begin(), edges.end());

        // Building MST
        vector<pair<weight, edge>> A;
        for (auto & i : edges) {
            auto w = i.first;
            auto u = i.second.first;
            auto v = i.second.second;

            if (!samecomponent(set, u, v)) {
                A.push_back(i);
                set.union_set(u, v);
            }
        }

        for (auto & i : A) {
            auto w = i.first;
            auto u = i.second.first;
            auto v = i.second.second;

            cout << u << "--" << w << "->" << v << endl;
        }
        cout << endl;
    }
};

#endif //ASD_GRAPH_H
