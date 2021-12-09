#pragma once

#include "iterators.h"

namespace ft
{

template <typename TType, typename TAllocator = std::allocator<TType> >
class vector
{
public:
    typedef TType value_type;
    typedef TAllocator allocator_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef typename allocator_type::reference reference;
    typedef const typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;
    typedef RandomAccessIterator<value_type> iterator;
//    typedef ... const_iterator;
//    typedef ... reverse_iterator;
//    typedef ... const_reverse_iterator;

    static_assert(
        std::is_same<value_type, typename allocator_type::value_type>::value,
        "Different type into vector and vector allocator"); // concept-like construction

private:
    allocator_type m_Allocator;
    size_type m_Size;
    size_type m_Capacity;
    pointer m_Data;

public:
    explicit vector(const allocator_type& alloc = allocator_type());
    explicit vector(size_type mem_size, const value_type& value = value_type(), const allocator_type& alloc = allocator_type());

    template <typename InputIterator>
    vector(InputIterator begin, InputIterator end, const allocator_type& alloc = allocator_type());

    vector(const vector& other);

    ~vector();

    allocator_type get_allocator() const;

    // iterator methods

    // capacity methods
    size_type size() const;
    size_type max_size() const;
//    void resize(size_type new_size, value_type val = value_type());
    size_type capacity() const;
    bool empty() const;

    // element access methods
    reference operator[](size_type position);
    const_reference operator[](size_type position) const;

    reference at(size_type position);
    const_reference at(size_type position) const;

    // modifiers methods
    void assign(size_type new_size, const value_type& val);

private:
    void destroy_elements();
};

template <typename TType, typename TAllocator>
vector<TType, TAllocator>::vector(const allocator_type& alloc)
    : m_Allocator(alloc)
    , m_Size(0)
    , m_Capacity(0)
    , m_Data(nullptr)
{}

template <typename TType, typename TAllocator>
vector<TType, TAllocator>::vector(size_type mem_size, const value_type& value, const allocator_type& alloc)
    : m_Allocator(alloc)
    , m_Size(mem_size)
    , m_Capacity(mem_size)
{
    m_Data = m_Allocator.allocate(m_Capacity);
    for (size_type i = 0; i < m_Size; ++i)
    {
        m_Allocator.construct(m_Data + i, value);
    }
}

template <typename TType, typename TAllocator>
template <typename InputIterator>
vector<TType, TAllocator>::vector(InputIterator begin, InputIterator end, const allocator_type& alloc)
    : m_Allocator(alloc)
    , m_Size(end - begin)
    , m_Capacity(end - begin)
{
    m_Data = m_Allocator.allocate(m_Capacity);
    while (begin != end)
    {
        m_Allocator.construct(begin, *begin);
        ++begin;
    }
}

template <typename TType, typename TAllocator>
vector<TType, TAllocator>::vector(const vector& other)
    : m_Allocator(other.m_Allocator)
    , m_Size(other.m_Size)
    , m_Capacity(other.m_Capacity)
{
    m_Data = m_Allocator.allocate(m_Capacity);
    for (size_type i = 0; i < other.m_Size; ++i)
    {
        m_Data[i] = other[i];
    }
}

template <typename TType, typename TAllocator>
vector<TType, TAllocator>::~vector()
{
    destroy_elements();
    m_Allocator.deallocate(m_Data, m_Capacity);
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::allocator_type vector<TType, TAllocator>::get_allocator() const
{
    return m_Allocator;
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::size_type vector<TType, TAllocator>::size() const
{
    return m_Size;
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::size_type vector<TType, TAllocator>::max_size() const
{
    return std::numeric_limits<size_type>::max();
}

//template <typename TType, typename TAllocator>
//void vector<TType, TAllocator>::resize(vector::size_type new_size, value_type val)
//{
//
//}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::size_type vector<TType, TAllocator>::capacity() const
{
    return m_Capacity;
}

template <typename TType, typename TAllocator>
bool vector<TType, TAllocator>::empty() const
{
    return size() == 0;
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::reference vector<TType, TAllocator>::operator[](vector::size_type position)
{
    return *(m_Data + position);
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::const_reference vector<TType, TAllocator>::operator[](vector::size_type position) const
{
    return *(m_Data + position);
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::reference vector<TType, TAllocator>::at(vector::size_type position)
{
    if (position >= size())
    {
        throw std::out_of_range("out of range of vector");
    }
    return operator[](position);
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::const_reference vector<TType, TAllocator>::at(vector::size_type position) const
{
    if (position >= size())
    {
        throw std::out_of_range("out of range of vector");
    }
    return operator[](position);
}

template <typename TType, typename TAllocator>
void vector<TType, TAllocator>::assign(vector::size_type new_size, const value_type& val)
{
    if (!empty())
    {
        destroy_elements();
    }
    if (new_size >= capacity())
    {
        /// TODO
    }
}

template <typename TType, typename TAllocator>
void vector<TType, TAllocator>::destroy_elements()
{
    for (size_type i = 0; i < m_Size; ++i)
    {
        m_Allocator.destroy(m_Data + i);
    }
}

}
