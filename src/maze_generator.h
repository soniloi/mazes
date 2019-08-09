#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include "int_generator.h"

class MazeGenerator {
public:
    bool** generate(IntGenerator* ig, unsigned int width, unsigned int height);
};

#endif
