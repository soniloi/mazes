#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include <vector>

#include "int_generator.h"

class MazeGenerator {
public:
    bool** generate(IntGenerator* ig, unsigned int height, unsigned int width);
private:
    std::vector<std::pair<int, int>> calculateNeighbours(bool** maze, unsigned int height, unsigned int width,
        unsigned int y, unsigned int x, bool state);
    // TODO: replace this with a better check
    bool contains_coords(std::vector<std::pair<int, int>> coords_set, std::pair<int, int> coords);
};

#endif
