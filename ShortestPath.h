#ifndef AIZOGRAF_SHORTESTPATH_H
#define AIZOGRAF_SHORTESTPATH_H
#include "Graph.h"

// Class ShortestPath has two algorithms which calculate the shortest path from given node, to another one
class ShortestPath {
public:
    static int dijkstra(Graph& graph,int start_node,int end_node, std::ostringstream* result= nullptr);
    static int bellman(Graph& graph,int start_node, int end_node, std::ostringstream* result= nullptr);
private:
};


#endif //AIZOGRAF_SHORTESTPATH_H
