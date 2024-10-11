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
    @file   reflection_impl.h
    @date   31, May 2024
    
    ===============================================================
 */
#pragma once


#include "../common.h"
#include "../type_container.h"
#include <string_view>



//======================================================================================================================
namespace extrait::detail
{
    //==================================================================================================================
    template<class Fn>
    [[nodiscard]]
    constexpr inline std::string_view getSignature(Fn &&fn) noexcept;
    
    //==================================================================================================================
    template<class T, class R, bool WithNoexcept, bool WithLv, bool WithRv, bool WithConst, bool WithVolatile,
             class ...Params>
    struct toFunctionPointer;

#define EXTRAIT_DEF_FTRANSFORMER(S, ...) \
    template<class T, class R, class ...Params> \
    struct toFunctionPointer<T, R, __VA_ARGS__, Params...> { using type = R(T::*)(Params...) S; }

    //                       QUALIFIERS                  | NOEXCEPT | LVALUE | RVALUE | CONST | VOLATILE
#define EXTRAIT_DEF_FTRANSFORMER_BASE(A, L, R) \
    EXTRAIT_DEF_FTRANSFORMER(A,                            false,     L,       R,       false,  false); \
    EXTRAIT_DEF_FTRANSFORMER(const A,                      false,     L,       R,       true,   false); \
    EXTRAIT_DEF_FTRANSFORMER(volatile A,                   false,     L,       R,       false,  true ); \
    EXTRAIT_DEF_FTRANSFORMER(const volatile A,             false,     L,       R,       true,   true ); \
    EXTRAIT_DEF_FTRANSFORMER(A noexcept,                   true,      L,       R,       false,  false); \
    EXTRAIT_DEF_FTRANSFORMER(const A noexcept,             true,      L,       R,       true,   false); \
    EXTRAIT_DEF_FTRANSFORMER(volatile A noexcept,          true,      L,       R,       false,  true ); \
    EXTRAIT_DEF_FTRANSFORMER(const volatile A noexcept,    true,      L,       R,       true,   true )

    EXTRAIT_DEF_FTRANSFORMER_BASE(, false, false);
    EXTRAIT_DEF_FTRANSFORMER_BASE(&, true,  false);
    EXTRAIT_DEF_FTRANSFORMER_BASE(&&, false, true);
    
#undef EXTRAIT_DEF_FTRANSFORMER_BASE
#undef EXTRAIT_DEF_FTRANSFORMER
    
    template<class R, class ...Params>
    struct toFunctionPointer<void, R, false, false, false, false, false, Params...>
    {
        using type = R(*)(Params...);
    };
    
    template<class R, class ...Params>
    struct toFunctionPointer<void, R, true, false, false, false, false, Params...>
    {
        using type = R(*)(Params...) noexcept;
    };
    
    //==================================================================================================================
    template<auto Func, bool IsMember>
    struct InvokeHelper;

    template<auto Func>
    struct InvokeHelper<Func, true>
    {
        /** 
         *  @brief Invokes the current function with the specified parameters.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Function/invoke
         *  @par owner The owner object
         *  @par args The arguments passed to the invocable
         *  @return The return value of the function invoked
         */
        template<class T, class ...Args>
        constexpr static inline auto invoke(T &&owner, Args &&...args)
            noexcept(noexcept((std::forward<T>(owner).*Func)(std::forward<Args>(args)...)))
        {
            return (std::forward<T>(owner).*Func)(std::forward<Args>(args)...);
        }
        
        /** 
         *  @brief Invokes the current function with the specified parameters.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Function/invoke
         *  @par owner The owner pointer
         *  @par args The arguments passed to the invocable
         *  @return The return value of the function invoked
         */
        template<class T, class ...Args>
        constexpr static inline auto invoke(T *owner, Args &&...args)
            noexcept(noexcept((owner->*Func)(std::forward<Args>(args)...)))
        {
            return (owner->*Func)(std::forward<Args>(args)...);
        }
    };

    template<auto Func>
    struct InvokeHelper<Func, false>
    {
        /** 
         *  @brief Invokes the current function with the specified parameters.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Function/invoke
         *  @par owner The owner object
         *  @par args The arguments passed to the invocable
         *  @return The return value of the function invoked
         */
        template<class ...Args>
        constexpr static inline auto invoke(std::nullptr_t, Args &&...args)
            noexcept(noexcept((Func)(std::forward<Args>(args)...)))
        {
            return (Func)(std::forward<Args>(args)...);
        }
    };

    //==================================================================================================================
    template<auto Func,
             class T, class R, class Params, bool IsMember,
             bool QualNoex, bool QualLV, bool QualRV, bool QualCon, bool QualVol>
    struct FuncBase;
    
