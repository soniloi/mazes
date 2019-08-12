#include <iostream>

#include "maze.h"
#include "maze_generator.h"
#include "random_int_generator.h"

int main(int argc, char ** argv) {
    RandomIntGenerator rng(3010349);
    MazeGenerator generator;

    unsigned int height = 17;
    unsigned int width = 35;
    Maze maze = generator.generate(&rng, height, width);

    bool** grid = maze.grid();
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            if (!grid[i][j]) {
                std::cout << "██";
            }
            else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
}
