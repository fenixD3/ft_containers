#pragma once

#include "type_traits.h"

namespace ft
{

template <typename T>
struct less
{
    bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs < rhs;
    }
};

template <>
struct less<void>
{
    template <typename T, typename U, typename Ret = decltype(declval<T>() < declval<U>())>
    Ret operator()(const T& lhs, const U& rhs) const
    {
        return lhs < rhs;
    }
};

template <typename T>
struct equal_to
{
    bool operator()(const T& lhs, const T& rhs) const
    {
        return lhs == rhs;
    }
};

template <>
struct equal_to<void>
{
    template <typename T, typename U, typename Ret = decltype(declval<T>() == declval<U>())>
    Ret operator()(const T& lhs, const U& rhs) const
    {
        return lhs == rhs;
    }
};

}
