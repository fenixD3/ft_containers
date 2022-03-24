#include "set.h"
#include <gtest/gtest.h>
#include <set>

class SetTests : public testing::Test
{
protected:
    using ft_set_type = ft::set<int>;
    using std_set_type = std::set<int>;

protected:
    SetTests()
    {
        ft_set.insert(num_2);
        ft_set.insert(num_1);
    }

    const int num_1 = 1, num_2 = 23;

    ft_set_type empty_set;
    ft_set_type ft_set;
    std_set_type std_set = { num_2, num_1 };

    void check_ft_std_sets(const std_set_type& expected_set)
    {
        auto std_it = expected_set.begin();
        for (const auto& val : ft_set)
        {
            ASSERT_EQ(val, *std_it);
            ++std_it;
        }
    }
};

TEST_F(SetTests, EmptyAndSize)
{
    ASSERT_TRUE(empty_set.empty());
    ASSERT_EQ(empty_set.size(), 0);

    ASSERT_FALSE(ft_set.empty());
    ASSERT_EQ(ft_set.size(), 2);
}

TEST_F(SetTests, IteratorsWithOperations)
{
    ft_set_type::iterator it_begin = ft_set.begin();
    ft_set_type::const_iterator c_it = ft_set.begin();
    ASSERT_TRUE(it_begin == c_it);
    ASSERT_TRUE(c_it == it_begin);

    auto exp_begin = num_1;
    ASSERT_EQ(*it_begin, exp_begin);

    auto it_end = ft_set.end();
    auto exp_end = num_2;
    ASSERT_EQ(*(--it_end), exp_end);
    ASSERT_EQ(*it_end, *ft_set.rbegin());

    const int new_num = 2;
    ft_set.insert(new_num);
    auto exp_middle = new_num;
    ASSERT_EQ(*(--it_end), exp_middle);

    ASSERT_EQ(*it_begin, exp_begin);
    ASSERT_EQ(*(it_begin++), exp_begin);
    ASSERT_EQ(*it_begin, exp_middle);
    ASSERT_EQ(*(++it_begin), exp_end);
    ASSERT_EQ(++it_begin, ft_set.end());
}

TEST_F(SetTests, Find)
{
    auto found = ft_set.find(num_2);
    ASSERT_EQ(*found, num_2);
}

TEST_F(SetTests, FindNotExist)
{
    const int not_exist = 666;
    auto found = ft_set.find(not_exist);
    ASSERT_EQ(found, ft_set.end());
}

TEST_F(SetTests, InsertOnlyVal)
{
    const int new_num = 2;

    ft_set_type::size_type old_size = ft_set.size();
    const auto& [new_it, exp_true] = ft_set.insert(new_num);
    ASSERT_EQ(*new_it, new_num);
    ASSERT_TRUE(exp_true);
    ASSERT_EQ(++old_size, ft_set.size());

    std_set.insert(new_num);
    check_ft_std_sets(std_set);

    const auto& [old_it, exp_false] = ft_set.insert(num_2);
    ASSERT_EQ(*old_it, num_2);
    ASSERT_FALSE(exp_false);
    check_ft_std_sets(std_set);
    ASSERT_EQ(old_size, ft_set.size());
}

TEST_F(SetTests, InsertHint)
{
    const int new_num = 2;

    ft_set_type::size_type old_size = ft_set.size();
    auto inserted_it = ft_set.insert(ft_set.begin(), new_num);
    ASSERT_EQ(*inserted_it, new_num);
    ASSERT_EQ(++old_size, ft_set.size());

    std_set.insert(std_set.begin(), new_num);
    check_ft_std_sets(std_set);

    inserted_it = ft_set.insert((++ft_set.begin()), num_2);
    ASSERT_EQ(*inserted_it, num_2);
    ASSERT_EQ(old_size, ft_set.size());

    const int new_num_2 = 44;

    inserted_it = ft_set.insert((++ft_set.begin()), new_num_2);
    ASSERT_EQ(*inserted_it, new_num_2);
    ASSERT_EQ(++old_size, ft_set.size());

    std_set.insert(std_set.begin(), new_num_2);
    check_ft_std_sets(std_set);
}

TEST_F(SetTests, InsertRange)
{
    empty_set.insert(33);
    empty_set.insert(44);
    empty_set.insert(66);
    empty_set.insert(num_2);

    ft_set_type::size_type old_size = ft_set.size();
    ft_set.insert(empty_set.begin(), empty_set.end());
    ASSERT_EQ(old_size + 3, ft_set.size());

    std_set_type new_std_set = { 33, 44, 66, num_2 };
    std_set.insert(new_std_set.begin(), new_std_set.end());
    check_ft_std_sets(std_set);
}

