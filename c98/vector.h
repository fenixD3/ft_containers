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
    explicit vector(const allocator_type& alloc = allocator_type())
        : m_Allocator(alloc)
        , m_Size(0)
        , m_Capacity(0)
        , m_Data(NULL)
    {}

    explicit vector(size_type mem_size, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
        : m_Allocator(alloc)
        , m_Size(mem_size)
        , m_Capacity(mem_size)
    {
        m_Data = m_Allocator.allocate(m_Capacity);
        construct_elements(0, m_Size, m_Data, value);
    }

    template <typename InputIterator>
    vector(InputIterator begin, InputIterator end, const allocator_type& alloc = allocator_type())
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

    vector(const vector& other)
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
    vector& operator=(const vector& other)
    {
        if (&other != this)
        {
            m_Allocator = other.m_Allocator;
            for (size_type i = 0; i < other.m_Size; ++i)
            {
                push_back(other[i]);
            }
        }
        return *this;
    }

    ~vector()
    {
        clear();
        m_Allocator.deallocate(m_Data, m_Capacity);
    }

    allocator_type get_allocator() const
    {
        return m_Allocator;
    }

    // iterator methods
    iterator begin() { return iterator(m_Data); }
    const_iterator begin() const { return const_iterator(m_Data); }
    iterator end() { return iterator(m_Data + m_Size); }
    const_iterator end() const { return const_iterator(m_Data + m_Size); }

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    const_iterator cbegin() const { return const_iterator(m_Data); }
    const_iterator cend() const { return const_iterator(m_Data + m_Size); }
    const_reverse_iterator crbegin() const { return reverse_iterator(cend()); }
    const_reverse_iterator crend() const { return reverse_iterator(cbegin()); }

    // capacity methods
    size_type size() const { return m_Size; }
    size_type max_size() const { return std::numeric_limits<size_type>::max(); }

    void resize(size_type new_size, value_type val = value_type()) /// change size, saving old elements if it happens allocation
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

    size_type capacity() const { return m_Capacity; }
    bool empty() const { return size() == 0; }

    void reserve(size_type new_capacity) /// Only change capacity, saving old elements if it happens allocation
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

    // element access methods
    reference operator[](size_type position) { return *(m_Data + position); }
    const_reference operator[](size_type position) const { return *(m_Data + position); }

    reference at(size_type position)
    {
        if (position >= size())
        {
            throw std::out_of_range("out of range of vector");
        }
        return (*this)[position];
    }

    const_reference at(size_type position) const
    {
        if (position >= size())
        {
            throw std::out_of_range("out of range of vector");
        }
        return (*this)[position];
    }

    reference front() { return *begin(); }
    const_reference front() const { return *begin(); }
    reference back() { return *(end() - 1); }
    const_reference back() const { return *(end() - 1); }

    // modifiers methods
    void assign(size_type new_size, const value_type& val) /// change size, substituting all old elements to val
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

    template <typename InputIterator>
    typename enable_if<is_convertible<typename InputIterator::iterator_category, input_iterator_tag>::value>::type
    assign(InputIterator begin, InputIterator end)
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

    void push_back(const value_type& val)
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

    void pop_back()
    {
        --m_Size;
        destroy_elements(m_Size, m_Size + 1);
    }

    iterator insert(iterator position, const value_type& val)
    {
        iterator inserted;
        size_type inserting_idx = position - begin();
        insert(position, 1, val);
        inserted = &m_Data[inserting_idx];
        return inserted;
    }

    void insert(iterator position, size_type inserted_cnt, const value_type& val)
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

    template <typename InputIterator>
    typename enable_if<is_convertible<typename InputIterator::iterator_category, input_iterator_tag>::value>::type
    insert(iterator position, InputIterator first, InputIterator last)
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

    iterator erase(iterator position)
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

    iterator erase(iterator first, iterator last)
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

    void swap(vector& x)
    {
        if (&x == this)
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

    void clear()
    {
        destroy_elements(0, m_Size);
        m_Size = 0;
    }

private:
    void construct_elements(size_type begin_pos,
                            size_type end_pos,
                            pointer destination,
                            const value_type& source)
    {
        for (size_type i = begin_pos; i < end_pos; ++i)
        {
            m_Allocator.construct(destination + i, source);
        }
    }

    void construct_elements(size_type begin_pos,
                            size_type end_pos,
                            pointer destination,
                            pointer source)
    {
        for (size_type i = begin_pos; i < end_pos; ++i)
        {
            m_Allocator.construct(destination + i, source[i]);
        }
    }

    void destroy_elements(size_type begin_pos, size_type end_pos)
    {
        for (size_type i = begin_pos; i < end_pos; ++ i)
        {
            m_Allocator.destroy(m_Data + i);
        }
    }
};


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
