#ifndef PLAYER_EVENT_HANDLER_H
#define PLAYER_EVENT_HANDLER_H

#include <SDL2/SDL.h>

#include "maze.h"
#include "player.h"

class PlayerEventHandler {
public:
    void handle_event(Player& player, SDL_Event& event);
    void move_player(Player& player, Maze::MazeGrid& grid);
private:
    static const int PLAYER_MOVEMENT_VELOCITY = 1;
};

#endif
