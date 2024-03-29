#include "maze_generator.h"

using MazeRow = Maze::MazeRow;
using MazeGrid = Maze::MazeGrid;
using Coordinates = Maze::Coordinates;

Maze MazeGenerator::generate(IntGenerator* ig, unsigned int height, unsigned int width) {
    assert(height >= 5 && "Height must be at least 5");
    assert(width >= 5 && "Width must be at least 5");
    assert(height % 2 == 1 && "Height must be odd");
    assert(width % 2 == 1 && "Width must be odd");

    MazeGrid grid = generate_blank_grid(height, width);
    Coordinates start_point = generate_start_point(ig, height, width);

    Coordinates frontier_cell = Coordinates(start_point.first, start_point.second);
    grid[frontier_cell.first][frontier_cell.second] = CellType::Passage;

    std::vector<Coordinates> frontier_cells = calculateNeighbours(grid, start_point, CellType::Wall);
    while(!frontier_cells.empty()) {
        frontier_cell = remove_random_coordinates(ig, frontier_cells);
        Coordinates passage_cell = find_passage_cell(ig, grid, frontier_cell);
        grid[passage_cell.first][passage_cell.second] = CellType::Passage;
        grid[frontier_cell.first][frontier_cell.second] = CellType::Passage;
        add_closed_to_frontier(grid, frontier_cells, frontier_cell);
    }

    Coordinates finish_point = Coordinates(frontier_cell.first, frontier_cell.second);
    return Maze(grid, start_point, finish_point);
}

MazeGrid MazeGenerator::generate_blank_grid(unsigned int height, unsigned int width) {
    MazeGrid grid(height);
    for (unsigned int i = 0; i < height; ++i) {
        grid[i] = MazeRow(width, CellType::Wall);
    }
    return grid;
}

Coordinates MazeGenerator::generate_start_point(IntGenerator* ig, unsigned int height, unsigned int width) {
    unsigned int y = get_valid_index(ig, height);
    unsigned int x = get_valid_index(ig, width);
    return Coordinates(y, x);
}

unsigned int MazeGenerator::get_valid_index(IntGenerator* ig, unsigned int limit) {
    return ig->generate(0, limit / 2 - 1) * 2 + 1;
}

std::vector<Coordinates> MazeGenerator::calculateNeighbours(MazeGrid maze, Coordinates cell, CellType type) {
    unsigned int height = maze.size();
    unsigned int width = maze[0].size();
    unsigned int y = cell.first;
    unsigned int x = cell.second;

    std::vector<Coordinates> neighbours;

    if (y >= 2 && maze[y-2][x] == type) {
        neighbours.push_back(Coordinates(y-2, x));
    }
    if (y < (height - 2) && maze[y+2][x] == type) {
        neighbours.push_back(Coordinates(y+2, x));
    }
    if (x >= 2 && maze[y][x-2] == type) {
        neighbours.push_back(Coordinates(y, x-2));
    }
    if (x < (width - 2) && maze[y][x+2] == type) {
        neighbours.push_back(Coordinates(y, x+2));
    }

    return neighbours;
}

Coordinates MazeGenerator::remove_random_coordinates(IntGenerator* ig, std::vector<Coordinates>& vec) {
    int index = ig->generate(0, vec.size() - 1);
    Coordinates coords = vec[index];
    vec.erase(vec.begin() + index);
    return coords;
}

Coordinates MazeGenerator::find_passage_cell(IntGenerator* ig, MazeGrid grid, Coordinates frontier_cell) {
    std::vector<Coordinates> adjacent_passage_cells = calculateNeighbours(grid, frontier_cell, CellType::Passage);
    Coordinates adjacent_passage_cell = remove_random_coordinates(ig, adjacent_passage_cells);
    unsigned int passage_cell_y = (frontier_cell.first + adjacent_passage_cell.first) / 2;
    unsigned int passage_cell_x = (frontier_cell.second + adjacent_passage_cell.second) / 2;
    return Coordinates(passage_cell_y, passage_cell_x);
}


void MazeGenerator::add_closed_to_frontier(MazeGrid grid, std::vector<Coordinates>& frontier_cells, Coordinates frontier_cell) {
    std::vector<Coordinates> closed_cells = calculateNeighbours(grid, frontier_cell, CellType::Wall);
    for (auto it = closed_cells.begin(); it != closed_cells.end(); it++) {
        Coordinates coords = *it;
        if (grid[it->first][it->second] != CellType::Passage && !contains_coords(frontier_cells, coords)) {
            frontier_cells.push_back(coords);
        }
    }
}

bool MazeGenerator::contains_coords(std::vector<Coordinates> coords_collection, Coordinates coords) {
    for (auto it = coords_collection.begin(); it != coords_collection.end(); it++) {
        if (it->first == coords.first && it->second == coords.second) {
            return true;
        }
    }
    return false;
}
