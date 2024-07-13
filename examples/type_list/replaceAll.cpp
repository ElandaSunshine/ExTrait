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
        << printTypeList(Proxy<extrait::replaceAll_t<Input, double, long>>{})
        << printTypeList(Proxy<extrait::replaceAll_t<Input, char, long, double, float>>{})
        << printTypeList(Proxy<extrait::replaceAll_t<std::tuple<>, char, long>>{});

    // Commented out because these assert and fail compilation
    // extrait::replaceAll_t<int, int, char>; // "int" is not a class template
    // extrait::replaceAll_t<std::array<float, 3>, float, char>; // "std::array<float, 3>" has a non-type template parameter
    // extrait::replaceAll_t<ReplaceInput, float>; // no replacement types specified
}
