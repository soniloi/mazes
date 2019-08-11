#include "maze_generator.h"

// TODO: remove
#include <iostream>

bool** MazeGenerator::generate(IntGenerator* ig, unsigned int height, unsigned int width) {
    bool** result = new bool*[height];
    for (unsigned int i = 0; i < height; ++i) {
        result[i] = new bool[width];
        for (unsigned int j = 0; j < width; ++j) {
            result[i][j] = false;
        }
    }

    // TODO: randomize, preferably choosing coords near a corner?
    unsigned int frontier_cell_y = 1;
    unsigned int frontier_cell_x = 1;

    result[frontier_cell_y][frontier_cell_x] = true;

    std::vector<std::pair<int, int>> frontier_cells = calculateNeighbours(result, height, width, frontier_cell_y, frontier_cell_x, false);
    std::cout << "starting at (" << frontier_cell_y << "," << frontier_cell_x << ")" << std::endl;

    while(!frontier_cells.empty()) {
        std::cout << "\tfrontier cells: " << std::endl;
        for (auto it = frontier_cells.begin(); it != frontier_cells.end(); it++) {
            std::cout << "\t\t(" << it->first << "," << it->second << ")" << std::endl;
        }

        int frontier_index = ig->generate(frontier_cells.size()) - 1;
        std::pair<int, int> frontier_cell = frontier_cells[frontier_index];
        frontier_cell_y = frontier_cell.first;
        frontier_cell_x = frontier_cell.second;
        std::cout << "visiting (" << frontier_cell_y << "," << frontier_cell_x << ")" << std::endl;

        std::vector<std::pair<int, int>> passage_cells = calculateNeighbours(result, height, width, frontier_cell_y, frontier_cell_x, true);
        std::cout << "\tpassage cells: " << std::endl;
        for (auto it = passage_cells.begin(); it != passage_cells.end(); it++) {
            std::cout << "\t\t(" << it->first << "," << it->second << ")" << std::endl;
        }

        int passage_index = ig->generate(passage_cells.size()) - 1;
        std::pair<int, int> passage_cell = passage_cells[passage_index];
        unsigned int passage_cell_y = passage_cell.first;
        unsigned int passage_cell_x = passage_cell.second;

        unsigned int open_x = (frontier_cell_x + passage_cell_x) / 2;
        unsigned int open_y = (frontier_cell_y + passage_cell_y) / 2;
        result[open_y][open_x] = true;
        result[frontier_cell_y][frontier_cell_x] = true;
        std::cout << "\tmarking (" << open_y << "," << open_x << ") passage" << std::endl;
        std::cout << "\tmarking (" << frontier_cell_y << "," << frontier_cell_x << ") passage" << std::endl;

        std::vector<std::pair<int, int>> closed_cells = calculateNeighbours(result, height, width, frontier_cell_y, frontier_cell_x, false);
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
    return result;
}

std::vector<std::pair<int, int>> MazeGenerator::calculateNeighbours(bool** maze, unsigned int height, unsigned int width,
        unsigned int y, unsigned int x, bool state){
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
