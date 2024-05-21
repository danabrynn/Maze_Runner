#ifndef CONSOLEGAME_H_
#define CONSOLEGAME_H_

#include <iostream>
#include <string>
#include "maze.h"


class ConsoleGame { 

    public:
        /**
         * Continuously gets input from user to allow movement through the maze via console
         * @param maze - the maze
        */
        void getInput(Maze & maze);



    private:
        // Current player x and y coordinates in maze
        int x = 0;
        int y = 0;

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


};

#endif
