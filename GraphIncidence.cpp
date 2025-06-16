//
// Created by kuba on 25.05.2025.
//

#include "GraphIncidence.h"
#include <iostream>
#include <sstream>

GraphIncidence::~GraphIncidence() {
    for (int i = 0; i < V; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void GraphIncidence::set_nodes(int number) {
    V = number;
    edge_count = 0;
}

void GraphIncidence::init(int edges) {
    matrix = new int*[V];
    for(int i=0; i<V; i++){
        matrix[i] = new int[edges]();
    }
    max_edges = edges;
}

void GraphIncidence::add_edge(int v1, int v2, int wage, bool directed) {
    matrix[v1][edge_count] = wage;
    if(!directed) matrix[v2][edge_count] = -wage;
    else matrix[v2][edge_count] = -wage;
    edge_count++;
}

std::string GraphIncidence::toString() {
    std::ostringstream out;
    out << "Macierz Incydencji" << std::endl;
    for(int i=0; i<V; i++){
        for(int j=0; j<edge_count; j++){
            out << matrix[i][j] << "\t";
        }
        out << "\n";
    }
    return out.str();
}

void GraphIncidence::get_all_edges(EdgeList &list, bool directed) {
    for (int i = 0; i < edge_count; i++) {
        int v1 = -1;
        int v2 = -1;
        int wage = 0;

        for (int j = 0; j < V; j++) {
            int value = matrix[j][i];
            if (value != 0) {
                if (v1 == -1) {
                    v1 = j;
                    wage = value;
                } else {
                    v2 = j;
                    break;
                }
            }
        }

        // Sprawdzenie poprawności
        if (v1 != -1 && v2 != -1) {
            if (wage < 0) {
                std::swap(v1, v2);
                wage = -wage;
            }
            list.add_edge(v1, v2, wage);
        }
    }
}

int GraphIncidence::get_edge(int v1, int v2) {
    for(int i=0; i<edge_count; i++){
        int node1 = matrix[v1][i];
        int node2 = matrix[v2][i];
        if(node1!=0 && node2!=0){
            if(node1>0) return node1;
            else return node2;
        }
    }
    return 0;
}

int GraphIncidence::get_nodes() {
    return V;
}

int GraphIncidence::get_edges_number() {
    return edge_count;
}

void GraphIncidence::get_edges_from_node(EdgeList &list, int node, bool directed) {
    for (int i = 0; i < edge_count; i++) {
        int wage = matrix[node][i];

        // Sprawdź, czy node jest źródłem krawędzi (w przypadku skierowanego grafu)
        if (wage > 0 || (!directed && wage != 0)) {
            int target = -1;
            for (int j = 0; j < V; j++) {
                if (j != node && matrix[j][i] != 0) {
                    target = j;
                    break;
                }
            }

            if (target != -1) {
                list.add_edge(node, target, std::abs(wage));
            }
        }
    }
}

bool GraphIncidence::has_edges_from_node(int node, bool directed) {
    for (int i = 0; i < edge_count; i++) {
        int wage = matrix[node][i];

        if (wage > 0 || (!directed && wage != 0)) {
            int target = -1;
            for (int j = 0; j < V; j++) {
                if (j != node && matrix[j][i] != 0) {
                    target = j;
                    break;
                }
            }
            if (target != -1) return true;
        }
    }
    return false;
}
