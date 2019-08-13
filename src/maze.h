#ifndef MAZE_H
#define MAZE_H

#include <vector>

class Maze {
public:
    using MazeRow = std::vector<bool>;
    using MazeGrid = std::vector<MazeRow>;
    using Coordinates = std::pair<int, int>;
    Maze(MazeGrid grid, Coordinates start, Coordinates finish);
    MazeGrid grid();
    Coordinates start();
    Coordinates finish();

private:
    MazeGrid grid_;
    Coordinates start_;
    Coordinates finish_;
};

#endif
