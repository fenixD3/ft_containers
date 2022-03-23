#pragma once

#include "rb_tree.h"
#include "utility.h"
#include "type_traits.h"
//#include "functional.h"

namespace ft
{

template <typename Key,                                      // map::key_type
           typename Val,                                       // map::mapped_type
           typename Compare = std::less<Key>,                     // map::key_compare
           typename Alloc = std::allocator<pair<const Key, Val> >    // map::allocator_type
>
class map
{
public:
    typedef Key key_type; //	The first template parameter (Key)
    typedef Val mapped_type; //	The second template parameter (Val)
    typedef pair<const key_type, mapped_type> value_type; //	pair<const key_type,mapped_type>
    typedef Compare key_compare; //	The third template parameter (Compare)	defaults to: less<key_type>
    typedef Alloc allocator_type; //	The fourth template parameter (Alloc)	defaults to: allocator<value_type>
    typedef typename allocator_type::reference reference; // allocator_type::reference	for the default allocator: value_type&
    typedef const typename allocator_type::const_reference const_reference; //	allocator_type::const_reference	for the default allocator: const value_type&
    typedef typename allocator_type::pointer pointer; //	allocator_type::pointer	for the default allocator: value_type*
    typedef const typename allocator_type::const_pointer const_pointer; //	allocator_type::const_pointer	for the default allocator: const value_type*

    class value_compare
    {
        // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
//        friend class map;
    protected:
        Compare m_Comp;
        explicit value_compare(Compare c) : m_Comp(c) {}  // constructed with map's comparison object
    public:
        typedef bool result_type;
        typedef value_type first_argument_type;
        typedef value_type second_argument_type;

    public:
        bool operator()(const value_type& x, const value_type& y) const
        {
            return m_Comp(x.first, y.first);
        }
    };	// Nested function class to compare elements	see value_comp

private:
    typedef RbTree<key_type, value_type, key_compare, Select1st<value_type>, allocator_type> rb_tree_type;

public:
    typedef typename rb_tree_type::iterator iterator; // a bidirectional iterator to value_type	convertible to const_iterator
    typedef typename rb_tree_type::const_iterator const_iterator; //	a bidirectional iterator to const value_type
    typedef typename rb_tree_type::reverse_iterator reverse_iterator; //	reverse_iterator<iterator>
    typedef typename rb_tree_type::const_reverse_iterator const_reverse_iterator; //	reverse_iterator<const_iterator>
    typedef typename rb_tree_type::difference_type difference_type; //	a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
    typedef typename rb_tree_type::size_type size_type; //	an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t

private:
    rb_tree_type m_Tree;

public:
    explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : m_Tree(comp, alloc) {}

    template <class InputIterator>
    map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
        : m_Tree(comp, alloc)
    {
        for (; first != last; first++)
        {
            m_Tree.add(*first);
        }
    }

    map(const map& x) : m_Tree(x.m_Tree) {}

    ~map() {}

    map& operator=(const map& x)
    {
        if (&x != this)
        {
            m_Tree = x.m_Tree;
        }
        return *this;
    }

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

    mapped_type& operator[](const key_type& key)
    {
        return (m_Tree.add(ft::make_pair(key, mapped_type())))->m_Value.second;
    }

    pair<iterator, bool> insert(const value_type& val)
    {
        iterator found = find(val.first);
        if (found != end())
        {
            return pair<iterator, bool>(found, false);
        }
        iterator ret(&m_Tree, m_Tree.add(val));
        return pair<iterator, bool>(ret, true);
    }

    iterator insert(iterator position, const value_type& val)
    {
        iterator found = find(val.first);
        if (found != end())
        {
            return found;
        }
        return iterator(&m_Tree, m_Tree.add(position, val));
    }

    template <typename InputIterator>
    typename enable_if<is_same<typename InputIterator::value_type, value_type>::value>::type
    insert(InputIterator first, InputIterator last)
    {
        while (first != last)
        {
            if (find(first->first) == end())
            {
                m_Tree.add(*first);
            }
            ++first;
        }
    }

    void erase(iterator position)
    {
        m_Tree.deleteKey(position->first);
    }

    size_type erase(const key_type& k)
    {
        return m_Tree.deleteKey(k);
    }

    void erase(iterator first, iterator last)
    {
        while (first != last)
        {
            erase(first++);
        }
    }

    void swap(map& x)
    {
        m_Tree.swap(x.m_Tree);
    }

    void clear()
    {
        m_Tree.clear();
    }

    key_compare key_comp() const { return m_Tree.key_comp(); }
    value_compare value_comp() const { return value_compare(m_Tree.key_comp()); }

    iterator find(const key_type& k)
    {
        return iterator(&m_Tree, m_Tree.find(k));
    }

    const_iterator find(const key_type& k) const
    {
        return const_iterator(&m_Tree, m_Tree.find(k));
    }

    size_type count(const key_type& k) const
    {
        return (m_Tree.find(k)) ? 1 : 0;
    }

    iterator lower_bound(const key_type& k)
    {
        return iterator(&m_Tree, m_Tree.lower_bound(k));
    }

    const_iterator lower_bound(const key_type& k) const
    {
        return iterator(&m_Tree, m_Tree.lower_bound(k));
    }

    iterator upper_bound(const key_type& k)
    {
        return iterator(&m_Tree, m_Tree.upper_bound(k));
    }

    const_iterator upper_bound(const key_type& k) const
    {
        return const_iterator(&m_Tree, m_Tree.upper_bound(k));
    }

    ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
    {
        return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
    }

    ft::pair<iterator, iterator> equal_range(const key_type& k)
    {
        return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
    }

    allocator_type get_allocator() const
    {
        return allocator_type(m_Tree.get_allocator());
    }

    friend bool operator==(const map& lhs, const map& rhs)
    {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    friend bool operator<(const map& lhs, const map& rhs)
    {
        return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
};

template <typename Key, typename Val, typename Compare, typename Alloc>
bool operator!=(const map<Key, Val, Compare, Alloc>& lhs, const map<Key, Val, Compare, Alloc>& rhs)
{
    return !(lhs == rhs);
}

template <typename Key, typename Val, typename Compare, typename Alloc>
bool operator<=(const map<Key, Val, Compare, Alloc>& lhs, const map<Key, Val, Compare, Alloc>& rhs)
{
    return !(rhs < lhs);
}

template <typename Key, typename Val, typename Compare, typename Alloc>
bool operator>(const map<Key, Val, Compare, Alloc>& lhs, const map<Key, Val, Compare, Alloc>& rhs)
{
    return rhs < lhs;
}

template <typename Key, typename Val, typename Compare, typename Alloc>
bool operator>=(const map<Key, Val, Compare, Alloc>& lhs, const map<Key, Val, Compare, Alloc>& rhs)
{
    return !(lhs < rhs);
}

template <typename Key, typename Val, typename Compare, typename Alloc>
void swap(map<Key, Val, Compare, Alloc>& a, map<Key, Val, Compare, Alloc>& b)
{
    a.swap(b);
}

}
