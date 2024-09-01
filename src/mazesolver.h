#ifndef MAZESOLVER_H_
#define MAZESOLVER_H_

#include <unordered_set>

#include "maze.h"

class MazeSolver { 
    public:
        /**
         * Constructor to create a maze solver
         * @param maze - the maze to be solved
        */
        MazeSolver(Maze & maze);

        /**
         * Returns a set containing the integer representation of all cells that are part of the maze solution
        */
        std::set<int> getSolution();


    private:
        std::set<int> solution;

        /**
         * Finds a solution to the maze. Cells that are part of the solution are stored in this.solution
         */
        void solveMaze(Maze & maze);

        /**
         * Recursively solves maze using depth-first search.
         * @param maze - maze to be solved
         * @param cell - starting cell for maze solution
        */
        bool solveMazeDFS(Maze & maze, Maze::Cell & cell);

};

#endif