#pragma once

#include <limits>
#include <memory>

#include "random_access_iter.h"
#include "reverse_iter.h"
#include "algorithm.h"

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
    typedef RandomAccessIterator<pointer, vector> iterator;
    typedef RandomAccessIterator<const_pointer, vector> const_iterator;
    typedef ReverseIterator<iterator> reverse_iterator;
    typedef ReverseIterator<const_iterator> const_reverse_iterator;

//    static_assert(
//        std::is_same<value_type, typename allocator_type::value_type>::value,
//        "Different type into vector and vector allocator"); // concept-like construction for C++11+

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
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;

    const_iterator cbegin() const;
    const_iterator cend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    // capacity methods
    size_type size() const;
    size_type max_size() const;
    void resize(size_type new_size, value_type val = value_type()); /// change size, saving old elements if it happens allocation
    size_type capacity() const;
    bool empty() const;
    void reserve(size_type new_capacity); /// Only change capacity, saving old elements if it happens allocation

    // element access methods
    reference operator[](size_type position);
    const_reference operator[](size_type position) const;
    reference at(size_type position);
    const_reference at(size_type position) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    // modifiers methods
    void assign(size_type new_size, const value_type& val); /// change size, substituting all old elements to val

    template <
        typename InputIterator,
        typename = typename enable_if<is_convertible<typename InputIterator::iterator_category, input_iterator_tag>::value>::type
    >
    void assign(InputIterator begin, InputIterator end);
    void push_back(const value_type& val);
    void pop_back();
    iterator insert(iterator position, const value_type& val);
    void insert(iterator position, size_type inserted_cnt, const value_type& val);

    template <
        typename InputIterator,
        typename = typename enable_if<is_convertible<typename InputIterator::iterator_category, input_iterator_tag>::value>::type
    >
    void insert(iterator position, InputIterator first, InputIterator last);

    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);
    void swap(vector& x);
    void clear();

private:
    void construct_elements(size_type begin_pos,
                            size_type end_pos,
                            pointer destination,
                            const value_type& source);
    void construct_elements(size_type begin_pos,
                            size_type end_pos,
                            pointer destination,
                            pointer source);
    void destroy_elements(size_type begin_pos, size_type end_pos);
    void move_elements(size_type begin_pos, size_type end_pos);
};

template <typename TType, typename TAllocator>
vector<TType, TAllocator>::vector(const allocator_type& alloc)
    : m_Allocator(alloc)
    , m_Size(0)
    , m_Capacity(0)
    , m_Data(NULL)
{}

template <typename TType, typename TAllocator>
vector<TType, TAllocator>::vector(size_type mem_size, const value_type& value, const allocator_type& alloc)
    : m_Allocator(alloc)
    , m_Size(mem_size)
    , m_Capacity(mem_size)
{
    m_Data = m_Allocator.allocate(m_Capacity);
    construct_elements(0, m_Size, m_Data, value);
}

template <typename TType, typename TAllocator>
template <typename InputIterator>
vector<TType, TAllocator>::vector(InputIterator begin, InputIterator end, const allocator_type& alloc)
    : m_Allocator(alloc)
    , m_Size(0)
    , m_Capacity(end - begin)
{
    m_Data = m_Allocator.allocate(m_Capacity);
    while (begin != end)
    {
        push_back(*begin);
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
        m_Allocator.construct(m_Data + i, other[i]);
    }
}

