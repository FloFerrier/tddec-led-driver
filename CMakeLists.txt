cmake_minimum_required(VERSION 3.20)
project(tddec-led-driver)

include(FetchContent)
FetchContent_Declare(
    CppUTest
    GIT_REPOSITORY https://github.com/cpputest/cpputest.git
    GIT_TAG        v4.0
)
set(TESTS OFF CACHE BOOL "Switch off CppUTest Test build")
FetchContent_MakeAvailable(CppUTest)

enable_testing()

add_library(LedDriver src/LedDriver.c)
target_include_directories(LedDriver PUBLIC inc)

add_executable(test_LedDriver
    tests/AllTests.cpp
    tests/LedDriverTest.cpp
)

target_link_libraries(test_LedDriver PRIVATE
    LedDriver
    CppUTest
)

add_test(NAME test_LedDriver COMMAND test_LedDriver)
