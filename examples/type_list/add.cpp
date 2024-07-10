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
        << printTypeList(Proxy<extrait::add_t<Input, char, bool>>{})
        << printTypeList(Proxy<extrait::add_t<std::tuple<>, char, bool>>{})
        << printTypeList(Proxy<extrait::replace_t<std::tuple<>, char, long>>{});

    // Commented out because these assert and fail compilation
    // extrait::add_t<int, float>; // "int" is not a class template
    // extrait::add_t<std::array<float, 3>, float>; // "std::array<float, 3>" has a non-type template parameter
    // extrait::add_t<AddInput>; // no types to add specified
}
