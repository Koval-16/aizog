//
// Created by kuba on 23.05.2025.
//

#include "ShortestPath.h"
#include "Math.h"
#include "EdgeList.h"
#include <iostream>
#include <sstream>

int ShortestPath::dijkstra(Graph& graph, std::ostringstream* result) {
    // 1.Inicjujemy tablicę: wierzchołek początkowy droga=0, pozostałe droga=MAX
    // 2.Dla wszystkich wierzchołków: relaksacja dróg
    // - jeśli krawędź zmniejsza drogę, to aktualizujemy w tablicy
    // 3.Gdy zakończymy relaksację krawedzi danego wierzchołka, to:
    // - usuwamy go z puli, a następny wierzchołek to ten o aktualnie najmniejszej drodze
    // 4.Wyznaczamy ścieżkę od ostatniego

    // 1.Inicjujemy tablicę: wierzchołek początkowy droga=0, pozostałe droga=MAX
    int node = 0;
    int dijkstra_tab[graph.get_nodes()][2]; // [0]<-wartosc, [1]<-wierzcholek
    for(int i=0; i<graph.get_nodes(); i++){
        if(i==node){
            dijkstra_tab[i][0] = 0;
            dijkstra_tab[i][1] = node;
        }
        else{
            dijkstra_tab[i][0] = INT_MAX;
            dijkstra_tab[i][1] = -1;
        }
    }

    bool visited[graph.get_nodes()];
    for(int i=0; i<graph.get_nodes(); i++) visited[i]=false;

    // 2.Dla wszystkich wierzchołków: relaksacja dróg
    // - jeśli krawędź zmniejsza drogę, to aktualizujemy w tablicy
    int n = node;
    for(int j=0; j<graph.get_nodes(); j++){
        EdgeList list;
        graph.get_edges_from_node(list,n,true);
        for(int i=0; i<list.get_size(); i++){
            int target = list.get(i)->get_target_node();
            int new_wage = list.get(i)->get_wage()+dijkstra_tab[n][0];
            if(new_wage<dijkstra_tab[target][0]){
                dijkstra_tab[target][0]=new_wage;
                dijkstra_tab[target][1]=n;
            }
        }
        // 3.Gdy zakończymy relaksację krawedzi danego wierzchołka, to:
        // - usuwamy go z puli, a następny wierzchołek to ten o aktualnie najmniejszej drodze
        visited[n]=true;
        int lowest = INT_MAX;
        for(int i=0; i<graph.get_nodes(); i++){
            if(!visited[i]){
                if(dijkstra_tab[i][0]<lowest){
                    lowest=dijkstra_tab[i][0];
                    n = i;
                }
            }
        }
    }

    // 4.Wyznaczamy ścieżkę od ostatniego
    int end = 2;
    int value = dijkstra_tab[end][0];
    int src = dijkstra_tab[end][1];
    if(result) *result << "Value: " << value << " Path: " << end << " <-- ";
    while(src!=node){
        if(result) *result << src << " <-- ";
        src = dijkstra_tab[src][1];
    }
    if(result) *result << node << std::endl;
    return value;
}

int ShortestPath::bellman(Graph& graph, std::ostringstream* result) {
    // 1.Tworzymy liste krawędzi
    // 2.Inicjujemy tablicę: wierzchołek początkowy droga=0, reszta=MAX
    // 3.Lecimy po kolei krawędzie, relaksacja, jeśli zmniejsza to do tabeli
    // 4.Tyle iteracji ile wierzchołków

    // 1.Tworzymy liste krawędzi
    EdgeList list;
    graph.get_all_edges(list,true);

    // 2.Inicjujemy tablicę: wierzchołek początkowy droga=0, reszta=MAX
    int node = 0;
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
    for(int i=0; i<graph.get_nodes(); i++){
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

    // 4.Wyznaczamy ścieżkę od ostatniego
    int end = 2;
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