# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Development/Coding/cpp/ExTrait/cmake-build-debug-visual-studio/_deps/googletest-src"
  "D:/Development/Coding/cpp/ExTrait/cmake-build-debug-visual-studio/_deps/googletest-build"
  "D:/Development/Coding/cpp/ExTrait/cmake-build-debug-visual-studio/_deps/googletest-subbuild/googletest-populate-prefix"
  "D:/Development/Coding/cpp/ExTrait/cmake-build-debug-visual-studio/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "D:/Development/Coding/cpp/ExTrait/cmake-build-debug-visual-studio/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "D:/Development/Coding/cpp/ExTrait/cmake-build-debug-visual-studio/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "D:/Development/Coding/cpp/ExTrait/cmake-build-debug-visual-studio/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Development/Coding/cpp/ExTrait/cmake-build-debug-visual-studio/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Development/Coding/cpp/ExTrait/cmake-build-debug-visual-studio/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
