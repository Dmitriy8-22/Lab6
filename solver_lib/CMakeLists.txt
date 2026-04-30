cmake_minimum_required(VERSION 3.14)
project(solver)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(solver STATIC solver.cpp)
target_include_directories(solver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Windows: math functions are in standard library
if(NOT WIN32)
    target_link_libraries(solver PRIVATE m)
endif()

if(ENABLE_COVERAGE)
    target_compile_options(solver PRIVATE --coverage -g -O0)
    target_link_options(solver PRIVATE --coverage)
endif()

install(TARGETS solver
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
