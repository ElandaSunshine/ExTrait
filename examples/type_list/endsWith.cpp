#include <extrait/type_list.h>

// #include <array>
#include <iostream>
#include <vector>



// Our class template
template<class ...Types>
struct Foo {};

int main()
{
    std::cout << std::boolalpha
        << extrait::endsWith_v<std::tuple<int, long, short, void, char, bool, float>, char, bool, float> << '\n'
        << extrait::endsWith_v<std::vector<float>, std::allocator<float>> << '\n'
        << extrait::endsWith_v<std::tuple<>> << '\n'
        << extrait::endsWith_v<std::tuple<int, long, short, void, char, bool, float>, char, long, short> << '\n';

    // Commented out because these assert and fail compilation
    // extrait::endsWith_v<int, int>; // "int" is not a class template
    // extrait::endsWith_v<std::array<float, 3>, float>; // "std::array<float, 3>" has a non-type template parameter
}
