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
        << printTypeList(Proxy<extrait::replaceAt_t<Input, 5, long>>{})
        << printTypeList(Proxy<extrait::replaceAt_t<Input, 2, long, double, float>>{});

    // Commented out because these assert and fail compilation
    // extrait::replaceAt_t<int, int, char>; // "int" is not a class template
    // extrait::replaceAt_t<std::array<float, 3>, float, char>; // "std::array<float, 3>" has a non-type template parameter
    // extrait::replaceAt_t<std::tuple<>, 0, char>; // empty parameter-list, index 0 out of bounds
    // extrait::replaceAt_t<ReplaceAllInput, 0>; // no replacement types specified
    // extrait::replaceAt_t<ReplaceAllInput, 7, char>; index 7 out of bounds
}
