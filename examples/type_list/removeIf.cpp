#include <extrait/common.h>
#include <extrait/type_list.h>

// #include <array>
#include <iostream>



template<class>
struct Proxy {};

template<template<class...> class T, class First, class ...Types>
std::string printTypeList(Proxy<T<First, Types...>>)
{
    const std::string first(extrait::getActualTypeName<First>());
    return (first + ((", " + std::string(extrait::getActualTypeName<Types>())) + ...) + "\n");
}

template<template<class...> class T>
std::string printTypeList(Proxy<T<>>)
{
    return "no types\n";
}

// Here we define our predicate which takes a template parameter T, which is the currently checked type of our
// input parameter-list
// We want to remove/retain all types that are floating point
template<class T>
struct FloatingPointPredicate : std::bool_constant<std::is_floating_point_v<T>> {};

int main()
{
    using Input = std::tuple<int, float, char, short, char, double, float>;

    std::cout
        // prints the parameter list with all floating point types removed
        << printTypeList(Proxy<extrait::removeIf_t<Input, FloatingPointPredicate>>{})
        
        // prints the parameter list with only the floating point types remaining
        << printTypeList(Proxy<extrait::filter_t<Input, FloatingPointPredicate>>{});

    // Commented out because these assert and fail compilation
    // extrait::removeIf_t<int, FloatingPointPredicate>; // "int" is not a class template
    // extrait::removeIf_t<std::array<float, 3>, FloatingPointPredicate>; // "std::array<float, 3>" has a non-type template parameter
    // extrait::removeIf_t<Input, int>; // "int" is not a valid predicate type
}
