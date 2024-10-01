/**
    
    
    ++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--
    -                      __.....__                                              .--.                             +
    +                  .-''         '.                                            |__|                             -
    -                 /     .-''"'-.  `.                     .|  .-,.--.          .--.     .|                      +
    +                /     /________\   \ ____     _____   .' |_ |  .-. |    __   |  |   .' |_                     -
    -                |                  |`.   \  .'    / .'     || |  | | .:--.'. |  | .'     |                    +
    +                \    .-------------'  `.  `'    .' '--.  .-'| |  | |/ |   \ ||  |'--.  .-'                    -
    -                 \    '-.____...---.    '.    .'      |  |  | |  '- `" __ | ||  |   |  |                      +
    +                  `.             .'     .'     `.     |  |  | |      .'.''| ||__|   |  |                      -
    -                    `''-...... -'     .'  .'`.   `.   |  '.'| |     / /   | |_      |  '.'                    +
    +                                    .'   /    `.   `. |   / |_|     \ \._,\ '/      |   /                     -
    -                                   '----'       '----'`'-'           `--'  `"       `'-'                      +
    ++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--
    
    
    
    MIT License
    
    Copyright (c) 2024 ElandaSunshine
    
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
    
    ===============================================================
    
    @author Elanda
    @file   Stringable.cpp
    @date   09, July 2024
    
    ===============================================================
 */

#include <extrait/stringable.h>
#include <gtest/gtest.h>



//**********************************************************************************************************************
// region Preprocessor
//======================================================================================================================
#ifndef EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    #define EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS 1
#endif
//======================================================================================================================
// endregion Preprocessor
//**********************************************************************************************************************
// region Unit Tests
//======================================================================================================================
TEST(CommonSuite, StripTest)
{
    using namespace extrait;
    
    //....................
    EXPECT_EQ("null",  toString(nullptr));
    EXPECT_EQ("false", toString(false));
    EXPECT_EQ("true",  toString(true));
    
    int val = 0;
    int *ptr = &val;
    EXPECT_EQ(detail::addressToString(ptr), toString(ptr));
    
    int **ptr2 = &ptr;
    EXPECT_EQ(detail::addressToString(ptr2), toString(ptr2));
    
    int ***ptr3 = &ptr2;
    EXPECT_EQ(detail::addressToString(ptr3), toString(ptr3));
    
    std::string_view stv = "Hello world!";
    EXPECT_EQ(R"("Hello world!")", toString(stv));
    
    std::array arr{ 0, 1, 3, 5, 7, 42, 69, 140, 420, 666 };
    EXPECT_EQ("[0, 1, 3, 5, 7, 42, 69, 140, 420, 666]", toString(arr)) << getActualTypeName(arr);

    std::vector<int> vec { 0, 1, 3, 5, 7, 42, 69, 140, 420, 666 };
    EXPECT_EQ("[0, 1, 3, 5, 7, 42, 69, 140, 420, 666]", toString(vec)) << getActualTypeName(vec);
    
    std::deque<int> deq { 0, 1, 3, 5, 7, 42, 69, 140, 420, 666 };
    EXPECT_EQ("[0, 1, 3, 5, 7, 42, 69, 140, 420, 666]", toString(deq)) << getActualTypeName(deq);
    
    std::queue<int> que(deq);
    EXPECT_EQ("[0, 1, 3, 5, 7, 42, 69, 140, 420, 666]", toString(que)) << getActualTypeName(que);
    
    std::list<int> lst { 0, 1, 3, 5, 7, 42, 69, 140, 420, 666 };
    EXPECT_EQ("[0, 1, 3, 5, 7, 42, 69, 140, 420, 666]", toString(lst)) << getActualTypeName(lst);
    
    std::forward_list<int> flst { 0, 1, 3, 5, 7, 42, 69, 140, 420, 666 };
    EXPECT_EQ("[0, 1, 3, 5, 7, 42, 69, 140, 420, 666]", toString(flst)) << getActualTypeName(flst);
    
    std::set<int> set { 42, 0, 1, 3, 140, 5, 666, 7, 42, 69, 420, 42, 420 };
    EXPECT_EQ("[0, 1, 3, 5, 7, 42, 69, 140, 420, 666]", toString(set)) << getActualTypeName(set);
    
    std::stack<int> stck(deq);
    EXPECT_EQ("[0, 1, 3, 5, 7, 42, 69, 140, 420, 666]", toString(stck)) << getActualTypeName(stck);
    
    std::priority_queue pque(std::greater<int>{}, vec);
    EXPECT_EQ("[0, 1, 3, 5, 7, 42, 69, 140, 420, 666]", toString(pque)) << getActualTypeName(pque);
    
    std::multiset<int> mset { 42, 0, 1, 3, 140, 5, 666, 7, 42, 69, 420, 42, 420 };
    EXPECT_EQ("[0, 1, 3, 5, 7, 42, 42, 42, 69, 140, 420, 420, 666]", toString(mset)) << getActualTypeName(mset);
    
    std::map<int, std::string> map {
        {   0, "zero"        },
        {   7, "seven"       },
        {  42, "forty two"   },
        {  69, "sixty nine"  },
        { 420, "BLAZEIT"     },
        { 666, "six six six" }
    };
    EXPECT_EQ(R"({0="zero", 7="seven", 42="forty two", 69="sixty nine", 420="BLAZEIT", 666="six six six"})", toString(map)) << getActualTypeName(map);
    
    std::multimap<int, std::string> mmap {
        {  69, "sixty nine"  },
        {   0, "zero"        },
        {   7, "seven"       },
        {  42, "forty two"   },
        {  69, "sixty nine"  },
        { 420, "BLAZEIT"     },
        { 666, "six six six" },
        {  42, "forty two"   }
    };
    EXPECT_EQ(R"({0="zero", 7="seven", 42="forty two", 42="forty two", 69="sixty nine", 69="sixty nine", 420="BLAZEIT", 666="six six six"})", toString(mmap)) << getActualTypeName(mmap);
}
//======================================================================================================================
// endregion Unit Tests
//**********************************************************************************************************************
