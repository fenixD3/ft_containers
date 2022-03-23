#include "stack.h"
#include <gtest/gtest.h>

#include <vector>
#include <stack>

class StackTests : public testing::Test
{
protected:
    ft::stack<int> st;
    std::pair<int, int> dd;
    std::vector<int> vec_std = {1, 2, 3};
};

TEST_F(StackTests, Empty)
{
    ASSERT_TRUE(st.empty());

    ft::stack<int, std::vector<int>> st1(vec_std);
    ASSERT_FALSE(st1.empty());
}

TEST_F(StackTests, Size)
{
    ASSERT_EQ(st.size(), 0);

    ft::stack<int, std::vector<int>> st1(vec_std);
    ASSERT_EQ(st1.size(), vec_std.size());

    ft::vector<int> vec_ft(vec_std.begin(), vec_std.end());
    ft::stack<int, ft::vector<int>> st_ft_vec(vec_ft);
    ASSERT_EQ(st_ft_vec.size(), vec_ft.size());
}

TEST_F(StackTests, PushTop)
{
    ft::stack<int, std::vector<int>> st1(vec_std);

    auto old_size = vec_std.size();
    const int new_val = 44;
    st1.push(new_val);
    ASSERT_NE(old_size + 1, vec_std.size());
    ASSERT_EQ(old_size + 1, st1.size());
    ASSERT_EQ(st1.top(), new_val);

    ft::vector<int> vec_ft(vec_std.begin(), vec_std.end());
    ft::stack<int, ft::vector<int>> st_ft_vec(vec_ft);
    st_ft_vec.push(new_val);
    ASSERT_NE(old_size + 1, vec_ft.size());
    ASSERT_EQ(old_size + 1, st_ft_vec.size());
}

TEST_F(StackTests, Pop)
{
    ft::stack<int, std::vector<int>> st1(vec_std);

    auto old_size = vec_std.size();
    st1.pop();
    ASSERT_NE(old_size - 1, vec_std.size());
    ASSERT_EQ(old_size - 1, st1.size());

    ft::vector<int> vec_ft(vec_std.begin(), vec_std.end());
    ft::stack<int, ft::vector<int>> st_ft_vec(vec_ft);
    st_ft_vec.pop();
    ASSERT_NE(old_size - 1, vec_ft.size());
    ASSERT_EQ(old_size - 1, st_ft_vec.size());
}
