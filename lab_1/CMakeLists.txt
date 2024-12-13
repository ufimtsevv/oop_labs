cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(1b VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTING "Build the testing tree." ON)

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

    add_executable(1b tests.cpp ring_buffer.hpp)

    target_link_libraries(1b GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(1b)
else()
    add_executable(1b main.cpp ring_buffer.hpp) 
endif()
