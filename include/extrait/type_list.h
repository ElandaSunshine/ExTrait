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
    @file   type_list.h
    @date   30, April 2024
    
    ===============================================================
 */

#pragma once

#include "detail/type_list_impl.h"



namespace extrait
{
    //==================================================================================================================
    /**
     *  @brief An alias for int, having enough room for indexing template arguments and negative values for
     *         out of range purposes.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/type-list%23index-helpers-index_t
     */
    using index_t = detail::index_t;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief An alias for std::integral_constant with extrait::index_t as type.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/type-list%23index-helpers-endOfTypeList
     */
    template<index_t Index>
    using indexConstant = std::integral_constant<index_t, Index>;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Denoting the end of a type list.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/type-list%23index-helpers-indexConstant
     */
    constexpr inline index_t endOfTypeList = -1;
    
    //==================================================================================================================
    /**
     *  @brief Determines whether a given type is an instantiation of a type list conformant class template.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/hasTypeList
     *  @tparam T The type to check
     */
    template<class T>
    struct hasTypeList : detail::hasTypeList<T> {};
    
    /**
     *  @brief Type helper for extrait::hasTypeList.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/hasTypeList
     *  @tparam T The type to check
     */
    template<class T>
    constexpr inline bool hasTypeList_v = hasTypeList<T>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines whether two types instantiate the same class template.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/sameClassTemplate
     *  @tparam T The type to compare against U
     *  @tparam U The type to compare against T
     */
    template<class T, class U>
    struct sameClassTemplate : detail::sameClassTemplate<T, U> {};
    
    /**
     *  @brief Type helper for extrait::sameClassTemplate.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/sameClassTemplate
     *  @tparam T The type to compare against U
     *  @tparam U The type to compare against T
     */
    template<class T, class U>
    constexpr inline bool sameClassTemplate_v = sameClassTemplate<T, U>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines whether two class template type lists are exactly the same.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/sameTemplateArguments
     *  @tparam T The type to compare against U
     *  @tparam U The type to compare against T
     */
    template<class T, class U>
    struct sameTemplateArguments : detail::sameTemplateArguments<T, U> {};
    
    /**
     *  @brief Type helper for extrait::sameTemplateArguments.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/sameTemplateArguments
     *  @tparam T The type to compare against U
     *  @tparam U The type to compare against T
     */
    template<class T, class U>
    constexpr inline bool sameTemplateArguments_v = sameTemplateArguments<T, U>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines whether a type list contains a certain type.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/contains
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Key The type to find
     */
    template<class T, class Key>
    struct contains : detail::contains<T, Key> {};
    
    /**
     *  @brief Type helper for extrait::contains.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/contains
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Key The type to find
     */
    template<class T, class Key>
    constexpr inline bool contains_v = contains<T, Key>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines whether a given type list is empty.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/isEmpty
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to evaluate
     */
    template<class T>
    struct isEmpty : detail::isEmpty<T> {};
    
    /**
     *  @brief Type helper for extrait::isEmpty.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/isEmpty
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to evaluate
     */
    template<class T>
    constexpr inline bool isEmpty_v = isEmpty<T>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines whether a given type list is empty.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/isEmpty
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to evaluate
     */
    template<class T>
    struct isEmptyInstantiated : detail::isEmptyInstantiated<T> {};
    
    /**
     *  @brief Type helper for extrait::isEmptyInstantiated.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/isEmpty
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to evaluate
     */
    template<class T>
    constexpr inline bool isEmptyInstantiated_v = isEmptyInstantiated<T>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines whether a type list starts with a set of types.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/startsWith
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Types The types to find at the beginning of the type list
     */
    template<class T, class ...Types>
    struct startsWith : detail::startsWith<T, Types...> {};
    
    /**
     *  @brief Type helper for extrait::startsWith.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/startsWith
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Types The types to find at the beginning of the type list
     */
    template<class T, class ...Types>
    constexpr inline bool startsWith_v = startsWith<T, Types...>::value;
    
    //.............
    /**
     *  @brief Determines whether a type list ends with a set of types.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/startsWith
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Types The types to find at the end of the type list
     */
    template<class T, class ...Types>
    struct endsWith : detail::endsWith<T, Types...> {};
    
