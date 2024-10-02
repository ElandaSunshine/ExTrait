########################################################################################################################
cmake_minimum_required(VERSION 3.28)



########################################################################################################################
project(ExTrait
    VERSION      1.0.0
    DESCRIPTION  "A useful helper library, providing you with a handful of amazing type-traits and template magic."
    HOMEPAGE_URL "https://elandasunshine.github.io/ExTrait"
    LANGUAGES    CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(EXTRAIT_BUILD_TESTS           "Build all included tests"     OFF)
option(EXTRAIT_EXPERIMENTAL_FEATURES "If set to ON, will enable experimental features that are still in testing" OFF)



########################################################################################################################
add_library(${PROJECT_NAME} INTERFACE)

if (EXTRAIT_DUMP_CLANG_AST AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${PROJECT_NAME}
        PUBLIC
            "-ast-dump=json")
endif()

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

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_custom_target(${PROJECT_NAME}_ast)

    file(GLOB headers
        LIST_DIRECTORIES FALSE
        "${CMAKE_CURRENT_LIST_DIR}/include/extrait/*.h")

    foreach(header IN LISTS headers)
        get_filename_component(file ${header} NAME)
        add_custom_command(TARGET ${PROJECT_NAME}_ast
            COMMAND ${CMAKE_CXX_COMPILER} -Xclang -ast-dump=json -fsyntax-only ${header})
    endforeach()
endif()
