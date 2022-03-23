#pragma once

#include "iterator_traits.h"
#include "type_traits.h"

namespace ft
{

template <typename TIter, typename TContainer>
class RandomAccessIterator
{
public:
    typedef std::size_t size_type;
    typedef typename iterator_traits<TIter>::iterator_category iterator_category;
    typedef typename iterator_traits<TIter>::difference_type difference_type;
    typedef typename iterator_traits<TIter>::pointer pointer;
    typedef typename iterator_traits<TIter>::value_type value_type;
    typedef typename iterator_traits<TIter>::reference reference;

private:
    pointer m_Iterator;

public:
    RandomAccessIterator() : m_Iterator(NULL) {}
    RandomAccessIterator(pointer ptr) : m_Iterator(ptr) {}

    template <typename TUIter>
    RandomAccessIterator(const RandomAccessIterator<TUIter,
                         typename enable_if<is_same<typename TContainer::pointer, TUIter>::value, TContainer>::type>& other)
        : m_Iterator(other.operator->())
    {}

    RandomAccessIterator(const RandomAccessIterator& other) : m_Iterator(other.m_Iterator) {}
    RandomAccessIterator& operator=(const RandomAccessIterator& other)
    {
        if (this == &other)
        {
            return *this;
        }
        m_Iterator = other.m_Iterator;
        return *this;
    }

    friend bool operator==(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs)
    {
        return lhs.m_Iterator == rhs.m_Iterator;
    }

    friend bool operator<(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs)
    {
        return lhs.m_Iterator < rhs.m_Iterator;
    }

    reference operator*() const { return *m_Iterator; }
    pointer operator->() const { return m_Iterator; }

    // prefix version
    RandomAccessIterator& operator++()
    {
        ++m_Iterator;
        return *this;
    }

    RandomAccessIterator& operator--()
    {
        --m_Iterator;
        return *this;
    }

    // postfix version
    RandomAccessIterator operator++(int)
    {
        RandomAccessIterator temp(*this);
        ++(*this);
        return temp;
    }

    RandomAccessIterator operator--(int)
    {
        RandomAccessIterator temp(*this);
        --(*this);
        return temp;
    }

    RandomAccessIterator& operator+=(const difference_type offset)
    {
        m_Iterator += offset;
        return *this;
    }

    RandomAccessIterator& operator-=(const difference_type offset)
    {
        m_Iterator -= offset;
        return *this;
    }

    template <typename TUIter, typename TUContainer>
    friend typename RandomAccessIterator<TUIter, TUContainer>::difference_type operator-(
            const RandomAccessIterator<TUIter, TUContainer>& lhs,
            const RandomAccessIterator<TUIter, TUContainer>& rhs);

    friend RandomAccessIterator operator+(const RandomAccessIterator& lhs, const difference_type rhs)
    {
        return RandomAccessIterator(lhs.m_Iterator + rhs);
    }

    friend RandomAccessIterator operator-(const RandomAccessIterator& lhs, const difference_type rhs)
    {
        return RandomAccessIterator(lhs.m_Iterator - rhs);
    }

    friend RandomAccessIterator operator+(const difference_type lhs, const RandomAccessIterator& rhs)
    {
        return RandomAccessIterator(rhs + lhs);
    }

    reference operator[](const size_type offset) const { return *(m_Iterator + offset); }
};

template <typename TIter, typename TContainer>
bool operator!=(const RandomAccessIterator<TIter, TContainer>& lhs, const RandomAccessIterator<TIter, TContainer>& rhs)
{
    return !(lhs == rhs);
}

template <typename TIter, typename TContainer>
bool operator<=(const RandomAccessIterator<TIter, TContainer>& lhs, const RandomAccessIterator<TIter, TContainer>& rhs)
{
    return !(rhs < lhs);
}

template <typename TIter, typename TContainer>
bool operator>(const RandomAccessIterator<TIter, TContainer>& lhs, const RandomAccessIterator<TIter, TContainer>& rhs)
{
    return rhs < lhs;
}

template <typename TIter, typename TContainer>
bool operator>=(const RandomAccessIterator<TIter, TContainer>& lhs, const RandomAccessIterator<TIter, TContainer>& rhs)
{
    return !(lhs < rhs);
}

template <typename TUIter, typename TUContainer>
typename RandomAccessIterator<TUIter, TUContainer>::difference_type operator-(
        const RandomAccessIterator<TUIter, TUContainer>& lhs, 
        const RandomAccessIterator<TUIter, TUContainer>& rhs)
{
    return lhs.m_Iterator - rhs.m_Iterator;
}

}
