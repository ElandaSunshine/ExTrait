#include <extrait/type_list.h>
#include <iostream>
#include <vector>



int main()
{
    std::cout << std::boolalpha
        << extrait::hasTypeList_v<std::tuple<int>> << '\n'
        << extrait::hasTypeList_v<std::vector<int>> << '\n'
        << extrait::hasTypeList_v<std::array<int, 0>> << '\n'
        << extrait::hasTypeList_v<int> << '\n';
}
