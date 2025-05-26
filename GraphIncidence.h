//
// Created by kuba on 25.05.2025.
//

#ifndef AIZOG_GRAPHINCIDENCE_H
#define AIZOG_GRAPHINCIDENCE_H
#include "Graph.h"


class GraphIncidence : public Graph{
private:
    int** matrix;
    int V;
    int edge_count;
public:
    ~GraphIncidence() override;
    void set_nodes(int number) override;
    void init() override;
    void add_edge(int v1, int v2, int wage, bool directed) override;
    void print() override;
    void get_all_edges(EdgeList& list, bool directed) override;
    int get_edge(int v1, int v2) override;
    int get_nodes() override;
    int get_edges_number() override;
    void get_edges_from_node(EdgeList &list, int node, bool directed) override;
};


#endif //AIZOG_GRAPHINCIDENCE_H
