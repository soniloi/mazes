#include "maze.h"

using MazeGrid = Maze::MazeGrid;

Maze::Maze(MazeGrid grid) {
    this->grid_ = grid;
}

MazeGrid Maze::grid() {
    return this->grid_;
}
