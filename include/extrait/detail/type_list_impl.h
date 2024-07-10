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
    @file   type_list_impl.h
    @date   20, May 2024
    
    ===============================================================
 */

#pragma once

#include "../common.h"



//======================================================================================================================
namespace extrait::detail
{
    //==================================================================================================================
    using index_t = int;
    
    //==================================================================================================================
    template<class T, index_t Start, index_t End, class ...Types>
    struct RangedList_impl;
    
    //.............
    template<template<class...> class T, index_t Start, index_t End, class ...Types, class Next, class ...TTypes>
    struct RangedList_impl<T<TTypes...>, Start, End, Next, Types...>
    {
        using type = typename RangedList_impl<T<TTypes...>, (Start - 1), (End - 1), Types...>::type;
    };
    
    template<template<class...> class T, index_t End, class ...Types, class Next, class ...TTypes>
    struct RangedList_impl<T<TTypes...>, 0, End, Next, Types...>
    {
        using type = typename RangedList_impl<T<TTypes..., Next>, 0, (End - 1), Types...>::type;
    };
    
    //.............
    template<template<class...> class T, class ...Types, class Next, class ...TTypes>
    struct RangedList_impl<T<TTypes...>, 0, 0, Next, Types...>
    {
        using type = T<TTypes...>;
    };
    
    template<template<class...> class T, class ...TTypes>
    struct RangedList_impl<T<TTypes...>, 0, 0>
    {
        using type = T<TTypes...>;
    };
    
    //------------------------------------------------------------------------------------------------------------------
    template<index_t Start, index_t End, class ...Types>
    struct RangedList
    {
        //==============================================================================================================
        static_assert(Start >= 0 && Start <= sizeof...(Types), "start index out of bounds");
        static_assert(End   >= 0 && End   <= sizeof...(Types), "end index out of bounds");
        static_assert(Start <= End, "end index can't be lower than start index");
        
        //==============================================================================================================
        using prefix = typename RangedList_impl<TypeList<>, 0,     Start,            Types...>::type;
        using range  = typename RangedList_impl<TypeList<>, Start, End,              Types...>::type;
        using suffix = typename RangedList_impl<TypeList<>, End,   sizeof...(Types), Types...>::type;
    };
    
    //==================================================================================================================
    template<class T>
    struct hasTypeList : std::false_type {};
    
    template<template<class...> class T, class ...TTypes>
    struct hasTypeList<T<TTypes...>> : std::true_type {};
    
