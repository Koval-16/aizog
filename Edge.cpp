#include "Edge.h"

int Edge::get_node() {
    return node;
}

int Edge::get_target_node() {
    return target_node;
}

int Edge::get_wage() {
    return wage;
}

Edge::Edge(){

}

Edge::Edge(int v1, int v2, int weight) {
    node = v1;
    target_node = v2;
    wage = weight;
}
