/**
    
    
    ++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--
    -                      __.....__                                              .--.                             +
    +                  .-''         '.                                            |__|                             -
    -                 /     .-''"'-.  `.                     .|  .-,.--.          .--.     .|                      +
    +                /     /________\   \ ____     _____   .' |_ |  .-. |    __   |  |   .' |_                     -
    -                |                  |`.   \  .'    / .'     || |  | | .:--.'. |  | .'     |                    +
    +                \    .-------------'  `.  `'    .' '--.  .-'| |  | |/ |   \ ||  |'--.  .-'                    -
    -                 \    '-.____...---.    '.    .'      |  |  | |  '- `" __ | ||  |   |  |                      +
    +                  `.             .'     .'     `.     |  |  | |      .'.''| ||__|   |  |                      -
    -                    `''-...... -'     .'  .'`.   `.   |  '.'| |     / /   | |_      |  '.'                    +
    +                                    .'   /    `.   `. |   / |_|     \ \._,\ '/      |   /                     -
    -                                   '----'       '----'`'-'           `--'  `"       `'-'                      +
    ++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--
    
    
    
    MIT License
    
    Copyright (c) 2024 ElandaSunshine
    
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
    
    ===============================================================
    
    @author Elanda
    @file   common_impl.h
    @date   20, May 2024
    
    ===============================================================
 */

#pragma once

#include <string_view>



namespace extrait
{
    template<class ...T>
    extern const bool assertDep_type;
    
    template<auto ...V>
    extern const bool assertDep_value;
}

namespace extrait::detail
{
    //==================================================================================================================
    template<class ...Types>
    struct TypeList
    {
        template<template<class...> class T>
        using to = T<Types...>;
    };
    
    //==================================================================================================================
    template<class T>         struct strip                      { using type = T;                       };
    template<class T>         struct strip<const T>             { using type = typename strip<T>::type; };
    template<class T>         struct strip<volatile T>          { using type = typename strip<T>::type; };
    template<class T>         struct strip<const volatile T>    { using type = typename strip<T>::type; };
    template<class T>         struct strip<T&>                  { using type = typename strip<T>::type; };
    template<class T>         struct strip<const T&>            { using type = typename strip<T>::type; };
    template<class T>         struct strip<volatile T&>         { using type = typename strip<T>::type; };
    template<class T>         struct strip<const volatile T&>   { using type = typename strip<T>::type; };
    template<class T>         struct strip<T&&>                 { using type = typename strip<T>::type; };
    template<class T>         struct strip<const T&&>           { using type = typename strip<T>::type; };
    template<class T>         struct strip<volatile T&&>        { using type = typename strip<T>::type; };
    template<class T>         struct strip<const volatile T&&>  { using type = typename strip<T>::type; };
    template<class T>         struct strip<T*>                  { using type = typename strip<T>::type; };
    template<class T>         struct strip<T*const>             { using type = typename strip<T>::type; };
    template<class T>         struct strip<T*volatile>          { using type = typename strip<T>::type; };
    template<class T>         struct strip<T*const volatile>    { using type = typename strip<T>::type; };
    template<class T>         struct strip<T[]>                 { using type = typename strip<T>::type; };
    template<class T>         struct strip<const T[]>           { using type = typename strip<T>::type; };
    template<class T>         struct strip<volatile T[]>        { using type = typename strip<T>::type; };
    template<class T>         struct strip<const volatile T[]>  { using type = typename strip<T>::type; };
    template<class T, auto N> struct strip<T[N]>                { using type = typename strip<T>::type; };
    template<class T, auto N> struct strip<const T[N]>          { using type = typename strip<T>::type; };
    template<class T, auto N> struct strip<volatile T[N]>       { using type = typename strip<T>::type; };
    template<class T, auto N> struct strip<const volatile T[N]> { using type = typename strip<T>::type; };
    
    template<class R, class ...P> struct strip<R(*)(P...)>          { using type = R(P...); };
    template<class R, class ...P> struct strip<R(*)(P...) noexcept> { using type = R(P...) noexcept; };
    
