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
    @file   type_container.h
    @date   09, May 2024
    
    ===============================================================
 */

#pragma once

#include "detail/type_container_impl.h"



namespace extrait
{
    //==================================================================================================================
    /**
     *  @brief A pseudo-iterator for TypeArray that deals with iteration based on template aliases.
     *  
     *  Every instantiation of this class template represents a positional interface for any given TypeArray,
     *  providing a set of utilities for the represented type as well as an interface to easily switch back and forth
     *  between any type in the associated TypeArray.
     *  
     *  Every iterator instantiation comes with the basic index (the type it currently "points to") and an alias for
     *  the associated TypeArray. Thus, every instantiation is unique for each unique TypeArray instantiation and
     *  the corresponding index representing the position.
     *  
     *  This interface also allows certain helpers in TypeArray to be used with this instead of a plain index_t.
     *  
     *  This class can also be object-instantiated, which can provide a useful helper utility when passing them across
     *  functions. Functions like forEach() and forAll() require such an instance.
     *  
     *  A specialisation of this class is provided for the case Index == Array::length, at which point helper alias
     *  "type" is no longer provided (no type exists past the end), for these cases it might be helpful to bounds-check
     *  any usage of said alias.
     *  
     *  If index is out of bounds of the associated TypeArray (except one past the end), compilation will fail.  
     *  Compilation will also fail if Array is not a valid TypeArray type.
     *  
     *  @tparam Array The TypeArray the iterator is associated with
     *  @tparam Index The current index inside the type array, if left default instantiated, index will be 0
     *  
     *  @see extrait::ReverseTypeIterator
     *  @see extrait::TypeArray
     *  @see extrait::forEach()
     *  @see extrait::forAll()
     */
    
    template<template<class...> class T, index_t I, bool Reverse, class ...Types>
    struct TypeIteratorBase<T<Types...>, I, Reverse>
        : detail::iteratorContainer<T<Types...>, I>
    {
        static_assert(I >= 0 && I <= sizeof...(Types), "iterator index out of bounds");
        
        //--------------------------------------------------------------------------------------------------------------
        using Array = T<Types...>;
        
        //--------------------------------------------------------------------------------------------------------------
        constexpr static index_t index = I;
        
        //--------------------------------------------------------------------------------------------------------------
        template<class Other, std::enable_if_t<detail::isCompatibleTypeIt<TypeIteratorBase, Other>::value>* = nullptr>
        constexpr static bool isEqual = (index == Other::index);
        
        template<class Other, std::enable_if_t<detail::isCompatibleTypeIt<TypeIteratorBase, Other>::value>* = nullptr>
        constexpr static bool isNotEqual = (index != Other::index);
        
        template<class Other, std::enable_if_t<detail::isCompatibleTypeIt<TypeIteratorBase, Other>::value>* = nullptr>
        constexpr static bool isLessThan = (index < Other::index);
        
        template<class Other, std::enable_if_t<detail::isCompatibleTypeIt<TypeIteratorBase, Other>::value>* = nullptr>
        constexpr static bool isLessThanOrEqual = (index <= Other::index);
        
        template<class Other, std::enable_if_t<detail::isCompatibleTypeIt<TypeIteratorBase, Other>::value>* = nullptr>
        constexpr static bool isGreaterThan = (index > Other::index);
        
        template<class Other, std::enable_if_t<detail::isCompatibleTypeIt<TypeIteratorBase, Other>::value>* = nullptr>
        constexpr static bool isGreaterThanOrEqual = (index >= Other::index);
        
        //--------------------------------------------------------------------------------------------------------------
        template<index_t J = index, std::enable_if_t<(J >= 0 && J < sizeof...(Types))>* = nullptr>
        using next = TypeIteratorBase<Array, (J + 1), Reverse>;
        
        template<index_t J = index, std::enable_if_t<(J > 0 && J <= sizeof...(Types))>* = nullptr>
        using prev = TypeIteratorBase<Array, (J - 1), Reverse>;
        
        template<index_t N>
        using inc = TypeIteratorBase<Array, (index + N), Reverse>;
        
        template<index_t N>
        using dec = TypeIteratorBase<Array, (index - N), Reverse>;
        
        template<index_t J>
        using with = TypeIteratorBase<Array, J, Reverse>;
    };
    
    template<class T, index_t I>
    using TypeIterator = TypeIteratorBase<T, I, false>;
    
    template<class T, index_t I>
    using ReverseTypeIterator = TypeIteratorBase<T, I, true>;
    
