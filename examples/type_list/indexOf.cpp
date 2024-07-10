#include <extrait/type_list.h>

// #include <array>
#include <iostream>
#include <tuple>



int main()
{
    using Input = std::tuple<int, float, long, short, char, double, float>;
    
    std::cout
        << extrait::indexOf_v<Input, float> << '\n'
        << extrait::indexOf_v<Input, double> << '\n'
        << extrait::indexOf_v<Input, long long> << '\n'
        << extrait::indexOf_v<std::tuple<>, long long> << '\n';
    
    // Commented out because these assert and fail compilation
    // extrait::indexOf_v<int, int>; // "int" is not a class template
    // extrait::indexOf_v<std::array<float, 3>, float>; // "std::array<float, 3>" has a non-type template parameter
}
