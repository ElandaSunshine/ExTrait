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
     *  @brief An alias for int, used for parameter-list indexing.
     */
    using index_t = detail::index_t;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief An alias for std::integral_constant specialised for index_t.
     */
    template<index_t Index>
    using indexConstant = std::integral_constant<index_t, Index>;
    
    //==================================================================================================================
    /**
     *  @brief A constant initialised to -1, that should indicate the end of a class template parameter-list.
     */
    constexpr inline int endOfTypeList = -1;

    //==================================================================================================================
    /**
     *  @ingroup type_list
     *  @brief Determines whether a given type is an instantiation of a class-template with only types.
     *  
     *  If type T is an instantiation of a class-template with a type-only
     *  parameter-list (regardless if it is empty or not), a static "value" constant will be provided
     *  that evaluates to true, if on the other hand T is a non-class template type or a class template type that
     *  contains at least one non-type template parameter, this evaluates to false.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and so will evaluate to false.
     *  
     *  This can be used to make sure that any of the other parameter-list type traits in this library
     *  is supplied with a valid type.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T Any type
     */
    template<class T>
    struct hasTypeList : detail::hasTypeList<T> {};
    
    /**
     *  @brief Value helper for extrait::hasTypeList.
     */
    template<class T>
    constexpr inline bool hasTypeList_v = hasTypeList<T>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines whether two types instantiate the same template
     *  
     *  If both T and U instantiate the same class template, a static "value" constant will be provided that evaluates
     *  to true, otherwise false.  
     *  If either T or U is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T or U, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T Any valid type-only class template instantiation
     *  @tparam U Any valid type-only class template instantiation
     *  
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, class U>
    struct sameClassTemplate : detail::sameClassTemplate<T, U> {};
    
    /**
     *  @brief Type helper for extrait::sameClassTemplate.
     */
    template<class T, class U>
    constexpr inline bool sameClassTemplate_v = sameClassTemplate<T, U>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines whether two class template parameter-lists are exactly the same.
     *  
     *  If the parameter-list of T and U are exactly equal, by that means, every template argument in T is the same
     *  template argument in U and at the same position, a static "value" constant will be provided that
     *  evaluates to true, otherwise evaluates to false.
     *  
     *  If T or U is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T or U, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T Any valid type-only class template instantiation
     *  @tparam U Any valid type-only class template instantiation
     *  
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, class U>
    struct sameTemplateArguments : detail::sameTemplateArguments<T, U> {};
    
    /**
     *  @brief Value helper for extrait::sameTemplateArguments.
     */
    template<class T, class U>
    constexpr inline bool sameTemplateArguments_v = sameTemplateArguments<T, U>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines whether a parameter-list contains a certain type.
     *  
     *  If type Key could be found at least once in the template parameter-list of type T, a static "value" constant
     *  will be provided that evaluates to true, otherwise evaluates to false.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T   Any valid type-only class template instantiation
     *  @tparam Key Any type that should be found in the parameter-list of instantiation T
     *  
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, class Key>
    struct contains : detail::contains<T, Key> {};
    
    /**
     *  @brief Value helper for extrait::contains.
     */
    template<class T, class Key>
    constexpr inline bool contains_v = contains<T, Key>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines whether a given parameter-list of a class template is empty.
     *  
     *  If any type was found in the parameter-list of type T, a static "value" constant will be provided that
     *  evaluates to false, otherwise evaluates to true.  
     *  In contrast to extrait::isEmptyInstantiated, this will ignore any default template parameters of class template
     *  T and evaluate to true even if the class template contains any default template parameters.  
     *  However, if the template explicity specifies a default template parameter with the same type as what the
     *  defaulted type is, this will also count as empty.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *
     *  @tparam T Any valid type-only class template instantiation
     * 
     *  @see extrait::isEmptyInstantiated
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T>
    struct isEmpty : detail::isEmpty<T> {};
    
    /**
     *  @brief Value helper for extrait::isEmpty.
     */
    template<class T>
    constexpr inline bool isEmpty_v = isEmpty<T>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines whether a given instantiation of a class-template has an empty parameter-list.
     *  
     *  If any type was found in the parameter-list of type T, a static "value" constant will be provided that
     *  evaluates to false, otherwise evaluates to true.  
     *  In contrast to extrait::isEmpty, this will not ignore default template parameters of class template T and
     *  also consider whether the passed in class template instantiation contains any defaulted template parameters.
     *  If, in this case, T represents Type<> and Type has defaulted template parameters, it will not count as empty.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *
     *  @tparam T Any valid type-only class template instantiation
     * 
     *  @see extrait::isEmpty
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T>
    struct isEmptyInstantiated : detail::isEmptyInstantiated<T> {};
    
    /**
     *  @brief Value helper for extrait::isEmptyInstantiated.
     */
    template<class T>
    constexpr inline bool isEmptyInstantiated_v = isEmptyInstantiated<T>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines whether a class template's parameter-list starts with a set of types.
     *  
     *  If the parameter-list of type T starts with the same types as specified in StartTypes and in the same order,
     *  a static "value" constant will be provided that evaluates to true, otherwise evaluates to false.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T          Any valid type-only class template instantiation
     *  @tparam StartTypes A list of types the class template instantiation T's parameter-list should start with
     *  
     *  @see extrait::endsWith
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, class ...StartTypes>
    struct startsWith : detail::startsWith<T, StartTypes...> {};
    
    /**
     *  @brief Value helper for extrait::startsWith.
     */
    template<class T, class ...StartTypes>
    constexpr inline bool startsWith_v = startsWith<T, StartTypes...>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines whether a class template's parameter-list ends with a set of types.
     *  
     *  If the parameter-list of type T ends with the same types as specified in EndTypes and in the
     *  same order (left to right), a static "value" constant will be provided that evaluates to true,
     *  otherwise evaluates to false.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T        Any valid type-only class template instantiation
     *  @tparam EndTypes A list of types the class template instantiation T's parameter-list should end with
     *  
     *  @see extrait::startsWith
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, class ...EndTypes>
    struct endsWith : detail::endsWith<T, EndTypes...> {};
    
    /**
     *  @brief Value helper for extrait::endsWith.
     */
    template<class T, class ...EndTypes>
    constexpr inline bool endsWith_v = endsWith<T, EndTypes...>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines how many of the types in a parameter-list match a predicate.
     *  
     *  Provides a static "value" constant expression that represents the number of types in the parameter-list of
     *  class template instantiation T that matched a given predicate.
     *  
     *  Where Predicate is a class template that takes the currently (one at a time) inspected type from the
     *  parameter-list of class template instantiation T as template argument and provides a static "value" constant
     *  expression that is a bool that determines true if the type should be counted.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T         Any valid type-only class template instantiation
     *  @tparam Predicate A predicate determining whether a type should be counted
     *  
     *  @see extrait::mismatch
     *  @see extrait::matchAny
     *  @see extrait::matchAll
     *  @see extrait::matchNone
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, template<class> class Predicate>
    struct match : detail::match<T, Predicate, false> {};
    
    /**
     *  @brief Value helper for extrait::match.
     */
    template<class T, template<class> class Predicate>
    constexpr inline std::size_t match_v = match<T, Predicate>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines how many of the types in a parameter-list did not match a predicate.
     *  
     *  Provides a static "value" constant expression that represents the number of types in the parameter-list of
     *  class template instantiation T that did not match a given predicate.
     *  
     *  Where Predicate is a class template that takes the currently (one at a time) inspected type from the
     *  parameter-list of class template instantiation T as template argument and provides a static "value" constant
     *  expression that is a bool that determines true if the type should be ignored and thus not counted.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T         Any valid type-only class template instantiation
     *  @tparam Predicate A predicate determining whether a type should be ignored
     *  
     *  @see extrait::match
     *  @see extrait::matchAny
     *  @see extrait::matchAll
     *  @see extrait::matchNone
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, template<class> class Predicate>
    struct mismatch : detail::match<T, Predicate, true> {};
    
    /**
     *  @brief Value helper for extrait::mismatch.
     */
    template<class T, template<class> class Predicate>
    constexpr inline std::size_t mismatch_v = mismatch<T, Predicate>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines if any type in a parameter-list matched a given Predicate.
     *  
     *  Provides a static "value" constant expression that evaluates to true if at least one type in the parameter-list
     *  of class template instantiation T matched Predicate.  
     *  This will always return false if the given parameter-list is empty.
     *  
     *  Where Predicate is a class template that takes the currently (one at a time) inspected type from the
     *  parameter-list of class template instantiation T as template argument and provides a static "value" constant
     *  expression that is a bool that determines whether a type matches.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T         Any valid type-only class template instantiation
     *  @tparam Predicate A predicate determining whether a type has matched
     *  
     *  @see extrait::match
     *  @see extrait::mismatch
     *  @see extrait::matchAll
     *  @see extrait::matchNone
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, template<class> class Predicate>
    struct matchAny : detail::matchAny<T, Predicate> {};
    
    /**
     *  @brief Value helper for extrait::matchAny.
     */
    template<class T, template<class> class Predicate>
    constexpr inline bool matchAny_v = matchAny<T, Predicate>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines if all types in a parameter-list matched a given Predicate.
     *  
     *  Provides a static "value" constant expression that evaluates to true if all types in the parameter-list
     *  of class template instantiation T matched Predicate.  
     *  This will always return true if the given parameter-list is empty.
     *  
     *  Where Predicate is a class template that takes the currently (one at a time) inspected type from the
     *  parameter-list of class template instantiation T as template argument and provides a static "value" constant
     *  expression that is a bool that determines whether a type matches.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T         Any valid type-only class template instantiation
     *  @tparam Predicate A predicate determining whether a type has matched
     *  
     *  @see extrait::match
     *  @see extrait::mismatch
     *  @see extrait::matchAny
     *  @see extrait::matchNone
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, template<class> class Predicate>
    struct matchAll : std::bool_constant<(match_v<T, Predicate> == detail::length<T>::value)> {};
    
    /**
     *  @brief Value helper for extrait::matchAll.
     */
    template<class T, template<class> class Predicate>
    constexpr inline bool matchAll_v = matchAll<T, Predicate>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines if none of the types in a parameter-list matched a given Predicate.
     *  
     *  Provides a static "value" constant expression that evaluates to true if not a single type in the parameter-list
     *  of class template instantiation T matched Predicate, that means, if all types returned false, this is true.  
     *  This will always return true if the given parameter-list is empty.
     *  
     *  Where Predicate is a class template that takes the currently (one at a time) inspected type from the
     *  parameter-list of class template instantiation T as template argument and provides a static "value" constant
     *  expression that is a bool that determines whether a type matches.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T         Any valid type-only class template instantiation
     *  @tparam Predicate A predicate determining whether a type has matched
     *  
     *  @see extrait::match
     *  @see extrait::mismatch
     *  @see extrait::matchAny
     *  @see extrait::matchAll
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, template<class> class Predicate>
    struct matchNone : std::bool_constant<(match_v<T, Predicate> == 0)> {};
    
    /**
     *  @brief Value helper for extrait::matchNone.
     */
    template<class T, template<class> class Predicate>
    constexpr inline bool matchNone_v = matchNone<T, Predicate>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines the index of the first matching type inside a template parameter-list.
     *  
     *  If type Key was found to be in the parameter-list of class template instantiation T, then a static "value"
     *  constant will be provided that gives back the 0-based index of that type inside the parameter-list.  
     *  If, however, the type could not be found, the constant will evaluate to extrait::endOfTypeList.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T   Any valid type-only class template instantiation
     *  @tparam Key Any type the index should be found for in the parameter-list of instantiation T
     *  
     *  @see extrait::lastIndexOf
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, class Key>
    struct indexOf : detail::indexOf<T, Key> {};
    
    /**
     *  @brief Value helper for extrait::indexOf.
     */
    template<class T, class Key>
    constexpr inline index_t indexOf_v = indexOf<T, Key>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines the index of the last matching type inside a template parameter-list.
     *  
     *  If type Key was found to be in the parameter-list of class template instantiation T, then a static "value"
     *  constant will be provided that gives back the 0-based index of the last match of that type inside the
     *  parameter-list.  
     *  If, however, the type could not be found, the constant will evaluate to extrait::endOfTypeList.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T   Any valid type-only class template instantiation
     *  @tparam Key Any type the last index should be found for in the parameter-list of instantiation T
     *  
     *  @see extrait::lastIndexOf
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, class Key>
    struct lastIndexOf : detail::lastIndexOf<T, Key> {};
    
    /**
     *  @brief Value helper for extrait::lastIndexOf.
     */
    template<class T, class Key>
    constexpr inline index_t lastIndexOf_v = lastIndexOf<T, Key>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Determines the number of template arguments inside a template parameter-list.
     *  
     *  Provides a static constant "value" that determines the number of template parameters in the parameter-list
     *  of class template instantiation T.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T Any valid type-only class template instantiation
     *  
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T>
    struct length : detail::length<T> {};
    
    /** 
     *  @brief Value helper for extrait::length.
     */
    template<class T>
    constexpr inline int length_v = length<T>::value;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Unifies a list of template parameter-lists into one template parameter-list.
     *  
     *  Provides a member alias "type" that is a unification of all template arguments of every class template
     *  instantiation of U and instantiates class template T with all of these arguments.  
     *  The order is as given to template parameter U where all of the template arguments of all the given
     *  class template instantiations of U are adopted in appearance order to class template T, from left to right.
     *  
     *  If any of the class template instantiations of U is not a class template or is a class template with at least
     *  one non-type template parameter, compilation will fail.
     *  
     *  Any modification to any of the class template instantiations of U, such as pointer, reference,
     *  array or cv-qualification of the original type, will render the type a non-class template type and
     *  compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T Any valid type-only class template that can take enough arguments
     *  @tparam U A list of class template instantiations that should be joined into a new instance of class template T
     *  
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<template<class...> class T, class ...U>
    struct join : detail::join<T, U...> {};
    
    /** 
     *  @brief Type helper for extrait::join.
     */
    template<template<class...> class T, class ...U>
    using join_t = typename join<T, U...>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Takes the parameter-list of a class template instantiation and applies it to another class template.
     *  
     *  Provides a member alias "type" that is a copy of the parameter-list of class template instantiation T
     *  and instantiates the class template U with that parameter-list.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T Any valid type-only class template instantiation
     *  @tparam U Any class template that can take enough arguments
     *  
     *  @see extrait::reinstantiate
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, template<class...> class U>
    struct convert : detail::convert<T, U> {};
    
    /**
     *  @brief Type helper for extrait::convert.
     */
    template<class T, template<class...> class U>
    using convert_t = typename convert<T, U>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Reinstantiates an existing class template instantiation with a different parameter-list.
     *  
     *  Provides a member alias "type" that is a new instantiation of class template of instantiation T with
     *  a new list of template arguments Types.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T     Any valid type-only class template instantiation
     *  @tparam Types Any list of types that should make up the new parameter-list of class template of instantiation T
     *  
     *  @see extrait::convert
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, class ...Types>
    struct reinstantiate : detail::reinstantiate<T, Types...> {};
    
    /**
     *  @brief Type helper for extrait::reinstantiate.
     */
    template<class T, class ...Types>
    using reinstantiate_t = typename reinstantiate<T, Types...>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Reverses the types in a given template parameter-list.
     *  
     *  Provides a member alias "type" that is a copy of the original parameter-list of class template instantiation T
     *  with all template arguments reversed and re-instantiated as new instantiation of class template T.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T Any valid type-only class template instantiation
     *  
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T>
    struct reverse : detail::reverse<T> {};
    
    /**
     *  @brief Type helper for extrait::reverse.
     */
    template<class T>
    using reverse_t = typename reverse<T>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Cuts a template parameter-list to a specified range.
     *  
     *  Provides a member alias "type" that is a copy of the original parameter-list of class template instantiation T
     *  with only the template arguments remaining that were found in the given range [Start, End], where Start is
     *  a 0-based index referring to the first template argument inside the parameter-list of T that should be included
     *  in the resulting parameter-list and End is the last index of the range but excluding that element.
     *  If Start and End refer to the same index in the parameter-list, an empty instantiation of T will be provided.
     *  
     *  If Start or End is larger than the number of template arguments in the template parameter-list of T or Start
     *  is bigger than End, then compilation will fail.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T     Any valid type-only class template instantiation
     *  @tparam Start The start index of the range to keep
     *  @tparam End   The end index of the range to keep (exclusive)
     *  
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, index_t Start, index_t End>
    struct sublist : detail::sublist<T, Start, End> {};
    
    /**
     *  @brief Type helper for extrait::sublist.
     */
    template<class T, index_t Start, index_t End>
    using sublist_t = typename sublist<T, Start, End>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Gets a type at a certain index inside a template parameter-list.
     *  
     *  Provides a member alias "type" that refers to the type at the specified index I,
     *  starting at 0 for the first type, inside the parameter-list of class template instantiation T.  
     *  A class template of instantiation T with default template parameters will count these default template
     *  parameters as part of the parameter-list.
     *  
     *  If I is not less than the number of template arguments in the template parameter-list of T,
     *  then compilation will fail.  
     *  For an empty class template instantiation of T, index will always be out of bounds and so cause compilation
     *  to fail.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T Any valid type-only class template instantiation
     *  @tparam I The index of the type to get
     *  
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, index_t I>
    struct get : detail::get<T, I> {};
    
    /**
     *  @brief Type helper for extrait::get.
     */
    template<class T, index_t I>
    using get_t = typename get<T, I>::type;
    
    /**
     *  @brief Type helper that refers to the first template argument in the template parameter-list of T.
     */
    template<class T>
    using first_t = get_t<T, 0>;
    
    /**
     *  @brief Type helper that refers to the last template argument in the template parameter-list of T.
     */
    template<class T>
    using last_t = get_t<T, (length_v<T> - 1)>;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Gets the minimum type in a parameter-list.
     *  
     *  Provides a member alias "type" that is one of the types that was compared to all other types in the
     *  parameter-list of class template instantiation T and based on the given type Comparator, was evaluated to be
     *  the smallest among them.
     *  
     *  Where Comparator is a class template that takes two types as arguments, where the first argument is a type that
     *  in the current comparison pass is compared to the key type and the second argument is the key type that is
     *  compared to the type in the next comparison pass, this class template must provide a static constant expression
     *  "value" that determines true if the first argument is smaller than the second argument (key).  
     *  If there are several types with an equal result, the first encountered type will be taken.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T          Any valid type-only class template instantiation
     *  @tparam Comparator Any type satisfying a valid comparing type
     *  
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, template<class, class> class Comparator>
    struct minType : detail::minmax<T, Comparator, false> {};
    
    /**
     *  @brief Type helper for extrait::minType.
     */
    template<class T, template<class, class> class Comparator>
    using minType_t = typename minType<T, Comparator>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Gets the maximum type in a parameter-list.
     *  
     *  Provides a member alias "type" that is one of the types that was compared to all other types in the
     *  parameter-list of class template instantiation T and based on the given type Comparator, was evaluated to be
     *  the biggest among them.
     *  
     *  Where Comparator is a class template that takes two types as arguments, where the first argument is a type that
     *  in the current comparison pass is compared to the key type and the second argument is the key type that is
     *  compared to the type in the next comparison pass, this class template must provide a static constant expression
     *  "value" that determines true if the first argument is smaller than the second argument (key).  
     *  If there are several types with an equal result, the first encountered type will be taken.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T          Any valid type-only class template instantiation
     *  @tparam Comparator Any type satisfying a valid comparing type
     *  
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, template<class, class> class Comparator>
    struct maxType : detail::minmax<T, Comparator, true> {};
    
    /**
     *  @brief Type helper for extrait::maxType.
     */
    template<class T, template<class, class> class Comparator>
    using maxType_t = typename maxType<T, Comparator>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Replaces the first matching type in a template parameter-list with a list of replacement types.
     *  
     *  If type Key could be found in the parameter-list of class template instantiation T, will replace the first
     *  occurrence of this type with the given list of types Replacement and provide a member alias "type" for an
     *  instantiation of class template T with the new parameter-list, otherwise T.  
     *  If Replacement does not provide any types, compilation will fail.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T           Any valid type-only class template instantiation
     *  @tparam Key         Any type that should be found to be replaced in the parameter-list of instantiation T
     *  @tparam Replacement A list of types the found type should be replaced with (preserving order)
     *  
     *  @see extrait::replaceAll
     *  @see extrait::replaceAt
     *  @see extrait::replaceRange
     *  @see extrait::replaceIf
     *  @see extrait::replaceIfNot
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, class Key, class ...Replacement>
    struct replace : detail::replace<T, Key, Replacement...> {};
    
    /**
     *  @brief Type helper for extrait::replace.
     */
    template<class T, class Key, class ...Replacement>
    using replace_t = typename replace<T, Key, Replacement...>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Replaces all matching types in a template parameter-list with a list of replacement types.
     *  
     *  If type Key could be found in the parameter-list of class template instantiation T, will replace all
     *  occurrences of this type with the given list of types Replacement and provide a member alias "type" for an
     *  instantiation of class template T with the new parameter-list, otherwise T.  
     *  If Replacement does not provide any types, compilation will fail.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T           Any valid type-only class template instantiation
     *  @tparam Key         Any type that should be found to be replaced in the parameter-list of instantiation T
     *  @tparam Replacement A list of types the found type should be replaced with (preserving order)
     *  
     *  @see extrait::replace
     *  @see extrait::replaceAt
     *  @see extrait::replaceRange
     *  @see extrait::replaceIf
     *  @see extrait::replaceIfNot
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, class Key, class ...Replacement>
    struct replaceAll : detail::replaceAll<T, Key, Replacement...> {};
    
    /**
     *  @brief Type helper for extrait::replaceAll.
     */
    template<class T, class Key, class ...Replacement>
    using replaceAll_t = typename replaceAll<T, Key, Replacement...>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Replaces a type at a given index inside a template parameter-list with a list of replacement types.
     *  
     *  Replaces the type at position I inside the parameter-list of class template instantiation T with
     *  the given list of types Replacement and provide a member alias "type" for an instantiation of
     *  class template T with the new parameter-list, otherwise T.  
     *  If Replacement does not provide any types, compilation will fail.
     *  
     *  If I is not less than the number of template arguments in the template parameter-list of T,
     *  then compilation will fail.  
     *  For an empty class template instantiation of T, index will always be out of bounds and so cause compilation
     *  to fail.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T           Any valid type-only class template instantiation
     *  @tparam I           The index of the type to replace
     *  @tparam Replacement A list of types the found type should be replaced with (preserving order)
     *  @tparam NewT        The new type to set the type at the index to (set_t only)
     *  
     *  @see extrait::replace
     *  @see extrait::replaceAll
     *  @see extrait::replaceRange
     *  @see extrait::replaceIf
     *  @see extrait::replaceIfNot
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, index_t I, class ...Replacement>
    struct replaceAt : detail::replaceAt<T, I, Replacement...> {};
    
    /**
     *  @brief Type helper for extrait::replaceAt.
     */
    template<class T, index_t I, class ...Replacement>
    using replaceAt_t = typename replaceAt<T, I, Replacement...>::type;
    
    /**
     *  @brief Type helper that replaces the first template argument in the template parameter-list of T.
     */
    template<class T, class ...Replacement>
    using replaceFirst_t = replaceAt_t<T, 0, Replacement...>;
    
    /**
     *  @brief Type helper that replaces the last template argument in the template parameter-list of T.
     */
    template<class T, class ...Replacement>
    using replaceLast_t = replaceAt_t<T, (length_v<T> - 1), Replacement...>;
    
    /**
     *  @brief Type helper that sets a type at a certain index to another singular type.
     */
     template<class T, index_t I, class NewT>
     using set_t = replaceAt_t<T, I, NewT>;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Replaces a range of types of a template parameter-list with a list of replacement types.
     *  
     *  Provides a member alias "type" that is a copy of the original parameter-list of class template instantiation T
     *  with the template arguments that were found in the given range [Start, End] replaced by types Replacement,
     *  where Start is a 0-based index referring to the first template argument inside the parameter-list of T that
     *  should be included in the replaced parameter-list and End is the last index of the range but excluding
     *  that element.  
     *  If Start and End refer to the same index in the parameter-list, no types will be replaced but instead inserted
     *  at index Start == End.  
     *  If Replacement does not provide any types, compilation will fail.
     *  
     *  If Start or End is larger than the number of template arguments in the template parameter-list of T or Start
     *  is bigger than End, then compilation will fail.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T           Any valid type-only class template instantiation
     *  @tparam Start       The start index of the range to replace
     *  @tparam End         The end index of the range to replace (exclusive)
     *  @tparam Replacement A list of types the range should be replaced with (preserving order)
     *  
     *  @see extrait::replace
     *  @see extrait::replaceAll
     *  @see extrait::replaceAt
     *  @see extrait::replaceIf
     *  @see extrait::replaceIfNot
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, index_t Start, index_t End, class ...Replacement>
    struct replaceRange : detail::replaceRange<T, Start, End, Replacement...> {};
    
    /**
     *  @brief Type helper for extrait::replaceRange.
     */
    template<class T, index_t Start, index_t End, class ...Replacement>
    using replaceRange_t = typename replaceRange<T, Start, End, Replacement...>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Replaces all types inside a template parameter-list, that match a certain predicate, with a list
     *         of replacement types.
     *  
     *  Provides a member alias "type", that is copy of the original class template instantiation T with all types
     *  that match Predicate replaced by types Replacement.  
     *  If Replacement does not provide any types, compilation will fail.
     *  
     *  Where Predicate is a class template that takes the currently (one at a time) inspected type from the
     *  parameter-list of class template instantiation T as template argument and provides a static "value" constant
     *  expression that is a bool that determines true if the type should be replaced.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T or Predicate, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T           Any valid type-only class template instantiation
     *  @tparam Predicate   A predicate determining whether a type should be replaced
     *  @tparam Replacement A list of types a matching type should be replaced with (preserving order)
     *  
     *  @see extrait::replace
     *  @see extrait::replaceAll
     *  @see extrait::replaceAt
     *  @see extrait::replaceRange
     *  @see extrait::replaceIfNot
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, template<class> class Predicate, class ...Replacement>
    struct replaceIf : detail::replaceIf<T, Predicate, false, Replacement...> {};
    
    /**
     *  @brief Type helper for extrait::replaceIf.
     */
    template<class T, template<class> class Predicate, class ...Replacement>
    using replaceIf_t = typename replaceIf<T, Predicate, Replacement...>::type;
    
    /**
     *  @brief Replaces all types inside a template parameter-list that did not match a certain predicate with a list
     *         of replacement types.
     *  
     *  Provides a member alias "type", that is copy of the original class template instantiation T with all types
     *  that did not match Predicate replaced by types Replacement.  
     *  If Replacement does not provide any types, compilation will fail.
     *  
     *  Where Predicate is a class template that takes the currently (one at a time) inspected type from the
     *  parameter-list of class template instantiation T as template argument and provides a static "value" constant
     *  expression that is a bool that determines true if the type should not be replaced.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T or Predicate, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T           Any valid type-only class template instantiation
     *  @tparam Predicate   A predicate determining whether a type should be left as-is
     *  @tparam Replacement A list of types a matching type should be replaced with (preserving order)
     *  
     *  @see extrait::replace
     *  @see extrait::replaceAll
     *  @see extrait::replaceAt
     *  @see extrait::replaceRange
     *  @see extrait::replaceIf
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, template<class> class Predicate, class ...Replacement>
    struct replaceIfNot : detail::replaceIf<T, Predicate, true, Replacement...> {};
    
    /**
     *  @brief Type helper for extrait::replaceIfNot.
     */
    template<class T, template<class> class Predicate, class ...Replacement>
    using replaceIfNot_t = typename replaceIfNot<T, Predicate, Replacement...>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Remove the first match of a type in a template parameter-list.
     *  
     *  If type Key could be found in the parameter-list of class template instantiation T, will remove the first
     *  occurrence of this type from the parameter-list and provide a member alias "type" for an
     *  instantiation of class template T with the new parameter-list, otherwise T.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T   Any valid type-only class template instantiation
     *  @tparam Key Any type that should be found to be removed from the parameter-list of instantiation T
     *  
     *  @see extrait::removeAll
     *  @see extrait::removeAt
     *  @see extrait::removeRange
     *  @see extrait::removeIf
     *  @see extrait::filter
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, class Key>
    struct remove : detail::remove<T, Key> {};
    
    /**
     *  @brief Type helper for extrait::remove.
     */
    template<class T, class Key>
    using remove_t = typename remove<T, Key>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Removes all matching types in a template parameter-list.
     *  
     *  If type Key could be found in the parameter-list of class template instantiation T, will remove all
     *  occurrences of this type and provide a member alias "type" for an instantiation of class template T with the
     *  new parameter-list, otherwise T.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T   Any valid type-only class template instantiation
     *  @tparam Key Any type that should be found to be removed from the parameter-list of instantiation T
     *  
     *  @see extrait::remove
     *  @see extrait::removeAt
     *  @see extrait::removeRange
     *  @see extrait::removeIf
     *  @see extrait::filter
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, class Key>
    struct removeAll : detail::removeAll<T, Key> {};
    
    /**
     *  @brief Type helper for extrait::removeAll.
     */
    template<class T, class Key>
    using removeAll_t = typename removeAll<T, Key>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Removes a type at a given index inside a template parameter-list.
     *  
     *  Removes the type at position I inside the parameter-list of class template instantiation T and provides a
     *  member alias "type" for an instantiation of class template T with the new parameter-list, otherwise T.
     *  
     *  If I is not less than the number of template arguments in the template parameter-list of T,
     *  then compilation will fail.  
     *  For an empty class template instantiation of T, index will always be out of bounds and so cause compilation
     *  to fail.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T Any valid type-only class template instantiation
     *  @tparam I The index of the type to remove
     *  
     *  @see extrait::remove
     *  @see extrait::replaceAll
     *  @see extrait::replaceRange
     *  @see extrait::removeIf
     *  @see extrait::filter
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, index_t I>
    struct removeAt : detail::removeAt<T, I> {};
    
    /**
     *  @brief Type helper for extrait::removeAt.
     */
    template<class T, index_t I>
    using removeAt_t = typename removeAt<T, I>::type;
    
    /**
     *  @brief Type helper for extrait::removeAt that removes the first template argument in the template
     *         parameter-list of T.
     */
    template<class T>
    using removeFirst_t = removeAt_t<T, 0>;
    
    /**
     *  @brief Type helper for extrait::removeAt that removes the last template argument in the template
     *         parameter-list of T.
     */
    template<class T>
    using removeLast_t = removeAt_t<T, (length_v<T> - 1)>;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Removes a range of types of a template parameter-list.
     *  
     *  Provides a member alias "type" that is a copy of the original parameter-list of class template instantiation T
     *  with the template arguments that were found in the given range [Start, End] removed,
     *  where Start is a 0-based index referring to the first template argument inside the parameter-list of T that
     *  should be included in the removed parameter-list and End is the last index of the range but excluding
     *  that element.  
     *  If Start and End refer to the same index in the parameter-list, no types will be removed.
     *  
     *  If Start or End is larger than the number of template arguments in the template parameter-list of T or Start
     *  is bigger than End, then compilation will fail.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T     Any valid type-only class template instantiation
     *  @tparam Start The start index of the range to remove
     *  @tparam End   The end index of the range to remove (exclusive)
     *  
     *  @see extrait::remove
     *  @see extrait::removeAll
     *  @see extrait::removeRange
     *  @see extrait::removeIf
     *  @see extrait::filter
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, index_t Start, index_t End>
    struct removeRange : detail::removeRange<T, Start, End> {};
    
    /**
     *  @brief Type helper for extrait::removeRange.
     */
    template<class T, index_t Start, index_t End>
    using removeRange_t = typename removeRange<T, Start, End>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Removes all types inside a template parameter-list that match a certain predicate.
     *  
     *  Provides a member alias "type", that is copy of the original class template instantiation T with all types
     *  that match Predicate removed.
     *  
     *  Where Predicate is a class template that takes the currently (one at a time) inspected type from the
     *  parameter-list of class template instantiation T as template argument and provides a static "value" constant
     *  expression that is a bool that determines true if the type should be removed.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T or Predicate, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T         Any valid type-only class template instantiation
     *  @tparam Predicate A predicate determining whether a type should be removed
     *  
     *  @see extrait::remove
     *  @see extrait::removeAll
     *  @see extrait::removeAt
     *  @see extrait::removeRange
     *  @see extrait::filter
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, template<class> class Predicate>
    struct removeIf : detail::removeIf<T, Predicate, false> {};
    
    /**
     *  @brief Type helper for extrait::removeIf.
     */
    template<class T, template<class> class Predicate>
    using removeIf_t = typename removeIf<T, Predicate>::type;
    
    /**
     *  @brief Retains all types inside a template parameter-list that matched a certain predicate.
     *  
     *  Provides a member alias "type", that is copy of the original class template instantiation T with only the types
     *  remaining that matched Predicate.
     *  
     *  Where Predicate is a class template that takes the currently (one at a time) inspected type from the
     *  parameter-list of class template instantiation T as template argument and provides a static "value" constant
     *  expression that is a bool that determines true if the type should be kept.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T or Predicate, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T         Any valid type-only class template instantiation
     *  @tparam Predicate A predicate determining whether a type should be retained
     *  
     *  @see extrait::remove
     *  @see extrait::removeAll
     *  @see extrait::removeAt
     *  @see extrait::removeRange
     *  @see extrait::removeIf
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, template<class> class Predicate>
    struct filter : detail::removeIf<T, Predicate, true> {};
    
    /**
     *  @brief Type helper for extrait::filter.
     */
    template<class T, template<class> class Predicate>
    using filter_t = typename filter<T, Predicate>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Removes duplicate types in a template parameter-list.
     *  
     *  Provides a member alias "type" that is a copy of the original parameter-list of class template instantiation T
     *  with all types that occur more than once in the parameter-list removed so that only the first occurrence of the
     *  same type remains in the parameter-list.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T Any valid type-only class template instantiation
     *  
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T>
    struct deduplicate : detail::deduplicate<T> {};
    
    /**
     *  @brief Type helper for extrait::deduplicate.
     */
    template<class T>
    using deduplicate_t = typename deduplicate<T>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Adds a list of types to an instantiated template parameter-list.
     *  
     *  Provides a member alias "type" that is a copy of the original parameter-list of class template instantiation T
     *  with all of types Types added at the end of the parameter-list.  
     *  If list Types does not provide at least one type, this will fail compilation.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T     Any valid type-only class template instantiation
     *  @tparam Types A list of types to append to the end of the parameter-list
     *  
     *  @see extrait::addIfAbsent
     *  @see extrait::insert
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, class ...Types>
    struct add : detail::add<T, Types...> {};
    
    /**
     *  @brief Type helper for extrait::add.
     */
    template<class T, class ...Types>
    using add_t = typename add<T, Types...>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Adds a list of types to an instantiated template parameter-list if they aren't already in the list.
     *  
     *  Provides a member alias "type" that is a copy of the original parameter-list of class template instantiation T
     *  with all of types Types added at the end of the parameter-list that do not already exist in the parameter-list
     *  of class template instantiation T.  
     *  If list Types does not provide at least one type, this will fail compilation.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T     Any valid type-only class template instantiation
     *  @tparam Types A list of types to append to the end of the parameter-list
     *  
     *  @see extrait::add
     *  @see extrait::insert
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, class ...Types>
    struct addIfAbsent : detail::addIfAbsent<T, Types...> {};
    
    /**
     *  @addtogroup extrait::addIfAbsent
     *  @brief Type helper for extrait::addIfAbsent.
     */
    template<class T, class ...Add>
    using addIfAbsent_t = typename addIfAbsent<T, Add...>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Inserts a list of types to an instantiated template parameter-list at the specified index.
     *  
     *  Provides a member alias "type" that is a copy of the original parameter-list of class template instantiation T
     *  with all of types Types added at the specified index of the parameter-list.  
     *  If the index is one past the end, the types will be inserted at the end of the parameter-list.  
     *  If list Types does not provide at least one type, this will fail compilation.
     *  
     *  If I is not less or equal than the number of template arguments in the template parameter-list of T,
     *  then compilation will fail.  
     *  For an empty class template instantiation of T, index 0 denotes the end of the list and hence inserts the
     *  types at the start of the parameter-list.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T     Any valid type-only class template instantiation
     *  @tparam I     The index of where to insert the types (can be one past the end to denote the end of the list)
     *  @tparam Types A list of types to insert at the specified index
     *  
     *  @see extrait::add
     *  @see extrait::addIfAbsent
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, index_t I, class ...Add>
    struct insert : detail::insert<T, I, Add...> {};
    
    /**
     *  @brief Type helper for extrait::insert.
     */
    template<class T, index_t I, class ...Add>
    using insert_t = typename insert<T, I, Add...>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Left rotates a range of types in a parameter-list.
     *  
     *  Provides a member alias "type" that is a copy of the original parameter-list of class template instantiation T
     *  with the types in range [Start, End] left rotated until the type at index Middle is at the start of the given
     *  range [Start, End].
     *  
     *  If Start or End is larger than the number of template arguments in the template parameter-list of T or Start
     *  is bigger than End, then compilation will fail.  
     *  If Middle is smaller than Start or Middle is bigger than End, compilation will fail.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T      Any valid type-only class template instantiation
     *  @tparam Start  The start index of the range to rotate
     *  @tparam Middle The index of the type inside range [Start, End] that should appear at the beginning of the range
     *  @tparam End    The end index of the range to rotate
     *  
     *  @see extrait::move
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, index_t Start, index_t Middle, index_t End>
    struct rotate : detail::rotate<T, Start, Middle, End> {};
    
    /**
     *  @brief Type helper for extrait::rotate.
     */
    template<class T, index_t Start, index_t Middle, index_t End>
    using rotate_t = typename rotate<T, Start, Middle, End>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Moves a type from a certain index to a new index in a parameter-list.
     *  
     *  Provides a member alias "type" that is a copy of the original parameter-list of class template instantiation T
     *  with the type at index I in the parameter-list of class template instantiation T moved to the new
     *  index Dest if I and Dest are not the same, otherwise T.  
     *  Any types between the types I and Dest are left rotated until the type is at the destination index.
     *  
     *  Other than extrait::swap, this will rotate the affected range [I, Dest] or [Dest, I] entirely.
     *  
     *  If I or Dest is larger than or equal the number of template arguments in the template parameter-list of T,
     *  then compilation will fail.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T    Any valid type-only class template instantiation
     *  @tparam I    The index of the type to move
     *  @tparam Dest The destination index of the type to where the type should be moved to
     *  
     *  @see extrait::rotate
     *  @see extrait::swap
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, index_t I, index_t Dest>
    struct move : detail::move<T, I, Dest> {};
    
    /**
     *  @brief Type helper for extrait::move.
     */
    template<class T, index_t I, index_t Dest>
    using move_t = typename move<T, I, Dest>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Swap a type from a certain index with another type at a different index in a parameter-list.
     *  
     *  Provides a member alias "type" that is a copy of the original parameter-list of class template instantiation T
     *  with the type at index I in the parameter-list of class template instantiation T swapped with the type at
     *  index Dest.
     *  
     *  Other than extrait::move, this will not rotate anything but merely switch out the affected indices.
     *  
     *  If I or Dest is larger than or equal the number of template arguments in the template parameter-list of T,
     *  then compilation will fail.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T    Any valid type-only class template instantiation
     *  @tparam I    The index of the type to swap
     *  @tparam Dest The index of the other type to swap
     *  
     *  @see extrait::move
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, index_t I, index_t Dest>
    struct swap : detail::swap<T, I, Dest> {};
    
    /**
     *  @brief Type helper for extrait::swap.
     */
    template<class T, index_t I, index_t Dest>
    using swap_t = typename swap<T, I, Dest>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Sorts the types in a parameter-list.
     *  
     *  Provides a member alias "type" that is a copy of the parameter-list of class template instantiation T with
     *  every type in the parameter-list sorted through a comparison class template.  
     *  The resulting parameter-list will always be the same length as the input parameter-list.
     *  
     *  Where Comparator is a class template that takes two types as arguments, where the first argument is a type that
     *  in the current comparison pass is compared to the key type and the second argument is the key type that is
     *  compared to every type preceding it, this class template must provide a static constant expression "value"
     *  that determines true if the key type should be ordered before the compared type.  
     *  The order between equal elements is the same order as they appeared in the input template, that means that if
     *  T1 and T2 share the same comparative potential and T1 appears before T2 in the parameter-list, T1 will also be
     *  ordered before T2 in the resultant parameter-list.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T          Any valid type-only class template instantiation
     *  @tparam Comparator Any type satisfying a valid comparing type
     *  
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, template<class, class> class Comparator>
    struct sort : detail::sort<T, Comparator> {};
    
    /**
     *  @brief Type helper for extrait::sort.
     */
    template<class T, template<class, class> class Comparator>
    using sort_t = typename sort<T, Comparator>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Transforms the types of a template parameter-list according to a given mapping template.
     *  
     *  Provides a member alias "type" that is a copy of the parameter-list of class template instantiation T with
     *  every type in the parameter-list remapped through a class template Mapper.  
     *  The resulting parameter-list will always be the same length as the input parameter-list.
     *  
     *  Where Mapper is a class template that takes the currently (one at a time) inspected type from the parameter-list
     *  of class template instantiation T as template argument and provides a member alias "type" that aliases the
     *  transformed type based on the type given as template parameter  
     *  If the mapper does not follow this structure or doesn't map every incoming type to a valid result type,
     *  compilation will fail.
     *  
     *  If T is not a class template or is a class template with at least one non-type template parameter,
     *  compilation will fail.
     *  
     *  Any modification to T, such as pointer, reference, array or cv-qualification of the original type,
     *  will render the type a non-class template type and compilation will fail.  
     *  In these cases you can use extrait::strip to strip any of these modifications off the type beforehand.
     *  
     *  Adding custom template specialisations to this template results in undefined behaviour.
     *  
     *  @tparam T      Any valid type-only class template instantiation
     *  @tparam Mapper Any type satisfying a valid mapping class template
     *  
     *  @see extrait::strip
     *  @see extrait::hasTypeList
     *  @see extrait::TypeArray
     */
    template<class T, template<class> class Mapper>
    struct map : detail::map<T, Mapper> {};
    
    /**
     *  @brief Type helper for extrait::map.
     */
    template<class T, template<class> class Mapper>
    using map_t = typename map<T, Mapper>::type;
}
