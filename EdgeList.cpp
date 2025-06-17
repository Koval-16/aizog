#include "EdgeList.h"

EdgeList::EdgeList() {
    size = 0;
    capacity = 1;
    edges = new Edge*[capacity];
}

EdgeList::~EdgeList(){
    for(int i=0; i<size; i++) delete edges[i];
    delete[] edges;
}

void EdgeList::add_edge(int v1, int v2, int wage) {
    resize();
    edges[size++] = new Edge(v1,v2,wage);
}

void EdgeList::remove_edge(int id) {
    delete edges[id];
    for(int i=id; i<size-1; i++) edges[i]=edges[i+1];
    size--;
    capacity--;
}

void EdgeList::resize(){
    capacity++;
    Edge** new_edges = new Edge*[capacity];
    for(int i=0; i<size; i++) new_edges[i] = edges[i];
    delete[] edges;
    edges = new_edges;
}

Edge *EdgeList::get(int id) {
    return edges[id];
}

int EdgeList::get_size() {
    return size;
}

void EdgeList::set(int id, Edge *edge) {
    edges[id] = edge;
}

Edge **EdgeList::get_array() {
    return edges;
}
