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
    @file   TypeTraits.cpp
    @date   30, April 2024
    
    ===============================================================
 */

#include <extrait/type_container.h>

#include <gtest/gtest.h>



//**********************************************************************************************************************
// region Preprocessor
//======================================================================================================================
#ifndef EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    #define EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS 0
#endif
//======================================================================================================================
// endregion Preprocessor
//**********************************************************************************************************************
// region Suite Setup
//======================================================================================================================
namespace
{
    //==================================================================================================================
    template<class = void, class ...Args>
    struct withDefaultParameter {};
    
    //==================================================================================================================
    template<class ...Types>
    struct Foo {};
    
    template<class ...Types>
    struct Bar {};
    
    //==================================================================================================================
    template<class T>
    struct FloatingPointPredicate : std::bool_constant<std::is_floating_point_v<T>> {};
    
    template<class>
    struct AlwaysPredicate : std::true_type {};
    
    template<class>
    struct NeverPredicate : std::false_type {};
    
    //==================================================================================================================
    template<class T>
    struct RefMapper
    {
        using type = std::add_lvalue_reference_t<T>;
    };
    
    template<class T>
    struct RefIfIntegralMapper
    {
        using type = std::conditional_t<
            std::is_integral_v<T>,
                std::add_lvalue_reference_t<T>,
                T
        >;
    };
    
    //==================================================================================================================
    template<class T, class Key>
    struct SizeComparer
    {
        constexpr static bool value = (sizeof(Key) < sizeof(T));
    };
    
    template<class T, class Key>
    struct ValueComparer
    {
        constexpr static bool value = false;
    };
    
    template<int TValue, int KeyValue>
    struct ValueComparer<std::integral_constant<int, TValue>, std::integral_constant<int, KeyValue>>
    {
        constexpr static bool value = (KeyValue < TValue);
    };
    
    template<class T, std::size_t LastSize = 0>
    struct SizeChecker;
    
    template<template<class...> class T, std::size_t LastSize, class Next, class ...TTypes>
    struct SizeChecker<T<Next, TTypes...>, LastSize>
    {
        constexpr static bool value = []() -> bool
        {
            constexpr std::size_t current_size = sizeof(Next);
            
            if constexpr (current_size < LastSize)
            {
                return false;
            }
            else
            {
                return SizeChecker<T<TTypes...>, std::max(LastSize, current_size)>::value;
            }
        }();
    };
    
    template<template<class...> class T, std::size_t LastSize>
    struct SizeChecker<T<>, LastSize>
    {
        constexpr static bool value = true;
    };
    
    template<class T, int LastVal = 0>
    struct ValueChecker;
    
    template<template<class...> class T, int LastVal, int CurrentValue, class ...TTypes>
    struct ValueChecker<T<std::integral_constant<int, CurrentValue>, TTypes...>, LastVal>
    {
        constexpr static bool value = []() -> bool
        {
            if constexpr (CurrentValue < LastVal)
            {
                return false;
            }
            else
            {
                return SizeChecker<T<TTypes...>, std::max(LastVal, CurrentValue)>::value;
            }
        }();
    };
    
    template<template<class...> class T, int LastVal>
    struct ValueChecker<T<>, LastVal>
    {
        constexpr static bool value = true;
    };
    
    template<int Val>
    using val = std::integral_constant<int, Val>;
    