    //==================================================================================================================
    template<class T, class U>
    struct sameClassTemplate
    {
        static_assert(assertDep_type<T, U>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, class ...TTypes, class ...UTypes>
    struct sameClassTemplate<T<TTypes...>, T<UTypes...>> : std::true_type {};
    
    template<template<class...> class T, template<class...> class U, class ...TTypes, class ...UTypes>
    struct sameClassTemplate<T<TTypes...>, U<UTypes...>> : std::false_type {};
    
    //==================================================================================================================
    template<template<class> class P, class = void>
    struct isValidPredicate : std::false_type {};
    
    template<template<class> class P>
    struct isValidPredicate<P, std::void_t<decltype(P<void*>::value)>> : std::true_type {};
    
    //==================================================================================================================
    template<template<class> class M, class = void>
    struct isValidMapper : std::false_type {};
    
    template<template<class> class M>
    struct isValidMapper<M, std::void_t<typename M<void*>::type>> : std::true_type {};
    
    //==================================================================================================================
    template<template<class, class> class C, class = void>
    struct isValidComparator : std::false_type {};
    
    template<template<class, class> class C>
    struct isValidComparator<C, std::void_t<decltype(C<void*, void*>::value)>> : std::true_type {};
    
    //==================================================================================================================
    template<class T, class = void>
    struct isEmpty_impl : std::false_type {};
    
    template<template<class...> class T, class ...TTypes>
    struct isEmpty_impl<T<TTypes...>, std::void_t<decltype(std::declval<T<>>())>>
        : std::bool_constant<std::is_same_v<T<TTypes...>, T<>>> {};
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, class = void>
    struct isEmpty
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, class ...TTypes>
    struct isEmpty<T<TTypes...>> : isEmpty_impl<T<TTypes...>> {};
    
    //==================================================================================================================
    template<class T>
    struct isEmptyInstantiated
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, class ...TTypes>
    struct isEmptyInstantiated<T<TTypes...>> : std::bool_constant<(sizeof...(TTypes) == 0)> {};
    
    template<template<class...> class T, class First, class ...TTypes>
    struct isEmptyInstantiated<T<First, TTypes...>> : std::false_type {};
    
    //==================================================================================================================
    template<class T, class Key>
    struct contains
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, class Key>
    struct contains<T<>, Key> : std::false_type {};
    
    template<template<class...> class T, class Key, class ...TTypes>
    struct contains<T<TTypes...>, Key> : std::bool_constant<(std::is_same_v<Key, TTypes> || ...)> {};
    
    //==================================================================================================================
    template<class T, class U>
    struct sameTemplateArguments
    {
        static_assert(assertDep_type<T, U>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, template<class...> class U, class ...TTypes>
    struct sameTemplateArguments<T<TTypes...>, U<TTypes...>> : std::true_type {};
    
    template<template<class...> class T, template<class...> class U, class ...TTypes, class ...UTypes>
    struct sameTemplateArguments<T<TTypes...>, U<UTypes...>> : std::false_type {};
    
    //==================================================================================================================
    template<class T, class ...StartTypes>
    struct startsWith_impl;
    
    //.............
    template<template<class...> class T, class ...StartTypes, class StartNext, class ...TTypes>
    struct startsWith_impl<T<StartNext, TTypes...>, StartNext, StartTypes...>
    {
        constexpr static bool value = startsWith_impl<T<TTypes...>, StartTypes...>::value;
    };
    
    //.............
    template<template<class...> class T, class ...TTypes>
    struct startsWith_impl<T<TTypes...>> : std::true_type {};
    
    template<template<class...> class T, class ...StartTypes, class StartNext, class ...TTypes>
    struct startsWith_impl<T<TTypes...>, StartNext, StartTypes...> : std::false_type {};
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, class ...StartTypes>
    struct startsWith
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    //.............
    template<template<class...> class T, class ...StartTypes, class ...TTypes>
    struct startsWith<T<TTypes...>, StartTypes...> : startsWith_impl<TypeList<TTypes...>, StartTypes...> {};
    
    //==================================================================================================================
    template<class T, class End>
    struct endsWith_impl;
    
    template<template<class...> class T, template<class...> class End, class ...TTypes, class ...EndTypes>
    struct endsWith_impl<T<TTypes...>, End<EndTypes...>> : startsWith_impl<T<TTypes...>, EndTypes...> {};
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, class ...EndTypes>
    struct endsWith
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<class T> struct reverse;
    
    template<template<class...> class T, class ...EndTypes, class ...TTypes>
    struct endsWith<T<TTypes...>, EndTypes...>
        : endsWith_impl<
            typename reverse<TypeList<TTypes...>>::type,
            typename reverse<TypeList<EndTypes...>>::type
        > {};
    
    //==================================================================================================================
    template<template<class> class P, bool Invert, class ...Types>
    struct match_impl;
    
    template<template<class> class P, bool Invert, class Next, class ...Types>
    struct match_impl<P, Invert, Next, Types...>
        : std::integral_constant<
            std::size_t,
            (static_cast<std::size_t>(P<Next>::value != Invert) + match_impl<P, Invert, Types...>::value)
        > {};
    
    template<template<class> class P, bool Invert>
    struct match_impl<P, Invert> : std::integral_constant<std::size_t, 0> {};
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, template<class> class P, bool Invert>
    struct match
    {
        static_assert(isValidPredicate<P>::value, "invalid predicate type");
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, template<class> class P, bool Invert, class ...TTypes>
    struct match<T<TTypes...>, P, Invert> : match_impl<P, Invert, TTypes...>
    {
        static_assert(isValidPredicate<P>::value, "invalid predicate type");
    };
    
    //==================================================================================================================
    template<template<class> class P, class ...Types>
    struct matchAny_impl;
    
    template<template<class> class P, class Next, class ...Types>
    struct matchAny_impl<P, Next, Types...>
        : std::bool_constant<(P<Next>::value || matchAny_impl<P, Types...>::value)> {};
    
    template<template<class> class P>
    struct matchAny_impl<P> : std::false_type {};
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, template<class> class P>
    struct matchAny
    {
        static_assert(isValidPredicate<P>::value, "invalid predicate type");
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, template<class> class P, class ...TTypes>
    struct matchAny<T<TTypes...>, P> : matchAny_impl<P, TTypes...>
    {
        static_assert(isValidPredicate<P>::value, "invalid predicate type");
    };
    
    //==================================================================================================================
    template<class Key, index_t I, class ...Types>
    struct indexOf_impl;
    
    //.............
    template<class Key, index_t I, class ...Types, class Next>
    struct indexOf_impl<Key, I, Next, Types...>
    {
        constexpr static index_t value = indexOf_impl<Key, (I + 1), Types...>::value;
    };
    
    //.............
    template<class Key, index_t I, class ...Types>
    struct indexOf_impl<Key, I, Key, Types...> : std::integral_constant<index_t, I> {};
    
    template<class Key, index_t I>
    struct indexOf_impl<Key, I> : std::integral_constant<index_t, -1> {};
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, class Key>
    struct indexOf
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, class Key, class ...TTypes>
    struct indexOf<T<TTypes...>, Key> : indexOf_impl<Key, 0, TTypes...> {};
    
    //==================================================================================================================
    template<class Key, index_t I, index_t Found, class ...Types>
    struct lastIndexOf_impl;
    
    //.............
    template<class Key, index_t I, index_t Found, class ...Types, class Next>
    struct lastIndexOf_impl<Key, I, Found, Next, Types...>
    {
        constexpr static index_t value = lastIndexOf_impl<Key, (I + 1), Found, Types...>::value;
    };
    
    template<class Key, index_t I, index_t Found, class ...Types>
    struct lastIndexOf_impl<Key, I, Found, Key, Types...>
    {
        constexpr static index_t value = lastIndexOf_impl<Key, (I + 1), I, Types...>::value;
    };
    
    //.............
    template<class Key, index_t I, index_t Found>
    struct lastIndexOf_impl<Key, I, Found> : std::integral_constant<index_t, Found> {};
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, class Key>
    struct lastIndexOf
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, class Key, class ...TTypes>
    struct lastIndexOf<T<TTypes...>, Key> : lastIndexOf_impl<Key, 0, -1, TTypes...> {};
    
    //==================================================================================================================
    template<class T>
    struct length
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, class ...TTypes>
    struct length<T<TTypes...>> : std::integral_constant<std::size_t, sizeof...(TTypes)> {};
    
    //==================================================================================================================
    template<class T, class ...U>
    struct join_impl;
    
    //.............
    template<template<class...> class T, class ...U, class Next, class ...TTypes>
    struct join_impl<T<TTypes...>, Next, U...>
    {
        static_assert(assertDep_type<Next>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, class ...U, template<class...> class Next, class ...TTypes, class ...NTypes>
    struct join_impl<T<TTypes...>, Next<NTypes...>, U...>
    {
        using type = typename join_impl<T<TTypes..., NTypes...>, U...>::type;
    };
    
    //.............
    template<template<class...> class T, class ...TTypes>
    struct join_impl<T<TTypes...>>
    {
        using type = T<TTypes...>;
    };
    
    //------------------------------------------------------------------------------------------------------------------
    template<template<class...> class T, class ...U>
    struct join
    {
        using type = typename join_impl<T<>, U...>::type;
    };
    
    //==================================================================================================================
    template<template<class...> class T, class U, class ...Types>
    struct reverse_impl;
    
    //.............
    template<template<class...> class T, template<class...> class U, class ...Types, class Next, class ...UTypes>
    struct reverse_impl<T, U<UTypes...>, Next, Types...>
    {
        using type = typename reverse_impl<T, U<Next, UTypes...>, Types...>::type;
    };
    
    //.............
    template<template<class...> class T, template<class...> class U, class ...UTypes>
    struct reverse_impl<T, U<UTypes...>>
    {
        using type = T<UTypes...>;
    };
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T>
    struct reverse
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, class ...TTypes>
    struct reverse<T<TTypes...>>
    {
        using type = typename reverse_impl<T, TypeList<>, TTypes...>::type;
    };
    
    
    //==================================================================================================================
    template<class T, index_t Start, index_t End>
    struct sublist
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, index_t Start, index_t End, class ...TTypes>
    struct sublist<T<TTypes...>, Start, End>
    {
        using type = typename RangedList<Start, End, TTypes...>::range::template to<T>;
    };
    
    //==================================================================================================================
    template<index_t I, class ...Types>
    struct get_impl;
    
    //.............
    template<index_t I, class Next, class ...Types>
    struct get_impl<I, Next, Types...>
    {
        using type = typename get_impl<(I - 1), Types...>::type;
    };
    
    //.............
    template<class Next, class ...Types>
    struct get_impl<0, Next, Types...>
    {
        using type = Next;
    };
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, index_t I>
    struct get
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, index_t I, class ...TTypes>
    struct get<T<TTypes...>, I>
    {
        static_assert(sizeof...(TTypes) > 0, "cannot get type argument from empty parameter-list");
        static_assert(I >= 0 && I < sizeof...(TTypes), "index out of bounds");
        
        using type = typename get_impl<I, TTypes...>::type;
    };
    
    //==================================================================================================================
    template<class Key, class T, class U, class ...Types>
    struct replace_impl;
    
    //.............
    template<class Key, template<class...> class T, template<class...> class U, class ...Types,
             class Next, class ...TTypes, class ...UTypes>
    struct replace_impl<Key, T<TTypes...>, U<UTypes...>, Next, Types...>
    {
        using type = typename replace_impl<Key, T<TTypes..., Next>, U<UTypes...>, Types...>::type;
    };
    
    //.............
    template<class Key, template<class...> class T, template<class...> class U, class ...Types,
             class ...TTypes, class ...UTypes>
    struct replace_impl<Key, T<TTypes...>, U<UTypes...>, Key, Types...>
    {
        using type = T<TTypes..., UTypes..., Types...>;
    };
    
    template<class Key, template<class...> class T, template<class...> class U, class ...TTypes, class ...UTypes>
    struct replace_impl<Key, T<TTypes...>, U<UTypes...>>
    {
        using type = T<TTypes...>;
    };
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, class Key, class ...Repl>
    struct replace
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };

    template<template<class...> class T, class Key, class ...Repl, class ...TTypes>
    struct replace<T<TTypes...>, Key, Repl...>
    {
        static_assert(sizeof...(Repl) > 0, "no replacement types given");
        using type = typename replace_impl<Key, TypeList<>, TypeList<Repl...>, TTypes...>::type::template to<T>;
    };
    
    //==================================================================================================================
    template<class Key, class T, class U, class ...Types>
    struct replaceAll_impl;
    
    //.............
    template<class Key, template<class...> class T, template<class...> class U, class ...Types,
             class Next, class ...TTypes, class ...UTypes>
    struct replaceAll_impl<Key, T<TTypes...>, U<UTypes...>, Next, Types...>
    {
        using type = typename replaceAll_impl<Key, T<TTypes..., Next>, U<UTypes...>, Types...>::type;
    };
    
    template<class Key, template<class...> class T, template<class...> class U, class ...Types,
             class ...TTypes, class ...UTypes>
    struct replaceAll_impl<Key, T<TTypes...>, U<UTypes...>, Key, Types...>
    {
        using type = typename replaceAll_impl<Key, T<TTypes..., UTypes...>, U<UTypes...>, Types...>::type;
    };
    
    //.............
    template<class Key, template<class...> class T, template<class...> class U, class ...TTypes, class ...UTypes>
    struct replaceAll_impl<Key, T<TTypes...>, U<UTypes...>>
    {
        using type = T<TTypes...>;
    };
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, class Key, class ...Repl>
    struct replaceAll
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, class Key, class ...Repl, class ...TTypes>
    struct replaceAll<T<TTypes...>, Key, Repl...>
    {
        static_assert(sizeof...(Repl) > 0, "no replacement types given");
        using type = typename replaceAll_impl<Key, TypeList<>, TypeList<Repl...>, TTypes...>::type::template to<T>;
    };
    
    //==================================================================================================================
    template<index_t I, class T, class U, class ...Types>
    struct replaceAt_impl;
    
    //.............
    template<index_t I, template<class...> class T, template<class...> class U, class ...Types,
             class Next, class ...TTypes, class ...UTypes>
    struct replaceAt_impl<I, T<TTypes...>, U<UTypes...>, Next, Types...>
    {
        using type = typename replaceAt_impl<(I - 1), T<TTypes..., Next>, U<UTypes...>, Types...>::type;
    };
    
    //.............
    template<template<class...> class T, template<class...> class U, class ...Types,
             class Next, class ...TTypes, class ...UTypes>
    struct replaceAt_impl<0, T<TTypes...>, U<UTypes...>, Next, Types...>
    {
        using type = T<TTypes..., UTypes..., Types...>;
    };
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, index_t I, class ...Repl>
    struct replaceAt
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, index_t I, class ...Repl, class ...TTypes>
    struct replaceAt<T<TTypes...>, I, Repl...>
    {
        static_assert(sizeof...(Repl) > 0, "no replacement types given");
        static_assert(I >= 0 && I < sizeof...(TTypes), "index out of bounds");
        
        using type = typename replaceAt_impl<I, TypeList<>, TypeList<Repl...>, TTypes...>::type::template to<T>;
    };
    
    //==================================================================================================================
    template<class T, index_t Start, index_t End, class ...Repl>
    struct replaceRange
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, index_t Start, index_t End, class ...Repl, class ...TTypes>
    struct replaceRange<T<TTypes...>, Start, End, Repl...>
    {
    private:
        using range = RangedList<Start, End, TTypes...>;
        
    public:
        static_assert(sizeof...(Repl) > 0, "no replacement types given");
        using type = typename join<T, typename range::prefix, TypeList<Repl...>, typename range::suffix>::type;
    };
    
    //==================================================================================================================
    template<template<class> class P, class T, class U, index_t I, bool Invert, class ...Types>
    struct replaceIf_impl;
    
    //.............
    template<template<class> class P, template<class ...> class T, template<class ...> class U, index_t I, bool Invert,
             class ...Types, class Next, class ...TTypes, class ...UTypes>
    struct replaceIf_impl<P, T<TTypes...>, U<UTypes...>, I, Invert, Next, Types...>
    {
        using type = typename replaceIf_impl<
            P,
            std::conditional_t<
                P<Next>::value != Invert,
                T<TTypes..., UTypes...>,
                T<TTypes..., Next>
            >,
            U<UTypes...>,
            (I + 1),
            Invert,
            Types...
        >::type;
    };
    
    //.............
    template<template<class> class P, template<class ...> class T, template<class ...> class U, index_t I, bool Invert,
             class ...TTypes, class ...UTypes>
    struct replaceIf_impl<P, T<TTypes...>, U<UTypes...>, I, Invert>
    {
        using type = T<TTypes...>;
    };
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, template<class> class P, bool Invert, class ...Repl>
    struct replaceIf
    {
        static_assert(isValidPredicate<P>::value, "invalid predicate type");
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, template<class> class P, bool Invert, class ...Repl, class ...TTypes>
    struct replaceIf<T<TTypes...>, P, Invert, Repl...>
    {
        static_assert(isValidPredicate<P>::value, "invalid predicate type");
        static_assert(sizeof...(Repl) > 0, "no replacement types given");
        
        using type = typename replaceIf_impl<
            P,
            TypeList<>,
            TypeList<Repl...>,
            0,
            Invert,
            TTypes...
        >::type::template to<T>;
    };
    
    //==================================================================================================================
    template<class T, class Key>
    struct remove
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    //.............
    template<template<class ...> class T, class Key, class ...TTypes>
    struct remove<T<TTypes...>, Key>
    {
        using type = typename replace_impl<Key, TypeList<>, TypeList<>, TTypes...>::type::template to<T>;
    };
    
    //==================================================================================================================
    template<class T, class Key>
    struct removeAll
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    //.............
    template<template<class ...> class T, class Key, class ...TTypes>
    struct removeAll<T<TTypes...>, Key>
    {
        using type = typename replaceAll_impl<Key, TypeList<>, TypeList<>, TTypes...>::type::template to<T>;
    };
    
    //==================================================================================================================
    template<class T, index_t I>
    struct removeAt
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    //.............
    template<template<class ...> class T, index_t I, class ...TTypes>
    struct removeAt<T<TTypes...>, I>
    {
        static_assert(I >= 0 && I < sizeof...(TTypes), "index out of bounds");
        using type = typename replaceAt_impl<I, TypeList<>, TypeList<>, TTypes...>::type::template to<T>;
    };
    
    //==================================================================================================================
    template<class T, index_t Start, index_t End>
    struct removeRange
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, index_t Start, index_t End, class ...TTypes>
    struct removeRange<T<TTypes...>, Start, End>
    {
    private:
        using range = RangedList<Start, End, TTypes...>;
        
    public:
        using type = typename join<T, typename range::prefix, typename range::suffix>::type;
    };
    
    //==================================================================================================================
    template<class T, template<class> class P, bool Invert>
    struct removeIf
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, template<class> class P, bool Invert, class ...TTypes>
    struct removeIf<T<TTypes...>, P, Invert>
    {
        using type = typename replaceIf_impl<P, TypeList<>, TypeList<>, 0, Invert, TTypes...>::type::template to<T>;
    };
    
    //==================================================================================================================
    template<class T, class ...Add>
    struct addIfAbsent_impl;
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T>
    struct deduplicate
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, class ...TTypes>
    struct deduplicate<T<TTypes...>>
    {
        using type = typename addIfAbsent_impl<TypeList<>, TTypes...>::type::template to<T>;
    };
    
    //==================================================================================================================
    template<class T, class ...Add>
    struct add
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, class ...Add, class ...TTypes>
    struct add<T<TTypes...>, Add...>
    {
        static_assert(sizeof...(Add) > 0, "need at least one type to add");
        using type = T<TTypes..., Add...>;
    };
    
    //==================================================================================================================
    template<class T, class ...Add>
    struct addIfAbsent_impl;
    
    //.............
    template<template<class...> class T, class ...Add, class Next, class ...TTypes>
    struct addIfAbsent_impl<T<TTypes...>, Next, Add...>
    {
        using type = typename addIfAbsent_impl<
            std::conditional_t<
                contains<T<TTypes...>, Next>::value,
                    T<TTypes...>,
                    T<TTypes..., Next>
            >,
            Add...
        >::type;
    };
    
    //.............
    template<template<class...> class T, class ...TTypes>
    struct addIfAbsent_impl<T<TTypes...>>
    {
        using type = T<TTypes...>;
    };
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, class ...Add>
    struct addIfAbsent
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, class ...Add, class ...TTypes>
    struct addIfAbsent<T<TTypes...>, Add...>
    {
        static_assert(sizeof...(Add) > 0, "need at least one type to add");
        using type = typename addIfAbsent_impl<TypeList<TTypes...>, Add...>::type::template to<T>;
    };
    
    //==================================================================================================================
    template<class T, index_t I, class ...Add>
    struct insert
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, index_t I, class ...Add, class ...TTypes>
    struct insert<T<TTypes...>, I, Add...>
    {
    private:
        using range = RangedList<I, I, TTypes...>;
    
    public:
        static_assert(sizeof...(Add) > 0, "need at least one type to insert");
        using type = typename join<T, typename range::prefix, TypeList<Add...>, typename range::suffix>::type;
    };
    
    // Simpler if we insert at the end
    template<template<class...> class T, class ...Add, class ...TTypes>
    struct insert<T<TTypes...>, sizeof...(TTypes), Add...>
    {
        static_assert(sizeof...(Add) > 0, "need at least one type to insert");
        using type = T<TTypes..., Add...>;
    };
    
    // Better if we insert at the start
    template<template<class...> class T, class ...Add, class ...TTypes>
    struct insert<T<TTypes...>, 0, Add...>
    {
        static_assert(sizeof...(Add) > 0, "need at least one type to insert");
        using type = T<Add..., TTypes...>;
    };
    
    template<template<class...> class T, class ...Add>
    struct insert<T<>, 0, Add...>
    {
        static_assert(sizeof...(Add) > 0, "need at least one type to insert");
        using type = T<Add...>;
    };
    
    //==================================================================================================================
    template<class T, index_t I, index_t End>
    struct rotate_impl;
    
    //.............
    template<template<class...> class T, index_t I, index_t End, class Next, class ...TTypes>
    struct rotate_impl<T<Next, TTypes...>, I, End>
    {
        using type = typename rotate_impl<T<TTypes..., Next>, (I - 1), End>::type;
    };
    
    //.............
    template<template<class...> class T, index_t End, class Next, class ...TTypes>
    struct rotate_impl<T<Next, TTypes...>, 0, End>
    {
        using type = T<Next, TTypes...>;
    };
    
    template<template<class...> class T, index_t End, class Next, class ...TTypes>
    struct rotate_impl<T<Next, TTypes...>, End, End>
    {
        using type = T<Next, TTypes...>;
    };
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, index_t Start, index_t Middle, index_t End>
    struct rotate
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, index_t Start, index_t Middle, index_t End, class ...TTypes>
    struct rotate<T<TTypes...>, Start, Middle, End>
    {
    private:
        static_assert(Middle >= Start && Middle <= End, "middle index out of range");
        using range = RangedList<Start, End, TTypes...>;
        
    public:
        using type = typename join<
            T,
            typename range::prefix,
            typename rotate_impl<typename range::range, (Middle - Start), (End - Start)>::type,
            typename range::suffix
        >::type;
    };
    
    template<template<class...> class T, index_t Start, class ...TTypes>
    struct rotate<T<TTypes...>, Start, Start, Start>
    {
        using type = T<TTypes...>;
    };
    
    //==================================================================================================================
    template<class T, index_t I, index_t Dest, bool RotateLeft>
    struct move_impl;
    
    template<class T, index_t I, index_t Dest>
    struct move_impl<T, I, Dest, true>
    {
        static_assert(I >= 0 && I < length<T>::value, "index out of bounds");
        static_assert(Dest >= 0 && Dest < length<T>::value, "index out of bounds");
        
        using type = typename rotate<T, Dest, I, (I + 1)>::type;
    };
    
    template<class T, index_t I, index_t Dest>
    struct move_impl<T, I, Dest, false>
    {
        static_assert(I >= 0 && I < length<T>::value, "index out of bounds");
        static_assert(Dest >= 0 && Dest < length<T>::value, "index out of bounds");
        
        using type = typename rotate<T, I, (I + 1), (Dest + 1)>::type;
    };
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, index_t I, index_t Dest>
    struct move
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, index_t I, index_t Dest, class ...TTypes>
    struct move<T<TTypes...>, I, Dest>
    {
        using type = typename move_impl<TypeList<TTypes...>, I, Dest, (I > Dest)>::type::template to<T>;
    };
    
    //==================================================================================================================
    template<class T, index_t I, index_t Dest>
    struct swap
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, index_t I, index_t Dest, class ...TTypes>
    struct swap<T<TTypes...>, I, Dest>
    {
    private:
        using IndexType = typename get<T<TTypes...>, I>::type;
        using DestType  = typename get<T<TTypes...>, Dest> ::type;
        
    public:
        using type = typename replaceAt<
            typename replaceAt<T<TTypes...>, I, DestType>::type,
            Dest,
            IndexType
        >::type;
    };
    
    //==================================================================================================================
    template<class T, template<class> class M>
    struct map
    {
        static_assert(isValidMapper<M>::value, "invalid mapper type");
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, template<class> class M, class ...TTypes>
    struct map<T<TTypes...>, M>
    {
        static_assert(isValidMapper<M>::value, "invalid mapper type");
        using type = T<typename M<TTypes>::type...>;
    };
    
    //==================================================================================================================
    template<class T, class Key, template<class, class> class C, index_t I>
    struct sort_compareAndInsert;
    
    template<template<class...> class T, class Key, template<class, class> class C, index_t I, class ...TTypes>
    struct sort_compareAndInsert<T<TTypes...>, Key, C, I>
    {
        using Arg = typename get<T<TTypes...>, I>::type;
        using type = std::conditional_t<
            C<Arg, Key>::value,
                typename sort_compareAndInsert<T<TTypes...>, Key, C, (I - 1)>::type,
                typename insert<T<TTypes...>, (I + 1), Key>::type
        >;
    };
    
    template<template<class...> class T, class Key, template<class, class> class Cmp, class ...TTypes>
    struct sort_compareAndInsert<T<TTypes...>, Key, Cmp, -1>
    {
        using type = T<Key, TTypes...>;
    };
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, index_t I, template<class, class> class C, class ...Types>
    struct sort_impl;
    
    template<template<class...> class T, index_t I, template<class, class> class C, class ...Types, class Next,
             class ...TTypes>
    struct sort_impl<T<TTypes...>, I, C, Next, Types...>
    {
        using type = typename sort_impl<
            typename sort_compareAndInsert<T<TTypes...>, Next, C, (I - 1)>::type,
            (I + 1),
            C,
            Types...
        >::type;
    };
    
    template<template<class...> class T, index_t I, template<class, class> class C, class ...TTypes>
    struct sort_impl<T<TTypes...>, I, C>
    {
        using type = T<TTypes...>;
    };
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, template<class, class> class C>
    struct sort
    {
        static_assert(isValidComparator<C>::value, "invalid comparator type");
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, template<class, class> class C, class ...TTypes>
    struct sort<T<TTypes...>, C>
    {
        static_assert(isValidComparator<C>::value, "invalid comparator type");
        using type = typename sort_impl<TypeList<>, 0, C, TTypes...>::type::template to<T>;
    };
    
    //==================================================================================================================
    template<template<class, class> class C, bool Invert, class Key, class ...Types>
    struct minmax_impl;
    
    template<template<class, class> class C, bool Invert, class Key, class Next, class ...Types>
    struct minmax_impl<C, Invert, Key, Next, Types...>
    {
        using type = typename minmax_impl<
            C,
            Invert,
            std::conditional_t<
                ((C<Next, Key>::value) != Invert),
                    Next,
                    Key
            >,
            Types...
        >::type;
    };
    
    template<template<class, class> class C, bool Invert, class Key>
    struct minmax_impl<C, Invert, Key>
    {
        using type = Key;
    };
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, template<class, class> class C, bool Invert>
    struct minmax
    {
        static_assert(isValidComparator<C>::value, "invalid comparator type");
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, template<class, class> class C, bool Invert, class ...TTypes>
    struct minmax<T<TTypes...>, C, Invert>
    {
        static_assert(isValidComparator<C>::value, "invalid comparator type");
        static_assert(sizeof...(TTypes) > 0, "no types to compare given");
        
        using type = typename minmax_impl<C, Invert, TTypes...>::type;
    };
    
    //==================================================================================================================
    template<class T, template<class...> class U>
    struct convert
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, template<class...> class U, class ...TTypes>
    struct convert<T<TTypes...>, U>
    {
        using type = U<TTypes...>;
    };
    
    //==================================================================================================================
    template<class T, class ...Types>
    struct reinstantiate
    {
        static_assert(assertDep_type<T>, "invalid type, must be a class template with a type only parameter-list");
    };
    
    template<template<class...> class T, class ...Types, class ...TTypes>
    struct reinstantiate<T<TTypes...>, Types...>
    {
        using type = T<Types...>;
    };
}
