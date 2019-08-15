#include "maze_display.h"

MazeDisplay::~MazeDisplay() {
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

bool MazeDisplay::init(unsigned int height, unsigned int width) {
    unsigned int window_height = height * DOTS_PER_CELL;
    unsigned int window_width = width * DOTS_PER_CELL;

    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to init SDL. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    this->window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width,
        window_height, SDL_WINDOW_SHOWN);
    if (!this->window) {
        std::cerr << "Failed to create window. Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void MazeDisplay::display(Maze maze) {
    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }
}
