#include <gtest/gtest.h>
#include "../src/BigArray.cpp"

TEST(MyClassTest, test_sozd) {
    BitArray res(10);
    int i = res[4];
    ASSERT_EQ(i, 0);
    ASSERT_NE(res[6], 1);
}
