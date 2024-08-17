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
    /** 
     *  @addtogroup type_list
     *  @{
     */
     
    //==================================================================================================================
    //
    // 
    // @brief A pseudo-iterator for TypeArray that deals with iteration based on template aliases.
    // 
    // Every instantiation of this class template represents a positional interface for any given TypeArray,
    // providing a set of utilities for the represented type as well as an interface to easily switch back and forth
    // between any type in the associated TypeArray.
    // 
    // Every iterator instantiation comes with the basic index (the type it currently "points to") and an alias for
    // the associated TypeArray. Thus, every instantiation is unique for each unique TypeArray instantiation and
    // the corresponding index representing the position.
    // 
    // This interface also allows certain helpers in TypeArray to be used with this instead of a plain index_t.
    // 
    // This class can also be object-instantiated, which can provide a useful helper utility when passing them across
    // functions. Functions like forEach() and forAll() require such an instance.
    // 
    // A specialisation of this class is provided for the case Index == Array::length, at which point helper alias
    // "type" is no longer provided (no type exists past the end), for these cases it might be helpful to bounds-check
    // any usage of said alias.
    // 
    // If index is out of bounds of the associated TypeArray (except one past the end), compilation will fail.  
    // Compilation will also fail if Array is not a valid TypeArray type.
    // 
    // @tparam Array The TypeArray the iterator is associated with
    // @tparam Index The current index inside the type array, if left default instantiated, index will be 0
    // 
    //
    
    /**
     *  @brief A helper class for pseudo-iterating over type lists.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
     *  @tparam T The underlying <a href="https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf">type list conformant</a> type
     *  @tparam I The index of the current type inside the type list
     *  @tparam Reverse Whether to index from back to front if true
     *  @metadata{category, type_iterator}
     */
    template<class T, index_t I, bool Reverse>
    struct TypeIteratorBase;
    
    template<template<class...> class T, index_t I, bool Reverse, class ...Types>
    struct TypeIteratorBase<T<Types...>, I, Reverse>
        : detail::iteratorContainer<T<Types...>, I>
    {
        static_assert(I >= 0 && I <= sizeof...(Types), "iterator index out of bounds");
        
        //--------------------------------------------------------------------------------------------------------------
        /** 
         *  @brief The iterator's underlying <a href="https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf">type list conformant</a> type.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
         *  @metadata{category, alias}
         */
        using Array = T<Types...>;
        
        //--------------------------------------------------------------------------------------------------------------
        /** 
         *  @brief The iterator's current index in the type list.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
         *  @metadata{category, constant}
         */
        constexpr static index_t index = I;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Determines whether two iterators index the same type of the same TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
         *  @metadata{category, comparison}
         */
        template<class Other, std::enable_if_t<detail::isCompatibleTypeIt<TypeIteratorBase, Other>::value>* = nullptr>
        constexpr static bool isEqual = (index == Other::index);
        
        /**
         *  @brief Determines whether to iterators index different types of the same TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
         *  @metadata{category, comparison}
         */
        template<class Other, std::enable_if_t<detail::isCompatibleTypeIt<TypeIteratorBase, Other>::value>* = nullptr>
        constexpr static bool isNotEqual = (index != Other::index);
        
        /**
         *  @brief Determines whether the type indexed by this iterator comes before the type indexed
         *         by the other iterator.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
         *  @metadata{category, comparison}
         */
        template<class Other, std::enable_if_t<detail::isCompatibleTypeIt<TypeIteratorBase, Other>::value>* = nullptr>
        constexpr static bool isLessThan = (index < Other::index);
        
        /**
         *  @brief Determines whether the type indexed by this iterator either comes before or is the same type as
         *         the one indexed by the other iterator.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
         *  @metadata{category, comparison}
         */
        template<class Other, std::enable_if_t<detail::isCompatibleTypeIt<TypeIteratorBase, Other>::value>* = nullptr>
        constexpr static bool isLessThanOrEqual = (index <= Other::index);
        
        /**
         *  @brief Determines whether the type indexed by this iterator comes after the type indexed
         *         by the other iterator.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
         *  @metadata{category, comparison}
         */
        template<class Other, std::enable_if_t<detail::isCompatibleTypeIt<TypeIteratorBase, Other>::value>* = nullptr>
        constexpr static bool isGreaterThan = (index > Other::index);
        
        /**
         *  @brief Determines whether the type indexed by this iterator either comes after or is the same type as
         *         the one indexed by the other iterator.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
         *  @metadata{category, comparison}
         */
        template<class Other, std::enable_if_t<detail::isCompatibleTypeIt<TypeIteratorBase, Other>::value>* = nullptr>
        constexpr static bool isGreaterThanOrEqual = (index >= Other::index);
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Gets a new instantiation of the current iterator with index incremented by one.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
         *  @metadata{category, indexing}
         */
        template<index_t J = index, std::enable_if_t<(J >= 0 && J < sizeof...(Types))>* = nullptr>
        using next = TypeIteratorBase<Array, (J + 1), Reverse>;
        
        /**
         *  @brief Gets a new instantiation of the current iterator with index decremented by one.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
         *  @metadata{category, indexing}
         */
        template<index_t J = index, std::enable_if_t<(J > 0 && J <= sizeof...(Types))>* = nullptr>
        using prev = TypeIteratorBase<Array, (J - 1), Reverse>;
        
        /**
         *  @brief Gets a new instantiation of the current iterator with index incremented by the given amount.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
         *  @metadata{category, indexing}
         */
        template<index_t N>
        using inc = TypeIteratorBase<Array, (index + N), Reverse>;
        
        /**
         *  @brief Gets a new instantiation of the current iterator with index decremented by the given amount.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
         *  @metadata{category, indexing}
         */
        template<index_t N>
        using dec = TypeIteratorBase<Array, (index - N), Reverse>;
        
        /**
         *  @brief Gets a new instantiation of the current iterator with the specified fixed index.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
         *  @metadata{category, indexing}
         */
        template<index_t J>
        using with = TypeIteratorBase<Array, J, Reverse>;
    };
    
    /**
     *  @brief A helper alias for extrait::TypeIteratorBase that indexes from front to back.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
     *  @tparam T The underlying <a href="https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf">type list conformant</a> type
     *  @tparam I The index of the current type inside the type list
     *  @ref extrait::TypeIteratorBase
     *  @metadata{category, helper_alias}
     */
    template<class T, index_t I>
    using TypeIterator = TypeIteratorBase<T, I, false>;
    
    /**
     *  @brief A helper alias for extrait::TypeIteratorBase that indexes from back to front.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
     *  @tparam T The underlying <a href="https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf">type list conformant</a> type
     *  @tparam I The index of the current type inside the type list
     *  @ref extrait::TypeIteratorBase
     *  @metadata{category, helper_alias}
     */
    template<class T, index_t I>
    using ReverseTypeIterator = TypeIteratorBase<T, I, true>;
    
    //==================================================================================================================
    /**
     *  @brief A tuple-like helper class for holding and manipulating type lists.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray
     *  @tparam Types The types this TypeArray manages
     *  @metadata{category, type_container}
     */
    template<class ...Types>
    struct TypeArray
    {
        //==============================================================================================================
        using begin_t  = TypeIterator<TypeArray, 0>;
        using end_t    = TypeIterator<TypeArray, sizeof...(Types)>;
        using rbegin_t = ReverseTypeIterator<TypeArray, 0>;
        using rend_t   = ReverseTypeIterator<TypeArray, sizeof...(Types)>;
        
        //--------------------------------------------------------------------------------------------------------------
        /** 
         *  @brief Determines whether this TypeArray is empty.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray
         *  @metadata{category, list_properties}
         */
        constexpr static bool isEmpty = false;
        
        /**
         *  @brief Determines the number of types in this TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray
         *  @metadata{category, list_properties}
         */
        constexpr static std::size_t length = sizeof...(Types);
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Compares a type with this TypeArray for equality.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/equals
         *  @metadata{category, comparative}
         */
        template<class Other>
        constexpr static bool equals = std::is_same_v<TypeArray, Other>;
        
        /**
         *  @brief Determines whether this TypeArray and another class template instantiation share the same type list.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/sameTypeList
         *  @metadata{category, comparative}
         */
        template<class Other>
        constexpr static bool sameTypeList = sameTemplateArguments_v<TypeArray, Other>;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Determines whether this TypeArray contains a certain type.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/contains
         *  @metadata{category, type_search}
         */
        template<class Key>
        constexpr static bool contains = contains_v<TypeArray, Key>;
        
        /**
         *  @brief Determines whether this TypeArray starts with the given set of types.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/startsWith
         *  @metadata{category, type_search}
         *  @metadata{ref_desc, Determines whether a type list starts or ends with a set of types.}
         */
        template<class ...Keys>
        constexpr static bool startsWith = startsWith_v<TypeArray, Keys...>;
        
        /**
         *  @brief Determines whether this TypeArray ends with the given set of types.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/startsWith
         *  @ref extrait::TypeArray::startsWith
         *  @metadata{category, type_search}
         */
        template<class ...Keys>
        constexpr static bool endsWith = endsWith_v<TypeArray, Keys...>;
        
        /**
         *  @brief Determines how many types in this TypeArray matched a given predicate.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/match
         *  @metadata{category, type_search}
         *  @metadata{ref_desc, Determines how types match a predicate.}
         */
        template<template<class> class Predicate>
        constexpr static std::size_t match = match_v<TypeArray, Predicate>;
        
        /**
         *  @brief Determines how many types in this TypeArray did not match a given predicate.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/match
         *  @ref extrait::TypeArray::match
         *  @metadata{category, type_search}
         */
        template<template<class> class Predicate>
        constexpr static std::size_t mismatch = match_v<TypeArray, Predicate>;
        
        /**
         *  @brief Determines whether at least one type in this TypeArray matched a given predicate.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/match
         *  @ref extrait::TypeArray::match
         *  @metadata{category, type_search}
         */
        template<template<class> class Predicate>
        constexpr static bool matchAny = matchAny_v<TypeArray, Predicate>;
        
        /**
         *  @brief Determines whether all types in this TypeArray matched a given predicate.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/match
         *  @ref extrait::TypeArray::match
         *  @metadata{category, type_search}
         */
        template<template<class> class Predicate>
        constexpr static bool matchAll = matchAll_v<TypeArray, Predicate>;
        
        /**
         *  @brief Determines whether no type in this TypeArray matched a given predicate.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/match
         *  @ref extrait::TypeArray::match
         *  @metadata{category, type_search}
         */
        template<template<class> class Predicate>
        constexpr static bool matchNone = matchNone_v<TypeArray, Predicate>;
        
        /**
         *  @brief Determines the index of the first matching type found in a type list.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/indexOf
         *  @metadata{category, type_search}
         *  @metadata{ref_desc, Determines the index of a type in a type list.}
         */
        template<class Key>
        constexpr static index_t indexOf = indexOf_v<TypeArray, Key>;
        
        /**
         *  @brief Determines the index of the last matching type found in a type list.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/indexOf
         *  @ref extrait::TypeArray::indexOf
         *  @metadata{category, type_search}
         */
        template<class Key>
        constexpr static index_t lastIndexOf = lastIndexOf_v<TypeArray, Key>;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Wraps the current type list with a different class template.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/to
         *  @metadata{category, list_conversion}
         */
        template<template<class...> class T>
        using to = T<Types...>;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Gives back an empty TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/clear
         *  @metadata{category, list_mutation}
         */
        using clear = TypeArray<>;
        
        /**
         *  @brief Joins the type lists of multiple instantiated class template type lists into one TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/join
         *  @metadata{category, list_mutation}
         */
        template<class ...Others>
        using join = join_t<TypeArray, TypeArray, Others...>;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Gets the type from this TypeArray at the specified index.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/get
         *  @metadata{category, type_fetching}
         */
        template<auto I>
        using get = get_t<TypeArray, detail::deindex_v<I>>;
        
        /**
         *  @brief Gets the first type from this TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/get
         *  @ref extrait::TypeArray::get
         *  @metadata{category, type_fetching}
         */
        using front = first_t<TypeArray>;
        
        /**
         *  @brief Gets the last type from this TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/get
         *  @ref extrait::TypeArray::get
         *  @metadata{category, type_fetching}
         */
        using back = last_t<TypeArray>;
        
        /**
         *  @brief Gets the type that was considered the minimum among all other types of this TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/min
         *  @metadata{category, type_fetching}
         *  @metadata{ref_desc, Gets the type that was considered the minimum or maximum among all other types of this TypeArray.}
         */
        template<template<class, class> class Comparator>
        using min = minType_t<TypeArray, Comparator>;
        
        /**
         *  @brief Gets the type that was considered the maximum among all other types of this TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/min
         *  @ref extrait::TypeArray::min
         *  @metadata{category, type_fetching}
         */
        template<template<class, class> class Comparator>
        using max = maxType_t<TypeArray, Comparator>;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Appends the specified types at the end of the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/add
         *  @metadata{category, list_mutation}
         */
        template<class ...Add>
        using add = TypeArray<Types..., Add...>;
        
        /**
         *  @brief Adds the specified types at the beginning of the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/add
         *  @ref extrait::TypeArray::add
         *  @metadata{category, list_mutation}
         */
        template<class ...Add>
        using prepend = TypeArray<Add..., Types...>;
        
        /**
         *  @brief Appends the specified types at the end of the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/add
         *  @ref extrait::TypeArray::add
         *  @metadata{category, list_mutation}
         */
        template<class ...Add>
        using addIfAbsent = addIfAbsent_t<TypeArray, Add...>;
        
        /**
         *  @brief Inserts a set of types at a specified index in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/insert
         *  @metadata{category, list_mutation}
         */
        template<auto I, class ...Add>
        using insert = insert_t<TypeArray, detail::deindex_v<I>, Add...>;
        
        /**
         *  @brief Removes all types that are duplicates of previously occurring types in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/deduplicate
         *  @metadata{category, list_mutation}
         */
        using deduplicate = deduplicate_t<TypeArray>;
        
        /**
         *  @brief Creates a TypeArray with a sub-portion of the types (in the specified range) of the original TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/subarray
         *  @metadata{category, list_mutation}
         */
        template<auto Start, auto End>
        using subarray = sublist_t<TypeArray, detail::deindex_v<Start>, detail::deindex_v<End>>;
        
        /**
         *  @brief Removes the first type that matched key from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/remove
         *  @metadata{category, list_mutation}
         *  @metadata{ref_desc, Removes a type from the associated TypeArray based on the given template arguments.}
         */
        template<class Key>
        using remove = remove_t<TypeArray, Key>;
        
        /**
         *  @brief Removes all types that matched key from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/remove%23tabber-removeAll
         *  @ref extrait::TypeArray::remove
         *  @metadata{category, list_mutation}
         */
        template<class Key>
        using removeAll = removeAll_t<TypeArray, Key>;
        
        /**
         *  @brief Removes the first type from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/remove%23tabber-removeFirst
         *  @ref extrait::TypeArray::remove
         *  @metadata{category, list_mutation}
         */
        using removeFirst = removeFirst_t<TypeArray>;
        
        /**
         *  @brief Removes the last type from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/remove%23tabber-removeLast
         *  @ref extrait::TypeArray::remove
         *  @metadata{category, list_mutation}
         */
        using removeLast = removeLast_t<TypeArray>;
        
        /**
         *  @brief Removes the type at the specified index from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/remove%23tabber-removeAt
         *  @ref extrait::TypeArray::remove
         *  @metadata{category, list_mutation}
         */
        template<auto I>
        using removeAt = removeAt_t<TypeArray, detail::deindex_v<I>>;
        
        /**
         *  @brief Removes a range of types from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/remove%23tabber-removeRange
         *  @ref extrait::TypeArray::remove
         *  @metadata{category, list_mutation}
         */
        template<auto Start, auto End>
        using removeRange = removeRange_t<TypeArray, detail::deindex_v<Start>, detail::deindex_v<End>>;
        
        /**
         *  @brief Removes all types that matched a predicate from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/remove%23tabber-removeIf
         *  @ref extrait::TypeArray::remove
         *  @metadata{category, list_mutation}
         */
        template<template<class> class Predicate>
        using removeIf = removeIf_t<TypeArray, Predicate>;
        
        /**
         *  @brief Retains all types that matched a predicate in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/remove%23tabber-filter
         *  @ref extrait::TypeArray::remove
         *  @metadata{category, list_mutation}
         */
        template<template<class> class Predicate>
        using filter = filter_t<TypeArray, Predicate>;
        
        /**
         *  @brief Replaces the first type that matched key from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/replace
         *  @metadata{category, list_mutation}
         *  @metadata{ref_desc, Replaces types inside the associated TypeArray based on the given template arguments.}
         */
        template<class Key, class ...Replacement>
        using replace = replace_t<TypeArray, Key, Replacement...>;
        
        /**
         *  @brief Replaces all types that matched key in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/replace%23tabber-replaceAll
         *  @ref extrait::TypeArray::replace
         *  @metadata{category, list_mutation}
         */
        template<class Key, class ...Replacement>
        using replaceAll = replaceAll_t<TypeArray, Key, Replacement...>;
        
        /**
         *  @brief Replaces the first type in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/replace%23tabber-replaceFirst
         *  @ref extrait::TypeArray::replace
         *  @metadata{category, list_mutation}
         */
        template<class ...Replacement>
        using replaceFirst = replaceFirst_t<TypeArray, Replacement...>;
        
        /**
         *  @brief Replaces the last type in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/replace%23tabber-replaceLast
         *  @ref extrait::TypeArray::replace
         *  @metadata{category, list_mutation}
         */
        template<class ...Replacement>
        using replaceLast = replaceLast_t<TypeArray, Replacement...>;
        
        /**
         *  @brief Replaces the type at the specified index in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/replace%23tabber-replaceAt
         *  @ref extrait::TypeArray::replace
         *  @metadata{category, list_mutation}
         */
        template<auto I, class ...Replacement>
        using replaceAt = replaceAt_t<TypeArray, detail::deindex_v<I>, Replacement...>;
        
        /**
         *  @brief Replaces a range of types in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/replace%23tabber-replaceRange
         *  @ref extrait::TypeArray::replace
         *  @metadata{category, list_mutation}
         */
        template<auto Start, auto End, class ...Replacement>
        using replaceRange = replaceRange_t<TypeArray, detail::deindex_v<Start>, detail::deindex_v<End>, Replacement...>;
        
        /**
         *  @brief Replaces all types that matched a predicate in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/replace%23tabber-replaceIf
         *  @ref extrait::TypeArray::replace
         *  @metadata{category, list_mutation}
         */
        template<template<class> class Predicate, class ...Replacement>
        using replaceIf = replaceIf_t<TypeArray, Predicate, Replacement...>;
        
        /**
         *  @brief Replaces all types that did not match a predicate in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/replace%23tabber-replaceIfNot
         *  @ref extrait::TypeArray::replace
         *  @metadata{category, list_mutation}
         */
        template<template<class> class Predicate, class ...Replacement>
        using replaceIfNot = replaceIfNot_t<TypeArray, Predicate, Replacement...>;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Moves two types and left rotates the types between the indices.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/move
         *  @metadata{category, arrangement}
         */
        template<auto I, auto Dest>
        using move = move_t<TypeArray, detail::deindex_v<I>, detail::deindex_v<Dest>>;
        
        /**
         *  @brief Swaps two types in the TypeArray without altering the positions of other types.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/swap
         *  @metadata{category, arrangement}
         */
        template<auto I, auto Dest>
        using swap = swap_t<TypeArray, detail::deindex_v<I>, detail::deindex_v<Dest>>;
        
        /**
         *  @brief Left rotates the types at in the specified range of the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/rotate
         *  @metadata{category, arrangement}
         */
        template<auto Start, auto Middle, auto End>
        using rotate = rotate_t<TypeArray, detail::deindex_v<Start>, detail::deindex_v<Middle>, detail::deindex_v<End>>;
        
        /**
         *  @brief Sorts the types in the TypeArray based on a given comparator.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/sort
         *  @metadata{category, arrangement}
         */
        template<template<class, class> class Comparator>
        using sort = sort_t<TypeArray, Comparator>;
        
        /**
         *  @brief Reverses the types in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/reverse
         *  @metadata{category, arrangement}
         */
        using reverse = reverse_t<TypeArray>;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Gives back a new TypeArray with all types mapped to the given mapper.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/map
         *  @metadata{category, argument_mutation}
         */
        template<template<class> class Mapper>
        using map = map_t<TypeArray, Mapper>;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief A TypeIterator to the beginning (first element) of the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/begin
         */
        constexpr static auto begin = begin_t{};
        
        /**
         *  @brief A TypeIterator to the end (one past last element) of the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/end
         */
        constexpr static auto end = end_t{};
        
        /**
         *  @brief A ReverseTypeIterator to the beginning (last element) of the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/rbegin
         */
        constexpr static auto rbegin = rbegin_t{};
        
        /**
         *  @brief A ReverseTypeIterator to the end (one before first element) of the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/rend
         */
        constexpr static auto rend = rend_t{};
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Constructs a new TypeArray type.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray
         */
        constexpr TypeArray() noexcept = default;
        
        /**
         *  @brief Constructs a new TypeArray type and deduces the TypeArray argument list based on the given extrait::DeductionPolicy.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray
         */
        template<class ...T>
        explicit constexpr TypeArray([[maybe_unused]] T &&...types) noexcept {}
    };

