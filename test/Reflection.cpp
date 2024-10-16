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
    @file   Reflection.cpp
    @date   30, April 2024
    
    ===============================================================
 */

#include <extrait/reflection.h>

#include <gtest/gtest.h>



//**********************************************************************************************************************
// region Preprocessor
//======================================================================================================================
#ifndef EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS
    #define EXTRAIT_TEST_SUITE_TYPE_TRAITS_TEST_ASSERTS 0
#endif
//======================================================================================================================
// endregion Preprocessor
//**********************************************************************************************************************
// region Suite Setup
//======================================================================================================================
namespace
{
    //==================================================================================================================
    struct TestMethod
    {
        long someMethod(int x, long y) const && noexcept { return (x * y); }
        long someMethod(int x, long y) const & noexcept { return (x * y); }
        
        void someOtherMethod(int, long, double) const && noexcept {}
        void someOtherMethod(int) volatile noexcept {}
        void someOtherMethod() const volatile & {}
        
        int (**volatile const *const hello_bla)[][343] {};
        int (**volatile const *const &hello)[][343] { hello_bla };
    };
    
    //==================================================================================================================
    long test(int x, float y) noexcept { return (x * y); }
    long test2(int x, float y, double z) { return (x * y * z); }
}
//======================================================================================================================
// endregion Suite Setup
//**********************************************************************************************************************
// region Unit Tests
//======================================================================================================================
TEST(ReflectionSuite, TestFunction)
{
    //==================================================================================================================
    using namespace extrait;
    
    //------------------------------------------------------------------------------------------------------------------
    EXPECT_TRUE((std::is_same_v<FunctionPointer_t<void(bool, bool(*)(int))>,                               void(*)(bool, bool(*)(int))>));
    EXPECT_TRUE((std::is_same_v<MemberFunctionPointer_t<TestMethod, void(int, long) const && noexcept>,    void(TestMethod::*)(int, long) const && noexcept>));
    EXPECT_TRUE((std::is_same_v<MemberObjectPointer_t<TestMethod, int **volatile const *const[][343]>,     int **volatile const *const (TestMethod::*)[][343]>));
    
    using FreeFunc = Function<::test>;
    EXPECT_TRUE((std::is_same_v<FreeFunc::Parameters,    TypeArray<int, float>>));
    EXPECT_TRUE((std::is_same_v<FreeFunc::Owner,         void>));
    EXPECT_TRUE((std::is_same_v<FreeFunc::Return,        long>));
    EXPECT_TRUE((std::is_same_v<FreeFunc::Pointer,       long(*)(int, float) noexcept>));
    EXPECT_TRUE((std::is_same_v<FreeFunc::Signature,     long(int, float) noexcept>));
    
    EXPECT_EQ(FreeFunc::value, ::test);
    EXPECT_EQ(FreeFunc::parameterCount, 2);
    
    EXPECT_FALSE(FreeFunc::isMemberFunction);
    EXPECT_FALSE(FreeFunc::isConstQualified);
    EXPECT_FALSE(FreeFunc::isVolatileQualified);
    EXPECT_FALSE(FreeFunc::isLvalueQualified);
    EXPECT_FALSE(FreeFunc::isRvalueQualified);
    
    EXPECT_TRUE (FreeFunc::isNoexcept);
    EXPECT_FALSE(Function<::test2>::isNoexcept);
    
    EXPECT_TRUE((std::is_same_v<funcParameterList_t<::test>, TypeArray<int, float>>));
    EXPECT_TRUE((std::is_same_v<funcOwnerType_t<::test>,     void>));
    EXPECT_TRUE((std::is_same_v<funcReturnType_t<::test>,    long>));
    EXPECT_TRUE((std::is_same_v<funcSignature_t<::test>,     long(int, float) noexcept>));
    
    EXPECT_EQ(funcParameterCount_v<::test>, 2);
    
    EXPECT_FALSE(isMemberFunction_v<::test>);
    EXPECT_FALSE(isFuncConstQualified_v<::test>);
    EXPECT_FALSE(isFuncVolatileQualified_v<::test>);
    EXPECT_FALSE(isFuncLvalueQualified_v<::test>);
    EXPECT_FALSE(isFuncRvalueQualified_v<::test>);
    
    EXPECT_TRUE (isFuncNoexcept_v<::test>);
    EXPECT_FALSE(isFuncNoexcept_v<::test2>);
    
    static constexpr auto ov = Overload<long(int, long) const && noexcept>::of(&TestMethod::someMethod);
    using MemFunc = Function<ov>;
    EXPECT_TRUE((std::is_same_v<MemFunc::Parameters,    TypeArray<int, long>>));
    EXPECT_TRUE((std::is_same_v<MemFunc::Owner,         ::TestMethod>));
    EXPECT_TRUE((std::is_same_v<MemFunc::Return,        long>));
    EXPECT_TRUE((std::is_same_v<MemFunc::Pointer,       long(TestMethod::*)(int, long) const && noexcept>));
    EXPECT_TRUE((std::is_same_v<MemFunc::Signature,     long(int, long) const && noexcept>));
    
    EXPECT_EQ(MemFunc::value, ov);
    EXPECT_EQ(MemFunc::parameterCount, 2);
    
    EXPECT_TRUE (MemFunc::isMemberFunction);
    EXPECT_TRUE (MemFunc::isNoexcept);
    EXPECT_TRUE (MemFunc::isConstQualified);
    EXPECT_TRUE (MemFunc::isRvalueQualified);
    EXPECT_FALSE(MemFunc::isVolatileQualified);
    EXPECT_FALSE(MemFunc::isLvalueQualified);
    
    EXPECT_TRUE((std::is_same_v<funcParameterList_t<ov>, TypeArray<int, long>>));
    EXPECT_TRUE((std::is_same_v<funcOwnerType_t<ov>,     ::TestMethod>));
    EXPECT_TRUE((std::is_same_v<funcReturnType_t<ov>,    long>));
    EXPECT_TRUE((std::is_same_v<funcSignature_t<ov>,     long(int, long) const && noexcept>));
    
    EXPECT_EQ(funcParameterCount_v<ov>, 2);
    
    EXPECT_TRUE (isMemberFunction_v<ov>);
    EXPECT_TRUE (isFuncNoexcept_v<ov>);
    EXPECT_TRUE (isFuncConstQualified_v<ov>);
    EXPECT_TRUE (isFuncRvalueQualified_v<ov>);
    EXPECT_FALSE(isFuncVolatileQualified_v<ov>);
    EXPECT_FALSE(isFuncLvalueQualified_v<ov>);
    
    //....................
    EXPECT_TRUE((std::is_same_v<decltype(Overload<void(int, long, double) const && noexcept>::of(&TestMethod::someOtherMethod)), void(TestMethod::*)(int, long, double) const && noexcept>));
    EXPECT_TRUE((std::is_same_v<decltype(Overload<void(int) volatile noexcept>::of(&TestMethod::someOtherMethod)), void(TestMethod::*)(int) volatile noexcept>));
    EXPECT_TRUE((std::is_same_v<decltype(Overload<void() const volatile &>::of(&TestMethod::someOtherMethod)), void(TestMethod::*)() const volatile &>));
    
    EXPECT_FALSE((std::is_same_v<decltype(Overload<void(int, long, double) const && noexcept>::of(&TestMethod::someOtherMethod)), void(TestMethod::*)(int, long, double) const &&>));
    EXPECT_FALSE((std::is_same_v<decltype(Overload<void(int) volatile noexcept>::of(&TestMethod::someOtherMethod)), void(TestMethod::*)(int) noexcept>));
    EXPECT_FALSE((std::is_same_v<decltype(Overload<void() const volatile &>::of(&TestMethod::someOtherMethod)), void(TestMethod::*)() const volatile & noexcept>));

    //....................
    EXPECT_EQ((Function<::test>::invoke(nullptr, 2, 5.0f)), 10);
    EXPECT_EQ((Function<ov>::invoke(TestMethod{}, 2, 5)), 10);

    //....................
    EXPECT_NE(Function<::test>::toString(), "");
    EXPECT_NE(Function<ov>::toString(),     "");
}

//======================================================================================================================
// endregion Unit Tests
//**********************************************************************************************************************
