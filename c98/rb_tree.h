#pragma once

#include <memory>

#include "iterator_traits.h"
#include "reverse_iter.h"

#include "algorithm.h"
#include "utility.h"

namespace ft
{

enum RbTreeColor
{
    RED,
    BLACK,
};

template <typename Val>
class RbTreeNode
{
public:
    typedef RbTreeNode* node_ptr;
    typedef const RbTreeNode* const_node_ptr;

public:
    RbTreeColor m_Color;
    node_ptr m_Parent;
    node_ptr m_Left;
    node_ptr m_Right;
    Val m_Value;
    bool m_IsLeft;

public:
    RbTreeNode(Val value)
        : m_Color(RbTreeColor::RED)
        , m_Parent(NULL)
        , m_Left(NULL)
        , m_Right(NULL)
        , m_Value(value)
        , m_IsLeft(true)
    {}

    RbTreeNode(const RbTreeNode& other)
        : m_Color(other.m_Color)
        , m_Parent(other.m_Parent)
        , m_Left(other.m_Left)
        , m_Right(other.m_Right)
        , m_Value(other.m_Value)
        , m_IsLeft(other.m_IsLeft)
    {}

    RbTreeNode& operator=(const RbTreeNode& other)
    {
        if (this != &other)
        {
            m_Color = other.m_Color;
            m_Parent = other.m_Parent;
            m_Left = other.m_Left;
            m_Right = other.m_Right;
            m_Value = other.m_Value;
            m_IsLeft = other.m_IsLeft;
        }
        return *this;
    }

    ~RbTreeNode() {}
};

template <typename Key, typename Val, typename Compare, typename KeyExtract, typename Alloc>
class RbTree;

template <typename Key, typename Val, typename Compare, typename KeyExtract, typename Alloc>
class RbTreeIterator
{
    typedef RbTree<Key, Val, Compare, KeyExtract, Alloc> tree_type;
public:
    typedef bidirectional_iterator_tag iterator_category;
    typedef RbTreeNode<Val> node_type;
    typedef typename node_type::node_ptr node_ptr;

    typedef Val value_type;
    typedef value_type& reference;
    typedef value_type* pointer;
    typedef ptrdiff_t difference_type;

private:
    node_ptr m_Node;
    const tree_type *m_TreePtr;

public:
    RbTreeIterator(const tree_type *tree, node_ptr node = NULL) : m_Node(node), m_TreePtr(tree) {}
    RbTreeIterator(const RbTreeIterator& other) : m_Node(other.base()), m_TreePtr(other.m_TreePtr) {}
    RbTreeIterator& operator=(const RbTreeIterator& other)
    {
        if (this != &other)
        {
            m_Node = other.base();
            m_TreePtr = other.m_TreePtr;
        }
        return *this;
    }

    RbTreeIterator& operator++()
    {
        if (m_Node == NULL)
        {
            m_Node = m_TreePtr->get_min();
        }
        else if (m_Node->m_Right)
        {
            m_Node = m_Node->m_Right;
            while (m_Node && m_Node->m_Left)
            {
                m_Node = m_Node->m_Left;
            }
        }
        else
        {
            while (m_Node && m_Node->m_Parent && !m_Node->m_IsLeft)
            {
                m_Node = m_Node->m_Parent;
            }
            m_Node = m_Node->m_Parent;
        }
        return *this;
    }
    
    RbTreeIterator operator++(int)
    {
        RbTreeIterator old(*this);
        ++(*this);
        return old;
    }

    RbTreeIterator& operator--()
    {
        if (m_Node == NULL)
        {
            m_Node = m_TreePtr->get_max();
        }
        else if (m_Node->m_Left)
        {
            m_Node = m_Node->m_Left;
            while (m_Node && m_Node->m_Right)
            {
                m_Node = m_Node->m_Right;
            }
        }
        else
        {
            while (m_Node && m_Node->m_Parent && m_Node->m_IsLeft)
            {
                m_Node = m_Node->m_Parent;
            }
            m_Node = m_Node->m_Parent;
        }
        return *this;
    }
    
