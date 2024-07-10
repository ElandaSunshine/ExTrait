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
    @file   type_container_impl.h
    @date   25, May 2024
    
    ===============================================================
 */

#pragma once

#include "../type_list.h"

#include <variant>
#include <array>



namespace extrait
{
    template<class T, index_t I, bool Reverse>
    struct TypeIteratorBase;
}

namespace extrait::detail
{
    //==================================================================================================================
    template<class T>
    struct isTypeIt : std::false_type {};
    
    template<class Array, index_t I, bool Reverse>
    struct isTypeIt<TypeIteratorBase<Array, I, Reverse>> : std::true_type {};
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, class U>
    struct isCompatibleTypeIt : std::false_type {};
    
    template<template<class, index_t, bool> class T, index_t I1, index_t I2, class Array, bool Reverse>
    struct isCompatibleTypeIt<T<Array, I1, Reverse>, T<Array, I2, Reverse>> : std::true_type {};
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, index_t I, class = void>
    struct iteratorContainer {};
    
    template<template<class...> class T, index_t I, class ...Types>
    struct iteratorContainer<T<Types...>, I, std::enable_if_t<I >= 0 && I < sizeof...(Types)>>
    {
        using type = get_t<T<Types...>, I>;
    };
    
    //==================================================================================================================
    template<class T, auto Index>
    struct deindex
    {
        static_assert(assertDep_type<T>,
                      "invalid indexing type, only extrait::index_t, "
                      "extrait::TypeIterator and extrait::ReverseTypeIterator are allowed");
    };
    
    template<auto Index>
    struct deindex<index_t, Index>
    {
         constexpr static index_t value = Index;
    };
    
    template<class T, auto Index, bool Reverse>
    struct deindex<TypeIteratorBase<T, Index, Reverse>, Index>
    {
        constexpr static index_t value = Index;
    };
    
    template<auto I>
    constexpr static index_t deindex_v = deindex<std::decay_t<decltype(I)>, I>::value;
    
    //==================================================================================================================
    template<template<class...> class T, class ...Args, class ...Types>
    constexpr inline static auto makeVariant(T<Types...>, Args &&...args)
        noexcept(noexcept(std::variant<Types...>(std::forward<Args>(args)...)))
    {
        return std::variant<Types...>(std::forward<Args>(args)...);
    }
    
    //------------------------------------------------------------------------------------------------------------------
    template<template<class...> class T, class ...Args, class ...Types>
    constexpr inline static auto makeVarArray(T<Types...>, Args &&...args)
        noexcept(noexcept(std::array<std::variant<Types...>, sizeof...(Types)> {
            std::variant<Types...>(std::in_place_type<Types>, std::forward<Args>(args)...)...
        }))
    {
        return std::array<std::variant<Types...>, sizeof...(Types)> {
            std::variant<Types...>(std::in_place_type<Types>, std::forward<Args>(args)...)...
        };
    }
    
    //------------------------------------------------------------------------------------------------------------------
    template<class Start, class Fn, std::size_t ...I>
    constexpr inline static auto forEach_helper(Start, std::index_sequence<I...>, Fn &&fn)
        noexcept(noexcept((std::forward<Fn>(fn)(typename Start::template inc<I>{}), ...)))
        -> std::enable_if_t<std::is_same_v<void, decltype(std::forward<Fn>(fn)(Start{}))>>
    {
        ((void) std::forward<Fn>(fn)(typename Start::template inc<I>{}), ...);
    }
    
    template<class Start, class Fn, std::size_t ...I>
    constexpr inline static auto forEach_helper(Start, std::index_sequence<I...>, Fn &&fn)
        noexcept(noexcept((std::forward<Fn>(fn)(typename Start::template inc<I>{}), ...)))
        -> std::enable_if_t<
            !std::is_same_v<void, decltype(std::forward<Fn>(fn)(Start{}))>,
            std::array<std::decay_t<decltype(std::forward<Fn>(fn)(Start{}))>, sizeof...(I)>
        >
    {
        return { (fn)(typename Start::template inc<I>{})... };
    }
    
    template<template<class, index_t, bool> class T, class U, index_t Start, index_t End, bool R, class Fn>
    constexpr inline static auto forEach(T<U, Start, R> start, T<U, End, R>, Fn &&fn)
         noexcept(noexcept(forEach_helper(start, std::make_index_sequence<End - Start>{}, std::forward<Fn>(fn))))
    {
        return forEach_helper(start, std::make_index_sequence<End - Start>{}, std::forward<Fn>(fn));
    }
    
    //------------------------------------------------------------------------------------------------------------------
    template<class Start, class Fn, std::size_t ...I>
    constexpr inline static auto apply_helper(Start, std::index_sequence<I...>, Fn &&fn)
        noexcept(noexcept(std::forward<Fn>(fn)(typename Start::template inc<(Start::index + I)>{}...)))
    {
        return std::forward<Fn>(fn)(typename Start::template inc<(Start::index + I)>{}...);
    }
    
    template<template<class, index_t, bool> class T, class U, index_t Start, index_t End, bool R, class Fn>
    constexpr inline static auto apply(T<U, Start, R> start, T<U, End, R>, Fn &&fn)
        noexcept(noexcept(apply_helper(start, std::make_index_sequence<End - Start>{}, std::forward<Fn>(fn))))
    {
        return apply_helper(start, std::make_index_sequence<End - Start>{}, std::forward<Fn>(fn));
    }
}
