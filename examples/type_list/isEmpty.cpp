#include <extrait/type_list.h>

// #include <array>
#include <iostream>
#include <tuple>



template<class = void, class ...Args>
struct withDefaultParameter {};

int main()
{
    std::cout << std::boolalpha
        << extrait::isEmpty_v<std::tuple<>> << '\n'
        << extrait::isEmpty_v<::withDefaultParameter<>> << '\n'
        << extrait::isEmpty_v<std::tuple<int>> << '\n';

    // Commented out because these assert and fail compilation
    // extrait::isEmpty_v<int>; // "int" is not a class template
    // extrait::isEmpty_v<std::array<float, 3>>; // "std::array<float, 3>" has a non-type template parameter
}
