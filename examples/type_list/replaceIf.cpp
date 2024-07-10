#include <extrait/common.h>
#include <extrait/predicate.h>
#include <extrait/type_list.h>

// #include <array>
#include <iostream>



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
// We want to replace all types that are/aren't floating point
template<class T>
struct FloatingPointPredicate : std::bool_constant<std::is_floating_point_v<T>> {};

int main()
{
    using Input = std::tuple<int, float, char, short, char, double, float>;

    std::cout
        // prints the parameter list with all floating point types replaced by int
        << printTypeList(Proxy<extrait::replaceIf_t<Input, FloatingPointPredicate, int>>{})
        
        // prints the parameter list with only the non-floating point types replaced by int
        << printTypeList(Proxy<extrait::replaceIfNot_t<Input, FloatingPointPredicate, int>>{});

    // Commented out because these assert and fail compilation
    // extrait::replaceIf_t<int, FloatingPointPredicate, char>; // "int" is not a class template
    // extrait::replaceIf_t<std::array<float, 3>, FloatingPointPredicate, char>; // "std::array<float, 3>" has a non-type template parameter
    // extrait::replaceIf_t<Input, int, char>; // "int" is not a valid predicate type
    // extrait::replaceIf_t<Input, FloatingPointPredicate>; // no replacement types specified
}
