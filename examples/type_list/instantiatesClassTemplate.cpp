#include <extrait/type_list.h>

#include <array>
#include <iostream>
#include <tuple>
#include <vector>



int main()
{
    std::cout << std::boolalpha
        << extrait::instantiatesClassTemplate_v<std::tuple<int>> << '\n'
        << extrait::instantiatesClassTemplate_v<std::vector<int>> << '\n'
        << extrait::instantiatesClassTemplate_v<std::array<int, 0>> << '\n'
        << extrait::instantiatesClassTemplate_v<int> << '\n';
}
