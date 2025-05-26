//
// Created by kuba on 23.05.2025.
//

#ifndef AIZOGRAF_MST_H
#define AIZOGRAF_MST_H
#include "Graph.h"
#include "EdgeList.h"

class MST {
public:
    static int prim(Graph& graph, int representation);
    static int kruskal(Graph& graph, int representation);
private:
    static void sort(EdgeList& list);
};


#endif //AIZOGRAF_MST_H
