#ifndef MAZE_H
#define MAZE_H

#include <vector>

class Maze {
public:
    using MazeRow = std::vector<bool>;
    using MazeGrid = std::vector<MazeRow>;
    Maze(MazeGrid grid);
    MazeGrid grid();

private:
    MazeGrid grid_;
};

#endif
