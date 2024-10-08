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
    @file   TypeTraits.cpp
    @date   30, April 2024
    
    ===============================================================
 */

#include <extrait/common.h>
#include <type_traits>
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
// region Suite Setup
//======================================================================================================================
namespace
{
    //==================================================================================================================
    struct TestMethod { void someMethod(int, long) {} int (**volatile const *const &hello)[][343]; };
    
    //==================================================================================================================
    template<class T>
    using TestSelect = extrait::select_t<
        // Cases
        extrait::branch<float,       std::is_floating_point_v<T>>,
        extrait::branch<std::size_t, std::is_unsigned_v<T>>,
        extrait::branch<int,         (sizeof(T) == 4)>,
        extrait::branch<int*,        std::is_array_v<T>>,
        
        // Default
        void
    >;
    
    template<class T>
    using TestAssemble = extrait::assemble_t<std::tuple,
        extrait::branch<char, std::is_integral_v<T>>,
        extrait::branch<short, std::is_integral_v<T>>,
        
        std::nullptr_t,
        
        extrait::branch<int, std::is_integral_v<T>>,
        extrait::branch<long, std::is_integral_v<T>>,
        extrait::branch<long long, std::is_integral_v<T>>,
        
        extrait::branch<float, std::is_floating_point_v<T>>,
        extrait::branch<double, std::is_floating_point_v<T>>,
        extrait::branch<long double, std::is_floating_point_v<T>>,
        
