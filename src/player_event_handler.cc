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
    player.position_x = calculate_next(player.position_x, player.velocity_x, grid[0].size());
    player.position_y = calculate_next(player.position_y, player.velocity_y, grid.size());
}

int PlayerEventHandler::calculate_next(int current_position, int velocity, int limit) {
    int next = current_position + velocity;
    if (next < 0 || next >= limit) {
        next -= velocity;
    }
    return next;
}
