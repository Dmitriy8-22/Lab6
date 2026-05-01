cmake_minimum_required(VERSION 3.14)
project(solver_app)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(solver_app equation.cpp)

target_link_libraries(solver_app PRIVATE solver formatter_ex)

# Установка бинарного файла для CPack
install(TARGETS solver_app
    RUNTIME DESTINATION bin
)

if(ENABLE_COVERAGE)
    target_compile_options(solver_app PRIVATE --coverage -g -O0)
    target_link_options(solver_app PRIVATE --coverage)
endif()
