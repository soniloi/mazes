#ifndef MAZE_H
#define MAZE_H

#include <vector>

enum class CellType {
    Wall,
    Passage
};

class Maze {
public:
    using MazeRow = std::vector<CellType>;
    using MazeGrid = std::vector<MazeRow>;
    using Coordinates = std::pair<unsigned int, unsigned int>;
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
