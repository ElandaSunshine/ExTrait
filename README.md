![Banner-rounded](https://github.com/user-attachments/assets/97a9a030-f3e5-4b97-943c-ff806bfc3b36)

## Introduction
The __ExTrait__ library is a library that focuses on metaprogramming and templates and types in general.

Since templates and general metaprogramming are sometimes awful to look at and hard to track why and how they do things the way they do, this library aims at abstracting many of these questions away, attempting to make them more reasonable and readable to the human eye. Hence a lot of the things that this library provides might look awful in the implementation, but provide a meaningful, concise and accessible interface.

## History
This Project started as part of another library, for a framework called the [JUCE Framework](https://github.com/juce-framework/JUCE), which is a framework for C++ that allows dealing with audio development in a simpler way than with other APIs.

However, these classes and interfaces had little to no dependency on the actual framework and hence it wouldn't have made much sense to leave it as that, as part of another framework. So the decision was made to cut ties with the framework in this instance and make it available to anyone that might benefit from it.

## Motivation
Back when this library was still part of the other library, a few things were needed for some of the other projects, a way to deal with lists of types to do things based on them. Which, majorly, were to tune down the usage of inheritance by simulating an interface with several classes and then, via [std::variant](https://en.cppreference.com/w/cpp/utility/variant), call the object's methods. Interestingly, this was the case more often than not, thus the interface called TypeArray was born.

The reason why it was called that is that there needed to be a way to simulate an [std::array](https://en.cppreference.com/w/cpp/container/array), but for types instead.
For obvious reasons, this presented a challenge, you can't just deal with types the same way as with objects in an array, so the conclusion came after some time, trying to model the std array interface: "How about modelling it in a way that resembles C++'s type traits?"
This is exactly what turned out to be the solution, this class was created and now included plenty of new type traits that would later become an interface that we now know as [extrait::TypeArray](https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray).

Similarly, there were times when there was a need for stringifying types, majorly for logging purposes. There was a similar function in the standard, namely [std::to_string](https://en.cppreference.com/w/cpp/string/basic_string/to_string), however, it does not provide an interface that would allow overriding the method for custom types except if you were to be using ADL.
But it was not desirable to use `using std::to_string` for that, so it was about time to do something similar to what other libraries were already doing, which is some sort of adapter template that users can plug their custom types in with their own template specialisations and this was indeed a great solution. This is how "Stringable" came to be and later ported to this library as [extrait::Stringable](https://elandasunshine.github.io/wiki?page=Extrait/types/Stringable).

After the realisation that all of these things might come in handy outside of the framework that was being used, the consideration arrived: "Might not more people have a use for these things?". Said and done!

## Components
This library is separated into smaller components that may depend on each other. More information about what a component is [here](https://elandasunshine.github.io/wiki?page=Extrait/component).
| Name          | Summary                                                                                         |
|---------------|-------------------------------------------------------------------------------------------------|
| Common        | Provides a common tool set of template and type utilities.                                      |
| Type List     | Provides a set of template utilities to deal with type-only parameter lists of class templates. |
| Reflection    | Provides a set of tools to deal with the inspection of types.                                   |
| Serialisation | Provides a toolset that allows dealing with types and strings.                                  |

## Installation
This section deals with a quick start guide for installation using [CMake](https://cmake.org/), for a more detailed guide go [here](https://elandasunshine.github.io/wiki?page=Extrait/installation).

### Using CMake
```cmake
# Discover the library somewhere in your project hierarchy
add_subdirectory(path/to/extrait)

# Tell the linker to use this library
target_link_libraries(TargetName
    PRIVATE
        ExTrait)
```

### Without CMake
Since this is a header-only library, you can just copy the `includes/extrait` folder into your own header folder, but make sure to copy the `extrait` folder and not only what is in there.

## Usage
If you decided that you wanted to use this library for your project, there is a full documentation page over on our wiki page.

Here are a few useful links:
- [ExTrait Wiki Overview](https://elandasunshine.github.io/wiki?page=Extrait)
- [Guides](https://elandasunshine.github.io/wiki?page=Extrait/guide)
- [Type Arrays](https://elandasunshine.github.io/wiki?page=Extrait/types/TypeArray)
- [Reflection](https://elandasunshine.github.io/wiki?page=Extrait/reflection)

## License
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## Contact
If you need more information or would like to contact us, you can find us on our Discord:  
[![ElandaSunshine Community](https://discordapp.com/api/guilds/781531690383179826/widget.png?style=banner2)](https://discord.com/invite/jzRyAtnJBc)
