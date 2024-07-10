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
    using Input = std::tuple<int, double, float, float, char, short, char, double, int, float>;
    
    std::cout
        << printTypeList(Proxy<extrait::deduplicate_t<Input>>{})
        << printTypeList(Proxy<extrait::deduplicate_t<std::tuple<int, long, float, short, char, bool>>>{})
        << printTypeList(Proxy<extrait::deduplicate_t<std::tuple<>>>{});

    // Commented out because these assert and fail compilation
    // extrait::deduplicate_t<int>;  // "int" is not a class template
    // extrait::deduplicate_t<std::array<float, 3>>;  // "std::array<float, 3>" has a non-type template parameter
}
