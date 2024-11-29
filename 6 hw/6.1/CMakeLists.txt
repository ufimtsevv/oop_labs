cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(5_hw VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ON - сборка с тестами, OFF - без
option(BUILD_TESTING "Build the testing tree." OFF)

if(BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        SOURCE_DIR "googletest-main"
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(googletest)
    enable_testing()

    add_executable(5_hw tests.cpp time.h)

    target_link_libraries(5_hw GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(5_hw)
else()
    add_executable(5_hw main.cpp time.hpp) 
endif()
