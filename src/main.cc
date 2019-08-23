#include <iostream>

#include "game.h"
#include "maze.h"
#include "maze_generator.h"
#include "random_int_generator.h"
#include "maze_display.h"

using MazeGrid = Maze::MazeGrid;
using Coordinates = Maze::Coordinates;

int main(int argc, char ** argv) {
    RandomIntGenerator rng(3010349);
    MazeGenerator generator;

    unsigned int height = 17;
    unsigned int width = 35;
    Maze maze = generator.generate(&rng, height, width);

    Coordinates start_point = maze.start();
    Coordinates finish_point = maze.finish();

    MazeGrid grid = maze.grid();
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            if (i == start_point.first && j == start_point.second) {
                std::cout << "◁▷";
            }
            else if (i == finish_point.first && j == finish_point.second) {
                std::cout << "▷◁";
            }
            else if (grid[i][j] == CellType::Wall) {
                std::cout << "██";
            }
            else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "start point: (" << start_point.first << "," << start_point.second << ")" << std::endl;
    std::cout << "finish point: (" << finish_point.first << "," << finish_point.second << ")" << std::endl;

    MazeDisplay display(width, height);
    if (!display.init("res/blocks.png", "res/dot.png")) {
        exit(EXIT_FAILURE);
    }

    Player player(start_point.second, start_point.first);
    Game game(&maze, &player);
    display.display(&game);
}
