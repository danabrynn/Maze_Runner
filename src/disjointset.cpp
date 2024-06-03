#include "disjointset.h"

/**
 * Constructor to create a disjoint set
 * @param n - size of disjoint set
*/
DisjointSet::DisjointSet(int n) {
    parent.resize(n, -1);
}

/**
 * Finds the representative (root node) of the set that x is a member of. Performs path compression.
 * @param x - element to find set representative of
*/
int DisjointSet::find(int x) {
    if (parent[x] < 0) return x;
    parent[x] = find(parent[x]);
    return parent[x];
}

/**
 * Union by size on the sets that x and y are members of. Does nothing if x and y are already in the same set.
 * @param x - first element
 * @param y - second element
*/
void DisjointSet::setUnion(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY) return;
    // x set has more elements
    if (parent[rootX] < parent[rootY]) {
        parent[rootX] += parent[rootY];
        parent[rootY] = rootX;
    // y set has more elements (or equal)
    } else {
        parent[rootY] += parent[rootX];
        parent[rootX] = rootY;
    }
}