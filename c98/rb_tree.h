#pragma once

#include <memory>

#include "iterator_traits.h"

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
        , m_Parent(0)
        , m_Left(0)
        , m_Right(0)
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

    static node_ptr next_node(node_ptr node)
    {
        if (node == NULL)
        {
            node = RbTreeNode::get_min(node);
        }
        else if (node->m_Right)
        {
            node = node->m_Right;
            while (node && node->m_Left)
            {
                node = node->m_Left;
            }
        }
        else
        {
            while (node && node->m_Parent && !node->m_IsLeft)
            {
                node = node->m_Parent;
            }
            node = node->m_Parent;
        }
        return node;
    }

    static node_ptr prev_node(node_ptr node)
    {
        if (node == NULL)
        {
            node = RbTreeNode::get_max(node);
        }
        else if (node->m_Left)
        {
            node = node->m_Left;
            while (node && node->m_Right)
            {
                node = node->m_Right;
            }
        }
        else
        {
            while (node && node->m_Parent && node->m_IsLeft)
            {
                node = node->m_Parent;
            }
            node = node->m_Parent;
        }
        return node;
    }

private:
    static node_ptr get_min(node_ptr node)
    {
        while (node != 0 && node->left != 0)
        {
            node = node->left;
        }
        return node;
    }

//    static const_node_ptr get_min(const_node_ptr node)
//    {
//        while (node != 0 && node->left != 0)
//        {
//            node = node->left;
//        }
//        return node;
//    }

    static node_ptr get_max(node_ptr node)
    {
        while (node != 0 && node->right != 0)
        {
            node = node->right;
        }
        return node;
    }

//    static const_node_ptr get_max(const_node_ptr node)
//    {
//        while (node != 0 && node->right != 0)
//        {
//            node = node->right;
//        }
//        return node;
//    }
};

template <typename Val, bool IsConst>
class RbTreeIterator
{
public:
    typedef bidirectional_iterator_tag iterator_category;
    typedef typename iterator_traits<RbTreeIterator>::difference_type difference_type;
    typedef RbTreeNode<Val> node_type;
    typedef typename node_type::node_ptr node_ptr;
    
    typedef Val value_type;
    typedef value_type& reference;
    typedef value_type* pointer;

private:
    node_ptr m_Node;

public:
    RbTreeIterator(node_ptr node = NULL) : m_Node(node) {}
    RbTreeIterator(const RbTreeIterator& other) : m_Node(other.m_Node) {}
    RbTreeIterator& operator=(const RbTreeIterator& other)
    {
        if (this != &other)
        {
            m_Node = other.m_Node;
        }
        return *this;
    }

    RbTreeIterator& operator++()
    {
        m_Node = node_type::next_node(m_Node);
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
        m_Node = node_type::prev_node(m_Node);
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
    
    friend bool operator==(const RbTreeIterator &lhs, const RbTreeIterator &rhs)
    {
        return lhs.m_Node == rhs.m_Node;
    }
    
    friend bool operator!=(const RbTreeIterator &lhs, const RbTreeIterator &rhs)
    {
        return lhs.m_Node != rhs.m_Node;
    }
};

template <typename Key, typename Val, typename Compare, typename KeyExtract, typename Alloc = std::allocator<Val> >
class RbTree
{
private:
    typedef Compare key_compare;
    typedef Alloc allocator_value_type;

    typedef RbTreeNode<Val> node_type;
    typedef typename allocator_value_type::template rebind<node_type>::other node_allocator;

public:
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef RbTreeIterator<Val> iterator;
    typedef RbTreeIterator<const Val> const_iterator; /// TODO ???

private:
    typename node_type::node_ptr m_Root;
    size_type m_Size;

    key_compare m_Comparator;
    node_allocator m_Allocator;

public:
    RbTree(const key_compare& comp, const allocator_value_type& alloc = allocator_value_type())
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
            m_Allocator.allocate(m_Root, other.m_Root);
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
                m_Allocator.allocate(m_Root, other.m_Root);
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
        deleteTree();
        m_Allocator.deallocate(m_Root, m_Size);
        m_Root = NULL;
        m_Size = 0;
    }

    void swap(RbTree &x)
    {
        char buffer[sizeof(RbTree)];
        memcpy(buffer, &x, sizeof(RbTree));
        memcpy(reinterpret_cast<char *>(&x), this, sizeof(RbTree));
        memcpy(reinterpret_cast<char *>(this), buffer, sizeof(RbTree));
    }

