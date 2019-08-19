#ifndef MAZE_DISPLAY_H
#define MAZE_DISPLAY_H

#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "maze.h"

class MazeDisplay {
public:
    bool init(unsigned int height, unsigned int width, std::string block_path, std::string dot_path);
    void display(Maze maze);
    ~MazeDisplay();
private:
    static const int DOTS_PER_CELL = 24;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* block_texture;
    SDL_Texture* dot_texture;
    std::map<CellType, SDL_Rect> clips;
    bool init_sdl(unsigned int height, unsigned int width);
    bool init_media(std::string block_path, std::string dot_path);
    void init_clips(int block_size);
    void display_grid(Maze::MazeGrid grid);
};

#endif
