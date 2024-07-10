#include <extrait/common.h>
#include <extrait/type_list.h>

// #include <array>
#include <iostream>
#include <vector>



int main()
{
    using Input = std::tuple<int, float, long, short, char, double, float>;
    
    std::cout
        << extrait::getActualTypeName<extrait::get_t<Input, 4>>() << '\n'
        << extrait::getActualTypeName<extrait::get_t<std::vector<float>, 1>>() << '\n'
        << extrait::getActualTypeName<extrait::first_t<Input>>() << '\n'
        << extrait::getActualTypeName<extrait::last_t<Input>>() << '\n';

    // Commented out because these assert and fail compilation
    // extrait::get_t<int, 0>; // "int" is not a class template
    // extrait::get_t<std::array<float, 3>, 0>; // "std::array<float, 3>" has a non-type template parameter
    // extrait::get_t<TypeAtInput, 7>; // index 7 out of bounds
    // extrait::first_t<std::tuple<>>; // can't get first type of empty parameter-list
    // extrait::last_t<std::tuple<>>; // can't get last type of empty parameter-list
}
