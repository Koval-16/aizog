//
// Created by kuba on 25.05.2025.
//

#ifndef AIZOG_GRAPH_H
#define AIZOG_GRAPH_H
#include "EdgeList.h"
#include <iostream>

class Graph {
private:
    int V; // number of nodes
    int edge_count;
public:
    virtual ~Graph() = default;
    virtual void set_nodes(int number) = 0;
    virtual void init(int edges) = 0;
    virtual void add_edge(int v1, int v2, int wage, bool directed) = 0;
    virtual std::string toString() = 0;
    virtual void get_all_edges(EdgeList& list, bool directed) = 0;
    virtual int get_edge(int v1, int v2) = 0;
    virtual int get_nodes() = 0;
    virtual int get_edges_number() = 0;
    virtual void get_edges_from_node(EdgeList &list, int node, bool directed) = 0;
    virtual bool has_edges_from_node(int node, bool directed) = 0;
};


#endif //AIZOG_GRAPH_H