    RbTreeIterator operator--(int)
    {
        RbTreeIterator old(*this);
        --(*this);
        return old;
    }
    
    reference operator*() const { return m_Node->m_Value; }
    pointer operator->() const { return &(m_Node->m_Value); }

    node_ptr base() const
    {
        return m_Node;
    }

    const tree_type *get_tree_ptr() const
    {
        return m_TreePtr;
    }
    
    friend bool operator==(const RbTreeIterator &lhs, const RbTreeIterator &rhs)
    {
        return lhs.m_Node == rhs.m_Node;
    }
    
    friend bool operator!=(const RbTreeIterator &lhs, const RbTreeIterator &rhs)
    {
        return lhs.m_Node != rhs.m_Node;
    }
};

template <typename Key, typename Val, typename Compare, typename KeyExtract, typename Alloc>
class RbTreeConstIterator
{
    typedef RbTree<Key, Val, Compare, KeyExtract, Alloc> tree_type;
public:
    typedef bidirectional_iterator_tag iterator_category;
    typedef RbTreeNode<Val> node_type;
    typedef typename node_type::const_node_ptr node_ptr;

    typedef Val value_type;
    typedef const value_type& reference;
    typedef const value_type* pointer;
    typedef ptrdiff_t difference_type;

    typedef RbTreeIterator<Key, Val, Compare, KeyExtract, Alloc> iterator;

private:
    node_ptr m_Node;
    const tree_type *m_TreePtr;

public:
    RbTreeConstIterator(const tree_type *tree, node_ptr node = NULL) : m_Node(node), m_TreePtr(tree) {}
    RbTreeConstIterator(const iterator& other) : m_Node(other.base()), m_TreePtr(other.get_tree_ptr()) {}
    RbTreeConstIterator& operator=(const iterator& other)
    {
        if (this != &other)
        {
            m_Node = other.base();
            m_TreePtr = other.m_TreePtr;
        }
        return *this;
    }

    RbTreeConstIterator& operator++()
    {
        if (m_Node == NULL)
        {
            m_Node = m_TreePtr->get_min();
        }
        else if (m_Node->m_Right)
        {
            m_Node = m_Node->m_Right;
            while (m_Node && m_Node->m_Left)
            {
                m_Node = m_Node->m_Left;
            }
        }
        else
        {
            while (m_Node && m_Node->m_Parent && !m_Node->m_IsLeft)
            {
                m_Node = m_Node->m_Parent;
            }
            m_Node = m_Node->m_Parent;
        }
        return *this;
    }

    RbTreeConstIterator operator++(int)
    {
        RbTreeConstIterator old(*this);
        ++(*this);
        return old;
    }

    RbTreeConstIterator& operator--()
    {
        if (m_Node == NULL)
        {
            m_Node = m_TreePtr->get_max();
        }
        else if (m_Node->m_Left)
        {
            m_Node = m_Node->m_Left;
            while (m_Node && m_Node->m_Right)
            {
                m_Node = m_Node->m_Right;
            }
        }
        else
        {
            while (m_Node && m_Node->m_Parent && m_Node->m_IsLeft)
            {
                m_Node = m_Node->m_Parent;
            }
            m_Node = m_Node->m_Parent;
        }
        return *this;
    }

    RbTreeConstIterator operator--(int)
    {
        RbTreeConstIterator old(*this);
        --(*this);
        return old;
    }

    reference operator*() const { return m_Node->m_Value; }
    pointer operator->() const { return &(m_Node->m_Value); }

    node_ptr base() const
    {
        return m_Node;
    }

    friend bool operator==(const RbTreeConstIterator &lhs, const RbTreeConstIterator &rhs)
    {
        return lhs.base() == rhs.base();
    }