    /**
     *  @brief Type helper for extrait::endsWith.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/startsWith
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Types The types to find at the end of the type list
     */
    template<class T, class ...Types>
    constexpr inline bool endsWith_v = endsWith<T, Types...>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines the number of types that matched a predicate.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/match
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Predicate The predicate class template to match against the types in the type list
     */
    template<class T, template<class> class Predicate>
    struct match : detail::match<T, Predicate, false> {};
    
    /**
     *  @brief Type helper for extrait::match.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/match
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Predicate The predicate class template to match against the types in the type list
     */
    template<class T, template<class> class Predicate>
    constexpr inline std::size_t match_v = match<T, Predicate>::value;
    
    //.............
    /**
     *  @brief Determines the number of types did not match a predicate.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/match
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Predicate The predicate class template to match against the types in the type list
     */
    template<class T, template<class> class Predicate>
    struct mismatch : detail::match<T, Predicate, true> {};
    
    /**
     *  @brief Type helper for extrait::mismatch.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/match
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Predicate The predicate class template to match against the types in the type list
     */
    template<class T, template<class> class Predicate>
    constexpr inline std::size_t mismatch_v = mismatch<T, Predicate>::value;
    
    //.............
    /**
     *  @brief Determines if any type matched a predicate.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/match
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Predicate The predicate class template to match against the types in the type list
     */
    template<class T, template<class> class Predicate>
    struct matchAny : std::bool_constant<(match_v<T, Predicate> > 0)> {};
    
    /**
     *  @brief Type helper for extrait::matchAny.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/match
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Predicate The predicate class template to match against the types in the type list
     */
    template<class T, template<class> class Predicate>
    constexpr inline bool matchAny_v = matchAny<T, Predicate>::value;
    
    //.............
    /**
     *  @brief Determines if all types matched a predicate.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/match
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Predicate The predicate class template to match against the types in the type list
     */
    template<class T, template<class> class Predicate>
    struct matchAll : std::bool_constant<(match_v<T, Predicate> == detail::length<T>::value)> {};
    
    /**
     *  @brief Type helper for extrait::matchAll.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/match
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Predicate The predicate class template to match against the types in the type list
     */
    template<class T, template<class> class Predicate>
    constexpr inline bool matchAll_v = matchAll<T, Predicate>::value;
    
    //.............
    /**
     *  @brief Determines if no types matched a predicate.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/match
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Predicate The predicate class template to match against the types in the type list
     */
    template<class T, template<class> class Predicate>
    struct matchNone : std::bool_constant<(match_v<T, Predicate> == 0)> {};
    
    /**
     *  @brief Type helper for extrait::matchNone.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/match
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Predicate The predicate class template to match against the types in the type list
     */
    template<class T, template<class> class Predicate>
    constexpr inline bool matchNone_v = matchNone<T, Predicate>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines the index of the first matching type found in a type list.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/indexOf
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Key The type to find in the type list
     */
    template<class T, class Key>
    struct indexOf : detail::indexOf<T, Key> {};
    
    /**
     *  @brief Type helper for extrait::indexOf.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/indexOf
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Key The type to find in the type list
     */
    template<class T, class Key>
    constexpr inline index_t indexOf_v = indexOf<T, Key>::value;
    
    //.............
    /**
     *  @brief Determines the index of the last matching type found in a type list.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/indexOf
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Key The type to find in the type list
     */
    template<class T, class Key>
    struct lastIndexOf : detail::lastIndexOf<T, Key> {};
    
    /**
     *  @brief Type helper for extrait::lastIndexOf.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/indexOf
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to search in
     *  @tparam Key The type to find in the type list
     */
    template<class T, class Key>
    constexpr inline index_t lastIndexOf_v = lastIndexOf<T, Key>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Queries the length of a type list.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/length
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to query
     */
    template<class T>
    struct length : detail::length<T> {};
    
    /**
     *  @brief Type helper for extrait::length.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/length
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to query
     */
    template<class T>
    constexpr inline int length_v = length<T>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Transfers the type list of an instantiation to a different class template.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/convert
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to convert
     *  @tparam U A [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) class template to convert to
     */
    template<class T, template<class...> class U>
    struct convert : detail::convert<T, U> {};
    
    /**
     *  @brief Type helper for extrait::convert.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/convert
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) type to convert
     *  @tparam U A [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) class template to convert to
     */
    template<class T, template<class...> class U>
    using convert_t = typename convert<T, U>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Re-instantiates a class template instantiation with new template arguments.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/reinstantiate
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to re-instantiate
     *  @tparam Types A list of types to re-instantiate T with
     */
    template<class T, class ...Types>
    struct reinstantiate : detail::reinstantiate<T, Types...> {};
    
