#include <extrait/type_list.h>

// #include <array>
#include <iostream>
#include <tuple>



int main()
{
    std::cout
        << extrait::length_v<std::tuple<int, float, long, short, char, double, float>> << '\n'
        << extrait::length_v<std::tuple<>> << '\n';
    
    // Commented out because these assert and fail compilation
    // extrait::length_v<int>; // "int" is not a class template
    // extrait::length_v<std::array<float, 3>>; // "std::array<float, 3>" has a non-type template parameter
}
