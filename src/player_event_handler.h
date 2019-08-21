#ifndef PLAYER_EVENT_HANDLER_H
#define PLAYER_EVENT_HANDLER_H

#include <SDL2/SDL.h>

#include "player.h"

class PlayerEventHandler {
public:
    void handle_event(Player* player, SDL_Event& event);
    void move_player(Player* player, int player_dot_size, int window_width, int window_height);
private:
    static const int PLAYER_MOVEMENT_VELOCITY = 12;
    int calculate_next(int current_position, int velocity, int player_dot_size, int limit);
};

#endif
