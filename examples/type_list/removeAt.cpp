#include <extrait/common.h>
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

int main()
{
    using Input = std::tuple<int, float, char, short, char, double, float>;
    
    std::cout
        << printTypeList(Proxy<extrait::removeAt_t<Input, 5>>{})
        << printTypeList(Proxy<extrait::removeAt_t<Input, 2>>{});

    // Commented out because these assert and fail compilation
    // extrait::removeAt_t<int, 0>; // "int" is not a class template
    // extrait::removeAt_t<std::array<float, 3>, 0>; // "std::array<float, 3>" has a non-type template parameter
    // extrait::removeAt_t<std::tuple<>, 0>; // empty parameter-list, index 0 out of bounds
    // extrait::removeAt_t<ReplaceAllInput, 7>; index 7 out of bounds
}
