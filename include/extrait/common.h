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
    //==================================================================================================================
    template<class T>
    struct strip : detail::strip<T> {};
    
    template<class T>
    using strip_t = typename strip<T>::type;
    
    //==================================================================================================================
    template<class ...T>
    constexpr inline bool assertDep_type = false;
    
    template<auto ...V>
    constexpr inline bool assertDep_value = false;
    
    //==================================================================================================================
    template<class...>
    struct TypeView;
    
    template<auto...>
    struct ValueView;
    
    //==================================================================================================================
    template<class ...Branches>
    struct select : detail::select<Branches...> {};
    
    template<class ...Branches>
    using select_t = typename select<Branches...>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    template<template<class...> class T, class ...Branches>
    struct assemble : detail::assemble<T, Branches...> {};
    
    template<template<class...> class T, class ...Branches>
    using assemble_t = typename assemble<T, Branches...>::type;
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, bool Condition>
    struct branch {};
    
    //==================================================================================================================
    template<class T>
    [[nodiscard]]
    constexpr inline std::string_view getActualTypeName() noexcept
    {
        return detail::getActualTypeName<T>();
    }
    
    template<class T>
    [[nodiscard]]
    constexpr inline std::string_view getActualTypeName([[maybe_unused]] T &&object) noexcept
    {
        return getActualTypeName<T>();
    }
    
    //==================================================================================================================
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
    
    template<class Derived, class Base>
    [[nodiscard]]
    constexpr inline Derived stynamic_cast(Base &base) noexcept
    {
        // Tried converting to a derived class that base is not an instance of
        assert(dynamic_cast<Derived>(base) != nullptr);
        return static_cast<Derived>(base);
    }
}
