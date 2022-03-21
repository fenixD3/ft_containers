#pragma once

#include "rb_tree.h"
#include "utility.h"
//#include "functional.h"
#include "reverse_iter.h"

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
    typedef ReverseIterator<iterator> reverse_iterator; //	reverse_iterator<iterator>
    typedef ReverseIterator<const_iterator> const_reverse_iterator; //	reverse_iterator<const_iterator>
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
//        for (; first != last; first++)
//            m_Tree.add(*first);
    }

    map(const map& x) : m_Tree(x.m_Tree) {}

    ~map() {}

    map& operator=(const map& x)
    {
        m_Tree = x.m_Tree;
        return *this;
    }

    iterator begin() { return m_Tree.begin(); }
    const_iterator begin() const { return m_Tree.begin(); }
    iterator end() { return m_Tree.end(); }
    const_iterator end() const { return m_Tree.end(); }
    reverse_iterator rbegin() { return m_Tree.rbegin(); }
    const_reverse_iterator rbegin() const { return m_Tree.rbegin(); }
    reverse_iterator rend() { return m_Tree.rend(); }
    const_reverse_iterator rend() const { return m_Tree.rend(); }

    bool empty() const { return m_Tree.empty(); }
    size_type size() const { return m_Tree.size(); }
    size_type max_size() const { return m_Tree.max_size(); }

    mapped_type& operator[](const key_type& key)
    {
        return (m_Tree.add(key, mapped_type()))->value_.second;
    }

    pair<iterator, bool> insert(const value_type& val)
    {
//        iterator ret(m_Tree.add(val), &m_Tree);
//        return pair<iterator, bool>(ret, (ret->second == val.second));
    }

    iterator insert(iterator position, const value_type& val)
    {
//        return iterator(m_Tree.add(position, val), &m_Tree);
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last)
    {
//        while (first != last)
//            m_Tree.add(*first++);
    }

    void erase(iterator position)
    {
//        m_Tree.deleteKey(position->first);
    }

    size_type erase(const key_type& k)
    {
//        return m_Tree.deleteKey(k);
    }

    void erase(iterator first, iterator last)
    {
        // ? can make more efficient
//        while (first != end() && first != last &&
//               (last == end() || !comp(last->first, first->first)))
//            first = m_Tree.deleteKey(first);
    }

    void swap(map& x)
    {
//        char buffer[sizeof(map)];
//        memcpy(buffer, &x, sizeof(map));
//        memcpy(reinterpret_cast<char*>(&x), this, sizeof(map));
//        memcpy(reinterpret_cast<char*>(this), buffer, sizeof(map));
    }

    void clear()
    {
//        m_Tree.clear();
    }

    key_compare key_comp() const { return m_Tree.key_comp(); }
    value_compare value_comp() const { return value_compare(m_Tree.key_comp()); }

    iterator find(const key_type& k)
    {
//        return iterator(m_Tree.find(k), &m_Tree);
    }

    const_iterator find(const key_type& k) const
    {
//        return const_iterator(m_Tree.find(k), &m_Tree);
    }

    size_type count(const key_type& k) const
    {
//        return (m_Tree.find(k)) ? 1 : 0;
    }

    iterator lower_bound(const key_type& k)
    {
//        return iterator(m_Tree.lower_bound(k), &m_Tree);
    }

    const_iterator lower_bound(const key_type& k) const
    {
//        return iterator(m_Tree.lower_bound(k), &m_Tree);
    }

    iterator upper_bound(const key_type& k)
    {
//        return iterator(m_Tree.upper_bound(k), &m_Tree);
    }

    const_iterator upper_bound(const key_type& k) const
    {
//        return const_iterator(m_Tree.upper_bound(k), &m_Tree);
    }

    ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
    {
//        return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
    }

    ft::pair<iterator, iterator> equal_range(const key_type& k)
    {
//        return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
    }

    allocator_type get_allocator() const
    {
        return allocator_type(m_Tree.get_allocator());
    }

    friend bool operator==(const map& lhs, const map& rhs)
    {
        return lhs.m_Tree == rhs.m_Tree;
    }

    friend bool operator<(const map& lhs, const map& rhs)
    {
        return lhs.m_Tree < rhs.m_Tree;
    }
};

template <class Key, class Val, class Compare, class Alloc>
bool operator!=(const map<Key, Val, Compare, Alloc>& lhs, const map<Key, Val, Compare, Alloc>& rhs)
{
    return !(lhs == rhs);
}

template <class Key, class Val, class Compare, class Alloc>
bool operator<=(const map<Key, Val, Compare, Alloc>& lhs, const map<Key, Val, Compare, Alloc>& rhs)
{
    return !(rhs < lhs);
}

template <class Key, class Val, class Compare, class Alloc>
bool operator>(const map<Key, Val, Compare, Alloc>& lhs, const map<Key, Val, Compare, Alloc>& rhs)
{
    return rhs < lhs;
}

template <class Key, class Val, class Compare, class Alloc>
bool operator>=(const map<Key, Val, Compare, Alloc>& lhs, const map<Key, Val, Compare, Alloc>& rhs)
{
    return !(lhs < rhs);
}

template <class Key, class Val, class Compare>
void swap(ft::map<Key, Val, Compare>& a, ft::map<Key, Val, Compare>& b)
{
    a.swap(b);
}

}
