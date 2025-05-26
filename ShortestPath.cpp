//
// Created by kuba on 23.05.2025.
//

#include "ShortestPath.h"

void ShortestPath::dijkstra(Graph graph) {
    // 1.Inicjujemy tablicę: wierzchołek początkowy droga=0, pozostałe droga=MAX
    // 2.Dla wszystkich wierzchołków: relaksacja dróg
    // - jeśli krawędź zmniejsza drogę, to aktualizujemy w tablicy
    // 3.Gdy zakończymy relaksację krawedzi danego wierzchołka, to:
    // - usuwamy go z puli, a następny wierzchołek to ten o aktualnie najmniejszej drodze
    // 4.Wyznaczamy ścieżkę od ostatniego
}

void ShortestPath::bellman(Graph graph) {
    // 1.Tworzymy liste krawędzi
    // 2.Inicjujemy tablicę: wierzchołek początkowy droga=0, reszta=MAX
    // 3.Lecimy po kolei krawędzie, relaksacja, jeśli zmniejsza to do tabeli
    // 4.Tyle iteracji ile wierzchołków
}