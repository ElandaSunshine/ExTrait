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
    using Input = std::tuple<int, float, long, short, char, double, float>;
    
    std::cout
        << printTypeList(Proxy<extrait::sublist_t<Input, 0, 3>>{})
        << printTypeList(Proxy<extrait::sublist_t<Input, 2, 6>>{})
        << printTypeList(Proxy<extrait::sublist_t<Input, 5, 7>>{})
        << printTypeList(Proxy<extrait::sublist_t<Input, 0, 0>>{})
        << printTypeList(Proxy<extrait::sublist_t<Input, 7, 7>>{})
        << printTypeList(Proxy<extrait::sublist_t<std::tuple<>, 0, 0>>{});

    // Commented out because these assert and fail compilation
    // extrait::sublist_t<int, 0, 0>; // "int" is not a class template
    // extrait::sublist_t<std::array<float, 3>, 0, 0>; // "std::array<float, 3>" has a non-type template parameter
    // extrait::sublist_t<Input, 0, 8>; // 8 end index is out of bounds
    // extrait::sublist_t<Input, 8, 8>; // 8 start index is out of bounds
    // extrait::sublist_t<Input, 7, 4>; // 4 end index is smaller than 7 start index
}
