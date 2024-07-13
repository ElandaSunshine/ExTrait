########################################################################################################################
function(extrait_add_example target)
    cmake_parse_arguments(PARG "" "" "DEFINES" ${ARGN})
    
    get_filename_component(out_parent_name      "${target}"          DIRECTORY)
    get_filename_component(out_file_name        "${target}"          NAME_WE)
    get_filename_component(out_parent_file_name "${out_parent_name}" NAME)
    
    string(TOUPPER "${out_parent_file_name}_${out_file_name}" EXAMPLE_NAME)
    set(EXAMPLE_TARGET Example${EXAMPLE_NAME})
    
    add_executable(${EXAMPLE_TARGET} ${target})
    
    if (MSVC AND MSVC_VERSION GREATER_EQUAL 1914)
        target_compile_options(${EXAMPLE_TARGET}
            PRIVATE
                "/Zc:__cplusplus")
    endif()
    
    if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        target_compile_definitions(${EXAMPLE_TARGET}
            PRIVATE
                _CONSOLE=1)
    endif()
    
    if (DEFINED PARG_DEFINES AND NOT "DEFINES" IN_LIST PARG_KEYWORDS_MISSING_VALUES)
        target_compile_definitions(${EXAMPLE_TARGET}
            PRIVATE
                ${PARG_DEFINES})
    endif()
    
    target_link_libraries(${EXAMPLE_TARGET}
        PRIVATE
            ExTrait)
endfunction()



########################################################################################################################
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${ExTrait_SOURCE_DIR}/examples/**/*.cpp")

foreach (source IN LISTS sources)
    extrait_add_example("${source}")
endforeach()