template <typename TType, typename TAllocator>
vector<TType, TAllocator>::~vector()
{
    clear();
    m_Allocator.deallocate(m_Data, m_Capacity);
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::allocator_type vector<TType, TAllocator>::get_allocator() const
{
    return m_Allocator;
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::iterator vector<TType, TAllocator>::begin()
{
    return iterator(m_Data);
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::const_iterator vector<TType, TAllocator>::begin() const
{
    return const_iterator(m_Data);
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::iterator vector<TType, TAllocator>::end()
{
    return iterator(m_Data + m_Size);
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::const_iterator vector<TType, TAllocator>::end() const
{
    return const_iterator(m_Data + m_Size);
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::reverse_iterator vector<TType, TAllocator>::rbegin()
{
    return typename vector::reverse_iterator(end());
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::const_reverse_iterator vector<TType, TAllocator>::rbegin() const
{
    return typename vector::reverse_iterator(end());
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::reverse_iterator vector<TType, TAllocator>::rend()
{
    return typename vector::reverse_iterator(begin());
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::const_reverse_iterator vector<TType, TAllocator>::rend() const
{
    return typename vector::reverse_iterator(begin());
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::const_iterator vector<TType, TAllocator>::cbegin() const
{
    return m_Data;
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::const_iterator vector<TType, TAllocator>::cend() const
{
    return m_Data + m_Size;
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::const_reverse_iterator vector<TType, TAllocator>::crbegin() const
{
    return typename vector::reverse_iterator(cend());
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::const_reverse_iterator vector<TType, TAllocator>::crend() const
{
    return typename vector::reverse_iterator(cbegin());
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

template <typename TType, typename TAllocator>
void vector<TType, TAllocator>::resize(vector::size_type new_size, value_type val)
{
    if (new_size > max_size())
    {
        throw std::length_error("resize of vector: new size is too much");
    }
    if (new_size > capacity())
    {
        reserve(capacity() * 2 * (new_size / capacity()));
        construct_elements(m_Size, new_size, m_Data, val);
    }
    else
    {
        destroy_elements(new_size, m_Size);
    }
    m_Size = new_size;
}

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
void vector<TType, TAllocator>::reserve(size_type new_capacity)
{
    if (new_capacity > max_size())
    {
        throw std::length_error("reserve of vector: new capacity is too much");
    }
    if (new_capacity > capacity())
    {
        pointer new_data = m_Allocator.allocate(new_capacity);
        construct_elements(0, m_Size, new_data, m_Data);

        size_type saved_size = m_Size;
        clear();
        m_Allocator.deallocate(m_Data, m_Capacity);
        m_Data = new_data;
        m_Size = saved_size;
    }
    m_Capacity = new_capacity;
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
    return (*this)[position];
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::const_reference vector<TType, TAllocator>::at(vector::size_type position) const
{
    if (position >= size())
    {
        throw std::out_of_range("out of range of vector");
    }
    return (*this)[position];
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::reference vector<TType, TAllocator>::front()
{
    return *begin();
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::const_reference vector<TType, TAllocator>::front() const
{
    return *begin();
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::reference vector<TType, TAllocator>::back()
{
    return *(end() - 1);
}

template <typename TType, typename TAllocator>
typename vector<TType, TAllocator>::const_reference vector<TType, TAllocator>::back() const
{
    return *(end() - 1);
}

template <typename TType, typename TAllocator>
void vector<TType, TAllocator>::assign(vector::size_type new_size, const value_type& val)
{
    if (!empty())
    {
        clear();
    }
    if (new_size > capacity())
    {
        m_Allocator.deallocate(m_Data, m_Capacity);
        m_Capacity *= 2 * (new_size / capacity());
        m_Data = m_Allocator.allocate(capacity());
    }
    construct_elements(0, new_size, m_Data, val);
    m_Size = new_size;
}

template<typename TType, typename TAllocator>
template <typename InputIterator, typename>
void vector<TType, TAllocator>::assign(InputIterator begin, InputIterator end)
{
    if (!empty())
    {
        clear();
    }
    difference_type new_size = end - begin;
    if (new_size > capacity())
    {
        m_Allocator.deallocate(m_Data, m_Capacity);
        m_Capacity *= 2 * (new_size / capacity());
        m_Data = m_Allocator.allocate(capacity());
    }
    while (begin != end)
    {
        push_back(*begin);
        ++begin;
    }
    m_Size = new_size;
}

template<typename TType, typename TAllocator>
void vector<TType, TAllocator>::push_back(const value_type &val)
{
    if (size() == capacity())
    {
        if (capacity() == 0)
        {
            reserve(1);
        }
        else
        {
            reserve(capacity() * 2);
        }
    }
    construct_elements(m_Size, m_Size + 1, m_Data, val);
    ++m_Size;
}

template<typename TType, typename TAllocator>
void vector<TType, TAllocator>::pop_back()
{
    --m_Size;
    destroy_elements(m_Size, m_Size + 1);
}

template<typename TType, typename TAllocator>
typename vector<TType, TAllocator>::iterator vector<TType, TAllocator>::insert(iterator position, const value_type& val)
{
    typename vector::iterator inserted;
    size_type inserting_idx = position - begin();
    insert(position, 1, val);
    inserted = &m_Data[inserting_idx];
    return inserted;
}

template<typename TType, typename TAllocator>
void vector<TType, TAllocator>::insert(iterator position, size_type inserted_cnt, const value_type& val)
{
    size_type inserting_idx = position - begin();
    size_type new_size = m_Size + inserted_cnt;
    if (new_size > m_Capacity)
    {
        size_type new_capacity = m_Capacity ? m_Capacity * 2 * (new_size / m_Capacity) : new_size;
        pointer new_data = m_Allocator.allocate(new_capacity);

        construct_elements(0, inserting_idx, new_data, m_Data);
        for (size_type i = 0; i < inserted_cnt; ++i)
        {
            m_Allocator.construct(new_data + inserting_idx + i, val);
        }
        for (size_type i = inserting_idx + inserted_cnt; i < new_size; ++i)
        {
            m_Allocator.construct(new_data + i, m_Data[i - inserted_cnt]);
        }
//            construct_elements(inserting_idx + 1, m_Size, new_data, m_Data);

        clear();
        m_Allocator.deallocate(m_Data, m_Capacity);
        m_Data = new_data;
        m_Capacity = new_capacity;
    }
    else
    {
        for (size_type i = m_Size - 1; i >= inserting_idx; --i)
        {
            m_Allocator.construct(m_Data + i + inserted_cnt, m_Data[i]);
            m_Allocator.destroy(m_Data + i);
        }
        for (size_type i = 0; i < inserted_cnt; ++i)
        {
            m_Allocator.construct(m_Data + inserting_idx + i, val);
        }
    }
    m_Size = new_size;
}

template<typename TType, typename TAllocator>
template <typename InputIterator, typename>
void vector<TType, TAllocator>::insert(iterator position, InputIterator first, InputIterator last)
{
    size_type inserted_cnt = last - first;
    size_type inserting_idx = position - begin();
    size_type new_size = m_Size + inserted_cnt;
    if (new_size > m_Capacity)
    {
        size_type new_capacity = m_Capacity ? m_Capacity * 2 * (new_size / m_Capacity) : new_size;
        pointer new_data = m_Allocator.allocate(new_capacity);

        construct_elements(0, inserting_idx, new_data, m_Data);
        for (size_type i = 0; i < inserted_cnt; ++i)
        {
            m_Allocator.construct(new_data + inserting_idx + i, *(first + i));
        }
        for (size_type i = inserting_idx + inserted_cnt; i < new_size; ++i)
        {
            m_Allocator.construct(new_data + i, m_Data[i - inserted_cnt]);
        }
//        construct_elements(inserting_idx + 1, m_Size, new_data, m_Data);

        clear();
        m_Allocator.deallocate(m_Data, m_Capacity);
        m_Data = new_data;
        m_Capacity = new_capacity;
    }
    else
    {
        for (size_type i = m_Size - 1; i >= inserting_idx; --i)
        {
            m_Allocator.construct(m_Data + i + inserted_cnt, m_Data[i]);
            m_Allocator.destroy(m_Data + i);
        }
        for (size_type i = 0; i < inserted_cnt; ++i)
        {
            m_Allocator.construct(m_Data + inserting_idx + i, *(first + i));
        }
    }
    m_Size = new_size;
}

template<typename TType, typename TAllocator>
typename vector<TType, TAllocator>::iterator vector<TType, TAllocator>::erase(iterator position)
{
    size_type erased_idx = position - begin();
    destroy_elements(erased_idx, erased_idx + 1);
    for (size_type i = erased_idx + 1; i < m_Size; ++i)
    {
        m_Allocator.construct(m_Data + (i - 1), m_Data[i]);
        m_Allocator.destroy(m_Data + i);
    }
    --m_Size;
    return begin() + erased_idx;
}

template<typename TType, typename TAllocator>
typename vector<TType, TAllocator>::iterator vector<TType, TAllocator>::erase(iterator first, iterator last)
{
    size_type start_idx = first - begin();
    size_type end_idx = last - begin();

    destroy_elements(start_idx, end_idx);
    for (size_type i = end_idx; i < m_Size; ++i)
    {
        m_Allocator.construct(m_Data + start_idx + (i - end_idx), m_Data[i]);
        m_Allocator.destroy(m_Data + i);
    }
    m_Size -= last - first;
    return begin() + start_idx;
}

template<typename TType, typename TAllocator>
void vector<TType, TAllocator>::swap(vector& x)
{
    if (x == *this)
    {
        return;
    }

    allocator_type tmp_alloc = m_Allocator;
    size_type tmp_size = m_Size;
    size_type tmp_capacity = m_Capacity;
    pointer tmp_data = m_Data;

    m_Allocator = x.m_Allocator;
    m_Size = x.m_Size;
    m_Capacity = x.m_Capacity;
    m_Data = x.m_Data;

    x.m_Allocator = tmp_alloc;
    x.m_Size = tmp_size;
    x.m_Capacity = tmp_capacity;
    x.m_Data = tmp_data;
}

template <typename TType, typename TAllocator>
void vector<TType, TAllocator>::clear()
{
    destroy_elements(0, m_Size);
    m_Size = 0;
}

template <typename TType, typename TAllocator>
void vector<TType, TAllocator>::construct_elements(size_type begin_pos,
                                                   size_type end_pos,
                                                   pointer destination,
                                                   const value_type& source)
{
    for (size_type i = begin_pos; i < end_pos; ++i)
    {
        m_Allocator.construct(destination + i, source);
    }
}

template <typename TType, typename TAllocator>
void vector<TType, TAllocator>::construct_elements(size_type begin_pos,
                                                   size_type end_pos,
                                                   pointer destination,
                                                   pointer source)
{
    for (size_type i = begin_pos; i < end_pos; ++i)
    {
        m_Allocator.construct(destination + i, source[i]);
    }
}

template <typename TType, typename TAllocator>
void vector<TType, TAllocator>::destroy_elements(size_type begin_pos, size_type end_pos)
{
    for (size_type i = begin_pos; i < end_pos; ++ i)
    {
        m_Allocator.destroy(m_Data + i);
    }
}

template <typename TType, typename TAllocator>
void vector<TType, TAllocator>::move_elements(size_type begin_pos, size_type end_pos)
{

}

template <class TType, class TAlloc>
void swap(vector<TType, TAlloc>& x, vector<TType, TAlloc>& y)
{
    x.swap(y);
}

template <typename TType, typename TAlloc>
bool operator==(const vector<TType,TAlloc>& lhs, const vector<TType,TAlloc>& rhs)
{
    return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename TType, typename TAlloc>
bool operator!=(const vector<TType,TAlloc>& lhs, const vector<TType,TAlloc>& rhs)
{
    return !(lhs == rhs);
}

template <typename TType, typename TAlloc>
bool operator<(const vector<TType,TAlloc>& lhs, const vector<TType,TAlloc>& rhs)
{
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename TType, typename TAlloc>
bool operator>(const vector<TType,TAlloc>& lhs, const vector<TType,TAlloc>& rhs)
{
    return rhs < lhs;
}

template <typename TType, typename TAlloc>
bool operator<=(const vector<TType,TAlloc>& lhs, const vector<TType,TAlloc>& rhs)
{
    return !(rhs < lhs);
}

template <typename TType, typename TAlloc>
bool operator>=(const vector<TType,TAlloc>& lhs, const vector<TType,TAlloc>& rhs)
{
    return !(lhs < rhs);
}

}
