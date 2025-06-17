#ifndef AIZOG_GRAPHADJACENCY_H
#define AIZOG_GRAPHADJACENCY_H
#include "Graph.h"
#include <iostream>

// Graph is represented by Adjacency Matrix
class GraphAdjacency : public Graph {
private:
    int V;
    int edge_count;
    int** matrix;
public:
    ~GraphAdjacency() override;
    void set_nodes(int number) override;
    void init(int edges) override;
    void add_edge(int v1, int v2, int wage, bool directed) override;
    std::string toString() override;
    bool edge_exists(int v1, int v2);
    void get_all_edges(EdgeList& list, bool directed) override;
    int get_edge(int v1, int v2) override;
    int get_nodes() override;
    int get_edges_number() override;
    void get_edges_from_node(EdgeList &list, int node, bool directed) override;
    bool has_edges_from_node(int node, bool directed) override;
};


#endif //AIZOG_GRAPHADJACENCY_H
