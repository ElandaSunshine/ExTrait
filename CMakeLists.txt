########################################################################################################################
cmake_minimum_required(VERSION 3.28)



########################################################################################################################
project(ExTrait
    VERSION      1.0.0
    DESCRIPTION  "A useful helper library, providing you with a handful of amazing type-traits and template magic."
    HOMEPAGE_URL "https://elandasunshine.github.io/ExTrait"
    LANGUAGES    CXX)

set(CMAKE_CXX_STANDARD 17)


option(EXTRAIT_BUILD_TESTS           "Build all included tests"     OFF)
option(EXTRAIT_BUILD_EXAMPLES        "Build all included tests"     OFF)
option(EXTRAIT_EXPERIMENTAL_FEATURES "If set to ON, will enable experimental features that are still in testing" OFF)

set(input hello hello2 hello3 hello4)

list(TRANSFORM input
    REPLACE "(.+)" "\"\\1\""
    OUTPUT_VARIABLE input)
list(JOIN input "," input_string)

message(FATAL_ERROR "${input_string}")

return()


########################################################################################################################
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/include)

target_compile_definitions(${PROJECT_NAME}
    INTERFACE
        EXTRAIT_EXPERIMENTAL_FEATURES=$<BOOL:${EXTRAIT_EXPERIMENTAL_FEATURES}>)

if (EXTRAIT_BUILD_TESTS)
    include(CTest)
    add_subdirectory(test)
endif()