    template<class T, class Key>
    struct RelationComparer
    {
        constexpr static bool value = (sizeof(T) < sizeof(Key));
    };
}
//======================================================================================================================
// endregion Suite Setup
//**********************************************************************************************************************
// region Unit Tests
//======================================================================================================================
TEST(TypeTraitSuite, TestTraits)
{
    //==================================================================================================================
    using namespace extrait;
    
    //------------------------------------------------------------------------------------------------------------------
    EXPECT_TRUE ((hasTypeList_v<std::tuple<int>>));
    EXPECT_TRUE ((hasTypeList_v<std::tuple<>>));
    EXPECT_TRUE ((hasTypeList_v<std::vector<int>>));
    EXPECT_FALSE((hasTypeList_v<std::array<int, 0>>));
    EXPECT_FALSE((hasTypeList_v<int>));
    
    //....................
    EXPECT_TRUE ((sameClassTemplate_v<::Foo<float, void>, ::Foo<float, void>>));
    EXPECT_TRUE ((sameClassTemplate_v<::Foo<float, void>, ::Foo<int, float, long>>));
    EXPECT_TRUE ((sameClassTemplate_v<::Bar<float, void>, ::Bar<int, float, long>>));
    EXPECT_TRUE ((sameClassTemplate_v<::Bar<float, void>, ::Bar<>>));
    EXPECT_TRUE ((sameClassTemplate_v<::Bar<>,            ::Bar<>>));
    EXPECT_FALSE((sameClassTemplate_v<::Foo<float, void>, ::Bar<int, float, long>>));
    EXPECT_FALSE((sameClassTemplate_v<::Foo<>,            ::Bar<>>));
    EXPECT_FALSE((sameClassTemplate_v<::Foo<>,            ::Bar<int, float, long>>));

#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    sameClassTemplate_v<int, ::Foo<float>>;
    sameClassTemplate_v<std::array<float, 3>, ::Foo<float>>;
    sameClassTemplate_v<::Foo<float>&, ::Foo<float>>;
#endif

    //....................
    EXPECT_TRUE ((contains_v<std::tuple<int, long, short, float>, short>));
    EXPECT_FALSE((contains_v<std::tuple<int, long, short, float>, char>));
    EXPECT_FALSE((contains_v<std::tuple<>,                        int>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    contains_v<int, int>;
    contains_v<std::array<float, 3>, float>;
    contains_v<std::tuple<int, float>&, int>;
#endif
    
    //....................
    EXPECT_TRUE ((isEmpty_v<std::tuple<>>));
    EXPECT_TRUE ((isEmpty_v<::withDefaultParameter<>>));
    EXPECT_TRUE ((isEmpty_v<::withDefaultParameter<void>>));
    EXPECT_FALSE((isEmpty_v<std::tuple<int>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    isEmpty_v<int>;
    isEmpty_v<std::array<float, 3>>;
#endif
    
    //....................
    EXPECT_TRUE ((isEmptyInstantiated_v<std::tuple<>>));
    EXPECT_FALSE((isEmptyInstantiated_v<::withDefaultParameter<>>));
    EXPECT_FALSE((isEmptyInstantiated_v<::withDefaultParameter<void>>));
    EXPECT_FALSE((isEmptyInstantiated_v<std::tuple<int>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    isEmptyInstantiated_v<int>;
    isEmptyInstantiated_v<std::array<float, 3>>;
#endif
    
    //....................
    EXPECT_TRUE ((sameTemplateArguments_v<std::tuple<int, long, short>, std::tuple<int, long, short>>));
    EXPECT_TRUE ((sameTemplateArguments_v<::Foo<int, long, short>, std::tuple<int, long, short>>));
    EXPECT_TRUE ((sameTemplateArguments_v<std::vector<int>, std::tuple<int, std::allocator<int>>>));
    EXPECT_TRUE ((sameTemplateArguments_v<std::tuple<>, std::tuple<>>));
    EXPECT_FALSE((sameTemplateArguments_v<std::tuple<int, long, short>, std::tuple<int, long, short, char>>));
    EXPECT_FALSE((sameTemplateArguments_v<::Foo<int, long, short>, std::tuple<int, long, short, long>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    sameTemplateArguments_v<int, std::tuple<int, long, short>>;
    sameTemplateArguments_v<std::array<float, 3>, std::tuple<int, long, short>>;
#endif
    
    //....................
    EXPECT_TRUE ((startsWith_v<std::tuple<int, long, short, void, char, bool, float>, int, long, short>));
    EXPECT_TRUE ((startsWith_v<std::tuple<int, long, short, void, char, bool, float>>));
    EXPECT_TRUE ((startsWith_v<std::vector<float>, float, std::allocator<float>>));
    EXPECT_TRUE ((startsWith_v<std::tuple<>>));
    EXPECT_FALSE((startsWith_v<std::tuple<int, long, short, void, char, bool, float>, char, long, short>));
    EXPECT_FALSE((startsWith_v<std::tuple<>,                                          char, long, short>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    startsWith_v<int, int>;
    startsWith_v<std::array<float, 3>, float>;
#endif
    
    //....................
    EXPECT_TRUE ((endsWith_v<std::tuple<int, long, short, void, char, bool, float>, char, bool, float>));
    EXPECT_TRUE ((endsWith_v<std::tuple<int, long, short, void, char, bool, float>>));
    EXPECT_TRUE ((endsWith_v<std::vector<float>, std::allocator<float>>));
    EXPECT_TRUE ((endsWith_v<std::tuple<>>));
    EXPECT_FALSE((endsWith_v<std::tuple<int, long, short, void, char, bool, float>, char, long, short>));
    EXPECT_FALSE((endsWith_v<std::tuple<>,                                          char, long, short>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    endsWith_v<int, int>;
    endsWith_v<std::array<float, 3>, float>;
#endif
    
    //....................
    using MatchInput = std::tuple<int, float, long, short, char, double, float>;
    EXPECT_EQ((match_v   <MatchInput, ::FloatingPointPredicate>), 3);
    EXPECT_EQ((mismatch_v<MatchInput, ::FloatingPointPredicate>), 4);
    
    EXPECT_TRUE ((matchAny_v <MatchInput, ::FloatingPointPredicate>));
    EXPECT_FALSE((matchAll_v <MatchInput, ::FloatingPointPredicate>));
    EXPECT_FALSE((matchNone_v<MatchInput, ::FloatingPointPredicate>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    match_v<int, ::FloatingPointPredicate>;
    match_v<std::array<float, 3>, ::FloatingPointPredicate>;
    match_v<MatchInput, ::Foo>;
#endif
    
    //....................
    using IndexOfInput = std::tuple<int, float, long, short, char, double, float>;
    EXPECT_EQ((indexOf_v<IndexOfInput, float>),     1);
    EXPECT_EQ((indexOf_v<IndexOfInput, int>),       0);
    EXPECT_EQ((indexOf_v<IndexOfInput, double>),    5);
    EXPECT_EQ((indexOf_v<IndexOfInput, long long>), endOfTypeList);
    EXPECT_EQ((indexOf_v<std::tuple<>, long long>), endOfTypeList);
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    indexOf_v<int, int>;
    indexOf_v<std::array<float, 3>, float>;
#endif
    
    //....................
    using IndexOfInput = std::tuple<int, float, long, short, char, double, float>;
    EXPECT_EQ((lastIndexOf_v<IndexOfInput, float>),     6);
    EXPECT_EQ((lastIndexOf_v<IndexOfInput, int>),       0);
    EXPECT_EQ((lastIndexOf_v<IndexOfInput, double>),    5);
    EXPECT_EQ((lastIndexOf_v<IndexOfInput, long long>), endOfTypeList);
    EXPECT_EQ((lastIndexOf_v<std::tuple<>, long long>), endOfTypeList);
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    lastIndexOf_v<int, int>;
    lastIndexOf_v<std::array<float, 3>, float>;
#endif
    
    //....................
    EXPECT_EQ((length_v<std::tuple<int, float, long, short, char, double, float>>), 7);
    EXPECT_EQ((length_v<std::tuple<>>), 0);
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    length_v<int>;
    length_v<std::array<float, 3>>;
#endif
    
    //....................
    EXPECT_TRUE ((std::is_same_v<std::tuple<int, long, float>,
                 join_t<std::tuple, std::tuple<int>, std::tuple<long>, std::tuple<float>>>));
    EXPECT_TRUE ((std::is_same_v<std::tuple<>,
                 join_t<std::tuple, std::tuple<>, std::tuple<>, std::tuple<>>>));
    EXPECT_TRUE ((std::is_same_v<std::tuple<float, std::allocator<float>, int>,
                 join_t<std::tuple, std::vector<float>, std::tuple<int>>>));
    EXPECT_FALSE((std::is_same_v<std::tuple<int, long, float>,
                 join_t<std::tuple, std::tuple<int>, std::tuple<long>>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    join_t<std::tuple, std::tuple<int>, int>;
    join_t<std::tuple, std::tuple<int>, std::array<float, 3>>;
#endif
    
    //....................
    EXPECT_TRUE ((std::is_same_v<std::tuple<int, float, long>, reverse_t<std::tuple<long, float, int>>>));
    EXPECT_TRUE ((std::is_same_v<std::tuple<>, reverse_t<std::tuple<>>>));
    EXPECT_FALSE((std::is_same_v<std::tuple<int, float, long>, reverse_t<std::tuple<int, float, long>>>));
    EXPECT_FALSE((std::is_same_v<std::tuple<int, float, long>, reverse_t<std::tuple<>>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    reverse_t<int>;
    reverse_t<std::array<float, 3>>;
#endif
    
    //....................
    using SublistInput = std::tuple<int, float, long, short, char, double, float>;
    
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, long>,          sublist_t<SublistInput, 0, 3>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<long, short, char, double>, sublist_t<SublistInput, 2, 6>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<double, float>,             sublist_t<SublistInput, 5, 7>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<>,                          sublist_t<SublistInput, 0, 0>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<>,                          sublist_t<SublistInput, 7, 7>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<>,                          sublist_t<std::tuple<>, 0, 0>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    sublist_t<int, 0, 0>;
    sublist_t<std::array<float, 3>, 0, 0>;
    sublist_t<SublistInput, 0, 8>;
    sublist_t<SublistInput, 8, 8>;
    sublist_t<SublistInput, 7, 4>;
#endif
    
    //....................
    using TypeAtInput = std::tuple<int, float, long, short, char, double, float>;
    EXPECT_TRUE((std::is_same_v<char,                  get_t<TypeAtInput, 4>>));
    EXPECT_TRUE((std::is_same_v<std::allocator<float>, get_t<std::vector<float>, 1>>));
    EXPECT_TRUE((std::is_same_v<int,                   first_t<TypeAtInput>>));
    EXPECT_TRUE((std::is_same_v<float,                 last_t<TypeAtInput>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    get_t<int, 0>;
    get_t<std::array<float, 3>, 0>;
    get_t<TypeAtInput, 7>;
    first_t<std::tuple<>>;
    last_t<std::tuple<>>;
#endif
    
    //....................
    using ReplaceInput = std::tuple<int, float, char, short, char, double, float>;
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, char, short, char, long, float>,
        replace_t<ReplaceInput, double, long>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, long, double, float, short, char, double, float>,
        replace_t<ReplaceInput, char, long, double, float>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<>,
        replace_t<std::tuple<>, char, long>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    replace_t<int, int, char>;
    replace_t<std::array<float, 3>, float, char>;
    replace_t<ReplaceInput, float>;
#endif
    
    //....................
    using ReplaceAllInput = std::tuple<int, float, char, short, char, double, float>;
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, char, short, char, long, float>,
        replaceAll_t<ReplaceAllInput, double, long>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, long, double, float, short, long, double, float, double, float>,
        replaceAll_t<ReplaceAllInput, char, long, double, float>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<>,
        replaceAll_t<std::tuple<>, char, long>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    replaceAll_t<int, int, char>;
    replaceAll_t<std::array<float, 3>, float, char>;
    replaceAll_t<ReplaceAllInput, float>;
#endif
    
    //....................
    using ReplaceAtInput = std::tuple<int, float, char, short, char, double, float>;
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, char, short, char, long, float>,
        replaceAt_t<ReplaceAtInput, 5, long>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, long, double, float, short, char, double, float>,
        replaceAt_t<ReplaceAtInput, 2, long, double, float>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<float, float, char, short, char, double, float>,
        set_t<ReplaceAtInput, 0, float>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    replaceAt_t<int, 0, char>;
    replaceAt_t<std::array<float, 3>, 0, char>;
    replaceAt_t<std::tuple<>, 0, char>;
    replaceAt_t<ReplaceAtInput, 0>;
    replaceAt_t<ReplaceAtInput, 7, char>;
#endif
    
    //....................
    using ReplaceRangeInput = std::tuple<int, float, char, short, char, double, float>;
    EXPECT_TRUE((std::is_same_v<std::tuple<long, double, float>,
        replaceRange_t<ReplaceRangeInput, 0, 5, long>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<long, double, float, int, float, char, short, char, double, float>,
        replaceRange_t<ReplaceRangeInput, 0, 0, long, double, float>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, char, short, char, double, float, long, double, float>,
        replaceRange_t<ReplaceRangeInput, 7, 7, long, double, float>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<long, double, float>,
        replaceRange_t<ReplaceRangeInput, 0, 7, long, double, float>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<long, double, float>,
        replaceRange_t<std::tuple<>, 0, 0, long, double, float>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    replaceRange_t<int, 0, 0, char>;
    replaceRange_t<std::array<float, 3>, 0, 0, char>;
    replaceRange_t<ReplaceRangeInput, 0, 8, char>;
    replaceRange_t<ReplaceRangeInput, 8, 8, char>;
    replaceRange_t<ReplaceRangeInput, 6, 4, char>;
#endif
    
    //....................
    using ReplaceIfInput = std::tuple<int, float, char, short, char, double, float>;
    
    EXPECT_TRUE((std::is_same_v<std::tuple<int, long, char, short, char, long, long>,
        replaceIf_t<ReplaceIfInput, ::FloatingPointPredicate, long>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<long, long, long, long, long, long, long>,
        replaceIf_t<ReplaceIfInput, ::AlwaysPredicate, long>>));
    EXPECT_TRUE((std::is_same_v<ReplaceIfInput,
        replaceIf_t<ReplaceIfInput, ::NeverPredicate, long>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    replaceIf_t<int, ReplaceIfPredicate, char>;
    replaceIf_t<std::array<float, 3>, ReplaceIfPredicate, char>;
    replaceIf_t<ReplaceIfInput, int, char>;
    replaceIf_t<ReplaceIfInput, ReplaceIfPredicate>;
#endif
    
    //....................
    using RemoveInput = std::tuple<int, float, char, short, char, double, float>;
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, char, short, char, float>,
        remove_t<RemoveInput, double>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, short, char, double, float>,
        remove_t<RemoveInput, char>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<>,
        remove_t<std::tuple<>, char>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    remove_t<int, int>;
    remove_t<std::array<float, 3>, float>;
#endif
    
    //....................
    using RemoveAllInput = std::tuple<int, float, char, short, char, double, float>;
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, char, short, char, float>,
        removeAll_t<RemoveAllInput, double>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, short, double, float>,
        removeAll_t<RemoveAllInput, char>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<>,
        removeAll_t<std::tuple<>, char>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    removeAll_t<int, int>;
    removeAll_t<std::array<float, 3>, float>;
#endif
    
    //....................
    using RemoveAtInput = std::tuple<int, float, char, short, char, double, float>;
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, char, short, char, float>,
        removeAt_t<RemoveAtInput, 5>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, short, char, double, float>,
        removeAt_t<RemoveAtInput, 2>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<float, char, short, char, double, float>,
        removeFirst_t<RemoveAtInput>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, char, short, char, double>,
        removeLast_t<RemoveAtInput>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    removeAt_t<int, 0>;
    removeAt_t<std::array<float, 3>, 0>;
    removeAt_t<std::tuple<>, 0>;
    removeAt_t<RemoveAtInput, 7>;
#endif
    
    //....................
    using RemoveRangeInput = std::tuple<int, float, char, short, char, double, float>;
    EXPECT_TRUE((std::is_same_v<std::tuple<double, float>,
        removeRange_t<RemoveRangeInput, 0, 5>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, char, short, char, double, float>,
        removeRange_t<RemoveRangeInput, 0, 0>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, char, short, char, double, float>,
        removeRange_t<RemoveRangeInput, 7, 7>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<>,
        removeRange_t<RemoveRangeInput, 0, 7>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<>,
        removeRange_t<std::tuple<>, 0, 0>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    removeRange_t<int, 0, 0>;
    removeRange_t<std::array<float, 3>, 0, 0>;
    removeRange_t<RemoveRangeInput, 0, 8>;
    removeRange_t<RemoveRangeInput, 8, 8>;
    removeRange_t<RemoveRangeInput, 6, 4>;
#endif
    
    //....................
    using RemoveIfInput = std::tuple<int, float, char, short, char, double, float>;
    
    EXPECT_TRUE((std::is_same_v<std::tuple<int, char, short, char>,
        removeIf_t<RemoveIfInput, ::FloatingPointPredicate>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<>,
        removeIf_t<RemoveIfInput, ::AlwaysPredicate>>));
    EXPECT_TRUE((std::is_same_v<RemoveIfInput,
        removeIf_t<RemoveIfInput, ::NeverPredicate>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<float, double, float>,
        filter_t<RemoveIfInput, ::FloatingPointPredicate>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    removeIf_t<int, ::FloatingPointPredicate>;
    removeIf_t<std::array<float, 3>, ::FloatingPointPredicate>;
    removeIf_t<RemoveIfInput, ::Foo>;
#endif
    
    //....................
    using DeduplicateInput = std::tuple<int, double, float, float, char, short, char, double, int, float>;
    
    EXPECT_TRUE((std::is_same_v<std::tuple<int, double, float, char, short>,
        deduplicate_t<DeduplicateInput>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int, long, float, short, char, bool>,
        deduplicate_t<std::tuple<int, long, float, short, char, bool>>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<>,
        deduplicate_t<std::tuple<>>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    deduplicate_t<int>;
    deduplicate_t<std::array<float, 3>>;
#endif
    
    //....................
    using AddInput = std::tuple<int, double, float>;
    EXPECT_TRUE((std::is_same_v<std::tuple<int, double, float, char, bool>,
        add_t<AddInput, char, bool>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<char, bool>,
        add_t<std::tuple<>, char, bool>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    add_t<int, float>;
    add_t<std::array<float, 3>, float>;
    add_t<AddInput>;
#endif
    
    //....................
    using AddIfAbsentInput = std::tuple<int, double, float>;
    EXPECT_TRUE((std::is_same_v<std::tuple<int, double, float, char, bool>,
        addIfAbsent_t<AddIfAbsentInput, char, float, double, int, bool, double, float>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<char, bool>,
        addIfAbsent_t<std::tuple<>, char, bool>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    addIfAbsent_t<int, float>;
    addIfAbsent_t<std::array<float, 3>, float>;
    addIfAbsent_t<AddInput>;
#endif
    
    //....................
    using InsertInput = std::tuple<int, double, float>;
    EXPECT_TRUE((std::is_same_v<std::tuple<char, bool, int, double, float>,
        insert_t<InsertInput, 0, char, bool>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int, double, float, char, bool>,
        insert_t<InsertInput, length_v<InsertInput>, char, bool>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int, double, float, double, float>,
        insert_t<InsertInput, 2, float, double>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<float, double>,
        insert_t<std::tuple<>, 0, float, double>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    insert_t<int, 0, int>;
    insert_t<std::array<float, 3>, 0, int>;
    insert_t<AddIfAbsentInput, 0>;
    insert_t<AddIfAbsentInput, 4, float>;
    insert_t<std::tuple<>, 1, float>;
#endif
    
    //....................
    using RotateInput = std::tuple<int, float, char, short, char, double, float>;
    EXPECT_TRUE((std::is_same_v<std::tuple<int, short, char, double, float, char, float>,
        rotate_t<RotateInput, 1, 3, 6>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<short, char, double, float, int, float, char>,
        rotate_t<RotateInput, 0, 3, 7>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, char, short, char, double, float>,
        rotate_t<RotateInput, 0, 0, 0>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<>,
        rotate_t<std::tuple<>, 0, 0, 0>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    rotate_t<int, 0, 0, 0>;
    rotate_t<std::array<float, 3>, 0, 0, 0>;
    rotate_t<RotateInput, 8, 0, 0>;
    rotate_t<RotateInput, 0, 0, 8>;
    rotate_t<RotateInput, 0, 1, 0>;
#endif

    //....................
    using MoveInput = std::tuple<int, float, char, short, char, double, float>;
    EXPECT_TRUE((std::is_same_v<std::tuple<int, char, short, char, double, float, float>,
        move_t<MoveInput, 1, 6>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int, char, short, char, double, float, float>,
        move_t<MoveInput, 1, 5>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, float, char, short, char, double>,
        move_t<MoveInput, 6, 1>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<double, int, float, char, short, char, float>,
        move_t<MoveInput, 5, 0>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    move_t<int, 0, 0>;
    move_t<std::array<float, 3>, 0, 0>;
    move_t<RotateInput, 8, 0>;
    move_t<RotateInput, 0, 8>;
    move_t<std::tuple<>, 0, 0>;
#endif
    
    //....................
    using SwapInput = std::tuple<int, float, char, short, char, double, float>;
    EXPECT_TRUE((std::is_same_v<std::tuple<float, float, char, short, char, double, int>,
        swap_t<SwapInput, 0, 6>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<char, float, int, short, char, double, float>,
        swap_t<SwapInput, 0, 2>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, char, short, float, double, char>,
        swap_t<SwapInput, 6, 4>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, char, char, short, double, float>,
        swap_t<SwapInput, 3, 4>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int, float, char, char, short, double, float>,
        swap_t<SwapInput, 4, 3>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    swap_t<int, 0, 0>;
    swap_t<std::array<float, 3>, 0, 0>;
    swap_t<SwapInput, 7, 0>;
    swap_t<SwapInput, 0, 7>;
    swap_t<std::tuple<>, 0, 0>;
#endif
    
    //....................
    using MapInput = std::tuple<int, float, char, short, char, double, float>;
    EXPECT_TRUE((std::is_same_v<std::tuple<int&, float&, char&, short&, char&, double&, float&>,
        map_t<MapInput, ::RefMapper>>));
    EXPECT_TRUE((std::is_same_v<std::tuple<int&, float, char&, short&, char&, double, float>,
        map_t<MapInput, ::RefIfIntegralMapper>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    map_t<int, ::RefMapper>;
    map_t<std::array<float, 3>, ::RefMapper>;
    map_t<MapInput, Foo>;
#endif
    
    //....................
    using SortInputSize = std::tuple<long long, int, long, bool, short, short, double, float, char, long double>;
    using SizeSorted    = sort_t<SortInputSize, ::SizeComparer>;
    EXPECT_TRUE(::SizeChecker<SizeSorted>::value);
    EXPECT_TRUE((::SizeChecker<sort_t<std::tuple<int>, ::SizeComparer>>::value));
    EXPECT_TRUE((::SizeChecker<sort_t<std::tuple<>, ::SizeComparer>>::value));
    
    using SortInputValue = std::tuple<
        ::val<100>, ::val<2031>, ::val<8>, ::val<8429>, ::val<84>, ::val<1>, ::val<8499>, ::val<84>, ::val<8923>,
        ::val<920390>, ::val<8948>, ::val<849390>, ::val<8543020>, ::val<902>, ::val<29>, ::val<923>, ::val<8>,
        ::val<8293>, ::val<378449>, ::val<8402>, ::val<94938>, ::val<84593>, ::val<23348>, ::val<9420029>, ::val<28393>
    >;
    using ValueSorted = sort_t<SortInputValue, ::ValueComparer>;
    EXPECT_TRUE((::ValueChecker<ValueSorted>::value));
    EXPECT_TRUE((::ValueChecker<sort_t<std::tuple<::val<0>>, ::SizeComparer>>::value));
    EXPECT_TRUE((::ValueChecker<sort_t<std::tuple<>, ::SizeComparer>>::value));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    sort_t<int, ::SizeComparer>;
    sort_t<std::array<float, 3>, ::SizeComparer>;
#endif
    
    //....................
    using MinMaxInput = std::tuple<long long, int, long, bool, short, short, double, float, char, long double>;
    EXPECT_TRUE((std::is_same_v<bool,        minType_t<MinMaxInput, ::RelationComparer>>));
    EXPECT_TRUE((std::is_same_v<long double, maxType_t<MinMaxInput, ::RelationComparer>>));
    
#if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    minType_t<int, ::RelationComparer>;
    minType_t<std::array<float, 3>, ::RelationComparer>;
    minType_t<MinMaxInput, ::Foo>;
    maxType_t<int, ::RelationComparer>;
    maxType_t<std::array<float, 3>, ::RelationComparer>;
    maxType_t<MinMaxInput, ::Foo>;
#endif
}

TEST(TypeTraitSuite, TestContainer)
{
    //==================================================================================================================
    using TestList = extrait::TypeArray<int, long, float, double, short, bool>;
    
    //------------------------------------------------------------------------------------------------------------------
    EXPECT_TRUE ((TestList::equals<extrait::TypeArray<int, long, float, double, short, bool>>));
    EXPECT_FALSE((TestList::equals<extrait::TypeArray<>>));
    
    //....................
    EXPECT_FALSE((TestList::isEmpty));
    EXPECT_TRUE ((extrait::TypeArray<>::isEmpty));
    
    //....................
    try
    {
        EXPECT_EQ((std::get<0>(extrait::makeVariant<TestList>(7))),         7);
        EXPECT_EQ((std::get<1>(extrait::makeVariant<TestList>(7l))),        7l);
        EXPECT_EQ((std::get<2>(extrait::makeVariant<TestList>(7.f))),       7.f);
        EXPECT_EQ((std::get<3>(extrait::makeVariant<TestList>(7.))),        7.);
        EXPECT_EQ((std::get<4>(extrait::makeVariant<TestList>((short) 7))), 7.);
        EXPECT_EQ((std::get<5>(extrait::makeVariant<TestList>(true))),      true);
    }
    catch (std::exception &ex)
    {
        EXPECT_TRUE(false) << ex.what();
    }
    
    //....................
    const auto array = extrait::makeVarArray<TestList>(2);
    
    for (int i = 0; i < array.size(); ++i)
    {
        const auto val = array.at(i);
        
        EXPECT_EQ(val.index(), i);
        std::visit([](auto &&v) { EXPECT_TRUE(static_cast<bool>(v)); }, val);
    }
    
    //....................
    std::vector<TestList::to<std::variant>> res_list;
    
    extrait::forEach(TestList::begin, TestList::end, [&res_list](auto it)
    {
        using It = decltype(it);
        res_list.emplace_back(extrait::makeVariant<TestList>(typename It::type{}));
    });
    
    for (int i = 0; i < res_list.size(); ++i)
    {
        const auto val = res_list.at(i);
        
        EXPECT_EQ(val.index(), i);
        std::visit([](auto &&v) { EXPECT_FALSE(static_cast<bool>(v)); }, val);
    }
    
    //....................
    auto fe_array = extrait::forEach(TestList::begin_t::inc<2>{}, TestList::end, [](auto it)
        -> TestList::to<std::variant>
    {
        using It = decltype(it);
        return typename It::type{};
    });
    
    for (int i = 0; i < fe_array.size(); ++i)
    {
        const auto val = fe_array.at(i);
        
        EXPECT_EQ(val.index(), i + 2);
        std::visit([](auto &&v) { EXPECT_FALSE(static_cast<bool>(v)); }, val);
    }
    
    //....................
    auto ap_array = extrait::apply(TestList::begin, TestList::end, [](auto ...it)
        -> std::array<TestList::to<std::variant>, TestList::length>
    {
        return { typename decltype(it)::type{}... };
    });
    
    for (int i = 0; i < ap_array.size(); ++i)
    {
        const auto val = ap_array.at(i);
        
        EXPECT_EQ(val.index(), i);
        std::visit([](auto &&v) { EXPECT_FALSE(static_cast<bool>(v)); }, val);
    }
    
    //....................
    #if EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
        (void) TestList::begin_t::with<7>{};
        (void) TestList::begin_t::inc<7>{};
        (void) TestList::begin_t::dec<1>{};
        (void) TestList::end_t::type{};
    #endif
}
//======================================================================================================================
// endregion Unit Tests
//**********************************************************************************************************************
