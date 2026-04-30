cmake_minimum_required(VERSION 3.14)
project(formatter_ex)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(formatter_ex STATIC formatter_ex.cpp)
target_include_directories(formatter_ex PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(formatter_ex PUBLIC formatter)

if(ENABLE_COVERAGE)
    target_compile_options(formatter_ex PRIVATE --coverage -g -O0)
    target_link_options(formatter_ex PRIVATE --coverage)
endif()

install(TARGETS formatter_ex
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
