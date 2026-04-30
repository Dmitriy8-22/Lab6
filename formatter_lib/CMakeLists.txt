cmake_minimum_required(VERSION 3.14)
project(formatter)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(formatter STATIC formatter.cpp)
target_include_directories(formatter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(ENABLE_COVERAGE)
    target_compile_options(formatter PRIVATE --coverage -g -O0)
    target_link_options(formatter PRIVATE --coverage)
endif()

install(TARGETS formatter
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
