#include "map.h"
#include <gtest/gtest.h>
#include <map>

#include "vector.h"

class MapTests : public testing::Test
{
protected:
    using ft_map_type = ft::map<int, std::string>;
    using std_map_type = std::map<int, std::string>;

protected:
    MapTests()
    {
        ft_map[num_2] = str_2;
        ft_map[num_1] = str_1;
    }

    const int num_1 = 1, num_2 = 23;
    const std::string str_1 = "hello", str_2 = "world";

    ft_map_type empty_map;
    ft_map_type ft_map;
    std_map_type std_map = { {num_2, str_2}, {num_1, str_1} };

    void check_ft_std_maps(const std_map_type& expected_map)
    {
        auto std_it = expected_map.begin();
        for (const auto& [fst, sec] : ft_map)
        {
            ASSERT_EQ(fst, std_it->first);
            ASSERT_EQ(sec, std_it->second);
            ++std_it;
        }
    }

    ft_map_type::value_type create_pair(const int num, const std::string& str)
    {
        return ft::make_pair(num, str);
    }
};

TEST_F(MapTests, EmptyAndSize)
{
    ASSERT_TRUE(empty_map.empty());
    ASSERT_EQ(empty_map.size(), 0);

    ASSERT_FALSE(ft_map.empty());
    ASSERT_EQ(ft_map.size(), 2);
}

TEST_F(MapTests, AccessOperatorAndAssignment)
{
    ASSERT_EQ(ft_map[num_1], str_1);
    empty_map = ft_map;
    ASSERT_EQ(empty_map[num_1], str_1);
    ASSERT_EQ(empty_map[num_2], str_2);
}

TEST_F(MapTests, IteratorsWithOperations)
{
    ft_map_type::iterator it_begin = ft_map.begin();
    ft_map_type::const_iterator c_it = ft_map.begin();
    ASSERT_TRUE(it_begin == c_it);
    ASSERT_TRUE(c_it == it_begin);

    auto exp_begin = create_pair(num_1, str_1);
    ASSERT_EQ(*it_begin, exp_begin);

    auto it_end = ft_map.end();
    auto exp_end = create_pair(num_2, str_2);
    ASSERT_EQ(*(--it_end), exp_end);
    ASSERT_EQ(*it_end, *ft_map.rbegin());

    const int new_num = 2;
    const std::string new_str = "hey";
    ft_map[new_num] = new_str;
    auto exp_middle = create_pair(new_num, new_str);
    ASSERT_EQ(*(--it_end), exp_middle);

    ASSERT_EQ(*it_begin, exp_begin);
    ASSERT_EQ(*(it_begin++), exp_begin);
    ASSERT_EQ(*it_begin, exp_middle);
    ASSERT_EQ(*(++it_begin), exp_end);
    ASSERT_EQ(++it_begin, ft_map.end());
}

TEST_F(MapTests, Find)
{
    auto found = ft_map.find(num_2);
    ASSERT_EQ(*found, create_pair(num_2, str_2));
}

TEST_F(MapTests, FindNotExist)
{
    const int not_exist = 666;
    auto found = ft_map.find(not_exist);
    ASSERT_EQ(found, ft_map.end());
}

TEST_F(MapTests, InsertOnlyVal)
{
    const int new_num = 2;
    const std::string new_str = "hey";

    ft_map_type::size_type old_size = ft_map.size();
    const auto& [new_it, exp_true] = ft_map.insert({new_num, new_str});
    ASSERT_EQ(*new_it, create_pair(new_num, new_str));
    ASSERT_TRUE(exp_true);
    ASSERT_EQ(++old_size, ft_map.size());

    std_map.insert({new_num, new_str});
    check_ft_std_maps(std_map);

    const auto& [old_it, exp_false] = ft_map.insert({num_2, str_2});
    ASSERT_EQ(*old_it, create_pair(num_2, str_2));
    ASSERT_FALSE(exp_false);
    check_ft_std_maps(std_map);
    ASSERT_EQ(old_size, ft_map.size());
}

TEST_F(MapTests, InsertHint)
{
    const int new_num = 2;
    const std::string new_str = "hey";

    ft_map_type::size_type old_size = ft_map.size();
    auto inserted_it = ft_map.insert(ft_map.begin(), {new_num, new_str});
    ASSERT_EQ(*inserted_it, create_pair(new_num, new_str));
    ASSERT_EQ(++old_size, ft_map.size());

    std_map.insert(std_map.begin(), {new_num, new_str});
    check_ft_std_maps(std_map);

    inserted_it = ft_map.insert((++ft_map.begin()), {num_2, str_2});
    ASSERT_EQ(*inserted_it, create_pair(num_2, str_2));
    ASSERT_EQ(old_size, ft_map.size());

    const int new_num_2 = 44;
    const std::string new_str_2 = "lala";

    inserted_it = ft_map.insert((++ft_map.begin()), {new_num_2, new_str_2});
    ASSERT_EQ(*inserted_it, create_pair(new_num_2, new_str_2));
    ASSERT_EQ(++old_size, ft_map.size());

    std_map.insert(std_map.begin(), {new_num_2, new_str_2});
    check_ft_std_maps(std_map);
}

