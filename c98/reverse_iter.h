#pragma once

#include "iterator_traits.h"

namespace ft
{

template <typename TIter>
class ReverseIterator
{
public:
    typedef TIter iterator_type;
    typedef typename iterator_traits<TIter>::difference_type difference_type;
    typedef typename iterator_traits<TIter>::pointer pointer;
    typedef typename iterator_traits<TIter>::value_type value_type;
    typedef typename iterator_traits<TIter>::reference reference;

private:
    iterator_type m_Iterator;

public:
    ReverseIterator()
        : m_Iterator()
    {}

    explicit ReverseIterator(iterator_type iter)
        : m_Iterator(iter)
    {}

    ReverseIterator(const ReverseIterator& iter)
        : m_Iterator(iter.base())
    {}

    template <typename TUIter>
    ReverseIterator(const ReverseIterator<TUIter>& iter)
        : m_Iterator(iter.base())
    {}

    iterator_type base() const
    {
        return m_Iterator;
    }

    reference operator*() const
    {
        iterator_type tmp = m_Iterator;
        return *(--tmp);
    }

    pointer operator->() const
    {
        iterator_type tmp = m_Iterator;
        return (--tmp).operator->();
    }

    ReverseIterator& operator++()
    {
        --m_Iterator;
        return *this;
    }

    ReverseIterator operator++(int)
    {
        ReverseIterator tmp = *this;
        ++(*this);
        return tmp;
    }

    ReverseIterator& operator--()
    {
        ++m_Iterator;
        return *this;
    }

    ReverseIterator operator--(int)
    {
        ReverseIterator tmp = *this;
        --(*this);
        return tmp;
    }

    ReverseIterator& operator+=(const difference_type offset)
    {
        m_Iterator -= offset;
        return *this;
    }

    ReverseIterator& operator-=(const difference_type offset)
    {
        m_Iterator += offset;
        return *this;
    }

    friend ReverseIterator<TIter> operator+(const ReverseIterator<TIter>& lhs, const difference_type rhs)
    {
        return ReverseIterator(lhs.base() - rhs);
    }

    friend ReverseIterator<TIter> operator+(const difference_type lhs, const ReverseIterator<TIter>& rhs)
    {
        return rhs + lhs;
    }

    friend ReverseIterator<TIter> operator-(const ReverseIterator<TIter>& lhs, const difference_type rhs)
    {
        return ReverseIterator(lhs.base() + rhs);
    }

    friend typename ReverseIterator<TIter>::difference_type operator-(const ReverseIterator<TIter>& lhs, const ReverseIterator<TIter>& rhs)
    {
        return rhs.base() - lhs.base();
    }

    reference operator[](difference_type offset) const
    {
        return *(*this + offset);
    }
};

template <typename TIter>
bool operator==(const ReverseIterator<TIter>& lhs, const ReverseIterator<TIter>& rhs)
{
    return lhs.base() == rhs.base();
}

template <typename TIter>
bool operator!=(const ReverseIterator<TIter>& lhs, const ReverseIterator<TIter>& rhs)
{
    return !(lhs == rhs);
}

template <typename TIter>
bool operator<(const ReverseIterator<TIter>& lhs, const ReverseIterator<TIter>& rhs)
{
    return lhs.base() > rhs.base();
}

template <typename TIter>
bool operator<=(const ReverseIterator<TIter>& lhs, const ReverseIterator<TIter>& rhs)
{
    return lhs.base() >= rhs.base();
}

template <typename TIter>
bool operator>(const ReverseIterator<TIter>& lhs, const ReverseIterator<TIter>& rhs)
{
    return lhs.base() < rhs.base();
}

template <typename TIter>
bool operator>=(const ReverseIterator<TIter>& lhs, const ReverseIterator<TIter>& rhs)
{
    return lhs.base() <= rhs.base();
}

}
