#include "vector.hpp"
#include "gtest/gtest.h"

class VectorTests : public testing::Test
{
protected:
    ft::vector<int> v1;
    std::vector<int> v2;

    std::vector<int> std_vec = {1, 2, 3};
};

TEST_F(VectorTests, IsEmpty)
{
    ASSERT_TRUE(v1.empty());
}

TEST_F(VectorTests, EqualEmpty)
{
    ASSERT_EQ(v1.size(), v2.size());
    ASSERT_TRUE(ft::equal(v1.begin(), v1.end(), v2.begin()));
}

TEST_F(VectorTests, Equal)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());

    ASSERT_EQ(std_vec.size(), ft_vec.size());
    ASSERT_TRUE(ft::equal(ft_vec.begin(), ft_vec.end(), std_vec.begin()));
}

TEST_F(VectorTests, IterBegin)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());
    ft::vector<int>::iterator b_it = ft::vector<int>::iterator(&ft_vec[0]);
    ASSERT_EQ(ft_vec.begin(), b_it);
}

TEST_F(VectorTests, IterEnd)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());
    ft::vector<int>::iterator end_it = ft::vector<int>::iterator(&ft_vec[ft_vec.size()]);
    ASSERT_EQ(ft_vec.end(), end_it);
}

TEST_F(VectorTests, Size)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());
    ASSERT_EQ(ft_vec.size(), std_vec.size());
}

TEST_F(VectorTests, Capacity)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());
    ASSERT_EQ(ft_vec.capacity(), std_vec.capacity());
}

TEST_F(VectorTests, Resize)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());

    int old_size = ft_vec.size();
    int new_size = 15;
    ft_vec.resize(new_size);
    ASSERT_EQ(ft_vec.size(), new_size);

    for (auto i = 0; i < ft_vec.size(); ++i)
    {
        if (i >= old_size)
        {
            ASSERT_EQ(ft_vec[i], 0);
        }
        else
        {
            ASSERT_EQ(ft_vec[i], std_vec[i]);
        }
    }
}

TEST_F(VectorTests, ResizeLess)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());

    int new_size = 1;
    ft_vec.resize(new_size);
    ASSERT_EQ(ft_vec.size(), new_size);

    for (auto i = 0; i < ft_vec.size(); ++i)
    {
        ASSERT_EQ(ft_vec[i], std_vec[i]);
    }
}

TEST_F(VectorTests, ResizeWithDefault)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());

    int old_size = ft_vec.size();
    int new_size = 15;
    int default_val = 44;
    ft_vec.resize(new_size, default_val);
    ASSERT_EQ(ft_vec.size(), new_size);

    for (auto i = 0; i < ft_vec.size(); ++i)
    {
        if (i >= old_size)
        {
            ASSERT_EQ(ft_vec[i], default_val);
        }
        else
        {
            ASSERT_EQ(ft_vec[i], std_vec[i]);
        }
    }
}

TEST_F(VectorTests, Reserve)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());

    int new_capacity = 15;
    ft_vec.reserve(new_capacity);
    ASSERT_EQ(ft_vec.capacity(), new_capacity);

    for (auto i = 0; i < ft_vec.size(); ++i)
    {
        ASSERT_EQ(ft_vec[i], std_vec[i]);
    }
}

TEST_F(VectorTests, At)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());

    size_t position = 1;
    ASSERT_EQ(ft_vec.at(position), *(ft_vec.begin() + 1));
}

TEST_F(VectorTests, AtException)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());

    size_t wrong_position = 300;
    ASSERT_THROW(ft_vec.at(wrong_position), std::out_of_range);
}

TEST_F(VectorTests, Front)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());
    ASSERT_EQ(ft_vec.front(), *ft_vec.begin());
}

TEST_F(VectorTests, Back)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());
    ASSERT_EQ(ft_vec.back(), *(ft_vec.end() - 1));
}

TEST_F(VectorTests, Assign)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());
    int new_size = 10;
    int new_value = 100;
    ft_vec.assign(new_size, new_value);

    for (int item : ft_vec)
    {
        ASSERT_EQ(item, new_value);
    }
}

