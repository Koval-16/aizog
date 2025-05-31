//
// Created by kuba on 25.05.2025.
//

#include "GraphList.h"
#include <iostream>
#include <sstream>

GraphList::~GraphList() {
    for (int i = 0; i < V; i++) delete[] elist[i];
    delete[] elist;
    delete[] amount;
}

void GraphList::set_nodes(int number) {
    V = number;
    edge_count = 0;
}

void GraphList::init() {
    elist = new Edge*[V];
    amount = new int[V];
    for(int i=0; i<V; i++){
        elist[i] = nullptr;
        amount[i] = 0;
    }
}

void GraphList::add_edge(int v1, int v2, int wage, bool directed) {
    int old_size = amount[v1];
    Edge* temp = new Edge[old_size+1];
    for(int i=0; i<old_size; i++) temp[i]=elist[v1][i];
    temp[old_size] = Edge(v1,v2,wage);
    delete[] elist[v1];
    elist[v1] = temp;
    amount[v1]++;
    if(!directed){
        int old_size2 = amount[v2];
        Edge* temp2 = new Edge[old_size2+1];
        for(int i=0; i<old_size2; i++) temp2[i]=elist[v2][i];
        temp2[old_size2] = Edge(v2,v1,wage);
        delete[] elist[v2];
        elist[v2] = temp2;
        amount[v2]++;
    }
    edge_count++;
}

std::string GraphList::toString() {
    std::ostringstream out;
    out << "Lista nastepnikow" << std::endl;
    for(int i=0; i<V; i++){
        out << i << ": ";
        for(int j=0; j<amount[i]; j++){
            out << elist[i][j].get_target_node() << ":" << elist[i][j].get_wage() << "\t";
        }
        out << "\n";
    }
    return out.str();
}

void GraphList::get_all_edges(EdgeList &list, bool directed) {
    for(int i=0; i<V; i++){
        for(int j=0; j<amount[i]; j++){
            Edge edge = elist[i][j];
            if(!(!directed && edge.get_target_node()<i)){
                int v1 = i;
                int v2 = edge.get_target_node();
                int wage = edge.get_wage();
                list.add_edge(v1,v2,wage);
            }
        }
    }
}

int GraphList::get_edge(int v1, int v2) {
    for(int i=0; i<amount[v1]; i++){
        if(i==v2){
            return elist[v1][i].get_wage();
        }
    }
    return 0;
}

int GraphList::get_nodes() {
    return V;
}

int GraphList::get_edges_number() {
    return edge_count;
}

void GraphList::get_edges_from_node(EdgeList &list, int node, bool directed) {
    for (int j = 0; j < amount[node]; j++) {
        Edge edge = elist[node][j];
        int v1 = node;
        int v2 = edge.get_target_node();
        int wage = edge.get_wage();
        list.add_edge(v1, v2, wage);
    }
}
