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
    @file   stringable.h
    @date   09, July 2024
    
    ===============================================================
 */

#pragma once

#include "detail/stringable_impl.h"

#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <stack>
#include <string>
#include <thread>
#include <vector>



namespace extrait
{
    /** 
     *  @addtogroup reflection
     *  @{
     */
    
    //==================================================================================================================
    /**
     *  @brief A template that describes a type in a way so as to that it can be represented as a string.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<class T>
    struct Stringable
    {
        [[nodiscard]]
        static std::string toString(const T &object)
        {
            return detail::StringableDefault<T>::toString(object);
        }
    };

    //==================================================================================================================
    /**
     *  @brief Converts a type into a string.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/reflection
     */
    template<class T>
    [[nodiscard]]
    inline std::string toString(const T &object)
    {
        using Stringable = Stringable<T>;
        
        if constexpr (detail::hasStringableToString<Stringable>::value)
        {
            return Stringable::toString(object);
        }
        else
        {
            return detail::StringableDefault<T>::toString(object);
        }
    }
}

namespace extrait
{
    //==================================================================================================================
    template<>
    struct Stringable<bool>
    {
        [[nodiscard]]
        static std::string toString(bool object)
        {
            return (object ? "true" : "false");
        }
    };
    
    template<>
    struct Stringable<std::nullptr_t>
    {
        [[nodiscard]]
        static std::string toString(std::nullptr_t)
        {
            return "null";
        }
    };
    
    template<class T>
    struct Stringable<T*>
    {
        [[nodiscard]]
        static std::string toString(const T *object)
        {
            return (object ? detail::addressToString(object) : "null");
        }
        
        [[nodiscard]]
        static std::string name()
        {
            return getActualTypeName<T>() + '*';
        }
    };
    
    //------------------------------------------------------------------------------------------------------------------
    template<class ...T>
    struct Stringable<std::basic_string<T...>>
    {
        [[nodiscard]]
        static std::string toString(const std::basic_string<T...> &object)
        {
            return '"' + object + '"';
        }
    };
    
    template<class ...T>
    struct Stringable<std::basic_string_view<T...>>
    {
        [[nodiscard]]
        static std::string toString(const std::basic_string_view<T...> &object)
        {
            return extrait::toString(std::string(object));
        }
    };
    
    template<class T, std::size_t N>
    struct Stringable<std::array<T, N>> : detail::SequencedImpl<std::array<T, N>> {};
    
    template<class ...T>
    struct Stringable<std::vector<T...>> : detail::SequencedImpl<std::vector<T...>> {};
    
    template<class ...T>
    struct Stringable<std::deque<T...>> : detail::SequencedImpl<std::deque<T...>> {};
    
    template<class ...T>
    struct Stringable<std::list<T...>> : detail::SequencedImpl<std::list<T...>> {};
    
    template<class ...T>
    struct Stringable<std::forward_list<T...>> : detail::SequencedImpl<std::forward_list<T...>> {};
    
    template<class ...T>
    struct Stringable<std::set<T...>> : detail::SequencedImpl<std::set<T...>> {};
    
    template<class ...T>
    struct Stringable<std::multiset<T...>> : detail::SequencedImpl<std::multiset<T...>> {};
    
    template<class ...T>
    struct Stringable<std::unordered_set<T...>> : detail::SequencedImpl<std::unordered_set<T...>> {};
        
    template<class ...T>
    struct Stringable<std::unordered_multiset<T...>> : detail::SequencedImpl<std::unordered_multiset<T...>> {};
    
    template<class ...T>
    struct Stringable<std::queue<T...>>
    {
        [[nodiscard]]
        static std::string toString(const std::queue<T...> &object)
        {
            return extrait::toString(detail::getAdapterContainer(object));
        }
    };
    
    template<class ...T>
    struct Stringable<std::stack<T...>>
    {
        [[nodiscard]]
        static std::string toString(const std::stack<T...> &object)
        {
            return extrait::toString(detail::getAdapterContainer(object));
        }
    };
    
    template<class ...T>
    struct Stringable<std::priority_queue<T...>>
    {
        [[nodiscard]]
        static std::string toString(const std::priority_queue<T...> &object)
        {
            return extrait::toString(detail::getAdapterContainer(object));
        }
    };
    
    template<class ...T>
    struct Stringable<std::map<T...>> : detail::AssociativeImpl<std::map<T...>> {};
    
    template<class ...T>
    struct Stringable<std::multimap<T...>> : detail::AssociativeImpl<std::multimap<T...>> {};
    
    template<class ...T>
    struct Stringable<std::unordered_map<T...>> : detail::AssociativeImpl<std::unordered_map<T...>> {};
    
    template<class ...T>
    struct Stringable<std::unordered_multimap<T...>> : detail::AssociativeImpl<std::unordered_multimap<T...>> {};
    
    template<>
    struct Stringable<std::thread::id>
    {
        [[nodiscard]]
        static std::string toString(const std::thread::id &object)
        {
            std::stringstream ss;
            ss << object;
            return ss.str();
        }
    };
    
    /** @} */
}
