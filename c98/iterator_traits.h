#pragma once

namespace ft
{

template <typename TType>
struct iterator_traits
{
    typedef typename TType::difference_type difference_type;
    typedef typename TType::value_type value_type;
    typedef typename TType::pointer pointer;
    typedef typename TType::reference reference;
};

template <typename TType>
struct iterator_traits<TType*>
{
    typedef std::ptrdiff_t difference_type;
    typedef TType value_type;
    typedef TType* pointer;
    typedef TType& reference;
};

template <typename TType>
struct iterator_traits<const TType*>
{
    typedef std::ptrdiff_t difference_type;
    typedef TType value_type;
    typedef const TType* pointer;
    typedef const TType& reference;
};

}
