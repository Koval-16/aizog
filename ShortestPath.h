//
// Created by kuba on 23.05.2025.
//

#ifndef AIZOGRAF_SHORTESTPATH_H
#define AIZOGRAF_SHORTESTPATH_H
#include "Graph.h"


class ShortestPath {
public:
    static void dijkstra(Graph graph);
    static void bellman(Graph graph);
};


#endif //AIZOGRAF_SHORTESTPATH_H