        std::tuple<>
    >;
}
//======================================================================================================================
// endregion Suite Setup
//**********************************************************************************************************************
// region Unit Tests
//======================================================================================================================
TEST(CommonSuite, StripTest)
{
    using namespace extrait;
    
    //....................
    EXPECT_TRUE((std::is_same_v<strip_t<int>,                  int>));
    EXPECT_TRUE((std::is_same_v<strip_t<int&>,                 int>));
    EXPECT_TRUE((std::is_same_v<strip_t<int&&>,                int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const int>,            int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const int&>,           int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const int&&>,          int>));
    EXPECT_TRUE((std::is_same_v<strip_t<volatile int>,         int>));
    EXPECT_TRUE((std::is_same_v<strip_t<volatile int&>,        int>));
    EXPECT_TRUE((std::is_same_v<strip_t<volatile int&&>,       int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const volatile int>,   int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const volatile int&>,  int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const volatile int&&>, int>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<int**const *>,                                           int>));
    EXPECT_TRUE((std::is_same_v<strip_t<int***&>,                                                int>));
    EXPECT_TRUE((std::is_same_v<strip_t<int***&&>,                                               int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const int**volatile *>,                                  int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const int***&>,                                          int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const int***&&>,                                         int>));
    EXPECT_TRUE((std::is_same_v<strip_t<volatile int***>,                                        int>));
    EXPECT_TRUE((std::is_same_v<strip_t<volatile int*const *volatile *&>,                        int>));
    EXPECT_TRUE((std::is_same_v<strip_t<volatile int***&&>,                                      int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const volatile int***>,                                  int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const volatile int***&>,                                 int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const volatile int *volatile *const volatile *const &&>, int>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<int***[][2][3]>,                    int>));
    EXPECT_TRUE((std::is_same_v<strip_t<int(***&)[][2][3]>,                 int>));
    EXPECT_TRUE((std::is_same_v<strip_t<int(***&&)[][2][3]>,                int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const int***[][2][3]>,              int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const int(***&)[][2][3]>,           int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const int(***&&)[][2][3]>,          int>));
    EXPECT_TRUE((std::is_same_v<strip_t<volatile int***[][2][3]>,           int>));
    EXPECT_TRUE((std::is_same_v<strip_t<volatile int(***&)[][2][3]>,        int>));
    EXPECT_TRUE((std::is_same_v<strip_t<volatile int(***&&)[][2][3]>,       int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const volatile int***[][2][3]>,     int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const volatile int(***&)[][2][3]>,  int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const volatile int(***&&)[][2][3]>, int>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<int***[2][3]>,                    int>));
    EXPECT_TRUE((std::is_same_v<strip_t<int(***&)[2][3]>,                 int>));
    EXPECT_TRUE((std::is_same_v<strip_t<int(***&&)[2][3]>,                int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const int***[2][3]>,              int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const int(***&)[2][3]>,           int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const int(***&&)[2][3]>,          int>));
    EXPECT_TRUE((std::is_same_v<strip_t<volatile int***[2][3]>,           int>));
    EXPECT_TRUE((std::is_same_v<strip_t<volatile int(***&)[2][3]>,        int>));
    EXPECT_TRUE((std::is_same_v<strip_t<volatile int(***&&)[2][3]>,       int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const volatile int***[2][3]>,     int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const volatile int(***&)[2][3]>,  int>));
    EXPECT_TRUE((std::is_same_v<strip_t<const volatile int(***&&)[2][3]>, int>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<decltype(TestMethod::hello)>, int>));
    EXPECT_TRUE((std::is_same_v<strip_t<int **volatile const *const TestMethod::*>, int>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(*)(int, long)>,                  void(int, long)>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(&)(int, long)>,                  void(int, long)>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(&&)(int, long)>,                 void(int, long)>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(***)(int, long)>,                void(int, long)>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(**&)(int, long)>,                void(int, long)>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(**&&)(int, long)>,               void(int, long)>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(**const volatile *)(int, long)>, void(int, long)>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(*const *&)(int, long)>,          void(int, long)>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(*volatile *&&)(int, long)>,      void(int, long)>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(*)(int, long)                  noexcept>, void(int, long) noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(&)(int, long)                  noexcept>, void(int, long) noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(&&)(int, long)                 noexcept>, void(int, long) noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(***)(int, long)                noexcept>, void(int, long) noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(**&)(int, long)                noexcept>, void(int, long) noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(**&&)(int, long)               noexcept>, void(int, long) noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(**const volatile *)(int, long) noexcept>, void(int, long) noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(*const *&)(int, long)          noexcept>, void(int, long) noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(*volatile *&&)(int, long)      noexcept>, void(int, long) noexcept>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)>,                  void(int, long)>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)>,                 void(int, long)>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)>,                void(int, long)>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)>,                void(int, long)>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)>,                void(int, long)>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)>,               void(int, long)>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long)>, void(int, long)>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)>,          void(int, long)>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)>,      void(int, long)>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  const>, void(int, long) const>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 const>, void(int, long) const>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                const>, void(int, long) const>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                const>, void(int, long) const>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                const>, void(int, long) const>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               const>, void(int, long) const>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) const>, void(int, long) const>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          const>, void(int, long) const>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      const>, void(int, long) const>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  volatile>, void(int, long) volatile>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 volatile>, void(int, long) volatile>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                volatile>, void(int, long) volatile>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                volatile>, void(int, long) volatile>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                volatile>, void(int, long) volatile>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               volatile>, void(int, long) volatile>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) volatile>, void(int, long) volatile>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          volatile>, void(int, long) volatile>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      volatile>, void(int, long) volatile>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  const volatile>, void(int, long) const volatile>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 const volatile>, void(int, long) const volatile>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                const volatile>, void(int, long) const volatile>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                const volatile>, void(int, long) const volatile>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                const volatile>, void(int, long) const volatile>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               const volatile>, void(int, long) const volatile>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) const volatile>, void(int, long) const volatile>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          const volatile>, void(int, long) const volatile>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      const volatile>, void(int, long) const volatile>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  &>, void(int, long) &>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 &>, void(int, long) &>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                &>, void(int, long) &>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                &>, void(int, long) &>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                &>, void(int, long) &>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               &>, void(int, long) &>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) &>, void(int, long) &>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          &>, void(int, long) &>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      &>, void(int, long) &>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  const&>, void(int, long) const&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 const&>, void(int, long) const&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                const&>, void(int, long) const&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                const&>, void(int, long) const&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                const&>, void(int, long) const&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               const&>, void(int, long) const&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) const&>, void(int, long) const&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          const&>, void(int, long) const&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      const&>, void(int, long) const&>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  volatile&>, void(int, long) volatile&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 volatile&>, void(int, long) volatile&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                volatile&>, void(int, long) volatile&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                volatile&>, void(int, long) volatile&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                volatile&>, void(int, long) volatile&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               volatile&>, void(int, long) volatile&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) volatile&>, void(int, long) volatile&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          volatile&>, void(int, long) volatile&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      volatile&>, void(int, long) volatile&>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  const volatile&>, void(int, long) const volatile&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 const volatile&>, void(int, long) const volatile&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                const volatile&>, void(int, long) const volatile&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                const volatile&>, void(int, long) const volatile&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                const volatile&>, void(int, long) const volatile&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               const volatile&>, void(int, long) const volatile&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) const volatile&>, void(int, long) const volatile&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          const volatile&>, void(int, long) const volatile&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      const volatile&>, void(int, long) const volatile&>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  &&>, void(int, long) &&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 &&>, void(int, long) &&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                &&>, void(int, long) &&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                &&>, void(int, long) &&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                &&>, void(int, long) &&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               &&>, void(int, long) &&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) &&>, void(int, long) &&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          &&>, void(int, long) &&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      &&>, void(int, long) &&>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  const&&>, void(int, long) const&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 const&&>, void(int, long) const&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                const&&>, void(int, long) const&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                const&&>, void(int, long) const&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                const&&>, void(int, long) const&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               const&&>, void(int, long) const&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) const&&>, void(int, long) const&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          const&&>, void(int, long) const&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      const&&>, void(int, long) const&&>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  volatile&&>, void(int, long) volatile&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 volatile&&>, void(int, long) volatile&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                volatile&&>, void(int, long) volatile&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                volatile&&>, void(int, long) volatile&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                volatile&&>, void(int, long) volatile&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               volatile&&>, void(int, long) volatile&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) volatile&&>, void(int, long) volatile&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          volatile&&>, void(int, long) volatile&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      volatile&&>, void(int, long) volatile&&>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  const volatile&&>, void(int, long) const volatile&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 const volatile&&>, void(int, long) const volatile&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                const volatile&&>, void(int, long) const volatile&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                const volatile&&>, void(int, long) const volatile&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                const volatile&&>, void(int, long) const volatile&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               const volatile&&>, void(int, long) const volatile&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) const volatile&&>, void(int, long) const volatile&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          const volatile&&>, void(int, long) const volatile&&>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      const volatile&&>, void(int, long) const volatile&&>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  noexcept>, void(int, long) noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 noexcept>, void(int, long) noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                noexcept>, void(int, long) noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                noexcept>, void(int, long) noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                noexcept>, void(int, long) noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               noexcept>, void(int, long) noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) noexcept>, void(int, long) noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          noexcept>, void(int, long) noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      noexcept>, void(int, long) noexcept>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  const noexcept>, void(int, long) const noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 const noexcept>, void(int, long) const noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                const noexcept>, void(int, long) const noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                const noexcept>, void(int, long) const noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                const noexcept>, void(int, long) const noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               const noexcept>, void(int, long) const noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) const noexcept>, void(int, long) const noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          const noexcept>, void(int, long) const noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      const noexcept>, void(int, long) const noexcept>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  volatile noexcept>, void(int, long) volatile noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 volatile noexcept>, void(int, long) volatile noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                volatile noexcept>, void(int, long) volatile noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                volatile noexcept>, void(int, long) volatile noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                volatile noexcept>, void(int, long) volatile noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               volatile noexcept>, void(int, long) volatile noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) volatile noexcept>, void(int, long) volatile noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          volatile noexcept>, void(int, long) volatile noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      volatile noexcept>, void(int, long) volatile noexcept>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  const volatile noexcept>, void(int, long) const volatile noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 const volatile noexcept>, void(int, long) const volatile noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                const volatile noexcept>, void(int, long) const volatile noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                const volatile noexcept>, void(int, long) const volatile noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                const volatile noexcept>, void(int, long) const volatile noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               const volatile noexcept>, void(int, long) const volatile noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) const volatile noexcept>, void(int, long) const volatile noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          const volatile noexcept>, void(int, long) const volatile noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      const volatile noexcept>, void(int, long) const volatile noexcept>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  & noexcept>, void(int, long) & noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 & noexcept>, void(int, long) & noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                & noexcept>, void(int, long) & noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                & noexcept>, void(int, long) & noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                & noexcept>, void(int, long) & noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               & noexcept>, void(int, long) & noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) & noexcept>, void(int, long) & noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          & noexcept>, void(int, long) & noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      & noexcept>, void(int, long) & noexcept>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  const& noexcept>, void(int, long) const& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 const& noexcept>, void(int, long) const& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                const& noexcept>, void(int, long) const& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                const& noexcept>, void(int, long) const& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                const& noexcept>, void(int, long) const& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               const& noexcept>, void(int, long) const& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) const& noexcept>, void(int, long) const& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          const& noexcept>, void(int, long) const& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      const& noexcept>, void(int, long) const& noexcept>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  volatile& noexcept>, void(int, long) volatile& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 volatile& noexcept>, void(int, long) volatile& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                volatile& noexcept>, void(int, long) volatile& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                volatile& noexcept>, void(int, long) volatile& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                volatile& noexcept>, void(int, long) volatile& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               volatile& noexcept>, void(int, long) volatile& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) volatile& noexcept>, void(int, long) volatile& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          volatile& noexcept>, void(int, long) volatile& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      volatile& noexcept>, void(int, long) volatile& noexcept>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  const volatile& noexcept>, void(int, long) const volatile& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 const volatile& noexcept>, void(int, long) const volatile& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                const volatile& noexcept>, void(int, long) const volatile& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                const volatile& noexcept>, void(int, long) const volatile& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                const volatile& noexcept>, void(int, long) const volatile& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               const volatile& noexcept>, void(int, long) const volatile& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) const volatile& noexcept>, void(int, long) const volatile& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          const volatile& noexcept>, void(int, long) const volatile& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      const volatile& noexcept>, void(int, long) const volatile& noexcept>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  && noexcept>, void(int, long) && noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 && noexcept>, void(int, long) && noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                && noexcept>, void(int, long) && noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                && noexcept>, void(int, long) && noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                && noexcept>, void(int, long) && noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               && noexcept>, void(int, long) && noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) && noexcept>, void(int, long) && noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          && noexcept>, void(int, long) && noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      && noexcept>, void(int, long) && noexcept>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  const&& noexcept>, void(int, long) const&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 const&& noexcept>, void(int, long) const&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                const&& noexcept>, void(int, long) const&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                const&& noexcept>, void(int, long) const&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                const&& noexcept>, void(int, long) const&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               const&& noexcept>, void(int, long) const&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) const&& noexcept>, void(int, long) const&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          const&& noexcept>, void(int, long) const&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      const&& noexcept>, void(int, long) const&& noexcept>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  volatile&& noexcept>, void(int, long) volatile&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 volatile&& noexcept>, void(int, long) volatile&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                volatile&& noexcept>, void(int, long) volatile&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                volatile&& noexcept>, void(int, long) volatile&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                volatile&& noexcept>, void(int, long) volatile&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               volatile&& noexcept>, void(int, long) volatile&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) volatile&& noexcept>, void(int, long) volatile&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          volatile&& noexcept>, void(int, long) volatile&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      volatile&& noexcept>, void(int, long) volatile&& noexcept>));
    
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*)(int, long)                  const volatile&& noexcept>, void(int, long) const volatile&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&)(int, long)                 const volatile&& noexcept>, void(int, long) const volatile&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*&&)(int, long)                const volatile&& noexcept>, void(int, long) const volatile&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::***)(int, long)                const volatile&& noexcept>, void(int, long) const volatile&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&)(int, long)                const volatile&& noexcept>, void(int, long) const volatile&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**&&)(int, long)               const volatile&& noexcept>, void(int, long) const volatile&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::**const volatile *)(int, long) const volatile&& noexcept>, void(int, long) const volatile&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*const *&)(int, long)          const volatile&& noexcept>, void(int, long) const volatile&& noexcept>));
    EXPECT_TRUE((std::is_same_v<strip_t<void(TestMethod::*volatile *&&)(int, long)      const volatile&& noexcept>, void(int, long) const volatile&& noexcept>));
}