    template<class R, class ...P, class T> struct strip<R(T::*)(P...)>
    { using type = R(P...); };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) const>
    { using type = R(P...) const; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) volatile>
    { using type = R(P...) volatile; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) const volatile>
    { using type = R(P...) const volatile; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) &>
    { using type = R(P...) &; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) const&>
    { using type = R(P...) const&; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) volatile&>
    { using type = R(P...) volatile&; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) const volatile&>
    { using type = R(P...) const volatile&; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) &&>
    { using type = R(P...) &&; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) const&&>
    { using type = R(P...) const&&; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) volatile&&>
    { using type = R(P...) volatile&&; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) const volatile&&>
    { using type = R(P...) const volatile&&; };
    
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) noexcept>
    { using type = R(P...) noexcept; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) const noexcept>
    { using type = R(P...) const noexcept; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) volatile noexcept>
    { using type = R(P...) volatile noexcept; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) const volatile noexcept>
    { using type = R(P...) const volatile noexcept; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) & noexcept>
    { using type = R(P...) & noexcept; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) const& noexcept>
    { using type = R(P...) const& noexcept; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) volatile& noexcept>
    { using type = R(P...) volatile& noexcept; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) const volatile& noexcept>
    { using type = R(P...) const volatile& noexcept; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) && noexcept>
    { using type = R(P...) && noexcept; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) const&& noexcept>
    { using type = R(P...) const&& noexcept; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) volatile&& noexcept>
    { using type = R(P...) volatile&& noexcept; };
    template<class R, class ...P, class T> struct strip<R(T::*)(P...) const volatile&& noexcept>
    { using type = R(P...) const volatile&& noexcept; };
    
    template<class R, class T> struct strip<R T::*> { using type = typename strip<R>::type; };
    
    //==================================================================================================================
    template<class T, class ...Branches>
    struct select_impl
    {
        static_assert(sizeof...(Branches) != 0, "no branches were specified");
    };
    
    template<class T, template<class, template<class> class> class Branch, class U, template<class> class Trait,
             class ...Branches>
    struct select_impl<T, Branch<U, Trait>, Branches...>
    {
        using type = std::conditional_t<
            Trait<T>::value,
                U,
                typename select_impl<T, Branches...>::type
        >;
    };
    
    template<class T, class U, class ...Branches>
    struct select_impl<T, U, Branches...>
    {
        static_assert(sizeof...(Branches) == 0,
            "a fallback branch must come after all other branches have already occurred");
        using type = U;
    };

    //------------------------------------------------------------------------------------------------------------------
    template<class ...Branches>
    struct select
    {
        template<class T>
        using type = typename select_impl<T, Branches...>::type;
    };
    
    //==================================================================================================================
    template<class T, class U, class ...Branches>
    struct assemble_impl;
    
    //.............
    template<template<class...> class T, class U, template<class, template<class> class> class Branch,
            class ...Branches, class V, template<class> class Trait, class ...TTypes>
    struct assemble_impl<T<TTypes...>, U, Branch<V, Trait>, Branches...>
    {
        using type = std::conditional_t<
            Trait<U>::value,
                typename assemble_impl<T<TTypes..., V>, U, Branches...>::type,
                typename assemble_impl<T<TTypes...>, U, Branches...>::type
        >;
    };
    
    template<template<class...> class T, class U, class ...Branches, class Next, class ...TTypes>
    struct assemble_impl<T<TTypes...>, U, Next, Branches...>
    {
        using type = typename assemble_impl<T<TTypes..., Next>, U, Branches...>::type;
    };
    
    //.............
    template<template<class...> class T, class U, class ...TTypes>
    struct assemble_impl<T<TTypes...>, U>
    {
        using type = T<TTypes...>;
    };
    
    //------------------------------------------------------------------------------------------------------------------
    template<template<class...> class T, class ...Branches>
    struct assemble
    {
        template<class U>
        using type = typename assemble_impl<TypeList<>, U, Branches...>::type::template to<T>;
    };
    
    //------------------------------------------------------------------------------------------------------------------
    enum class TNPos { END };

#if defined(__GNUG__) || defined(__clang__)
    template<class TypeNameType, TNPos extrait_TnPOS = TNPos::END>
    [[nodiscard]]
    constexpr inline std::string_view getActualTypeName() noexcept
    {
        const std::string_view signature = __PRETTY_FUNCTION__;
        
        const std::size_t pos    = signature.find('=', signature.find("TypeNameType")) + 1;
        std::string_view  result = signature.substr(pos);
        
        #ifdef __clang__
            const std::size_t npos = result.rfind(',', result.find("extrait_TnPOS"));
        #else
            const std::size_t npos = result.rfind(';', result.find("extrait_TnPOS"));
        #endif
        result = result.substr(0, npos);
        
        result.remove_prefix(result.find_first_not_of("\n\t\r "));
        result = result.substr(0, result.find_last_not_of("\n\t\r ") + 1);
        
        return { result.data(), result.length() };
    }
#else
    template<class, TNPos = TNPos::END>
    [[nodiscard]]
    constexpr inline std::string_view getActualTypeName() noexcept
    {
        const std::string_view signature = __FUNCSIG__;
        const std::string_view funcname  = __FUNCTION__;
        
        const std::size_t pos    = signature.find_first_of('<', signature.find(funcname)) + 1;
        std::string_view  result = signature.substr(pos);
        
        const std::size_t npos = result.rfind(',', result.find("extrait::detail::TNPos::END"));
        result = result.substr(0, npos);
        
        result.remove_prefix(result.find_first_not_of("\n\t\r "));
        result = result.substr(0, result.find_last_not_of("\n\t\r ") + 1);
        
        return { result.data(), result.length() };
    }
#endif
}
