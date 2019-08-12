#ifndef MAZE_H
#define MAZE_H

#include <vector>

class Maze {
public:
    Maze(std::vector<std::vector<bool>> grid);
    std::vector<std::vector<bool>> grid();

private:
    std::vector<std::vector<bool>> grid_;
};

#endif
