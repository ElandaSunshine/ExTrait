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
    /**
     *  @brief A helper class that disassembles any invocable in its single parts like parameters, name ect. and
     *         publishes this information in a concise interface.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Function
     *  @tparam Fn The lambda or function pointer
     */
    template<auto Fn>
    struct Function : detail::Function<Fn> {};

    //==================================================================================================================
    /**
     *  @brief A helper class for extrait::Function, that allows selecting a specific overload of a function.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Overload
     *  @tparam T The function signature type
     */
    template<class T>
    struct Overload : detail::Overload<T> {};
    
    //==================================================================================================================
    /**
     *  @brief A helper alias for declaring the type of a function pointer.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/reflection/type_helpers%23tabber-FunctionPointer_t
     *  @tparam T The function signature type
     */
    template<class T>
    using FunctionPointer_t = typename detail::Function<nullptr, std::remove_pointer_t<T>*>::Pointer;
    
    /**
     *  @brief A helper alias for declaring the type of a member function pointer.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/reflection/type_helpers%23tabber-MemberFunctionPointer_t
     *  @tparam T The function signature type
     *  @tparam U The owner type of the member function
     */
    template<class T, class U>
    using MemberFunctionPointer_t = typename detail::Function<nullptr, std::remove_pointer_t<U> T::*>::Pointer;
    
    /**
     *  @brief A helper alias for declaring the type of a member object pointer.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/reflection/type_helpers%23tabber-MemberObjectPointer_t
     *  @tparam T The type of the member object
     *  @tparam U The owner type of the member object
     */
    template<class T, class U>
    using MemberObjectPointer_t = U T::*;
    
    //==================================================================================================================
    /**
     *  @brief Determines whether a function is a member function.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/isMemberFunction
     *  @tparam Fn The function pointer
     */
    template<auto Fn>
    struct isMemberFunction : std::bool_constant<Function<Fn>::isMemberFunction> {};
    
    /**
     *  @brief Value helper for extrait::isMemberFunction.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/isMemberFunction
     *  @tparam Fn The function pointer
     */
    template<auto Fn>
    constexpr inline bool isMemberFunction_v = isMemberFunction<Fn>::value;
    
    /**
     *  @brief Determines whether a function is a const qualified member function.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/isFuncConstQualified
     *  @tparam Fn The function pointer
     */
    template<auto Fn>
    struct isFuncConstQualified : std::bool_constant<Function<Fn>::isConstQualified> {};
    
    /**
     *  @brief Value helper for extrait::isFuncConstQualified.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/isFuncConstQualified
     *  @tparam Fn The function pointer
     */
    template<auto Fn>
    constexpr inline bool isFuncConstQualified_v = isFuncConstQualified<Fn>::value;
    
    /**
     *  @brief Determines whether a function is a volatile qualified member function.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/isFuncVolatileQualified
     *  @tparam Fn The function pointer
     */
    template<auto Fn>
    struct isFuncVolatileQualified : std::bool_constant<Function<Fn>::isVolatileQualified> {};
    
    /**
     *  @brief Value helper for extrait::isFuncVolatileQualified.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/isFuncVolatileQualified
     *  @tparam Fn The function pointer
     */
    template<auto Fn>
    constexpr inline bool isFuncVolatileQualified_v = isFuncVolatileQualified<Fn>::value;
    
    /**
     *  @brief Determines whether a function is a LValue qualified member function.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/isFuncLvalueQualified
     *  @tparam Fn The function pointer
     */
    template<auto Fn>
    struct isFuncLvalueQualified : std::bool_constant<Function<Fn>::isLvalueQualified> {};
    
    /**
     *  @brief Value helper for extrait::isFuncLvalueQualified.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/isFuncLvalueQualified
     *  @tparam Fn The function pointer
     */
    template<auto Fn>
    constexpr inline bool isFuncLvalueQualified_v = isFuncLvalueQualified<Fn>::value;
    
    /**
     *  @brief Determines whether a function is a RValue qualified member function.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/isFuncRvalueQualified
     *  @tparam Fn The function pointer
     */
    template<auto Fn>
    struct isFuncRvalueQualified : std::bool_constant<Function<Fn>::isRvalueQualified> {};
    
    /**
     *  @brief Value helper for extrait::isFuncRvalueQualified.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/isFuncRvalueQualified
     *  @tparam Fn The function pointer
     */
    template<auto Fn>
    constexpr inline bool isFuncRvalueQualified_v = isFuncRvalueQualified<Fn>::value;
    
    /**
     *  @brief Determines whether a function is noexcept.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/isFuncNoexcept
     *  @tparam Fn The function pointer
     */
    template<auto Fn>
    struct isFuncNoexcept : std::bool_constant<Function<Fn>::isNoexcept> {};
    
    /**
     *  @brief Value helper for extrait::isFuncNoexcept.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/isFuncNoexcept
     *  @tparam Fn The function pointer
     */
    template<auto Fn>
    constexpr inline bool isFuncNoexcept_v = isFuncNoexcept<Fn>::value;
    
    /**
     *  @brief Gets the number of parameter a function pointer has.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/funcParameterCount
     *  @tparam Fn The lambda or function pointer
     */
    template<auto Fn>
    struct funcParameterCount : std::integral_constant<std::size_t, Function<Fn>::parameterCount> {};
    
    /**
     *  @brief Value helper for extrait::funcParameterCount.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/funcParameterCount
     *  @tparam Fn The lambda or function pointer
     */
    template<auto Fn>
    constexpr inline std::size_t funcParameterCount_v = funcParameterCount<Fn>::value;
    
    /**
     *  @brief Gets the parameters of a function pointer as an extrait::TypeArray.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/funcParameterList
     *  @tparam Fn The lambda or function pointer
     */
    template<auto Fn>
    struct funcParameterList
    {
        using type = typename Function<Fn>::Parameters;
    };
    
    /**
     *  @brief Type helper for extrait::funcParameterList.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/funcParameterList
     *  @tparam Fn The lambda or function pointer
     */
    template<auto Fn>
    using funcParameterList_t = typename funcParameterList<Fn>::type;
    
    /**
     *  @brief Gets the return type of a function pointer.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/funcReturnType
     *  @tparam Fn The lambda or function pointer
     */
    template<auto Fn>
    struct funcReturnType
    {
        using type = typename Function<Fn>::Return;
    };
    
    /**
     *  @brief Type helper for extrait::funcReturnType.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/funcReturnType
     *  @tparam Fn The lambda or function pointer
     */
    template<auto Fn>
    using funcReturnType_t = typename funcReturnType<Fn>::type;
    
    /**
     *  @brief Gets the class the function pointer is a member of, if it is a member function.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/funcOwnerType
     *  @tparam Fn The function pointer
     */
    template<auto Fn>
    struct funcOwnerType
    {
        using type = typename Function<Fn>::Owner;
    };
    
    /**
     *  @brief Type helper for extrait::funcOwnerType.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/funcOwnerType
     *  @tparam Fn The function pointer
     */
    template<auto Fn>
    using funcOwnerType_t = typename funcOwnerType<Fn>::type;
    
    /**
     *  @brief Gets the signature type of a function pointer.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/funcSignature
     *  @tparam Fn The function pointer
     */
    template<auto Fn>
    struct funcSignature
    {
        using type = typename Function<Fn>::Signature;
    };
    
    /**
     *  @brief Type helper for extrait::funcSignature.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/funcSignature
     *  @tparam Fn The function pointer
     */
    template<auto Fn>
    using funcSignature_t = typename funcSignature<Fn>::type;
    
    //==================================================================================================================
    /**
     *  @brief Gets the function signature of a function pointer as compile time string.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/funcs/funcToString
     *  @param funcPtr The function pointer
     *  @return The signature of the given function pointer or lambda as compile time string
     */
    template<class Fn>
    constexpr inline std::string_view funcToString(Fn &&funcPtr)
    {
        return detail::getSignature(std::forward<Fn>(funcPtr));
    }
}
//======================================================================================================================
// endregion Function
//**********************************************************************************************************************