    friend bool operator!=(const RbTreeConstIterator &lhs, const RbTreeConstIterator &rhs)
    {
        return lhs.base() != rhs.base();
    }
};

template <typename Key, typename Val, typename Compare, typename KeyExtract, typename Alloc>
inline bool operator==(
    const RbTreeIterator<Key, Val, Compare, KeyExtract, Alloc>& lhs, 
    const RbTreeConstIterator<Key, Val, Compare, KeyExtract, Alloc>& rhs)
{
    return lhs.base() == rhs.base();
}

template <typename Key, typename Val, typename Compare, typename KeyExtract, typename Alloc>
inline bool operator!=(
    const RbTreeIterator<Key, Val, Compare, KeyExtract, Alloc>& lhs, 
    const RbTreeConstIterator<Key, Val, Compare, KeyExtract, Alloc>& rhs)
{
    return lhs.base() != rhs.base();
}

template <typename Key, typename Val, typename Compare, typename KeyExtract, typename Alloc = std::allocator<Val> >
class RbTree
{
private:
    typedef Compare key_compare_type;
    typedef Alloc allocator_value_type;

    typedef RbTreeNode<Val> node_type;
    typedef typename allocator_value_type::template rebind<node_type>::other node_allocator;

public:
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef RbTreeIterator<Key, Val, Compare, KeyExtract, Alloc> iterator;
    typedef RbTreeConstIterator<Key, Val, Compare, KeyExtract, Alloc> const_iterator;
    typedef ReverseIterator<iterator> reverse_iterator;
    typedef ReverseIterator<const_iterator> const_reverse_iterator;

private:
    typename node_type::node_ptr m_Root;
    size_type m_Size;

    key_compare_type m_Comparator;
    node_allocator m_Allocator;

public:
    RbTree(const key_compare_type& comp, const allocator_value_type& alloc = allocator_value_type())
        : m_Root(NULL)
        , m_Size(0)
        , m_Comparator(comp)
        , m_Allocator(alloc)
    {}

    RbTree(const RbTree& other)
        : m_Root(NULL)
        , m_Size(other.m_Size)
        , m_Comparator(other.m_Comparator)
        , m_Allocator(other.m_Allocator)
    {
        if (other.m_Root != NULL)
        {
            m_Root = m_Allocator.allocate(1);
            m_Allocator.construct(m_Root, *other.m_Root);
            copyTree(m_Root, other.m_Root);
        }
    }

    RbTree& operator=(const RbTree& other)
    {
        if (this != &other)
        {
            if (other.m_Root != NULL)
            {
                m_Root = m_Allocator.allocate(1);
                m_Allocator.construct(m_Root, *other.m_Root);
                copyTree(m_Root, other.m_Root);
            }
            else
            {
                m_Root = other.m_Root;
            }
            m_Size = other.m_Size;
            m_Comparator = other.m_Comparator;
            m_Allocator = other.m_Allocator;
        }
        return *this;
    }

    ~RbTree()
    {
        deleteTree(m_Root);
        if (m_Root != NULL)
        {
            m_Allocator.deallocate(m_Root, m_Size);
            m_Root = NULL;
            m_Size = 0;
        }
    }

    void swap(RbTree &x)
    {
        if (&x == this)
        {
            return;
        }

        typename node_type::node_ptr root_tmp = x.m_Root;
        size_type size_tmp = x.m_Size;
        key_compare_type comparator_tmp = x.m_Comparator;
        node_allocator allocator_tmp = x.m_Allocator;

        x.m_Root = m_Root;
        x.m_Size = m_Size;
        x.m_Comparator = m_Comparator;
        x.m_Allocator = m_Allocator;

        m_Root = root_tmp;
        m_Size = size_tmp;
        m_Comparator = comparator_tmp;
        m_Allocator = allocator_tmp;
    }
    
    key_compare_type key_comp() const
    {
        return m_Comparator;
    }

    void clear()
    {
        deleteTree(m_Root);
        m_Root = NULL;
        m_Size = 0;
    }

    size_t size() const
    {
        return m_Size;
    }

    size_t max_size() const
    {
        return m_Allocator.max_size();
    }

    bool empty() const
    {
        return m_Size == 0;
    }

    typename node_type::node_ptr find(const Key& k) const
    {
        return find(m_Root, k);
    }

