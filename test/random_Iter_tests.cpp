#include "gtest/gtest.h"
#include "iterators.h"
#include "vector.hpp"

#include <string>

class RandomAccessIteratorTests : public testing::Test
{
protected:
    ft::vector<int> v1;
    ft::vector<std::string> v2;

protected:
    void SetUp() override
    {
        v1.push_back(1);
        v1.push_back(2);
        v1.push_back(3);

        v2.insert(v2.end(), "Hello");
        v2.insert(v2.end(), "World");
        v2.insert(v2.end(), "Piter");
    }
};

TEST_F(RandomAccessIteratorTests, Iteration)
{
    auto start_it = v1.begin();

    for (auto it = v1.begin(); it != v1.end(); ++it)
    {
        ASSERT_EQ(it, it - (it - start_it));
    }
}
