#pragma once

namespace ft
{

template <typename TType>
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

    template <typename TUType>
    friend difference_type operator-(const RandomAccessIterator<TUType>& lhs, const RandomAccessIterator<TUType>& rhs);

    friend RandomAccessIterator operator+(const RandomAccessIterator& lhs, const difference_type rhs)
    {
        return lhs.m_Iterator + rhs;
    }

    template <typename TUType>
    friend RandomAccessIterator<TUType> operator-(const RandomAccessIterator<TUType>& lhs, const difference_type rhs);

    template <typename TUType>
    friend RandomAccessIterator<TUType> operator+(const difference_type lhs, const RandomAccessIterator<TUType>& rhs);

    TType operator[](const size_type offset);
};

template <typename TType>
RandomAccessIterator<TType>::RandomAccessIterator()
    : m_Iterator(NULL)
{}

template <typename TType>
RandomAccessIterator<TType>::RandomAccessIterator(TType *ptr)
    : m_Iterator(ptr)
{}

template <typename TType>
RandomAccessIterator<TType>::RandomAccessIterator(const RandomAccessIterator& other)
    : m_Iterator(other.m_Iterator)
{}

template <typename TType>
RandomAccessIterator<TType>& RandomAccessIterator<TType>::operator=(const RandomAccessIterator& other)
{
    if (this == &other)
    {
        return *this;
    }
    m_Iterator = other.m_Iterator;
    return *this;
}

template <typename TType>
bool RandomAccessIterator<TType>::operator==(const RandomAccessIterator& other) const
{
    return m_Iterator == other.m_Iterator;
}

template <typename TType>
bool RandomAccessIterator<TType>::operator!=(const RandomAccessIterator& other) const
{
    return !(*this == other);
}

template <typename TType>
bool RandomAccessIterator<TType>::operator<(const RandomAccessIterator& other) const
{
    return m_Iterator < other.m_Iterator;
}

template <typename TType>
bool RandomAccessIterator<TType>::operator<=(const RandomAccessIterator& other) const
{
    return m_Iterator <= other.m_Iterator;
}

template <typename TType>
bool RandomAccessIterator<TType>::operator>(const RandomAccessIterator& other) const
{
    return m_Iterator > other.m_Iterator;
}

template <typename TType>
bool RandomAccessIterator<TType>::operator>=(const RandomAccessIterator& other) const
{
    return m_Iterator >= other.m_Iterator;
}

template <typename TType>
TType &RandomAccessIterator<TType>::operator*()
{
    return *m_Iterator;
}

template <typename TType>
TType *RandomAccessIterator<TType>::operator->()
{
    return m_Iterator;
}

template <typename TType>
RandomAccessIterator<TType>& RandomAccessIterator<TType>::operator++()
{
    ++m_Iterator;
    return *this;
}

template <typename TType>
RandomAccessIterator<TType>& RandomAccessIterator<TType>::operator--()
{
    --m_Iterator;
    return *this;
}

template <typename TType>
RandomAccessIterator<TType> RandomAccessIterator<TType>::operator++(int)
{
    RandomAccessIterator temp(*this);
    ++(*this);
    return temp;
}

template <typename TType>
RandomAccessIterator<TType> RandomAccessIterator<TType>::operator--(int)
{
    RandomAccessIterator temp(*this);
    --(*this);
    return temp;
}

template <typename TType>
RandomAccessIterator<TType>& RandomAccessIterator<TType>::operator+=(const typename RandomAccessIterator::difference_type offset)
{
    m_Iterator += offset;
    return *this;
}

template <typename TType>
RandomAccessIterator<TType>& RandomAccessIterator<TType>::operator-=(const typename RandomAccessIterator::difference_type offset)
{
    m_Iterator -= offset;
    return *this;
}

template <typename TUType>
typename RandomAccessIterator<TUType>::difference_type operator-(const RandomAccessIterator<TUType>& lhs, const RandomAccessIterator<TUType>& rhs)
{
    return lhs.m_Iterator - rhs.m_Iterator;
}

//template <typename TType>
//RandomAccessIterator<TType> operator+(const RandomAccessIterator<TType>& lhs, const typename RandomAccessIterator<TType>::difference_type rhs)
//{
//    return lhs.m_Iterator + rhs;
//}

template <typename TUType>
RandomAccessIterator<TUType> operator-(const RandomAccessIterator<TUType>& lhs, const typename RandomAccessIterator<TUType>::difference_type rhs)
{
    return lhs.m_Iterator - rhs;
}

template <typename TUType>
RandomAccessIterator<TUType> operator+(const typename RandomAccessIterator<TUType>::difference_type lhs, const RandomAccessIterator<TUType>& rhs)
{
    return rhs + lhs;
}

template <typename TType>
TType RandomAccessIterator<TType>::operator[](const size_type offset)
{
    return *(m_Iterator + offset);
}

}
