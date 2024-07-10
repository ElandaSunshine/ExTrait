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
    using Input = std::tuple<int, float, char, short, char, double, float>;
    
    std::cout
        << printTypeList(Proxy<extrait::replaceRange_t<Input, 0, 5, long>>{})
        << printTypeList(Proxy<extrait::replaceRange_t<Input, 7, 7, long, double, float>>{})
        << printTypeList(Proxy<extrait::replaceRange_t<Input, 0, 7, long, double, float>>{})
        << printTypeList(Proxy<extrait::replaceRange_t<std::tuple<>, 0, 0, long, double, float>>{});

    // Commented out because these assert and fail compilation
    // extrait::replaceRange_t<int, 0, 0, char>;  // "int" is not a class template
    // extrait::replaceRange_t<std::array<float, 3>, 0, 0, char>;  // "std::array<float, 3>" has a non-type template parameter
    // extrait::replaceRange_t<Input, 0, 8, char>; // end index 8 out of bounds
    // extrait::replaceRange_t<Input, 8, 8, char>; // start index 8 out of bounds
    // extrait::replaceRange_t<Input, 6, 4, char>; // start index greater than end index
}
