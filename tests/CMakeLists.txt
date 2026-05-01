cmake_minimum_required(VERSION 3.14)

project(banking_tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Для Windows: используем единый RuntimeLibrary
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
endif()

# Для всех: отключаем -Werror (особенно важно для macOS)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    add_compile_options(-Wno-error)
    add_compile_options(-Wno-maybe-uninitialized)
endif()

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0
)

set(INSTALL_GTEST OFF)
set(gtest_force_shared_crt ON)

FetchContent_MakeAvailable(googletest)

add_executable(run_tests
    main.cpp
    test_account.cpp
    test_transaction.cpp
    mock_account.h
)

target_include_directories(run_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(run_tests
    banking
    gtest_main
    gmock
)

# pthread только для Unix-систем
if(UNIX AND NOT APPLE)
    target_link_libraries(run_tests pthread)
endif()

if(ENABLE_COVERAGE)
    target_compile_options(run_tests PRIVATE --coverage -g -O0)
    target_link_options(run_tests PRIVATE --coverage)
endif()

include(GoogleTest)
gtest_discover_tests(run_tests)
