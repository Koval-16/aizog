#ifndef AIZOG_HEAP_H
#define AIZOG_HEAP_H

struct HeapNode {
    int n;     // numer wierzchołka
    int key;   // klucz (priorytet)
};

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