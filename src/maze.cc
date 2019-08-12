#include "maze.h"

Maze::Maze(bool** grid) {
    this->grid_ = grid;
}

bool** Maze::grid() {
    return this->grid_;
}
