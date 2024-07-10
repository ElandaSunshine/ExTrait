#include <extrait/common.h>
#include <extrait/type_list.h>

// #include <array>
#include <iostream>
#include <tuple>
#include <vector>



template<class>
struct Proxy {};

template<template<class...> class T, class First, class ...Types>
std::string printTypeList(Proxy<T<First, Types...>>)
{
    return (extrait::getActualTypeName<First>()
        + ((", " + extrait::getActualTypeName<Types>()) + ...) + "\n");
}

template<template<class...> class T>
std::string printTypeList(Proxy<T<>>)
{
    return "no types\n";
}

// Here we define our predicate which takes a template parameter T, which is the currently checked type of our
// input parameter-list
template<class T>
struct FloatingPointPredicate : std::bool_constant<std::is_floating_point_v<T>> {};

int main()
{
    using Input = std::tuple<int, float, long, short, char, double, float>;

    EXPECT_EQ((match_v   <MatchInput, ::FloatingPointPredicate>), 3);
    EXPECT_EQ((mismatch_v<MatchInput, ::FloatingPointPredicate>), 4);
    
    EXPECT_TRUE ((matchAny_v <MatchInput, ::FloatingPointPredicate>));
    EXPECT_FALSE((matchAll_v <MatchInput, ::FloatingPointPredicate>));
    EXPECT_FALSE((matchNone_v<MatchInput, ::FloatingPointPredicate>));
    
    std::cout
        << "Floating point types: " << extrait::match_v<Input, FloatingPointPredicate> << "\n"
        << "Non-floating point types: " << extrait::mismatch_v<Input, FloatingPointPredicate> << "\n"
        
        << std::boolalpha
        << "At least one type is floating point: " << extrait::matchAny_v<Input, FloatingPointPredicate> << "\n"
        << "All types are floating point: " << extrait::matchAll_v<Input, FloatingPointPredicate> << "\n"
        << "No type is floating point: " << extrait::matchNone_v<Input, FloatingPointPredicate> << "\n";

    // Commented out because these assert and fail compilation
    // extrait::match_v<int, ::FloatingPointPredicate>; // "int" is not a class template
    // extrait::match_v<std::array<float, 3>, ::FloatingPointPredicate>; // "std::array<float, 3>" has a non-type template parameter
    // extrait::match_v<MatchInput, Proxy>; // Proxy is not a valid predicate type, missing "value"
}