TEST_F(VectorTests, AssignIterators)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());
    std::vector<int> assignible_vec_std = {10, 10, 23, 43, 54, 78, 98};
    ft::vector<int> assignible_vec_ft(assignible_vec_std.begin(), assignible_vec_std.end());
    ft_vec.assign(assignible_vec_ft.begin(), assignible_vec_ft.end());

    ASSERT_EQ(ft_vec.size(), assignible_vec_std.size());

    for (auto i = 0; i < ft_vec.size(); ++i)
    {
        ASSERT_EQ(ft_vec[i], assignible_vec_std[i]);
    }
}

TEST_F(VectorTests, PushBack)
{
    const int num1 = 3;
    v1.push_back(num1);
    ASSERT_EQ(*v1.begin(), num1);
    ASSERT_EQ(v1.size(), 1);

    const int num2 = 45;
    v1.push_back(num2);
    ASSERT_EQ(*v1.begin(), num1);
    ASSERT_EQ(*(v1.end() - 1), num2);
    ASSERT_EQ(v1.size(), 2);
}

TEST_F(VectorTests, PopBack)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());
    int last_elem = ft_vec.back();
    int new_last_elem = ft_vec[ft_vec.size() - 2];
    size_t new_size = ft_vec.size() - 1;
    ft_vec.pop_back();

    ASSERT_EQ(ft_vec.size(), new_size);
    ASSERT_NE(ft_vec.back(), last_elem);
    ASSERT_EQ(ft_vec.back(), new_last_elem);
}

TEST_F(VectorTests, InsertPosition)
{
    const int value1 = 42;
    ft::vector<int>::iterator inserted1 = v1.insert(v1.begin(), value1);
    ASSERT_EQ(inserted1, v1.begin());
    ASSERT_EQ(*inserted1, value1);
    ASSERT_EQ(*v1.begin(), value1);

    const int value2 = 22;
    ft::vector<int>::iterator inserted2 = v1.insert(v1.end(), value2);
    ASSERT_NE(inserted2, v1.end());
    ASSERT_EQ(inserted2, v1.end() - 1);
    ASSERT_EQ(*inserted2, value2);
    ASSERT_EQ(v1.back(), value2);

    const int value3 = 3;
    ft::vector<int>::iterator inserted3 = v1.insert(v1.begin() + 1, value3);
    ASSERT_EQ(*inserted3, value3);

    std::vector<int> ideal_vec = {value1, value3, value2};
    ASSERT_EQ(v1.size(), ideal_vec.size());
    for (auto i = 0; i < v1.size(); ++i)
    {
        ASSERT_EQ(v1[i], ideal_vec[i]);
    }
}

TEST_F(VectorTests, InsertPositionNth)
{
    const int value1 = 42;
    int inserted_cnt = 1;
    v1.insert(v1.begin(), inserted_cnt, value1);
    ASSERT_EQ(*v1.begin(), value1);

    const int value2 = 22;
    inserted_cnt = 2;
    v1.insert(v1.end(), inserted_cnt, value2);
    for (auto it = v1.begin() + 1; it != v1.end(); ++it)
    {
        ASSERT_EQ(*it, value2);
    }

    const int value3 = 3;
    v1.insert(v1.begin() + 1, inserted_cnt, value3);

    std::vector<int> ideal_vec = {value1, value3, value3, value2, value2};
    ASSERT_EQ(v1.size(), ideal_vec.size());
    for (auto i = 0; i < v1.size(); ++i)
    {
        ASSERT_EQ(v1[i], ideal_vec[i]);
    }
}

TEST_F(VectorTests, InsertRange)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());
    v1.insert(v1.begin(), ft_vec.begin(), ft_vec.end());
    ASSERT_EQ(v1, ft_vec);

    const int new_val = 45;
    v1.push_back(new_val);
    ft_vec.push_back(new_val);
    v1.insert(v1.begin() + 2, ft_vec.begin(), ft_vec.end() - 1);

    std::vector<int> expected_vec = std_vec;
    expected_vec.push_back(new_val);
    std::vector<int> inserted_vec;
    std::transform(ft_vec.begin(), ft_vec.end() - 1, std::back_inserter(inserted_vec), [](int item) { return item; });
    expected_vec.insert(expected_vec.begin() + 2, inserted_vec.begin(), inserted_vec.end());

    for (auto i = 0; i < ft_vec.size(); ++i)
    {
        ASSERT_EQ(v1[i], expected_vec[i]);
    }
}

