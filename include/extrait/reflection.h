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
    @file   functional.h
    @date   12, May 2024
    
    ===============================================================
 */

#pragma once

#include "detail/reflection_impl.h"



//**********************************************************************************************************************
// region Function
//======================================================================================================================
namespace extrait
{
    //==================================================================================================================
    template<auto Fn>
    struct Function : detail::Function<Fn> {};
    
    //==================================================================================================================
    template<class T>
    struct Overload : detail::Overload<T> {};
    
    //==================================================================================================================
    template<class T>
    using FunctionPointer_t = typename detail::Function<nullptr, std::remove_pointer_t<T>*>::Pointer;
    
    template<class T, class U>
    using MemberFunctionPointer_t = typename detail::Function<nullptr, std::remove_pointer_t<U> T::*>::Pointer;
    
    template<class T, class U>
    using MemberObjectPointer_t = U T::*;
    
    //==================================================================================================================
    template<auto Fn>
    struct isMemberFunction : std::bool_constant<Function<Fn>::isMemberFunction> {};
    
    template<auto Fn>
    constexpr inline bool isMemberFunction_v = isMemberFunction<Fn>::value;
    
    template<auto Fn>
    struct isFuncConstQualified : std::bool_constant<Function<Fn>::isConstQualified> {};
    
    template<auto Fn>
    constexpr inline bool isFuncConstQualified_v = isFuncConstQualified<Fn>::value;
    
    template<auto Fn>
    struct isFuncVolatileQualified : std::bool_constant<Function<Fn>::isVolatileQualified> {};
    
    template<auto Fn>
    constexpr inline bool isFuncVolatileQualified_v = isFuncVolatileQualified<Fn>::value;
    
    template<auto Fn>
    struct isFuncLvalueQualified : std::bool_constant<Function<Fn>::isLvalueQualified> {};
    
    template<auto Fn>
    constexpr inline bool isFuncLvalueQualified_v = isFuncLvalueQualified<Fn>::value;
    
    template<auto Fn>
    struct isFuncRvalueQualified : std::bool_constant<Function<Fn>::isRvalueQualified> {};
    
    template<auto Fn>
    constexpr inline bool isFuncRvalueQualified_v = isFuncRvalueQualified<Fn>::value;
    
    template<auto Fn>
    struct isFuncNoexceptSpecified : std::bool_constant<Function<Fn>::isNoexcept> {};
    
    template<auto Fn>
    constexpr inline bool isFuncNoexceptSpecified_v = isFuncNoexceptSpecified<Fn>::value;
    
    template<auto Fn>
    struct funcParameterCount : std::integral_constant<std::size_t, Function<Fn>::parameterCount> {};
    
    template<auto Fn>
    constexpr inline std::size_t funcParameterCount_v = funcParameterCount<Fn>::value;
    
    template<auto Fn>
    struct funcParameterList
    {
        using type = typename Function<Fn>::Parameters;
    };
    
    template<auto Fn>
    using funcParameterList_t = typename funcParameterList<Fn>::type;
    
    template<auto Fn>
    struct funcReturnType
    {
        using type = typename Function<Fn>::Return;
    };
    
    template<auto Fn>
    using funcReturnType_t = typename funcReturnType<Fn>::type;
    
    template<auto Fn>
    struct funcOwnerType
    {
        using type = typename Function<Fn>::Owner;
    };
    
    template<auto Fn>
    using funcOwnerType_t = typename funcOwnerType<Fn>::type;
    
    template<auto Fn>
    struct funcSignature
    {
        using type = typename Function<Fn>::Signature;
    };
    
    template<auto Fn>
    using funcSignature_t = typename funcSignature<Fn>::type;
    
    //==================================================================================================================
    template<class Fn>
    constexpr inline std::string_view funcToString(Fn &&funcPtr)
    {
        return detail::getSignature(std::forward<Fn>(funcPtr));
    }
}
//======================================================================================================================
// endregion Function
//**********************************************************************************************************************
