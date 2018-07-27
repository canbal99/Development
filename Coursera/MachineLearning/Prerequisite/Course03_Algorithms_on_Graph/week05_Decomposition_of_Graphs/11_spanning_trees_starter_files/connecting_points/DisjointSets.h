
#include <iostream>
#include <vector>

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