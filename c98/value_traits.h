#pragma once

namespace ft
{

template <typename LeftType, typename RightType>
struct is_same
{
    static const bool value = false;
};

template <typename Type>
struct is_same<Type, Type>
{
    static const bool value = true;
};

}
