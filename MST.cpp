//
// Created by kuba on 23.05.2025.
//

#include "MST.h"
#include <iostream>
#include "Edge.h"
#include "EdgeList.h"

int MST::prim(Graph& graph, int represenation) {
    int mst = 0;

    int colours[graph.get_nodes()];
    for(int i=0; i<graph.get_nodes(); i++) colours[i] = i;

    int node = 0;
    colours[node] = -1;

    int edges_added = 0;
    int index = 0;

    EdgeList list;
    graph.get_edges_from_node(list,node,false);

    while(edges_added<graph.get_nodes()-1 && index<list.get_size()){
        sort(list);
        int v1 = list.get(index)->get_node();
        int v2 = list.get(index)->get_target_node();
        int wage = list.get(index)->get_wage();
        if(colours[v1]!=colours[v2]){
            std::cout << v1 << "->" << v2 << " = " << wage << std::endl;
            colours[v1] = -1;
            colours[v2] = -1;
            mst += wage;
            edges_added++;
            graph.get_edges_from_node(list,v2,false);
            list.remove_edge(index);
            index=-1;
        }
        index++;
    }

    return mst;
}

int MST::kruskal(Graph& graph, int representation) {
    int mst = 0;
    // 1.tworzymy listę krawędzi grafu
    EdgeList list;
    graph.get_all_edges(list,false);
    for(int i=0; i<list.get_size(); i++){
        std::cout << list.get(i)->get_node() << " <-> "<< list.get(i)->get_target_node() << " - " << list.get(i)->get_wage() << std::endl;
    }
    // 2.sortujemy krawędzie w tej liście wg ich wag
    sort(list);
    // 3.nadajemy unikalne kolory węzłom grafu (identyfikacja cykli)
    int colours[graph.get_nodes()];
    for(int i=0; i<graph.get_nodes(); i++) colours[i] = i;
    // 4.wybieramy kolejne krawędzie grafu zachłannie
    // 5.jeżeli co najmniej jeden z węzłów ma inny kolor niż kolor grafu, to dołączamy
    // 6.musimy dodać n-1 krawędzi
    int edges_added = 0;
    int index = 0;
    while(edges_added<graph.get_nodes()-1 && index < graph.get_edges_number()){
        int v1 = list.get(index)->get_node();
        int v2 = list.get(index)->get_target_node();
        int wage = list.get(index)->get_wage();
        if(colours[v1]!=colours[v2]){
            colours[v1] = -1;
            colours[v2] = -1;
            mst += wage;
            edges_added++;
            std::cout << v1 << "->" << v2 << " = " << wage << std::endl;
        }
        index++;
    }
    std::cout << mst << std::endl;
    return mst;
}

void MST::sort(EdgeList& list) {
    int size = list.get_size();
    for(int i=0; i<size-1; i++){
        for(int j=0; j<size-i-1; j++){
            if(list.get(j)->get_wage() > list.get(j+1)->get_wage()){
                Edge* temp = list.get(j);
                list.set(j, list.get(j+1));
                list.set(j+1, temp);
            }
        }
    }
}