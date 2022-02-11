#pragma once

#include "iterator_traits.h"
#include "type_traits.h"
#include "value_traits.h"

namespace ft
{

template <typename TIter, typename TContainer>
class RandomAccessIterator
{
public:
    typedef std::size_t size_type;
    typedef typename iterator_traits<TIter>::difference_type difference_type;
    typedef typename iterator_traits<TIter>::pointer pointer;
    typedef typename iterator_traits<TIter>::value_type value_type;
    typedef typename iterator_traits<TIter>::reference reference;

private:
    pointer m_Iterator;

public:
    RandomAccessIterator();
    RandomAccessIterator(pointer ptr);

    template <typename TUIter>
    RandomAccessIterator(const RandomAccessIterator<
        TUIter,
        typename enable_if<is_same<typename TContainer::pointer, TUIter>::value, TContainer>::type>& other);

    RandomAccessIterator(const RandomAccessIterator& other);
    RandomAccessIterator& operator=(const RandomAccessIterator& other);

    /// TODO may be rewrite to friend functions
    bool operator==(const RandomAccessIterator& other) const;
    bool operator!=(const RandomAccessIterator& other) const;
    bool operator<(const RandomAccessIterator& other) const;
    bool operator<=(const RandomAccessIterator& other) const;
    bool operator>(const RandomAccessIterator& other) const;
    bool operator>=(const RandomAccessIterator& other) const;

    reference operator*() const;
    pointer operator->() const;

    // prefix version
    RandomAccessIterator& operator++();
    RandomAccessIterator& operator--();

    // postfix version
    RandomAccessIterator operator++(int);
    RandomAccessIterator operator--(int);

    RandomAccessIterator& operator+=(const difference_type offset);
    RandomAccessIterator& operator-=(const difference_type offset);

    template <typename TUIter, typename TUContainer>
    friend typename RandomAccessIterator<TUIter, TUContainer>::difference_type operator-(
            const RandomAccessIterator<TUIter, TUContainer>& lhs,
            const RandomAccessIterator<TUIter, TUContainer>& rhs);

    template <typename TUIter, typename TUContainer>
    friend RandomAccessIterator<TUIter, TUContainer> operator+(
            const RandomAccessIterator<TUIter, TUContainer>& lhs,
            const typename RandomAccessIterator<TUIter, TUContainer>::difference_type rhs);

    template <typename TUIter, typename TUContainer>
    friend RandomAccessIterator<TUIter, TUContainer> operator-(
            const RandomAccessIterator<TUIter, TUContainer>& lhs,
            const typename RandomAccessIterator<TUIter, TUContainer>::difference_type rhs);

    template <typename TUIter, typename TUContainer>
    friend RandomAccessIterator<TUIter, TUContainer> operator+(
            const typename RandomAccessIterator<TUIter, TUContainer>::difference_type lhs,
            const RandomAccessIterator<TUIter, TUContainer>& rhs);

