#ifndef DISJOINTSET_H_
#define DISJOINTSET_H_

#include <vector>

class DisjointSet { 
    public:
        /**
         * Constructor to create a disjoint set
         * @param n - size of disjoint set
        */
        DisjointSet(int n);

        /**
         * Finds the representative (root node) of the set that x is a member of. Performs path compression.
         * @param x - element to find set representative of
        */
        int find(int x);

        /**
         * Union by size on the sets that x and y are members of. Does nothing if x and y are already in the same set.
         * @param x - first element
         * @param y - second element
        */
        void setUnion(int x, int y);


    private:
        // Stores the index of parent. If element is a root node, stores -1 * number of elements in its tree. 
        std::vector<int> parent;

};

#endif