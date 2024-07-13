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

int main()
{
    using Input = std::tuple<int, float, char, short, char, double, float>;
    
    std::cout
        << printTypeList(Proxy<extrait::rotate_t<Input, 1, 3, 6>>{})
        << printTypeList(Proxy<extrait::rotate_t<Input, 0, 3, 7>>{});

    // Commented out because these assert and fail compilation
    // extrait::rotate_t<int, 0, 0, 0>; // "int" is not a class template
    // extrait::rotate_t<std::array<float, 3>, 0, 0, 0>; // "std::array<float, 3>" has a non-type template parameter
    // extrait::rotate_t<RotateInput, 8, 0, 0>; // start index 8 out of bounds
    // extrait::rotate_t<RotateInput, 0, 0, 8>; // end index 8 out of bounds
    // extrait::rotate_t<RotateInput, 0, 1, 0>; // middle index 1 is greater than end index 0
    // extrait::rotate_t<RotateInput, 1, 0, 1>; // middle index 0 is less than start index 1

}
