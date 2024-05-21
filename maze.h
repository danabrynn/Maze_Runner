#ifndef MAZE_H_
#define MAZE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>

class Maze { 
    public:
        
        /**
         * Constructor to create a random maze
        */
        Maze();

        /**
         * Constructor to create a random maze
         * @param width - number of cells in maze width
         * @param height - number of cells in maze height
        */
        Maze(int width, int height);

        /**
         * Destructor; frees all cells associated with maze
        */
        ~Maze();

        /**
         * Prints a representation of maze to console
        */
        void printMaze();



    private:
        /**
         * Struct representing each cell in the maze. Comtaining the cell's x and y coordinates, visited status, 
         * and how it is connected to neighboring cells.
        */
        struct Cell 
        {
            int x;
            int y;
            bool left_path = false;
            bool right_path = false;
            bool up_path = false;
            bool down_path = false;
            bool isVisited = false;
        };

        int width;
        int height;
        struct Cell** maze;

        /**
         * Randomly generates a maze
         * @param width - maze width
         * @param height - maze height
        */
        void generateMaze(int width, int height);

        /**
         * Recursively generates maze using depth-first search.
         * @param cell - the starting cell for maze generation
        */
        void recursivelyGenerateMaze(Cell & cell);

        /**
         * Returns a list of pointers to all of a cell's unvisited neighbors. The cells directly above, below, right
         * and left of a cell are considered its neighbors. A cell will be marked as visted if there is an existing
         * path to the cell.
         * @param cell - cell whose neighbors will be returned
        */
        std::vector<Cell*> getUnvisitedNeighbors(Cell & cell) const;

        /**
         * Removes the wall between two cells if they are neighbors.
         * @param cellA - first cell
         * @param cellB - second cell
        */
        void removeWall(Cell & cellA, Cell & cellB);

};

#endif