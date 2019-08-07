#include "gtest/gtest.h"

#include "game.h"

namespace {

TEST(RunTest, TestResult) {
    Game game;
    ASSERT_EQ(71, game.run());
}

}

int main(int argc, char ** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
