#include "pch.h"
#include <gtest\gtest.h>
#include "Array.h"

TEST(MyClassTest, test_sozd) {
    BitArray res(10);
    int i = res[4];
    ASSERT_EQ(i, 0);
    ASSERT_NE(res[6], 1);
}

TEST(MyClassTest, test_none) {
    BitArray res(10);
    ASSERT_EQ(res.none(), true);
}

TEST(MyClassTest, test_size) {
    BitArray res(10);
    ASSERT_EQ(res.size(), 10);
}

TEST(MyClassTest, test_string) {
    BitArray res(10);
    ASSERT_EQ(res.to_string(), "0000000000");
}

TEST(MyClassTest, test_empty) {
    BitArray res(10);
    ASSERT_EQ(res.empty(), false);
}

TEST(MyClassTest, test_set) {
    BitArray res(10);
    res.set(5, true);
    ASSERT_EQ(res[5], true);
}

TEST(MyClassTest, test_any) {
    BitArray res(10);
    res.set(5, true);
    ASSERT_EQ(res.any(), true);
}

TEST(MyClassTest, test_count) {
    BitArray res1(10);

    res1.set(5, true);
    ASSERT_EQ(res1.count(), 1);
}

TEST(MyClassTest, test_smeh) {
    BitArray res(10);
    res.set(5, true);
    res >>= 1;
    ASSERT_EQ(res[6], true);
}

TEST(MyClassTest, test_empty_clear) {
    BitArray res(10);
    res.clear();
    ASSERT_EQ(res.empty(), true);
}

TEST(MyClassTest, test_operator) {
    BitArray res(10);
    BitArray res2(10, 1);
    bool as = (res != res2);
    ASSERT_EQ(as, true);
}

TEST(MyClassTest, test_operator2) {
    BitArray res(10);
    BitArray res2(10);
    bool as = (res == res2);
    ASSERT_EQ(as, true);
}
TEST(MyClassTest, test_operator3) {
    BitArray res(10);
    BitArray res2(10, 1);
    bool as = (res == ~res2);
    ASSERT_EQ(as, true);
}
TEST(MyClassTest, test_reset) {
    BitArray res(10);
    BitArray res2(10, 1);
    res2.reset();
    bool as = (res == res2);
    ASSERT_EQ(as, true);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