    template<auto Func,
             class T, class R, class ...Params, bool IsMember,
             bool QualNoex, bool QualLV, bool QualRV, bool QualCon, bool QualVol>
    struct FuncBase<Func, T, R, TypeArray<Params...>, IsMember, QualNoex, QualLV, QualRV, QualCon, QualVol>
        : InvokeHelper<Func, IsMember>
    {
        //==============================================================================================================
        /** 
         *  @brief An extrait::TypeArray with all the parameter types of the function pointer.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Function
         */
        using Parameters = TypeArray<Params...>;
        
        /** 
         *  @brief The owning type if the Invocable function pointer is a non-static member function pointer,
         *  otherwise void.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Function
         */
        using Owner = T;
        
        /** 
         *  @brief The return type of the Invocable function pointer.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Function
         */
        using Return = R;
        
        /** 
         *  @brief The type of the function pointer that was passed to the extrait::Function template.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Function
         */
        using Pointer = typename toFunctionPointer<T, R, QualNoex, QualLV, QualRV, QualCon, QualVol, Params...>::type;
        
        /** 
         *  @brief The function signature type without the pointer or reference.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Function
         */
        using Signature = strip_t<Pointer>;
        
        //--------------------------------------------------------------------------------------------------------------
        /** 
         *  @brief The current extrait::Function's given function pointer object.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Function
         */
        constexpr static auto value = Func;
        
        //--------------------------------------------------------------------------------------------------------------
        /** 
         *  @brief An int that determines the number of parameters in a function.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Function/parameterCount
         */
        constexpr static int parameterCount = sizeof...(Params);
        
        /** 
         *  @brief A bool that determines whether a function is a non-static member function.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Function/isMemberFunction
         */
        constexpr static bool isMemberFunction = IsMember;
        
        //--------------------------------------------------------------------------------------------------------------
        /** 
         *  @brief A bool that determines whether a function is a const qualified member function.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Function/isConstQualified
         */
        constexpr static bool isConstQualified = QualCon;
        
        /** 
         *  @brief A bool that determines whether a function is a volatile qualified member function.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Function/isVolatileQualified
         */
        constexpr static bool isVolatileQualified = QualVol;
        
        /** 
         *  @brief A bool that determines whether a function is an LValue qualified member function.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Function/isLvalueQualified
         */
        constexpr static bool isLvalueQualified = QualLV;
        
        /** 
         *  @brief A bool that determines whether a function is an RValue qualified member function.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Function/isRvalueQualified
         */
        constexpr static bool isRvalueQualified = QualRV;
        
        //--------------------------------------------------------------------------------------------------------------
        /** 
         *  @brief A bool that determines whether a function is noexcept.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Function/isNoexcept
         */
        constexpr static bool isNoexcept = QualNoex;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Gets the function signature of this Function's invocable as compile time string.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Function/toString
         *  @return The function signature as compile time string
         */
        constexpr static inline std::string_view toString() noexcept
        {
            return getSignature<Func>();
        }
    };

    //==================================================================================================================
    template<auto V, class T = decltype(V)>
    struct Function
    {
        static_assert(assertDep_type<T>,
            "Invalid template argument, type must be a valid pointer-to-function or pointer-to-member-function type");
    };

    //------------------------------------------------------------------------------------------------------------------
#define EXMEM_IMPL(A, ...) \
    template<auto F, class T, class R, class ...P> \
    struct Function<F, R(T::*)(P...) A> : FuncBase<F, T, R, TypeArray<P...>, true, __VA_ARGS__ > {}
    
    //------------------------------------------------------------------------------------------------------------------
    //         QUALIFIERS                  | NOEXCEPT | LVALUE | RVALUE | CONST | VOLATILE
#define EXMEM_IMPL_BASE(A, L, R) \
    EXMEM_IMPL(A,                            false,     L,       R,       false,  false); \
    EXMEM_IMPL(const A,                      false,     L,       R,       true,   false); \
    EXMEM_IMPL(volatile A,                   false,     L,       R,       false,  true ); \
    EXMEM_IMPL(const volatile A,             false,     L,       R,       true,   true ); \
    EXMEM_IMPL(A noexcept,                   true,      L,       R,       false,  false); \
    EXMEM_IMPL(const A noexcept,             true,      L,       R,       true,   false); \
    EXMEM_IMPL(volatile A noexcept,          true,      L,       R,       false,  true ); \
    EXMEM_IMPL(const volatile A noexcept,    true,      L,       R,       true,   true )
    
    //------------------------------------------------------------------------------------------------------------------
    EXMEM_IMPL_BASE(,   false, false);
    EXMEM_IMPL_BASE(&,  true,  false);
    EXMEM_IMPL_BASE(&&, false, true );

#undef EXMEM_IMPL_BASE
#undef EXMEM_IMPL
    
