#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using std::vector;

struct DisjointSetsElement {
    int size, parent, rank;

    DisjointSetsElement(int size = 0, int parent = -1, int rank = 0) :
    size(size), parent(parent), rank(rank) {
    }
};

class DisjointSets {
private:
    int setCount;
    int size;
    int max_table_size;
    vector <DisjointSetsElement> sets;

public:
    
    DisjointSets(int size) : setCount(size), size(size), max_table_size(0), sets(size) {
        for (int i = 0; i < size; i++)
            sets[i].parent = i;
    }
    
    ~DisjointSets() {
        sets.clear();
    }

    int find(int table) {
        if (table != sets[table].parent) {
            sets[table].parent = find(sets[table].parent);
        }
        return sets[table].parent;
    }

    void merge(int destination, int source) {
        int realDestination = find(destination);
        int realSource = find(source);
        if (realDestination != realSource) {
            if (sets[realDestination].rank > sets[realSource].rank) {
                sets[realSource].parent = realDestination;
                sets[realDestination].size += sets[realSource].size;
                sets[realSource].size = 0;
                if (max_table_size < sets[realDestination].size) {
                    max_table_size = sets[realDestination].size;
                }
            } else {
                sets[realDestination].parent = realSource;
                sets[realSource].size += sets[realDestination].size;
                sets[realDestination].size = 0;
                if (sets[realDestination].rank == sets[realSource].rank) {
                    sets[realSource].rank += 1;
                }
                if (max_table_size < sets[realSource].size) {
                    max_table_size = sets[realSource].size;
                }
            }
            setCount--;
        }
    }
    
    int count() {
        return setCount;
    }
    
    bool connected(int left, int right) {
        return find(left)==find(right);
    }
};

struct Edge {
    int p1,p2;
    double d;
    Edge(int p1, int p2, double d) : p1(p1), p2(p2), d(d) {};
};

double distance(int x1, int y1, int x2, int y2) {
    return std::sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

double minimum_distance(vector<int> x, vector<int> y) {
    double result = 0.;
    //write your code here
    
    DisjointSets disjointSet(x.size());
    vector<Edge> edges;
    
    for (int i=0; i<x.size(); i++) {
        for (int j=i+1; j<x.size(); j++) {
            edges.push_back(Edge(i,j,distance(x[i],y[i],x[j],y[j])));
        }
    }
    
    std::sort(edges.begin(),edges.end(),[](const Edge& lhs, const Edge& rhs)->bool{return lhs.d<rhs.d;});
    //std::for_each(edges.begin(),edges.end(),[](Edge& elem){std::cout<<elem.d<<" ";});
    //std::cout<<"\n";
    
    for (int i=0; i<edges.size();i++) {
        if (!disjointSet.connected(edges[i].p1,edges[i].p2)) {
            disjointSet.merge(edges[i].p1,edges[i].p2);
            result += edges[i].d;
            if (disjointSet.count()==1) break;
        }
    }
    
    return result;
}

int main() {
    size_t n;
    std::cin >> n;
    vector<int> x(n), y(n);
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