    /**
     *  @brief Type helper for extrait::reinstantiate.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/reinstantiate
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to re-instantiate
     *  @tparam Types A list of types to re-instantiate T with
     */
    template<class T, class ...Types>
    using reinstantiate_t = typename reinstantiate<T, Types...>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Reverse a type list so that all types appear in opposite direction.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/reverse
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     */
    template<class T>
    struct reverse : detail::reverse<T> {};
    
    /**
     *  @brief Type helper for extrait::reverse.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/reverse
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     */
    template<class T>
    using reverse_t = typename reverse<T>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Instantiates a new type list with a sub-range of the original type list.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/sublist
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Start The start index of the sub-range
     *  @tparam End The end index of the sub-range (exclusive)
     */
    template<class T, index_t Start, index_t End>
    struct sublist : detail::sublist<T, Start, End> {};
    
    /**
     *  @brief Type helper for extrait::sublist.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/sublist
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Start The start index of the sub-range
     *  @tparam End The end index of the sub-range (exclusive)
     */
    template<class T, index_t Start, index_t End>
    using sublist_t = typename sublist<T, Start, End>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Merges a set of at least one type list into one.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/join
     *  @tparam T A [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) class template that adapts all the types
     *  @tparam U A list of [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiations which parameters should be adapted
     */
    template<template<class...> class T, class ...U>
    struct join : detail::join<T, U...> {};
    
    /**
     *  @brief Type helper for extrait::join.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/join#
     *  @tparam T A [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) class template that adapts all the types
     *  @tparam U A list of [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiations which parameters should be adapted
     */
    template<template<class...> class T, class ...U>
    using join_t = typename join<T, U...>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Gets a type, inside a type list, at a certain index.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/get
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to search
     *  @tparam I The index of the type to get
     */
    template<class T, index_t I>
    struct get : detail::get<T, I> {};
    
    /**
     *  @brief Type helper for extrait::get.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/get
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to search
     *  @tparam I The index of the type to get
     */
    template<class T, index_t I>
    using get_t = typename get<T, I>::type;
    
    //.............
    /**
     *  @brief Gets the first type from a type list.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/get
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to search
     */
    template<class T>
    struct first : get<T, 0> {};
    
    /**
     *  @brief Type helper for extrait::first.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/get
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to search
     */
    template<class T>
    using first_t = typename first<T>::type;
    
    //.............
    /**
     *  @brief Gets the last type from a type list.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/get
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to search
     */
    template<class T>
    struct last : get<T, (length_v<T> - 1)> {};
    
    /**
     *  @brief Type helper for extrait::last.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/get
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to search
     */
    template<class T>
    using last_t = typename last<T>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Gets the type that was found to be the minimum among the other types, based on a given comparator.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/minType
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to search
     *  @tparam Comparator The comparator class template that the types will be compared against each other with
     */
    template<class T, template<class, class> class Comparator>
    struct minType : detail::minmax<T, Comparator, false> {};
    
    /**
     *  @brief Type helper for extrait::minType.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/minType
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to search
     *  @tparam Comparator The comparator class template that the types will be compared against each other with
     */
    template<class T, template<class, class> class Comparator>
    using minType_t = typename minType<T, Comparator>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Gets the type that was found to be the maximum among the other types, based on a given comparator.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/minType
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to search
     *  @tparam Comparator The comparator class template that the types will be compared against each other with
     */
    template<class T, template<class, class> class Comparator>
    struct maxType : detail::minmax<T, Comparator, true> {};
    
    /**
     *  @brief Type helper for extrait::maxType.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/minType
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to search
     *  @tparam Comparator The comparator class template that the types will be compared against each other with
     */
    template<class T, template<class, class> class Comparator>
    using maxType_t = typename maxType<T, Comparator>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Replaces the first occurrence of a type that matches a given type.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/replace
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Key The type to replace
     *  @tparam Replacement The list of types to insert where the old type was
     */
    template<class T, class Key, class ...Replacement>
    struct replace : detail::replace<T, Key, Replacement...> {};
    
    /**
     *  @brief Type helper for extrait::replace.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/replace
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Key The type to replace
     *  @tparam Replacement The list of types to insert where the old type was
     */
    template<class T, class Key, class ...Replacement>
    using replace_t = typename replace<T, Key, Replacement...>::type;
    
    //.............
    /**
     *  @brief Replaces all types that match a given type.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/replace
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Key The type to replace
     *  @tparam Replacement The list of types to insert where the old types were
     */
    template<class T, class Key, class ...Replacement>
    struct replaceAll : detail::replaceAll<T, Key, Replacement...> {};
    
    /**
     *  @brief Type helper for extrait::replaceAll.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/replace
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Key The type to replace
     *  @tparam Replacement The list of types to insert where the old types were
     */
    template<class T, class Key, class ...Replacement>
    using replaceAll_t = typename replaceAll<T, Key, Replacement...>::type;
    
    //.............
    /**
     *  @brief Replaces a type inside a type list at the specified index.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/replace
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam I The index of the type to replace
     *  @tparam Replacement The list of types to insert where the old type was 
     */
    template<class T, index_t I, class ...Replacement>
    struct replaceAt : detail::replaceAt<T, I, Replacement...> {};
    
    /**
     *  @brief Type helper for extrait::replaceAt.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/replace
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam I The index of the type to replace
     *  @tparam Replacement The list of types to insert where the old type was
     */
    template<class T, index_t I, class ...Replacement>
    using replaceAt_t = typename replaceAt<T, I, Replacement...>::type;
    
    //.............
    /**
     *  @brief Replaces the first type in a type list.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/replace
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Replacement The list of types to insert where the old type was
     */
    template<class T, class ...Replacement>
    struct replaceFirst : replaceAt<T, 0, Replacement...> {};
    
    /**
     *  @brief Type helper for extrait::replaceFirst.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/replace
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Replacement The list of types to insert where the old type was
     */
    template<class T, class ...Replacement>
    using replaceFirst_t = typename replaceFirst<T, Replacement...>::type;
    
    //.............
    /**
     *  @brief Replaces the last type in a type list.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/replace
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Replacement The list of types to insert where the old type was
     */
    template<class T, class ...Replacement>
    struct replaceLast : replaceAt<T, (length_v<T> - 1), Replacement...> {};
    
    /**
     *  @brief Type helper for extrait::replaceLast.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/replace
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Replacement The list of types to insert where the old type was
     */
    template<class T, class ...Replacement>
    using replaceLast_t = typename replaceLast<T, Replacement...>::type;
    
    //.............
    /**
     *  @brief Replaces exactly one type with another at a specified index.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/replace
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam I The index of the type to replace
     *  @tparam Replacement The type to insert where the old type was
     */
    template<class T, index_t I, class Replacement>
    struct set : replaceAt<T, I, Replacement> {};
    
    /**
     *  @brief Type helper for extrait::set.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/replace
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam I The index of the type to replace
     *  @tparam Replacement The type to insert where the old type was
     */
    template<class T, index_t I, class Replacement>
    using set_t = typename set<T, I, Replacement>::type;
    
    //.............
    /**
     *  @brief Replaces a range of types inside a type list.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/replace
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Start The start index of the range to replace
     *  @tparam End The end index of the range to replace (exclusive)
     *  @tparam Replacement The list of types to insert where the old types were
     */
    template<class T, index_t Start, index_t End, class ...Replacement>
    struct replaceRange : detail::replaceRange<T, Start, End, Replacement...> {};
    
    /**
     *  @brief Type helper for extrait::replaceRange.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/replace
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Start The start index of the range to replace
     *  @tparam End The end index of the range to replace (exclusive)
     *  @tparam Replacement The list of types to insert where the old types were
     */
    template<class T, index_t Start, index_t End, class ...Replacement>
    using replaceRange_t = typename replaceRange<T, Start, End, Replacement...>::type;
    
    //.............
    /**
     *  @brief Replaces all types inside a type list that matched a predicate.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/replace
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Predicate The predicate to determine the types to replace
     *  @tparam Replacement The list of types to insert where the old types were
     */
    template<class T, template<class> class Predicate, class ...Replacement>
    struct replaceIf : detail::replaceIf<T, Predicate, false, Replacement...> {};
    
    /**
     *  @brief Type helper for extrait::replaceIf.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/replace
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Predicate The predicate to determine the types to replace
     *  @tparam Replacement The list of types to insert where the old types were
     */
    template<class T, template<class> class Predicate, class ...Replacement>
    using replaceIf_t = typename replaceIf<T, Predicate, Replacement...>::type;
    
    //.............
    /**
     *  @brief Replaces all types inside a type list that did not match a predicate.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/replace
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Predicate The predicate to determine the types to replace
     *  @tparam Replacement The list of types to insert where the old types were
     */
    template<class T, template<class> class Predicate, class ...Replacement>
    struct replaceIfNot : detail::replaceIf<T, Predicate, true, Replacement...> {};
    
    /**
     *  @brief Type helper for extrait::replaceIfNot.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/replace
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Predicate The predicate to determine the types to replace
     *  @tparam Replacement The list of types to insert where the old types were
     */
    template<class T, template<class> class Predicate, class ...Replacement>
    using replaceIfNot_t = typename replaceIfNot<T, Predicate, Replacement...>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Removes the first occurrence of a type that matches a given type.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/remove
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Key The type to remove
     */
    template<class T, class Key>
    struct remove : detail::remove<T, Key> {};
    
    /**
     *  @brief Type helper for extrait::remove.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/remove
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Key The type to remove
     */
    template<class T, class Key>
    using remove_t = typename remove<T, Key>::type;
    
    //.............
    /**
     *  @brief Removes all types from a type list that match a given type.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/remove
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Key The type to remove
     */
    template<class T, class Key>
    struct removeAll : detail::removeAll<T, Key> {};
    
    /**
     *  @brief Type helper for extrait::removeAll.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/remove
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Key The type to remove
     */
    template<class T, class Key>
    using removeAll_t = typename removeAll<T, Key>::type;
    
    //.............
    /**
     *  @brief Removes a type from a type list at the specified index.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/remove
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam I The index of the type to remove
     */
    template<class T, index_t I>
    struct removeAt : detail::removeAt<T, I> {};
    
    /**
     *  @brief Type helper for extrait::removeAt.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/remove
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam I The index of the type to remove
     */
    template<class T, index_t I>
    using removeAt_t = typename removeAt<T, I>::type;
    
    //.............
    /**
     *  @brief Removes the first type from a type list.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/remove
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     */
    template<class T>
    struct removeFirst : removeAt<T, 0> {};
    
    /**
     *  @brief Type helper for extrait::removeFirst.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/remove
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     */
    template<class T>
    using removeFirst_t = typename removeFirst<T>::type;
    
    //.............
    /**
     *  @brief Removes the last type from a type list.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/remove
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     */
    template<class T>
    struct removeLast : removeAt<T, (length_v<T> - 1)> {};
    
    /**
     *  @brief Type helper for extrait::removeLast.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/remove
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     */
    template<class T>
    using removeLast_t = typename removeLast<T>::type;
    
    //.............
    /**
     *  @brief Removes a range of types from a type list.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/remove
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Start The start index of the range
     *  @tparam End The end index of the range (exclusive)
     */
    template<class T, index_t Start, index_t End>
    struct removeRange : detail::removeRange<T, Start, End> {};
    
    /**
     *  @brief Type helper for extrait::removeRange.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/remove
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Start The start index of the range
     *  @tparam End The end index of the range (exclusive)
     */
    template<class T, index_t Start, index_t End>
    using removeRange_t = typename removeRange<T, Start, End>::type;
    
    //.............
    /**
     *  @brief Removes all types from a type list that matched a predicate.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/remove
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Predicate The predicate to determine the types to remove
     */
    template<class T, template<class> class Predicate>
    struct removeIf : detail::removeIf<T, Predicate, false> {};
    
    /**
     *  @brief Type helper for extrait::removeIf.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/remove
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Predicate The predicate to determine the types to remove
     */
    template<class T, template<class> class Predicate>
    using removeIf_t = typename removeIf<T, Predicate>::type;
    
    //.............
    /**
     *  @brief Removes all types from a type list that did not match a predicate.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/remove
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Predicate The predicate to determine the types to retain
     */
    template<class T, template<class> class Predicate>
    struct filter : detail::removeIf<T, Predicate, true> {};
    
    /**
     *  @brief Type helper for extrait::filter.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/remove
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Predicate The predicate to determine the types to retain
     */
    template<class T, template<class> class Predicate>
    using filter_t = typename filter<T, Predicate>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Instantiates a new type list with each repeated occurrence of a type removed.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/deduplicate
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     */
    template<class T>
    struct deduplicate : detail::deduplicate<T> {};
    
    /**
     *  @brief Type helper for extrait::deduplicate.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/deduplicate
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     */
    template<class T>
    using deduplicate_t = typename deduplicate<T>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Appends new types to the end of a type list.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/add
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Types The list of types to append
     */
    template<class T, class ...Types>
    struct add : detail::add<T, Types...> {};
    
    /**
     *  @brief Type helper for extrait::add.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/add
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Types The list of types to append
     */
    template<class T, class ...Types>
    using add_t = typename add<T, Types...>::type;
    
    //.............
    /**
     *  @brief Appends new types to the end of a type list if they aren't already contained.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/add
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Types The list of types to append
     */
    template<class T, class ...Types>
    struct addIfAbsent : detail::addIfAbsent<T, Types...> {};
    
    /**
     *  @brief Type helper for extrait::addIfAbsent.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/add
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Types The list of types to append
     */
    template<class T, class ...Add>
    using addIfAbsent_t = typename addIfAbsent<T, Add...>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Inserts a type at a certain index of a type list.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/insert
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam I The index the types should be inserted at
     *  @tparam Types The list of types to insert
     */
    template<class T, index_t I, class ...Types>
    struct insert : detail::insert<T, I, Types...> {};
    
    /**
     *  @brief Type helper for extrait::insert.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/insert
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam I The index the types should be inserted at
     *  @tparam Types The list of types to insert
     */
    template<class T, index_t I, class ...Types>
    using insert_t = typename insert<T, I, Types...>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Left rotates a range of types in a type list.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/rotate
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Start The start index of the range to rotate
     *  @tparam Middle The index of the type to move to the start of the range
     *  @tparam End The end index of the range to rotate (exclusive)
     */
    template<class T, index_t Start, index_t Middle, index_t End>
    struct rotate : detail::rotate<T, Start, Middle, End> {};
    
    /**
     *  @brief Type helper for extrait::rotate.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/rotate
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Start The start index of the range to rotate
     *  @tparam Middle The index of the type to move to the start of the range
     *  @tparam End The end index of the range to rotate (exclusive)
     */
    template<class T, index_t Start, index_t Middle, index_t End>
    using rotate_t = typename rotate<T, Start, Middle, End>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Moves a certain type to a new index inside a type list and rotates the types next to it.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/move
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam I The index of the type to move
     *  @tparam Dest The index of the slot to move the type to (can be one past the end)
     */
    template<class T, index_t I, index_t Dest>
    struct move : detail::move<T, I, Dest> {};
    
    /**
     *  @brief Type helper for extrait::move.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/move
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam I The index of the type to move
     *  @tparam Dest The index of the slot to move the type to (can be one past the end)
     */
    template<class T, index_t I, index_t Dest>
    using move_t = typename move<T, I, Dest>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Moves a certain type to a new index inside a type list without any rotation.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/swap
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam I The index of the type to swap
     *  @tparam Dest The index of the second type to swap with this one
     */
    template<class T, index_t I, index_t Dest>
    struct swap : detail::swap<T, I, Dest> {};
    
    /**
     *  @brief Type helper for extrait::swap.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/swap
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam I The index of the type to swap
     *  @tparam Dest The index of the second type to swap with this one
     */
    template<class T, index_t I, index_t Dest>
    using swap_t = typename swap<T, I, Dest>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Sorts the type list of a class template instantiation.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/sort
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Comparator The comparator class template that the types will be compared against each other with
     */
    template<class T, template<class, class> class Comparator>
    struct sort : detail::sort<T, Comparator> {};
    
    /**
     *  @brief Type helper for extrait::sort.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/sort
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Comparator The comparator class template that the types will be compared against each other with
     */
    template<class T, template<class, class> class Comparator>
    using sort_t = typename sort<T, Comparator>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Transforms the types of a type list based on a given mapper.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/map
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Mapper The mapper class template that will transform every type
     */
    template<class T, template<class> class Mapper>
    struct map : detail::map<T, Mapper> {};
    
    /**
     *  @brief Type helper for extrait::map.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/map
     *  @tparam T The [type list conformant](https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf) instantiation to modify
     *  @tparam Mapper The mapper class template that will transform every type
     */
    template<class T, template<class> class Mapper>
    using map_t = typename map<T, Mapper>::type;
}
