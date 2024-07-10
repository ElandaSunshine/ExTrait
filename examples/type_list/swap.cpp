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
        << printTypeList(Proxy<extrait::swap_t<Input, 0, 6>>{})
        << printTypeList(Proxy<extrait::swap_t<Input, 0, 2>>{})
        << printTypeList(Proxy<extrait::swap_t<Input, 3, 4>>{})
        << printTypeList(Proxy<extrait::swap_t<Input, 4, 3>>{});

    // Commented out because these assert and fail compilation
    // extrait::swap_t<int, 0, 0>; // "int" is not a class template
    // extrait::swap_t<std::array<float, 3>, 0, 0>; // "std::array<float, 3>" has a non-type template parameter
    // extrait::swap_t<SwapInput, 7, 0>; // start index 7 out of bounds
    // extrait::swap_t<SwapInput, 0, 7>; // end index 7 out of bounds
    // extrait::swap_t<std::tuple<>, 0, 0>; // both indices 0 out of bounds
}