#if !DOXYGEN
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
        
        using reverse = reverse_t<TypeArray>;
        
        using clear = TypeArray<>;
        
        //--------------------------------------------------------------------------------------------------------------
        template<auto I>
        using get = get_t<TypeArray, detail::deindex_v<I>>;
        
        //--------------------------------------------------------------------------------------------------------------
        template<class ...Add>
        using add = TypeArray<Add...>;
        
        template<class ...Prepend>
        using prepend = TypeArray<Prepend...>;
        
        template<class ...Add>
        using addIfAbsent = addIfAbsent_t<TypeArray, Add...>;
        
        template<auto I, class ...Insertions>
        using insert = insert_t<TypeArray, detail::deindex_v<I>, Insertions...>;
        
        using deduplicate = deduplicate_t<TypeArray>;
        
        //--------------------------------------------------------------------------------------------------------------
        template<class Key>
        using remove = remove_t<TypeArray, Key>;
        
        template<class Key>
        using removeAll = removeAll_t<TypeArray, Key>;
        
        template<auto I>
        using removeAt = removeAt_t<TypeArray, detail::deindex_v<I>>;
        
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
        
        template<auto I, class ...Replacement>
        using replaceAt = replaceAt_t<TypeArray, detail::deindex_v<I>, Replacement...>;
        
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
        template<auto I, auto Dest>
        using move = move_t<TypeArray, detail::deindex_v<I>, detail::deindex_v<Dest>>;
        
        template<auto I, auto J>
        using swap = swap_t<TypeArray, detail::deindex_v<I>, detail::deindex_v<J>>;
        
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
        
        //--------------------------------------------------------------------------------------------------------------
        constexpr TypeArray() noexcept = default;
        
        template<class ...T>
        explicit constexpr TypeArray([[maybe_unused]] T &&...types) noexcept {}
    };
