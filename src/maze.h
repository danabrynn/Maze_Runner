#ifndef MAZE_H_
#define MAZE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>

class Maze { 
    public:
        static const int GRID_SIZE = 3;
        
        /**
         * Constructor to create a random maze
         * @param width - number of cells in maze width
         * @param height - number of cells in maze height
         * @param animate - show maze generation process
        */
        Maze(int width = 35, int height = 20, bool animate = false);

        /**
         * Destructor; frees all cells associated with maze
        */
        virtual ~Maze();

        /**
         * Prints a representation of maze to console
         * @param x - optional parameter, x coordinate of point to mark on maze
         * @param y - optional parameter, y coordinate of point to mark on maze
        */
        void printMaze(int x = -1, int y = -1);

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

        /**
         * Returns a cell from the maze
         * @param x - x coordinate of the cell
         * @param y - y coordinate of the cell
        */
        Cell getCell(int x, int y) const;

        /**
         * Returns maze width
        */
        int getWidth();

        /**
         * Returns maze height
        */
        int getHeight();

    private:

        int width;
        int height;
        struct Cell** maze;
        bool animate;

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

        /**
         * helper for printMaze
         * @param x - char to print 
        */
        void formattedPrint(char x);

};

#endif