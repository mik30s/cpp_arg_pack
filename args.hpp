#pragma once

#ifndef ARGS_HPP
#define ARGS_HPP

#include <type_traits>

namespace arg_pack {

template<unsigned int n>
struct Args
{
    template<typename First, typename... Rest>
    constexpr auto operator() (First first_arg, Rest... other_args)
    {
        return Args<n-1>{}(other_args...);
    }
};

// handle zero case
template<>
struct Args<0>
{
    template<typename First, typename... Rest>
    constexpr auto operator() (First first_arg, Rest...)
    {
        return first_arg; // just return the first argument
    }
};

template<typename... Elem>
struct ArgsValueHolder{};

template<typename FirstElem, typename... Elem>
struct ArgsValueHolder : public ArgsValueHolder<Elem...>
{
private:
    FirstElem tail;
public:
    ArgsValueHolder(FirstElem first, Elem...rest)
        :ArgsHolder(rest...), tail(first){}
};

template<typename T>
struct ArgsTypeHolder
{
    using type = T;
};

// sepcializations
template<typename T, typename... Ts>
struct ArgsTypeHolder<0, ArgsValueHolder<T, Ts...>>
{
    using type = T;
};


// sepcializations
template<unsigned size, typename T, typename... Ts>
struct ArgsTypeHolder<size, ArgsValueHolder<T, Ts...>>
{
    using type = decltype(ArgsTypeHolder<size - 1, ArgsValueHolder<T, Ts...>>::type);
};


}

template<unsigned n>
using arg_in = arg_pack::Args<n>;


#endif // ARGS_HPP
