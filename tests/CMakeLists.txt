cmake_minimum_required(VERSION 3.14)

project(banking_tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    pthread
)

if(ENABLE_COVERAGE)
    target_compile_options(run_tests PRIVATE --coverage -g -O0)
    target_link_options(run_tests PRIVATE --coverage)
endif()

include(GoogleTest)
gtest_discover_tests(run_tests)
почему с такими тестами все работало, а сейчас не работает
