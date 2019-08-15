#ifndef MAZE_DISPLAY_H
#define MAZE_DISPLAY_H

#include <iostream>
#include <SDL2/SDL.h>

#include "maze.h"

class MazeDisplay {
public:
    bool init(unsigned int height, unsigned int width);
    void display(Maze maze);
    ~MazeDisplay();
private:
    static const int DOTS_PER_CELL = 24;
    SDL_Window* window;
};

#endif
