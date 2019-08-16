#ifndef MAZE_DISPLAY_H
#define MAZE_DISPLAY_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "maze.h"

class MazeDisplay {
public:
    bool init(unsigned int height, unsigned int width, std::string filepath);
    void display(Maze maze);
    ~MazeDisplay();
private:
    static const int DOTS_PER_CELL = 24;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    bool init_sdl(unsigned int height, unsigned int width);
    bool init_media(std::string path);
};

#endif
