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
    @file   stringable_impl.h
    @date   09, July 2024
    
    ===============================================================
 */

#pragma once

#include "../common.h"
#include <sstream>



namespace extrait
{
    //==================================================================================================================
    template<class T>
    struct Stringable;
    
    //==================================================================================================================
    template<class T>
    [[nodiscard]]
    inline std::string toString(const T &object);
}

namespace extrait::detail
{
    //==================================================================================================================
    template<class T>
    [[nodiscard]]
    inline std::string addressToString(const T *ptr)
    {
        std::stringstream ss;
        ss << std::hex << ptr;
        return ss.str();
    }
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, class = void>
    struct toStringStdExists : std::false_type {};
    
    template<class T>
    struct toStringStdExists<T, std::void_t<decltype(std::to_string(std::declval<T>()))>> : std::true_type {};
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T, class = void>
    struct hasStringableToString : std::false_type {};
    
    template<class T>
    struct hasStringableToString<Stringable<T>, std::void_t<decltype(Stringable<T>::toString(std::declval<T>()))>>
        : std::true_type {};
    
    template<class T, class = void>
    struct hasToString : std::false_type {};
    
    template<class T>
    struct hasToString<T, std::void_t<decltype(std::string(std::declval<T>().toString()))>> : std::true_type {};
    
    template<class T, class = void>
    struct hasTo_String : std::false_type {};
    
    template<class T>
    struct hasTo_String<T, std::void_t<decltype(std::string(std::declval<T>().to_string()))>> : std::true_type {};
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T>
    struct StringableDefault
    {
        [[nodiscard]]
        inline static std::string toString(const T &object)
        {
            if constexpr (detail::toStringStdExists<T>::value)
            {
                return std::to_string(object);
            }
            else if constexpr (hasToString<T>::value)
            {
                return object.toString();
            }
            else if constexpr (hasTo_String<T>::value)
            {
                return object.to_string();
            }
            else
            {
                return std::string(extrait::getActualTypeName(object)) + "@" + addressToString(std::addressof(object));
            }
        }
    };
    
    //------------------------------------------------------------------------------------------------------------------
    template<class T>
    struct SequencedImpl
    {
        [[nodiscard]]
        inline static std::string toString(const T &object)
        {
            std::stringstream ss;
            
            for (auto it = object.begin(); it != object.end(); ++it)
            {
                ss << extrait::toString(*it);
                
                if (std::next(it) != object.end())
                {
                    ss << ", ";
                }
            }
            
            return '[' + ss.str() + ']';
        }
    };
    
    template<class T>
    struct AssociativeImpl
    {
        [[nodiscard]]
        inline static std::string toString(const T &object)
        {
            std::stringstream ss;
            
            for (auto it = object.begin(); it != object.end(); ++it)
            {
                std::string key = extrait::toString(it->first);
                
                if (key.empty() || key[0] != '"')
                {
                    std::string new_key = ("\"" + key + "\"");
                    std::swap(key, new_key);
                }
                
                ss << key << ':' << extrait::toString(it->second);
                
                if (std::next(it) != object.end())
                {
                    ss << ", ";
                }
            }
            
            return '{' + ss.str() + '}';
        }
    };
    
    template<class U>
    inline decltype(auto) getAdapterContainer(U &adapter)
    {
        struct Extract : U
        {
            static decltype(auto) get(U &a)
            {
                return a.*&Extract::c;
            }
        };
        
        return Extract::get(adapter);
    }
}
