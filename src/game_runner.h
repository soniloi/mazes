#ifndef MAZE_DISPLAY_H
#define MAZE_DISPLAY_H

#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "game.h"
#include "player_event_handler.h"

class GameRunner {
public:
    GameRunner(int width, int height);
    bool init(std::string block_path, std::string finish_path, std::string dot_path);
    void run(Game* game);
    ~GameRunner();
private:
    static const int DOTS_PER_CELL = 24;
    int window_width;
    int window_height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* block_texture;
    SDL_Texture* finish_texture;
    SDL_Texture* dot_texture;
    std::map<CellType, SDL_Rect> clips;
    PlayerEventHandler handler;
    bool init_sdl(unsigned int height, unsigned int width);
    bool init_media(std::string block_path, std::string finish_path, std::string dot_path);
    bool load_image(std::string path, SDL_Texture*& texture);
    void init_clips(int block_size);
    void render_game(Maze::MazeGrid& grid, Maze::Coordinates& finish_point, Player* player);
    void render_grid(Maze::MazeGrid& grid);
    void render_cell(int position_x, int position_y, SDL_Texture*& texture);
    bool finished(Maze::Coordinates& finish_point, Player* player);
};

#endif