TEST_F(VectorTests, Erase)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());
    auto erased_pos = ft_vec.begin() + 1;
    auto it = ft_vec.erase(erased_pos);
    auto it_std = std_vec.erase(std_vec.begin() + 1);
    ASSERT_EQ(*it, *it_std);
    ASSERT_EQ(it, ft_vec.begin() + 1);

    for (auto i = 0; i < ft_vec.size(); ++i)
    {
        ASSERT_EQ(ft_vec[i], std_vec[i]);
    }

    erased_pos = ft_vec.end() - 1;
    it = ft_vec.erase(erased_pos);
    ASSERT_EQ(it, ft_vec.end());

    std_vec.erase(std_vec.end() - 1);
    for (auto i = 0; i < ft_vec.size(); ++i)
    {
        ASSERT_EQ(ft_vec[i], std_vec[i]);
    }
}

TEST_F(VectorTests, EraseRange)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());
    const int new_value = 45;
    ft_vec.push_back(new_value);
    std_vec.push_back(new_value);

    auto erased_pos_first = ft_vec.begin() + 1;
    auto erased_pos_last = ft_vec.begin() + 2;
    auto erased_elems = erased_pos_last - erased_pos_first;
    auto it = ft_vec.erase(erased_pos_first, erased_pos_last);
    auto it_std = std_vec.erase(std_vec.begin() + 1, std_vec.begin() + 2);
    ASSERT_EQ(*it, *it_std);
    ASSERT_EQ(it, ft_vec.begin() + erased_elems);

    for (auto i = 0; i < ft_vec.size(); ++i)
    {
        ASSERT_EQ(ft_vec[i], std_vec[i]);
    }

    erased_pos_first = ft_vec.end() - 1;
    erased_pos_last = ft_vec.end();
    it = ft_vec.erase(erased_pos_first, erased_pos_last);
    it_std = std_vec.erase(std_vec.end() - 1, std_vec.end());
    ASSERT_EQ(*it, *it_std);
    ASSERT_EQ(it, ft_vec.end());

    for (auto i = 0; i < ft_vec.size(); ++i)
    {
        ASSERT_EQ(ft_vec[i], std_vec[i]);
    }
}

TEST_F(VectorTests, EraseRangeNth)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());
    const int new_value = 45;
    ft_vec.push_back(new_value);
    std_vec.push_back(new_value);

    auto erased_pos_first = ft_vec.begin() + 1;
    auto erased_pos_last = ft_vec.end();
    auto erased_first_idx = erased_pos_first - ft_vec.begin();
    auto it = ft_vec.erase(erased_pos_first, erased_pos_last);
    auto it_std = std_vec.erase(std_vec.begin() + 1, std_vec.end());
    ASSERT_EQ(it, ft_vec.end());
    ASSERT_EQ(*it, *it_std);
    ASSERT_EQ(it, ft_vec.begin() + erased_first_idx);

    for (auto i = 0; i < ft_vec.size(); ++i)
    {
        ASSERT_EQ(ft_vec[i], std_vec[i]);
    }
}

TEST_F(VectorTests, Clear)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());
    ft_vec.clear();

    ASSERT_EQ(ft_vec.size(), 0);
}

TEST_F(VectorTests, SwapMethod)
{
    ft::vector<int> ft_vec(std_vec.begin(), std_vec.end());

    std::vector<int> swapped_vec = {11, 12, 13, 14};
    ft::vector<int> ft_new_vec(swapped_vec.begin(), swapped_vec.end());

    ft_vec.swap(ft_new_vec);

    ASSERT_EQ(ft_vec.size(), swapped_vec.size());
    ASSERT_EQ(ft_vec.capacity(), swapped_vec.capacity());
    for (auto i = 0; i < ft_vec.size(); ++i)
    {
        ASSERT_EQ(ft_vec[i], swapped_vec[i]);
    }

    ASSERT_EQ(ft_new_vec.size(), std_vec.size());
    ASSERT_EQ(ft_new_vec.capacity(), std_vec.capacity());
    for (auto i = 0; i < ft_new_vec.size(); ++i)
    {
        ASSERT_EQ(ft_new_vec[i], std_vec[i]);
    }
}