    typename node_type::node_ptr find(typename node_type::node_ptr node, const Key& k) const
    {
        while (node)
        {
            if (!m_Comparator(KeyExtract()(node->m_Value), k) && !m_Comparator(k, KeyExtract()(node->m_Value)))
            {
                iterator it(this, node);
                iterator next(this, node);
                for (--next; next.base() && (!m_Comparator(KeyExtract()(*next), k) && !m_Comparator(k, KeyExtract()(*next))); --next)
                {
                    --it;
                }
                return it.base();
            }
            if (!m_Comparator(KeyExtract()(node->m_Value), k))
            {
                node = node->m_Left;
            }
            else
            {
                node = node->m_Right;
            }
        }
        return NULL;
    }

    typename node_type::node_ptr lower_bound(const Key& k) const
    {
        iterator it(this, get_min());
        while (it.base() && m_Comparator(KeyExtract()(*it), k))
        {
            ++it;
        }
        return it.base();
    }

    typename node_type::node_ptr upper_bound(const Key& k) const
    {
        iterator it(this, get_min());
        while (it.base() && !m_Comparator(k, KeyExtract()(*it)))
        {
            ++it;
        }
        return it.base();
    }

    typename node_type::node_ptr add(Val toAdd)
    {
        typename node_type::node_ptr added = NULL;

        m_Root = add(NULL, m_Root, toAdd, true, &added);
        m_Root->m_Color = RbTreeColor::BLACK;
        return added;
    }

    typename node_type::node_ptr add(iterator it, Val value) { return add(it.base(), value); }
    typename node_type::node_ptr add(typename node_type::node_ptr preceding, Val value)
    {
        bool first = false;
        iterator it(this, preceding);
        while (it.base())
        {
            if (m_Comparator(KeyExtract()(value), KeyExtract()(*it)))
            {
                first = true;
                --it;
            }
            else if (m_Comparator(KeyExtract()(*it), KeyExtract()(value)))
            {
                if (first)
                    break;
                ++it;
            }
            else
            {
                typename node_type::node_ptr added = m_Allocator.allocate(1);
                {
                    m_Allocator.construct(added, value);
                    added->m_Parent = it.base()->m_Parent;
                    added->m_IsLeft = it.base()->m_IsLeft;
                }
                if (added->m_Parent)
                    added->m_IsLeft ? added->m_Parent->m_Left = added : added->m_Parent->m_Right = added;
                else
                    m_Root = added;
                added->m_Left = it.base()->m_Left;
                if (added->m_Left)
                    added->m_Left->m_Parent = added;
                it.base()->m_Left = NULL;
                it.base()->m_IsLeft = false;
                added->m_Right = it.base();
                it.base()->m_Parent = added;
                ++m_Size;
                return added;
            }
        }
        return add(value);
    }

    bool deleteKey(const Key& k)
    {
        if (!find(m_Root, k))
        {
            return false;
        }
        if (m_Size < 2)
        {
            m_Size = 0;
            m_Allocator.destroy(m_Root);
            m_Root = NULL;
            return true;
        }
        if (!isRed(m_Root->m_Left) && !isRed(m_Root->m_Right))
            m_Root->m_Color = RbTreeColor::RED;
        m_Root = deleteKey(m_Root, k);
        if (m_Root)
            m_Root->m_Color = RbTreeColor::BLACK;
        return true;
    }

    typename node_type::node_ptr deleteKey(typename node_type::node_ptr x, const Key& k)
    {
        if (m_Comparator(k, KeyExtract()(x->m_Value)))
        {
            if (!isRed(x->m_Left) && x->m_Left && !isRed(x->m_Left->m_Left))
                x = moveRedLeft(x);
            x->m_Left = deleteKey(x->m_Left, k);
        }
        else
        {
            if (isRed(x->m_Left))
                x = rotateRight(x);
            if (!m_Comparator(KeyExtract()(x->m_Value), k) && !x->m_Right)
            {
                --m_Size;
                m_Allocator.destroy(x);
                return NULL;
            }
            if (!isRed(x->m_Right) && x->m_Right && !isRed(x->m_Right->m_Left))
                x = moveRedRight(x);
            if (!m_Comparator(KeyExtract()(x->m_Value), k) && !m_Comparator(k, KeyExtract()(x->m_Value)))
            {
                typename node_type::node_ptr h = get_min(x->m_Right);
                rewrite_value(x->m_Value, h->m_Value);
                x->m_Right = deleteMin(x->m_Right);
            }
            else
                x->m_Right = deleteKey(x->m_Right, k);
        }
        return balance(x);
    }

