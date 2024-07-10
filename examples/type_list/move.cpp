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
        << printTypeList(Proxy<extrait::move_t<Input, 1, 6>>{})
        << printTypeList(Proxy<extrait::move_t<Input, 6, 1>>{});

    // Commented out because these assert and fail compilation
    // extrait::move_t<int, 0, 0>; // "int" is not a class template
    // extrait::move_t<std::array<float, 3>, 0, 0>; // "std::array<float, 3>" has a non-type template parameter
    // extrait::move_t<RotateInput, 8, 0>; // start index 8 out of bounds
    // extrait::move_t<RotateInput, 0, 8>; // end index 8 out of bounds
    // extrait::move_t<std::tuple<>, 0, 0>;  // both indices 0 out of bounds
}
