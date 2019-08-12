#ifndef MAZE_H
#define MAZE_H

class Maze {
public:
    Maze(bool** grid);
    bool** grid();

private:
    bool** grid_;
};

#endif
