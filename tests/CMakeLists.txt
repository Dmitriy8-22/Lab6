cmake_minimum_required(VERSION 3.14)

project(banking_tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Принудительно используем /MD для всех таргетов на Windows
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
    # Отключаем предупреждения о несовместимости
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
endif()

# Отключаем -Werror для Unix систем
if(UNIX AND NOT APPLE)
    add_compile_options(-Wno-error -Wno-maybe-uninitialized)
endif()

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0
)

# Настройки для googletest
set(INSTALL_GTEST OFF)
set(gtest_force_shared_crt ON)  # Заставляет googletest использовать /MD

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

# pthread только для Linux (не для macOS и Windows)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(run_tests pthread)
endif()

if(ENABLE_COVERAGE)
    target_compile_options(run_tests PRIVATE --coverage -g -O0)
    target_link_options(run_tests PRIVATE --coverage)
endif()

include(GoogleTest)
gtest_discover_tests(run_tests)
