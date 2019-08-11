#include <iostream>

#include "maze_generator.h"
#include "random_int_generator.h"

int main(int argc, char ** argv) {
    RandomIntGenerator rng(3010349);
    MazeGenerator generator;

    unsigned int width = 35;
    unsigned int height = 16;
    bool** maze = generator.generate(&rng, height, width);

    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            if (!maze[i][j]) {
                std::cout << "██";
            }
            else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
}
