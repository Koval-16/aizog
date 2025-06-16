//
// Created by kuba on 25.05.2025.
//

#include "GraphList.h"
#include <iostream>
#include <sstream>

GraphList::~GraphList() {
    for (int i = 0; i < V; ++i) {
        Successor* curr = adj[i];
        while (curr != nullptr) {
            Successor* to_delete = curr;
            curr = curr->next;
            delete to_delete;
        }
    }
    delete[] adj;
}

void GraphList::set_nodes(int number) {
    V = number;
    edge_count = 0;
}

void GraphList::init() {
    adj = new Successor*[V];
    for(int i=0; i<V; i++){
        adj[i] = nullptr;
    }
}

void GraphList::add_edge(int v1, int v2, int wage, bool directed) {
    adj[v1] = new Successor(v2,wage,adj[v1]);
    if(!directed){
        adj[v2] = new Successor(v1,wage,adj[v2]);
    }
    edge_count++;
}

std::string GraphList::toString() {
    std::ostringstream out;
    out << "Lista nastepnikow" << std::endl;
    for(int i=0; i<V; i++){
        out << i << ": ";
        Successor* curr = adj[i];
        while (curr != nullptr) {
            out << curr->node << ":" << curr->wage << "\t";
            curr = curr->next;
        }
        out << "\n";
    }
    return out.str();
}

void GraphList::get_all_edges(EdgeList &list, bool directed) {
    for (int v1 = 0; v1 < V; ++v1) {
        Successor* curr = adj[v1];
        while (curr != nullptr) {
            int v2 = curr->node;
            int wage = curr->wage;
            if (directed || v1 < v2) {
                list.add_edge(v1, v2, wage);
            }
            curr = curr->next;
        }
    }
}

int GraphList::get_edge(int v1, int v2) {
    Successor* curr = adj[v1];
    while (curr != nullptr) {
        if (curr->node == v2) {
            return curr->wage;
        }
        curr = curr->next;
    }
    return 0; // brak takiej krawędzi
}

int GraphList::get_nodes() {
    return V;
}

int GraphList::get_edges_number() {
    return edge_count;
}

void GraphList::get_edges_from_node(EdgeList &list, int node, bool directed) {
    Successor* curr = adj[node];
    while (curr != nullptr) {
        list.add_edge(node, curr->node, curr->wage);
        curr = curr->next;
    }
}

bool GraphList::has_edges_from_node(int node, bool directed) {
    Successor* curr = adj[node];
    if(curr!= nullptr) return true;
    return false;
}
