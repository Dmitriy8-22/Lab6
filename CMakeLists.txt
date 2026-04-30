cmake_minimum_required(VERSION 3.14)

project(Lab5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -g -O0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

add_subdirectory(banking)
add_subdirectory(tests)
add_subdirectory(solver_lib)
add_subdirectory(solver_application)

include(CPackConfig.cmake)
