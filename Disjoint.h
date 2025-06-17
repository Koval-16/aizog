#ifndef AIZOG_DISJOINT_H
#define AIZOG_DISJOINT_H

//Class Disjoint represents structure of disjoint sets, it's used in Kruskal algorithm
class Disjoint {
public:
    Disjoint(int nodes);
    ~Disjoint();
    void make_set(int n);
    void union_set(int x, int y);
    int find_set(int x);
private:
    int* parent;
    int* rank;
    int size;
    void link(int x, int y);
};


#endif //AIZOG_DISJOINT_H