    //------------------------------------------------------------------------------------------------------------------
    template<auto Func, class R, class ...P>
    struct Function<Func, R(*)(P...)>
        : FuncBase<Func, void, R, TypeArray<P...>, false, false, false, false, false, false> {};
    
    template<auto Func, class R, class ...P>
    struct Function<Func, R(*)(P...) noexcept>
        : FuncBase<Func, void, R, TypeArray<P...>, false, true, false, false, false, false> {};
    
    //==================================================================================================================
    template<class T, class = void>
    struct isFunctionPointer : std::false_type {};
    
    template<class T>
    struct isFunctionPointer<T, std::void_t<decltype(Function<T{}>{})>> : std::true_type {};
    
    //==================================================================================================================
    enum class SigPos { BEGIN, END };

#ifdef __GNUG__
    template<class _extrait_FuncSig>
    [[nodiscard]]
    constexpr inline std::string_view getSignature_impl(_extrait_FuncSig&&) noexcept
    {
        constexpr std::string_view signature = __PRETTY_FUNCTION__;
        constexpr std::string_view param     = "_extrait_FuncSig";
        std::string_view           result    = signature.substr(signature.find(param) + param.length());
        
        result.remove_prefix(result.find('=') + 1);
        result = result.substr(0, result.find(';'));
        
        {
            const std::size_t start = result.find_first_not_of(' ');
            const std::size_t end   = (result.find_last_not_of(' ') + 1);
            result = result.substr(start, end);
        }
        
        return { result.data(), result.length() };
    }
#elif defined(_MSC_VER)
    template<SigPos = SigPos::BEGIN, class _extrait_FuncSig, SigPos = SigPos::END>
    constexpr inline std::string_view getSignature_impl(_extrait_FuncSig&&) noexcept
    {
        constexpr std::string_view signature = __FUNCSIG__;
        constexpr std::string_view s_name    = "SigPos::BEGIN";
        
        std::string_view result = signature.substr(signature.find(s_name) + s_name.length());
        result.remove_prefix(result.find(',') + 1);
        result = result.substr(0, result.find("SigPos::END"));
        result = result.substr(0, result.rfind(','));
        
        // trim
        {
            const std::size_t start = result.find_first_not_of(' ');
            const std::size_t end   = (result.find_last_not_of(' ') + 1);
            result = result.substr(start, end);
        }
        
        return { result.data(), result.length() };
    }
    
    template<auto F>
    [[nodiscard]]
    constexpr inline std::string_view getSignature_helper() noexcept
    {
        return getSignature_impl<SigPos::BEGIN, F>();
    }
#else
    template<auto F>
    constexpr inline std::string_view getSignature_helper() noexcept
    {
        return "n/a";
    }
#endif

    template<class Fn>
    [[nodiscard]]
    constexpr inline std::string_view getSignature(Fn &&fn) noexcept
    {
        return getSignature_impl(std::forward<Fn>(fn));
    }
    
    //==================================================================================================================
    template<class T, class = void>
    struct Overload
    {
        //==============================================================================================================
        /**
         *  @brief The signature type of the function overload.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Overload
         */
        using Signature = T;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Gets the overloaded function pointer for the specified function signature type.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Overload/of
         *  @param func The function pointer
         *  @return The overloaded function pointer
         */
        template<class U = T>
        [[nodiscard]]
        constexpr static inline auto of(...) noexcept
        {
            static_assert(assertDep_type<U>, "Argument is not a function pointer or an overload that doesn't exist");
        }
        
        /**
         *  @brief Gets the overloaded member function pointer for the specified function signature type.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Overload/of
         *  @param func The function pointer
         *  @return The overloaded function pointer
         */
        template<class Owner>
        [[nodiscard]]
        constexpr static inline auto of(T Owner::* func) noexcept
        {
            return func;
        }
    };
    
    template<class T>
    struct Overload<T, std::void_t<decltype(std::declval<T*>())>>
    {
        //==============================================================================================================
        /**
         *  @brief The signature type of the function overload.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Overload
         */
        using Signature = T;
        
        //--------------------------------------------------------------------------------------------------------------
        /**
         *  @brief Gets the overloaded function pointer for the specified function signature type.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Overload/of
         *  @param func The function pointer
         *  @return The overloaded function pointer
         */
        [[nodiscard]]
        constexpr static inline auto of(T* func) noexcept
        {
            return func;
        }
        
        /**
         *  @brief Gets the overloaded member function pointer for the specified function signature type.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Overload/of
         *  @param func The function pointer
         *  @return The overloaded function pointer
         */
        template<class Owner>
        [[nodiscard]]
        constexpr static inline auto of(T Owner::* func) noexcept
        {
            return func;
        }
    };
}
