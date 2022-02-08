#include "gtest/gtest.h"
#include "iterators.h"
#include "vector.hpp"

#include <string>
#include <vector>
#include <iostream>

class RandomAccessIteratorTests : public testing::Test
{
//private:
//    std::vector<std::string> v_str = {"Hello", "World", "Piter"};

protected:
    ft::vector<int> v_int;
    /*const*/ ft::vector<std::string> c_v_str;

protected:
//    RandomAccessIteratorTests()
//        : c_v_str(v_str.begin(), v_str.end())
//    {}

    void SetUp() override
    {
        v_int.push_back(1);
        v_int.push_back(2);
        v_int.push_back(3);

        c_v_str.insert(c_v_str.end(), "Hello");
        c_v_str.insert(c_v_str.end(), "World");
        c_v_str.insert(c_v_str.end(), "Piter");
    }
};

TEST_F(RandomAccessIteratorTests, AccessOperator)
{
    ASSERT_EQ(v_int[0], 1);
    ASSERT_EQ(v_int[1], 2);
    ASSERT_EQ(v_int[2], 3);
}

TEST_F(RandomAccessIteratorTests, Iteration)
{
    auto start_it = v_int.begin();

    for (auto it = v_int.begin(); it != v_int.end(); ++it)
    {
        ASSERT_EQ(*it, *(start_it + (it - start_it)));
    }
}
