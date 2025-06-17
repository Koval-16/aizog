#ifndef AIZOG_HEAP_H
#define AIZOG_HEAP_H

// Struct representing single node in heap
struct HeapNode {
    int n;
    int key;
};

// Heap is used as a prio-queue, it's used in Prim and Dijkstra algorithms and increases their speed
class Heap {
public:
    Heap(int nodes, int* key);
    HeapNode extract_min();
    void decrease_key(int vertex, int new_key);
    bool is_empty();
    bool is_in_heap(int v);
private:
    int capacity;
    int size;
    int* pos;
    HeapNode* heap;
    void build_heap();
    int parent(int id);
    int left(int id);
    int right(int id);
    void heapify(int id);
};

#endif //AIZOG_HEAP_H