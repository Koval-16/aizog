#ifndef AIZOGRAF_EDGELIST_H
#define AIZOGRAF_EDGELIST_H
#include "Edge.h"

// List storing edges
class EdgeList {
private:
    Edge** edges;
    int size;
    int capacity;
    void resize();
public:
    EdgeList();
    ~EdgeList();

    void add_edge(int v1, int v2, int wage);
    void remove_edge(int id);
    void set_capacity(int set);
    Edge* get(int id);
    Edge** get_array();
    int get_size();
    void set(int id, Edge* edge);
};


#endif //AIZOGRAF_EDGELIST_H