#endif
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Specifies how the types that are deduced from constructing a TypeArray should be given to the parameter
     *         list of the TypeArray.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/DeductionPolicy%23tabber-
     *  @tparam Id The internal ID of the deduction policy
     */
    template<std::size_t Id>
    struct DeductionPolicy {};
    
    /**
     *  @brief Specifies that all types deduced from constructing a TypeArray should be decayed first before given
     *         to the TypeArray.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/DeductionPolicy
     */
    using deductionPolicyDecay = DeductionPolicy<0>;
    
    /**
     *  @brief Specifies that all types deduced from constructing a TypeArray should be stripped off all
     *         type modifications first before given to the TypeArray.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/DeductionPolicy
     */
    using deductionPolicyStrip = DeductionPolicy<1>;
    
    /**
     *  @brief Specifies that all types deduced from constructing a TypeArray should be mapped to a different type
     *         first before given to the TypeArray.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/DeductionPolicy
     */
    template<template<class> class Mapper>
    struct deductionPolicyMap : DeductionPolicy<2> {};
    
    /**
     *  @brief Value helper for extrait::deductionPolicyDecay.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/DeductionPolicy
     */
    constexpr inline auto deductionPolicyDecay_v = deductionPolicyDecay{};
    
    /**
     *  @brief Value helper for extrait::deductionPolicyStrip.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/DeductionPolicy
     */
    constexpr inline auto deductionPolicyStrip_v = deductionPolicyStrip{};
    
    /**
     *  @brief Value helper for extrait::deductionPolicyMap.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/DeductionPolicy
     */
    template<template<class> class Mapper>
    constexpr inline auto deductionPolicyMap_v = deductionPolicyMap<Mapper>{};
    
    //------------------------------------------------------------------------------------------------------------------
    template<class ...Types>
    TypeArray(deductionPolicyDecay, Types &&...types) -> TypeArray<std::decay_t<Types>...>;
    
    template<class ...Types>
    TypeArray(deductionPolicyStrip, Types &&...types) -> TypeArray<strip_t<Types>...>;
    
    template<template<class> class Mapper, class ...Types>
    TypeArray(deductionPolicyMap<Mapper>, Types &&...types) -> TypeArray<typename Mapper<Types>::type...>;
    
    template<class ...Types>
    TypeArray(Types &&...types) -> TypeArray<Types...>;
    
    //==================================================================================================================
    /**
     *  @brief Constructs a variant from a specified <a href="https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf">type list conformant</a>
     *         type and given arguments.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/funcs/makeVariant
     */
    template<class T, class ...Args>
    constexpr inline static auto makeVariant(Args &&...args)
        noexcept(noexcept(detail::makeVariant(T{}, std::forward<Args>(args)...)))
    {
        return detail::makeVariant(T{}, std::forward<Args>(args)...);
    }
    
    /**
     *  @brief Constructs an array with all types from the given <a href="https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf">type list conformant</a>
     *         type with each element being a variant constructed from the type given at the specified position.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/funcs/makeVarArray
     */
    template<class T, class ...Args>
    constexpr inline static auto makeVarArray(Args &&...args)
         noexcept(noexcept(detail::makeVarArray(T{}, std::forward<Args>(args)...)))
    {
        return detail::makeVarArray(T{}, std::forward<Args>(args)...);
    }
    
    /**
     *  @brief Calls a callback for each type given in a <a href="https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf">type list conformant</a>
     *         type and optionally returns an array with the results of each execution.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/funcs/forEach
     */
    template<class T, class U, class Fn>
    constexpr inline static auto forEach(T start, U end, Fn &&fn)
         noexcept(noexcept(detail::forEach(start, end, std::forward<Fn>(fn))))
    {
        return detail::forEach(start, end, std::forward<Fn>(fn));
    }
    
    /**
     *  @brief Calls a callback for all types given in a <a href="https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf">type list conformant</a>
     *         type at once with a parameter pack, and optionally returns the result of this operation.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/funcs/apply
     */
    template<class T, class U, class Fn>
    constexpr inline static auto apply(T start, U end, Fn &&fn)
         noexcept(noexcept(detail::apply(start, end, std::forward<Fn>(fn))))
    {
        return detail::apply(start, end, std::forward<Fn>(fn));
    }
    
    /** @} */
}