    reference operator[](const size_type offset) const;
};

template <typename TIter, typename TContainer>
RandomAccessIterator<TIter, TContainer>::RandomAccessIterator()
    : m_Iterator(NULL)
{}

template <typename TIter, typename TContainer>
RandomAccessIterator<TIter, TContainer>::RandomAccessIterator(pointer ptr)
    : m_Iterator(ptr)
{}

template <typename TIter, typename TContainer>
template <typename TUIter>
RandomAccessIterator<TIter, TContainer>::RandomAccessIterator(const RandomAccessIterator<
        TUIter,
        typename enable_if<is_same<typename TContainer::pointer, TUIter>::value, TContainer>::type>& other)
    : m_Iterator(other.m_Iterator)
{}

template <typename TIter, typename TContainer>
RandomAccessIterator<TIter, TContainer>::RandomAccessIterator(const RandomAccessIterator& other)
        : m_Iterator(other.m_Iterator)
{}

template <typename TIter, typename TContainer>
RandomAccessIterator<TIter, TContainer>& RandomAccessIterator<TIter, TContainer>::operator=(const RandomAccessIterator& other)
{
    if (this == &other)
    {
        return *this;
    }
    m_Iterator = other.m_Iterator;
    return *this;
}

template <typename TIter, typename TContainer>
bool RandomAccessIterator<TIter, TContainer>::operator==(const RandomAccessIterator& other) const
{
    return m_Iterator == other.m_Iterator;
}

template <typename TIter, typename TContainer>
bool RandomAccessIterator<TIter, TContainer>::operator!=(const RandomAccessIterator& other) const
{
    return !(*this == other);
}

template <typename TIter, typename TContainer>
bool RandomAccessIterator<TIter, TContainer>::operator<(const RandomAccessIterator& other) const
{
    return m_Iterator < other.m_Iterator;
}

template <typename TIter, typename TContainer>
bool RandomAccessIterator<TIter, TContainer>::operator<=(const RandomAccessIterator& other) const
{
    return m_Iterator <= other.m_Iterator;
}

template <typename TIter, typename TContainer>
bool RandomAccessIterator<TIter, TContainer>::operator>(const RandomAccessIterator& other) const
{
    return m_Iterator > other.m_Iterator;
}

template <typename TIter, typename TContainer>
bool RandomAccessIterator<TIter, TContainer>::operator>=(const RandomAccessIterator& other) const
{
    return m_Iterator >= other.m_Iterator;
}

template <typename TIter, typename TContainer>
typename RandomAccessIterator<TIter, TContainer>::reference RandomAccessIterator<TIter, TContainer>::operator*() const
{
    return *m_Iterator;
}

template <typename TIter, typename TContainer>
typename RandomAccessIterator<TIter, TContainer>::pointer RandomAccessIterator<TIter, TContainer>::operator->() const
{
    return m_Iterator;
}

template <typename TIter, typename TContainer>
RandomAccessIterator<TIter, TContainer>& RandomAccessIterator<TIter, TContainer>::operator++()
{
    ++m_Iterator;
    return *this;
}

template <typename TIter, typename TContainer>
RandomAccessIterator<TIter, TContainer>& RandomAccessIterator<TIter, TContainer>::operator--()
{
    --m_Iterator;
    return *this;
}

template <typename TIter, typename TContainer>
RandomAccessIterator<TIter, TContainer> RandomAccessIterator<TIter, TContainer>::operator++(int)
{
    RandomAccessIterator temp(*this);
    ++(*this);
    return temp;
}

template <typename TIter, typename TContainer>
RandomAccessIterator<TIter, TContainer> RandomAccessIterator<TIter, TContainer>::operator--(int)
{
    RandomAccessIterator temp(*this);
    --(*this);
    return temp;
}

template <typename TIter, typename TContainer>
RandomAccessIterator<TIter, TContainer>& RandomAccessIterator<TIter, TContainer>::operator+=(
        const typename RandomAccessIterator::difference_type offset)
{
    m_Iterator += offset;
    return *this;
}

template <typename TIter, typename TContainer>
RandomAccessIterator<TIter, TContainer>& RandomAccessIterator<TIter, TContainer>::operator-=(
        const typename RandomAccessIterator::difference_type offset)
{
    m_Iterator -= offset;
    return *this;
}

template <typename TUIter, typename TUContainer>
typename RandomAccessIterator<TUIter, TUContainer>::difference_type operator-(
        const RandomAccessIterator<TUIter, TUContainer>& lhs, 
        const RandomAccessIterator<TUIter, TUContainer>& rhs)
{
    return lhs.m_Iterator - rhs.m_Iterator;
}

template <typename TUIter, typename TUContainer>
RandomAccessIterator<TUIter, TUContainer> operator+(
        const RandomAccessIterator<TUIter, TUContainer>& lhs, 
        const typename RandomAccessIterator<TUIter, TUContainer>::difference_type rhs)
{
    return lhs.m_Iterator + rhs;
}

template <typename TUIter, typename TUContainer>
RandomAccessIterator<TUIter, TUContainer> operator-(
        const RandomAccessIterator<TUIter, TUContainer>& lhs,
        const typename RandomAccessIterator<TUIter, TUContainer>::difference_type rhs)
{
    return lhs.m_Iterator - rhs;
}

template <typename TUIter, typename TUContainer>
RandomAccessIterator<TUIter, TUContainer> operator+(
        const typename RandomAccessIterator<TUIter, TUContainer>::difference_type lhs, 
        const RandomAccessIterator<TUIter, TUContainer>& rhs)
{
    return rhs + lhs;
}

template <typename TIter, typename TContainer>
typename RandomAccessIterator<TIter, TContainer>::reference RandomAccessIterator<TIter, TContainer>::operator[](const size_type offset) const
{
    return *(m_Iterator + offset);
}

}
