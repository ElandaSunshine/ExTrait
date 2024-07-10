#include <extrait/type_list.h>

// #include <array>
#include <iostream>
#include <tuple>



int main()
{
    std::cout << std::boolalpha
        << extrait::contains_v<std::tuple<int, long, short, float>, short> << '\n'
        << extrait::contains_v<std::tuple<int, long, short, float>, int>   << '\n';

    // Commented out because these assert and fail compilation
    // extrait::contains_v<int, int>; // "int" is not a class template
    // extrait::contains_v<std::array<float, 3>, float>; // "std::array<float, 3>" has a non-type template parameter
    // extrait::contains_v<std::tuple<int, float>&, int>; // "std::tuple<int, float>&" is not a class template but a reference to a class template
}
