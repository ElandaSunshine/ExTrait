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
    using Input = std::tuple<int, double, float>;
    
    std::cout
        << printTypeList(Proxy<extrait::insert_t<Input, 2, float, double>>{}) // Insert at position 2
        << printTypeList(Proxy<extrait::insert_t<Input, 0, char, bool>>{}) // Insert at the start
        << printTypeList(Proxy<extrait::insert_t<Input, extrait::length_v<Input>, char, bool>>{}); // insert at the end

    // Commented out because these assert and fail compilation
    // extrait::insert_t<int, 0, int>; // "int" is not a class template
    // extrait::insert_t<std::array<float, 3>, 0, int>; // "std::array<float, 3>" has a non-type template parameter
    // extrait::insert_t<AddIfAbsentInput, 0>; // no types to add specified
    // extrait::insert_t<AddIfAbsentInput, 4, float>; // index 4 out of bounds
    // extrait::insert_t<std::tuple<>, 1, float>; // index 1 out of bounds, 0 is allowed since we know that we can add to the end
}
