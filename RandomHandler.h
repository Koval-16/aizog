//
// Created by kuba on 19.05.2025.
//

#ifndef AIZOGRAF_RANDOMHANDLER_H
#define AIZOGRAF_RANDOMHANDLER_H

#include "Graph.h"
#include "GraphAdjacency.h"

class RandomHandler {
public:
    static void generate_graph(int nodes, float density, GraphAdjacency& graph_adj, Graph& graph_inc, Graph& graph_list, bool directed);
private:
    static int* add_number(int* tab, int& size, int number);
    static int remove_number(int*& tab, int& size, int position);
};


#endif //AIZOGRAF_RANDOMHANDLER_H
