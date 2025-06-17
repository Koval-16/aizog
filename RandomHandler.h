#ifndef AIZOGRAF_RANDOMHANDLER_H
#define AIZOGRAF_RANDOMHANDLER_H

#include "Graph.h"
#include "GraphAdjacency.h"

// Generates a random graph, basing on given parameters
class RandomHandler {
public:
    static void generate_graph(int nodes, float density, GraphAdjacency& graph_adj, Graph& graph_inc, Graph& graph_list, bool directed);
};


#endif //AIZOGRAF_RANDOMHANDLER_H
