#include "vector.hpp"
#include "gtest/gtest.h"

TEST(VectorTest, IsEmpty)
{
    ft::vector<int> v1;
    ASSERT_TRUE(v1.empty());
}

TEST(VectorTest, EqualWithStd)
{
    ft::vector<int> v1;
    std::vector<int> v2;
    ASSERT_EQ(v1.size(), v2.size());
    ASSERT_TRUE(ft::equal(v1.begin(), v1.end(), v2.begin()));
}

//int main()
//{
//    ::testing::InitGoogleTest();
//    return RUN_ALL_TESTS();
//}
