#include "maze_generator.h"

// TODO: remove
#include <iostream>

Maze MazeGenerator::generate(IntGenerator* ig, unsigned int height, unsigned int width) {
    assert(height >= 3 && "Height must be at least 3");
    assert(width >= 3 && "Width must be at least 3");
    assert(height % 2 == 1 && "Height must be odd");
    assert(width % 2 == 1 && "Width must be odd");

    std::vector<std::vector<bool>> result(height);
    for (unsigned int i = 0; i < height; ++i) {
        result[i] = std::vector<bool>(width, false);
    }

    // TODO: randomization should preferably choose coords near a corner
    unsigned int start_y = get_valid_index(ig, height);
    unsigned int start_x = get_valid_index(ig, width);
    unsigned int frontier_cell_y = start_y;
    unsigned int frontier_cell_x = start_x;

    result[frontier_cell_y][frontier_cell_x] = true;

    std::vector<std::pair<int, int>> frontier_cells = calculateNeighbours(result, frontier_cell_y, frontier_cell_x, false);
    std::cout << "starting at (" << start_y << "," << start_x << ")" << std::endl;

    while(!frontier_cells.empty()) {
        std::cout << "\tfrontier cells: " << std::endl;
        for (auto it = frontier_cells.begin(); it != frontier_cells.end(); it++) {
            std::cout << "\t\t(" << it->first << "," << it->second << ")" << std::endl;
        }

        int frontier_index = ig->generate(0, frontier_cells.size() - 1);
        std::pair<int, int> frontier_cell = frontier_cells[frontier_index];
        frontier_cell_y = frontier_cell.first;
        frontier_cell_x = frontier_cell.second;
        std::cout << "visiting (" << frontier_cell_y << "," << frontier_cell_x << ")" << std::endl;

        std::vector<std::pair<int, int>> passage_cells = calculateNeighbours(result, frontier_cell_y, frontier_cell_x, true);
        std::cout << "\tpassage cells: " << std::endl;
        for (auto it = passage_cells.begin(); it != passage_cells.end(); it++) {
            std::cout << "\t\t(" << it->first << "," << it->second << ")" << std::endl;
        }

        int passage_index = ig->generate(0, passage_cells.size() - 1);
        std::pair<int, int> passage_cell = passage_cells[passage_index];
        unsigned int passage_cell_y = passage_cell.first;
        unsigned int passage_cell_x = passage_cell.second;

        unsigned int open_x = (frontier_cell_x + passage_cell_x) / 2;
        unsigned int open_y = (frontier_cell_y + passage_cell_y) / 2;
        result[open_y][open_x] = true;
        result[frontier_cell_y][frontier_cell_x] = true;
        std::cout << "\tmarking (" << open_y << "," << open_x << ") passage" << std::endl;
        std::cout << "\tmarking (" << frontier_cell_y << "," << frontier_cell_x << ") passage" << std::endl;

        std::vector<std::pair<int, int>> closed_cells = calculateNeighbours(result, frontier_cell_y, frontier_cell_x, false);
        std::cout << "\tclosed cells: " << std::endl;
        for (auto it = closed_cells.begin(); it != closed_cells.end(); it++) {
            std::cout << "\t\t(" << it->first << "," << it->second << ")" << std::endl;
        }
        for (auto it = closed_cells.begin(); it != closed_cells.end(); it++) {
            std::pair<int, int> coords = *it;
            if (!result[it->first][it->second] && !contains_coords(frontier_cells, coords)) {
                frontier_cells.push_back(coords);
            }
        }

        frontier_cells.erase(frontier_cells.begin() + frontier_index);
        for (auto it = frontier_cells.begin(); it != frontier_cells.end(); it++) {
        }
        /*
        for (unsigned int i = 0; i < height; ++i) {
            for (unsigned int j = 0; j < width; ++j) {
                std::cout << result[i][j] << ' ';
            }
            std::cout << std::endl;
        }
        */
    }
    return Maze(result);
}

unsigned int MazeGenerator::get_valid_index(IntGenerator* ig, unsigned int limit) {
    return ig->generate(0, limit / 2 - 1) * 2 + 1;
}

std::vector<std::pair<int, int>> MazeGenerator::calculateNeighbours(std::vector<std::vector<bool>> maze,
    unsigned int y, unsigned int x, bool state) {
    unsigned int height = maze.size();
    unsigned int width = maze[0].size();

    std::vector<std::pair<int, int>> neighbours;

    if (y >= 2 && maze[y-2][x] == state) {
        neighbours.push_back(std::pair<int, int> (y-2, x));
    }
    if (y < (height - 2) && maze[y+2][x] == state) {
        neighbours.push_back(std::pair<int, int> (y+2, x));
    }
    if (x >= 2 && maze[y][x-2] == state) {
        neighbours.push_back(std::pair<int, int> (y, x-2));
    }
    if (x < (width - 2) && maze[y][x+2] == state) {
        neighbours.push_back(std::pair<int, int> (y, x+2));
    }

    return neighbours;
}

bool MazeGenerator::contains_coords(std::vector<std::pair<int, int>> coords_vec, std::pair<int, int> coords) {
    for (auto it = coords_vec.begin(); it != coords_vec.end(); it++) {
        if (it->first == coords.first && it->second == coords.second) {
            return true;
        }
    }
    return false;
}