    typename node_type::node_ptr deleteKey(iterator it) { return deleteKey(it.base()); }
    typename node_type::node_ptr deleteKey(typename node_type::node_ptr x)
    {
        typename node_type::node_ptr ret = NULL;
        if (!x)
            return x;
        if (m_Size == 1)
            m_Root = NULL;
        else if (!x->m_Right)
        {
            if (!x->m_Parent)
            {
                m_Root = x->m_Left;
                m_Root->m_Parent = NULL;
            }
            else
            {
                (x->m_IsLeft) ? x->m_Parent->m_Left = x->m_Left : x->m_Parent->m_Right = x->m_Left;
                if (x->m_Left)
                {
                    x->m_Left->m_IsLeft = x->m_IsLeft;
                    x->m_Left->m_Parent = x->m_Parent;
                }
                if (x->m_IsLeft)
                    ret = x->m_Parent;
                else
                {
                    iterator it(this, x);
                    ++it;
                    ret = it.base();
                }
            }
        }
        else
        {
            ret = eraseRight(x);
        }
        --m_Size;
        m_Allocator.destroy(x);
        return ret;
    }

    typename node_type::node_ptr eraseRight(typename node_type::node_ptr x)
    {
        typename node_type::node_ptr h = get_min(x->m_Right);

        h->m_IsLeft ? h->m_Parent->m_Left = h->m_Right : h->m_Parent->m_Right = h->m_Right;
        if (h->m_Parent->m_Left)
        {
            h->m_Parent->m_Left->m_Parent = h->m_Parent;
            h->m_Parent->m_Left->m_IsLeft = true;
        }
        if (h->m_Parent->m_Right)
            h->m_Parent->m_Right->m_Parent = h->m_Parent;
        h->m_IsLeft = x->m_IsLeft;
        h->m_Color = x->m_Color;
        h->m_Parent = x->m_Parent;
        if (!h->m_Parent)
            m_Root = h;
        else
            x->m_IsLeft ? h->m_Parent->m_Left = h : h->m_Parent->m_Right = h;
        if (x->m_Right)
        {
            h->m_Right = x->m_Right;
            h->m_Right->m_Parent = h;
        }
        h->m_Left = x->m_Left;
        h->m_Left ? h->m_Left->m_Parent = h : NULL;
        return h;
    }

    typename node_type::node_ptr get_min() const
    {
        return get_min(m_Root);
    }

    typename node_type::node_ptr get_min(typename node_type::node_ptr node) const
    {
        while (node != NULL && node->m_Left != NULL)
        {
            node = node->m_Left;
        }
        return node;
    }

    typename node_type::node_ptr get_max() const
    {
        return get_max(m_Root);
    }

    typename node_type::node_ptr get_max(typename node_type::node_ptr node) const
    {
        while (node != NULL && node->m_Right != NULL)
        {
            node = node->m_Right;
        }
        return node;
    }

private:
    typename node_type::node_ptr add(typename node_type::node_ptr parent,
                                     typename node_type::node_ptr x,
                                     Val& value,
                                     bool left,
                                     typename node_type::node_ptr *added)
    {
        if (x == NULL)
        {
            ++m_Size;
            *added = m_Allocator.allocate(1);
            m_Allocator.construct(*added, value);
            (*added)->m_Parent = parent;
            (*added)->m_IsLeft = left;
            return *added;
        }
        if (!m_Comparator(KeyExtract()(x->m_Value), KeyExtract()(value)) && !m_Comparator(KeyExtract()(value), KeyExtract()(x->m_Value)))
        {
            *added = x;
        }
        else if (!m_Comparator(KeyExtract()(value), KeyExtract()(x->m_Value)))
        {
            x->m_Right = add(x, x->m_Right, value, false, added);
        }
        else
        {
            x->m_Left = add(x, x->m_Left, value, true, added);
        }

        if (isRed(x->m_Right) && !isRed(x->m_Left))
        {
            x = rotateLeft(x);
        }
        if (isRed(x->m_Left) && isRed(x->m_Left->m_Left))
        {
            x = rotateRight(x);
        }
        if (isRed(x->m_Left) && isRed(x->m_Right))
        {
            colorFlip(x);
        }
        return x;
    }

