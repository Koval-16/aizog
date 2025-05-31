//
// Created by kuba on 25.05.2025.
//

#include "GraphAdjacency.h"
#include <iostream>
#include <sstream>

GraphAdjacency::~GraphAdjacency() {
    for (int i = 0; i < V; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void GraphAdjacency::set_nodes(int number) {
    V = number;
    edge_count = 0;
}

void GraphAdjacency::init() {
    matrix = new int*[V];
    for(int i=0; i<V; i++) matrix[i] = new int[V]();
}

void GraphAdjacency::add_edge(int v1, int v2, int wage, bool directed) {
    matrix[v1][v2] = wage;
    if(!directed) matrix[v2][v1] = wage;
    edge_count++;
}

std::string GraphAdjacency::toString() {
    std::ostringstream out;
    out << "Macierz Sasiedztwa" << std::endl;
    for(int i=0; i<V; i++){
        for(int j=0; j<V; j++){
            out << matrix[i][j] << "\t";
        }
        out << "\n";
    }
    return out.str();
}

bool GraphAdjacency::edge_exists(int v1, int v2) {
    if(matrix[v1][v2]!=0) return true;
    else return false;
}

void GraphAdjacency::get_all_edges(EdgeList &list, bool directed) {
    for(int i=0; i<V; i++){
        int k;
        if(directed) k=0;
        else k=i+1;
        for(int j=k; j<V; j++){
            int wage = get_edge(i, j);
            if(wage!=0){
                list.add_edge(i,j,wage);
            }
        }
    }
}

int GraphAdjacency::get_edge(int v1, int v2) {
    return matrix[v1][v2];
}

int GraphAdjacency::get_nodes() {
    return V;
}

int GraphAdjacency::get_edges_number() {
    return edge_count;
}

void GraphAdjacency::get_edges_from_node(EdgeList &list, int node, bool directed) {
    for(int j = 0; j < V; j++) {
        if (j != node) {
            int wage = get_edge(node, j);
            if (wage != 0) {
                list.add_edge(node, j, wage);
            }
        }
    }
}
