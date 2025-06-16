//
// Created by kuba on 23.05.2025.
//

#ifndef AIZOGRAF_MST_H
#define AIZOGRAF_MST_H
#include "Graph.h"
#include "EdgeList.h"

class MST {
public:
    static int prim(Graph& graph, std::ostringstream* result= nullptr);
    static int kruskal(Graph& graph, std::ostringstream* result= nullptr);
private:
    static void sort(EdgeList& list);
    static void quick_sort(EdgeList& list, int left, int right);
    static int partition(EdgeList& list, int left, int right);
};


#endif //AIZOGRAF_MST_H
