#include "MST.h"
#include <iostream>
#include <sstream>
#include "Edge.h"
#include "EdgeList.h"
#include "Disjoint.h"
#include "Heap.h"

int MST::prim(Graph& graph, std::ostringstream* result) {
    int mst = 0;
    int v = graph.get_nodes();

    int* key = new int[v];
    int* parent = new int[v];
    bool* in_mst = new bool[v];

    for(int i=0; i<v; i++){
        key[i] = INT_MAX;
        parent[i] = -1;
        in_mst[i] = false;
    }
    key[0] = 0;
    Heap heap(v,key);

    while(!heap.is_empty()){
        HeapNode minimum = heap.extract_min();
        if (parent[minimum.n] != -1 && result) {
            *result << parent[minimum.n] << " -> " << minimum.n << " = " << key[minimum.n] << std::endl;
        }
        in_mst[minimum.n] = true;
        EdgeList list;
        list.set_capacity(graph.get_edges_number_from_node(minimum.n,false));
        graph.get_edges_from_node(list,minimum.n,false);
        for(int u=0; u<list.get_size(); u++){
            int target = list.get(u)->get_target_node();
            int weight = list.get(u)->get_wage();
            if(!in_mst[target] && heap.is_in_heap(target) && weight<key[target]){
                key[target] = weight;
                parent[target] = minimum.n;
                heap.decrease_key(target,weight);
            }
        }
    }

    for(int i = 1; i < v; i++) {
        mst += key[i];
    }
    delete[] key;
    delete[] parent;
    delete[] in_mst;
    return mst;
}

int MST::kruskal(Graph& graph, std::ostringstream* result) {
    int mst = 0;
    EdgeList list;
    list.set_capacity(graph.get_edges_number());
    graph.get_all_edges(list,false);
    sort(list);
    Disjoint dis(graph.get_nodes());
    int v = graph.get_nodes();

    int edges_added = 0;
    int index = 0;
    while(edges_added<graph.get_nodes()-1 && index < graph.get_edges_number()){
        int v1 = list.get(index)->get_node();
        int v2 = list.get(index)->get_target_node();
        int wage = list.get(index)->get_wage();
        if (dis.find_set(v1)!=dis.find_set(v2)) {
            mst += wage;
            edges_added++;
            dis.union_set(v1,v2);
            if (result) *result << v1 << "->" << v2 << " = " << wage << std::endl;
        }
        index++;
    }
    return mst;
}

void MST::sort(EdgeList& list) {
    quick_sort(list, 0, list.get_size()-1);
}

void MST::quick_sort(EdgeList& list, int left, int right){
    if(left<right){
        int q = partition(list, left, right);
        quick_sort(list,left,q);
        quick_sort(list,q+1,right);
    }
}

int MST::partition(EdgeList& list, int left, int right){
    int pivot_id = (right+left)/2;
    Edge* pivot = list.get(pivot_id);
    int i = left-1;
    int j = right+1;
    while(true){
        do{
            i++;
        } while(pivot->get_wage()>list.get(i)->get_wage());
        do{
            j--;
        } while(pivot->get_wage()<list.get(j)->get_wage());
        if(i<j){
            Edge* temp = list.get(i);
            list.set(i,list.get(j));
            list.set(j,temp);
        }
        else{
            if(j==right) j--;
            return j;
        }
    }
}