TEST_F(MapTests, InsertRange)
{
    empty_map[33] = "range_1";
    empty_map[44] = "range_2";
    empty_map[66] = "range_3";
    empty_map[num_2] = str_2;

    ft_map_type::size_type old_size = ft_map.size();
    ft_map.insert(empty_map.begin(), empty_map.end());
    ASSERT_EQ(old_size + 3, ft_map.size());

    std_map_type new_std_map = { {33, "range_1"}, {44, "range_2"}, {66, "range_3"}, {num_2, str_2} };
    std_map.insert(new_std_map.begin(), new_std_map.end());
    check_ft_std_maps(std_map);
}

TEST_F(MapTests, EraseKey)
{
    auto old_size = ft_map.size();
    auto erased_cnt = ft_map.erase(num_2);
    ASSERT_EQ(--old_size, ft_map.size());
    ASSERT_EQ(erased_cnt, 1);

    std_map.erase(num_2);
    check_ft_std_maps(std_map);

    erased_cnt = ft_map.erase(666);
    ASSERT_EQ(old_size, ft_map.size());
    ASSERT_EQ(erased_cnt, 0);
}

TEST_F(MapTests, ErasePosition)
{
    const int new_num = 2;
    const std::string new_str = "hey";
    ft_map[new_num] = new_str;

    auto old_size = ft_map.size();
    ft_map.erase(++ft_map.begin());

    ASSERT_EQ(--old_size, ft_map.size());

    std_map[new_num] = new_str;
    std_map.erase(++std_map.begin());
    check_ft_std_maps(std_map);
}

TEST_F(MapTests, EraseRange)
{
    empty_map[33] = "range_1";
    empty_map[44] = "range_2";
    empty_map[66] = "range_3";
    empty_map[num_2] = str_2;

    ft_map.insert(empty_map.begin(), empty_map.end());
    ft_map_type::size_type old_size = ft_map.size();

    ft_map.erase(++ft_map.begin(), --(--ft_map.end()));
    ASSERT_EQ(old_size -= 2, ft_map.size());

    std_map_type new_std_map = { {33, "range_1"}, {44, "range_2"}, {66, "range_3"}, {num_2, str_2} };
    std_map.insert(new_std_map.begin(), new_std_map.end());
    std_map.erase(++std_map.begin(), --(--std_map.end()));
    check_ft_std_maps(std_map);
}

TEST_F(MapTests, Swap)
{
    empty_map[33] = "range_1";
    empty_map[44] = "range_2";
    empty_map[66] = "range_3";
    empty_map[num_2] = str_2;

    ft_map_type old_fst = ft_map;
    ft_map_type old_sec = empty_map;
    ft_map.swap(empty_map);

    ASSERT_EQ(ft_map, old_sec);
    ASSERT_EQ(empty_map, old_fst);
}

TEST_F(MapTests, Clear)
{
    ft_map.clear();
    ASSERT_EQ(ft_map.size(), 0);
    ASSERT_EQ(ft_map.begin(), ft_map.end());
}

TEST_F(MapTests, Count)
{
    ASSERT_EQ(ft_map.count(num_2), 1);
    ASSERT_EQ(ft_map.count(555), 0);
}

TEST_F(MapTests, LowerBound)
{
    empty_map[33] = "range_1";
    empty_map[44] = "range_2";
    empty_map[66] = "range_3";

    ft_map.insert(empty_map.begin(), empty_map.end());
    auto lower_bound_it = ft_map.lower_bound(22);

    ASSERT_EQ(*lower_bound_it, create_pair(num_2, str_2));

    lower_bound_it = ft_map.lower_bound(num_1);
    ASSERT_EQ(*lower_bound_it, create_pair(num_1, str_1));

    lower_bound_it = ft_map.lower_bound(666);
    ASSERT_EQ(lower_bound_it, ft_map.end());
}

TEST_F(MapTests, UpperBound)
{
    empty_map[33] = "range_1";
    empty_map[44] = "range_2";
    empty_map[66] = "range_3";
    empty_map[num_2] = str_2;

    ft_map.insert(empty_map.begin(), empty_map.end());
    auto lower_bound_it = ft_map.upper_bound(22);

    ASSERT_EQ(*lower_bound_it, create_pair(num_2, str_2));

    lower_bound_it = ft_map.upper_bound(num_1);
    ASSERT_EQ(*lower_bound_it, create_pair(num_2, str_2));

    lower_bound_it = ft_map.lower_bound(666);
    ASSERT_EQ(lower_bound_it, ft_map.end());
}

TEST_F(MapTests, EqualRange)
{
    empty_map[33] = "range_1";
    empty_map[44] = "range_2";
    empty_map[66] = "range_3";

    ft_map.insert(empty_map.begin(), empty_map.end());
    const auto& [left_1, right_1] = ft_map.equal_range(22);
    ASSERT_EQ(*left_1, create_pair(num_2, str_2));
    ASSERT_EQ(*right_1, create_pair(num_2, str_2));
    ASSERT_EQ(left_1, right_1);

    const auto& [left_2, right_2] = ft_map.equal_range(-1);
    ASSERT_EQ(left_2, ft_map.begin());
    ASSERT_EQ(right_2, ft_map.begin());

    const auto& [left_3, right_3] = ft_map.equal_range(666);
    ASSERT_EQ(left_3, ft_map.end());
    ASSERT_EQ(right_3, ft_map.end());

    const auto& [left_4, right_4] = ft_map.equal_range(33);
    ASSERT_EQ(*left_4, create_pair(33, "range_1"));
    ASSERT_EQ(*right_4, create_pair(44, "range_2"));
}
