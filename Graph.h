
#ifndef AIZOG_GRAPH_H
#define AIZOG_GRAPH_H
#include "EdgeList.h"
#include <iostream>

// interface used by other Graph classes
class Graph {
private:
    int V; // number of nodes
    int edge_count;
public:
    virtual ~Graph() = default; // destructur
    virtual void set_nodes(int number) = 0; // sets number of nodes
    virtual void init(int edges) = 0; // inits the representation of graph
    virtual void add_edge(int v1, int v2, int wage, bool directed) = 0; // adds edge to graph
    virtual std::string toString() = 0; // returns string visualising the graph
    virtual void get_all_edges(EdgeList& list, bool directed) = 0; // gets all edges from graph
    virtual int get_edge(int v1, int v2) = 0; // returns a wage of given edge
    virtual int get_nodes() = 0; // returns number of nodes
    virtual int get_edges_number() = 0; // returns number of edges
    virtual void get_edges_from_node(EdgeList &list, int node, bool directed) = 0; // gets edges from specified node
    virtual bool has_edges_from_node(int node, bool directed) = 0; // checks if given node has any edges from
};


#endif //AIZOG_GRAPH_H
