#include "maze.h"

using MazeGrid = Maze::MazeGrid;
using Coordinates = Maze::Coordinates;

Maze::Maze(MazeGrid grid, Coordinates start, Coordinates finish) {
    this->grid_ = grid;
    this->start_ = start;
    this->finish_ = finish;
}

MazeGrid Maze::grid() {
    return this->grid_;
}

Coordinates Maze::start() {
    return this->start_;
}

Coordinates Maze::finish() {
    return this->finish_;
}
