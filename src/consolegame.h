#ifndef CONSOLEGAME_H_
#define CONSOLEGAME_H_

#include <iostream>
#include <string>
#include <memory> 
#include <limits>
#include <vector>
#include <tuple> 
#include <unistd.h>
#include <set>

#include "maze.h"
#include "mazesolver.h"


class ConsoleGame { 

    public:
        /**
         * Constructor to create a console game. Initializes player coordinates to (0,0).
        */
        ConsoleGame();

        /**
         * Continuously gets input from user to allow movement through the maze via console
         * @param maze - the maze
        */
        void getInput();



    private:
        // Current player x and y coordinates in maze
        int x;
        int y;
        std::unique_ptr<Maze> maze;
        std::vector<std::tuple<int, int>> positions; // All positions player has visited
        std::set<int> solution; // positions in maze solution
        bool displaySolution;

        /**
         * Responds to player input
         * @param input - player input
         * @param cell - maze cell at the player's current x and y coordinates
        */
        void respondToInput(char input, Maze::Cell cell);

        /**
         * Centers title above maze
         * @param title - the title to display
         * @param mazeWidth - width of maze
        */
        void printCenteredTitle(std::string title, int mazeWidth);

        /**
         * Generates a new maze based on user input
        */
        void createMaze();

        /**
         * Gets an integer from console. Displays error message and reprompts user if integer not entered properly.
         * @param message - message to display prompting user for input
        */
        int getIntegerFromConsole(std::string message);

        /**
         * Responds to user reaching target
        */
        void endGame();

        /**
         * Records current x and y position in maze
        */
        void recordCurrentPosition();


};

#endif
