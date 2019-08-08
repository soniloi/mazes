#include "gtest/gtest.h"

#include "random_int_generator.h"

namespace {

TEST(GenerateTest, TestResult) {
    RandomIntGenerator generator(3010349);

    ASSERT_EQ(41, generator.generate(491));
}

}

int main(int argc, char ** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
