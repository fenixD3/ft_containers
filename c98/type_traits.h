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
    typedef bool_constant<Val> type;
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

}