TEST_F(SetTests, EraseVal)
{
    auto old_size = ft_set.size();
    auto erased_cnt = ft_set.erase(num_2);
    ASSERT_EQ(--old_size, ft_set.size());
    ASSERT_EQ(erased_cnt, 1);

    std_set.erase(num_2);
    check_ft_std_sets(std_set);

    erased_cnt = ft_set.erase(666);
    ASSERT_EQ(old_size, ft_set.size());
    ASSERT_EQ(erased_cnt, 0);
}

TEST_F(SetTests, ErasePosition)
{
    const int new_num = 2;
    ft_set.insert(new_num);

    auto old_size = ft_set.size();
    ft_set.erase(++ft_set.begin());

    ASSERT_EQ(--old_size, ft_set.size());

    std_set.insert(new_num);
    std_set.erase(++std_set.begin());
    check_ft_std_sets(std_set);
}

TEST_F(SetTests, EraseRange)
{
    empty_set.insert(33);
    empty_set.insert(44);
    empty_set.insert(66);
    empty_set.insert(num_2);

    ft_set.insert(empty_set.begin(), empty_set.end());
    ft_set_type::size_type old_size = ft_set.size();

    ft_set.erase(++ft_set.begin(), --(--ft_set.end()));
    ASSERT_EQ(old_size -= 2, ft_set.size());

    std_set_type new_std_set = { 33, 44, 66, num_2 };
    std_set.insert(new_std_set.begin(), new_std_set.end());
    std_set.erase(++std_set.begin(), --(--std_set.end()));
    check_ft_std_sets(std_set);
}

TEST_F(SetTests, Swap)
{
    empty_set.insert(33);
    empty_set.insert(44);
    empty_set.insert(66);
    empty_set.insert(num_2);

    ft_set_type old_fst = ft_set;
    ft_set_type old_sec = empty_set;
    ft_set.swap(empty_set);

    ASSERT_EQ(ft_set, old_sec);
    ASSERT_EQ(empty_set, old_fst);
}

TEST_F(SetTests, Clear)
{
    ft_set.clear();
    ASSERT_EQ(ft_set.size(), 0);
    ASSERT_EQ(ft_set.begin(), ft_set.end());
}

TEST_F(SetTests, Count)
{
    ASSERT_EQ(ft_set.count(num_2), 1);
    ASSERT_EQ(ft_set.count(555), 0);
}

TEST_F(SetTests, LowerBound)
{
    empty_set.insert(33);
    empty_set.insert(44);
    empty_set.insert(66);

    ft_set.insert(empty_set.begin(), empty_set.end());
    auto lower_bound_it = ft_set.lower_bound(22);

    ASSERT_EQ(*lower_bound_it, num_2);

    lower_bound_it = ft_set.lower_bound(num_1);
    ASSERT_EQ(*lower_bound_it, num_1);

    lower_bound_it = ft_set.lower_bound(666);
    ASSERT_EQ(lower_bound_it, ft_set.end());
}

TEST_F(SetTests, UpperBound)
{
    empty_set.insert(33);
    empty_set.insert(44);
    empty_set.insert(66);
    empty_set.insert(num_2);

    ft_set.insert(empty_set.begin(), empty_set.end());
    auto lower_bound_it = ft_set.upper_bound(22);

    ASSERT_EQ(*lower_bound_it, num_2);

    lower_bound_it = ft_set.upper_bound(num_1);
    ASSERT_EQ(*lower_bound_it, num_2);

    lower_bound_it = ft_set.lower_bound(666);
    ASSERT_EQ(lower_bound_it, ft_set.end());
}

TEST_F(SetTests, EqualRange)
{
    empty_set.insert(33);
    empty_set.insert(44);
    empty_set.insert(66);

    ft_set.insert(empty_set.begin(), empty_set.end());
    const auto& [left_1, right_1] = ft_set.equal_range(22);
    ASSERT_EQ(*left_1, num_2);
    ASSERT_EQ(*right_1, num_2);
    ASSERT_EQ(left_1, right_1);

    const auto& [left_2, right_2] = ft_set.equal_range(-1);
    ASSERT_EQ(left_2, ft_set.begin());
    ASSERT_EQ(right_2, ft_set.begin());

    const auto& [left_3, right_3] = ft_set.equal_range(666);
    ASSERT_EQ(left_3, ft_set.end());
    ASSERT_EQ(right_3, ft_set.end());

    const auto& [left_4, right_4] = ft_set.equal_range(33);
    ASSERT_EQ(*left_4, 33);
    ASSERT_EQ(*right_4, 44);
}
