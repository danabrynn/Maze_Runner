#include "mazesolver.h"

/**
 * Constructor to create a maze solver
 * @param maze - the maze to be solved
*/
MazeSolver::MazeSolver(Maze & maze)
{
    solveMaze(maze);
}

/**
 * Returns a set containing the integer representation of all cells that are part of the maze solution
*/
std::set<int> MazeSolver::getSolution() {
    return solution;
}

/**
 * Finds a solution to the maze. Cells that are part of the solution are stored in this.solution
*/
void MazeSolver::solveMaze(Maze & maze) {
    // mark all cells unvisited
    for (int i = 0; i < maze.height; i++) {
        for (int j = 0; j < maze.width; j++) {
            maze.maze[j][i].isVisited = false;
        }
    }
    // solve
    solveMazeDFS(maze, maze.maze[0][0]);
}

/**
 * Recursively solves maze using depth-first search.
 * @param maze - maze to be solved
 * @param cell - starting cell for maze solution
*/
bool MazeSolver::solveMazeDFS(Maze & maze, Maze::Cell & cell) {
    cell.isVisited = true;
    if (cell.x == maze.width - 1 && cell.y == maze.height - 1) {
        solution.insert(maze.getCellInteger(cell.x, cell.y));
        return true;
    }

    auto unvisitedNeighbors = maze.getUnvisitedNeighbors(cell, false);
    bool solved = false;

    while (!unvisitedNeighbors.empty() && !solved) {
        if (solveMazeDFS(maze, *unvisitedNeighbors[0])) {
            solved = true;
            solution.insert(maze.getCellInteger(cell.x, cell.y));
        }
        unvisitedNeighbors = maze.getUnvisitedNeighbors(cell, false);
    }
    return solved;
}