#include <gtest/gtest.h>

// Example test
TEST(ExampleTest, BasicAssertions) {
    EXPECT_EQ(7 + 10, 17);
    EXPECT_NE(7 * 10, 60);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}