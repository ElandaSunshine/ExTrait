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
    using Input = std::tuple<int, double, float>;
    
    std::cout
        << printTypeList(Proxy<extrait::addIfAbsent_t<Input, char, float, double, int, bool, double, float>>{})
        << printTypeList(Proxy<extrait::addIfAbsent_t<std::tuple<>, char, bool>>{});

    // Commented out because these assert and fail compilation
    // extrait::addIfAbsent_t<int, float>; // "int" is not a class template
    // extrait::addIfAbsent_t<std::array<float, 3>, float>; // "std::array<float, 3>" has a non-type template parameter
    // extrait::addIfAbsent_t<AddInput>; // no types to add specified
}
