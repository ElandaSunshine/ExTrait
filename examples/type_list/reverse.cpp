#include <extrait/common.h>
#include <extrait/type_list.h>

// #include <array>
#include <iostream>
#include <tuple>



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
    std::cout
        << printTypeList(Proxy<extrait::reverse_t<std::tuple<long, float, int>>>{})
        << printTypeList(Proxy<extrait::reverse_t<std::tuple<int, float, long, char, short>>>{})
        << printTypeList(Proxy<extrait::reverse_t<std::tuple<>>>{});

    // Commented out because these assert and fail compilation
    // extrait::reverse_t<int>; // "int" is not a class template
    // extrait::reverse_t<std::array<float, 3>>; // "std::array<float, 3>" has a non-type template parameter
}