    //------------------------------------------------------------------------------------------------------------------
    template<class ...Types>
    struct TypeArray
    {
        //==============================================================================================================
        using begin_t  = TypeIterator<TypeArray, 0>;
        
        using end_t = TypeIterator<TypeArray, sizeof...(Types)>;
        
        using rbegin_t = ReverseTypeIterator<TypeArray, 0>;
        
        using rend_t = ReverseTypeIterator<TypeArray, sizeof...(Types)>;
        
        //--------------------------------------------------------------------------------------------------------------
        template<class Other>
        constexpr static bool equals = std::is_same_v<TypeArray, Other>;
        
        template<class Other>
        constexpr static bool sameTypeList = sameTemplateArguments_v<TypeArray, Other>;
        
        template<class Key>
        constexpr static bool contains = contains_v<TypeArray, Key>;
        
        constexpr static bool isEmpty = false;

        template<class ...Keys>
        constexpr static bool startsWith = startsWith_v<TypeArray, Keys...>;
        
        template<class ...Keys>
        constexpr static bool endsWith = endsWith_v<TypeArray, Keys...>;
        
        template<template<class> class Predicate>
        constexpr static std::size_t match = match_v<TypeArray, Predicate>;
        
        template<template<class> class Predicate>
        constexpr static std::size_t mismatch = match_v<TypeArray, Predicate>;
        
        template<template<class> class Predicate>
        constexpr static bool matchAny = matchAny_v<TypeArray, Predicate>;
        
        template<template<class> class Predicate>
        constexpr static bool matchAll = matchAll_v<TypeArray, Predicate>;
        
        template<template<class> class Predicate>
        constexpr static bool matchNone = matchNone_v<TypeArray, Predicate>;
        
        //--------------------------------------------------------------------------------------------------------------
        template<class T>
        constexpr static index_t indexOf = indexOf_v<TypeArray, T>;
        
        template<class T>
        constexpr static index_t lastIndexOf = lastIndexOf_v<TypeArray, T>;
        
        constexpr static std::size_t length = sizeof...(Types);
        
        //--------------------------------------------------------------------------------------------------------------
        template<template<class...> class T>
        using to = T<Types...>;
        
        using toVariant = to<std::variant>;
        
        template<std::size_t N>
        using toVarArray = std::array<toVariant, N>;
        
        template<class ...Others>
        using join = join_t<TypeArray, TypeArray, Others...>;
        
        using reverse = reverse_t<TypeArray>;
        
        using clear = TypeArray<>;
        
        //--------------------------------------------------------------------------------------------------------------
        template<auto Index>
        using get = get_t<TypeArray, detail::deindex_v<Index>>;
        
        using front = first_t<TypeArray>;
        
        using back = last_t<TypeArray>;
        
        //--------------------------------------------------------------------------------------------------------------
        template<class ...Add>
        using add = TypeArray<Types..., Add...>;
        
        template<class ...Prepend>
        using prepend = TypeArray<Prepend..., Types...>;
        
        template<class ...Add>
        using addIfAbsent = addIfAbsent_t<TypeArray, Add...>;
        
        template<auto Index, class ...Insertions>
        using insert = insert_t<TypeArray, detail::deindex_v<Index>, Insertions...>;
        
        using deduplicate = deduplicate_t<TypeArray>;
        
        //--------------------------------------------------------------------------------------------------------------
        template<class Key>
        using remove = remove_t<TypeArray, Key>;
        
        template<class Key>
        using removeAll = removeAll_t<TypeArray, Key>;
        
        using removeFirst = removeFirst_t<TypeArray>;
        
        using removeLast = removeLast_t<TypeArray>;
        
        template<auto Index>
        using removeAt = removeAt_t<TypeArray, detail::deindex_v<Index>>;
        
        template<auto Start, auto End>
        using removeRange = removeRange_t<TypeArray, detail::deindex_v<Start>, detail::deindex_v<End>>;
        
        template<template<class> class Predicate>
        using removeIf = removeIf_t<TypeArray, Predicate>;
        
        template<template<class> class Predicate>
        using filter = filter_t<TypeArray, Predicate>;
        
        //--------------------------------------------------------------------------------------------------------------        
        template<class Key, class ...Replacement>
        using replace = replace_t<TypeArray, Key, Replacement...>;
        
        template<class Key, class ...Replacement>
        using replaceAll = replaceAll_t<TypeArray, Key, Replacement...>;
        
        template<class ...Replacement>
        using replaceFirst = replaceFirst_t<TypeArray, Replacement...>;
        