    void deleteMin()
    {
        if (m_Root == NULL)
            return;
        if (!isRed(m_Root->m_Left && !isRed(m_Root->m_Right)))
            m_Root->m_Color = RbTreeColor::RED;
        m_Root = deleteMin(m_Root);
        if (m_Root)
            m_Root->m_Color = RbTreeColor::BLACK;
    }

    typename node_type::node_ptr deleteMin(typename node_type::node_ptr h)
    {
        if (!h->m_Left)
        {
            --m_Size;
            m_Allocator.destroy(h);
            return NULL;
        }
        if (!isRed(h->m_Left) && !isRed(h->m_Left->m_Left))
            h = moveRedLeft(h);
        h->m_Left = deleteMin(h->m_Left);
        return balance(h);
    }

    void deleteMax()
    {
        if (m_Root == NULL)
            return;
        if (!isRed(m_Root->m_Left && !isRed(m_Root->m_Right)))
            m_Root->m_Color = RbTreeColor::RED;

        m_Root = deleteMax(m_Root);
        if (m_Root)
            m_Root->m_Color = RbTreeColor::BLACK;
    }

    typename node_type::node_ptr deleteMax(typename node_type::node_ptr h)
    {
        if (isRed(h->m_Left))
            h = rotateRight(h);
        if (h->m_Right == NULL)
        {
            --m_Size;
            m_Allocator.destroy(h);
            return NULL;
        }
        if (!isRed(h->m_Right) && !isRed(h->m_Right->m_Left))
            h = moveRedRight(h->m_Right);

        h->m_Right = deleteMax(h->m_Right);
        return balance(h);
    }

    void colorFlip(typename node_type::node_ptr node)
    {
        node->m_Color = (node->m_Color == RbTreeColor::RED) ? RbTreeColor::BLACK : RbTreeColor::RED;
        node->m_Left->m_Color = (node->m_Left->m_Color == RbTreeColor::RED) ? RbTreeColor::BLACK : RbTreeColor::RED;
        node->m_Right->m_Color = (node->m_Right->m_Color == RbTreeColor::RED) ? RbTreeColor::BLACK : RbTreeColor::RED;
    }

    template <typename Type>
    typename enable_if<is_same<Type, Key>::value>::type
    rewrite_value(Type& val, Type& new_val)
    {
        val = new_val;
    }

    template <typename Type>
    typename enable_if<!is_same<Type, Key>::value>::type
    rewrite_value(Type& val, Type& new_val)
    {
        const_cast<Key&>(val.first) = new_val.first;
        val.second = new_val.second;
    }

    typename node_type::node_ptr rotateLeft(typename node_type::node_ptr h)
    {
        typename node_type::node_ptr x = h->m_Right;
        h->m_Right = x->m_Left;
        if (h->m_Right)
        {
            h->m_Right->m_Parent = h;
            h->m_Right->m_IsLeft = false;
        }
        x->m_Parent = h->m_Parent;
        x->m_IsLeft = h->m_IsLeft;
        x->m_Color = h->m_Color;
        x->m_Left = h;
        h->m_IsLeft = true;
        h->m_Parent = x;
        h->m_Color = RbTreeColor::RED;
        return x;
    }

    typename node_type::node_ptr rotateRight(typename node_type::node_ptr h)
    {
        typename node_type::node_ptr x = h->m_Left;
        h->m_Left = x->m_Right;
        if (h->m_Left)
        {
            h->m_Left->m_Parent = h;
            h->m_Left->m_IsLeft = true;
        }
        x->m_Parent = h->m_Parent;
        x->m_IsLeft = h->m_IsLeft;
        x->m_Color = h->m_Color;
        x->m_Right = h;
        h->m_IsLeft = false;
        h->m_Parent = x;
        h->m_Color = RbTreeColor::RED;
        return x;
    }

