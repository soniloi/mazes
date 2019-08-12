#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "maze_generator.h"
#include "mock_int_generator.h"

using testing::_;
using testing::Return;

namespace {

class MazeGeneratorTest : public ::testing::Test {
protected:
  MockIntGenerator ig;
  MazeGenerator generator;
};

TEST_F(MazeGeneratorTest, GenerateSmallHeight) {
    EXPECT_DEATH({
        generator.generate(&ig, 2, 11);
    }, ".*Height must be at least 3");
}

TEST_F(MazeGeneratorTest, GenerateSmallWidth) {
    EXPECT_DEATH({
        generator.generate(&ig, 7, 1);
    }, ".*Width must be at least 3");
}

TEST_F(MazeGeneratorTest, GenerateEvenHeight) {
    EXPECT_DEATH({
        generator.generate(&ig, 6, 11);
    }, ".*Height must be odd");
}

TEST_F(MazeGeneratorTest, GenerateEvenWidth) {
    EXPECT_DEATH({
        generator.generate(&ig, 7, 10);
    }, ".*Width must be odd");
}

TEST_F(MazeGeneratorTest, GenerateAlwaysSelectingFirst) {
    unsigned int height = 5;
    unsigned int width = 7;
    EXPECT_CALL(ig, generate(0, _)).WillRepeatedly(Return(0));
    bool expected[height][width] = {
        {false, false, false, false, false, false, false},
        {false, true,  true,  true,  true,  true,  false},
        {false, true,  false, true,  false, true,  false},
        {false, true,  false, true,  false, true,  false},
        {false, false, false, false, false, false, false}
    };

    Maze maze = generator.generate(&ig, height, width);

    bool** actual = maze.grid();
    for (unsigned int i = 0; i < height; ++i) {
        for (unsigned int j = 0; j < width; ++j) {
            ASSERT_EQ(expected[i][j], actual[i][j]);
        }
    }
}
}

int main(int argc, char ** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
