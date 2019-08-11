#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "maze_generator.h"
#include "mock_int_generator.h"

using testing::_;
using testing::Return;

namespace {

TEST(GenerateTest, TestMazeAlwaysSelectingFirst) {
    unsigned int height = 5;
    unsigned int width = 7;
    MockIntGenerator ig;
    MazeGenerator generator;
    EXPECT_CALL(ig, generate(0, _)).WillRepeatedly(Return(0));
    bool expected[height][width] = {
        {false, false, false, false, false, false, false},
        {false, true,  true,  true,  true,  true,  false},
        {false, true,  false, true,  false, true,  false},
        {false, true,  false, true,  false, true,  false},
        {false, false, false, false, false, false, false}
    };

    bool** actual = generator.generate(&ig, height, width);

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
