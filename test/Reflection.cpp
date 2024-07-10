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
        void someMethod(int, long) const && noexcept {}
        
        void someOtherMethod(int, long, double) const && noexcept {}
        void someOtherMethod(int) volatile noexcept {}
        void someOtherMethod() const volatile & {}
        
        int (**volatile const *const &hello)[][343];
    };
    
    //==================================================================================================================
    long test(int, float) noexcept { return 0; }
    long test2(int, float, double)  { return 0; }
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
    
    EXPECT_EQ(FreeFunc::funcPtr, ::test);
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
    
    EXPECT_TRUE (isFuncNoexceptSpecified_v<::test>);
    EXPECT_FALSE(isFuncNoexceptSpecified_v<::test2>);
    
    using MemFunc = Function<&::TestMethod::someMethod>;
    EXPECT_TRUE((std::is_same_v<MemFunc::Parameters,    TypeArray<int, long>>));
    EXPECT_TRUE((std::is_same_v<MemFunc::Owner,         ::TestMethod>));
    EXPECT_TRUE((std::is_same_v<MemFunc::Return,        void>));
    EXPECT_TRUE((std::is_same_v<MemFunc::Pointer,       void(TestMethod::*)(int, long) const && noexcept>));
    EXPECT_TRUE((std::is_same_v<MemFunc::Signature,     void(int, long) const && noexcept>));
    
    EXPECT_EQ(MemFunc::funcPtr, &TestMethod::someMethod);
    EXPECT_EQ(MemFunc::parameterCount, 2);
    
    EXPECT_TRUE (MemFunc::isMemberFunction);
    EXPECT_TRUE (MemFunc::isNoexcept);
    EXPECT_TRUE (MemFunc::isConstQualified);
    EXPECT_TRUE (MemFunc::isRvalueQualified);
    EXPECT_FALSE(MemFunc::isVolatileQualified);
    EXPECT_FALSE(MemFunc::isLvalueQualified);
    
    EXPECT_TRUE((std::is_same_v<funcParameterList_t<&::TestMethod::someMethod>, TypeArray<int, long>>));
    EXPECT_TRUE((std::is_same_v<funcOwnerType_t<&::TestMethod::someMethod>,     ::TestMethod>));
    EXPECT_TRUE((std::is_same_v<funcReturnType_t<&::TestMethod::someMethod>,    void>));
    EXPECT_TRUE((std::is_same_v<funcSignature_t<&::TestMethod::someMethod>,     void(int, long) const && noexcept>));
    
    EXPECT_EQ(funcParameterCount_v<&::TestMethod::someMethod>, 2);
    
    EXPECT_TRUE (isMemberFunction_v<&::TestMethod::someMethod>);
    EXPECT_TRUE (isFuncNoexceptSpecified_v<&::TestMethod::someMethod>);
    EXPECT_TRUE (isFuncConstQualified_v<&::TestMethod::someMethod>);
    EXPECT_TRUE (isFuncRvalueQualified_v<&::TestMethod::someMethod>);
    EXPECT_FALSE(isFuncVolatileQualified_v<&::TestMethod::someMethod>);
    EXPECT_FALSE(isFuncLvalueQualified_v<&::TestMethod::someMethod>);
    
    //....................
    EXPECT_TRUE((std::is_same_v<decltype(Overload<void(int, long, double) const && noexcept>::of(&TestMethod::someOtherMethod)), void(TestMethod::*)(int, long, double) const && noexcept>));
    EXPECT_TRUE((std::is_same_v<decltype(Overload<void(int) volatile noexcept>::of(&TestMethod::someOtherMethod)), void(TestMethod::*)(int) volatile noexcept>));
    EXPECT_TRUE((std::is_same_v<decltype(Overload<void() const volatile &>::of(&TestMethod::someOtherMethod)), void(TestMethod::*)() const volatile &>));
    
    EXPECT_FALSE((std::is_same_v<decltype(Overload<void(int, long, double) const && noexcept>::of(&TestMethod::someOtherMethod)), void(TestMethod::*)(int, long, double) const &&>));
    EXPECT_FALSE((std::is_same_v<decltype(Overload<void(int) volatile noexcept>::of(&TestMethod::someOtherMethod)), void(TestMethod::*)(int) noexcept>));
    EXPECT_FALSE((std::is_same_v<decltype(Overload<void() const volatile &>::of(&TestMethod::someOtherMethod)), void(TestMethod::*)() const volatile & noexcept>));
}

//======================================================================================================================
// endregion Unit Tests
//**********************************************************************************************************************
