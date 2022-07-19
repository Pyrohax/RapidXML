cmake_minimum_required(VERSION 3.8.0)

# Custom macro function to add project filters
macro(ADD_PROJECT_FILTERS path input_list prepend)
  foreach(_source IN ITEMS ${${input_list}})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${path}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${prepend}/${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
  endforeach()
endmacro()

add_definitions(-DUNICODE)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/MP>")
set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY CMAKE_CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Binaries)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Libraries)

set(SUBMODULES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Submodules")

project(RapidXML CXX)

set(SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/")

file(GLOB_RECURSE SRC SRC_DIR
    "*.cpp"
    "*.h"
    "*.hpp")

add_library(RapidXMLLib INTERFACE ${SRC})
target_compile_features(RapidXMLLib PRIVATE cxx_std_17)
target_include_directories(RapidXMLLib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

ADD_PROJECT_FILTERS(${SRC_DIR} SRC Source)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "RapidXMLLib")