        template<class ...Replacement>
        using replaceLast = replaceLast_t<TypeArray, Replacement...>;
        
        template<auto Index, class ...Replacement>
        using replaceAt = replaceAt_t<TypeArray, detail::deindex_v<Index>, Replacement...>;
        
        template<auto Start, auto End, class ...Replacement>
        using replaceRange = replaceRange_t<TypeArray, detail::deindex_v<Start>, detail::deindex_v<End>, Replacement...>;
        
        template<template<class> class Predicate, class ...Replacement>
        using replaceIf = replaceIf_t<TypeArray, Predicate, Replacement...>;
        
        template<template<class> class Predicate, class ...Replacement>
        using replaceIfNot = replaceIfNot_t<TypeArray, Predicate, Replacement...>;
        
        //--------------------------------------------------------------------------------------------------------------
        template<auto Start, auto End>
        using subarray = sublist_t<TypeArray, detail::deindex_v<Start>, detail::deindex_v<End>>;
        
        //--------------------------------------------------------------------------------------------------------------
        template<auto Index, auto Dest>
        using move = move_t<TypeArray, detail::deindex_v<Index>, detail::deindex_v<Dest>>;
        
        template<auto Index1, auto Index2>
        using swap = swap_t<TypeArray, detail::deindex_v<Index1>, detail::deindex_v<Index2>>;
        
        template<auto Start, auto Middle, auto End>
        using rotate = rotate_t<TypeArray, detail::deindex_v<Start>, detail::deindex_v<Middle>, detail::deindex_v<End>>;
        
        template<template<class, class> class Comparator>
        using sort = sort_t<TypeArray, Comparator>;
        
        template<template<class> class Mapper>
        using map = map_t<TypeArray, Mapper>;
        
        //--------------------------------------------------------------------------------------------------------------
        constexpr static auto begin = begin_t{};
        
        constexpr static auto end = end_t{};
        
        constexpr static auto rbegin = rbegin_t{};
        
        constexpr static auto rend = rend_t{};
    };
    
    template<>
    struct TypeArray<>
    {
        //==============================================================================================================
        using begin_t = TypeIterator<TypeArray, 0>;
        
        using end_t = TypeIterator<TypeArray, 0>;
        
        using rbegin_t = ReverseTypeIterator<TypeArray, 0>;
        
        using rend_t = ReverseTypeIterator<TypeArray, 0>;
        
        //--------------------------------------------------------------------------------------------------------------
        template<class Other>
        constexpr static bool equals = std::is_same_v<TypeArray, Other>;
        
        template<class Other>
        constexpr static bool sameTypeList = sameTemplateArguments_v<TypeArray, Other>;
        
        template<class Key>
        constexpr static bool contains = false;
        
        constexpr static bool isEmpty = true;

        template<class ...Keys>
        constexpr static bool startsWith = startsWith_v<TypeArray, Keys...>;
        
        template<class ...Keys>
        constexpr static bool endsWith = endsWith_v<TypeArray, Keys...>;
        
        template<template<class> class Predicate>
        constexpr static std::size_t match = match_v<TypeArray, Predicate>;
        
        template<template<class> class Predicate>
        constexpr static std::size_t mismatch = match_v<TypeArray, Predicate>;
        
        template<template<class> class Predicate>
        constexpr static bool matchAny = matchAny_v<TypeArray, Predicate>;
        
        template<template<class> class Predicate>
        constexpr static bool matchAll = matchAll_v<TypeArray, Predicate>;
        
        template<template<class> class Predicate>
        constexpr static bool matchNone = matchNone_v<TypeArray, Predicate>;
        
        //--------------------------------------------------------------------------------------------------------------
        template<class T>
        constexpr static index_t indexOf = endOfTypeList;
        
        template<class T>
        constexpr static index_t lastIndexOf = endOfTypeList;
        
        constexpr static std::size_t size = 0;
        
        //--------------------------------------------------------------------------------------------------------------
        template<template<class...> class T>
        using to = T<>;
        
        using toVariant = std::variant<std::monostate>;
        
        template<std::size_t N>
        using toVarArray = std::array<toVariant, N>;
        
        template<class ...Others>
        using join = join_t<TypeArray, Others...>;
        
        using reverse = TypeArray;
        
        using clear = TypeArray;
        
        //--------------------------------------------------------------------------------------------------------------
        template<auto Index>
        using get = get_t<TypeArray, detail::deindex_v<Index>>;
        
        //--------------------------------------------------------------------------------------------------------------
        template<class ...Add>
        using add = TypeArray<Add...>;
        