TEST(CommonSuite, SelectionUtilsTest)
{
    using namespace extrait;

    //....................
    EXPECT_TRUE((std::is_same_v<int,         ::TestSelect<std::int32_t>>));
    EXPECT_TRUE((std::is_same_v<float,       ::TestSelect<double>>));
    EXPECT_TRUE((std::is_same_v<std::size_t, ::TestSelect<unsigned char>>));
    EXPECT_TRUE((std::is_same_v<int*,        ::TestSelect<int[34][34]>>));
    EXPECT_TRUE((std::is_same_v<void,        ::TestSelect<std::nullptr_t>>));
    
    //....................
    EXPECT_TRUE((std::is_same_v<
        std::tuple<char, short, std::nullptr_t, int, long, long long, std::tuple<>>,
        ::TestAssemble<int>
    >)) << extrait::getActualTypeName<::TestAssemble<int>>();
    EXPECT_TRUE((std::is_same_v<
        std::tuple<char, short, std::nullptr_t, int, long, long long, std::tuple<>>,
        ::TestAssemble<char>
    >)) << extrait::getActualTypeName<::TestAssemble<char>>();
    EXPECT_TRUE((std::is_same_v<
        std::tuple<std::nullptr_t, float, double, long double, std::tuple<>>,
        ::TestAssemble<float>
    >)) << extrait::getActualTypeName<::TestAssemble<float>>();
    EXPECT_TRUE((std::is_same_v<
        std::tuple<std::nullptr_t, float, double, long double, std::tuple<>>,
        ::TestAssemble<long double>
    >)) << extrait::getActualTypeName<::TestAssemble<long double>>();
    EXPECT_TRUE((std::is_same_v<
        std::tuple<std::nullptr_t, std::tuple<>>,
        ::TestAssemble<std::nullptr_t>
    >)) << extrait::getActualTypeName<::TestAssemble<std::nullptr_t>>();
}

TEST(CommonSuite, MiscTest)
{
    
}
//======================================================================================================================
// endregion Unit Tests
//**********************************************************************************************************************
