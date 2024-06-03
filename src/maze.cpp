#include "maze.h"

static const int RIGHT_WALL = 0;
static const int DOWN_WALL = 1;

/**
 * Constructor to create a random maze
 * @param width - number of cells in maze width
 * @param height - number of cells in maze height
 * @param animate - show maze generation process
 * @param algorithm - maze generation algorithm to use (DFS, Kruskal)
*/
Maze::Maze(int width, int height, bool animate, Algorithm algorithm)
    : width(width),
      height(height),
      animate(animate),
      rng(std::random_device{}())
{
    generateMaze(width, height, algorithm);
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
 * @param algorithm - maze generation algorithm to use
*/
void Maze::generateMaze(int width, int height, Algorithm algorithm) {
    maze = new Cell*[width];
    for (int i = 0; i < width; i++) {
        maze[i] = new Cell[height];
        for (int j = 0; j < height; j++) {
            maze[i][j].x = i;
            maze[i][j].y = j;
        }
    }
    if (algorithm == DFS) {
        recursivelyGenerateMaze(maze[width/2][height/2]);
    } else if (algorithm == Kruskal) {
        kruskalGenerateMaze();
    }
}

/**
 * Recursively generates maze using depth-first search.
 * @param cell - the starting cell for maze generation
*/
void Maze::recursivelyGenerateMaze(Cell & cell) {
    cell.isVisited = true;
    auto unvisitedNeighbors = getUnvisitedNeighbors(cell);
    std::uniform_int_distribution<int> dist(0, unvisitedNeighbors.size() - 1);
    while (!unvisitedNeighbors.empty()) {
        int next_index = dist(rng);
        Cell * next_cell = unvisitedNeighbors[next_index];
        removeWall(cell, *next_cell);
        animateMaze("Maze Generation : depth first search starting at maze center");
        recursivelyGenerateMaze(*next_cell);
        unvisitedNeighbors = getUnvisitedNeighbors(cell);
        dist = std::uniform_int_distribution<int>(0, unvisitedNeighbors.size() - 1);
    }
}

/**
 * Generates maze using Kruskal's algorithm
*/
void Maze::kruskalGenerateMaze() {
    auto walls = getRandomizedListOfWalls();
    DisjointSet cell_set(width*height);
    int cell_number,  next_cell_number;
    for (const auto& wall : walls) {
        cell_number = std::get<0>(wall);
        if (std::get<1>(wall) == RIGHT_WALL) {
            next_cell_number = cell_number + 1;
        } else {
            next_cell_number = cell_number + width;
        }
        if (cell_set.find(cell_number) != cell_set.find(next_cell_number)) {
            removeWall(maze[cell_number % width][cell_number / width], maze[next_cell_number % width][next_cell_number / width]);
            cell_set.setUnion(cell_number, next_cell_number);
            animateMaze("Maze Generation : Kruskal's Algorithm");
        }
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

/**
 * Returns int representing cell's location in maze grid
 * @param x - cell's x coordinate in maze
 * @param y - cell's y coordinate in maze
*/
int Maze::getCellInteger(int x, int y) {
    return (y * width) + x;
}

/**
 * Returns a list of all the walls in a maze in a randomized order. Wall represented as a tuple
 * with first int storing the cell's position in the maze (getCellInteger(x, y)) and the second int 
 * storing whether the wall is a RIGHT_WALL or DOWN_WALL.
*/
std::vector<std::tuple<int, int>> Maze::getRandomizedListOfWalls() {
    std::vector<std::tuple<int, int>> walls;
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            std::cout << "x: " << x << "y: " << y << std::endl;
            if (x != width -1) {
                walls.push_back(std::make_tuple(getCellInteger(x, y), RIGHT_WALL));
            }
            if (y != height -1) {
                walls.push_back(std::make_tuple(getCellInteger(x, y), DOWN_WALL));
            }
        }
    }
    std::shuffle(walls.begin(), walls.end(), rng);
    return walls;
}

/**
 * Clears terminal window, prints current state of maze, and suspends execution for sleepTime if 
 * this->animate = true. Otherwise does nothing.
 * @param title - string to print above maze
 * @param sleepTime - length of time to sleep in microseconds, must be < 1000000
*/
void Maze::animateMaze(std::string title, int sleepTime) {
    if (this->animate) {
        system("clear");
        std::cout << title << "\n";
        printMaze();
        usleep(sleepTime);
    }
}