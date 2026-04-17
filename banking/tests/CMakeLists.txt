cmake_minimum_required(VERSION 3.10)

project(banking_tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ищем библиотеки
find_library(GTEST_LIB gtest /usr/lib /usr/local/lib)
find_library(GTEST_MAIN_LIB gtest_main /usr/lib /usr/local/lib)
find_library(GMOCK_LIB gmock /usr/lib /usr/local/lib)

add_executable(run_tests
    test_account.cpp
    test_transaction.cpp
    ../Account.cpp
    ../Transaction.cpp
)

target_link_libraries(run_tests 
    ${GTEST_LIB}
    ${GTEST_MAIN_LIB}
    ${GMOCK_LIB}
    pthread
)

target_include_directories(run_tests PRIVATE ..)

include(GoogleTest)
gtest_discover_tests(run_tests)
