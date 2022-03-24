#pragma once

namespace ft
{

template <bool, typename ReturnType = void>
struct enable_if {};

template <typename ReturnType>
struct enable_if<true, ReturnType>
{
    typedef ReturnType type;
};

template <bool Val>
struct bool_constant
{
    typedef bool_constant<Val> type; /// TODO why?
    static const bool value = Val;
};

typedef bool_constant<true> true_type;
typedef bool_constant<false> false_type;

template <typename LeftType, typename RightType>
struct is_same : false_type
{};

template <typename Type>
struct is_same<Type, Type> : true_type
{};

template <typename T>
struct add_rvalue_reference
{
    typedef T&& type;
};

template <>
struct add_rvalue_reference<void>
{
    typedef void type;
};

template <>
struct add_rvalue_reference<const void>
{
    typedef const void type;
};

template <>
struct add_rvalue_reference<volatile void>
{
    typedef volatile void type;
};

template <>
struct add_rvalue_reference<const volatile void>
{
    typedef volatile void type;
};

template <typename T>
struct remove_const
{
    typedef T type;
};

template <typename T>
struct remove_const<const T>
{
    typedef T type;
};

template <typename T>
struct remove_volatile
{
    typedef T type;
};

template <typename T>
struct remove_volatile<volatile T>
{
    typedef T type;
};

template <typename T>
struct remove_cv : remove_volatile<typename remove_const<T>::type> /// metafunction forwarding!!!
{};

template <typename T>
typename add_rvalue_reference<T>::type declval();

template <typename From, typename To>
struct is_convertible_helper
{
private:
    static void aux(To);

    template <typename F, typename = decltype(aux(declval<F>()))>
    static true_type dummy(void*);

    template <typename, typename>
    static false_type dummy(...);

public:
    typedef decltype(dummy<From>(NULL)) type;
    static const bool value = type::value; /// in standard realization this variable isn't
};

template <typename From, typename To>
struct is_convertible : is_convertible_helper<From, To>
{};

template <typename>
struct is_integral_helper : false_type
{};

template <>
struct is_integral_helper<bool> : true_type
{};

template <>
struct is_integral_helper<char> : true_type
{};

template <>
struct is_integral_helper<char16_t> : true_type
{};

template <>
struct is_integral_helper<char32_t> : true_type
{};

template <>
struct is_integral_helper<wchar_t> : true_type
{};

template <>
struct is_integral_helper<short> : true_type
{};

template <>
struct is_integral_helper<int> : true_type
{};

template <>
struct is_integral_helper<long> : true_type
{};

template <>
struct is_integral_helper<long long> : true_type
{};

template <typename T>
struct is_integral : is_integral_helper<typename remove_cv<T>::type>
{};

template <bool Cond, typename True, typename False>
struct conditional;

template <typename True, typename False>
struct conditional<true, True, False>
{
    typedef True type;
};

template <typename True, typename False>
struct conditional<false, True, False>
{
    typedef False type;
};

}
