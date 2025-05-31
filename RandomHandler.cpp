//
// Created by kuba on 19.05.2025.
//

#include "RandomHandler.h"
#include "Graph.h"
#include "GraphAdjacency.h"
#include <cstdlib>
#include <iostream>

void RandomHandler::generate_graph(int nodes, float density,GraphAdjacency& graph_adj, Graph& graph_inc, Graph& graph_list, bool directed) {
    // Calculating number of edges
    int max_edges = (nodes-1)*nodes/2;
    if(directed) max_edges=(nodes-1)*nodes;
    int edges = max_edges*density;
    int current_edges = 0;

    // Init tabs
    graph_adj.set_nodes(nodes);
    graph_inc.set_nodes(nodes);
    graph_list.set_nodes(nodes);

    graph_adj.init();
    graph_inc.init();
    graph_list.init();
    int* connected_nodes = nullptr;
    int connected_size = 0;
    int* waiting_room = nullptr;
    int waiting_size = 0;
    for(int i=0; i<nodes; i++){
        waiting_room = add_number(waiting_room,waiting_size,i);
    }

    if (!directed) {
        // Creating first edge (spanning tree for undirected)
        connected_nodes = add_number(connected_nodes,connected_size, remove_number(waiting_room,waiting_size,0));
        int p = rand()%waiting_size;
        connected_nodes = add_number(connected_nodes,connected_size, remove_number(waiting_room,waiting_size,p));
        int w = (rand()%1000)+1;
        graph_adj.add_edge(connected_nodes[0],connected_nodes[1],w,directed);
        graph_inc.add_edge(connected_nodes[0],connected_nodes[1],w,directed);
        graph_list.add_edge(connected_nodes[0],connected_nodes[1],w,directed);
        current_edges++;

        while(waiting_size!=0){
            int chosen = rand()%connected_size;
            int pos = rand()%waiting_size;
            int removed = remove_number(waiting_room,waiting_size,pos);
            w = (rand()%1000)+1;
            graph_adj.add_edge(connected_nodes[chosen],removed, w, directed);
            graph_inc.add_edge(connected_nodes[chosen],removed, w, directed);
            graph_list.add_edge(connected_nodes[chosen],removed, w, directed);
            current_edges++;
            connected_nodes = add_number(connected_nodes,connected_size, removed);
        }
    } else {
        // Creating Hamiltonian cycle for directed graph
        int* cycle = new int[nodes];
        for (int i = 0; i < nodes; i++) {
            cycle[i] = i;
        }

        // Fisher-Yates shuffle (excluding node 0 as starting point)
        for (int i = nodes - 1; i > 1; i--) {
            int j = 1 + rand() % i; // don't swap 0
            std::swap(cycle[i], cycle[j]);
        }

        // Create Hamiltonian cycle
        for (int i = 0; i < nodes - 1; i++) {
            int from = cycle[i];
            int to = cycle[i + 1];
            int w = rand() % 1000 + 1;
            graph_adj.add_edge(from, to, w, directed);
            graph_inc.add_edge(from, to, w, directed);
            graph_list.add_edge(from, to, w, directed);
            current_edges++;
        }
        // Closing the cycle
        int w = rand() % 1000 + 1;
        graph_adj.add_edge(cycle[nodes - 1], cycle[0], w, directed);
        graph_inc.add_edge(cycle[nodes - 1], cycle[0], w, directed);
        graph_list.add_edge(cycle[nodes - 1], cycle[0], w, directed);
        current_edges++;

        delete[] cycle;
    }


    // Creating other edges
    int** list_of_edges = new int*[max_edges];
    int index = 0;
    for(int i=0; i<nodes; i++){
        int k;
        if(directed) k=0;
        else k=i+1;
        for(int j=k; j<nodes; j++){
            if(!graph_adj.edge_exists(i,j) && i!=j){
                list_of_edges[index] = new int[2];
                list_of_edges[index][0] = i;
                list_of_edges[index][1] = j;
                index++;
            }
        }
    }

    // Fisher Yates
    for(int i=index-1; i>0; i--){
        int j=rand()%(i+1);
        int* temp = list_of_edges[i];
        list_of_edges[i] = list_of_edges[j];
        list_of_edges[j] = temp;
    }
    int id = 0;
    while(current_edges<edges){
        int v1 = list_of_edges[id][0];
        int v2 = list_of_edges[id][1];
        int w = rand()%1000;
        graph_adj.add_edge(v1,v2,w,directed);
        graph_inc.add_edge(v1,v2,w,directed);
        graph_list.add_edge(v1,v2,w,directed);
        current_edges++;
        id++;
    }
    for(int i = 0; i < index; ++i){
        delete[] list_of_edges[i];
    }
    delete[] list_of_edges;
}

int* RandomHandler::add_number(int *tab, int &size, int number) {
    int* new_tab = new int[size+1];
    for(int i=0; i<size; i++) new_tab[i] = tab[i];
    new_tab[size] = number;
    delete[] tab;
    size++;
    return new_tab;
}

int RandomHandler::remove_number(int *&tab, int &size, int position){
    int* new_tab = new int[size-1];
    int new_size = 0;
    int removed_number;
    for(int i=0; i<size; i++){
        if(i!=position){
            new_tab[new_size] = tab[i];
            new_size++;
        }
        else{
            removed_number = tab[i];
        }
    }
    delete[] tab;
    tab = new_tab;
    size--;
    return removed_number;
}