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
     *  @brief A helper class for pseudo-iterating over type lists.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
     *  @tparam T The underlying [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type
     *  @tparam I The index of the current type inside the type list
     *  @tparam Reverse Whether to index from back to front if true
     */
    template<class T, index_t I, bool Reverse>
    struct TypeIteratorBase
    {
        static_assert(assertDep_type<T>, "template argument T is not a type list conformant class template instantiation");
    };

    template<template<class...> class T, index_t I, bool Reverse,
             class ...Types>
    struct TypeIteratorBase<T<Types...>, I, Reverse>
        : detail::TypeIteratorBase_impl<TypeIteratorBase<T<Types...>, I, Reverse>>
        , detail::TypeIteratorNext_impl<TypeIteratorBase<T<Types...>, I, Reverse>>
        , detail::TypeIteratorPrev_impl<TypeIteratorBase<T<Types...>, I, Reverse>>
    {
        //--------------------------------------------------------------------------------------------------------------
        static_assert((I >= 0 && I <= sizeof...(Types)), "index out of bounds");

        //--------------------------------------------------------------------------------------------------------------
        /** 
         *  @brief The iterator's underlying [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
         */
        using Array = T<Types...>;
        
        //--------------------------------------------------------------------------------------------------------------
        /** 
         *  @brief The iterator's current index in the type list.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
         */
        constexpr static index_t index = I;

        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Determines whether two iterators index the same type of the same TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase/isEqual
         *  @tparam Other The other type iterator
         */
        template<class Other, std::enable_if_t<detail::isCompatibleTypeIt<TypeIteratorBase, Other>::value>* = nullptr>
        constexpr static bool isEqual = (index == Other::index);
        
        /**
         *  @brief Determines whether to iterators index different types of the same TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase/isEqual
         *  @tparam Other The other type iterator
         */
        template<class Other, std::enable_if_t<detail::isCompatibleTypeIt<TypeIteratorBase, Other>::value>* = nullptr>
        constexpr static bool isNotEqual = (index != Other::index);
        
        /**
         *  @brief Determines whether the type indexed by this iterator comes before the type indexed
         *         by the other iterator.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase/isEqual
         *  @tparam Other The other type iterator
         */
        template<class Other, std::enable_if_t<detail::isCompatibleTypeIt<TypeIteratorBase, Other>::value>* = nullptr>
        constexpr static bool isLessThan = (index < Other::index);
        
        /**
         *  @brief Determines whether the type indexed by this iterator either comes before or is the same type as
         *         the one indexed by the other iterator.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase/isEqual
         *  @tparam Other The other type iterator
         */
        template<class Other, std::enable_if_t<detail::isCompatibleTypeIt<TypeIteratorBase, Other>::value>* = nullptr>
        constexpr static bool isLessThanOrEqual = (index <= Other::index);
        
        /**
         *  @brief Determines whether the type indexed by this iterator comes after the type indexed
         *         by the other iterator.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase/isEqual
         *  @tparam Other The other type iterator
         */
        template<class Other, std::enable_if_t<detail::isCompatibleTypeIt<TypeIteratorBase, Other>::value>* = nullptr>
        constexpr static bool isGreaterThan = (index > Other::index);
        
        /**
         *  @brief Determines whether the type indexed by this iterator either comes after or is the same type as
         *         the one indexed by the other iterator.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase/isEqual
         *  @tparam Other The other type iterator
         */
        template<class Other, std::enable_if_t<detail::isCompatibleTypeIt<TypeIteratorBase, Other>::value>* = nullptr>
        constexpr static bool isGreaterThanOrEqual = (index >= Other::index);

        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Gets a new instantiation of the current iterator with index incremented by the given amount.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase/inc
         *  @tparam N The amount to decrement the iterator
         */
        template<index_t N>
        using inc = TypeIteratorBase<Array, (index + N), Reverse>;

        /**
         *  @brief Gets a new instantiation of the current iterator with index decremented by the given amount.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase/inc
         *  @tparam N The amount to decrement the iterator
         */
        template<index_t N>
        using dec = TypeIteratorBase<Array, (index - N), Reverse>;
        
        /**
         *  @brief Gets a new instantiation of the current iterator with the specified fixed index.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase/with
         *  @tparam J The new index
         */
        template<index_t J>
        using with = TypeIteratorBase<Array, J, Reverse>;

        //--------------------------------------------------------------------------------------------------------------
        constexpr TypeIteratorBase() noexcept = default;
    };

    /**
     *  @brief A helper alias for extrait::TypeIteratorBase that indexes from front to back.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
     *  @tparam T The underlying [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type
     *  @tparam I The index of the current type inside the type list
     */
    template<class T, index_t I>
    using TypeIterator = TypeIteratorBase<T, I, false>;
    
    /**
     *  @brief A helper alias for extrait::TypeIteratorBase that indexes from back to front.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeIteratorBase
     *  @tparam T The underlying [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type
     *  @tparam I The index of the current type inside the type list
     */
    template<class T, index_t I>
    using ReverseTypeIterator = TypeIteratorBase<T, I, true>;
    
    //==================================================================================================================
    /**
     *  @brief A tuple-like helper class for holding and manipulating type lists.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray
     *  @tparam Types The types this TypeArray manages
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
         */
        constexpr static bool isEmpty = false;
        
        /**
         *  @brief Determines the number of types in this TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray
         */
        constexpr static std::size_t length = sizeof...(Types);
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Compares a type with this TypeArray for equality.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/equals
         *  @tparam Other Another type to compare
         */
        template<class Other>
        constexpr static bool equals = std::is_same_v<TypeArray, Other>;
        
        /**
         *  @brief Determines whether this TypeArray and another class template instantiation share the same type list.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/sameTypeList
         *  @tparam Other Another type to compare
         */
        template<class Other>
        constexpr static bool sameTypeList = sameTemplateArguments_v<TypeArray, Other>;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Determines whether this TypeArray contains a certain type.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/contains
         *  @tparam Key The type to find
         */
        template<class Key>
        constexpr static bool contains = contains_v<TypeArray, Key>;
        
        /**
         *  @brief Determines whether this TypeArray starts with the given set of types.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/startsWith
         *  @tparam Keys The types to find at the start of the type list
         */
        template<class ...Keys>
        constexpr static bool startsWith = startsWith_v<TypeArray, Keys...>;
        
        /**
         *  @brief Determines whether this TypeArray ends with the given set of types.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/startsWith
         *  @tparam Keys The types to find at the end of the type list
         */
        template<class ...Keys>
        constexpr static bool endsWith = endsWith_v<TypeArray, Keys...>;
        
        /**
         *  @brief Determines how many types in this TypeArray matched a given predicate.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/match
         *  @tparam Predicate The predicate to apply to the types
         */
        template<template<class> class Predicate>
        constexpr static std::size_t match = match_v<TypeArray, Predicate>;
        
        /**
         *  @brief Determines how many types in this TypeArray did not match a given predicate.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/match
         *  @tparam Predicate The predicate to apply to the types
         */
        template<template<class> class Predicate>
        constexpr static std::size_t mismatch = match_v<TypeArray, Predicate>;
        
        /**
         *  @brief Determines whether at least one type in this TypeArray matched a given predicate.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/match
         *  @tparam Predicate The predicate to apply to the types
         */
        template<template<class> class Predicate>
        constexpr static bool matchAny = matchAny_v<TypeArray, Predicate>;
        
        /**
         *  @brief Determines whether all types in this TypeArray matched a given predicate.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/match
         *  @tparam Predicate The predicate to apply to the types
         */
        template<template<class> class Predicate>
        constexpr static bool matchAll = matchAll_v<TypeArray, Predicate>;
        
        /**
         *  @brief Determines whether no type in this TypeArray matched a given predicate.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/match
         *  @tparam Predicate The predicate to apply to the types
         */
        template<template<class> class Predicate>
        constexpr static bool matchNone = matchNone_v<TypeArray, Predicate>;
        
        /**
         *  @brief Determines the index of the first matching type found in a type list.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/indexOf
         *  @tparam Key The type to find
         */
        template<class Key>
        constexpr static index_t indexOf = indexOf_v<TypeArray, Key>;
        
        /**
         *  @brief Determines the index of the last matching type found in a type list.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/indexOf
         *  @tparam Key The type to find
         */
        template<class Key>
        constexpr static index_t lastIndexOf = lastIndexOf_v<TypeArray, Key>;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Wraps the current type list with a different class template.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/to
         *  @tparam T Any [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) class template
         */
        template<template<class...> class T>
        using to = T<Types...>;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Gives back an empty TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/clear
         */
        using clear = TypeArray<>;
        
        /**
         *  @brief Joins the type lists of multiple instantiated class template type lists into one TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/join
         *  @tparam Others A list of [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) template instantiations
         */
        template<class ...Others>
        using join = join_t<TypeArray, TypeArray, Others...>;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Gets the type from this TypeArray at the specified index.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/get
         *  @tparam I The index of the type to get
         */
        template<auto I>
        using get = get_t<TypeArray, detail::deindex_v<I>>;
        
        /**
         *  @brief Gets the first type from this TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/get
         */
        using front = first_t<TypeArray>;
        
        /**
         *  @brief Gets the last type from this TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/get
         */
        using back = last_t<TypeArray>;
        
        /**
         *  @brief Gets the type that was considered the minimum among all other types of this TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/min
         *  @tparam Comparator The comparator class template that the types will be compared against each other
         */
        template<template<class, class> class Comparator>
        using min = minType_t<TypeArray, Comparator>;
        
        /**
         *  @brief Gets the type that was considered the maximum among all other types of this TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/min
         *  @tparam Comparator The comparator class template that the types will be compared against each other
         */
        template<template<class, class> class Comparator>
        using max = maxType_t<TypeArray, Comparator>;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Appends the specified types at the end of the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/add
         *  @tparam Add The list of types to add
         */
        template<class ...Add>
        using add = TypeArray<Types..., Add...>;
        
        /**
         *  @brief Adds the specified types at the beginning of the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/prepend
         *  @tparam Add The list of types to add
         */
        template<class ...Add>
        using prepend = TypeArray<Add..., Types...>;
        
        /**
         *  @brief Appends the specified types at the end of the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/add
         *  @tparam Add The list of types to add
         */
        template<class ...Add>
        using addIfAbsent = addIfAbsent_t<TypeArray, Add...>;
        
        /**
         *  @brief Inserts a set of types at a specified index in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/insert
         *  @tparam I The index the types should be inserted at
         *  @tparam Add The list of types to insert
         */
        template<auto I, class ...Add>
        using insert = insert_t<TypeArray, detail::deindex_v<I>, Add...>;
        
        /**
         *  @brief Removes all types that are duplicates of previously occurring types in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/deduplicate
         */
        using deduplicate = deduplicate_t<TypeArray>;
        
        /**
         *  @brief Creates a TypeArray with a sub-portion of the types (in the specified range) of the original TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/subarray
         *  @tparam Start The start index of the range
         *  @tparam End The end index of the range (exclusive)
         */
        template<auto Start, auto End>
        using subarray = sublist_t<TypeArray, detail::deindex_v<Start>, detail::deindex_v<End>>;
        
        /**
         *  @brief Removes the first type that matched key from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/remove
         *  @tparam Key The type to remove
         */
        template<class Key>
        using remove = remove_t<TypeArray, Key>;
        
        /**
         *  @brief Removes all types that matched key from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/remove
         *  @tparam Key The type to remove
         */
        template<class Key>
        using removeAll = removeAll_t<TypeArray, Key>;
        
        /**
         *  @brief Removes the first type from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/remove
         */
        using removeFirst = removeFirst_t<TypeArray>;
        
        /**
         *  @brief Removes the last type from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/remove
         */
        using removeLast = removeLast_t<TypeArray>;
        
        /**
         *  @brief Removes the type at the specified index from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/remove
         *  @tparam I The index of the type to remove
         */
        template<auto I>
        using removeAt = removeAt_t<TypeArray, detail::deindex_v<I>>;
        
        /**
         *  @brief Removes a range of types from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/remove
         *  @tparam Start The start index of the range
         *  @tparam End The end index of the range (exclusive)
         */
        template<auto Start, auto End>
        using removeRange = removeRange_t<TypeArray, detail::deindex_v<Start>, detail::deindex_v<End>>;
        
        /**
         *  @brief Removes all types that matched a predicate from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/remove
         *  @tparam Predicate The predicate to determine the types to remove
         */
        template<template<class> class Predicate>
        using removeIf = removeIf_t<TypeArray, Predicate>;
        
        /**
         *  @brief Retains all types that matched a predicate in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/remove
         *  @tparam Predicate The predicate to determine the types to retain
         */
        template<template<class> class Predicate>
        using filter = filter_t<TypeArray, Predicate>;
        
        /**
         *  @brief Replaces the first type that matched key from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/replace
         *  @tparam Key The type to replace
         *  @tparam Replacement The list of types to insert where the old type was
         */
        template<class Key, class ...Replacement>
        using replace = replace_t<TypeArray, Key, Replacement...>;
        
        /**
         *  @brief Replaces all types that matched key in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/replace
         *  @tparam Key The type to replace
         *  @tparam Replacement The list of types to insert where the old types were
         */
        template<class Key, class ...Replacement>
        using replaceAll = replaceAll_t<TypeArray, Key, Replacement...>;
        
        /**
         *  @brief Replaces the first type in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/replace
         *  @tparam Replacement The list of types to insert where the old type was
         */
        template<class ...Replacement>
        using replaceFirst = replaceFirst_t<TypeArray, Replacement...>;
        
        /**
         *  @brief Replaces the last type in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/replace
         *  @tparam Replacement The list of types to insert where the old type was
         */
        template<class ...Replacement>
        using replaceLast = replaceLast_t<TypeArray, Replacement...>;
        
        /**
         *  @brief Replaces the type at the specified index in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/replace
         *  @tparam I The index of the type to replace
         *  @tparam Replacement The list of types to insert where the old type was
         */
        template<auto I, class ...Replacement>
        using replaceAt = replaceAt_t<TypeArray, detail::deindex_v<I>, Replacement...>;
        
        /**
         *  @brief Replaces a range of types in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/replace
         *  @tparam Start The start index of the range to replace
         *  @tparam End The end index of the range to replace (exclusive)
         *  @tparam Replacement The list of types to insert where the old types were
         */
        template<auto Start, auto End, class ...Replacement>
        using replaceRange = replaceRange_t<TypeArray, detail::deindex_v<Start>, detail::deindex_v<End>, Replacement...>;
        
        /**
         *  @brief Replaces all types that matched a predicate in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/replace
         *  @tparam Predicate The predicate to determine the types to replace
         *  @tparam Replacement The list of types to insert where the old types were
         */
        template<template<class> class Predicate, class ...Replacement>
        using replaceIf = replaceIf_t<TypeArray, Predicate, Replacement...>;
        
        /**
         *  @brief Replaces all types that did not match a predicate in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/replace
         *  @tparam Predicate The predicate to determine the types to retain
         *  @tparam Replacement The list of types to insert where the old type was
         */
        template<template<class> class Predicate, class ...Replacement>
        using replaceIfNot = replaceIfNot_t<TypeArray, Predicate, Replacement...>;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Moves two types and left rotates the types between the indices.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/move
         *  @tparam I The index of the type to move
         *  @tparam Dest The index of the slot to move the type to (can be one past the end)
         */
        template<auto I, auto Dest>
        using move = move_t<TypeArray, detail::deindex_v<I>, detail::deindex_v<Dest>>;
        
        /**
         *  @brief Swaps two types in the TypeArray without altering the positions of other types.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/swap
         *  @tparam I The index of the type to swap
         *  @tparam Dest The index of the second type to swap with this one
         */
        template<auto I, auto Dest>
        using swap = swap_t<TypeArray, detail::deindex_v<I>, detail::deindex_v<Dest>>;
        
        /**
         *  @brief Left rotates the types at in the specified range of the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/rotate
         *  @tparam Start The start index of the range to rotate
         *  @tparam Middle The index of the type to move to the start of the range
         *  @tparam End The end index of the range to rotate (exclusive)
         */
        template<auto Start, auto Middle, auto End>
        using rotate = rotate_t<TypeArray, detail::deindex_v<Start>, detail::deindex_v<Middle>, detail::deindex_v<End>>;
        
        /**
         *  @brief Sorts the types in the TypeArray based on a given comparator.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/sort
         *  @tparam Comparator The comparator class template that the types will be compared against each other
         */
        template<template<class, class> class Comparator>
        using sort = sort_t<TypeArray, Comparator>;
        
        /**
         *  @brief Reverses the types in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/reverse
         */
        using reverse = reverse_t<TypeArray>;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Gives back a new TypeArray with all types mapped to the given mapper.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/map
         *  @tparam Mapper The mapper class template that will transform every type
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
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/TypeArray
         */
        constexpr TypeArray() noexcept = default;
        
        /**
         *  @brief Constructs a new TypeArray type and deduces the TypeArray argument list based on the given extrait::DeductionPolicy.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/TypeArray
         */
        template<class ...T>
        explicit constexpr TypeArray([[maybe_unused]] T &&...types) noexcept {}
    };

    /**
     *  @brief A specialisation for extrait::TypeArray that deals with empty type lists.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty
     */
    template<>
    struct TypeArray<>
    {
        //==============================================================================================================
        using begin_t  = TypeIterator<TypeArray, 0>;
        using end_t    = TypeIterator<TypeArray, 0>;
        using rbegin_t = ReverseTypeIterator<TypeArray, 0>;
        using rend_t   = ReverseTypeIterator<TypeArray, 0>;
        
        //--------------------------------------------------------------------------------------------------------------
        /** 
         *  @brief Determines whether this TypeArray is empty.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty
         */
        constexpr static bool isEmpty = true;
        
        /**
         *  @brief Determines the number of types in this TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty
         */
        constexpr static std::size_t length = 0;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Compares a type with this TypeArray for equality.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/equals
         *  @tparam Other Another type to compare
         */
        template<class Other>
        constexpr static bool equals = std::is_same_v<TypeArray, Other>;
        
        /**
         *  @brief Determines whether this TypeArray and another class template instantiation share the same type list.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/sameTypeList
         *  @tparam Other Another type to compare
         */
        template<class Other>
        constexpr static bool sameTypeList = sameTemplateArguments_v<TypeArray, Other>;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Determines whether this TypeArray contains a certain type.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/contains
         *  @tparam Key The type to find
         */
        template<class Key>
        constexpr static bool contains = false;
        
        /**
         *  @brief Determines whether this TypeArray starts with the given set of types.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/startsWith
         *  @tparam Keys The types to find at the start of the type list
         */
        template<class ...Keys>
        constexpr static bool startsWith = (sizeof...(Keys) == 0);
        
        /**
         *  @brief Determines whether this TypeArray ends with the given set of types.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/startsWith
         *  @tparam Keys The types to find at the end of the type list
         */
        template<class ...Keys>
        constexpr static bool endsWith = (sizeof...(Keys) == 0);
        
        /**
         *  @brief Determines how many types in this TypeArray matched a given predicate.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/match
         *  @tparam Predicate The predicate to apply to the types
         */
        template<template<class> class Predicate>
        constexpr static std::size_t match = 0;
        
        /**
         *  @brief Determines how many types in this TypeArray did not match a given predicate.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/match
         *  @tparam Predicate The predicate to apply to the types
         */
        template<template<class> class Predicate>
        constexpr static std::size_t mismatch = 0;
        
        /**
         *  @brief Determines whether at least one type in this TypeArray matched a given predicate.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/match
         *  @tparam Predicate The predicate to apply to the types
         */
        template<template<class> class Predicate>
        constexpr static bool matchAny = false;
        
        /**
         *  @brief Determines whether all types in this TypeArray matched a given predicate.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/match
         *  @tparam Predicate The predicate to apply to the types
         */
        template<template<class> class Predicate>
        constexpr static bool matchAll = true;
        
        /**
         *  @brief Determines whether no type in this TypeArray matched a given predicate.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/match
         *  @tparam Predicate The predicate to apply to the types
         */
        template<template<class> class Predicate>
        constexpr static bool matchNone = true;
        
        /**
         *  @brief Determines the index of the first matching type found in a type list.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/indexOf
         *  @tparam Key The type to find
         */
        template<class Key>
        constexpr static index_t indexOf = endOfTypeList;
        
        /**
         *  @brief Determines the index of the last matching type found in a type list.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/indexOf
         *  @tparam Key The type to find
         */
        template<class Key>
        constexpr static index_t lastIndexOf = endOfTypeList;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Wraps the current type list with a different class template.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/to
         *  @tparam T Any [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) class template
         */
        template<template<class...> class T>
        using to = T<>;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Gives back an empty TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/clear
         */
        using clear = TypeArray<>;
        
        /**
         *  @brief Joins the type lists of multiple instantiated class template type lists into one TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/join
         *  @tparam Others A list of [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) template instantiations
         */
        template<class ...Others>
        using join = join_t<TypeArray, Others...>;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Appends the specified types at the end of the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/add
         *  @tparam Add The list of types to add
         */
        template<class ...Add>
        using add = TypeArray<Add...>;
        
        /**
         *  @brief Adds the specified types at the beginning of the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/prepend
         *  @tparam Add The list of types to add
         */
        template<class ...Add>
        using prepend = TypeArray<Add...>;
        
        /**
         *  @brief Appends the specified types at the end of the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/add
         *  @tparam Add The list of types to add
         */
        template<class ...Add>
        using addIfAbsent = addIfAbsent_t<TypeArray, Add...>;
        
        /**
         *  @brief Inserts a set of types at a specified index in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/insert
         *  @tparam I The index the types should be inserted at
         *  @tparam Add The list of types to insert
         */
        template<auto I, class ...Add>
        using insert = insert_t<TypeArray, detail::deindex_v<I>, Add...>;
        
        /**
         *  @brief Removes all types that are duplicates of previously occurring types in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/deduplicate
         */
        using deduplicate = TypeArray;
        
        /**
         *  @brief Creates a TypeArray with a sub-portion of the types (in the specified range) of the original TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray/subarray
         *  @tparam Start The start index of the range
         *  @tparam End The end index of the range (exclusive)
         */
        template<auto Start, auto End>
        using subarray = sublist_t<TypeArray, detail::deindex_v<Start>, detail::deindex_v<End>>;
        
        /**
         *  @brief Removes the first type that matched key from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/remove
         *  @tparam Key The type to remove
         */
        template<class Key>
        using remove = TypeArray<>;
        
        /**
         *  @brief Removes all types that matched key from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/remove
         *  @tparam Key The type to remove
         */
        template<class Key>
        using removeAll = TypeArray<>;
        
        /**
         *  @brief Removes a range of types from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/remove
         *  @tparam Start The start index of the range
         *  @tparam End The end index of the range (exclusive)
         */
        template<auto Start, auto End>
        using removeRange = removeRange_t<TypeArray, detail::deindex_v<Start>, detail::deindex_v<End>>;
        
        /**
         *  @brief Removes all types that matched a predicate from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/remove
         *  @tparam Predicate The predicate to determine the types to remove
         */
        template<template<class> class Predicate>
        using removeIf = TypeArray<>;
        
        /**
         *  @brief Retains all types that matched a predicate in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/remove
         *  @tparam Predicate The predicate to determine the types to retain

         */
        template<template<class> class Predicate>
        using filter = TypeArray<>;
        
        /**
         *  @brief Replaces the first type that matched key from the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/replace
         *  @tparam Key The type to replace
         *  @tparam Replacement The list of types to insert where the old type was
         */
        template<class Key, class ...Replacement>
        using replace = TypeArray<>;
        
        /**
         *  @brief Replaces all types that matched key in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/replace
         *  @tparam Key The type to replace
         *  @tparam Replacement The list of types to insert where the old types were
         */
        template<class Key, class ...Replacement>
        using replaceAll = TypeArray<>;
        
        /**
         *  @brief Replaces a range of types in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/replace
         *  @tparam Start The start index of the range to replace
         *  @tparam End The end index of the range to replace (exclusive)
         *  @tparam Replacement The list of types to insert where the old types were
         */
        template<auto Start, auto End, class ...Replacement>
        using replaceRange = replaceRange_t<TypeArray, detail::deindex_v<Start>, detail::deindex_v<End>, Replacement...>;
        
        /**
         *  @brief Replaces all types that matched a predicate in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/replace
         *  @tparam Predicate The predicate to determine the types to replace
         *  @tparam Replacement The list of types to insert where the old types were
         */
        template<template<class> class Predicate, class ...Replacement>
        using replaceIf = TypeArray<>;
        
        /**
         *  @brief Replaces all types that did not match a predicate in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/replace
         *  @tparam Predicate The predicate to determine the types to retain
         *  @tparam Replacement The list of types to insert where the old type was
         */
        template<template<class> class Predicate, class ...Replacement>
        using replaceIfNot = TypeArray<>;
        
        //--------------------------------------------------------------------------------------------------------------                
        /**
         *  @brief Sorts the types in the TypeArray based on a given comparator.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/sort
         *  @tparam Comparator The comparator class template that the types will be compared against each other
         */
        template<template<class, class> class Comparator>
        using sort = TypeArray;
        
        /**
         *  @brief Reverses the types in the TypeArray.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/reverse
         */
        using reverse = TypeArray;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Gives back a new TypeArray with all types mapped to the given mapper.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/map
         *  @tparam Mapper The mapper class template that will transform every type
         */
        template<template<class> class Mapper>
        using map = TypeArray<>;
        
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
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray_empty/TypeArray
         */
        constexpr TypeArray() noexcept = default;
    };
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Specifies how the types that are deduced from constructing a TypeArray should be given to the parameter
     *         list of the TypeArray.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/DeductionPolicy
     *  @tparam Id The internal ID of the deduction policy
     */
    template<std::size_t Id>
    struct DeductionPolicy {};
    
    /**
     *  @brief Specifies that all types deduced from constructing a TypeArray should be decayed first before given
     *         to the TypeArray.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/DeductionPolicy%23tabber-decay
     */
    using deductionPolicyDecay = DeductionPolicy<0>;
    
    /**
     *  @brief Specifies that all types deduced from constructing a TypeArray should be stripped off all
     *         type modifications first before given to the TypeArray.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/DeductionPolicy%23tabber-strip
     */
    using deductionPolicyStrip = DeductionPolicy<1>;
    
    /**
     *  @brief Specifies that all types deduced from constructing a TypeArray should be mapped to a different type
     *         first before given to the TypeArray.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/DeductionPolicy%23tabber-map
     *  @tparam Mapper The mapper class template that will transform every type
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
     *  @tparam Mapper The mapper class template that will transform every type
     */
    template<template<class> class Mapper>
    constexpr inline auto deductionPolicyMap_v = deductionPolicyMap<Mapper>{};
    
    //------------------------------------------------------------------------------------------------------------------
