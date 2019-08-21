#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player(int x, int y);
    int position_x;
    int position_y;
    int velocity_x;
    int velocity_y;
};

#endif
