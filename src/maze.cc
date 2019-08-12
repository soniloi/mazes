#include "maze.h"

Maze::Maze(std::vector<std::vector<bool>> grid) {
    this->grid_ = grid;
}

std::vector<std::vector<bool>> Maze::grid() {
    return this->grid_;
}
