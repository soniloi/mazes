#include "maze_display.h"

MazeDisplay::~MazeDisplay() {
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

bool MazeDisplay::init(unsigned int height, unsigned int width, std::string filepath) {
    bool success = true;
    success = init_sdl(height, width);
    if (success) {
        success = init_media(filepath);
    }
    return success;
}

bool MazeDisplay::init_sdl(unsigned int height, unsigned int width) {
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

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if (!this->renderer) {
        std::cerr << "Failed to create renderer. Error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_SetRenderDrawColor(this->renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Failed to init SDL_image. Error: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

bool MazeDisplay::init_media(std::string path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "Failed to load image " << path << ". Error: " << SDL_GetError() << std::endl;
        return false;
    }

    this->texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    if (!this->texture) {
        std::cerr << "Failed to create texture from " << path << ". Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_FreeSurface(surface);
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

        SDL_RenderClear(this->renderer);

        SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);

        SDL_RenderPresent(this->renderer);
    }
}