    void clear()
    {
        deleteTree(m_Root);
        m_Root = 0;
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

    typename node_type::node_ptr find(const Key& k) const
    {
        return find(m_Root, k);
    }

    typename node_type::node_ptr find(typename node_type::node_ptr node, const Key& k) const
    {
        while (node)
        {
            if (!m_Comparator(KeyExtract(node->m_Value), k) && !m_Comparator(k, KeyExtract(node->m_Value)))
            {
                iterator it(node, this);
                iterator next(node, this);
                for (--next; next.m_Node && (!m_Comparator(KeyExtract(*next), k) && !m_Comparator(k, KeyExtract(*next))); --next)
                    --it;
                return it.m_Node;
            }
            if (!m_Comparator(KeyExtract(node->m_Value), k))
                node = node->m_Left;
            else
                node = node->m_Right;
        }
        return nullptr;
    }

    typename node_type::node_ptr lower_bound(const Key& k) const
    {
        iterator it(min(), this);
        while (it.m_Node && m_Comparator(KeyExtract(*it), k))
            ++it;
        return it.m_Node;
    }

    typename node_type::node_ptr upper_bound(const Key& k) const
    {
        iterator it(min(), this);
        while (it.m_Node && !m_Comparator(k, KeyExtract(*it)))
            ++it;
        return it.m_Node;
    }

    size_type count(const Key& k) const
    {
        size_type count = 0;

//        for (RbTreeIterator<Val, Compare> it(find(m_Root, k), this);
//             it.m_Node && !m_Comparator(KeyExtract(*it), k) && !m_Comparator(k, KeyExtract(*it)); ++it)
//            ++count;
        return count;
    }

    typename node_type::node_ptr add(Val toAdd)
    {
        typename node_type::node_ptr added;  // sending address to this pointer so that I can select it even with the recursive

        m_Root = add(NULL, m_Root, toAdd, true, &added);
        m_Root->m_Color = RbTreeColor::BLACK;
        return added;
    }

    typename node_type::node_ptr add(iterator it, Val value) { return add(it.m_Node, value); }
    typename node_type::node_ptr add(typename node_type::node_ptr preceding, Val value)
    {
        bool first = false;
        iterator it(preceding, this);
        while (it.m_Node)
        {
            if (m_Comparator(KeyExtract(value), KeyExtract(*it)))
            {  // --> value < it
                first = true;
                --it;
            }
            else if (m_Comparator(KeyExtract(*it), KeyExtract(value)))
            {  // --> value > it
                if (first)
                    break;
                ++it;
            }
            else
            {
                typename node_type::node_ptr added = m_Allocator.allocate(1);
                {
//                    added = new node_type(value, it.m_Node->m_Parent, it.m_Node->m_IsLeft);
                    m_Allocator.construct(added, value);
                    added->m_Parent = it.m_Node->m_Parent;
                    added->m_IsLeft = it.m_Node->m_IsLeft
                }
                if (added->m_Parent)
                    added->m_IsLeft ? added->m_Parent->m_Left = added : added->m_Parent->m_Right = added;
                else
                    m_Root = added;
                added->m_Left = it.m_Node->m_Left;
                if (added->m_Left)
                    added->m_Left->m_Parent = added;
                it.m_Node->m_Left = 0;
                it.m_Node->m_IsLeft = false;
                added->m_Right = it.m_Node;
                it.m_Node->m_Parent = added;
                ++m_Size;
                return added;
            }
        }
        return add(value);
    }

    bool deleteKey(Key& k)
    {
        if (!find(m_Root, k))
        {
            return false;
        }
        if (m_Size < 2)
        {
            m_Size = 0;
            m_Allocator.destroy(m_Root);
//            delete m_Root;
            m_Root = nullptr;
            return true;
        }
        if (!isRed(m_Root->m_Left) && !isRed(m_Root->m_Right))
            m_Root->m_Color = RbTreeColor::RED;
        m_Root = deleteKey(m_Root, k);
        if (m_Root)
            m_Root->m_Color = RbTreeColor::BLACK;
        return true;
    }

    typename node_type::node_ptr deleteKey(typename node_type::node_ptr x, Key& k)
    {
        if (m_Comparator(k, KeyExtract(x->m_Value)))
        {
            if (!isRed(x->m_Left) && x->m_Left && !isRed(x->m_Left->m_Left))
                x = moveRedLeft(x);
            x->m_Left = deleteKey(x->m_Left, k);
        }
        else
        {
            if (isRed(x->m_Left))
                x = rotateRight(x);
            if (!m_Comparator(KeyExtract(x->m_Value), k) && !x->m_Right)
            {  // EQUAL
                --m_Size;
                m_Allocator.destroy(x);
//                delete x;
                return 0;
            }
            if (!isRed(x->m_Right) && x->m_Right && !isRed(x->m_Right->m_Left))
                x = moveRedRight(x);
            if (!m_Comparator(KeyExtract(x->m_Value), k) && !m_Comparator(k, KeyExtract(x->m_Value)))
            {
                typename node_type::node_ptr h = min(x->m_Right);
                x->m_Value = h->m_Value;
                x->m_Right = deleteMin(x->m_Right);
            }
            else
                x->m_Right = deleteKey(x->m_Right, k);
        }
        return balance(x);
    }

    typename node_type::node_ptr deleteKey(iterator it) { return deleteKey(it.m_Node); }
    typename node_type::node_ptr deleteKey(typename node_type::node_ptr x)
    {
        typename node_type::node_ptr ret = 0;
        if (!x)
            return x;
        if (m_Size == 1)
            m_Root = 0;
        else if (!x->m_Right)
        {
            if (!x->m_Parent)
            {
                m_Root = x->m_Left;
                m_Root->m_Parent = 0;
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
                    iterator it(x, this);
                    ++it;
                    ret = it.m_Node;
                }
            }
        }
        else
            ret = eraseRight(x);
        --m_Size;
        m_Allocator.destroy(x);
//        delete x;
        return ret;
    }

