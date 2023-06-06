//
// Created by apont on 2/27/2023.
//

#ifndef ASD_GRAPH_H
#define ASD_GRAPH_H

typedef enum color {WHITE, GRAY, BLACK} color;

template <class T> class adjlist;

// Vertex data structure
template <class T> class vertex {
private:
    vertex<T> * P;
    int D;
    int F;
    color C;
    T DATA;
    std::vector<vertex<T> *> ADJ;

public:
    explicit vertex(vertex<T> * p = nullptr, int d = -1, int f = -1, color c = WHITE, T data = nullptr): P(p), D(d), F(f), C(c), DATA(data) {}
    explicit vertex(T data): P(nullptr), D(-1), F(-1), C(WHITE), DATA(data) {}
    explicit vertex(T data, std::vector<vertex<T> *> adj): DATA(data), ADJ(adj), P(nullptr), D(-1), F(-1), C(WHITE) {}

    void p(vertex<T> * p) { this->P = p; }
    vertex<T> * p(){ return this->P; }

    void d(int d) { this->D = d; }
    int d() { return this->D; }

    void f(int f) { this->F = f; }
    int f() { return this->F; }

    void c(color c) { this->C = c; }
    color c() { return this->C; }

    void data(T data) { this->DATA = data; }
    T data() { return this->DATA; }

    void initialize_for_traversal() {
        this->P = nullptr;
        this->D = -1;
        this->F = -1;
        this->C = WHITE;
    }

    void adj(std::vector<vertex<T> *> adj) { this->ADJ = adj; }
    std::vector<vertex<T> *> adj() { return this->ADJ; }

    void push_to_adj(vertex<T> * v) { this->ADJ.push_back(v); }

    void print_adj() {
        std::cout << "Vertex " << this->DATA << " adj list (size " << this->ADJ.size() << "):" << std::endl;
        std::cout << this->DATA;
        for (auto v : this->ADJ) {
            std::cout  << " -> ";
            std::cout << v->node_data();
        }
        std::cout << std::endl;
    }
};

template <class T> class graph {
private:
    std::vector<vertex<T> *> V;
    vertex<T> * find_node(T key);
    void DFS_Visit(vertex<T> * u, int & time);

public:
    explicit graph(std::vector<vertex<T> *> vertex_vctr): V(vertex_vctr) {}

    void print_all_adj() { for (auto v : V) v->print_adj(); }

    void DFS();
    void BFS(T souce_key);
};

template<class T>
void graph<T>::DFS() {
    std::cout << "DFS: ";
    for (auto v : V)
        v->initialize_for_traversal();
    int time = 0;
    for (vertex<T> * v : V) {
        if (v->c() == WHITE) {
            DFS_Visit(v, time);
        }
    }
    std::cout << std::endl;
}

template<class T>
void graph<T>::DFS_Visit(vertex<T> *u, int &time) {
    time++;
    u->d(time);
    u->c(GRAY);
    for (auto v : u->adj()) {
        if (v->c() == WHITE) {
            v->p(u);
            DFS_Visit(v, time);
        }
    }
    time++;
    u->f(time);
    u->c(BLACK);
    std::cout << u->data();
}

template<class T>
vertex<T> *graph<T>::find_node(T key) {
    for (auto v : V) {
        if (v->node_data() == key) {
            return v;
        }
    }
    return nullptr;
}

template<class T>
void graph<T>::BFS(T source_key) {
    std::cout << "BFS: ";
    for (auto v : V)
        v->initialize_for_traversal();

    auto source_node = find_node(source_key);
    source_node->c(GRAY);
    source_node->d(0);
    source_node->p(nullptr);

    std::queue<vertex<T>*> Q;
    Q.push(source_node);

    vertex<T> * u;
    while (!Q.empty()) {
        u = Q.front();
        Q.pop();
        for (auto v : u->adj()) {
            if (v->c() == WHITE) {
                v->p(u);
                v->d(u->d() + 1);
                v->c(GRAY);
                Q.push(v);
            }
        }
        u->c(BLACK);
        std::cout << u->data();
    }
    std::cout << std::endl;
}




#endif //ASD_GRAPH_H
