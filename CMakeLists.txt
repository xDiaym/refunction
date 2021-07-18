cmake_minimum_required(VERSION 3.0)
project(refunction LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_TESTS "Build tests." OFF)
option(NO_RTTI "Disable RTTI support." OFF)

if(${NO_RTTI})
    target_compile_definitions(refunction INTERFACE RE_FUNCTION_NO_RTTI)
endif()

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE .)


if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR} OR ${BUILD_TESTS})
    include(CTest)
    add_subdirectory(tests)
    enable_testing()
endif ()