#if !DOXYGEN
    template<class ...Types>
    TypeArray(deductionPolicyDecay, Types &&...types) -> TypeArray<std::decay_t<Types>...>;
    
    template<class ...Types>
    TypeArray(deductionPolicyStrip, Types &&...types) -> TypeArray<strip_t<Types>...>;
    
    template<template<class> class Mapper, class ...Types>
    TypeArray(deductionPolicyMap<Mapper>, Types &&...types) -> TypeArray<typename Mapper<Types>::type...>;
    
    template<class ...Types>
    TypeArray(Types &&...types) -> TypeArray<Types...>;
#endif

    //==================================================================================================================
    /**
     *  @brief Constructs a variant from a specified [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf)
     *         type and given arguments.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/funcs/makeVariant
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) class template instantiation to transform
     *  @param args The arguments to construct the variant from, see [std::variant constructors](https://en.cppreference.com/w/cpp/utility/variant/variant)
     *  @return A std::variant created from the given arguments.
     */
    template<class T, class ...Args>
    constexpr inline static auto makeVariant(Args &&...args)
        noexcept(noexcept(detail::makeVariant(T{}, std::forward<Args>(args)...)))
    {
        return detail::makeVariant(T{}, std::forward<Args>(args)...);
    }
    
    /**
     *  @brief Constructs an array with all types from the given [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf)
     *         type with each element being a variant constructed from the type given at the specified position.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/funcs/makeVarArray
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) class template instantiation to transform
     *  @param args The arguments passed to each variant in the array (via std::in_place_type_t), see [std::variant constructors](https://en.cppreference.com/w/cpp/utility/variant/variant)
     *  @return A std::array containing as many variants as types in the type list, with each variant constructed with the type at the same position as in the array.
     */
    template<class T, class ...Args>
    constexpr inline static auto makeVarArray(Args &&...args)
         noexcept(noexcept(detail::makeVarArray(T{}, std::forward<Args>(args)...)))
    {
        return detail::makeVarArray(T{}, std::forward<Args>(args)...);
    }
    
    /**
     *  @brief Calls a callback for each type given in a [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf)
     *         type.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/funcs/forEach
     *  @param start An extrait::TypeIteratorBase pointing to the start of the range
     *  @param end An extrait::TypeIteratorBase pointing to the end of the range (exclusive)
     *  @param fn The invocable to execute for each type
     *  @return If the given invocable returns a value this will return a std::array with all the results of each invocation, otherwise void.
     */
    template<class T, class U, class Fn>
    constexpr inline static auto forEach(T start, U end, Fn &&fn)
         noexcept(noexcept(detail::forEach(start, end, std::forward<Fn>(fn))))
    {
        return detail::forEach(start, end, std::forward<Fn>(fn));
    }
    
    /**
     *  @brief Calls a callback for all types given in a [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf)
     *         type at once with a parameter pack.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/funcs/apply
     *  @param start An extrait::TypeIteratorBase pointing to the start of the range
     *  @param end An extrait::TypeIteratorBase pointing to the end of the range (exclusive)
     *  @param fn The invocable to execute for the parameter pack
     *  @return If the given invocable returns a value this will return that value, otherwise void.
     */
    template<class T, class U, class Fn>
    constexpr inline static auto apply(T start, U end, Fn &&fn)
         noexcept(noexcept(detail::apply(start, end, std::forward<Fn>(fn))))
    {
        return detail::apply(start, end, std::forward<Fn>(fn));
    }
}
