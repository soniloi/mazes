#include "player_event_handler.h"

using MazeGrid = Maze::MazeGrid;

void PlayerEventHandler::handle_event(Player& player, SDL_Event& event) {
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_UP: player.velocity_y -= PLAYER_MOVEMENT_VELOCITY; break;
            case SDLK_DOWN: player.velocity_y += PLAYER_MOVEMENT_VELOCITY; break;
            case SDLK_LEFT: player.velocity_x -= PLAYER_MOVEMENT_VELOCITY; break;
            case SDLK_RIGHT: player.velocity_x += PLAYER_MOVEMENT_VELOCITY; break;
            default: break;
        }
    }
    else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_UP: player.velocity_y += PLAYER_MOVEMENT_VELOCITY; break;
            case SDLK_DOWN: player.velocity_y -= PLAYER_MOVEMENT_VELOCITY; break;
            case SDLK_LEFT: player.velocity_x += PLAYER_MOVEMENT_VELOCITY; break;
            case SDLK_RIGHT: player.velocity_x -= PLAYER_MOVEMENT_VELOCITY; break;
            default: break;
        }
    }
}

void PlayerEventHandler::move_player(Player& player, MazeGrid& grid) {
    int next_x = player.position_x + player.velocity_x;
    if (next_x < 0 || (unsigned) next_x >= grid[0].size() || grid[player.position_y][next_x] == CellType::Wall) {
        next_x -= player.velocity_x;
    }
    player.position_x = next_x;

    int next_y = player.position_y + player.velocity_y;
    if (next_y < 0 || (unsigned) next_y >= grid.size() || grid[next_y][player.position_x] == CellType::Wall) {
        next_y -= player.velocity_y;
    }
    player.position_y = next_y;
}
