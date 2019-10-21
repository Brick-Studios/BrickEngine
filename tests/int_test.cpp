#include <iostream>
#include <gtest/gtest.h>

TEST(TEST1, Subtest_1){
    ASSERT_TRUE(3==3);
}

TEST(TEST1, Subtest_2){
    ASSERT_TRUE(4==4);
}