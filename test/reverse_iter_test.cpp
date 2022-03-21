#include <gtest/gtest.h>
#include "reverse_iter.h"
#include "vector.h"

#include <string>
#include <vector>
#include <iostream>

class ReverseIteratorTests : public testing::Test
{
protected:
    ft::vector<int> v_int;
    ft::vector<int>::reverse_iterator reverse_start_v_int;

    int first_i = 1, second_i = 2, third_i = 3;
    std::string first_s = "Hello", second_s = "World", third_s = "Piter";

    const std::vector<std::string> vec_str = {first_s, second_s, third_s};

protected:
    void SetUp() override
    {
        v_int.push_back(first_i);
        v_int.push_back(second_i);
        v_int.push_back(third_i);

        reverse_start_v_int = v_int.rbegin();
    }
};

TEST_F(ReverseIteratorTests, ConstIter)
{
    auto ves_str_it = vec_str.begin();
    const ft::vector<std::string> c_v_str(vec_str.begin(), vec_str.end());
    auto c_it = c_v_str.begin();

//    std::cout << *ves_str_it;
//    std::cout << *c_it;
//    *ves_str_it = "ggg";
//    *c_it = "ggg";
}

TEST_F(ReverseIteratorTests, ArrowOperator)
{
    ft::vector<std::string> new_str(vec_str.begin(), vec_str.end());
    auto new_it = new_str.begin();
    ASSERT_EQ(new_it->front(), vec_str.begin()->front());
}

TEST_F(ReverseIteratorTests, AccessOperator)
{
    for (auto i = 0; i < v_int.size(); ++i)
    {
        ASSERT_EQ(reverse_start_v_int[i], v_int[v_int.size() - i - 1]);
    }
}

TEST_F(ReverseIteratorTests, IterationStraight)
{
    for (auto it = v_int.rbegin(); it != v_int.rend(); ++it)
    {
        ASSERT_EQ(*it, *(reverse_start_v_int + (it - reverse_start_v_int)));
    }
}

TEST_F(ReverseIteratorTests, IterationBack)
{
    for (auto it = v_int.rend() - 1; it >= v_int.rbegin(); --it)
    {
        ASSERT_EQ(it, (reverse_start_v_int + (it - reverse_start_v_int)));
    }
}
