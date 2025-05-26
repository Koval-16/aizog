//
// Created by kuba on 25.05.2025.
//

#ifndef AIZOG_GRAPHLIST_H
#define AIZOG_GRAPHLIST_H
#include "Graph.h"
#include "Edge.h"

class GraphList : public Graph {
private:
    Edge** elist;
    int* amount;
    int V;
    int edge_count;
public:
    ~GraphList() override;
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


#endif //AIZOG_GRAPHLIST_H
