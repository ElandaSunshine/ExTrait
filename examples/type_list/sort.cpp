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

// Our comparer for the sorting, this sorts based on size of types, smallest to biggest
// Our Key here is the pivot, it will be compared to all of its preceding types which are T
// And if Key is smaller than T, we evaluate to "true" so that Key will be sorted before T
template<class T, class Key>
struct Comparer
{
    constexpr static bool value = (sizeof(Key) < sizeof(T));
};

int main()
{
    using Input = std::tuple<long long, int, long, bool, short, short, double, float, char, long double>;
    
    std::cout
        << printTypeList(Proxy<extrait::sort_t<Input, Comparer>>{});

    // Commented out because these assert and fail compilation
    // extrait::sort_t<int, Comparer>; // "int" is not a class template
    // extrait::sort_t<std::array<float, 3>, Comparer>; // "std::array<float, 3>" has a non-type template parameter
}
