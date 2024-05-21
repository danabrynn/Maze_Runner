#include "consolegame.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"
#define UNDERLINE "\033[4m"


/**
 * Continuously gets input from user to allow movement through the maze via console
 * @param maze - the maze
*/
void ConsoleGame::getInput(Maze & maze) {
    char input;
    do {
        system("clear");
        printCenteredTitle("Maze Generator 3000", maze.getWidth());
        maze.printMaze(x, y);
        std::cout << BLUE << "\nEnter W/A/S/D to move (Q to quit): " << RESET;
        std::cin >> input;
        input = toupper(input);
        if (input != 'Q') {
            respondToInput(input, maze.getCell(x,y));
        }
    } while (input != 'Q');
}

/**
 * Responds to player input
 * @param input - player input
 * @param cell - maze cell at the player's current x and y coordinates
*/
void ConsoleGame::respondToInput(char input, Maze::Cell cell) {
    switch (input) {
        case 'W':
            if (cell.up_path) y--;
            break;
        case 'A':
            if (cell.left_path) x--;
            break;
        case 'S':
            if (cell.down_path) y++;
            break;
        case 'D':
            if (cell.right_path) x++;
            break;
        default:
            break;
    }
}

/**
 * Centers title above maze
 * @param title - the title to display
 * @param mazeWidth - width of maze
*/
void ConsoleGame::printCenteredTitle(std::string title, int mazeWidth) {
    int spaces = (mazeWidth / 2) * Maze::GRID_SIZE - (title.size()/2);
    for (int x = 0; x < spaces; x++) {
        std::cout << " ";
    }
    std::cout << BOLD << UNDERLINE << CYAN << title << RESET << "\n";
}