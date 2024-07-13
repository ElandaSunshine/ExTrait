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

template<class T>
struct Mapper
{
    using type = std::conditional_t<
        std::is_integral_v<T>,
            std::add_lvalue_reference<T>,
            T
    >;
};

int main()
{
    using Input = std::tuple<int, float, char, short, char, double, float>;
    
    // Our mapper will add an lvalue-reference to every type if it is an integral type (and if it already isn't a reference type)
    // otherwise will leave the type as-is
    std::cout
        << printTypeList(Proxy<extrait::map_t<Input, Mapper>>{});

    // Commented out because these assert and fail compilation
    // extrait::map_t<int, ::RefMapper>; // "int" is not a class template
    // extrait::map_t<std::array<float, 3>, ::RefMapper>; // "std::array<float, 3>" has a non-type template parameter
    // extrait::map_t<MapInput, Foo>; // Foo might not be a valid mapper
}
