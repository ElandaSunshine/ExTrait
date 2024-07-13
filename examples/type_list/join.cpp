#include <extrait/common.h>
#include <extrait/type_list.h>

// #include <array>
#include <iostream>
#include <tuple>
#include <vector>



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
    std::cout
        << printTypeList(Proxy<extrait::join_t<std::tuple, std::tuple<int>, std::tuple<long>, std::tuple<float>>>{})
        << printTypeList(Proxy<extrait::join_t<std::tuple, std::tuple<>, std::tuple<>, std::tuple<>>>{})
        << printTypeList(Proxy<extrait::join_t<std::tuple, std::vector<float>, std::tuple<int>>>{})
        << printTypeList(Proxy<extrait::join_t<std::tuple, std::tuple<int>, std::tuple<long>>>{});

    // Commented out because these assert and fail compilation
    // extrait::join_t<std::tuple, std::tuple<int>, int>; // "int" is not a class template
    // extrait::join_t<std::tuple, std::tuple<int>, std::array<float, 3>>; // "std::array<float, 3>" has a non-type template parameter
}
