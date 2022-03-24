#pragma once

#include <memory>

#include "rb_tree.h"
#include "utility.h"
#include "functional.h"

namespace ft
{

template <class T,
          class Compare = ft::less<T>,
          class Alloc = std::allocator<T>
>
class set
{
public:
    typedef T key_type;
    typedef T value_type;
    typedef Compare key_compare;
    typedef Compare value_compare;
    typedef Alloc allocator_type;

    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;

private:
    typedef RbTree<key_type, value_type, key_compare, Identity<value_type>, allocator_type> rb_tree_type;

public:
    typedef typename rb_tree_type::iterator iterator;
    typedef typename rb_tree_type::const_iterator const_iterator;
    typedef typename rb_tree_type::reverse_iterator reverse_iterator;
    typedef typename rb_tree_type::const_reverse_iterator const_reverse_iterator;
    typedef typename rb_tree_type::difference_type difference_type;
    typedef typename rb_tree_type::size_type size_type;

private:
    rb_tree_type m_Tree;

public:
    explicit set(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : m_Tree(comp, alloc) {}

    template <class InputIterator>
    set(InputIterator first, InputIterator last,
        const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type()) : m_Tree(comp, alloc)
    {
        while (first != last)
        {
            m_Tree.add(*first++);
        }
    }

    set(const set& x) : m_Tree(x.m_Tree) {}

    set &operator=(const set& x)
    {
        if (&x != this)
        {
            m_Tree = x.m_Tree;
        }
        return *this;
    }

    ~set() {}

    iterator begin() { return iterator(&m_Tree, m_Tree.get_min()); }
    const_iterator begin() const { return const_iterator(&m_Tree, m_Tree.get_min()); }
    iterator end() { return iterator(&m_Tree, NULL); }
    const_iterator end() const { return const_iterator(&m_Tree, NULL); }

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

    bool empty() const { return m_Tree.empty(); }
    size_type size() const { return m_Tree.size(); }
    size_type max_size() const { return m_Tree.max_size(); }

    pair<iterator, bool> insert(const value_type& val)
    {
        iterator found = find(val);
        if (found != end())
        {
            return pair<iterator, bool>(found, false);
        }
        iterator ret(&m_Tree, m_Tree.add(val));
        return pair<iterator, bool>(ret, true);
    }

    iterator insert(iterator position, const value_type& val)
    {
        iterator found = find(val);
        if (found != end())
        {
            return found;
        }
        return iterator(&m_Tree, m_Tree.add(position, val));
    }

    template <class InputIterator>
    typename enable_if<is_same<typename InputIterator::value_type, value_type>::value>::type
    insert(InputIterator first, InputIterator last)
    {
        while (first != last)
        {
            if (find(*first) == end())
            {
                m_Tree.add(*first);
            }
            ++first;
        }
    }

    void erase(iterator position)
    {
        m_Tree.deleteKey(*position);
    }

    size_type erase(const value_type& val)
    {
        return m_Tree.deleteKey(val);
    }

    void erase(iterator first, iterator last)
    {
        while (first != last)
        {
            erase(first++);
        }
    }

    void swap(set& x)
    {
        m_Tree.swap(x.m_Tree);
    }

    void clear()
    {
        m_Tree.clear();
    }

    key_compare key_comp() const { return m_Tree.key_comp(); }
    value_compare value_comp() const { return m_Tree.key_comp(); }

    iterator find(const value_type& val) const
    {
        return iterator(&m_Tree, m_Tree.find(val));
    }

    size_type count(const value_type& val) const
    {
        return (m_Tree.find(val)) ? 1 : 0;
    }

    iterator lower_bound(const value_type& val) const
    {
        return iterator(&m_Tree, m_Tree.lower_bound(val));
    }

    iterator upper_bound(const value_type& val) const
    {
        return iterator(&m_Tree, m_Tree.upper_bound(val));
    }

    pair<iterator, iterator> equal_range(const value_type& val) const
    {
        return pair<iterator, iterator>(lower_bound(val), upper_bound(val));
    }

    allocator_type get_allocator() const
    {
        return allocator_type(m_Tree.get_allocator());
    }

    friend bool operator==(const set& lhs, const set& rhs)
    {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    friend bool operator<(const set& lhs, const set& rhs)
    {
        return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
};

template <typename T, typename Compare, typename Alloc>
bool operator!=(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
    return !(lhs == rhs);
}

template <typename T, typename Compare, typename Alloc>
bool operator>=(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
    return !(lhs < rhs);
}

template <class T, class Compare, class Alloc>
bool operator>(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
    return rhs < lhs;
}

template <class T, class Compare, class Alloc>
bool operator<=(const set<T, Compare, Alloc> &lhs, const set<T, Compare, Alloc> &rhs)
{
    return !(rhs < lhs);
}

template <class T, class Compare, class Alloc>
void swap(set<T, Compare, Alloc> &a, set<T, Compare, Alloc> &b)
{
    a.swap(b);
}

}