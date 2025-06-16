//
// Created by kuba on 23.05.2025.
//

#ifndef AIZOGRAF_SHORTESTPATH_H
#define AIZOGRAF_SHORTESTPATH_H
#include "Graph.h"


class ShortestPath {
public:
    static int dijkstra(Graph& graph, std::ostringstream* result= nullptr);
    static int bellman(Graph& graph, std::ostringstream* result= nullptr);
private:
};


#endif //AIZOGRAF_SHORTESTPATH_H
