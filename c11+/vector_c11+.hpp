#pragma once

namespace ft
{

template <typename TType, typename TAllocator = std::allocator<TType>>
class vector
{
public:
    using value_type = TType;
    using allocator_type = TAllocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<TAllocator>::pointer;
    using const_pointer = typename std::allocator_traits<TAllocator>::const_pointer;
//    using iterator = ;
//    using const_iterator = ;
//    using reverse_iterator = ;
//    using const_reverse_iterator = ;
};

}
