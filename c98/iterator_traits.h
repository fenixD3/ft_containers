#pragma once

namespace ft
{

struct input_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <typename TType>
struct iterator_traits
{
    typedef typename TType::iterator_category iterator_category;
    typedef typename TType::difference_type difference_type;
    typedef typename TType::value_type value_type;
    typedef typename TType::pointer pointer;
    typedef typename TType::reference reference;
};

template <typename TType>
struct iterator_traits<TType*>
{
    typedef random_access_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    typedef TType value_type;
    typedef TType* pointer;
    typedef TType& reference;
};

template <typename TType>
struct iterator_traits<const TType*>
{
    typedef random_access_iterator_tag iterator_category;
    typedef std::ptrdiff_t difference_type;
    typedef TType value_type;
    typedef const TType* pointer;
    typedef const TType& reference;
};

}
