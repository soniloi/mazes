#include "maze_display.h"

using MazeGrid = Maze::MazeGrid;

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
    init_clips(DOTS_PER_CELL);
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

void MazeDisplay::init_clips(int block_size) {
    this->clips[CellType::Wall] = {0, 0, block_size, block_size};
    this->clips[CellType::Passage] = {0, block_size, block_size, block_size};
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

        display_grid(maze.grid());

        SDL_RenderPresent(this->renderer);
    }
}

void MazeDisplay::display_grid(MazeGrid grid) {
    for (unsigned int i = 0; i < grid.size() ; ++i) {
        for (unsigned int j = 0; j < grid[0].size(); ++j) {
            int x = j * DOTS_PER_CELL;
            int y = i * DOTS_PER_CELL;
            SDL_Rect cell_rect = this->clips[grid[i][j]];
            SDL_Rect render_rect = {x, y, cell_rect.w, cell_rect.h};
            SDL_RenderCopy(this->renderer, this->texture, &cell_rect, &render_rect);
        }
    }
}

