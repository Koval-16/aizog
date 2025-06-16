#include "Heap.h"
#include <cmath>
#include <iostream>

Heap::Heap(int nodes, int* key) {
    heap = new HeapNode[nodes];
    pos = new int[nodes];
    capacity = nodes;
    for(int i=0; i<nodes; i++){
        heap[i] = {i,key[i]};
        pos[i] = i;
    }
    build_heap();
}

void Heap::build_heap() {
    size = capacity;
    for(int i = size / 2 - 1; i>=0; i--){
        heapify(i);
    }
}

int Heap::parent(int id) {
    return (id - 1) / 2;
}

int Heap::left(int id) {
    return 2 * id + 1;
}

int Heap::right(int id) {
    return 2 * id + 2;
}

void Heap::heapify(int id) {
    int l = left(id);
    int r = right(id);
    int smallest = id;
    if (l < size && heap[l].key < heap[smallest].key) smallest = l;
    if (r < size && heap[r].key < heap[smallest].key) smallest = r;
    if (smallest != id) {
        HeapNode temp = heap[id];
        heap[id] = heap[smallest];
        heap[smallest] = temp;
        pos[heap[id].n] = id;
        pos[heap[smallest].n] = smallest;
        heapify(smallest);
    }
}

HeapNode Heap::extract_min() {
    HeapNode min = heap[0];
    heap[0] = heap[size-1];
    pos[heap[0].n] = 0;
    pos[min.n] = -1;
    size--;
    heapify(0);
    return min;
}

void Heap::decrease_key(int vertex, int new_key) {
    int i = pos[vertex];
    heap[i].key = new_key;

    while (i != 0 && heap[parent(i)].key > heap[i].key) {
        HeapNode temp = heap[i];
        heap[i] = heap[parent(i)];
        heap[parent(i)] = temp;
        pos[heap[i].n] = i;
        pos[heap[parent(i)].n] = parent(i);
        i = parent(i);
    }
}

bool Heap::is_empty() {
    return size == 0;
}

bool Heap::is_in_heap(int v) {
    return pos[v]!=-1;
}
