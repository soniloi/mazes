#include "gtest/gtest.h"

#include "player_event_handler.h"

using MazeGrid = Maze::MazeGrid;
using MazeRow = Maze::MazeRow;

namespace {

class PlayerEventHandlerTest : public ::testing::Test {
protected:
    PlayerEventHandler handler;
    SDL_Keysym keysym;
    SDL_KeyboardEvent key;
    SDL_Event event;
    void setup_event(int type, int repeat, SDL_Keycode sym) {
        keysym.sym = sym;
        key.keysym = keysym;
        key.repeat = repeat;
        event.key = key;
        event.type = type;
    }
    MazeGrid generate_grid(int width, std::vector<unsigned int>& pattern) {
        int height = pattern.size();
        MazeGrid grid(height);
        for (int i = 0; i < height; ++i) {
            grid[i] = MazeRow(width, CellType::Wall);
            for (int j = 0; j < width; ++j) {
                if ((pattern[i] >> j) & 1) {
                    grid[i][j] = CellType::Passage;
                }
            }
        }
        return grid;
    }
};

TEST_F(PlayerEventHandlerTest, HandleEventKeyDownRepeat) {
    Player player(0, 0);
    setup_event(SDL_KEYDOWN, 1, SDLK_RIGHT);

    handler.handle_event(player, event);

    ASSERT_EQ(0, player.velocity_x);
    ASSERT_EQ(0, player.velocity_y);
}

TEST_F(PlayerEventHandlerTest, HandleEventKeyDownNoRepeatNonArrow) {
    Player player(0, 0);
    setup_event(SDL_KEYDOWN, 0, SDLK_0);

    handler.handle_event(player, event);

    ASSERT_EQ(0, player.velocity_x);
    ASSERT_EQ(0, player.velocity_y);
}

TEST_F(PlayerEventHandlerTest, HandleEventKeyDownNoRepeatArrow) {
    Player player(0, 0);
    setup_event(SDL_KEYDOWN, 0, SDLK_RIGHT);

    handler.handle_event(player, event);

    ASSERT_EQ(1, player.velocity_x);
    ASSERT_EQ(0, player.velocity_y);
}

TEST_F(PlayerEventHandlerTest, HandleEventKeyUpRepeat) {
    Player player(0, 0);
    setup_event(SDL_KEYUP, 1, SDLK_RIGHT);

    handler.handle_event(player, event);

    ASSERT_EQ(0, player.velocity_x);
    ASSERT_EQ(0, player.velocity_y);
}

TEST_F(PlayerEventHandlerTest, HandleEventKeyUpNoRepeatNonArrow) {
    Player player(0, 0);
    setup_event(SDL_KEYUP, 0, SDLK_0);

    handler.handle_event(player, event);

    ASSERT_EQ(0, player.velocity_x);
    ASSERT_EQ(0, player.velocity_y);
}

TEST_F(PlayerEventHandlerTest, HandleEventKeyUpNoRepeatArrow) {
    Player player(0, 0);
    setup_event(SDL_KEYUP, 0, SDLK_RIGHT);

    handler.handle_event(player, event);

    ASSERT_EQ(0, player.position_x);
    ASSERT_EQ(0, player.position_y);
    ASSERT_EQ(-1, player.velocity_x);
    ASSERT_EQ(0, player.velocity_y);
}

TEST_F(PlayerEventHandlerTest, MovePlayerBelowWindowLimit) {
    Player player(1, 0);
    player.velocity_x = 0;
    player.velocity_y = -1;
    std::vector<unsigned int> pattern = {0x4007, 0x77D5, 0x155D, 0x7D71, 0x0405, 0x040F};
    MazeGrid grid = generate_grid(16, pattern);

    handler.move_player(player, grid);

    ASSERT_EQ(1, player.position_x);
    ASSERT_EQ(0, player.position_y);
}

TEST_F(PlayerEventHandlerTest, MovePlayerAboveWindowLimit) {
    Player player(15, 2);
    player.velocity_x = 1;
    player.velocity_y = 0;
    std::vector<unsigned int> pattern = {0x4007, 0x77D5, 0x155D, 0x7D71, 0x0405, 0x040F};
    MazeGrid grid = generate_grid(16, pattern);

    handler.move_player(player, grid);

    ASSERT_EQ(15, player.position_x);
    ASSERT_EQ(2, player.position_y);
}

TEST_F(PlayerEventHandlerTest, MovePlayerHitWall) {
    Player player(5, 3);
    player.velocity_x = 0;
    player.velocity_y = 3;
    std::vector<unsigned int> pattern = {0x4007, 0x77D5, 0x155D, 0x7D71, 0x0405, 0x040F};
    MazeGrid grid = generate_grid(16, pattern);

    handler.move_player(player, grid);

    ASSERT_EQ(5, player.position_x);
    ASSERT_EQ(3, player.position_y);
}

TEST_F(PlayerEventHandlerTest, MovePlayerWithinLimits) {
    Player player(5, 1);
    player.velocity_x = 3;
    player.velocity_y = 0;
    std::vector<unsigned int> pattern = {0x4007, 0x77D5, 0x155D, 0x7D71, 0x0405, 0x040F};
    MazeGrid grid = generate_grid(16, pattern);

    handler.move_player(player, grid);

    ASSERT_EQ(8, player.position_x);
    ASSERT_EQ(1, player.position_y);
}
}

int main(int argc, char ** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
