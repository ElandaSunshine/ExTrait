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
    @file   common.h
    @date   19, May 2024
    
    ===============================================================
 */

#pragma once

#include "define.h"
#include "detail/common_impl.h"

#include <cassert>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>

#ifdef __GNUG__
    #include <cxxabi.h>
#endif



namespace extrait
{
    /** 
     *  @defgroup common "Common"
     *  @{
     */
    
    //==================================================================================================================
    /**
     *  @brief Strips a given type from all its modifications like array extents, pointers, references and so on.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/strip
     */
    template<class T>
    struct strip : detail::strip<T> {};
    
    template<class T>
    using strip_t = typename strip<T>::type;
    
    //==================================================================================================================
    /**
     *  @brief Allows making a static_assert depend on a given list of types.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/vars/assertDep%23tabber-type
     */
    template<class ...T>
    constexpr inline bool assertDep_type = false;
    
    /**
     *  @brief Allows making a static_assert depend on a given list of constexpr values.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/vars/assertDep%23tabber-value
     */
    template<auto ...V>
    constexpr inline bool assertDep_value = false;
    
    //==================================================================================================================
    /**
     *  @brief A hover docs utility type that shows the given types upon hovering. (if the IDE supports it)
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/common
     */
    template<class...>
    struct TypeView;
    
    /**
     *  @brief A hover docs utility type that shows the given constant expressions upon hovering. (if the IDE supports it)
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/common
     */
    template<auto...>
    struct ValueView;
    
    //==================================================================================================================
    /**
     *  @brief Selects a type based on the given case branches that hold a condition and a type for that condition.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/select
     */
    template<class ...Branches>
    struct select : detail::select<Branches...> {};
    
    template<class ...Branches>
    using select_t = typename select<Branches...>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Creates a new instantiation of the given <a href="https://elandasunshine.github.io/wiki?page=Extrait/nomenclature%23def-tlist-conf">type list conformant</a>
     *         class template with all types that each given branch case's condition evaluated to true.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/assemble
     */
    template<template<class...> class T, class ...Branches>
    struct assemble : detail::assemble<T, Branches...> {};
    
    template<template<class...> class T, class ...Branches>
    using assemble_t = typename assemble<T, Branches...>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief Specifies a branch in a given branching template, and associates a type with a given condition.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/branch
     */
    template<class T, bool Condition>
    struct branch {};
    
    //==================================================================================================================
    /**
     *  @brief Gets a constexpr name of the given type passed to this function.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/funcs/getActualTypeName
     */
    template<class T>
    [[nodiscard]]
    constexpr inline std::string_view getActualTypeName() noexcept
    {
        return detail::getActualTypeName<T>();
    }
    
    /**
     *  @brief Gets a constexpr name of the given type passed to this function.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/funcs/getActualTypeName
     */
    template<class T>
    [[nodiscard]]
    constexpr inline std::string_view getActualTypeName([[maybe_unused]] T &&object) noexcept
    {
        return getActualTypeName<T>();
    }
    
    //==================================================================================================================
    /**
     *  @brief A helper cast that checks whether a base can be casted to a derived object in debug configurations but
     *         removes this check during release configurations.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/funcs/stynamic_cast
     */
    template<class Derived, class Base>
    [[nodiscard]]
    constexpr inline Derived stynamic_cast(Base *const base) noexcept
    {
        // Cannot convert a nullptr
        assert(base != nullptr);
        
        // Tried converting to a derived class that base is not an instance of
        assert(dynamic_cast<Derived>(base) != nullptr);
        return static_cast<Derived>(base);
    }
    
    /**
     *  @brief A helper cast that checks whether a base can be casted to a derived object in debug configurations but
     *         removes this check during release configurations.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/funcs/stynamic_cast
     */
    template<class Derived, class Base>
    [[nodiscard]]
    constexpr inline Derived stynamic_cast(Base &base) noexcept
    {
        // Tried converting to a derived class that base is not an instance of
        assert(dynamic_cast<Derived>(base) != nullptr);
        return static_cast<Derived>(base);
    }
    
    /** @} */
}
