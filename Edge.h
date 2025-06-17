#ifndef AIZOG_EDGE_H
#define AIZOG_EDGE_H

// Represents edge, two nodes and the wage
class Edge {
private:
    int node;
    int target_node;
    int wage;
public:
    Edge();
    Edge(int v1, int v2, int weight);
    int get_node();
    int get_target_node();
    int get_wage();
};


#endif //AIZOG_EDGE_H