    typename node_type::node_ptr eraseRight(typename node_type::node_ptr x)
    {
        typename node_type::node_ptr h = min(x->m_Right);

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
        {  // x->right wasn't h or it was but h had a right child
            h->m_Right = x->m_Right;
            h->m_Right->m_Parent = h;
        }
        h->m_Left = x->m_Left;
        h->m_Left ? h->m_Left->m_Parent = h : 0;
        return h;
    }

private:
    typename node_type::node_ptr add(typename node_type::node_ptr parent,
                                     typename node_type::node_ptr x,
                                     Val& value,
                                     bool left,
                                     typename node_type::node_ptr *added)
    {
        if (x == 0)
        {
            ++m_Size;
            *added = m_Allocator.allocate(1);
//            *added = new node_type(value, parent, left);
            m_Allocator.construct(*added, value);
            (*added)->m_Parent = parent;
            (*added)->m_IsLeft = left;
            return *added;
        }
        if (!m_Comparator(KeyExtract(x->m_Value), KeyExtract(value)) && !m_Comparator(KeyExtract(value), KeyExtract(x->m_Value))/* && allowMulti == false*/)	// ---> EQUAL
            *added = x;
        else if (!m_Comparator(KeyExtract(value), KeyExtract(x->m_Value)))
            x->m_Right = add(x, x->m_Right, value, false, added);
        else
            x->m_Left = add(x, x->m_Left, value, true, added);  // if comp gives false

        if (isRed(x->m_Right) && !isRed(x->m_Left))
            x = rotateLeft(x);
        if (isRed(x->m_Left) && isRed(x->m_Left->m_Left))
            x = rotateRight(x);
        if (isRed(x->m_Left) && isRed(x->m_Right))
            colorFlip(x);
        return x;
    }

    void deleteMin()
    {
        if (m_Root == 0)
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
            // std::cout << "delete no left child "  << h->m_Value << std::endl;
            --m_Size;
            m_Allocator.destroy(h);
//            delete h;
            return 0;
        }
        if (!isRed(h->m_Left) && !isRed(h->m_Left->m_Left))
            h = moveRedLeft(h);
        h->m_Left = deleteMin(h->m_Left);
        return balance(h);
    }

    void deleteMax()
    {
        // if (m_Root == 0) throw
        if (m_Root == 0)
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
        if (h->m_Right == 0)
        {
            --m_Size;
            m_Allocator.destroy(h);
//            delete h;
            return 0;
        }
        if (!isRed(h->m_Right) && !isRed(h->m_Right->m_Left))
            h = moveRedRight(h->m_Right);

        h->m_Right = deleteMax(h->m_Right);
        return balance(h);
    }

    void colorFlip(typename node_type::node_ptr node)
    {
        node->m_Color = !node->m_Color;
        node->m_Left->m_Color = !node->m_Left->m_Color;
        node->m_Right->m_Color = !node->m_Right->m_Color;
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
        if (node == 0)
            return;
        deleteTree(node->m_Left);
        deleteTree(node->m_Right);
        m_Allocator.destroy(node);
//        delete node;
    }

    void copyTree(typename node_type::node_ptr dest, typename node_type::node_ptr src)
    {
        if (src->m_Left)
        {
            dest->m_Left = m_Allocator.allocate(1);
//          dest->m_Left = new node_type(*src->m_Left, dest);
            m_Allocator.construct(dest->m_Left, *src->m_Left);
            dest->m_Left->m_Parent = dest;

            copyTree(dest->m_Left, src->m_Left);
        }
        if (src->m_Right)
        {
            dest->m_Right = m_Allocator.allocate(1);
//            dest->m_Right = new node_type(*src->m_Right, dest);
            m_Allocator.construct(dest->m_Right, *src->m_Right);
            dest->m_Right->m_Parent = dest;

            copyTree(dest->m_Right, src->m_Right);
        }
    }

    size_t heigth()
    {
        if (!m_Root)
            return 0;
        return height(m_Root) - 1;
    }

    size_t heigth(typename node_type::node_ptr node)
    {
        if (node == 0)
            return 0;
        size_t left = height(node->m_Left);
        size_t right = height(node->m_Right);
        if (left > right)
            return left + 1;
        return right + 1;
    }
};

}
