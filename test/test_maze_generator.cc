#include "gtest/gtest.h"

#include "maze_generator.h"
#include "mock_int_generator.h"

namespace {

TEST(GenerateTest, TestResult) {
    unsigned int width = 5;
    unsigned int height = 7;

    MockIntGenerator ig;
    MazeGenerator generator;

    bool** maze = generator.generate(&ig, width, height);

    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
             ASSERT_FALSE(maze[i][j]);
        }
    }
}

}

int main(int argc, char ** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
