#include "consolegame.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define YELLOW  "\033[33m"
#define MAGENTA "\033[35m"
#define BOLD    "\033[1m"
#define UNDERLINE "\033[4m"

/**
 * Constructor to create a console game. Initializes player coordinates to (0,0).
*/
ConsoleGame::ConsoleGame()
    : x(0),
      y(0),
      maze(nullptr),
      displaySolution(false)
{}


/**
 * Continuously gets input from user to allow movement through the maze via console
 * @param maze - the maze
*/
void ConsoleGame::getInput() {
    std::cout << CYAN << BOLD << "\nWelcome! This program lets you generate randomized mazes and move through them."
              << RESET << CYAN <<"\nRecommended maze width/height is between ~" << YELLOW << " 15-55 cells "
              << CYAN << " (printing maze sizes larger than screen will cause bad formatting)\n\n" << RESET;
    char input;
    do {
        if (maze == nullptr) createMaze();
        system("clear");
        printCenteredTitle("Maze Generator 3000", maze->getWidth());
        if (displaySolution) {
            maze->printMaze(x, y, &solution);
        } else {
            maze->printMaze(x, y);
        }
        if (x == maze->getWidth() - 1 && y == maze->getHeight() -1) {
            endGame();
            return;
        }
        std::cout << BLUE << "\nEnter W/A/S/D to move, Z to toggle solution display, M to generate new maze (Q to quit): " << RESET;
        std::cin >> input;
        input = toupper(input);
        if (input != 'Q') {
            respondToInput(input, maze->getCell(x,y));
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
            recordCurrentPosition();
            break;
        case 'A':
            if (cell.left_path) x--;
            recordCurrentPosition();
            break;
        case 'S':
            if (cell.down_path) y++;
            recordCurrentPosition();
            break;
        case 'D':
            if (cell.right_path) x++;
            recordCurrentPosition();
            break;
        case 'M':
            createMaze();
            break;
        case 'Z':
            displaySolution = !displaySolution;
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

/**
 * Generates a new maze based on user input
*/
void ConsoleGame::createMaze() {
    int width = getIntegerFromConsole("Enter the maze width: ");
    int height = getIntegerFromConsole("Enter the maze height: ");
    char input;

    Maze::Algorithm algorithm = Maze::DFS;
    std::cout << "Algorithms:\n\tD - Depth First Search \n\tK - Kruskal's Algorithm \nMaze Generation Algorithm to Use: ";
    std::cin >> input;
    input = toupper(input);
    if (input == 'K') algorithm = Maze::Kruskal;

    bool animate = false;
    std::cout << "Show animation of maze generation? (Y/N): ";
    std::cin >> input;
    input = toupper(input);
    if (input == 'Y') animate = true;

    maze = std::make_unique<Maze>(width, height, animate, algorithm);
    x = 0;
    y = 0;
    positions.clear();
    recordCurrentPosition();
    MazeSolver solver(*maze);
    solution = solver.getSolution();
    displaySolution = false;
}

/**
 * Gets an integer from console. Displays error message and reprompts user if integer not entered properly.
 * @param message - message to display prompting user for input
*/
int ConsoleGame::getIntegerFromConsole(std::string message) {
    int variable;
    while (true) {
        std::cout << message;
        std::cin >> variable;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer." << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return variable;
        }
    }
}

/**
 * Responds to user reaching target
*/
void ConsoleGame::endGame() {
    for (const auto& position : positions) {
        system("clear");
        printCenteredTitle("Maze Generator 3000", maze->getWidth());
        if (displaySolution) {
            maze->printMaze(std::get<0>(position), std::get<1>(position), &solution);
        } else {
            maze->printMaze(std::get<0>(position), std::get<1>(position));
        }
        std::cout << BOLD << MAGENTA << "\nCONGRATULATIONS!!!" << RESET << std::endl;
        usleep(50000);
    }
    std::cout << "Generate new maze? (Y/N): ";
    char input;
    std::cin >> input;
    input = toupper(input);
    if (input == 'Y') {
        createMaze();
        getInput();
    }
}

/**
 * Records current x and y position in maze
*/
void ConsoleGame::recordCurrentPosition() {
    positions.push_back(std::make_tuple(x, y));
}