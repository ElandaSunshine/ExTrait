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

#include <array>
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
    //==================================================================================================================
    /**
     *  @brief A template that describes a type in a way so as to that it can be represented as a string.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     *  @tparam T The type to convert to string
     */
    template<class T>
    struct Stringable
    {   
        /**
         *  @brief Gets a compile time string of the given object.
         *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
         *  @param object The object to convert to string
         *  @return The contents of the given object as string
         */
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
     *  @tparam T The deduced type of the function parameter
     *  @param object The object to convert to string
     *  @return The contents of the given object as string
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
    /**
     *  @brief extrait::Stringable specialisation for converting booleans to a string.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<>
    struct Stringable<bool>
    {
        [[nodiscard]]
        static std::string toString(bool object)
        {
            return (object ? "true" : "false");
        }
    };
    
    /**
     *  @brief extrait::Stringable specialisation for converting std::nullptr to a string.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<>
    struct Stringable<std::nullptr_t>
    {
        [[nodiscard]]
        static std::string toString(std::nullptr_t)
        {
            return "null";
        }
    };
    
    /**
     *  @brief extrait::Stringable specialisation for converting pointers to a string.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<class T>
    struct Stringable<T*>
    {
        [[nodiscard]]
        static std::string toString(const T *object)
        {
            return (object ? detail::addressToString(object) : "null");
        }
    };
    
    //------------------------------------------------------------------------------------------------------------------
    /**
     *  @brief extrait::Stringable specialisation for converting any std::basic_string to strings.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<>
    struct Stringable<std::string>
    {
        [[nodiscard]]
        static std::string toString(const std::string &object)
        {
            return '"' + object + '"';
        }
    };
    
    /**
     *  @brief extrait::Stringable specialisation for converting any std::basic_string_view to strings.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<>
    struct Stringable<std::string_view>
    {
        [[nodiscard]]
        static std::string toString(const std::string_view &object)
        {
            return extrait::toString(std::string(object));
        }
    };
    
    /**
     *  @brief extrait::Stringable specialisation for converting std::array to strings.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<class T, std::size_t N>
    struct Stringable<std::array<T, N>> : detail::SequencedImpl<std::array<T, N>> {};
    
    /**
     *  @brief extrait::Stringable specialisation for converting std::vector to strings.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<class ...T>
    struct Stringable<std::vector<T...>> : detail::SequencedImpl<std::vector<T...>> {};
    
    /**
     *  @brief extrait::Stringable specialisation for converting std::deque to strings.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<class ...T>
    struct Stringable<std::deque<T...>> : detail::SequencedImpl<std::deque<T...>> {};
    
    /**
     *  @brief extrait::Stringable specialisation for converting std::list to strings.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<class ...T>
    struct Stringable<std::list<T...>> : detail::SequencedImpl<std::list<T...>> {};
    
    /**
     *  @brief extrait::Stringable specialisation for converting std::forward_list to strings.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<class ...T>
    struct Stringable<std::forward_list<T...>> : detail::SequencedImpl<std::forward_list<T...>> {};
    
    /**
     *  @brief extrait::Stringable specialisation for converting std::set to strings.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<class ...T>
    struct Stringable<std::set<T...>> : detail::SequencedImpl<std::set<T...>> {};
    
    /**
     *  @brief extrait::Stringable specialisation for converting std::multiset to strings.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<class ...T>
    struct Stringable<std::multiset<T...>> : detail::SequencedImpl<std::multiset<T...>> {};
    
    /**
     *  @brief extrait::Stringable specialisation for converting std::unordered_set to strings.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<class ...T>
    struct Stringable<std::unordered_set<T...>> : detail::SequencedImpl<std::unordered_set<T...>> {};
    
    /**
     *  @brief extrait::Stringable specialisation for converting std::unordered_multiset to strings.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<class ...T>
    struct Stringable<std::unordered_multiset<T...>> : detail::SequencedImpl<std::unordered_multiset<T...>> {};
    
    /**
     *  @brief extrait::Stringable specialisation for converting std::queue to strings.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<class ...T>
    struct Stringable<std::queue<T...>>
    {
        [[nodiscard]]
        static std::string toString(const std::queue<T...> &object)
        {
            return extrait::toString(detail::getAdapterContainer(object));
        }
    };
    
    /**
     *  @brief extrait::Stringable specialisation for converting std::stack to strings.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<class ...T>
    struct Stringable<std::stack<T...>>
    {
        [[nodiscard]]
        static std::string toString(const std::stack<T...> &object)
        {
            return extrait::toString(detail::getAdapterContainer(object));
        }
    };
    
    /**
     *  @brief extrait::Stringable specialisation for converting std::priority_queue to strings.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<class ...T>
    struct Stringable<std::priority_queue<T...>>
    {
        [[nodiscard]]
        static std::string toString(const std::priority_queue<T...> &object)
        {
            return extrait::toString(detail::getAdapterContainer(object));
        }
    };
    
    /**
     *  @brief extrait::Stringable specialisation for converting std::map to strings.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<class ...T>
    struct Stringable<std::map<T...>> : detail::AssociativeImpl<std::map<T...>> {};
    
    /**
     *  @brief extrait::Stringable specialisation for converting std::multimap to strings.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<class ...T>
    struct Stringable<std::multimap<T...>> : detail::AssociativeImpl<std::multimap<T...>> {};
    
    /**
     *  @brief extrait::Stringable specialisation for converting std::unordered_map to strings.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<class ...T>
    struct Stringable<std::unordered_map<T...>> : detail::AssociativeImpl<std::unordered_map<T...>> {};
    
    /**
     *  @brief extrait::Stringable specialisation for converting std::unordered_multimap to strings.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
    template<class ...T>
    struct Stringable<std::unordered_multimap<T...>> : detail::AssociativeImpl<std::unordered_multimap<T...>> {};
    
    /**
     *  @brief extrait::Stringable specialisation for converting std::thread::id to strings.
     *  @details https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable
     */
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
}
