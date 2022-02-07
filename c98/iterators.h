#pragma once

#include "type_traits.h"
#include "value_traits.h"

namespace ft
{

template <typename TType, typename TContainer>
class RandomAccessIterator
{
public:
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

private:
    TType *m_Iterator;

public:
    RandomAccessIterator();
    RandomAccessIterator(TType *ptr);

    template <typename TUType>
    RandomAccessIterator(const RandomAccessIterator<
        TUType,
        typename enable_if<is_same<typename TContainer::value_type, TUType>::value, TContainer>::type>& other);

    RandomAccessIterator(const RandomAccessIterator& other);
    RandomAccessIterator& operator=(const RandomAccessIterator& other);

    /// TODO may be rewrite to friend functions
    bool operator==(const RandomAccessIterator& other) const;
    bool operator!=(const RandomAccessIterator& other) const;
    bool operator<(const RandomAccessIterator& other) const;
    bool operator<=(const RandomAccessIterator& other) const;
    bool operator>(const RandomAccessIterator& other) const;
    bool operator>=(const RandomAccessIterator& other) const;

    TType &operator*();
    TType *operator->();

    // prefix version
    RandomAccessIterator& operator++();
    RandomAccessIterator& operator--();

    // postfix version
    RandomAccessIterator operator++(int);
    RandomAccessIterator operator--(int);

    RandomAccessIterator& operator+=(const difference_type offset);
    RandomAccessIterator& operator-=(const difference_type offset);

    template <typename TUType, typename TUContainer>
    friend typename RandomAccessIterator<TUType, TUContainer>::difference_type operator-(const RandomAccessIterator<TUType, TUContainer>& lhs, const RandomAccessIterator<TUType, TUContainer>& rhs);

    template <typename TUType, typename TUContainer>
    friend RandomAccessIterator<TUType, TUContainer> operator+(const RandomAccessIterator<TUType, TUContainer>& lhs, const typename RandomAccessIterator<TUType, TUContainer>::difference_type rhs);

    template <typename TUType, typename TUContainer>
    friend RandomAccessIterator<TUType, TUContainer> operator-(const RandomAccessIterator<TUType, TUContainer>& lhs, const typename RandomAccessIterator<TUType, TUContainer>::difference_type rhs);

    template <typename TUType, typename TUContainer>
    friend RandomAccessIterator<TUType, TUContainer> operator+(const typename RandomAccessIterator<TUType, TUContainer>::difference_type lhs, const RandomAccessIterator<TUType, TUContainer>& rhs);

