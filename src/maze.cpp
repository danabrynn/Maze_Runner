#include "maze.h"


/**
 * Constructor to create a random maze
 * @param width - number of cells in maze width
 * @param height - number of cells in maze height
 * @param animate - show maze generation process
*/
Maze::Maze(int width, int height, bool animate)
    : width(width),
      height(height),
      animate(animate) 
{
    generateMaze(width, height);
}

/**
 * Destructor; frees all cells associated with maze
*/
Maze::~Maze() {
    if (maze == nullptr) return;

    for (int i = 0; i < width; i++) // delete inner arrays
        delete[] maze[i];
    delete[] maze; // delete outer array

    maze = nullptr;
}

/**
 * Randomly generates a maze
 * @param width - maze width
 * @param height - maze height
*/
void Maze::generateMaze(int width, int height) {
    maze = new Cell*[width];
    for (int i = 0; i < width; i++) {
        maze[i] = new Cell[height];
        for (int j = 0; j < height; j++) {
            maze[i][j].x = i;
            maze[i][j].y = j;
        }
    }
    srand(time(0));
    recursivelyGenerateMaze(maze[width/2][height/2]);
}

/**
 * Recursively generates maze using depth-first search.
 * @param cell - the starting cell for maze generation
*/
void Maze::recursivelyGenerateMaze(Cell & cell) {
    cell.isVisited = true;
    auto unvisitedNeighbors = getUnvisitedNeighbors(cell);
    while (!unvisitedNeighbors.empty()) {
        int next_index = rand() % unvisitedNeighbors.size();
        Cell * next_cell = unvisitedNeighbors[next_index];
        removeWall(cell, *next_cell);
        if (animate) {
            system("clear");
            std::cout << "Maze Generation : depth first search starting at maze center" << "\n";
            printMaze();
            usleep(30000);
        }
        recursivelyGenerateMaze(*next_cell);
        unvisitedNeighbors = getUnvisitedNeighbors(cell);
    }
}

/**
 * Returns a cell from the maze
 * @param x - x coordinate of the cell
 * @param y - y coordinate of the cell
*/
Maze::Cell Maze::getCell(int x, int y) const {
    return maze[x][y];
}

/**
 * Returns maze width
*/
int Maze::getWidth() {
    return width;
}

/**
 * Returns maze height
*/
int Maze::getHeight() {
    return height;
}


/**
 * Prints a representation of maze to console
 * @param x - optional parameter, x coordinate of point to mark on maze
 * @param y - optional parameter, y coordinate of point to mark on maze
*/
void Maze::printMaze(int x, int y) {
    // print top border
    for (int j = 0; j < width; j++) {
        std::cout << " __";
    }
    std::cout << "\n";

    // print maze
    for (int i = 0; i < height; i++) {
        std::cout << '|';
        for (int j = 0; j < width; j++) {
            if (!maze[j][i].down_path) {
                if (x == j && y == i) {
                    std::cout << "_";
                    formattedPrint('X');
                } else {
                    std::cout << "__";
                }
            } else {
                if (x == j && y == i) {
                    std::cout << " ";
                    formattedPrint('X');
                } else {
                    std::cout << "  ";
                }
            }
            if (!maze[j][i].right_path) {
                std::cout << '|';
            } else {
                std::cout << ' ';
            }
        }
        if (i == height - 1) std::cout << " <- Goal";
        std::cout << "\n";
    }
}

/**
 * Returns a list of pointers to all of a cell's unvisited neighbors. The cells directly above, below, right
 * and left of a cell are considered its neighbors. A cell will be marked as visted if there is an existing
 * path to the cell.
 * @param cell - cell whose neighbors will be returned
*/
std::vector<Maze::Cell*> Maze::getUnvisitedNeighbors(Cell & cell) const {
    std::vector<Maze::Cell*> unvisitedNeighbors;
    if (cell.x > 0 && !(maze[cell.x - 1][cell.y].isVisited)) {
        unvisitedNeighbors.push_back(&maze[cell.x - 1][cell.y]);
    }
    if (cell.x < width - 1 && !(maze[cell.x + 1][cell.y].isVisited)) {
        unvisitedNeighbors.push_back(&maze[cell.x + 1][cell.y]);
    }
    if (cell.y > 0 && !(maze[cell.x][cell.y - 1].isVisited)) {
        unvisitedNeighbors.push_back(&maze[cell.x][cell.y - 1]);
    }
    if (cell.y < height - 1 && !(maze[cell.x][cell.y + 1].isVisited)) {
        unvisitedNeighbors.push_back(&maze[cell.x][cell.y + 1]);
    }
    return unvisitedNeighbors;
}

/**
* Removes the wall between two cells if they are neighbors.
 * @param cellA - first cell
 * @param cellB - second cell
*/
void Maze::removeWall(Cell & cellA, Cell & cellB) {
    if (cellA.x + 1 == cellB.x && cellA.y == cellB.y) {
        cellA.right_path = true;
        cellB.left_path = true;
    } else if (cellA.x - 1 == cellB.x && cellA.y == cellB.y) {
        cellA.left_path = true;
        cellB.right_path = true;
    } else if (cellA.x == cellB.x && cellA.y + 1 == cellB.y) {
        cellA.down_path = true;
        cellB.up_path = true;
    } else if (cellA.x == cellB.x && cellA.y - 1 == cellB.y) {
        cellA.up_path = true;
        cellB.down_path = true;
    } 
}

/**
 * helper for printMaze
 * @param x - char to print 
*/
void Maze::formattedPrint(char x) {
    std::cout << "\033[1m" << "\033[32m" << x << "\033[0m";
}

