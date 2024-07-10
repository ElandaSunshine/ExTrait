#include <extrait/type_list.h>

// #include <array>
#include <iostream>
#include <tuple>
#include <vector>


// Our class template
template<class ...Types>
struct Foo {};

int main()
{
    std::cout << std::boolalpha
        << extrait::sameTemplateArguments_v<std::tuple<int, long, short>, std::tuple<int, long, short>> << '\n'
        << extrait::sameTemplateArguments_v<::Foo<int, long, short>, std::tuple<int, long, short>> << '\n'
        << extrait::sameTemplateArguments_v<std::vector<int>,             std::tuple<int, std::allocator<int>>> << '\n'
        << extrait::sameTemplateArguments_v<std::tuple<int, long, short>, std::tuple<int, long, short, char>> << '\n'
        << extrait::sameTemplateArguments_v<::Foo<int, long, short>, std::tuple<int, long, short, long>> << '\n';

    // Commented out because these assert and fail compilation
    // extrait::sameTemplateArguments_v<int, std::tuple<int, long, short>>; // "int" is not a class template
    // extrait::sameTemplateArguments_v<std::array<float, 3>, std::tuple<int, long, short>>; // "std::array<float, 3>" has a non-type template parameter
}
