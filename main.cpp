#include "maze.h"
#include "consolegame.h"

int main() {
    Maze myMaze;
    ConsoleGame consoleGame;
    consoleGame.getInput(myMaze);
    // myMaze.printMaze();
    return 0;
}