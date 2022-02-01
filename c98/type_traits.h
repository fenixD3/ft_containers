#pragma once

namespace ft
{

template <bool, typename ReturnType = void>
struct enable_if {};

template <typename ReturnType>
struct enable_if<true, ReturnType>
{
    typedef ReturnType type;
};

}
