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

    graph_adj.init(edges);
    graph_list.init(edges);
    graph_inc.init(edges);


    int connected_nodes[nodes];
    int connected_size = 0;
    int waiting_room[nodes];
    int waiting_size = nodes;

    for(int i=0; i<nodes; i++) waiting_room[i] = i;

    // Creating first spanning tree (enough for undirected)
    connected_nodes[connected_size++] = 0;
    waiting_room[0] = waiting_room[--waiting_size];
    while(waiting_size!=0){
        int pos_1 = rand()%connected_size;
        int pos_2 = rand()%waiting_size;
        int removed = waiting_room[pos_2];
        waiting_room[pos_2] = waiting_room[--waiting_size];
        int wage = (rand()%1000)+1;
        connected_nodes[connected_size++] = removed;
        graph_adj.add_edge(connected_nodes[pos_1],removed,wage,directed);
        graph_inc.add_edge(connected_nodes[pos_1],removed,wage,directed);
        graph_list.add_edge(connected_nodes[pos_1],removed,wage,directed);
        current_edges++;
    }

    if(directed){
        int no_out_edges[nodes];
        int no_out_size = 0;
        for(int i=0; i<nodes; i++){
            if(!graph_adj.has_edges_from_node(i,directed)){
                no_out_edges[no_out_size++] = i;
            }

        }
        int iteration = 0;
        while(no_out_size!=0){
            int pos_1 = rand()%no_out_size;
            int pos_2=0;
            iteration++;
            int chosen = no_out_edges[pos_1];
            no_out_edges[pos_1] = no_out_edges[--no_out_size];
            int wage = (rand()%1000)+1;
            graph_adj.add_edge(chosen,pos_2,wage,directed);
            graph_inc.add_edge(chosen,pos_2,wage,directed);
            graph_list.add_edge(chosen,pos_2,wage,directed);
            current_edges++;
        }
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
