#include "ShortestPath.h"
#include "Math.h"
#include "EdgeList.h"
#include <iostream>
#include <sstream>
#include "Heap.h"

int ShortestPath::dijkstra(Graph& graph, int start_node, int end_node, std::ostringstream* result) {
    // 1.Inicjujemy tablicę: wierzchołek początkowy droga=0, pozostałe droga=MAX
    // 2.Dla wszystkich wierzchołków: relaksacja dróg
    // - jeśli krawędź zmniejsza drogę, to aktualizujemy w tablicy
    // 3.Gdy zakończymy relaksację krawedzi danego wierzchołka, to:
    // - usuwamy go z puli, a następny wierzchołek to ten o aktualnie najmniejszej drodze
    // 4.Wyznaczamy ścieżkę od ostatniego

    // 1.Inicjujemy tablicę: wierzchołek początkowy droga=0, pozostałe droga=MAX
    int node = start_node;
    int nodes = graph.get_nodes();
    int dist[nodes];
    int prev[nodes];

    for(int i = 0; i < nodes; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }
    dist[node] = 0;

    Heap heap(nodes, dist);

    while (!heap.is_empty()) {
        HeapNode minimal = heap.extract_min();
        int min = minimal.n;

        EdgeList list;
        graph.get_edges_from_node(list, min, true);

        for (int i=0; i < list.get_size(); i++) {
            int target = list.get(i)->get_target_node();
            int weight = list.get(i)->get_wage();
            if (heap.is_in_heap(target) && dist[min]!=INT_MAX && dist[min]+weight<dist[target]){
                dist[target] = dist[min]+weight;
                prev[target] = min;
                heap.decrease_key(target, dist[target]);
            }
        }
    }

    int end = end_node;
    if (dist[end] == INT_MAX) {
        if (result) *result << "Brak ścieżki z " << node << " do " << end << std::endl;
        return -1;
    }

    if (result) {
        *result << "Value: " << dist[end] << " Path: " << end;
        int src = prev[end];
        while (src != node) {
            *result << " <-- " << src;
            src = prev[src];
        }
        *result << " <-- " << node << std::endl;
    }
    return dist[end];
}

int ShortestPath::bellman(Graph& graph,int start_node, int end_node, std::ostringstream* result) {
    // 1.Tworzymy liste krawędzi
    // 2.Inicjujemy tablicę: wierzchołek początkowy droga=0, reszta=MAX
    // 3.Lecimy po kolei krawędzie, relaksacja, jeśli zmniejsza to do tabeli
    // 4.Tyle iteracji ile wierzchołków

    // 1.Tworzymy liste krawędzi
    EdgeList list;
    graph.get_all_edges(list,true);

    // 2.Inicjujemy tablicę: wierzchołek początkowy droga=0, reszta=MAX
    int node = start_node;
    int bellman_tab[graph.get_nodes()][2]; // [0]<-wartosc, [1]<-wierzcholek
    for(int i=0; i<graph.get_nodes(); i++){
        if(i==node){
            bellman_tab[i][0] = 0;
            bellman_tab[i][1] = node;
        }
        else{
            bellman_tab[i][0] = INT_MAX;
            bellman_tab[i][1] = -1;
        }
    }

    // 3.Lecimy po kolei krawędzie, relaksacja, jeśli zmniejsza to do tabeli
    // 4.Tyle iteracji ile wierzchołków
    for(int i=0; i<graph.get_nodes()-1; i++){
        for(int j=0; j<list.get_size(); j++){
            int source = list.get(j)->get_node();
            int target = list.get(j)->get_target_node();
            int new_wage = list.get(j)->get_wage();
            if(new_wage+bellman_tab[source][0] < bellman_tab[target][0] &&
            bellman_tab[source][0]!=INT_MAX){
                bellman_tab[target][0]= new_wage+bellman_tab[source][0];
                bellman_tab[target][1]= source;
            }
        }
    }
    for(int j=0; j<list.get_size(); j++){
        int source = list.get(j)->get_node();
        int target = list.get(j)->get_target_node();
        int new_wage = list.get(j)->get_wage();
        if(bellman_tab[source][0] != INT_MAX &&
           bellman_tab[source][0] + new_wage < bellman_tab[target][0]) {
            if(result) *result << "Wykryto cykl o ujemnej długości!" << std::endl;
            return -1;
        }
    }

    // 4.Wyznaczamy ścieżkę od ostatniego
    int end = end_node;
    int value = bellman_tab[end][0];
    int src = bellman_tab[end][1];
    if(result) *result << "Value: " << value << " Path: " << end << " <-- ";
    while(src!=node){
        if(result) *result << src << " <-- ";
        src = bellman_tab[src][1];
    }
    if(result) *result << node << std::endl;
    return value;
}