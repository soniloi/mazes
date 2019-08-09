#include "maze_generator.h"

bool** MazeGenerator::generate(IntGenerator* ig, unsigned int width, unsigned int height) {
    bool** result = new bool*[height];
    for (unsigned int i = 0; i < height; ++i) {
        result[i] = new bool[width];
        for (unsigned int j = 0; j < width; ++j) {
            result[i][j] = false;
        }
    }
    return result;
}
