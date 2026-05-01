cmake_minimum_required(VERSION 3.14)

project(Lab6)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# НЕ добавляем принудительный /MT - оставляем стандартное поведение
# Windows по умолчанию использует /MD, что совместимо с gtest_force_shared_crt ON

if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -g -O0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex_lib)
add_subdirectory(banking)
add_subdirectory(solver_lib)
add_subdirectory(solver_application)
add_subdirectory(tests)

include(CPackConfig.cmake)
