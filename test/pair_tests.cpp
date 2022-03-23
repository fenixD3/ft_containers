#include "utility.h"
#include <gtest/gtest.h>

class PairTests : public testing::Test
{
protected:
    PairTests()
        : fst_num(1)
        , fst_str("hello")
        , ft_pair(ft::make_pair(fst_num, fst_str))
    {}

    const int fst_num;
    const std::string fst_str;
    ft::pair<int, std::string> ft_pair;
};

TEST_F(PairTests, ExtractItems)
{
    ASSERT_EQ(ft_pair.first, fst_num);
    ASSERT_EQ(ft_pair.second, fst_str);
}

TEST_F(PairTests, Comparison)
{
    ft::pair<int, std::string> clone = ft_pair;
    ASSERT_TRUE(ft_pair == clone);

    ft::pair<int, std::string> non_equal_1 = ft::make_pair(fst_num, "world");
    ft::pair<int, std::string> non_equal_2 = ft::make_pair(23, fst_str);
    ASSERT_TRUE(ft_pair != non_equal_1);
    ASSERT_TRUE(ft_pair != non_equal_2);

    ASSERT_TRUE(ft_pair < non_equal_2);
    ASSERT_TRUE(ft_pair < non_equal_1);

    ASSERT_TRUE(non_equal_2 > ft_pair);
    ASSERT_TRUE(non_equal_1 > ft_pair);

    ASSERT_TRUE(ft_pair <= clone);
    ASSERT_TRUE(ft_pair >= clone);
}

TEST_F(PairTests, Select1st)
{
    ft::Select1st<ft::pair<int, std::string>> extracter{};
    ASSERT_EQ(ft_pair.first, extracter(ft_pair));
}
