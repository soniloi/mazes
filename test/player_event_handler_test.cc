#include "gtest/gtest.h"

#include "player_event_handler.h"

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
};

TEST_F(PlayerEventHandlerTest, HandleEventKeyDownRepeat) {
    Player player(0, 0);
    setup_event(SDL_KEYDOWN, 1, SDLK_RIGHT);

    handler.handle_event(&player, event);

    ASSERT_EQ(0, player.velocity_x);
    ASSERT_EQ(0, player.velocity_y);
}

TEST_F(PlayerEventHandlerTest, HandleEventKeyDownNoRepeatNonArrow) {
    Player player(0, 0);
    setup_event(SDL_KEYDOWN, 0, SDLK_0);

    handler.handle_event(&player, event);

    ASSERT_EQ(0, player.velocity_x);
    ASSERT_EQ(0, player.velocity_y);
}

TEST_F(PlayerEventHandlerTest, HandleEventKeyDownNoRepeatArrow) {
    Player player(0, 0);
    setup_event(SDL_KEYDOWN, 0, SDLK_RIGHT);

    handler.handle_event(&player, event);

    ASSERT_EQ(12, player.velocity_x);
    ASSERT_EQ(0, player.velocity_y);
}

TEST_F(PlayerEventHandlerTest, HandleEventKeyUpRepeat) {
    Player player(0, 0);
    setup_event(SDL_KEYUP, 1, SDLK_RIGHT);

    handler.handle_event(&player, event);

    ASSERT_EQ(0, player.velocity_x);
    ASSERT_EQ(0, player.velocity_y);
}

TEST_F(PlayerEventHandlerTest, HandleEventKeyUpNoRepeatNonArrow) {
    Player player(0, 0);
    setup_event(SDL_KEYUP, 0, SDLK_0);

    handler.handle_event(&player, event);

    ASSERT_EQ(0, player.velocity_x);
    ASSERT_EQ(0, player.velocity_y);
}

TEST_F(PlayerEventHandlerTest, HandleEventKeyUpNoRepeatArrow) {
    Player player(0, 0);
    setup_event(SDL_KEYUP, 0, SDLK_RIGHT);

    handler.handle_event(&player, event);

    ASSERT_EQ(0, player.position_x);
    ASSERT_EQ(0, player.position_y);
    ASSERT_EQ(-12, player.velocity_x);
    ASSERT_EQ(0, player.velocity_y);
}

TEST_F(PlayerEventHandlerTest, MovePlayerWithinWindowLimits) {
    Player player(56, 37);
    player.velocity_x = 18;
    player.velocity_y = -24;

    handler.move_player(&player, 6, 80, 50);

    ASSERT_EQ(74, player.position_x);
    ASSERT_EQ(13, player.position_y);
}

TEST_F(PlayerEventHandlerTest, MovePlayerExceedWindowLimits) {
    Player player(56, 37);
    player.velocity_x = 19;
    player.velocity_y = -39;

    handler.move_player(&player, 6, 80, 50);

    ASSERT_EQ(56, player.position_x);
    ASSERT_EQ(37, player.position_y);
}
}

int main(int argc, char ** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
