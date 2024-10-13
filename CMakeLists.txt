########################################################################################################################
cmake_minimum_required(VERSION 3.28 FATAL_ERROR)



########################################################################################################################
project(ExTrait
    VERSION      1.0.0
    DESCRIPTION  "A useful helper library, providing a handful of amazing type-traits and template magic."
    HOMEPAGE_URL "https://elandasunshine.github.io/ExTrait"
    LANGUAGES    CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(EXTRAIT_BUILD_TESTS "Build all included tests" OFF)
option(EXTRAIT_EXPERIMENTAL_FEATURES "If set to ON, will enable experimental features that are still in testing" OFF)



########################################################################################################################
# Creating library
string(TOLOWER "${PROJECT_NAME}" LC_PROJECT_NAME)
add_library(${PROJECT_NAME} INTERFACE)
add_library(${LC_PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Adding files
target_sources(${PROJECT_NAME}
    INTERFACE
        FILE_SET HEADERS
            BASE_DIRS "include")

# Add definitions
target_compile_definitions(${PROJECT_NAME}
    INTERFACE
        EXTRAIT_EXPERIMENTAL_FEATURES=$<BOOL:${EXTRAIT_EXPERIMENTAL_FEATURES}>)

# Tests setup
if (EXTRAIT_BUILD_TESTS)
    include(CTest)
    add_subdirectory(test)
endif()
