#include "game_runner.h"

using Coordinates = Maze::Coordinates;
using MazeGrid = Maze::MazeGrid;

GameRunner::GameRunner(int width, int height) {
    this->window_width = width * DOTS_PER_CELL;
    this->window_height = height * DOTS_PER_CELL;
}

GameRunner::~GameRunner() {
    SDL_DestroyTexture(this->block_texture);
    SDL_DestroyTexture(this->finish_texture);
    SDL_DestroyTexture(this->dot_texture);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    IMG_Quit();
    SDL_Quit();
}

bool GameRunner::init(std::string block_path, std::string finish_path, std::string dot_path) {
    bool success = true;
    success = init_sdl(window_height, window_width);
    if (success) {
        success = init_media(block_path, finish_path, dot_path);
    }
    init_clips(DOTS_PER_CELL);
    return success;
}

bool GameRunner::init_sdl(unsigned int height, unsigned int width) {
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

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

bool GameRunner::init_media(std::string block_path, std::string finish_path, std::string dot_path) {
    bool success = load_image(block_path, this->block_texture);
    if (success) {
        success = load_image(finish_path, this->finish_texture);
    }
    if (success) {
        success = load_image(dot_path, this->dot_texture);
    }
    return success;
}

bool GameRunner::load_image(std::string path, SDL_Texture*& texture) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "Failed to load image " << path << ". Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
    texture = SDL_CreateTextureFromSurface(this->renderer, surface);
    if (!texture) {
        std::cerr << "Failed to create texture from " << path << ". Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_FreeSurface(surface);
    return true;
}

void GameRunner::init_clips(int block_size) {
    this->clips[CellType::Wall] = {0, 0, block_size, block_size};
    this->clips[CellType::Passage] = {0, block_size, block_size, block_size};
}

void GameRunner::run(Game* game) {
    Maze* maze = game->maze();
    Player* player = game->player();

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            this->handler.handle_event(*player, event);
        }

        MazeGrid grid = maze->grid();
        Coordinates finish_point = maze->finish();
        this->handler.move_player(*player, grid);
        render_game(grid, finish_point, player);
    }
}

void GameRunner::render_game(MazeGrid& grid, Coordinates& finish_point, Player* player) {
    SDL_RenderClear(this->renderer);
    render_grid(grid);
    render_cell(finish_point.second, finish_point.first, this->finish_texture);
    render_cell(player->position_x, player->position_y, this->dot_texture);
    SDL_RenderPresent(this->renderer);
}

void GameRunner::render_grid(MazeGrid& grid) {
    for (unsigned int i = 0; i < grid.size() ; ++i) {
        for (unsigned int j = 0; j < grid[0].size(); ++j) {
            int x = j * DOTS_PER_CELL;
            int y = i * DOTS_PER_CELL;
            SDL_Rect cell_rect = this->clips[grid[i][j]];
            SDL_Rect render_rect = {x, y, cell_rect.w, cell_rect.h};
            SDL_RenderCopy(this->renderer, this->block_texture, &cell_rect, &render_rect);
        }
    }
}

void GameRunner::render_cell(int position_x, int position_y, SDL_Texture*& texture) {
    int x = position_x * DOTS_PER_CELL;
    int y = position_y * DOTS_PER_CELL;
    SDL_Rect clip_rect = {0, 0, DOTS_PER_CELL, DOTS_PER_CELL};
    SDL_Rect render_rect = {x, y, DOTS_PER_CELL, DOTS_PER_CELL};
    SDL_RenderCopy(this->renderer, texture, &clip_rect, &render_rect);
}
