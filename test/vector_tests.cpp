#include "vector.hpp"
#include "gtest/gtest.h"

TEST(VectorTest, IsEmpty)
{
    ft::vector<int> v1;
    ASSERT_TRUE(v1.empty());
}

TEST(VectorTest, EqualEmpty)
{
    ft::vector<int> v1;
    std::vector<int> v2;
    ASSERT_EQ(v1.size(), v2.size());
    ASSERT_TRUE(ft::equal(v1.begin(), v1.end(), v2.begin()));
}

TEST(VectorTest, ConstEqualEmpty)
{
    const ft::vector<int> v1;
    const std::vector<int> v2;
    ASSERT_EQ(v1.size(), v2.size());
    ASSERT_TRUE(ft::equal(v1.begin(), v1.end(), v2.begin()));
}

TEST(VectorTest, Equal)
{
    std::vector<int> std_vec = { 1, 2, 3};
    std::vector<int>::iterator s_it1 = std_vec.begin();
    std::vector<int>::iterator s_it2 = s_it1 + 1;
    std::vector<int>::iterator s_it3 = 1 + s_it1;

    std::cout << std_vec.end() - std_vec.begin() << std::endl;
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());
    ft::vector<int>::iterator it1 = ft_vec.begin();
    ft::vector<int>::iterator it2 = 1 + it1;

    ASSERT_EQ(std_vec.size(), ft_vec.size());
    ASSERT_TRUE(ft::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()));
}
