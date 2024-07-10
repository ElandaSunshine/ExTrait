########################################################################################################################
include(CTest)
include(FetchContent)

FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0)
FetchContent_MakeAvailable(googletest)



########################################################################################################################
if (WIN32 AND CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/bigobj)
endif()



########################################################################################################################
function(extrait_add_test target)
    cmake_parse_arguments(PARG "" "" "DEFINES" ${ARGN})
    
    string(TOUPPER ${target} TEST_NAME)
    set(TEST_TARGET Test${TEST_NAME})
    
    add_executable(${TEST_TARGET} ${ExTrait_SOURCE_DIR}/test/${target}.cpp)
    
    if (MSVC AND MSVC_VERSION GREATER_EQUAL 1914)
        target_compile_options(${TEST_TARGET}
            PRIVATE
                "/Zc:__cplusplus")
    endif()
    
    if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        target_compile_definitions(${TEST_TARGET}
            PRIVATE
                _CONSOLE=1)
    endif()
    
    if (DEFINED PARG_DEFINES AND NOT "DEFINES" IN_LIST PARG_KEYWORDS_MISSING_VALUES)
        target_compile_definitions(${TEST_TARGET}
            PRIVATE
                ${PARG_DEFINES})
    endif()
    
    target_link_libraries(${TEST_TARGET}
        PRIVATE
            # GTEST
            gtest
            gtest_main
            
            ExTrait)

    add_test(
        NAME    ${TEST_TARGET}
        COMMAND ${TEST_TARGET})
endfunction()



########################################################################################################################
extrait_add_test(TypeList)
extrait_add_test(Common)
extrait_add_test(Reflection)
extrait_add_test(Stringable)