    typename node_type::node_ptr moveRedLeft(typename node_type::node_ptr h)
    {
        colorFlip(h);
        if (isRed(h->m_Right->m_Left))
        {
            h->m_Right = rotateRight(h->m_Right);
            h = rotateLeft(h);
            colorFlip(h);
        }
        return h;
    }

    typename node_type::node_ptr moveRedRight(typename node_type::node_ptr h)
    {
        colorFlip(h);
        if (isRed(h->m_Left->m_Left))
        {
            h = rotateRight(h);
            colorFlip(h);
        }
        return h;
    }

    typename node_type::node_ptr balance(typename node_type::node_ptr h)
    {
        if (isRed(h->m_Right))
            h = rotateLeft(h);
        if (isRed(h->m_Left) && isRed(h->m_Left->m_Left))
            h = rotateRight(h);
        if (isRed(h->m_Left) && isRed(h->m_Right))
            colorFlip(h);

        return h;
    }

    void deleteTree(typename node_type::node_ptr node)
    {
        if (node == NULL)
            return;
        deleteTree(node->m_Left);
        deleteTree(node->m_Right);
        m_Allocator.destroy(node);
    }

    void copyTree(typename node_type::node_ptr dest, typename node_type::node_ptr src)
    {
        if (src->m_Left)
        {
            dest->m_Left = m_Allocator.allocate(1);
            m_Allocator.construct(dest->m_Left, *src->m_Left);
            dest->m_Left->m_Parent = dest;

            copyTree(dest->m_Left, src->m_Left);
        }
        if (src->m_Right)
        {
            dest->m_Right = m_Allocator.allocate(1);
            m_Allocator.construct(dest->m_Right, *src->m_Right);
            dest->m_Right->m_Parent = dest;

            copyTree(dest->m_Right, src->m_Right);
        }
    }

    bool isRed(typename node_type::node_ptr n)
    {
        if (n == NULL)
            return false;
        return n->m_Color == RbTreeColor::RED;
    }
};

//template <typename Key, typename Val, typename Compare, typename KeyExtract, typename Alloc>
//bool operator==(const RbTree<Key, Val, Compare, KeyExtract, Alloc>& lhs, const RbTree<Key, Val, Compare, KeyExtract, Alloc>& rhs)
//{
//    return lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin());
//}
//
//template <typename Key, typename Val, typename Compare, typename KeyExtract, typename Alloc>
//bool operator!=(const RbTree<Key, Val, Compare, KeyExtract, Alloc>& lhs, const RbTree<Key, Val, Compare, KeyExtract, Alloc>& rhs)
//{
//    return !(lhs == rhs);
//}
//
//template <typename Key, typename Val, typename Compare, typename KeyExtract, typename Alloc>
//bool operator<(const RbTree<Key, Val, Compare, KeyExtract, Alloc>& lhs, const RbTree<Key, Val, Compare, KeyExtract, Alloc>& rhs)
//{
//    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
//}
//
//template <typename Key, typename Val, typename Compare, typename KeyExtract, typename Alloc>
//bool operator>(const RbTree<Key, Val, Compare, KeyExtract, Alloc>& lhs, const RbTree<Key, Val, Compare, KeyExtract, Alloc>& rhs)
//{
//    return rhs < lhs;
//}
//
//template <typename Key, typename Val, typename Compare, typename KeyExtract, typename Alloc>
//bool operator<=(const RbTree<Key, Val, Compare, KeyExtract, Alloc>& lhs, const RbTree<Key, Val, Compare, KeyExtract, Alloc>& rhs)
//{
//    return !(rhs < lhs);
//}
//
//template <typename Key, typename Val, typename Compare, typename KeyExtract, typename Alloc>
//bool operator>=(const RbTree<Key, Val, Compare, KeyExtract, Alloc>& lhs, const RbTree<Key, Val, Compare, KeyExtract, Alloc>& rhs)
//{
//    return !(lhs < rhs);
//}

}
