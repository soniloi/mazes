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
    Maze::MazeGrid generate_blank_grid(unsigned int height, unsigned int width);
    Maze::Coordinates generate_start_point(IntGenerator* ig, unsigned int height, unsigned int width);
    unsigned int get_valid_index(IntGenerator* ig, unsigned int limit);
    std::vector<Maze::Coordinates> calculateNeighbours(Maze::MazeGrid maze, Maze::Coordinates cell, CellType type);
    Maze::Coordinates remove_random_coordinates(IntGenerator* ig, std::vector<Maze::Coordinates>& vec);
    Maze::Coordinates find_passage_cell(IntGenerator* ig, Maze::MazeGrid grid, Maze::Coordinates frontier_cell);
    void add_closed_to_frontier(Maze::MazeGrid grid, std::vector<Maze::Coordinates>& frontier_cells, Maze::Coordinates frontier_cell);
    // TODO: replace this with a better check
    bool contains_coords(std::vector<Maze::Coordinates> coords_collection, Maze::Coordinates coords);
};

#endif
