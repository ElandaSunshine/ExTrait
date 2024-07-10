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
        << printTypeList(Proxy<extrait::removeAll_t<Input, double>>{})
        << printTypeList(Proxy<extrait::removeAll_t<Input, char>>{})
        << printTypeList(Proxy<extrait::removeAll_t<std::tuple<>, char>>{});

    // Commented out because these assert and fail compilation
    // extrait::removeAll_t<int, int>; // "int" is not a class template
    // extrait::removeAll_t<std::array<float, 3>, float>; // "std::array<float, 3>" has a non-type template parameter
}
