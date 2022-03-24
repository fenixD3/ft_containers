#pragma once

#include "vector.h"

namespace ft
{

template <typename TType, typename TContainer = vector<TType> >
class stack
{
public:
    typedef TType value_type;
    typedef TContainer container_type;
    typedef typename container_type::size_type size_type;

protected:
    container_type m_Container;

public:
    explicit stack(const container_type& container = container_type())
        : m_Container(container)
    {}

    bool empty() const
    { 
        return m_Container.empty();
    }

    size_type size() const
    {
        return m_Container.size();
    }

    value_type& top()
    {
        return m_Container.back();
    }

    const value_type& top() const
    {
        return m_Container.back();
    }

    void push(const value_type& val)
    {
        m_Container.push_back(val);
    }

    void pop()
    {
        m_Container.pop_back();
    }

    friend bool operator==(const stack<TType, TContainer>& lhs, const stack<TType, TContainer>& rhs)
    {
        return lhs.m_Container == rhs.m_Container;
    }

    friend bool operator!=(const stack<TType, TContainer>& lhs, const stack<TType, TContainer>& rhs)
    {
        return !(lhs == rhs);
    }

    friend bool operator<(const stack<TType, TContainer>& lhs, const stack<TType, TContainer>& rhs)
    {
        return lhs.m_Container < rhs.m_Container;
    }

    friend bool operator<=(const stack<TType, TContainer>& lhs, const stack<TType, TContainer>& rhs)
    {
        return !(rhs < lhs);
    }

    friend bool operator>(const stack<TType, TContainer>& lhs, const stack<TType, TContainer>& rhs)
    {
        return rhs < lhs;
    }

    friend bool operator>=(const stack<TType, TContainer>& lhs, const stack<TType, TContainer>& rhs)
    {
        return !(lhs < rhs);
    }
};

}

