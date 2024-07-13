#include <extrait/type_list.h>

// #include <array>
#include <iostream>



// Our class template
template<class ...Types>
struct Foo {};

// Another class template
template<class ...Types>
struct Bar {};

int main()
{
    std::cout << std::boolalpha
        << extrait::sameClassTemplate_v<Foo<float, void>, Foo<float, void>> << '\n'
        << extrait::sameClassTemplate_v<Foo<float, void>, Foo<int, float, long>> << '\n'
        << extrait::sameClassTemplate_v<Bar<float, void>, Bar<int, float, long>> << '\n'
        << extrait::sameClassTemplate_v<Foo<float, void>, Bar<int, float, long>> << '\n';

    // Commented out because these assert and fail compilation
    // extrait::sameClassTemplate_v<int, Foo<float>>; // "int" is not a class template
    // extrait::sameClassTemplate_v<std::array<float, 3>, Foo<float>>; // "std::array<float, 3>" has a non-type template parameter
    // extrait::sameClassTemplate_v<Foo<float>&, Foo<float>>; // "std::vector<float>&" is not a class template but a reference to a class template
}
