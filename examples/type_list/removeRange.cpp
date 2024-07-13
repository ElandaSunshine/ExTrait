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
        << printTypeList(Proxy<extrait::removeRange_t<Input, 0, 5>>{})
        << printTypeList(Proxy<extrait::removeRange_t<Input, 7, 7>>{})
        << printTypeList(Proxy<extrait::removeRange_t<Input, 0, 7>>{})
        << printTypeList(Proxy<extrait::removeRange_t<std::tuple<>, 0, 0>>{});

    // Commented out because these assert and fail compilation
    // extrait::removeRange_t<int, 0, 0>;  // "int" is not a class template
    // extrait::removeRange_t<std::array<float, 3>, 0, 0>;  // "std::array<float, 3>" has a non-type template parameter
    // extrait::removeRange_t<Input, 0, 8>; // end index 8 out of bounds
    // extrait::removeRange_t<Input, 8, 8>; // start index 8 out of bounds
    // extrait::removeRange_t<Input, 6, 4>; // start index greater than end index
}