    TType operator[](const size_type offset);
};

template <typename TType, typename TContainer>
RandomAccessIterator<TType, TContainer>::RandomAccessIterator()
    : m_Iterator(NULL)
{}

template <typename TType, typename TContainer>
RandomAccessIterator<TType, TContainer>::RandomAccessIterator(TType *ptr)
    : m_Iterator(ptr)
{}

template <typename TType, typename TContainer>
template <typename TUType>
RandomAccessIterator<TType, TContainer>::RandomAccessIterator(const RandomAccessIterator<
        TUType,
        typename enable_if<is_same<typename TContainer::value_type, TUType>::value, TContainer>::type>& other)
    : m_Iterator(other.m_Iterator)
{}

template <typename TType, typename TContainer>
RandomAccessIterator<TType, TContainer>::RandomAccessIterator(const RandomAccessIterator& other)
        : m_Iterator(other.m_Iterator)
{}

template <typename TType, typename TContainer>
RandomAccessIterator<TType, TContainer>& RandomAccessIterator<TType, TContainer>::operator=(const RandomAccessIterator& other)
{
    if (this == &other)
    {
        return *this;
    }
    m_Iterator = other.m_Iterator;
    return *this;
}

template <typename TType, typename TContainer>
bool RandomAccessIterator<TType, TContainer>::operator==(const RandomAccessIterator& other) const
{
    return m_Iterator == other.m_Iterator;
}

template <typename TType, typename TContainer>
bool RandomAccessIterator<TType, TContainer>::operator!=(const RandomAccessIterator& other) const
{
    return !(*this == other);
}

template <typename TType, typename TContainer>
bool RandomAccessIterator<TType, TContainer>::operator<(const RandomAccessIterator& other) const
{
    return m_Iterator < other.m_Iterator;
}

template <typename TType, typename TContainer>
bool RandomAccessIterator<TType, TContainer>::operator<=(const RandomAccessIterator& other) const
{
    return m_Iterator <= other.m_Iterator;
}

template <typename TType, typename TContainer>
bool RandomAccessIterator<TType, TContainer>::operator>(const RandomAccessIterator& other) const
{
    return m_Iterator > other.m_Iterator;
}

template <typename TType, typename TContainer>
bool RandomAccessIterator<TType, TContainer>::operator>=(const RandomAccessIterator& other) const
{
    return m_Iterator >= other.m_Iterator;
}

template <typename TType, typename TContainer>
TType &RandomAccessIterator<TType, TContainer>::operator*()
{
    return *m_Iterator;
}

template <typename TType, typename TContainer>
TType *RandomAccessIterator<TType, TContainer>::operator->()
{
    return m_Iterator;
}

template <typename TType, typename TContainer>
RandomAccessIterator<TType, TContainer>& RandomAccessIterator<TType, TContainer>::operator++()
{
    ++m_Iterator;
    return *this;
}

template <typename TType, typename TContainer>
RandomAccessIterator<TType, TContainer>& RandomAccessIterator<TType, TContainer>::operator--()
{
    --m_Iterator;
    return *this;
}

template <typename TType, typename TContainer>
RandomAccessIterator<TType, TContainer> RandomAccessIterator<TType, TContainer>::operator++(int)
{
    RandomAccessIterator temp(*this);
    ++(*this);
    return temp;
}

template <typename TType, typename TContainer>
RandomAccessIterator<TType, TContainer> RandomAccessIterator<TType, TContainer>::operator--(int)
{
    RandomAccessIterator temp(*this);
    --(*this);
    return temp;
}

template <typename TType, typename TContainer>
RandomAccessIterator<TType, TContainer>& RandomAccessIterator<TType, TContainer>::operator+=(const typename RandomAccessIterator::difference_type offset)
{
    m_Iterator += offset;
    return *this;
}

template <typename TType, typename TContainer>
RandomAccessIterator<TType, TContainer>& RandomAccessIterator<TType, TContainer>::operator-=(const typename RandomAccessIterator::difference_type offset)
{
    m_Iterator -= offset;
    return *this;
}

template <typename TUType, typename TUContainer>
typename RandomAccessIterator<TUType, TUContainer>::difference_type operator-(const RandomAccessIterator<TUType, TUContainer>& lhs, const RandomAccessIterator<TUType, TUContainer>& rhs)
{
    return lhs.m_Iterator - rhs.m_Iterator;
}

template <typename TUType, typename TUContainer>
RandomAccessIterator<TUType, TUContainer> operator+(const RandomAccessIterator<TUType, TUContainer>& lhs, const typename RandomAccessIterator<TUType, TUContainer>::difference_type rhs)
{
    return lhs.m_Iterator + rhs;
}

template <typename TUType, typename TUContainer>
RandomAccessIterator<TUType, TUContainer> operator-(const RandomAccessIterator<TUType, TUContainer>& lhs, const typename RandomAccessIterator<TUType, TUContainer>::difference_type rhs)
{
    return lhs.m_Iterator - rhs;
}

template <typename TUType, typename TUContainer>
RandomAccessIterator<TUType, TUContainer> operator+(const typename RandomAccessIterator<TUType, TUContainer>::difference_type lhs, const RandomAccessIterator<TUType, TUContainer>& rhs)
{
    return rhs + lhs;
}

template <typename TType, typename TContainer>
TType RandomAccessIterator<TType, TContainer>::operator[](const size_type offset)
{
    return *(m_Iterator + offset);
}

}
