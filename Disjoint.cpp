//
// Created by kuba on 14.06.2025.
//

#include "Disjoint.h"

Disjoint::Disjoint(int nodes) {
    size = nodes;
    parent = new int[nodes];
    rank = new int[nodes];
    for(int i=0; i<nodes; i++){
        make_set(i);
    }
}

Disjoint::~Disjoint() {
    delete[] parent;
    delete[] rank;
}

void Disjoint::make_set(int n) {
    parent[n] = n;
    rank[n] = 0;
}

void Disjoint::union_set(int x, int y) {
    link(find_set(x), find_set(y));
}

int Disjoint::find_set(int x) {
    if(x!=parent[x]) parent[x] = find_set(parent[x]);
    return parent[x];
}

void Disjoint::link(int x, int y) {
    if(rank[x]>rank[y]) parent[y] = x;
    else parent[x] = y;
    if(rank[x]==rank[y]) rank[y]++;
}
