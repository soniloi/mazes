#include "game.h"

Game::Game(Maze* maze, Player* player) {
    this->maze_ = maze;
    this->player_ = player;
}

Maze* Game::maze() {
    return maze_;
}

Player* Game::player() {
    return player_;
}