        template<class ...Prepend>
        using prepend = TypeArray<Prepend...>;
        
        template<class ...Add>
        using addIfAbsent = addIfAbsent_t<TypeArray, Add...>;
        
        template<auto Index, class ...Insertions>
        using insert = insert_t<TypeArray, detail::deindex_v<Index>, Insertions...>;
        
        using deduplicate = deduplicate_t<TypeArray>;
        
        //--------------------------------------------------------------------------------------------------------------
        template<class Key>
        using remove = remove_t<TypeArray, Key>;
        
        template<class Key>
        using removeAll = removeAll_t<TypeArray, Key>;
        
        template<auto Index>
        using removeAt = removeAt_t<TypeArray, detail::deindex_v<Index>>;
        
        template<auto Start, auto End>
        using removeRange = removeRange_t<TypeArray, detail::deindex_v<Start>, detail::deindex_v<End>>;
        
        template<template<class> class Predicate>
        using removeIf = removeIf_t<TypeArray, Predicate>;
        
        template<template<class> class Predicate>
        using filter = filter_t<TypeArray, Predicate>;
        
        //--------------------------------------------------------------------------------------------------------------        
        template<class Key, class ...Replacement>
        using replace = replace_t<TypeArray, Key, Replacement...>;
        
        template<class Key, class ...Replacement>
        using replaceAll = replaceAll_t<TypeArray, Key, Replacement...>;
        
        template<auto Index, class ...Replacement>
        using replaceAt = replaceAt_t<TypeArray, detail::deindex_v<Index>, Replacement...>;
        
        template<auto Start, auto End, class ...Replacement>
        using replaceRange = replaceRange_t<TypeArray, detail::deindex_v<Start>, detail::deindex_v<End>, Replacement...>;
        
        template<template<class> class Predicate, class ...Replacement>
        using replaceIf = replaceIf_t<TypeArray, Predicate, Replacement...>;
        
        template<template<class> class Predicate, class ...Replacement>
        using replaceIfNot = replaceIfNot_t<TypeArray, Predicate, Replacement...>;
        
        //--------------------------------------------------------------------------------------------------------------
        template<auto Start, auto End>
        using subarray = sublist_t<TypeArray, detail::deindex_v<Start>, detail::deindex_v<End>>;
        
        //--------------------------------------------------------------------------------------------------------------
        template<auto Index, auto Dest>
        using move = move_t<TypeArray, detail::deindex_v<Index>, detail::deindex_v<Dest>>;
        
        template<auto Index1, auto Index2>
        using swap = swap_t<TypeArray, detail::deindex_v<Index1>, detail::deindex_v<Index2>>;
        
        template<auto Start, auto Middle, auto End>
        using rotate = rotate_t<TypeArray, detail::deindex_v<Start>, detail::deindex_v<Middle>, detail::deindex_v<End>>;
        
        template<template<class, class> class Comparator>
        using sort = sort_t<TypeArray, Comparator>;
        
        template<template<class> class Mapper>
        using map = map_t<TypeArray, Mapper>;
        
        //--------------------------------------------------------------------------------------------------------------
        constexpr static auto begin = begin_t{};
        
        constexpr static auto end = end_t{};
        
        constexpr static auto rbegin = rbegin_t{};
        
        constexpr static auto rend = rend_t{};
    };
    
    //==================================================================================================================
    template<class T, class ...Args>
    constexpr inline static auto makeVariant(Args &&...args)
        noexcept(noexcept(detail::makeVariant(T{}, std::forward<Args>(args)...)))
    {
        return detail::makeVariant(T{}, std::forward<Args>(args)...);
    }
    
    template<class T, class ...Args>
    constexpr inline static auto makeVarArray(Args &&...args)
         noexcept(noexcept(detail::makeVarArray(T{}, std::forward<Args>(args)...)))
    {
        return detail::makeVarArray(T{}, std::forward<Args>(args)...);
    }
    
    template<class T, class U, class Fn>
    constexpr inline static auto forEach(T start, U end, Fn &&fn)
         noexcept(noexcept(detail::forEach(start, end, std::forward<Fn>(fn))))
    {
        return detail::forEach(start, end, std::forward<Fn>(fn));
    }
    
    template<class T, class U, class Fn>
    constexpr inline static auto apply(T start, U end, Fn &&fn)
         noexcept(noexcept(detail::apply(start, end, std::forward<Fn>(fn))))
    {
        return detail::apply(start, end, std::forward<Fn>(fn));
    }
}
