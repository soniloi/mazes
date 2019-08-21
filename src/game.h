#ifndef GAME_H
#define GAME_H

#include "maze.h"
#include "player.h"

class Game {
public:
    Game(Maze* maze, Player* player);
    Maze* maze();
    Player* player();
private:
    Maze* maze_;
    Player* player_;
};

#endif
