#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include <cassert>
#include <vector>

#include "int_generator.h"
#include "maze.h"

class MazeGenerator {
public:
    Maze generate(IntGenerator* ig, unsigned int height, unsigned int width);
private:
    unsigned int get_valid_index(IntGenerator* ig, unsigned int limit);
    std::vector<std::pair<int, int>> calculateNeighbours(std::vector<std::vector<bool>> maze, unsigned int y,
        unsigned int x, bool state);
    // TODO: replace this with a better check
    bool contains_coords(std::vector<std::pair<int, int>> coords_set, std::pair<int, int> coords);
};

#endif